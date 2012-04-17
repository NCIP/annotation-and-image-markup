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

namespace AIM.Annotation.View.WinForms
{
	partial class AimAnnotationComponentControl
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
			this._cmbAnnotationType = new System.Windows.Forms.ComboBox();
			this.btnSelectTemplateDoc = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// _cmbAnnotationType
			// 
			this._cmbAnnotationType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._cmbAnnotationType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this._cmbAnnotationType.FormattingEnabled = true;
			this._cmbAnnotationType.Location = new System.Drawing.Point(127, 5);
			this._cmbAnnotationType.Name = "_cmbAnnotationType";
			this._cmbAnnotationType.Size = new System.Drawing.Size(407, 24);
			this._cmbAnnotationType.TabIndex = 0;
			this._cmbAnnotationType.DropDown += new System.EventHandler(this._cmbAnnotationType_DropDown);
			// 
			// btnSelectTemplateDoc
			// 
			this.btnSelectTemplateDoc.Location = new System.Drawing.Point(3, 5);
			this.btnSelectTemplateDoc.Name = "btnSelectTemplateDoc";
			this.btnSelectTemplateDoc.Size = new System.Drawing.Size(118, 24);
			this.btnSelectTemplateDoc.TabIndex = 2;
			this.btnSelectTemplateDoc.Text = "&AIM Template";
			this.btnSelectTemplateDoc.UseVisualStyleBackColor = true;
			this.btnSelectTemplateDoc.Click += new System.EventHandler(this.btnSelectTemplateDoc_Click);
			// 
			// AimAnnotationComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CausesValidation = false;
			this.Controls.Add(this.btnSelectTemplateDoc);
			this.Controls.Add(this._cmbAnnotationType);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "AimAnnotationComponentControl";
			this.Size = new System.Drawing.Size(537, 596);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ComboBox _cmbAnnotationType;
		private System.Windows.Forms.Button btnSelectTemplateDoc;

	}
}
