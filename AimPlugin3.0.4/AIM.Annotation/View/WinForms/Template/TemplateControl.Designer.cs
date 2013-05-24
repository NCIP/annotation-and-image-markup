namespace AIM.Annotation.View.WinForms.Template
{
	partial class TemplateControl
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
			this._tboxAnnotationName = new System.Windows.Forms.TextBox();
			this._lblAnnotationName = new System.Windows.Forms.Label();
			this._btnUserInfo = new System.Windows.Forms.Button();
			this._btnCreateAnnotation = new System.Windows.Forms.Button();
			this._btnExtension1 = new System.Windows.Forms.Button();
			this._componentContainerControl = new AIM.Annotation.View.WinForms.Template.ComponentContainerControl();
			this.SuspendLayout();
			// 
			// _tboxAnnotationName
			// 
			this._tboxAnnotationName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._tboxAnnotationName.BackColor = System.Drawing.Color.WhiteSmoke;
			this._tboxAnnotationName.Location = new System.Drawing.Point(3, 28);
			this._tboxAnnotationName.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._tboxAnnotationName.Name = "_tboxAnnotationName";
			this._tboxAnnotationName.Size = new System.Drawing.Size(324, 22);
			this._tboxAnnotationName.TabIndex = 1;
			// 
			// _lblAnnotationName
			// 
			this._lblAnnotationName.AutoSize = true;
			this._lblAnnotationName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F);
			this._lblAnnotationName.Location = new System.Drawing.Point(3, 3);
			this._lblAnnotationName.Margin = new System.Windows.Forms.Padding(3);
			this._lblAnnotationName.Name = "_lblAnnotationName";
			this._lblAnnotationName.Size = new System.Drawing.Size(142, 20);
			this._lblAnnotationName.TabIndex = 0;
			this._lblAnnotationName.Text = "Annotation Name:";
			// 
			// _btnUserInfo
			// 
			this._btnUserInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnUserInfo.Location = new System.Drawing.Point(246, 505);
			this._btnUserInfo.Name = "_btnUserInfo";
			this._btnUserInfo.Size = new System.Drawing.Size(75, 36);
			this._btnUserInfo.TabIndex = 4;
			this._btnUserInfo.Text = "User Info";
			this._btnUserInfo.UseVisualStyleBackColor = true;
			this._btnUserInfo.Click += new System.EventHandler(this._btnUserInfo_Click);
			// 
			// _btnCreateAnnotation
			// 
			this._btnCreateAnnotation.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this._btnCreateAnnotation.Location = new System.Drawing.Point(7, 505);
			this._btnCreateAnnotation.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._btnCreateAnnotation.Name = "_btnCreateAnnotation";
			this._btnCreateAnnotation.Size = new System.Drawing.Size(155, 37);
			this._btnCreateAnnotation.TabIndex = 3;
			this._btnCreateAnnotation.Text = "&Create Annotation";
			this._btnCreateAnnotation.UseVisualStyleBackColor = true;
			this._btnCreateAnnotation.Click += new System.EventHandler(this._btnCreateAnnotation_Click);
			// 
			// _btnExtension1
			// 
			this._btnExtension1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this._btnExtension1.Location = new System.Drawing.Point(174, 505);
			this._btnExtension1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
			this._btnExtension1.Name = "_btnExtension1";
			this._btnExtension1.Size = new System.Drawing.Size(15, 37);
			this._btnExtension1.TabIndex = 3;
			this._btnExtension1.Text = "";
			this._btnExtension1.UseVisualStyleBackColor = true;
			this._btnExtension1.Visible = false;
			this._btnExtension1.AutoSize = true;
			this._btnExtension1.Click += new System.EventHandler(this._btnCreateAnnotation_Click);
			// 
			// _componentContainerControl
			// 
			this._componentContainerControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._componentContainerControl.AutoScroll = true;
			this._componentContainerControl.Location = new System.Drawing.Point(0, 56);
			this._componentContainerControl.Margin = new System.Windows.Forms.Padding(4);
			this._componentContainerControl.Name = "_componentContainerControl";
			this._componentContainerControl.SelectedTemplate = null;
			this._componentContainerControl.Size = new System.Drawing.Size(327, 442);
			this._componentContainerControl.TabIndex = 2;
			// 
			// TemplateControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._componentContainerControl);
			this.Controls.Add(this._btnUserInfo);
			this.Controls.Add(this._btnCreateAnnotation);
			this.Controls.Add(this._btnExtension1);
			this.Controls.Add(this._tboxAnnotationName);
			this.Controls.Add(this._lblAnnotationName);
			this.Name = "TemplateControl";
			this.Size = new System.Drawing.Size(330, 544);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox _tboxAnnotationName;
		private System.Windows.Forms.Label _lblAnnotationName;
		private System.Windows.Forms.Button _btnUserInfo;
		private System.Windows.Forms.Button _btnCreateAnnotation;
		private System.Windows.Forms.Button _btnExtension1;
		private ComponentContainerControl _componentContainerControl;
	}
}
