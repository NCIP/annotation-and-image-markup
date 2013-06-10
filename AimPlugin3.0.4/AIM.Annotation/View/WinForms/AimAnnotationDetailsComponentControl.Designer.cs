#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

namespace AIM.Annotation.View.WinForms
{
    partial class AimAnnotationDetailsComponentControl
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
			System.Windows.Forms.Panel _panelCalcualtions;
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AimAnnotationDetailsComponentControl));
			this._tboxCalculations = new System.Windows.Forms.TextBox();
			this._infoTabs = new System.Windows.Forms.TabControl();
			this._tabAnatomicEnities = new System.Windows.Forms.TabPage();
			this._tabImagingObservations = new System.Windows.Forms.TabPage();
			this._tabCalculations = new System.Windows.Forms.TabPage();
			this._tabWebBrowser = new System.Windows.Forms.TabPage();
			this._wbDetails = new System.Windows.Forms.WebBrowser();
			this.contextMenuWb = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
			this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			_panelCalcualtions = new System.Windows.Forms.Panel();
			_panelCalcualtions.SuspendLayout();
			this._infoTabs.SuspendLayout();
			this._tabCalculations.SuspendLayout();
			this._tabWebBrowser.SuspendLayout();
			this.contextMenuWb.SuspendLayout();
			this.SuspendLayout();
			// 
			// _panelCalcualtions
			// 
			_panelCalcualtions.AutoScroll = true;
			_panelCalcualtions.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
			_panelCalcualtions.Controls.Add(this._tboxCalculations);
			_panelCalcualtions.Dock = System.Windows.Forms.DockStyle.Fill;
			_panelCalcualtions.Location = new System.Drawing.Point(3, 3);
			_panelCalcualtions.Name = "_panelCalcualtions";
			_panelCalcualtions.Size = new System.Drawing.Size(543, 458);
			_panelCalcualtions.TabIndex = 0;
			// 
			// _tboxCalculations
			// 
			this._tboxCalculations.Dock = System.Windows.Forms.DockStyle.Fill;
			this._tboxCalculations.Location = new System.Drawing.Point(0, 0);
			this._tboxCalculations.Multiline = true;
			this._tboxCalculations.Name = "_tboxCalculations";
			this._tboxCalculations.ReadOnly = true;
			this._tboxCalculations.Size = new System.Drawing.Size(543, 458);
			this._tboxCalculations.TabIndex = 0;
			// 
			// _infoTabs
			// 
			this._infoTabs.Controls.Add(this._tabAnatomicEnities);
			this._infoTabs.Controls.Add(this._tabImagingObservations);
			this._infoTabs.Controls.Add(this._tabCalculations);
			this._infoTabs.Controls.Add(this._tabWebBrowser);
			this._infoTabs.Dock = System.Windows.Forms.DockStyle.Fill;
			this._infoTabs.Location = new System.Drawing.Point(0, 0);
			this._infoTabs.Name = "_infoTabs";
			this._infoTabs.SelectedIndex = 0;
			this._infoTabs.Size = new System.Drawing.Size(557, 493);
			this._infoTabs.TabIndex = 0;
			// 
			// _tabAnatomicEnities
			// 
			this._tabAnatomicEnities.Location = new System.Drawing.Point(4, 25);
			this._tabAnatomicEnities.Name = "_tabAnatomicEnities";
			this._tabAnatomicEnities.Padding = new System.Windows.Forms.Padding(3);
			this._tabAnatomicEnities.Size = new System.Drawing.Size(549, 464);
			this._tabAnatomicEnities.TabIndex = 0;
			this._tabAnatomicEnities.Text = "Anatomic Enities";
			this._tabAnatomicEnities.UseVisualStyleBackColor = true;
			// 
			// _tabImagingObservations
			// 
			this._tabImagingObservations.Location = new System.Drawing.Point(4, 25);
			this._tabImagingObservations.Name = "_tabImagingObservations";
			this._tabImagingObservations.Padding = new System.Windows.Forms.Padding(3);
			this._tabImagingObservations.Size = new System.Drawing.Size(549, 464);
			this._tabImagingObservations.TabIndex = 1;
			this._tabImagingObservations.Text = "Imaging Observartions";
			this._tabImagingObservations.UseVisualStyleBackColor = true;
			// 
			// _tabCalculations
			// 
			this._tabCalculations.Controls.Add(_panelCalcualtions);
			this._tabCalculations.Location = new System.Drawing.Point(4, 25);
			this._tabCalculations.Name = "_tabCalculations";
			this._tabCalculations.Padding = new System.Windows.Forms.Padding(3);
			this._tabCalculations.Size = new System.Drawing.Size(549, 464);
			this._tabCalculations.TabIndex = 2;
			this._tabCalculations.Text = "Calculations";
			this._tabCalculations.UseVisualStyleBackColor = true;
			// 
			// _tabWebBrowser
			// 
			this._tabWebBrowser.Controls.Add(this._wbDetails);
			this._tabWebBrowser.Location = new System.Drawing.Point(4, 25);
			this._tabWebBrowser.Name = "_tabWebBrowser";
			this._tabWebBrowser.Padding = new System.Windows.Forms.Padding(3);
			this._tabWebBrowser.Size = new System.Drawing.Size(549, 464);
			this._tabWebBrowser.TabIndex = 3;
			this._tabWebBrowser.Text = "All Details";
			this._tabWebBrowser.UseVisualStyleBackColor = true;
			// 
			// _wbDetails
			// 
			this._wbDetails.AllowNavigation = true;
			this._wbDetails.AllowWebBrowserDrop = false;
			this._wbDetails.ContextMenuStrip = this.contextMenuWb;
			this._wbDetails.Dock = System.Windows.Forms.DockStyle.Fill;
			this._wbDetails.IsWebBrowserContextMenuEnabled = false;
			this._wbDetails.Location = new System.Drawing.Point(3, 3);
			this._wbDetails.MinimumSize = new System.Drawing.Size(20, 20);
			this._wbDetails.Name = "_wbDetails";
			this._wbDetails.Size = new System.Drawing.Size(543, 458);
			this._wbDetails.TabIndex = 0;
			this._wbDetails.WebBrowserShortcutsEnabled = false;
			// 
			// contextMenuWb
			// 
			this.contextMenuWb.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.toolStripSeparator4,
            this.selectAllToolStripMenuItem});
			this.contextMenuWb.Name = "contextMenuWb";
			this.contextMenuWb.Size = new System.Drawing.Size(153, 76);
			this.contextMenuWb.Opening += new System.ComponentModel.CancelEventHandler(this.ContextMenuWbOpening);
			// 
			// copyToolStripMenuItem
			// 
			this.copyToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("copyToolStripMenuItem.Image")));
			this.copyToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
			this.copyToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.copyToolStripMenuItem.Text = "&Copy";
			this.copyToolStripMenuItem.Click += new System.EventHandler(this.CopyToolStripMenuItemClick);
			// 
			// toolStripSeparator4
			// 
			this.toolStripSeparator4.Name = "toolStripSeparator4";
			this.toolStripSeparator4.Size = new System.Drawing.Size(149, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
			this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.selectAllToolStripMenuItem.Text = "Select &All";
			this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.SelectAllToolStripMenuItemClick);
			// 
			// AimAnnotationDetailsComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._infoTabs);
			this.Name = "AimAnnotationDetailsComponentControl";
			this.Size = new System.Drawing.Size(557, 493);
			_panelCalcualtions.ResumeLayout(false);
			_panelCalcualtions.PerformLayout();
			this._infoTabs.ResumeLayout(false);
			this._tabCalculations.ResumeLayout(false);
			this._tabWebBrowser.ResumeLayout(false);
			this.contextMenuWb.ResumeLayout(false);
			this.ResumeLayout(false);

        }

        #endregion

		private System.Windows.Forms.TabControl _infoTabs;
		private System.Windows.Forms.TabPage _tabAnatomicEnities;
		private System.Windows.Forms.TabPage _tabImagingObservations;
		private System.Windows.Forms.TabPage _tabCalculations;
		private System.Windows.Forms.TextBox _tboxCalculations;
		private System.Windows.Forms.TabPage _tabWebBrowser;
		private System.Windows.Forms.WebBrowser _wbDetails;
		private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
		private System.Windows.Forms.ContextMenuStrip contextMenuWb;
    }
}
