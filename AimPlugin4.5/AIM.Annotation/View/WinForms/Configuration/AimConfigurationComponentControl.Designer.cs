#region License

// Copyright (c) 2006-2007, ClearCanvas Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//    * Neither the name of ClearCanvas Inc. nor the names of its contributors 
//      may be used to endorse or promote products derived from this software without 
//      specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// OF SUCH DAMAGE.

#endregion

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
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts = new System.Windows.Forms.CheckBox();
            this._chkResetTemplateAfterAnnotationCreation = new System.Windows.Forms.CheckBox();
            this._chkAlwaysPromptOnRestoringTemplateData = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // _chkSendToGrid
            // 
            this._chkSendToGrid.AutoSize = true;
            this._chkSendToGrid.Location = new System.Drawing.Point(3, 3);
            this._chkSendToGrid.Margin = new System.Windows.Forms.Padding(2);
            this._chkSendToGrid.Name = "_chkSendToGrid";
            this._chkSendToGrid.Size = new System.Drawing.Size(212, 17);
            this._chkSendToGrid.TabIndex = 0;
            this._chkSendToGrid.Text = "Send New Annotations to &Data Service";
            this._chkSendToGrid.UseVisualStyleBackColor = true;
            // 
            // _chkStoreAnnotationsLocally
            // 
            this._chkStoreAnnotationsLocally.AutoSize = true;
            this._chkStoreAnnotationsLocally.Location = new System.Drawing.Point(3, 26);
            this._chkStoreAnnotationsLocally.Margin = new System.Windows.Forms.Padding(2);
            this._chkStoreAnnotationsLocally.Name = "_chkStoreAnnotationsLocally";
            this._chkStoreAnnotationsLocally.Size = new System.Drawing.Size(171, 17);
            this._chkStoreAnnotationsLocally.TabIndex = 1;
            this._chkStoreAnnotationsLocally.Text = "Store New Annotations &Locally";
            this._chkStoreAnnotationsLocally.UseVisualStyleBackColor = true;
            // 
            // _radStoreInMyDocuments
            // 
            this._radStoreInMyDocuments.AutoSize = true;
            this._radStoreInMyDocuments.Location = new System.Drawing.Point(18, 49);
            this._radStoreInMyDocuments.Margin = new System.Windows.Forms.Padding(2);
            this._radStoreInMyDocuments.Name = "_radStoreInMyDocuments";
            this._radStoreInMyDocuments.Size = new System.Drawing.Size(135, 17);
            this._radStoreInMyDocuments.TabIndex = 2;
            this._radStoreInMyDocuments.TabStop = true;
            this._radStoreInMyDocuments.Text = "Store in &My Documents";
            this._radStoreInMyDocuments.UseVisualStyleBackColor = true;
            // 
            // _radStoreInFolder
            // 
            this._radStoreInFolder.AutoSize = true;
            this._radStoreInFolder.Location = new System.Drawing.Point(18, 72);
            this._radStoreInFolder.Margin = new System.Windows.Forms.Padding(2);
            this._radStoreInFolder.Name = "_radStoreInFolder";
            this._radStoreInFolder.Size = new System.Drawing.Size(64, 17);
            this._radStoreInFolder.TabIndex = 3;
            this._radStoreInFolder.TabStop = true;
            this._radStoreInFolder.Text = "Store in:";
            this._radStoreInFolder.UseVisualStyleBackColor = true;
            // 
            // _btnBrowseForAnnotationsFolder
            // 
            this._btnBrowseForAnnotationsFolder.Location = new System.Drawing.Point(343, 72);
            this._btnBrowseForAnnotationsFolder.Margin = new System.Windows.Forms.Padding(2);
            this._btnBrowseForAnnotationsFolder.Name = "_btnBrowseForAnnotationsFolder";
            this._btnBrowseForAnnotationsFolder.Size = new System.Drawing.Size(25, 17);
            this._btnBrowseForAnnotationsFolder.TabIndex = 5;
            this._btnBrowseForAnnotationsFolder.Text = "...";
            this._btnBrowseForAnnotationsFolder.UseVisualStyleBackColor = true;
            this._btnBrowseForAnnotationsFolder.Click += new System.EventHandler(this._btnBrowseForAnnotationsFolder_Click);
            // 
            // _txtLocalAnnotationsFolderLocation
            // 
            this._txtLocalAnnotationsFolderLocation.Location = new System.Drawing.Point(84, 71);
            this._txtLocalAnnotationsFolderLocation.Margin = new System.Windows.Forms.Padding(2);
            this._txtLocalAnnotationsFolderLocation.Name = "_txtLocalAnnotationsFolderLocation";
            this._txtLocalAnnotationsFolderLocation.Size = new System.Drawing.Size(255, 20);
            this._txtLocalAnnotationsFolderLocation.TabIndex = 4;
            // 
            // _chkRequireUserInfo
            // 
            this._chkRequireUserInfo.AutoSize = true;
            this._chkRequireUserInfo.Location = new System.Drawing.Point(3, 93);
            this._chkRequireUserInfo.Margin = new System.Windows.Forms.Padding(2);
            this._chkRequireUserInfo.Name = "_chkRequireUserInfo";
            this._chkRequireUserInfo.Size = new System.Drawing.Size(143, 17);
            this._chkRequireUserInfo.TabIndex = 6;
            this._chkRequireUserInfo.Text = "Require &User Information";
            this._chkRequireUserInfo.UseVisualStyleBackColor = true;
            // 
            // _chkRequireMarkupInAnnotation
            // 
            this._chkRequireMarkupInAnnotation.AutoSize = true;
            this._chkRequireMarkupInAnnotation.Location = new System.Drawing.Point(3, 115);
            this._chkRequireMarkupInAnnotation.Margin = new System.Windows.Forms.Padding(2);
            this._chkRequireMarkupInAnnotation.Name = "_chkRequireMarkupInAnnotation";
            this._chkRequireMarkupInAnnotation.Size = new System.Drawing.Size(207, 17);
            this._chkRequireMarkupInAnnotation.TabIndex = 7;
            this._chkRequireMarkupInAnnotation.Text = "Require Graphic &Markup in Annotation";
            this._chkRequireMarkupInAnnotation.UseVisualStyleBackColor = true;
            // 
            // lblTemplatesFolder
            // 
            this.lblTemplatesFolder.AutoSize = true;
            this.lblTemplatesFolder.Location = new System.Drawing.Point(1, 214);
            this.lblTemplatesFolder.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblTemplatesFolder.Name = "lblTemplatesFolder";
            this.lblTemplatesFolder.Size = new System.Drawing.Size(91, 13);
            this.lblTemplatesFolder.TabIndex = 8;
            this.lblTemplatesFolder.Text = "Templates Folder:";
            // 
            // _txtLocalTemplatesFolderLocation
            // 
            this._txtLocalTemplatesFolderLocation.Location = new System.Drawing.Point(3, 230);
            this._txtLocalTemplatesFolderLocation.Margin = new System.Windows.Forms.Padding(2);
            this._txtLocalTemplatesFolderLocation.Name = "_txtLocalTemplatesFolderLocation";
            this._txtLocalTemplatesFolderLocation.Size = new System.Drawing.Size(336, 20);
            this._txtLocalTemplatesFolderLocation.TabIndex = 9;
            // 
            // _btnBrowseForTemplatesFolder
            // 
            this._btnBrowseForTemplatesFolder.Location = new System.Drawing.Point(343, 231);
            this._btnBrowseForTemplatesFolder.Margin = new System.Windows.Forms.Padding(2);
            this._btnBrowseForTemplatesFolder.Name = "_btnBrowseForTemplatesFolder";
            this._btnBrowseForTemplatesFolder.Size = new System.Drawing.Size(25, 17);
            this._btnBrowseForTemplatesFolder.TabIndex = 10;
            this._btnBrowseForTemplatesFolder.Text = "...";
            this._btnBrowseForTemplatesFolder.UseVisualStyleBackColor = true;
            this._btnBrowseForTemplatesFolder.Click += new System.EventHandler(this._btnBrowseForTemplatesFolder_Click);
            // 
            // _chkUseCrosshairsInsteadOfArrowsForTextCallouts
            // 
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.AutoSize = true;
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Location = new System.Drawing.Point(3, 157);
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Margin = new System.Windows.Forms.Padding(2);
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Name = "_chkUseCrosshairsInsteadOfArrowsForTextCallouts";
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Size = new System.Drawing.Size(260, 17);
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.TabIndex = 11;
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Text = "Use Crosshairs Instead of Arrows for Text Callouts";
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.UseVisualStyleBackColor = true;
            this._chkUseCrosshairsInsteadOfArrowsForTextCallouts.Visible = false;
            // 
            // _chkResetTemplateAfterAnnotationCreation
            // 
            this._chkResetTemplateAfterAnnotationCreation.AutoSize = true;
            this._chkResetTemplateAfterAnnotationCreation.Location = new System.Drawing.Point(3, 136);
            this._chkResetTemplateAfterAnnotationCreation.Margin = new System.Windows.Forms.Padding(2);
            this._chkResetTemplateAfterAnnotationCreation.Name = "_chkResetTemplateAfterAnnotationCreation";
            this._chkResetTemplateAfterAnnotationCreation.Size = new System.Drawing.Size(222, 17);
            this._chkResetTemplateAfterAnnotationCreation.TabIndex = 12;
            this._chkResetTemplateAfterAnnotationCreation.Text = "Reset Template After Annotation Creation";
            this._chkResetTemplateAfterAnnotationCreation.UseVisualStyleBackColor = true;
            // 
            // _chkAlwaysPromptOnRestoringTemplateData
            // 
            this._chkAlwaysPromptOnRestoringTemplateData.AutoSize = true;
            this._chkAlwaysPromptOnRestoringTemplateData.Checked = true;
            this._chkAlwaysPromptOnRestoringTemplateData.CheckState = System.Windows.Forms.CheckState.Checked;
            this._chkAlwaysPromptOnRestoringTemplateData.Location = new System.Drawing.Point(2, 178);
            this._chkAlwaysPromptOnRestoringTemplateData.Margin = new System.Windows.Forms.Padding(2);
            this._chkAlwaysPromptOnRestoringTemplateData.Name = "_chkAlwaysPromptOnRestoringTemplateData";
            this._chkAlwaysPromptOnRestoringTemplateData.Size = new System.Drawing.Size(233, 17);
            this._chkAlwaysPromptOnRestoringTemplateData.TabIndex = 13;
            this._chkAlwaysPromptOnRestoringTemplateData.Text = "Always Prompt On Restoring Template Data";
            this._chkAlwaysPromptOnRestoringTemplateData.UseVisualStyleBackColor = true;
            this._chkAlwaysPromptOnRestoringTemplateData.Visible = false;
            // 
            // AimConfigurationComponentControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this._chkAlwaysPromptOnRestoringTemplateData);
            this.Controls.Add(this._chkResetTemplateAfterAnnotationCreation);
            this.Controls.Add(this._chkUseCrosshairsInsteadOfArrowsForTextCallouts);
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
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "AimConfigurationComponentControl";
            this.Size = new System.Drawing.Size(409, 288);
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
		private System.Windows.Forms.CheckBox _chkUseCrosshairsInsteadOfArrowsForTextCallouts;
        private System.Windows.Forms.CheckBox _chkResetTemplateAfterAnnotationCreation;
        private System.Windows.Forms.CheckBox _chkAlwaysPromptOnRestoringTemplateData;
    }
}
