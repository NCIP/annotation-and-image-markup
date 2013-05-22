//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace AIM.Annotation.View.WinForms.Template
{
	partial class CharacteristicQuantificationDetailsControl
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
			this._lblName = new System.Windows.Forms.Label();
			this._txtName = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// _lblName
			// 
			this._lblName.AutoSize = true;
			this._lblName.Location = new System.Drawing.Point(3, 7);
			this._lblName.Name = "_lblName";
			this._lblName.Size = new System.Drawing.Size(49, 17);
			this._lblName.TabIndex = 0;
			this._lblName.Text = "Name:";
			// 
			// _txtName
			// 
			this._txtName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._txtName.Location = new System.Drawing.Point(59, 4);
			this._txtName.Name = "_txtName";
			this._txtName.ReadOnly = true;
			this._txtName.Size = new System.Drawing.Size(131, 22);
			this._txtName.TabIndex = 1;
			// 
			// CharacteristicQuantificationDetailsControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.Controls.Add(this._txtName);
			this.Controls.Add(this._lblName);
			this.Name = "CharacteristicQuantificationDetailsControl";
			this.Size = new System.Drawing.Size(193, 29);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label _lblName;
		private System.Windows.Forms.TextBox _txtName;
	}
}
