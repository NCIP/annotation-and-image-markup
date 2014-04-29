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

namespace SearchComponent.View.WinForms.Configuration
{
	partial class NBIADataServiceComponentControl
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
			this._nbiaDataServiceLabel = new System.Windows.Forms.Label();
			this._btnCancel = new System.Windows.Forms.Button();
			this._btnSave = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this._nbiaDataServiceRetrieveUrlComboBox = new System.Windows.Forms.ComboBox();
			this._nbiaDataServiceTransferUrlComboBox = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// _nbiaDataServiceLabel
			// 
			this._nbiaDataServiceLabel.AutoSize = true;
			this._nbiaDataServiceLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this._nbiaDataServiceLabel.ForeColor = System.Drawing.Color.SlateBlue;
			this._nbiaDataServiceLabel.Location = new System.Drawing.Point(1, 8);
			this._nbiaDataServiceLabel.Name = "_nbiaDataServiceLabel";
			this._nbiaDataServiceLabel.Size = new System.Drawing.Size(270, 25);
			this._nbiaDataServiceLabel.TabIndex = 1;
			this._nbiaDataServiceLabel.Text = "NBIA Data Service URLs";
			// 
			// _btnCancel
			// 
			this._btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this._btnCancel.Location = new System.Drawing.Point(459, 114);
			this._btnCancel.Margin = new System.Windows.Forms.Padding(2);
			this._btnCancel.Name = "_btnCancel";
			this._btnCancel.Size = new System.Drawing.Size(56, 19);
			this._btnCancel.TabIndex = 5;
			this._btnCancel.Text = "&Cancel";
			this._btnCancel.UseVisualStyleBackColor = true;
			this._btnCancel.Visible = false;
			// 
			// _btnSave
			// 
			this._btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._btnSave.DialogResult = System.Windows.Forms.DialogResult.OK;
			this._btnSave.Location = new System.Drawing.Point(399, 114);
			this._btnSave.Margin = new System.Windows.Forms.Padding(2);
			this._btnSave.Name = "_btnSave";
			this._btnSave.Size = new System.Drawing.Size(56, 19);
			this._btnSave.TabIndex = 6;
			this._btnSave.Text = "&Save";
			this._btnSave.UseVisualStyleBackColor = true;
			this._btnSave.Visible = false;
			this._btnSave.Click += new System.EventHandler(this._btnSave_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(3, 53);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 13);
			this.label1.TabIndex = 8;
			this.label1.Text = "Retrieve URL";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(3, 80);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(71, 13);
			this.label2.TabIndex = 9;
			this.label2.Text = "Transfer URL";
			// 
			// _nbiaDataServiceRetrieveUrlComboBox
			// 
			this._nbiaDataServiceRetrieveUrlComboBox.FormattingEnabled = true;
			this._nbiaDataServiceRetrieveUrlComboBox.Location = new System.Drawing.Point(81, 50);
			this._nbiaDataServiceRetrieveUrlComboBox.Name = "_nbiaDataServiceRetrieveUrlComboBox";
			this._nbiaDataServiceRetrieveUrlComboBox.Size = new System.Drawing.Size(374, 21);
			this._nbiaDataServiceRetrieveUrlComboBox.TabIndex = 10;
			// 
			// _nbiaDataServiceTransferUrlComboBox
			// 
			this._nbiaDataServiceTransferUrlComboBox.FormattingEnabled = true;
			this._nbiaDataServiceTransferUrlComboBox.Location = new System.Drawing.Point(80, 77);
			this._nbiaDataServiceTransferUrlComboBox.Name = "_nbiaDataServiceTransferUrlComboBox";
			this._nbiaDataServiceTransferUrlComboBox.Size = new System.Drawing.Size(375, 21);
			this._nbiaDataServiceTransferUrlComboBox.TabIndex = 11;
			// 
			// NBIADataServiceComponentControl
			// 
			this.AcceptButton = this._btnSave;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this._btnCancel;
			this.Controls.Add(this._nbiaDataServiceTransferUrlComboBox);
			this.Controls.Add(this._nbiaDataServiceRetrieveUrlComboBox);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this._btnSave);
			this.Controls.Add(this._btnCancel);
			this.Controls.Add(this._nbiaDataServiceLabel);
			this.Name = "NBIADataServiceComponentControl";
			this.Size = new System.Drawing.Size(527, 144);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label _nbiaDataServiceLabel;
		private System.Windows.Forms.Button _btnCancel;
		private System.Windows.Forms.Button _btnSave;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ComboBox _nbiaDataServiceRetrieveUrlComboBox;
		private System.Windows.Forms.ComboBox _nbiaDataServiceTransferUrlComboBox;
	}
}
