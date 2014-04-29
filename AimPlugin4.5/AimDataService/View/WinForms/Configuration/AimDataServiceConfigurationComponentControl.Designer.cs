namespace AimDataService.View.WinForms.Configuration
{
    partial class AimDataServiceConfigurationComponentControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this._aimDataServiceUrlLabel = new System.Windows.Forms.Label();
            this._aimDataServiceUrlTextBox = new System.Windows.Forms.TextBox();
            this._secureTokenServiceLoginUrl = new System.Windows.Forms.Label();
            this._secureTokenServiceLoginUrlTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // _aimDataServiceUrlLabel
            // 
            this._aimDataServiceUrlLabel.AutoSize = true;
            this._aimDataServiceUrlLabel.Location = new System.Drawing.Point(7, 10);
            this._aimDataServiceUrlLabel.Name = "_aimDataServiceUrlLabel";
            this._aimDataServiceUrlLabel.Size = new System.Drawing.Size(119, 13);
            this._aimDataServiceUrlLabel.TabIndex = 8;
            this._aimDataServiceUrlLabel.Text = "AIM Data Service URL:";
            // 
            // _aimDataServiceUrlTextBox
            // 
            this._aimDataServiceUrlTextBox.AcceptsReturn = true;
            this._aimDataServiceUrlTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._aimDataServiceUrlTextBox.Location = new System.Drawing.Point(7, 32);
            this._aimDataServiceUrlTextBox.Margin = new System.Windows.Forms.Padding(2);
            this._aimDataServiceUrlTextBox.Name = "_aimDataServiceUrlTextBox";
            this._aimDataServiceUrlTextBox.Size = new System.Drawing.Size(301, 20);
            this._aimDataServiceUrlTextBox.TabIndex = 7;
            // 
            // _secureTokenServiceLoginUrl
            // 
            this._secureTokenServiceLoginUrl.AutoSize = true;
            this._secureTokenServiceLoginUrl.Location = new System.Drawing.Point(5, 67);
            this._secureTokenServiceLoginUrl.Name = "_secureTokenServiceLoginUrl";
            this._secureTokenServiceLoginUrl.Size = new System.Drawing.Size(171, 13);
            this._secureTokenServiceLoginUrl.TabIndex = 10;
            this._secureTokenServiceLoginUrl.Text = "Secure Token Service Login URL:";
            // 
            // _secureTokenServiceLoginUrlTextBox
            // 
            this._secureTokenServiceLoginUrlTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._secureTokenServiceLoginUrlTextBox.Location = new System.Drawing.Point(5, 89);
            this._secureTokenServiceLoginUrlTextBox.Margin = new System.Windows.Forms.Padding(2);
            this._secureTokenServiceLoginUrlTextBox.Name = "_secureTokenServiceLoginUrlTextBox";
            this._secureTokenServiceLoginUrlTextBox.Size = new System.Drawing.Size(301, 20);
            this._secureTokenServiceLoginUrlTextBox.TabIndex = 9;
            // 
            // AimDataServiceConfigurationComponentControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this._secureTokenServiceLoginUrl);
            this.Controls.Add(this._secureTokenServiceLoginUrlTextBox);
            this.Controls.Add(this._aimDataServiceUrlLabel);
            this.Controls.Add(this._aimDataServiceUrlTextBox);
            this.Name = "AimDataServiceConfigurationComponentControl";
            this.Size = new System.Drawing.Size(310, 150);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _aimDataServiceUrlLabel;
        private System.Windows.Forms.TextBox _aimDataServiceUrlTextBox;
        private System.Windows.Forms.Label _secureTokenServiceLoginUrl;
        private System.Windows.Forms.TextBox _secureTokenServiceLoginUrlTextBox;
    }
}
