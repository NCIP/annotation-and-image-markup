namespace Segmentation.View.WinForms.Configuration
{
	partial class SegmentationConfigurationComponentControl
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
			this.components = new System.ComponentModel.Container();
			this._chkShowConfirmationWhenCreatingNewSegmentations = new System.Windows.Forms.CheckBox();
			this._openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.label1 = new System.Windows.Forms.Label();
			this._txtCategoryTypeModifierXmlConfigurationFileLocation = new System.Windows.Forms.TextBox();
			this._txtAnatomicRegionAndModifierXmlConfigurationFile = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this._btnBrowseForCategoryConfigurationFile = new System.Windows.Forms.Button();
			this._btnBrowseForAnatomicRegionConfigurationFile = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this._btnExportDefaultConfigFiles = new System.Windows.Forms.Button();
			this._toolTip = new System.Windows.Forms.ToolTip(this.components);
			this._folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
			this.SuspendLayout();
			// 
			// _chkShowConfirmationWhenCreatingNewSegmentations
			// 
			this._chkShowConfirmationWhenCreatingNewSegmentations.AutoSize = true;
			this._chkShowConfirmationWhenCreatingNewSegmentations.Location = new System.Drawing.Point(3, 2);
			this._chkShowConfirmationWhenCreatingNewSegmentations.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._chkShowConfirmationWhenCreatingNewSegmentations.Name = "_chkShowConfirmationWhenCreatingNewSegmentations";
			this._chkShowConfirmationWhenCreatingNewSegmentations.Size = new System.Drawing.Size(362, 21);
			this._chkShowConfirmationWhenCreatingNewSegmentations.TabIndex = 0;
			this._chkShowConfirmationWhenCreatingNewSegmentations.Text = "&Show confirmation when creating new segmentations";
			this._chkShowConfirmationWhenCreatingNewSegmentations.UseVisualStyleBackColor = true;
			// 
			// _openFileDialog
			// 
			this._openFileDialog.Filter = "XML files|*.xml|All files|*.*";
			this._openFileDialog.Title = "Select XML Configuration File";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(4, 38);
			this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(341, 17);
			this.label1.TabIndex = 1;
			this.label1.Text = "&Category, Type, and Modifier XML Configuration File:";
			// 
			// _txtCategoryTypeModifierXmlConfigurationFileLocation
			// 
			this._txtCategoryTypeModifierXmlConfigurationFileLocation.Location = new System.Drawing.Point(3, 58);
			this._txtCategoryTypeModifierXmlConfigurationFileLocation.Margin = new System.Windows.Forms.Padding(4);
			this._txtCategoryTypeModifierXmlConfigurationFileLocation.Name = "_txtCategoryTypeModifierXmlConfigurationFileLocation";
			this._txtCategoryTypeModifierXmlConfigurationFileLocation.Size = new System.Drawing.Size(348, 22);
			this._txtCategoryTypeModifierXmlConfigurationFileLocation.TabIndex = 2;
			// 
			// _txtAnatomicRegionAndModifierXmlConfigurationFile
			// 
			this._txtAnatomicRegionAndModifierXmlConfigurationFile.Location = new System.Drawing.Point(3, 121);
			this._txtAnatomicRegionAndModifierXmlConfigurationFile.Margin = new System.Windows.Forms.Padding(4);
			this._txtAnatomicRegionAndModifierXmlConfigurationFile.Name = "_txtAnatomicRegionAndModifierXmlConfigurationFile";
			this._txtAnatomicRegionAndModifierXmlConfigurationFile.Size = new System.Drawing.Size(348, 22);
			this._txtAnatomicRegionAndModifierXmlConfigurationFile.TabIndex = 5;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(4, 101);
			this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(347, 17);
			this.label2.TabIndex = 4;
			this.label2.Text = "&Anatomic Region and Modifier XML Configuration File:";
			// 
			// _btnBrowseForCategoryConfigurationFile
			// 
			this._btnBrowseForCategoryConfigurationFile.Location = new System.Drawing.Point(359, 59);
			this._btnBrowseForCategoryConfigurationFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._btnBrowseForCategoryConfigurationFile.Name = "_btnBrowseForCategoryConfigurationFile";
			this._btnBrowseForCategoryConfigurationFile.Size = new System.Drawing.Size(33, 21);
			this._btnBrowseForCategoryConfigurationFile.TabIndex = 3;
			this._btnBrowseForCategoryConfigurationFile.Text = "...";
			this._toolTip.SetToolTip(this._btnBrowseForCategoryConfigurationFile, "Select File");
			this._btnBrowseForCategoryConfigurationFile.UseVisualStyleBackColor = true;
			this._btnBrowseForCategoryConfigurationFile.Click += new System.EventHandler(this.OnBtnBrowseForCategoryConfigurationFileClick);
			// 
			// _btnBrowseForAnatomicRegionConfigurationFile
			// 
			this._btnBrowseForAnatomicRegionConfigurationFile.Location = new System.Drawing.Point(359, 122);
			this._btnBrowseForAnatomicRegionConfigurationFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._btnBrowseForAnatomicRegionConfigurationFile.Name = "_btnBrowseForAnatomicRegionConfigurationFile";
			this._btnBrowseForAnatomicRegionConfigurationFile.Size = new System.Drawing.Size(33, 21);
			this._btnBrowseForAnatomicRegionConfigurationFile.TabIndex = 6;
			this._btnBrowseForAnatomicRegionConfigurationFile.Text = "...";
			this._toolTip.SetToolTip(this._btnBrowseForAnatomicRegionConfigurationFile, "Select File");
			this._btnBrowseForAnatomicRegionConfigurationFile.UseVisualStyleBackColor = true;
			this._btnBrowseForAnatomicRegionConfigurationFile.Click += new System.EventHandler(this.OnBtnBrowseForAnatomicRegionConfigurationFileClick);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(4, 160);
			this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(222, 17);
			this.label3.TabIndex = 7;
			this.label3.Text = "&Export Default Configuration Files:";
			// 
			// _btnExportDefaultConfigFiles
			// 
			this._btnExportDefaultConfigFiles.Location = new System.Drawing.Point(233, 158);
			this._btnExportDefaultConfigFiles.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._btnExportDefaultConfigFiles.Name = "_btnExportDefaultConfigFiles";
			this._btnExportDefaultConfigFiles.Size = new System.Drawing.Size(33, 21);
			this._btnExportDefaultConfigFiles.TabIndex = 8;
			this._btnExportDefaultConfigFiles.Text = "...";
			this._toolTip.SetToolTip(this._btnExportDefaultConfigFiles, "Select Folder for Exported Files");
			this._btnExportDefaultConfigFiles.UseVisualStyleBackColor = true;
			this._btnExportDefaultConfigFiles.Click += new System.EventHandler(this.OnBtnExportDefaultConfigFilesClick);
			// 
			// SegmentationConfigurationComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._btnExportDefaultConfigFiles);
			this.Controls.Add(this.label3);
			this.Controls.Add(this._btnBrowseForAnatomicRegionConfigurationFile);
			this.Controls.Add(this._btnBrowseForCategoryConfigurationFile);
			this.Controls.Add(this._txtAnatomicRegionAndModifierXmlConfigurationFile);
			this.Controls.Add(this.label2);
			this.Controls.Add(this._txtCategoryTypeModifierXmlConfigurationFileLocation);
			this.Controls.Add(this.label1);
			this.Controls.Add(this._chkShowConfirmationWhenCreatingNewSegmentations);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "SegmentationConfigurationComponentControl";
			this.Size = new System.Drawing.Size(479, 230);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.CheckBox _chkShowConfirmationWhenCreatingNewSegmentations;
		private System.Windows.Forms.OpenFileDialog _openFileDialog;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox _txtCategoryTypeModifierXmlConfigurationFileLocation;
		private System.Windows.Forms.TextBox _txtAnatomicRegionAndModifierXmlConfigurationFile;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button _btnBrowseForCategoryConfigurationFile;
		private System.Windows.Forms.Button _btnBrowseForAnatomicRegionConfigurationFile;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button _btnExportDefaultConfigFiles;
		private System.Windows.Forms.ToolTip _toolTip;
		private System.Windows.Forms.FolderBrowserDialog _folderBrowserDialog;
	}
}
