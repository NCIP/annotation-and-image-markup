namespace AIM.Annotation.View.WinForms.Template
{
	partial class CharacteristicQuantificationNumericalControl
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
			this._ddlComparisonOperator = new System.Windows.Forms.ComboBox();
			this._lblUcumString = new System.Windows.Forms.Label();
			this._toolTipNumerical = new System.Windows.Forms.ToolTip(this.components);
			this._txtValue = new System.Windows.Forms.MaskedTextBox();
			this.SuspendLayout();
			// 
			// _ddlComparisonOperator
			// 
			this._ddlComparisonOperator.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this._ddlComparisonOperator.FormattingEnabled = true;
			this._ddlComparisonOperator.Location = new System.Drawing.Point(4, 4);
			this._ddlComparisonOperator.Name = "_ddlComparisonOperator";
			this._ddlComparisonOperator.Size = new System.Drawing.Size(56, 24);
			this._ddlComparisonOperator.TabIndex = 0;
			this._toolTipNumerical.SetToolTip(this._ddlComparisonOperator, "Select comparison operator");
			// 
			// _lblUcumString
			// 
			this._lblUcumString.AutoSize = true;
			this._lblUcumString.Location = new System.Drawing.Point(124, 9);
			this._lblUcumString.Name = "_lblUcumString";
			this._lblUcumString.Size = new System.Drawing.Size(48, 17);
			this._lblUcumString.TabIndex = 2;
			this._lblUcumString.Text = "UCUM";
			this._toolTipNumerical.SetToolTip(this._lblUcumString, "Value dimensionality, e.g. mm, cm (UCUM)");
			// 
			// _txtValue
			// 
			this._txtValue.CutCopyMaskFormat = System.Windows.Forms.MaskFormat.ExcludePromptAndLiterals;
			this._txtValue.Location = new System.Drawing.Point(66, 6);
			this._txtValue.Name = "_txtValue";
			this._txtValue.Size = new System.Drawing.Size(52, 22);
			this._txtValue.TabIndex = 1;
			// 
			// CharacteristicQuantificationNumericalControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.AutoSize = true;
			this.Controls.Add(this._txtValue);
			this.Controls.Add(this._lblUcumString);
			this.Controls.Add(this._ddlComparisonOperator);
			this.Name = "CharacteristicQuantificationNumericalControl";
			this.Size = new System.Drawing.Size(194, 35);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox _ddlComparisonOperator;
		private System.Windows.Forms.Label _lblUcumString;
		private System.Windows.Forms.ToolTip _toolTipNumerical;
		private System.Windows.Forms.MaskedTextBox _txtValue;
	}
}
