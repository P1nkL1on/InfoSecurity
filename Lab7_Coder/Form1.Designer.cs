namespace PictureShifrator
{
    partial class MainForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.textCode = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.pictureLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.bitCount = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bitCount)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(10, 13);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(56, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Load";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Load);
            // 
            // textCode
            // 
            this.textCode.Location = new System.Drawing.Point(185, 12);
            this.textCode.Multiline = true;
            this.textCode.Name = "textCode";
            this.textCode.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textCode.Size = new System.Drawing.Size(500, 420);
            this.textCode.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(10, 42);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(56, 49);
            this.button2.TabIndex = 2;
            this.button2.Text = "Code and save";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Code);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(10, 97);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(56, 23);
            this.button4.TabIndex = 4;
            this.button4.Text = "Decode";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Decode);
            // 
            // pictureBox
            // 
            this.pictureBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox.InitialImage = null;
            this.pictureBox.Location = new System.Drawing.Point(10, 240);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(169, 172);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox.TabIndex = 5;
            this.pictureBox.TabStop = false;
            // 
            // pictureLabel
            // 
            this.pictureLabel.AutoSize = true;
            this.pictureLabel.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.pictureLabel.Location = new System.Drawing.Point(7, 419);
            this.pictureLabel.Name = "pictureLabel";
            this.pictureLabel.Size = new System.Drawing.Size(82, 13);
            this.pictureLabel.TabIndex = 6;
            this.pictureLabel.Text = "TestPicture.png";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.label1.Location = new System.Drawing.Point(7, 435);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Last save: ";
            // 
            // bitCount
            // 
            this.bitCount.Location = new System.Drawing.Point(92, 16);
            this.bitCount.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.bitCount.Minimum = new decimal(new int[] {
            7,
            0,
            0,
            0});
            this.bitCount.Name = "bitCount";
            this.bitCount.Size = new System.Drawing.Size(74, 20);
            this.bitCount.TabIndex = 8;
            this.bitCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.bitCount.Value = new decimal(new int[] {
            7,
            0,
            0,
            0});
            this.bitCount.ValueChanged += new System.EventHandler(this.bitCount_ValueChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(697, 457);
            this.Controls.Add(this.bitCount);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureLabel);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textCode);
            this.Controls.Add(this.button1);
            this.Name = "MainForm";
            this.Text = "Picture Coder";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bitCount)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textCode;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Label pictureLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown bitCount;
    }
}

