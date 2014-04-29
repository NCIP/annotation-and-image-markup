namespace AIM.Annotation.View.WinForms
{
	partial class AimDetailsListControl
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
			this._mainPanel = new System.Windows.Forms.Panel();
			this.SuspendLayout();
			// 
			// _mainPanel
			// 
			this._mainPanel.AutoSize = true;
			this._mainPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._mainPanel.BackColor = System.Drawing.Color.Transparent;
			this._mainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this._mainPanel.Location = new System.Drawing.Point(0, 0);
			this._mainPanel.Margin = new System.Windows.Forms.Padding(2);
			this._mainPanel.Name = "_mainPanel";
			this._mainPanel.Size = new System.Drawing.Size(0, 0);
			this._mainPanel.TabIndex = 0;
			this._mainPanel.ClientSizeChanged += new System.EventHandler(this.OnPanelClientSizeChanged);
			// 
			// AimDetailsListControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.AutoSize = true;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.Controls.Add(this._mainPanel);
			this.DoubleBuffered = true;
			this.Margin = new System.Windows.Forms.Padding(2);
			this.Name = "AimDetailsListControl";
			this.Size = new System.Drawing.Size(0, 0);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel _mainPanel;
	}
}