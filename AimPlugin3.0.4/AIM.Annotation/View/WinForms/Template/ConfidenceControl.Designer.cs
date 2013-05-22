//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace AIM.Annotation.View.WinForms.Template
{
	partial class ConfidenceControl
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
			this._lblConfidence = new System.Windows.Forms.Label();
			this._upDownConfidence = new System.Windows.Forms.NumericUpDown();
			((System.ComponentModel.ISupportInitialize)(this._upDownConfidence)).BeginInit();
			this.SuspendLayout();
			// 
			// _lblConfidence
			// 
			this._lblConfidence.AutoSize = true;
			this._lblConfidence.Location = new System.Drawing.Point(4, 6);
			this._lblConfidence.Name = "_lblConfidence";
			this._lblConfidence.Size = new System.Drawing.Size(83, 17);
			this._lblConfidence.TabIndex = 0;
			this._lblConfidence.Text = "Confidence:";
			// 
			// _upDownConfidence
			// 
			this._upDownConfidence.DecimalPlaces = 2;
			this._upDownConfidence.Increment = new decimal(new int[] {
            2,
            0,
            0,
            65536});
			this._upDownConfidence.Location = new System.Drawing.Point(93, 4);
			this._upDownConfidence.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this._upDownConfidence.Name = "_upDownConfidence";
			this._upDownConfidence.Size = new System.Drawing.Size(73, 22);
			this._upDownConfidence.TabIndex = 1;
			this._upDownConfidence.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this._upDownConfidence.ValueChanged += new System.EventHandler(this.OnConfidenceValueChanged);
			// 
			// ConfidenceControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.Controls.Add(this._upDownConfidence);
			this.Controls.Add(this._lblConfidence);
			this.Name = "ConfidenceControl";
			this.Size = new System.Drawing.Size(170, 31);
			((System.ComponentModel.ISupportInitialize)(this._upDownConfidence)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label _lblConfidence;
		private System.Windows.Forms.NumericUpDown _upDownConfidence;
	}
}
