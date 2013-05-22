//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace AIM.Annotation.View.WinForms
{
    partial class AimAnnotationsListComponentControl
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
			this._tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
			this._labelNoAnnotationsAvailable = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// _tableLayoutPanel
			// 
			this._tableLayoutPanel.AutoSize = true;
			this._tableLayoutPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._tableLayoutPanel.ColumnCount = 1;
			this._tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this._tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
			this._tableLayoutPanel.Dock = System.Windows.Forms.DockStyle.Top;
			this._tableLayoutPanel.Location = new System.Drawing.Point(0, 0);
			this._tableLayoutPanel.Name = "_tableLayoutPanel";
			this._tableLayoutPanel.RowCount = 1;
			this._tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this._tableLayoutPanel.Size = new System.Drawing.Size(150, 0);
			this._tableLayoutPanel.TabIndex = 1;
			this._tableLayoutPanel.Visible = false;
			// 
			// _labelNoAnnotationsAvailable
			// 
			this._labelNoAnnotationsAvailable.AutoSize = true;
			this._labelNoAnnotationsAvailable.Dock = System.Windows.Forms.DockStyle.Top;
			this._labelNoAnnotationsAvailable.Location = new System.Drawing.Point(0, 0);
			this._labelNoAnnotationsAvailable.Name = "_labelNoAnnotationsAvailable";
			this._labelNoAnnotationsAvailable.Size = new System.Drawing.Size(126, 13);
			this._labelNoAnnotationsAvailable.TabIndex = 2;
			this._labelNoAnnotationsAvailable.Text = "No Annotations Available";
			this._labelNoAnnotationsAvailable.TextAlign = System.Drawing.ContentAlignment.TopCenter;
			// 
			// AimAnnotationsListComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.Controls.Add(this._labelNoAnnotationsAvailable);
			this.Controls.Add(this._tableLayoutPanel);
			this.DoubleBuffered = true;
			this.Margin = new System.Windows.Forms.Padding(2);
			this.Name = "AimAnnotationsListComponentControl";
			this.Size = new System.Drawing.Size(150, 244);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

		//private AimDetailsListControl _aimDetailsListControl;
		private System.Windows.Forms.TableLayoutPanel _tableLayoutPanel;
		private System.Windows.Forms.Label _labelNoAnnotationsAvailable;
    }
}
