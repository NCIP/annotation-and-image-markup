namespace AIMTemplateService.View.WinForms.Configuration
{
    partial class AtsConfigurationComponentControl
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
            this._txtAtsUrl = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this._checkBoxAutomaticallyImportTemplates = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // _txtAtsUrl
            // 
            this._txtAtsUrl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._txtAtsUrl.Location = new System.Drawing.Point(3, 37);
            this._txtAtsUrl.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this._txtAtsUrl.Name = "_txtAtsUrl";
            this._txtAtsUrl.Size = new System.Drawing.Size(434, 22);
            this._txtAtsUrl.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 10);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(181, 17);
            this.label1.TabIndex = 6;
            this.label1.Text = "AIM Template Service URL:";
            // 
            // _checkBoxAutomaticallyImportTemplates
            // 
            this._checkBoxAutomaticallyImportTemplates.AutoSize = true;
            this._checkBoxAutomaticallyImportTemplates.Location = new System.Drawing.Point(3, 65);
            this._checkBoxAutomaticallyImportTemplates.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this._checkBoxAutomaticallyImportTemplates.Name = "_checkBoxAutomaticallyImportTemplates";
            this._checkBoxAutomaticallyImportTemplates.Size = new System.Drawing.Size(403, 21);
            this._checkBoxAutomaticallyImportTemplates.TabIndex = 7;
            this._checkBoxAutomaticallyImportTemplates.Text = "Automatically import downloaded templates into workstation";
            this._checkBoxAutomaticallyImportTemplates.UseVisualStyleBackColor = true;
            // 
            // AtsConfigurationComponentControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this._checkBoxAutomaticallyImportTemplates);
            this.Controls.Add(this.label1);
            this.Controls.Add(this._txtAtsUrl);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "AtsConfigurationComponentControl";
            this.Size = new System.Drawing.Size(444, 186);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox _txtAtsUrl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox _checkBoxAutomaticallyImportTemplates;
    }
}
