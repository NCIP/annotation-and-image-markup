#region License

// Copyright (c) 2006-2007, ClearCanvas Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//    * Neither the name of ClearCanvas Inc. nor the names of its contributors 
//      may be used to endorse or promote products derived from this software without 
//      specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
// OF SUCH DAMAGE.

#endregion

namespace AIMTCGAService.View.WinForms
{
    partial class AIMTCGAComponentControl
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
			this.aimTCGApictureBox = new System.Windows.Forms.PictureBox();
			this.aimDtatServicelabel = new System.Windows.Forms.Label();
			this._aimTCGAServiceComboBox = new System.Windows.Forms.ComboBox();
			this._btnCancel = new System.Windows.Forms.Button();
			this._btnSave = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.aimTCGApictureBox)).BeginInit();
			this.SuspendLayout();
			// 
			// aimTCGApictureBox
			// 
			this.aimTCGApictureBox.Image = global::AIMTCGAService.View.WinForms.Properties.Resources.AIM_LOGO;
			this.aimTCGApictureBox.Location = new System.Drawing.Point(16, 10);
			this.aimTCGApictureBox.Margin = new System.Windows.Forms.Padding(4);
			this.aimTCGApictureBox.Name = "aimTCGApictureBox";
			this.aimTCGApictureBox.Size = new System.Drawing.Size(40, 107);
			this.aimTCGApictureBox.TabIndex = 0;
			this.aimTCGApictureBox.TabStop = false;
			// 
			// aimDtatServicelabel
			// 
			this.aimDtatServicelabel.AutoSize = true;
			this.aimDtatServicelabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.aimDtatServicelabel.ForeColor = System.Drawing.Color.SlateBlue;
			this.aimDtatServicelabel.Location = new System.Drawing.Point(64, 10);
			this.aimDtatServicelabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
			this.aimDtatServicelabel.Name = "aimDtatServicelabel";
			this.aimDtatServicelabel.Size = new System.Drawing.Size(307, 31);
			this.aimDtatServicelabel.TabIndex = 1;
			this.aimDtatServicelabel.Text = "AIM Data Service URL";
			// 
			// _aimTCGAServiceComboBox
			// 
			this._aimTCGAServiceComboBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._aimTCGAServiceComboBox.FormattingEnabled = true;
			this._aimTCGAServiceComboBox.Location = new System.Drawing.Point(70, 62);
			this._aimTCGAServiceComboBox.Margin = new System.Windows.Forms.Padding(4);
			this._aimTCGAServiceComboBox.Name = "_aimTCGAServiceComboBox";
			this._aimTCGAServiceComboBox.Size = new System.Drawing.Size(616, 24);
			this._aimTCGAServiceComboBox.TabIndex = 4;
			this._aimTCGAServiceComboBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this._aimTCGAServiceComboBox_KeyDown);
			// 
			// _btnCancel
			// 
			this._btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this._btnCancel.Location = new System.Drawing.Point(611, 117);
			this._btnCancel.Name = "_btnCancel";
			this._btnCancel.Size = new System.Drawing.Size(75, 23);
			this._btnCancel.TabIndex = 5;
			this._btnCancel.Text = "&Cancel";
			this._btnCancel.UseVisualStyleBackColor = true;
			// 
			// _btnSave
			// 
			this._btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnSave.DialogResult = System.Windows.Forms.DialogResult.OK;
			this._btnSave.Location = new System.Drawing.Point(530, 116);
			this._btnSave.Name = "_btnSave";
			this._btnSave.Size = new System.Drawing.Size(75, 23);
			this._btnSave.TabIndex = 6;
			this._btnSave.Text = "&Save";
			this._btnSave.UseVisualStyleBackColor = true;
			this._btnSave.Click += new System.EventHandler(this._btnSave_Click);
			// 
			// AIMTCGAComponentControl
			// 
			this.AcceptButton = this._btnSave;
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this._btnCancel;
			this.Controls.Add(this._btnSave);
			this.Controls.Add(this._btnCancel);
			this.Controls.Add(this._aimTCGAServiceComboBox);
			this.Controls.Add(this.aimDtatServicelabel);
			this.Controls.Add(this.aimTCGApictureBox);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "AIMTCGAComponentControl";
			this.Size = new System.Drawing.Size(703, 157);
			((System.ComponentModel.ISupportInitialize)(this.aimTCGApictureBox)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox aimTCGApictureBox;
        private System.Windows.Forms.Label aimDtatServicelabel;
        private System.Windows.Forms.ComboBox _aimTCGAServiceComboBox;
		private System.Windows.Forms.Button _btnCancel;
		private System.Windows.Forms.Button _btnSave;
    }
}
