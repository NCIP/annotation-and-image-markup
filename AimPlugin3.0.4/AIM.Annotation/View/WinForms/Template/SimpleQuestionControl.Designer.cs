//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

namespace AIM.Annotation.View.WinForms.Template
{
	partial class SimpleQuestionControl
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
			this._lblEntity = new AIM.Annotation.View.WinForms.ToolTipLinkLabel();
			this._toolTip = new System.Windows.Forms.ToolTip(this.components);
			this.SuspendLayout();
			// 
			// _lblEntity
			// 
			this._lblEntity.ActiveLinkColor = System.Drawing.SystemColors.ActiveCaption;
			this._lblEntity.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._lblEntity.AutoEllipsis = true;
			this._lblEntity.BackColor = System.Drawing.Color.Transparent;
			this._lblEntity.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._lblEntity.LinkArea = new System.Windows.Forms.LinkArea(0, 0);
			this._lblEntity.LinkColor = System.Drawing.SystemColors.ControlText;
			this._lblEntity.Location = new System.Drawing.Point(4, 4);
			this._lblEntity.Margin = new System.Windows.Forms.Padding(4);
			this._lblEntity.Name = "_lblEntity";
			this._lblEntity.ShowToolTip = false;
			this._lblEntity.Size = new System.Drawing.Size(137, 18);
			this._lblEntity.TabIndex = 1;
			this._lblEntity.Text = "Test";
			this._lblEntity.ToolTipText = null;
			// 
			// _toolTip
			// 
			this._toolTip.AutoPopDelay = 20000;
			this._toolTip.InitialDelay = 500;
			this._toolTip.IsBalloon = true;
			this._toolTip.ReshowDelay = 100;
			// 
			// SimpleQuestionControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.Controls.Add(this._lblEntity);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "SimpleQuestionControl";
			this.Size = new System.Drawing.Size(145, 28);
			this.ResumeLayout(false);

		}

		#endregion

		private ToolTipLinkLabel _lblEntity;
		private System.Windows.Forms.ToolTip _toolTip;
	}
}
