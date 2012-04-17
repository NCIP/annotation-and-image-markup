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
    partial class AIMSearchCriteriaComponentControl
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AIMSearchCriteriaComponentControl));
			this._titleBar = new Crownwood.DotNetMagic.Controls.TitleBar();
			this._imageAnnotation = new System.Windows.Forms.RadioButton();
			this._annotationOfAnnotation = new System.Windows.Forms.RadioButton();
			this._cancelButton = new System.Windows.Forms.Button();
			this._searchButton = new System.Windows.Forms.Button();
			this._resetButton = new System.Windows.Forms.Button();
			this._studyInstanceUid = new ClearCanvas.Desktop.View.WinForms.TextField();
			this._imagingObservationCharacteristics = new ClearCanvas.Desktop.View.WinForms.TextField();
			this._imagingObservations = new ClearCanvas.Desktop.View.WinForms.TextField();
			this._user = new ClearCanvas.Desktop.View.WinForms.TextField();
			this._anatomicEntityCharacteristics = new ClearCanvas.Desktop.View.WinForms.TextField();
			this._anatomicEntities = new ClearCanvas.Desktop.View.WinForms.TextField();
			this.SuspendLayout();
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
			// _imageAnnotation
			// 
			this._imageAnnotation.AutoCheck = false;
			this._imageAnnotation.AutoSize = true;
			this._imageAnnotation.Location = new System.Drawing.Point(12, 136);
			this._imageAnnotation.Name = "_imageAnnotation";
			this._imageAnnotation.Size = new System.Drawing.Size(108, 17);
			this._imageAnnotation.TabIndex = 6;
			this._imageAnnotation.Text = "Image Annotation";
			this._imageAnnotation.UseVisualStyleBackColor = true;
			// 
			// _annotationOfAnnotation
			// 
			this._annotationOfAnnotation.AutoCheck = false;
			this._annotationOfAnnotation.AutoSize = true;
			this._annotationOfAnnotation.Location = new System.Drawing.Point(122, 136);
			this._annotationOfAnnotation.Name = "_annotationOfAnnotation";
			this._annotationOfAnnotation.Size = new System.Drawing.Size(144, 17);
			this._annotationOfAnnotation.TabIndex = 7;
			this._annotationOfAnnotation.Text = "Annotation Of Annotation";
			this._annotationOfAnnotation.UseVisualStyleBackColor = true;
			// 
			// _cancelButton
			// 
			this._cancelButton.Location = new System.Drawing.Point(659, 82);
			this._cancelButton.Name = "_cancelButton";
			this._cancelButton.Size = new System.Drawing.Size(90, 22);
			this._cancelButton.TabIndex = 9;
			this._cancelButton.Text = "Cancel";
			this._cancelButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this._cancelButton.UseVisualStyleBackColor = true;
			this._cancelButton.Click += new System.EventHandler(this.OnCancel);
			// 
			// _searchButton
			// 
			this._searchButton.Image = ((System.Drawing.Image)(resources.GetObject("_searchButton.Image")));
			this._searchButton.Location = new System.Drawing.Point(659, 54);
			this._searchButton.Name = "_searchButton";
			this._searchButton.Size = new System.Drawing.Size(90, 22);
			this._searchButton.TabIndex = 8;
			this._searchButton.Text = "Search";
			this._searchButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this._searchButton.UseVisualStyleBackColor = true;
			this._searchButton.Click += new System.EventHandler(this.OnSearch);
			// 
			// _resetButton
			// 
			this._resetButton.Location = new System.Drawing.Point(659, 110);
			this._resetButton.Margin = new System.Windows.Forms.Padding(2);
			this._resetButton.Name = "_resetButton";
			this._resetButton.Size = new System.Drawing.Size(90, 22);
			this._resetButton.TabIndex = 10;
			this._resetButton.Text = "Reset";
			this._resetButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
			this._resetButton.UseVisualStyleBackColor = true;
			this._resetButton.Click += new System.EventHandler(this.OnReset);
			// 
			// _studyInstanceUid
			// 
			this._studyInstanceUid.LabelText = "Study Instance Uid";
			this._studyInstanceUid.Location = new System.Drawing.Point(491, 90);
			this._studyInstanceUid.Margin = new System.Windows.Forms.Padding(2);
			this._studyInstanceUid.Mask = "";
			this._studyInstanceUid.Name = "_studyInstanceUid";
			this._studyInstanceUid.PasswordChar = '\0';
			this._studyInstanceUid.Size = new System.Drawing.Size(146, 41);
			this._studyInstanceUid.TabIndex = 18;
			this._studyInstanceUid.ToolTip = null;
			this._studyInstanceUid.Value = null;
			// 
			// _imagingObservationCharacteristics
			// 
			this._imagingObservationCharacteristics.LabelText = "Imaging Observation Characteristics";
			this._imagingObservationCharacteristics.Location = new System.Drawing.Point(250, 90);
			this._imagingObservationCharacteristics.Margin = new System.Windows.Forms.Padding(2);
			this._imagingObservationCharacteristics.Mask = "";
			this._imagingObservationCharacteristics.Name = "_imagingObservationCharacteristics";
			this._imagingObservationCharacteristics.PasswordChar = '\0';
			this._imagingObservationCharacteristics.Size = new System.Drawing.Size(211, 41);
			this._imagingObservationCharacteristics.TabIndex = 17;
			this._imagingObservationCharacteristics.ToolTip = null;
			this._imagingObservationCharacteristics.Value = null;
			// 
			// _imagingObservations
			// 
			this._imagingObservations.LabelText = "Imaging Observations";
			this._imagingObservations.Location = new System.Drawing.Point(12, 90);
			this._imagingObservations.Margin = new System.Windows.Forms.Padding(2);
			this._imagingObservations.Mask = "";
			this._imagingObservations.Name = "_imagingObservations";
			this._imagingObservations.PasswordChar = '\0';
			this._imagingObservations.Size = new System.Drawing.Size(211, 41);
			this._imagingObservations.TabIndex = 16;
			this._imagingObservations.ToolTip = null;
			this._imagingObservations.Value = null;
			// 
			// _user
			// 
			this._user.LabelText = "User";
			this._user.Location = new System.Drawing.Point(491, 45);
			this._user.Margin = new System.Windows.Forms.Padding(2);
			this._user.Mask = "";
			this._user.Name = "_user";
			this._user.PasswordChar = '\0';
			this._user.Size = new System.Drawing.Size(146, 41);
			this._user.TabIndex = 15;
			this._user.ToolTip = null;
			this._user.Value = null;
			// 
			// _anatomicEntityCharacteristics
			// 
			this._anatomicEntityCharacteristics.LabelText = "Anatomic Entity Characteristics";
			this._anatomicEntityCharacteristics.Location = new System.Drawing.Point(250, 45);
			this._anatomicEntityCharacteristics.Margin = new System.Windows.Forms.Padding(2);
			this._anatomicEntityCharacteristics.Mask = "";
			this._anatomicEntityCharacteristics.Name = "_anatomicEntityCharacteristics";
			this._anatomicEntityCharacteristics.PasswordChar = '\0';
			this._anatomicEntityCharacteristics.Size = new System.Drawing.Size(211, 41);
			this._anatomicEntityCharacteristics.TabIndex = 14;
			this._anatomicEntityCharacteristics.ToolTip = null;
			this._anatomicEntityCharacteristics.Value = null;
			// 
			// _anatomicEntities
			// 
			this._anatomicEntities.LabelText = "Anatomic Entities";
			this._anatomicEntities.Location = new System.Drawing.Point(12, 45);
			this._anatomicEntities.Margin = new System.Windows.Forms.Padding(2);
			this._anatomicEntities.Mask = "";
			this._anatomicEntities.Name = "_anatomicEntities";
			this._anatomicEntities.PasswordChar = '\0';
			this._anatomicEntities.Size = new System.Drawing.Size(211, 41);
			this._anatomicEntities.TabIndex = 13;
			this._anatomicEntities.ToolTip = null;
			this._anatomicEntities.Value = null;
			// 
			// AIMSearchCriteriaComponentControl
			// 
			this.AcceptButton = this._searchButton;
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.Controls.Add(this._studyInstanceUid);
			this.Controls.Add(this._imagingObservationCharacteristics);
			this.Controls.Add(this._imagingObservations);
			this.Controls.Add(this._user);
			this.Controls.Add(this._anatomicEntityCharacteristics);
			this.Controls.Add(this._anatomicEntities);
			this.Controls.Add(this._resetButton);
			this.Controls.Add(this._cancelButton);
			this.Controls.Add(this._annotationOfAnnotation);
			this.Controls.Add(this._searchButton);
			this.Controls.Add(this._titleBar);
			this.Controls.Add(this._imageAnnotation);
			this.Name = "AIMSearchCriteriaComponentControl";
			this.Size = new System.Drawing.Size(766, 177);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		private Crownwood.DotNetMagic.Controls.TitleBar _titleBar;
		private System.Windows.Forms.RadioButton _imageAnnotation;
		private System.Windows.Forms.RadioButton _annotationOfAnnotation;
		private System.Windows.Forms.Button _cancelButton;
		private System.Windows.Forms.Button _searchButton;
		private System.Windows.Forms.Button _resetButton;
		private ClearCanvas.Desktop.View.WinForms.TextField _studyInstanceUid;
		private ClearCanvas.Desktop.View.WinForms.TextField _imagingObservationCharacteristics;
		private ClearCanvas.Desktop.View.WinForms.TextField _imagingObservations;
		private ClearCanvas.Desktop.View.WinForms.TextField _user;
		private ClearCanvas.Desktop.View.WinForms.TextField _anatomicEntityCharacteristics;
		private ClearCanvas.Desktop.View.WinForms.TextField _anatomicEntities;
    }
}
