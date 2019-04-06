using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace ImageDecodeComparer
{
    class ImageComparer
    {
        public ImageComparer()
        {
            comparer = zeroBitmap;
        }
        private Bitmap zeroBitmap = new Bitmap(@"..\..\test.png");
        private int currentIndex = 0;
        private List<Bitmap> pics;
        private Bitmap comparer = new Bitmap(@"..\..\test.png");
        private Bitmap comparer2 = new Bitmap(@"..\..\test.png");
        public string[] ListFiles()
        {
            using (OpenFileDialog file = new OpenFileDialog())
            {
                file.InitialDirectory = @"C:\Users\lion6_000\Documents\unver.infbez\InfoSecurity\images_lab_6";
                //file.InitialDirectory = @"D:\univer\4 kurs\2 semestr\infobez\InfoSecurity\images_lab_6";
                file.Multiselect = true;
                file.Filter = "Pictures (PNG, BMP, JPEG, JPG, GIF)|*.png; *.bmp; *.jpeg; *.jpg; *.gif";
                file.ShowDialog();
                return file.FileNames;
            }
        }

        public Bitmap getPicture1
        {
            get
            {
                return (currentIndex * 2 >= pics.Count) ? zeroBitmap : pics[currentIndex * 2];
            }
        }
        public Bitmap getPicture2
        {
            get
            {
                return (currentIndex * 2 + 1 >= pics.Count) ? zeroBitmap : pics[currentIndex * 2 + 1];
            }
        }
        public bool loadImageSequence()
        {
            string[] adresses = ListFiles();
            int l = adresses.Length;
            int upto = l % 2 == 0 ? l : (l - 1);
            if (upto == 0)
            {
                MessageBox.Show("Please, load an even count of images!", "Error");
                return false;
            }
            pics = new List<Bitmap>();
            for (int i = 0; i < upto; ++i)
            {
                pics.Add(new Bitmap(adresses[i]));
            }
            currentIndex = 0;
            return true;
        }
        public void next()
        {
            currentIndex = (currentIndex + 1) % (pics.Count / 2);
        }
        public void prev()
        {
            currentIndex = (currentIndex > 0) ? (currentIndex - 1) : (pics.Count / 2 - 1);
        }
        public bool isMoreThan2
        {
            get { return pics.Count >= 4; }
        }
        public Bitmap getComparer { get { return comparer; } }
        public Bitmap getComparer2 { get { return comparer2; } }

        public void calculateDifferentPixels()
        {
            Bitmap p1 = getPicture1, p2 = getPicture2;
            comparer = new Bitmap(p1.Width, p2.Height);
            for (int i = 0; i < comparer.Width; ++i) for (int j = 0; j < comparer.Height; ++j)
                {
                    Color c1 = p1.GetPixel(i, j), c2 = p2.GetPixel(i, j);
                    comparer.SetPixel(i, j, c1 == c2 ? Color.White : Color.Red);
                }
        }

        public Bitmap getPixelLevel(Bitmap source, int level, int channel)
        {
            int levelMin = 2;
            for (int i = 0; i < level; ++i)
                levelMin *= 2;

            Bitmap res = new Bitmap(source.Width, source.Height);
            for (int i = 0; i < res.Width; ++i) for (int j = 0; j < res.Height; ++j)
                {
                    Color pix = source.GetPixel(i, j);
                    int val = channel == 1 ? pix.R : (channel == 2 ? pix.G : pix.B);
                    List<int> bin = new List<int>();
                    while (val > 0)
                    {
                        bin.Add(val % 2);
                        val /= 2;
                    }
                    bool is0 = level >= bin.Count || bin[level] == 0;
                    res.SetPixel(i, j, is0 ? Color.Black : Color.White);
                }

            return res;
        }
        public void calculateBitLevel(int level, int channel)
        {
            comparer = getPixelLevel(getPicture1, level, channel);
            comparer2 = getPixelLevel(getPicture2, level, channel);
        }
    }
}
