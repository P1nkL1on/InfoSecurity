using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageDecodeComparer
{
    public partial class Form1 : Form
    {
        private ImageComparer ic = new ImageComparer();

        public Form1()
        {
            InitializeComponent();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            if (!ic.loadImageSequence())
                return;
            updatePics();
            buttonBack.Enabled = buttonForward.Enabled = ic.isMoreThan2;
        }
        private void updatePics()
        {
            panelImage1.CreateGraphics().DrawImage(ic.getPicture1, new Rectangle(0, 0, panelImage1.Width, panelImage1.Height));
            panelImage2.CreateGraphics().DrawImage(ic.getPicture2, new Rectangle(0, 0, panelImage2.Width, panelImage2.Height));
        }
        private void updateComparer()
        {
            panelImage3.CreateGraphics().DrawImage(ic.getComparer, new Rectangle(0, 0, panelImage3.Width, panelImage3.Height));
        }

        private void buttonBack_Click(object sender, EventArgs e)
        {
            ic.prev();
            updatePics();
        }

        private void buttonForward_Click(object sender, EventArgs e)
        {
            ic.next();
            updatePics();
        }

        private void buttonComparer_Click(object sender, EventArgs e)
        {
            ic.calculateDifferentPixels();
            updateComparer();
        }
    }
}
