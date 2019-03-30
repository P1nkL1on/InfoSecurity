namespace ImageDecodeComparer
{
    partial class Form1
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
            this.panelImage1 = new System.Windows.Forms.Panel();
            this.panelImage2 = new System.Windows.Forms.Panel();
            this.panelImage3 = new System.Windows.Forms.Panel();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.buttonBack = new System.Windows.Forms.Button();
            this.buttonForward = new System.Windows.Forms.Button();
            this.buttonComparer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // panelImage1
            // 
            this.panelImage1.AutoSize = true;
            this.panelImage1.Location = new System.Drawing.Point(13, 13);
            this.panelImage1.Name = "panelImage1";
            this.panelImage1.Size = new System.Drawing.Size(278, 375);
            this.panelImage1.TabIndex = 0;
            // 
            // panelImage2
            // 
            this.panelImage2.AutoSize = true;
            this.panelImage2.Location = new System.Drawing.Point(297, 13);
            this.panelImage2.Name = "panelImage2";
            this.panelImage2.Size = new System.Drawing.Size(278, 375);
            this.panelImage2.TabIndex = 1;
            // 
            // panelImage3
            // 
            this.panelImage3.AutoSize = true;
            this.panelImage3.Location = new System.Drawing.Point(581, 13);
            this.panelImage3.Name = "panelImage3";
            this.panelImage3.Size = new System.Drawing.Size(278, 375);
            this.panelImage3.TabIndex = 1;
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(13, 395);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(278, 23);
            this.buttonLoad.TabIndex = 2;
            this.buttonLoad.Text = "Load Image Seqence";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // buttonBack
            // 
            this.buttonBack.Location = new System.Drawing.Point(581, 394);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(75, 23);
            this.buttonBack.TabIndex = 3;
            this.buttonBack.Text = "<-";
            this.buttonBack.UseVisualStyleBackColor = true;
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // buttonForward
            // 
            this.buttonForward.Location = new System.Drawing.Point(784, 394);
            this.buttonForward.Name = "buttonForward";
            this.buttonForward.Size = new System.Drawing.Size(75, 23);
            this.buttonForward.TabIndex = 4;
            this.buttonForward.Text = "->";
            this.buttonForward.UseVisualStyleBackColor = true;
            this.buttonForward.Click += new System.EventHandler(this.buttonForward_Click);
            // 
            // buttonComparer
            // 
            this.buttonComparer.Location = new System.Drawing.Point(401, 395);
            this.buttonComparer.Name = "buttonComparer";
            this.buttonComparer.Size = new System.Drawing.Size(75, 23);
            this.buttonComparer.TabIndex = 5;
            this.buttonComparer.Text = "compare";
            this.buttonComparer.UseVisualStyleBackColor = true;
            this.buttonComparer.Click += new System.EventHandler(this.buttonComparer_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(880, 425);
            this.Controls.Add(this.buttonComparer);
            this.Controls.Add(this.buttonForward);
            this.Controls.Add(this.buttonBack);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.panelImage3);
            this.Controls.Add(this.panelImage2);
            this.Controls.Add(this.panelImage1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panelImage1;
        private System.Windows.Forms.Panel panelImage2;
        private System.Windows.Forms.Panel panelImage3;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonBack;
        private System.Windows.Forms.Button buttonForward;
        private System.Windows.Forms.Button buttonComparer;
    }
}

