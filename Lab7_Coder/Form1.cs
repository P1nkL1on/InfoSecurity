using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;

namespace PictureShifrator
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            bitCount.Enabled = button2.Enabled = button4.Enabled = false;
        }

        Coder coder;

        private void Load(object sender, EventArgs e)
        {
            OpenFileDialog f = new OpenFileDialog();
            if (f.ShowDialog() == DialogResult.OK)
            {
                System.IO.FileStream fs = new System.IO.FileStream(f.FileName, System.IO.FileMode.Open);
                Image img = System.Drawing.Image.FromStream(fs);
                fs.Close();
                //
                coder = new Coder(img);
                pictureBox.Image = img;
                pictureLabel.Text = f.FileName;
                bitCount.Enabled = button2.Enabled = button4.Enabled = true;
            }
        }
        private void Code(object sender, EventArgs e)
        {
            //try
            //{
            Image res = coder.Code(textCode.Text);
            MessageBox.Show("Coding success!");

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "Images|*.png;*.bmp;*.jpg";
            ImageFormat format = ImageFormat.Png;
            if (sfd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string ext = System.IO.Path.GetExtension(sfd.FileName);
                switch (ext)
                {
                    case ".jpg":
                        format = ImageFormat.Jpeg;
                        break;
                    case ".bmp":
                        format = ImageFormat.Bmp;
                        break;
                }
                res.Save(sfd.FileName, format);
                label1.Text = "Last save: " + sfd.FileName;
            }
            //}
            //catch (Exception ex) { MessageBox.Show(ex.Message); }
        }
        private void Decode(object sender, EventArgs e)
        {
            textCode.Text = coder.Decode();
            MessageBox.Show("Decoded!");
        }

        private void bitCount_ValueChanged(object sender, EventArgs e)
        {
            coder.setBCount((int)bitCount.Value);
        }
    }
}
