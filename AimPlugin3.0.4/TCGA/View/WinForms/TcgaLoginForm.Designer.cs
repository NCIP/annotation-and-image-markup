//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

namespace TCGA.View.WinForms
{
	partial class TcgaLoginForm
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

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TcgaLoginForm));
			this._lblName = new System.Windows.Forms.Label();
			this._lblLoginName = new System.Windows.Forms.Label();
			this._lblRoleInTrial = new System.Windows.Forms.Label();
			this._lblNumberWithinRoleOfClinicalTrial = new System.Windows.Forms.Label();
			this._txtUserName = new System.Windows.Forms.TextBox();
			this._txtLoginName = new System.Windows.Forms.TextBox();
			this._upDownNumberWithinRoleOfClinicalTrial = new System.Windows.Forms.NumericUpDown();
			this._btnCancel = new System.Windows.Forms.Button();
			this._btnLogin = new System.Windows.Forms.Button();
			this._cmbRoleInTrial = new System.Windows.Forms.ComboBox();
			((System.ComponentModel.ISupportInitialize)(this._upDownNumberWithinRoleOfClinicalTrial)).BeginInit();
			this.SuspendLayout();
			// 
			// _lblName
			// 
			this._lblName.AutoSize = true;
			this._lblName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblName.Location = new System.Drawing.Point(19, 28);
			this._lblName.Name = "_lblName";
			this._lblName.Size = new System.Drawing.Size(58, 20);
			this._lblName.TabIndex = 0;
			this._lblName.Text = "&Name:";
			// 
			// _lblLoginName
			// 
			this._lblLoginName.AutoSize = true;
			this._lblLoginName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblLoginName.Location = new System.Drawing.Point(19, 61);
			this._lblLoginName.Name = "_lblLoginName";
			this._lblLoginName.Size = new System.Drawing.Size(104, 20);
			this._lblLoginName.TabIndex = 2;
			this._lblLoginName.Text = "L&ogin Name:";
			// 
			// _lblRoleInTrial
			// 
			this._lblRoleInTrial.AutoSize = true;
			this._lblRoleInTrial.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblRoleInTrial.Location = new System.Drawing.Point(20, 96);
			this._lblRoleInTrial.Name = "_lblRoleInTrial";
			this._lblRoleInTrial.Size = new System.Drawing.Size(104, 20);
			this._lblRoleInTrial.TabIndex = 4;
			this._lblRoleInTrial.Text = "&Role In Trial:";
			// 
			// _lblNumberWithinRoleOfClinicalTrial
			// 
			this._lblNumberWithinRoleOfClinicalTrial.AutoSize = true;
			this._lblNumberWithinRoleOfClinicalTrial.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblNumberWithinRoleOfClinicalTrial.Location = new System.Drawing.Point(19, 133);
			this._lblNumberWithinRoleOfClinicalTrial.Name = "_lblNumberWithinRoleOfClinicalTrial";
			this._lblNumberWithinRoleOfClinicalTrial.Size = new System.Drawing.Size(281, 20);
			this._lblNumberWithinRoleOfClinicalTrial.TabIndex = 6;
			this._lblNumberWithinRoleOfClinicalTrial.Text = "&Number Within Role of Clinical Trial:";
			// 
			// _txtUserName
			// 
			this._txtUserName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._txtUserName.Location = new System.Drawing.Point(143, 25);
			this._txtUserName.Name = "_txtUserName";
			this._txtUserName.Size = new System.Drawing.Size(267, 22);
			this._txtUserName.TabIndex = 1;
			this._txtUserName.TextChanged += new System.EventHandler(this._txtUserName_TextChanged);
			// 
			// _txtLoginName
			// 
			this._txtLoginName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._txtLoginName.Location = new System.Drawing.Point(143, 61);
			this._txtLoginName.Name = "_txtLoginName";
			this._txtLoginName.Size = new System.Drawing.Size(267, 22);
			this._txtLoginName.TabIndex = 3;
			this._txtLoginName.TextChanged += new System.EventHandler(this._txtLoginName_TextChanged);
			// 
			// _upDownNumberWithinRoleOfClinicalTrial
			// 
			this._upDownNumberWithinRoleOfClinicalTrial.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._upDownNumberWithinRoleOfClinicalTrial.Location = new System.Drawing.Point(320, 131);
			this._upDownNumberWithinRoleOfClinicalTrial.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this._upDownNumberWithinRoleOfClinicalTrial.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			this._upDownNumberWithinRoleOfClinicalTrial.Name = "_upDownNumberWithinRoleOfClinicalTrial";
			this._upDownNumberWithinRoleOfClinicalTrial.Size = new System.Drawing.Size(90, 22);
			this._upDownNumberWithinRoleOfClinicalTrial.TabIndex = 7;
			this._upDownNumberWithinRoleOfClinicalTrial.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this._upDownNumberWithinRoleOfClinicalTrial.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
			this._upDownNumberWithinRoleOfClinicalTrial.ValueChanged += new System.EventHandler(this._upDownNumberWithinRoleOfClinicalTrial_ValueChanged);
			// 
			// _btnCancel
			// 
			this._btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnCancel.AutoSize = true;
			this._btnCancel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this._btnCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._btnCancel.Location = new System.Drawing.Point(337, 173);
			this._btnCancel.Name = "_btnCancel";
			this._btnCancel.Size = new System.Drawing.Size(71, 30);
			this._btnCancel.TabIndex = 9;
			this._btnCancel.Text = "&Cancel";
			this._btnCancel.UseVisualStyleBackColor = true;
			this._btnCancel.Click += new System.EventHandler(this.OnCancelButtonClick);
			// 
			// _btnLogin
			// 
			this._btnLogin.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnLogin.AutoSize = true;
			this._btnLogin.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._btnLogin.DialogResult = System.Windows.Forms.DialogResult.OK;
			this._btnLogin.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._btnLogin.Location = new System.Drawing.Point(271, 173);
			this._btnLogin.Name = "_btnLogin";
			this._btnLogin.Size = new System.Drawing.Size(60, 30);
			this._btnLogin.TabIndex = 8;
			this._btnLogin.Text = "&Login";
			this._btnLogin.UseVisualStyleBackColor = true;
			this._btnLogin.Click += new System.EventHandler(this.OnLoginButtonClick);
			// 
			// _cmbRoleInTrial
			// 
			this._cmbRoleInTrial.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._cmbRoleInTrial.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this._cmbRoleInTrial.FormattingEnabled = true;
			this._cmbRoleInTrial.Items.AddRange(new object[] {
            "<Select Role>",
            "Performing",
            "Referring",
            "Requesting",
            "Recording",
            "Verifying",
            "Assisting",
            "Circulating",
            "Standby"});
			this._cmbRoleInTrial.Location = new System.Drawing.Point(143, 92);
			this._cmbRoleInTrial.Name = "_cmbRoleInTrial";
			this._cmbRoleInTrial.Size = new System.Drawing.Size(267, 24);
			this._cmbRoleInTrial.TabIndex = 5;
			this._cmbRoleInTrial.SelectedIndexChanged += new System.EventHandler(this._cmbRoleInTrial_SelectedIndexChanged);
			// 
			// TcgaLoginForm
			// 
			this.AcceptButton = this._btnLogin;
			this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
			this.CancelButton = this._btnCancel;
			this.ClientSize = new System.Drawing.Size(435, 220);
			this.Controls.Add(this._cmbRoleInTrial);
			this.Controls.Add(this._btnLogin);
			this.Controls.Add(this._btnCancel);
			this.Controls.Add(this._upDownNumberWithinRoleOfClinicalTrial);
			this.Controls.Add(this._txtLoginName);
			this.Controls.Add(this._txtUserName);
			this.Controls.Add(this._lblNumberWithinRoleOfClinicalTrial);
			this.Controls.Add(this._lblRoleInTrial);
			this.Controls.Add(this._lblLoginName);
			this.Controls.Add(this._lblName);
			this.DoubleBuffered = true;
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Location = new System.Drawing.Point(200, 150);
			this.MaximumSize = new System.Drawing.Size(480, 304);
			this.Name = "TcgaLoginForm";
			this.Padding = new System.Windows.Forms.Padding(12);
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "TCGA User Credentials";
			this.TopMost = true;
			this.Load += new System.EventHandler(this.OnLoginFormLoad);
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TcgaLoginForm_MouseDown);
			this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TcgaLoginForm_MouseMove);
			((System.ComponentModel.ISupportInitialize)(this._upDownNumberWithinRoleOfClinicalTrial)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label _lblName;
		private System.Windows.Forms.Label _lblLoginName;
		private System.Windows.Forms.Label _lblRoleInTrial;
		private System.Windows.Forms.Label _lblNumberWithinRoleOfClinicalTrial;
		private System.Windows.Forms.TextBox _txtUserName;
		private System.Windows.Forms.TextBox _txtLoginName;
		private System.Windows.Forms.NumericUpDown _upDownNumberWithinRoleOfClinicalTrial;
		private System.Windows.Forms.Button _btnCancel;
		private System.Windows.Forms.Button _btnLogin;
		private System.Windows.Forms.ComboBox _cmbRoleInTrial;
	}
}