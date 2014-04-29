namespace XnatWebBrowser.View.WinForms.Configuration
{
    partial class XnatConfigurationComponentControl
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
            this._xnatUrlLabel = new System.Windows.Forms.Label();
            this._xnatUrlTextBox = new System.Windows.Forms.TextBox();
            this._autoImportDownloadFolderLabel = new System.Windows.Forms.Label();
            this._autoImportDownloadFolderTextBox = new System.Windows.Forms.TextBox();
            this._autoImportDownloadFolderButton = new System.Windows.Forms.Button();
            this._downloadCheckIntervalNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this._checkForDownloadsEveryLabel = new System.Windows.Forms.Label();
            this._secondsLabel = new System.Windows.Forms.Label();
            this._folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this._downloadCheckIntervalNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // _xnatUrlLabel
            // 
            this._xnatUrlLabel.AutoSize = true;
            this._xnatUrlLabel.Location = new System.Drawing.Point(0, 5);
            this._xnatUrlLabel.Name = "_xnatUrlLabel";
            this._xnatUrlLabel.Size = new System.Drawing.Size(64, 13);
            this._xnatUrlLabel.TabIndex = 10;
            this._xnatUrlLabel.Text = "XNAT URL:";
            // 
            // _xnatUrlTextBox
            // 
            this._xnatUrlTextBox.AcceptsReturn = true;
            this._xnatUrlTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._xnatUrlTextBox.Location = new System.Drawing.Point(0, 24);
            this._xnatUrlTextBox.Margin = new System.Windows.Forms.Padding(2);
            this._xnatUrlTextBox.Name = "_xnatUrlTextBox";
            this._xnatUrlTextBox.Size = new System.Drawing.Size(301, 20);
            this._xnatUrlTextBox.TabIndex = 9;
            // 
            // _autoImportDownloadFolderLabel
            // 
            this._autoImportDownloadFolderLabel.AutoSize = true;
            this._autoImportDownloadFolderLabel.Location = new System.Drawing.Point(3, 55);
            this._autoImportDownloadFolderLabel.Name = "_autoImportDownloadFolderLabel";
            this._autoImportDownloadFolderLabel.Size = new System.Drawing.Size(147, 13);
            this._autoImportDownloadFolderLabel.TabIndex = 12;
            this._autoImportDownloadFolderLabel.Text = "Auto Import Download Folder:";
            // 
            // _autoImportDownloadFolderTextBox
            // 
            this._autoImportDownloadFolderTextBox.AcceptsReturn = true;
            this._autoImportDownloadFolderTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._autoImportDownloadFolderTextBox.Location = new System.Drawing.Point(3, 74);
            this._autoImportDownloadFolderTextBox.Margin = new System.Windows.Forms.Padding(2);
            this._autoImportDownloadFolderTextBox.Name = "_autoImportDownloadFolderTextBox";
            this._autoImportDownloadFolderTextBox.Size = new System.Drawing.Size(301, 20);
            this._autoImportDownloadFolderTextBox.TabIndex = 11;
            // 
            // _autoImportDownloadFolderButton
            // 
            this._autoImportDownloadFolderButton.Location = new System.Drawing.Point(349, 75);
            this._autoImportDownloadFolderButton.Name = "_autoImportDownloadFolderButton";
            this._autoImportDownloadFolderButton.Size = new System.Drawing.Size(25, 17);
            this._autoImportDownloadFolderButton.TabIndex = 13;
            this._autoImportDownloadFolderButton.Text = "...";
            this._autoImportDownloadFolderButton.UseVisualStyleBackColor = true;
            this._autoImportDownloadFolderButton.Click += new System.EventHandler(this.AutoImportDownloadFolderButtonClick);
            // 
            // _downloadCheckIntervalNumericUpDown
            // 
            this._downloadCheckIntervalNumericUpDown.Location = new System.Drawing.Point(6, 125);
            this._downloadCheckIntervalNumericUpDown.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this._downloadCheckIntervalNumericUpDown.Name = "_downloadCheckIntervalNumericUpDown";
            this._downloadCheckIntervalNumericUpDown.Size = new System.Drawing.Size(58, 20);
            this._downloadCheckIntervalNumericUpDown.TabIndex = 14;
            // 
            // _checkForDownloadsEveryLabel
            // 
            this._checkForDownloadsEveryLabel.AutoSize = true;
            this._checkForDownloadsEveryLabel.Location = new System.Drawing.Point(3, 105);
            this._checkForDownloadsEveryLabel.Name = "_checkForDownloadsEveryLabel";
            this._checkForDownloadsEveryLabel.Size = new System.Drawing.Size(136, 13);
            this._checkForDownloadsEveryLabel.TabIndex = 15;
            this._checkForDownloadsEveryLabel.Text = "Check for downloads every";
            // 
            // _secondsLabel
            // 
            this._secondsLabel.AutoSize = true;
            this._secondsLabel.Location = new System.Drawing.Point(70, 127);
            this._secondsLabel.Name = "_secondsLabel";
            this._secondsLabel.Size = new System.Drawing.Size(47, 13);
            this._secondsLabel.TabIndex = 16;
            this._secondsLabel.Text = "seconds";
            // 
            // XnatConfigurationComponentControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this._secondsLabel);
            this.Controls.Add(this._checkForDownloadsEveryLabel);
            this.Controls.Add(this._downloadCheckIntervalNumericUpDown);
            this.Controls.Add(this._autoImportDownloadFolderButton);
            this.Controls.Add(this._autoImportDownloadFolderLabel);
            this.Controls.Add(this._autoImportDownloadFolderTextBox);
            this.Controls.Add(this._xnatUrlLabel);
            this.Controls.Add(this._xnatUrlTextBox);
            this.Name = "XnatConfigurationComponentControl";
            this.Size = new System.Drawing.Size(428, 212);
            ((System.ComponentModel.ISupportInitialize)(this._downloadCheckIntervalNumericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _xnatUrlLabel;
        private System.Windows.Forms.TextBox _xnatUrlTextBox;
        private System.Windows.Forms.Label _autoImportDownloadFolderLabel;
        private System.Windows.Forms.TextBox _autoImportDownloadFolderTextBox;
        private System.Windows.Forms.Button _autoImportDownloadFolderButton;
        private System.Windows.Forms.NumericUpDown _downloadCheckIntervalNumericUpDown;
        private System.Windows.Forms.Label _checkForDownloadsEveryLabel;
        private System.Windows.Forms.Label _secondsLabel;
        private System.Windows.Forms.FolderBrowserDialog _folderBrowserDialog;
    }
}
