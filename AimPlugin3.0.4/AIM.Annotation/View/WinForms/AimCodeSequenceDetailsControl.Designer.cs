//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

namespace AIM.Annotation.View.WinForms
{
	partial class AimCodeSequenceDetailsControl
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
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
			this._dgvCodeSequenceDetails = new System.Windows.Forms.DataGridView();
			this._codeMeaning = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this._codeValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this._codingSchemeDesignator = new System.Windows.Forms.DataGridViewTextBoxColumn();
			((System.ComponentModel.ISupportInitialize)(this._dgvCodeSequenceDetails)).BeginInit();
			this.SuspendLayout();
			// 
			// _dgvCodeSequenceDetails
			// 
			this._dgvCodeSequenceDetails.AllowUserToAddRows = false;
			this._dgvCodeSequenceDetails.AllowUserToDeleteRows = false;
			this._dgvCodeSequenceDetails.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCellsExceptHeader;
			dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
			dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
			dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
			dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
			dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
			this._dgvCodeSequenceDetails.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this._dgvCodeSequenceDetails.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this._dgvCodeSequenceDetails.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this._codeMeaning,
            this._codeValue,
            this._codingSchemeDesignator});
			this._dgvCodeSequenceDetails.Dock = System.Windows.Forms.DockStyle.Fill;
			this._dgvCodeSequenceDetails.Location = new System.Drawing.Point(0, 0);
			this._dgvCodeSequenceDetails.Name = "_dgvCodeSequenceDetails";
			this._dgvCodeSequenceDetails.ReadOnly = true;
			this._dgvCodeSequenceDetails.RowHeadersVisible = false;
			this._dgvCodeSequenceDetails.RowTemplate.Height = 24;
			this._dgvCodeSequenceDetails.Size = new System.Drawing.Size(390, 425);
			this._dgvCodeSequenceDetails.TabIndex = 0;
			// 
			// _codeMeaning
			// 
			this._codeMeaning.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
			this._codeMeaning.HeaderText = "Code Meaning";
			this._codeMeaning.MinimumWidth = 25;
			this._codeMeaning.Name = "_codeMeaning";
			this._codeMeaning.ReadOnly = true;
			// 
			// _codeValue
			// 
			this._codeValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
			this._codeValue.HeaderText = "Code Value";
			this._codeValue.MinimumWidth = 25;
			this._codeValue.Name = "_codeValue";
			this._codeValue.ReadOnly = true;
			// 
			// _codingSchemeDesignator
			// 
			this._codingSchemeDesignator.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
			this._codingSchemeDesignator.HeaderText = "Coding Scheme Designator";
			this._codingSchemeDesignator.MinimumWidth = 25;
			this._codingSchemeDesignator.Name = "_codingSchemeDesignator";
			this._codingSchemeDesignator.ReadOnly = true;
			// 
			// AimCodeSequenceDetailsControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._dgvCodeSequenceDetails);
			this.Name = "AimCodeSequenceDetailsControl";
			this.Size = new System.Drawing.Size(390, 425);
			((System.ComponentModel.ISupportInitialize)(this._dgvCodeSequenceDetails)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.DataGridView _dgvCodeSequenceDetails;
		private System.Windows.Forms.DataGridViewTextBoxColumn _codeMeaning;
		private System.Windows.Forms.DataGridViewTextBoxColumn _codeValue;
		private System.Windows.Forms.DataGridViewTextBoxColumn _codingSchemeDesignator;
	}
}
