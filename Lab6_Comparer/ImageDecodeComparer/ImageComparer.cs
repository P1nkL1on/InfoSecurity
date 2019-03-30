﻿using System;
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
        private Bitmap comparer;
        public string[] ListFiles()
        {
            using (OpenFileDialog file = new OpenFileDialog())
            {
                file.InitialDirectory = @"D:\univer\4 kurs\2 semestr\infobez\InfoSecurity\images_lab_6";
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
    }
}
