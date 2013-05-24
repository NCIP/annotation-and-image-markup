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

namespace SearchComponent.View.WinForms
{
    partial class NBIASearchCriteriaComponentControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NBIASearchCriteriaComponentControl));
            this._patientID = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._patientsName = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._patientsSex = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._project = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._sliceThickness = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._studyInstanceUid = new ClearCanvas.Desktop.View.WinForms.TextField();
            this._titleBar = new Crownwood.DotNetMagic.Controls.TitleBar();
            this._patientsBirthDate = new ClearCanvas.Desktop.View.WinForms.DateTimeField();
            this._searchButton = new System.Windows.Forms.Button();
            this._cancelButton = new System.Windows.Forms.Button();
            this._resetButton = new System.Windows.Forms.Button();
            this._modality = new SearchComponent.View.WinForms.ModalityPicker();
            this.SuspendLayout();
            // 
            // _patientID
            // 
            this._patientID.LabelText = "Patient ID";
            this._patientID.Location = new System.Drawing.Point(12, 45);
            this._patientID.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._patientID.Mask = "";
            this._patientID.Name = "_patientID";
            this._patientID.PasswordChar = '\0';
            this._patientID.Size = new System.Drawing.Size(148, 41);
            this._patientID.TabIndex = 1;
            this._patientID.ToolTip = null;
            this._patientID.Value = null;
            // 
            // _patientsName
            // 
            this._patientsName.LabelText = "Patient\'s Name";
            this._patientsName.Location = new System.Drawing.Point(172, 45);
            this._patientsName.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._patientsName.Mask = "";
            this._patientsName.Name = "_patientsName";
            this._patientsName.PasswordChar = '\0';
            this._patientsName.Size = new System.Drawing.Size(147, 41);
            this._patientsName.TabIndex = 2;
            this._patientsName.ToolTip = null;
            this._patientsName.Value = null;
            // 
            // _patientsSex
            // 
            this._patientsSex.LabelText = "Sex";
            this._patientsSex.Location = new System.Drawing.Point(332, 45);
            this._patientsSex.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._patientsSex.Mask = "";
            this._patientsSex.Name = "_patientsSex";
            this._patientsSex.PasswordChar = '\0';
            this._patientsSex.Size = new System.Drawing.Size(146, 41);
            this._patientsSex.TabIndex = 3;
            this._patientsSex.ToolTip = null;
            this._patientsSex.Value = null;
            // 
            // _project
            // 
            this._project.LabelText = "Project";
            this._project.Location = new System.Drawing.Point(12, 90);
            this._project.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._project.Mask = "";
            this._project.Name = "_project";
            this._project.PasswordChar = '\0';
            this._project.Size = new System.Drawing.Size(148, 41);
            this._project.TabIndex = 5;
            this._project.ToolTip = null;
            this._project.Value = null;
            // 
            // _sliceThickness
            // 
            this._sliceThickness.LabelText = "Slice Thickness";
            this._sliceThickness.Location = new System.Drawing.Point(173, 90);
            this._sliceThickness.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._sliceThickness.Mask = "";
            this._sliceThickness.Name = "_sliceThickness";
            this._sliceThickness.PasswordChar = '\0';
            this._sliceThickness.Size = new System.Drawing.Size(146, 41);
            this._sliceThickness.TabIndex = 11;
            this._sliceThickness.ToolTip = null;
            this._sliceThickness.Value = null;
            // 
            // _studyInstanceUid
            // 
            this._studyInstanceUid.LabelText = "Study Instance Uid";
            this._studyInstanceUid.Location = new System.Drawing.Point(332, 90);
            this._studyInstanceUid.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._studyInstanceUid.Mask = "";
            this._studyInstanceUid.Name = "_studyInstanceUid";
            this._studyInstanceUid.PasswordChar = '\0';
            this._studyInstanceUid.Size = new System.Drawing.Size(146, 41);
            this._studyInstanceUid.TabIndex = 12;
            this._studyInstanceUid.ToolTip = null;
            this._studyInstanceUid.Value = null;
            // 
            // _titleBar
            // 
            this._titleBar.Dock = System.Windows.Forms.DockStyle.Top;
            this._titleBar.Font = new System.Drawing.Font("Arial", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this._titleBar.GradientColoring = Crownwood.DotNetMagic.Controls.GradientColoring.LightBackToDarkBack;
            this._titleBar.Location = new System.Drawing.Point(0, 0);
            this._titleBar.MouseOverColor = System.Drawing.Color.Empty;
            this._titleBar.Name = "_titleBar";
            this._titleBar.Size = new System.Drawing.Size(766, 30);
            this._titleBar.Style = Crownwood.DotNetMagic.Common.VisualStyle.IDE2005;
            this._titleBar.TabIndex = 0;
            this._titleBar.Text = "Search";
            // 
            // _patientsBirthDate
            // 
            this._patientsBirthDate.LabelText = "Birth Date";
            this._patientsBirthDate.Location = new System.Drawing.Point(492, 45);
            this._patientsBirthDate.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._patientsBirthDate.Maximum = new System.DateTime(9998, 12, 31, 0, 0, 0, 0);
            this._patientsBirthDate.Minimum = new System.DateTime(1753, 1, 1, 0, 0, 0, 0);
            this._patientsBirthDate.Name = "_patientsBirthDate";
            this._patientsBirthDate.Nullable = true;
            this._patientsBirthDate.Size = new System.Drawing.Size(141, 41);
            this._patientsBirthDate.TabIndex = 4;
            this._patientsBirthDate.Value = null;
            // 
            // _searchButton
            // 
            this._searchButton.Image = ((System.Drawing.Image)(resources.GetObject("_searchButton.Image")));
            this._searchButton.Location = new System.Drawing.Point(659, 54);
            this._searchButton.Name = "_searchButton";
            this._searchButton.Size = new System.Drawing.Size(90, 22);
            this._searchButton.TabIndex = 13;
            this._searchButton.Text = "Search";
            this._searchButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._searchButton.UseVisualStyleBackColor = true;
            this._searchButton.Click += new System.EventHandler(this._searchButton_Click);
            // 
            // _cancelButton
            // 
            this._cancelButton.Location = new System.Drawing.Point(659, 82);
            this._cancelButton.Name = "_cancelButton";
            this._cancelButton.Size = new System.Drawing.Size(90, 22);
            this._cancelButton.TabIndex = 14;
            this._cancelButton.Text = "Cancel";
            this._cancelButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._cancelButton.UseVisualStyleBackColor = true;
            this._cancelButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // _resetButton
            // 
            this._resetButton.Location = new System.Drawing.Point(659, 110);
            this._resetButton.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this._resetButton.Name = "_resetButton";
            this._resetButton.Size = new System.Drawing.Size(90, 22);
            this._resetButton.TabIndex = 15;
            this._resetButton.Text = "Reset";
            this._resetButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this._resetButton.UseVisualStyleBackColor = true;
            this._resetButton.Click += new System.EventHandler(this._resetButton_Click);
            // 
            // _modality
            // 
            this._modality.AutoSize = true;
            this._modality.LabelText = "Modality";
            this._modality.Location = new System.Drawing.Point(492, 90);
            this._modality.Margin = new System.Windows.Forms.Padding(2);
            this._modality.Name = "_modality";
            this._modality.Size = new System.Drawing.Size(141, 40);
            this._modality.TabIndex = 8;
            // 
            // NBIASearchCriteriaComponentControl
            // 
            this.AcceptButton = this._searchButton;
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.Controls.Add(this._resetButton);
            this.Controls.Add(this._cancelButton);
            this.Controls.Add(this._searchButton);
            this.Controls.Add(this._patientsBirthDate);
            this.Controls.Add(this._titleBar);
            this.Controls.Add(this._modality);
            this.Controls.Add(this._studyInstanceUid);
            this.Controls.Add(this._sliceThickness);
            this.Controls.Add(this._project);
            this.Controls.Add(this._patientsSex);
            this.Controls.Add(this._patientsName);
            this.Controls.Add(this._patientID);
            this.Name = "NBIASearchCriteriaComponentControl";
            this.Size = new System.Drawing.Size(766, 151);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

		private ClearCanvas.Desktop.View.WinForms.TextField _patientID;
		private ClearCanvas.Desktop.View.WinForms.TextField _patientsName;
		private ClearCanvas.Desktop.View.WinForms.TextField _patientsSex;
        private ClearCanvas.Desktop.View.WinForms.TextField _project;
		private ClearCanvas.Desktop.View.WinForms.TextField _sliceThickness;
		private ClearCanvas.Desktop.View.WinForms.TextField _studyInstanceUid;
		private ModalityPicker _modality;
		private Crownwood.DotNetMagic.Controls.TitleBar _titleBar;
		private ClearCanvas.Desktop.View.WinForms.DateTimeField _patientsBirthDate;
		private System.Windows.Forms.Button _searchButton;
		private System.Windows.Forms.Button _cancelButton;
		private System.Windows.Forms.Button _resetButton;
    }
}
