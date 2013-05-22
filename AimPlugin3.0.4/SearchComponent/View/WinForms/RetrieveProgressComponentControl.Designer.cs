//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace SearchComponent.View.WinForms
{
    partial class RetrieveProgressComponentControl
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
			this._tableView = new ClearCanvas.Desktop.View.WinForms.TableView();
			this._titleBar = new Crownwood.DotNetMagic.Controls.TitleBar();
			this.SuspendLayout();
			// 
			// _tableView
			// 
			this._tableView.BackColor = System.Drawing.Color.White;
			this._tableView.Dock = System.Windows.Forms.DockStyle.Fill;
			this._tableView.FilterTextBoxWidth = 132;
			this._tableView.Location = new System.Drawing.Point(0, 37);
			this._tableView.Margin = new System.Windows.Forms.Padding(5);
			this._tableView.Name = "_tableView";
			this._tableView.ReadOnly = false;
			this._tableView.Size = new System.Drawing.Size(1090, 163);
			this._tableView.TabIndex = 24;
			// 
			// _titleBar
			// 
			this._titleBar.Dock = System.Windows.Forms.DockStyle.Top;
			this._titleBar.Font = new System.Drawing.Font("Arial", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._titleBar.GradientColoring = Crownwood.DotNetMagic.Controls.GradientColoring.LightBackToDarkBack;
			this._titleBar.Location = new System.Drawing.Point(0, 0);
			this._titleBar.Margin = new System.Windows.Forms.Padding(4);
			this._titleBar.MouseOverColor = System.Drawing.Color.Empty;
			this._titleBar.Name = "_titleBar";
			this._titleBar.Size = new System.Drawing.Size(1090, 37);
			this._titleBar.Style = Crownwood.DotNetMagic.Common.VisualStyle.IDE2005;
			this._titleBar.TabIndex = 23;
			this._titleBar.Text = "Retrieval Progress";
			// 
			// RetrieveProgressComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._tableView);
			this.Controls.Add(this._titleBar);
			this.Name = "RetrieveProgressComponentControl";
			this.Size = new System.Drawing.Size(1090, 200);
			this.ResumeLayout(false);

        }

        #endregion

		private ClearCanvas.Desktop.View.WinForms.TableView _tableView;
		private Crownwood.DotNetMagic.Controls.TitleBar _titleBar;
    }
}
