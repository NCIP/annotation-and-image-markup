namespace SearchComponent.View.WinForms
{
	partial class AddEntityForm
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

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this._items = new System.Windows.Forms.DataGridView();
			this.CodeValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.CodeMeaning = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.CodingSchemeDesignator = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this._ok = new System.Windows.Forms.Button();
			this._cancel = new System.Windows.Forms.Button();
			this._searchText = new System.Windows.Forms.TextBox();
			this._search = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this._items)).BeginInit();
			this.SuspendLayout();
			// 
			// _items
			// 
			this._items.AllowUserToAddRows = false;
			this._items.AllowUserToResizeColumns = false;
			this._items.AllowUserToResizeRows = false;
			this._items.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this._items.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this._items.BackgroundColor = System.Drawing.SystemColors.Window;
			this._items.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this._items.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
			this._items.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this._items.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.CodeValue,
            this.CodeMeaning,
            this.CodingSchemeDesignator});
			this._items.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
			this._items.Location = new System.Drawing.Point(16, 47);
			this._items.Margin = new System.Windows.Forms.Padding(4);
			this._items.Name = "_items";
			this._items.ReadOnly = true;
			this._items.RowHeadersVisible = false;
			this._items.RowTemplate.Height = 24;
			this._items.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this._items.Size = new System.Drawing.Size(504, 154);
			this._items.TabIndex = 2;
			// 
			// CodeValue
			// 
			this.CodeValue.DataPropertyName = "CodeValue";
			this.CodeValue.HeaderText = "Code Value";
			this.CodeValue.Name = "CodeValue";
			this.CodeValue.ReadOnly = true;
			// 
			// CodeMeaning
			// 
			this.CodeMeaning.DataPropertyName = "CodeMeaning";
			this.CodeMeaning.HeaderText = "Code Meaning";
			this.CodeMeaning.Name = "CodeMeaning";
			this.CodeMeaning.ReadOnly = true;
			// 
			// CodingSchemeDesignator
			// 
			this.CodingSchemeDesignator.DataPropertyName = "CodingSchemeDesignator";
			this.CodingSchemeDesignator.HeaderText = "Coding Scheme Designator";
			this.CodingSchemeDesignator.Name = "CodingSchemeDesignator";
			this.CodingSchemeDesignator.ReadOnly = true;
			// 
			// _ok
			// 
			this._ok.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._ok.Location = new System.Drawing.Point(315, 215);
			this._ok.Margin = new System.Windows.Forms.Padding(4);
			this._ok.Name = "_ok";
			this._ok.Size = new System.Drawing.Size(100, 28);
			this._ok.TabIndex = 3;
			this._ok.Text = "OK";
			this._ok.UseVisualStyleBackColor = true;
			this._ok.Click += new System.EventHandler(this._ok_Click);
			// 
			// _cancel
			// 
			this._cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this._cancel.Location = new System.Drawing.Point(420, 215);
			this._cancel.Margin = new System.Windows.Forms.Padding(4);
			this._cancel.Name = "_cancel";
			this._cancel.Size = new System.Drawing.Size(100, 28);
			this._cancel.TabIndex = 4;
			this._cancel.Text = "Cancel";
			this._cancel.UseVisualStyleBackColor = true;
			this._cancel.Click += new System.EventHandler(this._cancel_Click);
			// 
			// _searchText
			// 
			this._searchText.Location = new System.Drawing.Point(16, 15);
			this._searchText.Margin = new System.Windows.Forms.Padding(4);
			this._searchText.Name = "_searchText";
			this._searchText.Size = new System.Drawing.Size(417, 22);
			this._searchText.TabIndex = 0;
			// 
			// _search
			// 
			this._search.Location = new System.Drawing.Point(444, 14);
			this._search.Margin = new System.Windows.Forms.Padding(4);
			this._search.Name = "_search";
			this._search.Size = new System.Drawing.Size(76, 28);
			this._search.TabIndex = 1;
			this._search.Text = "Search";
			this._search.UseVisualStyleBackColor = true;
			this._search.Click += new System.EventHandler(this._search_Click);
			// 
			// AddEntityForm
			// 
			this.AcceptButton = this._ok;
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(539, 258);
			this.ControlBox = false;
			this.Controls.Add(this._search);
			this.Controls.Add(this._cancel);
			this.Controls.Add(this._ok);
			this.Controls.Add(this._searchText);
			this.Controls.Add(this._items);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "AddEntityForm";
			this.Text = "Add";
			((System.ComponentModel.ISupportInitialize)(this._items)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.DataGridView _items;
		private System.Windows.Forms.DataGridViewTextBoxColumn CodeValue;
		private System.Windows.Forms.DataGridViewTextBoxColumn CodeMeaning;
		private System.Windows.Forms.DataGridViewTextBoxColumn CodingSchemeDesignator;
		private System.Windows.Forms.Button _ok;
		private System.Windows.Forms.Button _cancel;
		private System.Windows.Forms.TextBox _searchText;
		private System.Windows.Forms.Button _search;
	}
}