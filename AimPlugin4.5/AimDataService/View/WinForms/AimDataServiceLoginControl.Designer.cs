namespace AimDataService.View.WinForms
{
    partial class AimDataServiceLoginControl
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
            System.Windows.Forms.Label lblPassword;
            System.Windows.Forms.Label lblUserName;
            this._lblAimDataServiceLogin = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnLogin = new System.Windows.Forms.Button();
            this.tboxPassword = new System.Windows.Forms.TextBox();
            this.tboxUserName = new System.Windows.Forms.TextBox();
            lblPassword = new System.Windows.Forms.Label();
            lblUserName = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lblPassword
            // 
            lblPassword.AutoSize = true;
            lblPassword.CausesValidation = false;
            lblPassword.Location = new System.Drawing.Point(6, 76);
            lblPassword.Name = "lblPassword";
            lblPassword.Size = new System.Drawing.Size(56, 13);
            lblPassword.TabIndex = 29;
            lblPassword.Text = "&Password:";
            lblPassword.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblUserName
            // 
            lblUserName.AutoSize = true;
            lblUserName.CausesValidation = false;
            lblUserName.Location = new System.Drawing.Point(6, 37);
            lblUserName.Name = "lblUserName";
            lblUserName.Size = new System.Drawing.Size(63, 13);
            lblUserName.TabIndex = 27;
            lblUserName.Text = "&User Name:";
            lblUserName.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // _lblAimDataServiceLogin
            // 
            this._lblAimDataServiceLogin.AutoSize = true;
            this._lblAimDataServiceLogin.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this._lblAimDataServiceLogin.ForeColor = System.Drawing.Color.MidnightBlue;
            this._lblAimDataServiceLogin.Location = new System.Drawing.Point(3, 12);
            this._lblAimDataServiceLogin.Name = "_lblAimDataServiceLogin";
            this._lblAimDataServiceLogin.Size = new System.Drawing.Size(170, 16);
            this._lblAimDataServiceLogin.TabIndex = 26;
            this._lblAimDataServiceLogin.Text = "AIM Data Service Login";
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnCancel.AutoSize = true;
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(224, 133);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 32;
            this.btnCancel.Text = "&Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.BtnCancelClick);
            // 
            // btnLogin
            // 
            this.btnLogin.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLogin.AutoSize = true;
            this.btnLogin.Location = new System.Drawing.Point(131, 133);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(75, 23);
            this.btnLogin.TabIndex = 31;
            this.btnLogin.Text = "&Log in";
            this.btnLogin.UseVisualStyleBackColor = true;
            this.btnLogin.Click += new System.EventHandler(this.BtnLoginClick);
            // 
            // tboxPassword
            // 
            this.tboxPassword.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tboxPassword.Location = new System.Drawing.Point(6, 92);
            this.tboxPassword.Name = "tboxPassword";
            this.tboxPassword.Size = new System.Drawing.Size(293, 20);
            this.tboxPassword.TabIndex = 30;
            this.tboxPassword.UseSystemPasswordChar = true;
            // 
            // tboxUserName
            // 
            this.tboxUserName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tboxUserName.Location = new System.Drawing.Point(6, 53);
            this.tboxUserName.Name = "tboxUserName";
            this.tboxUserName.Size = new System.Drawing.Size(293, 20);
            this.tboxUserName.TabIndex = 28;
            // 
            // AimDataServiceLoginControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnLogin);
            this.Controls.Add(this.tboxPassword);
            this.Controls.Add(lblPassword);
            this.Controls.Add(this.tboxUserName);
            this.Controls.Add(lblUserName);
            this.Controls.Add(this._lblAimDataServiceLogin);
            this.Name = "AimDataServiceLoginControl";
            this.Size = new System.Drawing.Size(302, 159);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label _lblAimDataServiceLogin;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnLogin;
        private System.Windows.Forms.TextBox tboxPassword;
        private System.Windows.Forms.TextBox tboxUserName;
    }
}
