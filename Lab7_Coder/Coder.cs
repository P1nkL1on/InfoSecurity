using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;

namespace PictureShifrator
{
    class Coder
    {
        Image image;
        int bCount = 7;
        public void setBCount(int X) { this.bCount = X; }

        public Coder(Image image)
        {
            this.image = image;
        }

        public Image Code(string message)
        {
            List<int> resCode = new List<int>();
            for (int i = 0; i < message.Length; i++)
            {
                char c = message[i];
                resCode.AddRange(CharTo01(c));
            }
            int added = 0;
            while ((resCode.Count % 3 != 0 || resCode.Count % bCount != 0) && added < bCount * 2)
            { resCode.Add(0); ++added; }  // to clear pixel format



            Bitmap b = (Bitmap)image;
            int nowBit = 0;
            for (int i = 0; i < b.Height; i++)
                for (int j = 0; j < b.Width; j++)
                    if (nowBit * 3 < resCode.Count)
                    {
                        b.SetPixel(j, i, TransformPixel(b.GetPixel(j, i), resCode[nowBit * 3], resCode[nowBit * 3 + 1], resCode[nowBit * 3 + 2]));
                        nowBit++;
                    }
            if (nowBit * 3 < resCode.Count)
                throw new Exception("Image is too small to code this message. Try to use image with at least " + resCode.Count / 3 + " px size.");
            //image = (Image)b;
            //b.Save("coded1.png");
            return (Image)b;
        }

        public string Decode()
        {
            string res = "";
            bool eof = false;
            Bitmap b = (Bitmap)image;
            currentCode.Clear();

            for (int i = 0; i < b.Height; i++)
                for (int j = 0; j < b.Width; j++)
                    if (!eof)
                    {
                        currentCode.AddRange(PixelToByte(b.GetPixel(j, i)));
                        res += Transform01ToStr(ref currentCode, out eof);
                    }

            return res;
        }

        string Transform01ToStr(ref List<int> list, out bool eof)
        {
            string s = ""; eof = false;
            while (list.Count >= bCount)
            {
                int summ = 0;
                for (int i = 0; i < bCount; i++)
                    summ += (int)Math.Pow(2, i) * list[bCount - i - 1];
               
                eof = (summ == 0);
                s += ((!eof) ? ((char)summ) : ' ');

                list.RemoveRange(0, bCount);
            }
            return s;
        }

        List<int> currentCode = new List<int>();

        int[] CharTo01(char c)
        {
            int[] res = new int[bCount];
            int cN = (int)c;
            currentCode.Clear();
            while (cN > 0)
            {
                currentCode.Add(cN % 2);
                cN /= 2;
            }
            if (currentCode.Count > bCount)
                throw new Exception("Can not use symbol \'" + c + "\' with a bit lenght " + currentCode.Count + ", because current bit length is " + bCount + ".");
            for (int i = 0; i < currentCode.Count; i++)
                res[bCount - currentCode.Count + i] = currentCode[currentCode.Count - 1 - i];
            return res;
        }

        Color TransformPixel(Color clr, int v0, int v1, int v2)
        {
            int cR = clr.R, cG = clr.G, cB = clr.B;
            if (v0 % 2 != cR % 2) cR++;
            if (v1 % 2 != cG % 2) cG++;
            if (v2 % 2 != cB % 2) cB++;
            if (cR > 255) cR -= 2;
            if (cG > 255) cG -= 2;
            if (cB > 255) cB -= 2;
            return Color.FromArgb(cR, cG, cB);
        }

        int[] PixelToByte(Color clr)
        {
            return new int[] { clr.R % 2, clr.G % 2, clr.B % 2 };
        }

    }
}
