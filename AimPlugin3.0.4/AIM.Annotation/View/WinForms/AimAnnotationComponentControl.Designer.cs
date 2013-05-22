//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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
