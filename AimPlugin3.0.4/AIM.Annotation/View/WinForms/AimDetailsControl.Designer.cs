//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

namespace AIM.Annotation.View.WinForms
{
	partial class AimDetailsControl
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
			this._groupBox = new System.Windows.Forms.GroupBox();
			this._tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
			this._flowPanelIo = new System.Windows.Forms.FlowLayoutPanel();
			this._lblIo = new System.Windows.Forms.Label();
			this._lblAe = new System.Windows.Forms.Label();
			this._flowPanelAe = new System.Windows.Forms.FlowLayoutPanel();
			this._linkOpenImageAnnotation = new System.Windows.Forms.LinkLabel();
			this._lblAimName = new AIM.Annotation.View.WinForms.ToolTipLinkLabel();
			this._toolTip = new System.Windows.Forms.ToolTip(this.components);
			this._groupBox.SuspendLayout();
			this._tableLayoutPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// _groupBox
			// 
			this._groupBox.AutoSize = true;
			this._groupBox.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._groupBox.BackColor = System.Drawing.Color.Transparent;
			this._groupBox.Controls.Add(this._tableLayoutPanel);
			this._groupBox.Controls.Add(this._linkOpenImageAnnotation);
			this._groupBox.Controls.Add(this._lblAimName);
			this._groupBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this._groupBox.Location = new System.Drawing.Point(0, 0);
			this._groupBox.Name = "_groupBox";
			this._groupBox.Size = new System.Drawing.Size(134, 97);
			this._groupBox.TabIndex = 0;
			this._groupBox.TabStop = false;
			// 
			// _tableLayoutPanel
			// 
			this._tableLayoutPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._tableLayoutPanel.AutoSize = true;
			this._tableLayoutPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._tableLayoutPanel.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
			this._tableLayoutPanel.ColumnCount = 2;
			this._tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
			this._tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
			this._tableLayoutPanel.Controls.Add(this._flowPanelIo, 1, 1);
			this._tableLayoutPanel.Controls.Add(this._lblIo, 0, 1);
			this._tableLayoutPanel.Controls.Add(this._lblAe, 0, 0);
			this._tableLayoutPanel.Controls.Add(this._flowPanelAe, 1, 0);
			this._tableLayoutPanel.Location = new System.Drawing.Point(3, 35);
			this._tableLayoutPanel.Name = "_tableLayoutPanel";
			this._tableLayoutPanel.RowCount = 2;
			this._tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this._tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
			this._tableLayoutPanel.Size = new System.Drawing.Size(125, 29);
			this._tableLayoutPanel.TabIndex = 2;
			this._tableLayoutPanel.SizeChanged += new System.EventHandler(this.OnTableLayoutPanelSizeChanged);
			// 
			// _flowPanelIo
			// 
			this._flowPanelIo.AutoSize = true;
			this._flowPanelIo.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this._flowPanelIo.Dock = System.Windows.Forms.DockStyle.Fill;
			this._flowPanelIo.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
			this._flowPanelIo.Location = new System.Drawing.Point(35, 18);
			this._flowPanelIo.Name = "_flowPanelIo";
			this._flowPanelIo.Size = new System.Drawing.Size(86, 7);
			this._flowPanelIo.TabIndex = 3;
			this._flowPanelIo.WrapContents = false;
			this._flowPanelIo.ClientSizeChanged += new System.EventHandler(this.OnFlowPanelIoClientSizeChanged);
			// 
			// _lblIo
			// 
			this._lblIo.AutoSize = true;
			this._lblIo.Location = new System.Drawing.Point(4, 15);
			this._lblIo.Name = "_lblIo";
			this._lblIo.Size = new System.Drawing.Size(21, 13);
			this._lblIo.TabIndex = 2;
			this._lblIo.Text = "IO:";
			this._lblIo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this._toolTip.SetToolTip(this._lblIo, "Imaging Observations");
			// 
			// _lblAe
			// 
			this._lblAe.AutoSize = true;
			this._lblAe.Location = new System.Drawing.Point(4, 1);
			this._lblAe.Name = "_lblAe";
			this._lblAe.Size = new System.Drawing.Size(24, 13);
			this._lblAe.TabIndex = 0;
			this._lblAe.Text = "AE:";
			this._lblAe.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this._toolTip.SetToolTip(this._lblAe, "Anatomic Enities");
			// 
			// _flowPanelAe
			// 
			this._flowPanelAe.AutoSize = true;
			this._flowPanelAe.Dock = System.Windows.Forms.DockStyle.Fill;
			this._flowPanelAe.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
			this._flowPanelAe.Location = new System.Drawing.Point(35, 4);
			this._flowPanelAe.Name = "_flowPanelAe";
			this._flowPanelAe.Size = new System.Drawing.Size(86, 7);
			this._flowPanelAe.TabIndex = 1;
			this._flowPanelAe.WrapContents = false;
			this._flowPanelAe.ClientSizeChanged += new System.EventHandler(this.OnFlowPanelAeClientSizeChanged);
			// 
			// _linkOpenImageAnnotation
			// 
			this._linkOpenImageAnnotation.AutoSize = true;
			this._linkOpenImageAnnotation.Location = new System.Drawing.Point(46, 75);
			this._linkOpenImageAnnotation.Name = "_linkOpenImageAnnotation";
			this._linkOpenImageAnnotation.Size = new System.Drawing.Size(64, 13);
			this._linkOpenImageAnnotation.TabIndex = 3;
			this._linkOpenImageAnnotation.TabStop = true;
			this._linkOpenImageAnnotation.Text = "Show Study";
			this._linkOpenImageAnnotation.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.OnOpenAnnotationLinkClicked);
			// 
			// _lblAimName
			// 
			this._lblAimName.AutoEllipsis = true;
			this._lblAimName.AutoSize = true;
			this._lblAimName.LinkArea = new System.Windows.Forms.LinkArea(0, 0);
			this._lblAimName.Location = new System.Drawing.Point(6, 15);
			this._lblAimName.Name = "_lblAimName";
			this._lblAimName.ShowToolTip = false;
			this._lblAimName.Size = new System.Drawing.Size(60, 13);
			this._lblAimName.TabIndex = 0;
			this._lblAimName.Text = "AIM Name:";
			this._lblAimName.ToolTipText = null;
			// 
			// _toolTip
			// 
			this._toolTip.AutoPopDelay = 20000;
			this._toolTip.InitialDelay = 500;
			this._toolTip.IsBalloon = true;
			this._toolTip.ReshowDelay = 100;
			this._toolTip.ShowAlways = true;
			// 
			// AimDetailsControl
			// 
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
			this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.Controls.Add(this._groupBox);
			this.DoubleBuffered = true;
			this.Name = "AimDetailsControl";
			this.Size = new System.Drawing.Size(134, 97);
			this._groupBox.ResumeLayout(false);
			this._groupBox.PerformLayout();
			this._tableLayoutPanel.ResumeLayout(false);
			this._tableLayoutPanel.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox _groupBox;
		private System.Windows.Forms.TableLayoutPanel _tableLayoutPanel;
		private System.Windows.Forms.FlowLayoutPanel _flowPanelIo;
		private System.Windows.Forms.Label _lblIo;
		private System.Windows.Forms.ToolTip _toolTip;
		private System.Windows.Forms.Label _lblAe;
		private System.Windows.Forms.FlowLayoutPanel _flowPanelAe;
		private System.Windows.Forms.LinkLabel _linkOpenImageAnnotation;
		private ToolTipLinkLabel _lblAimName;

	}
}