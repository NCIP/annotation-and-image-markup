//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

namespace AIM.Annotation.View.WinForms.Configuration
{
    partial class AimMarkupColorComponentControl
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
			this._btnSelectDefaultMarkupColor = new System.Windows.Forms.Button();
			this.lblDefaultMarkupColor = new System.Windows.Forms.Label();
			this._listViewLoginNameMarkupColor = new System.Windows.Forms.ListView();
			this.columnHeaderLoginName = new System.Windows.Forms.ColumnHeader();
			this.columnHeaderMarkupColor = new System.Windows.Forms.ColumnHeader();
			this.columnHeaderActive = new System.Windows.Forms.ColumnHeader();
			this._checkBoxRandomMarkupColor = new System.Windows.Forms.CheckBox();
			this._btnResetToDefaultColor = new System.Windows.Forms.Button();
			this._btnAddLogin = new System.Windows.Forms.Button();
			this._btnRemoveSelected = new System.Windows.Forms.Button();
			this._btnSelectAll = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// _btnSelectDefaultMarkupColor
			// 
			this._btnSelectDefaultMarkupColor.Location = new System.Drawing.Point(114, 5);
			this._btnSelectDefaultMarkupColor.Name = "_btnSelectDefaultMarkupColor";
			this._btnSelectDefaultMarkupColor.Size = new System.Drawing.Size(75, 23);
			this._btnSelectDefaultMarkupColor.TabIndex = 14;
			this._btnSelectDefaultMarkupColor.UseVisualStyleBackColor = true;
			this._btnSelectDefaultMarkupColor.Click += new System.EventHandler(this.OnSelectDefaultMarkupColorClick);
			// 
			// lblDefaultMarkupColor
			// 
			this.lblDefaultMarkupColor.AutoSize = true;
			this.lblDefaultMarkupColor.Location = new System.Drawing.Point(2, 10);
			this.lblDefaultMarkupColor.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lblDefaultMarkupColor.Name = "lblDefaultMarkupColor";
			this.lblDefaultMarkupColor.Size = new System.Drawing.Size(107, 13);
			this.lblDefaultMarkupColor.TabIndex = 13;
			this.lblDefaultMarkupColor.Text = "Default Markup Color";
			// 
			// _listViewLoginNameMarkupColor
			// 
			this._listViewLoginNameMarkupColor.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderLoginName,
            this.columnHeaderMarkupColor,
            this.columnHeaderActive});
			this._listViewLoginNameMarkupColor.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
			this._listViewLoginNameMarkupColor.LabelEdit = true;
			this._listViewLoginNameMarkupColor.Location = new System.Drawing.Point(5, 34);
			this._listViewLoginNameMarkupColor.Name = "_listViewLoginNameMarkupColor";
			this._listViewLoginNameMarkupColor.Size = new System.Drawing.Size(390, 207);
			this._listViewLoginNameMarkupColor.TabIndex = 16;
			this._listViewLoginNameMarkupColor.UseCompatibleStateImageBehavior = false;
			this._listViewLoginNameMarkupColor.View = System.Windows.Forms.View.Details;
			this._listViewLoginNameMarkupColor.AfterLabelEdit += new System.Windows.Forms.LabelEditEventHandler(this.OnListViewLoginNameMarkupColorAfterLabelEdit);
			this._listViewLoginNameMarkupColor.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OnListViewLoginNameMarkupColorMouseUp);
			this._listViewLoginNameMarkupColor.BeforeLabelEdit += new System.Windows.Forms.LabelEditEventHandler(this.OnListViewLoginNameMarkupColorBeforeLabelEdit);
			this._listViewLoginNameMarkupColor.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OnListViewLoginNameMarkupColorKeyDown);
			// 
			// columnHeaderLoginName
			// 
			this.columnHeaderLoginName.Text = "Login Name";
			this.columnHeaderLoginName.Width = 135;
			// 
			// columnHeaderMarkupColor
			// 
			this.columnHeaderMarkupColor.Text = "Markup Color";
			this.columnHeaderMarkupColor.Width = 120;
			// 
			// columnHeaderActive
			// 
			this.columnHeaderActive.Text = "Active";
			this.columnHeaderActive.Width = 42;
			// 
			// _checkBoxRandomMarkupColor
			// 
			this._checkBoxRandomMarkupColor.AutoSize = true;
			this._checkBoxRandomMarkupColor.Checked = true;
			this._checkBoxRandomMarkupColor.CheckState = System.Windows.Forms.CheckState.Checked;
			this._checkBoxRandomMarkupColor.Location = new System.Drawing.Point(196, 10);
			this._checkBoxRandomMarkupColor.Name = "_checkBoxRandomMarkupColor";
			this._checkBoxRandomMarkupColor.Size = new System.Drawing.Size(66, 17);
			this._checkBoxRandomMarkupColor.TabIndex = 17;
			this._checkBoxRandomMarkupColor.Text = "Random";
			this._checkBoxRandomMarkupColor.UseVisualStyleBackColor = true;
			this._checkBoxRandomMarkupColor.CheckedChanged += new System.EventHandler(this.OnRandomMarkupColorCheckedChanged);
			// 
			// _btnResetToDefaultColor
			// 
			this._btnResetToDefaultColor.Location = new System.Drawing.Point(124, 276);
			this._btnResetToDefaultColor.Name = "_btnResetToDefaultColor";
			this._btnResetToDefaultColor.Size = new System.Drawing.Size(147, 23);
			this._btnResetToDefaultColor.TabIndex = 18;
			this._btnResetToDefaultColor.Text = "Reset To Default Color";
			this._btnResetToDefaultColor.UseVisualStyleBackColor = true;
			this._btnResetToDefaultColor.Click += new System.EventHandler(this.OnSetToDefaultClick);
			// 
			// _btnAddLogin
			// 
			this._btnAddLogin.Location = new System.Drawing.Point(5, 247);
			this._btnAddLogin.Name = "_btnAddLogin";
			this._btnAddLogin.Size = new System.Drawing.Size(113, 23);
			this._btnAddLogin.TabIndex = 19;
			this._btnAddLogin.Text = "Add Login";
			this._btnAddLogin.UseVisualStyleBackColor = true;
			this._btnAddLogin.Click += new System.EventHandler(this.OnAddLoginClick);
			// 
			// _btnRemoveSelected
			// 
			this._btnRemoveSelected.Location = new System.Drawing.Point(124, 247);
			this._btnRemoveSelected.Name = "_btnRemoveSelected";
			this._btnRemoveSelected.Size = new System.Drawing.Size(147, 23);
			this._btnRemoveSelected.TabIndex = 20;
			this._btnRemoveSelected.Text = "Remove Selected";
			this._btnRemoveSelected.UseVisualStyleBackColor = true;
			this._btnRemoveSelected.Click += new System.EventHandler(this.OnRemoveClick);
			// 
			// _btnSelectAll
			// 
			this._btnSelectAll.Location = new System.Drawing.Point(5, 276);
			this._btnSelectAll.Name = "_btnSelectAll";
			this._btnSelectAll.Size = new System.Drawing.Size(113, 23);
			this._btnSelectAll.TabIndex = 21;
			this._btnSelectAll.Text = "Select All";
			this._btnSelectAll.UseVisualStyleBackColor = true;
			this._btnSelectAll.Click += new System.EventHandler(this.OnSelectAllClick);
			// 
			// AimMarkupColorComponentControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this._btnSelectAll);
			this.Controls.Add(this._btnRemoveSelected);
			this.Controls.Add(this._btnAddLogin);
			this.Controls.Add(this._btnResetToDefaultColor);
			this.Controls.Add(this._checkBoxRandomMarkupColor);
			this.Controls.Add(this._listViewLoginNameMarkupColor);
			this.Controls.Add(this._btnSelectDefaultMarkupColor);
			this.Controls.Add(this.lblDefaultMarkupColor);
			this.Name = "AimMarkupColorComponentControl";
			this.Size = new System.Drawing.Size(473, 354);
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _btnSelectDefaultMarkupColor;
        private System.Windows.Forms.Label lblDefaultMarkupColor;
        private System.Windows.Forms.ListView _listViewLoginNameMarkupColor;
        private System.Windows.Forms.ColumnHeader columnHeaderLoginName;
        private System.Windows.Forms.ColumnHeader columnHeaderMarkupColor;
        private System.Windows.Forms.CheckBox _checkBoxRandomMarkupColor;
        private System.Windows.Forms.Button _btnResetToDefaultColor;
        private System.Windows.Forms.Button _btnAddLogin;
        private System.Windows.Forms.Button _btnRemoveSelected;
        private System.Windows.Forms.Button _btnSelectAll;
        private System.Windows.Forms.ColumnHeader columnHeaderActive;
    }
}
