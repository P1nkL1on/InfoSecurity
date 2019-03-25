namespace Infobez_Cesar
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.encoded = new System.Windows.Forms.TextBox();
            this.decoded = new System.Windows.Forms.TextBox();
            this.decode = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // encoded
            // 
            this.encoded.Location = new System.Drawing.Point(13, 53);
            this.encoded.Multiline = true;
            this.encoded.Name = "encoded";
            this.encoded.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.encoded.Size = new System.Drawing.Size(404, 524);
            this.encoded.TabIndex = 0;
            this.encoded.Text = resources.GetString("encoded.Text");
            // 
            // decoded
            // 
            this.decoded.Location = new System.Drawing.Point(423, 53);
            this.decoded.Multiline = true;
            this.decoded.Name = "decoded";
            this.decoded.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.decoded.Size = new System.Drawing.Size(428, 524);
            this.decoded.TabIndex = 1;
            // 
            // decode
            // 
            this.decode.Location = new System.Drawing.Point(393, 12);
            this.decode.Name = "decode";
            this.decode.Size = new System.Drawing.Size(47, 23);
            this.decode.TabIndex = 2;
            this.decode.Text = "->";
            this.decode.UseVisualStyleBackColor = true;
            this.decode.Click += new System.EventHandler(this.decode_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(863, 589);
            this.Controls.Add(this.decode);
            this.Controls.Add(this.decoded);
            this.Controls.Add(this.encoded);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox encoded;
        private System.Windows.Forms.TextBox decoded;
        private System.Windows.Forms.Button decode;
    }
}

