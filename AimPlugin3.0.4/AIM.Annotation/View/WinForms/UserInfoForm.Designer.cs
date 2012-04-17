namespace AIM.Annotation.View.WinForms
{
    partial class FormUserInfo
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
            this._btnSave = new System.Windows.Forms.Button();
            this._btnCancel = new System.Windows.Forms.Button();
            this._lblUserName = new System.Windows.Forms.Label();
            this._lblLoginName = new System.Windows.Forms.Label();
            this._lblRoleInTrial = new System.Windows.Forms.Label();
            this._lblNumberWithinRoleInTrial = new System.Windows.Forms.Label();
            this._tboxUserName = new System.Windows.Forms.TextBox();
            this._tboxLoginName = new System.Windows.Forms.TextBox();
            this._updownNumberWithinRoleInTrial = new System.Windows.Forms.NumericUpDown();
            this._cmbRoleInTrial = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this._updownNumberWithinRoleInTrial)).BeginInit();
            this.SuspendLayout();
            // 
            // _btnSave
            // 
            this._btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this._btnSave.DialogResult = System.Windows.Forms.DialogResult.OK;
            this._btnSave.Location = new System.Drawing.Point(275, 150);
            this._btnSave.Name = "_btnSave";
            this._btnSave.Size = new System.Drawing.Size(75, 23);
            this._btnSave.TabIndex = 8;
            this._btnSave.Text = "&Save";
            this._btnSave.UseVisualStyleBackColor = true;
            this._btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // _btnCancel
            // 
            this._btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this._btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this._btnCancel.Location = new System.Drawing.Point(356, 150);
            this._btnCancel.Name = "_btnCancel";
            this._btnCancel.Size = new System.Drawing.Size(75, 23);
            this._btnCancel.TabIndex = 9;
            this._btnCancel.Text = "&Cancel";
            this._btnCancel.UseVisualStyleBackColor = true;
            this._btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // _lblUserName
            // 
            this._lblUserName.AutoSize = true;
            this._lblUserName.Location = new System.Drawing.Point(12, 16);
            this._lblUserName.Name = "_lblUserName";
            this._lblUserName.Size = new System.Drawing.Size(88, 17);
            this._lblUserName.TabIndex = 0;
            this._lblUserName.Text = "User Name*:";
            this._lblUserName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // _lblLoginName
            // 
            this._lblLoginName.AutoSize = true;
            this._lblLoginName.Location = new System.Drawing.Point(12, 45);
            this._lblLoginName.Name = "_lblLoginName";
            this._lblLoginName.Size = new System.Drawing.Size(93, 17);
            this._lblLoginName.TabIndex = 2;
            this._lblLoginName.Text = "Login Name*:";
            // 
            // _lblRoleInTrial
            // 
            this._lblRoleInTrial.AutoSize = true;
            this._lblRoleInTrial.Location = new System.Drawing.Point(12, 74);
            this._lblRoleInTrial.Name = "_lblRoleInTrial";
            this._lblRoleInTrial.Size = new System.Drawing.Size(88, 17);
            this._lblRoleInTrial.TabIndex = 4;
            this._lblRoleInTrial.Text = "Role In Trial:";
            // 
            // _lblNumberWithinRoleInTrial
            // 
            this._lblNumberWithinRoleInTrial.AutoSize = true;
            this._lblNumberWithinRoleInTrial.Location = new System.Drawing.Point(12, 104);
            this._lblNumberWithinRoleInTrial.Name = "_lblNumberWithinRoleInTrial";
            this._lblNumberWithinRoleInTrial.Size = new System.Drawing.Size(138, 17);
            this._lblNumberWithinRoleInTrial.TabIndex = 6;
            this._lblNumberWithinRoleInTrial.Text = "Number Within Role:";
            // 
            // _tboxUserName
            // 
            this._tboxUserName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._tboxUserName.Location = new System.Drawing.Point(158, 13);
            this._tboxUserName.Name = "_tboxUserName";
            this._tboxUserName.Size = new System.Drawing.Size(270, 22);
            this._tboxUserName.TabIndex = 1;
            // 
            // _tboxLoginName
            // 
            this._tboxLoginName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._tboxLoginName.Location = new System.Drawing.Point(158, 42);
            this._tboxLoginName.Name = "_tboxLoginName";
            this._tboxLoginName.Size = new System.Drawing.Size(270, 22);
            this._tboxLoginName.TabIndex = 3;
            // 
            // _updownNumberWithinRoleInTrial
            // 
            this._updownNumberWithinRoleInTrial.Location = new System.Drawing.Point(158, 99);
            this._updownNumberWithinRoleInTrial.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this._updownNumberWithinRoleInTrial.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this._updownNumberWithinRoleInTrial.Name = "_updownNumberWithinRoleInTrial";
            this._updownNumberWithinRoleInTrial.Size = new System.Drawing.Size(87, 22);
            this._updownNumberWithinRoleInTrial.TabIndex = 7;
            this._updownNumberWithinRoleInTrial.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
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
            this._cmbRoleInTrial.Location = new System.Drawing.Point(158, 70);
            this._cmbRoleInTrial.Name = "_cmbRoleInTrial";
            this._cmbRoleInTrial.Size = new System.Drawing.Size(270, 24);
            this._cmbRoleInTrial.TabIndex = 5;
            // 
            // FormUserInfo
            // 
            this.AcceptButton = this._btnSave;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this._btnCancel;
            this.ClientSize = new System.Drawing.Size(443, 185);
            this.Controls.Add(this._cmbRoleInTrial);
            this.Controls.Add(this._updownNumberWithinRoleInTrial);
            this.Controls.Add(this._tboxLoginName);
            this.Controls.Add(this._tboxUserName);
            this.Controls.Add(this._lblNumberWithinRoleInTrial);
            this.Controls.Add(this._lblRoleInTrial);
            this.Controls.Add(this._lblLoginName);
            this.Controls.Add(this._lblUserName);
            this.Controls.Add(this._btnCancel);
            this.Controls.Add(this._btnSave);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(451, 224);
            this.Name = "FormUserInfo";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "AIM User Information";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormUserInfo_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this._updownNumberWithinRoleInTrial)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _btnSave;
        private System.Windows.Forms.Button _btnCancel;
        private System.Windows.Forms.Label _lblUserName;
        private System.Windows.Forms.Label _lblLoginName;
        private System.Windows.Forms.Label _lblRoleInTrial;
        private System.Windows.Forms.Label _lblNumberWithinRoleInTrial;
        private System.Windows.Forms.TextBox _tboxUserName;
        private System.Windows.Forms.TextBox _tboxLoginName;
        private System.Windows.Forms.NumericUpDown _updownNumberWithinRoleInTrial;
        private System.Windows.Forms.ComboBox _cmbRoleInTrial;
    }
}