//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace AIM.Annotation.View.WinForms.Configuration
{
    partial class AimConfigurationComponentControl
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
			this._chkSendToGrid = new System.Windows.Forms.CheckBox();
			this._chkStoreAnnotationsLocally = new System.Windows.Forms.CheckBox();
			this._radStoreInMyDocuments = new System.Windows.Forms.RadioButton();
			this._radStoreInFolder = new System.Windows.Forms.RadioButton();
			this._folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
			this._btnBrowseForAnnotationsFolder = new System.Windows.Forms.Button();
			this._txtLocalAnnotationsFolderLocation = new System.Windows.Forms.TextBox();
			this._chkRequireUserInfo = new System.Windows.Forms.CheckBox();
			this._chkRequireMarkupInAnnotation = new System.Windows.Forms.CheckBox();
			this.lblTemplatesFolder = new System.Windows.Forms.Label();
			this._txtLocalTemplatesFolderLocation = new System.Windows.Forms.TextBox();
			this._btnBrowseForTemplatesFolder = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// _chkSendToGrid
			// 
			this._chkSendToGrid.AutoSize = true;
			this._chkSendToGrid.Location = new System.Drawing.Point(4, 4);
			this._chkSendToGrid.Name = "_chkSendToGrid";
			this._chkSendToGrid.Size = new System.Drawing.Size(235, 21);
			this._chkSendToGrid.TabIndex = 0;
			this._chkSendToGrid.Text = "Send New Annotations to ca&Grid";
			this._chkSendToGrid.UseVisualStyleBackColor = true;
			// 
			// _chkStoreAnnotationsLocally
			// 
			this._chkStoreAnnotationsLocally.AutoSize = true;
			this._chkStoreAnnotationsLocally.Location = new System.Drawing.Point(4, 32);
			this._chkStoreAnnotationsLocally.Name = "_chkStoreAnnotationsLocally";
			this._chkStoreAnnotationsLocally.Size = new System.Drawing.Size(222, 21);
			this._chkStoreAnnotationsLocally.TabIndex = 1;
			this._chkStoreAnnotationsLocally.Text = "Store New Annotations &Locally";
			this._chkStoreAnnotationsLocally.UseVisualStyleBackColor = true;
			// 
			// _radStoreInMyDocuments
			// 
			this._radStoreInMyDocuments.AutoSize = true;
			this._radStoreInMyDocuments.Location = new System.Drawing.Point(24, 60);
			this._radStoreInMyDocuments.Name = "_radStoreInMyDocuments";
			this._radStoreInMyDocuments.Size = new System.Drawing.Size(175, 21);
			this._radStoreInMyDocuments.TabIndex = 2;
			this._radStoreInMyDocuments.TabStop = true;
			this._radStoreInMyDocuments.Text = "Store in &My Documents";
			this._radStoreInMyDocuments.UseVisualStyleBackColor = true;
			// 
			// _radStoreInFolder
			// 
			this._radStoreInFolder.AutoSize = true;
			this._radStoreInFolder.Location = new System.Drawing.Point(24, 88);
			this._radStoreInFolder.Name = "_radStoreInFolder";
			this._radStoreInFolder.Size = new System.Drawing.Size(82, 21);
			this._radStoreInFolder.TabIndex = 3;
			this._radStoreInFolder.TabStop = true;
			this._radStoreInFolder.Text = "Store in:";
			this._radStoreInFolder.UseVisualStyleBackColor = true;
			// 
			// _btnBrowseForAnnotationsFolder
			// 
			this._btnBrowseForAnnotationsFolder.Location = new System.Drawing.Point(457, 88);
			this._btnBrowseForAnnotationsFolder.Name = "_btnBrowseForAnnotationsFolder";
			this._btnBrowseForAnnotationsFolder.Size = new System.Drawing.Size(33, 21);
			this._btnBrowseForAnnotationsFolder.TabIndex = 5;
			this._btnBrowseForAnnotationsFolder.Text = "...";
			this._btnBrowseForAnnotationsFolder.UseVisualStyleBackColor = true;
			this._btnBrowseForAnnotationsFolder.Click += new System.EventHandler(this._btnBrowseForAnnotationsFolder_Click);
			// 
			// _txtLocalAnnotationsFolderLocation
			// 
			this._txtLocalAnnotationsFolderLocation.Location = new System.Drawing.Point(112, 87);
			this._txtLocalAnnotationsFolderLocation.Name = "_txtLocalAnnotationsFolderLocation";
			this._txtLocalAnnotationsFolderLocation.Size = new System.Drawing.Size(339, 22);
			this._txtLocalAnnotationsFolderLocation.TabIndex = 4;
			// 
			// _chkRequireUserInfo
			// 
			this._chkRequireUserInfo.AutoSize = true;
			this._chkRequireUserInfo.Location = new System.Drawing.Point(4, 115);
			this._chkRequireUserInfo.Name = "_chkRequireUserInfo";
			this._chkRequireUserInfo.Size = new System.Drawing.Size(188, 21);
			this._chkRequireUserInfo.TabIndex = 6;
			this._chkRequireUserInfo.Text = "Require &User Information";
			this._chkRequireUserInfo.UseVisualStyleBackColor = true;
			// 
			// _chkRequireMarkupInAnnotation
			// 
			this._chkRequireMarkupInAnnotation.AutoSize = true;
			this._chkRequireMarkupInAnnotation.Location = new System.Drawing.Point(4, 142);
			this._chkRequireMarkupInAnnotation.Name = "_chkRequireMarkupInAnnotation";
			this._chkRequireMarkupInAnnotation.Size = new System.Drawing.Size(272, 21);
			this._chkRequireMarkupInAnnotation.TabIndex = 7;
			this._chkRequireMarkupInAnnotation.Text = "Require Graphic &Markup in Annotation";
			this._chkRequireMarkupInAnnotation.UseVisualStyleBackColor = true;
			// 
			// lblTemplatesFolder
			// 
			this.lblTemplatesFolder.AutoSize = true;
			this.lblTemplatesFolder.Location = new System.Drawing.Point(1, 171);
			this.lblTemplatesFolder.Name = "lblTemplatesFolder";
			this.lblTemplatesFolder.Size = new System.Drawing.Size(122, 17);
			this.lblTemplatesFolder.TabIndex = 8;
			this.lblTemplatesFolder.Text = "Templates Folder:";
			// 
			// _txtLocalTemplatesFolderLocation
			// 
			this._txtLocalTemplatesFolderLocation.Location = new System.Drawing.Point(4, 191);
			this._txtLocalTemplatesFolderLocation.Name = "_txtLocalTemplatesFolderLocation";
			this._txtLocalTemplatesFolderLocation.Size = new System.Drawing.Size(447, 22);
			this._txtLocalTemplatesFolderLocation.TabIndex = 9;
			// 
			// _btnBrowseForTemplatesFolder
			// 
			this._btnBrowseForTemplatesFolder.Location = new System.Drawing.Point(457, 192);
			this._btnBrowseForTemplatesFolder.Name = "_btnBrowseForTemplatesFolder";
			this._btnBrowseForTemplatesFolder.Size = new System.Drawing.Size(33, 21);
			this._btnBrowseForTemplatesFolder.TabIndex = 10;
			this._btnBrowseForTemplatesFolder.Text = "...";
			this._btnBrowseForTemplatesFolder.UseVisualStyleBackColor = true;
			this._btnBrowseForTemplatesFolder.Click += new System.EventHandler(this._btnBrowseForTemplatesFolder_Click);
			// 
			// AimConfigurationComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._btnBrowseForTemplatesFolder);
			this.Controls.Add(this._txtLocalTemplatesFolderLocation);
			this.Controls.Add(this.lblTemplatesFolder);
			this.Controls.Add(this._chkRequireMarkupInAnnotation);
			this.Controls.Add(this._chkRequireUserInfo);
			this.Controls.Add(this._btnBrowseForAnnotationsFolder);
			this.Controls.Add(this._txtLocalAnnotationsFolderLocation);
			this.Controls.Add(this._radStoreInFolder);
			this.Controls.Add(this._radStoreInMyDocuments);
			this.Controls.Add(this._chkStoreAnnotationsLocally);
			this.Controls.Add(this._chkSendToGrid);
			this.Name = "AimConfigurationComponentControl";
			this.Size = new System.Drawing.Size(545, 278);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private System.Windows.Forms.CheckBox _chkSendToGrid;
		private System.Windows.Forms.CheckBox _chkStoreAnnotationsLocally;
		private System.Windows.Forms.RadioButton _radStoreInMyDocuments;
		private System.Windows.Forms.RadioButton _radStoreInFolder;
		private System.Windows.Forms.FolderBrowserDialog _folderBrowserDialog;
		private System.Windows.Forms.Button _btnBrowseForAnnotationsFolder;
		private System.Windows.Forms.TextBox _txtLocalAnnotationsFolderLocation;
		private System.Windows.Forms.CheckBox _chkRequireUserInfo;
		private System.Windows.Forms.CheckBox _chkRequireMarkupInAnnotation;
		private System.Windows.Forms.Label lblTemplatesFolder;
		private System.Windows.Forms.TextBox _txtLocalTemplatesFolderLocation;
		private System.Windows.Forms.Button _btnBrowseForTemplatesFolder;
    }
}
