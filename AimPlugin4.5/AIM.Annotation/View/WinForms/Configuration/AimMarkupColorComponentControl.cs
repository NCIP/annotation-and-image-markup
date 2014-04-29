#region License

// Copyright (c) 2007 - 2014, Northwestern University, Vladimir Kleper, Skip Talbot
// and Pattanasak Mongkolwat.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//   Neither the name of the National Cancer Institute nor Northwestern University
//   nor the names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

using ClearCanvas.Desktop.View.WinForms;

using AIM.Annotation.Graphics;
using AIM.Annotation.Configuration;

namespace AIM.Annotation.View.WinForms.Configuration
{
    public partial class AimMarkupColorComponentControl : ApplicationComponentUserControl
    {
        private readonly AimMarkupColorComponent _component;
        private string _labelBeforeEdit = String.Empty;
        private bool _activated = false;

        public AimMarkupColorComponentControl(AimMarkupColorComponent component) : base(component)
        {
            _component = component;
            InitializeComponent();

            BindingSource bindingSource = new BindingSource();
            bindingSource.DataSource = _component;

            _checkBoxRandomMarkupColor.DataBindings.Add("Checked", _component, "UseRandomDefaultMarkupColor", true, DataSourceUpdateMode.OnPropertyChanged);
            OnRandomMarkupColorCheckedChanged(null, new EventArgs());
            PopulateLoginNameMarkupColorListView();
            this.Load += OnAimMarkupColorComponentControlParentChanged;
        }

        private void OnAimMarkupColorComponentControlParentChanged(object sender, EventArgs e)
        {
            ((Form)this.TopLevelControl).Activated += OnAimMarkupColorComponentControlActivated;
        }

        private void OnAimMarkupColorComponentControlActivated(object sender, EventArgs e)
        {
            if (!_activated)    
            {
                _activated = true;
                if (AimRoiGraphic.SelectedAimRoiGraphic != null)
                {
                    string username = AimRoiGraphic.SelectedAimRoiGraphic.UserLoginName;
                    if (username != null)
                    {
                        ListViewItem[] items = _listViewLoginNameMarkupColor.Items.Find(username, false);
                        if (items.Length > 0)
                        {
                            OpenColorDialogForSubitem(items[0], items[0].SubItems[1]);
                            items[0].Selected = true;
                        }
                    }
                }
            }
        }

        private void PopulateLoginNameMarkupColorListView()
        {
        	foreach (KeyValuePair<string, AimMarkupColorComponent.UserMarkupProperties> userMarkupProperties in _component.AvailableUserMarkupProperties)
        	{
				ListViewItem item = new ListViewItem(userMarkupProperties.Key);
				item.Name = userMarkupProperties.Key;
				item.UseItemStyleForSubItems = false;
				if (userMarkupProperties.Value.IsReadFromSettings)
					item.Font = new Font(item.Font, FontStyle.Bold);
				item.SubItems.Add(new ListViewItem.ListViewSubItem(item, string.Empty, Color.Black, userMarkupProperties.Value.Color, item.Font));
				if (userMarkupProperties.Value.IsDisplayed)
					item.SubItems.Add(new ListViewItem.ListViewSubItem(item, @" • ", Color.Black, item.BackColor, item.Font));
				_listViewLoginNameMarkupColor.Items.Add(item);
			}
        }

        private void OnSelectDefaultMarkupColorClick(object sender, EventArgs e)
        {
            using (ColorDialog colorDialog = new ColorDialog())
            {
                colorDialog.AllowFullOpen = true;
                colorDialog.AnyColor = true;
                colorDialog.Color = _component.DefaultMarkupColor;
                colorDialog.CustomColors = GetCustomColorSet();
                colorDialog.FullOpen = true;
                colorDialog.ShowHelp = false;
                colorDialog.SolidColorOnly = false;
                if (colorDialog.ShowDialog(this) == DialogResult.OK)
                {
                    _btnSelectDefaultMarkupColor.BackColor = colorDialog.Color;
                    _component.DefaultMarkupColor = colorDialog.Color;
                }
            }
        }

        private void OnRandomMarkupColorCheckedChanged(object sender, EventArgs e)
        {
            if (_checkBoxRandomMarkupColor.Checked)
            {
                _btnSelectDefaultMarkupColor.BackColor = SystemColors.Control;
                _btnSelectDefaultMarkupColor.Enabled = false;
            }
            else
            {
                _btnSelectDefaultMarkupColor.BackColor = _component.DefaultMarkupColor;
                _btnSelectDefaultMarkupColor.Enabled = true;
            }
        }

        private void OnListViewLoginNameMarkupColorMouseUp(object sender, MouseEventArgs e)
        {
            ListViewHitTestInfo info = _listViewLoginNameMarkupColor.HitTest(new Point(e.X, e.Y));
            if (info.SubItem != null && info.Item.SubItems.IndexOf(info.SubItem) == 1)
            {
                OpenColorDialogForSubitem(info.Item, info.SubItem);
            }
        }

        private void OpenColorDialogForSubitem(ListViewItem item, ListViewItem.ListViewSubItem subItem)
        {
            using (ColorDialog colorDialog = new ColorDialog())
            {
                colorDialog.AllowFullOpen = true;
                colorDialog.AnyColor = true;
                colorDialog.Color = subItem.BackColor;
                colorDialog.CustomColors = GetCustomColorSet();
                colorDialog.FullOpen = true;
                colorDialog.ShowHelp = false;
                colorDialog.SolidColorOnly = false;
                if (colorDialog.ShowDialog(this) == DialogResult.OK)
                {
                    subItem.BackColor = colorDialog.Color;
                    _component.SetLoginNameMarkupColor(item.Text, colorDialog.Color);
                }
            }
        }

        private int[] GetCustomColorSet()
        {
            List<int> colors = new List<int>();
            foreach (Color color in _component.GetSavedColors())
            {
                colors.Add(ColorToColorRef(color));
            }
            return colors.ToArray();
        }

        private static int ColorToColorRef(Color color)
        {
            return (color.R + (color.G << 8) + (color.B << 16));
        }

        private void OnListViewLoginNameMarkupColorAfterLabelEdit(object sender, LabelEditEventArgs e)
        {
            if (!string.IsNullOrEmpty(e.Label))
                _component.UpdateLoginName(_listViewLoginNameMarkupColor.Items[e.Item].Text, e.Label);
            else
                e.CancelEdit = true;
        }

        private void OnListViewLoginNameMarkupColorBeforeLabelEdit(object sender, LabelEditEventArgs e)
        {
            _labelBeforeEdit = e.Label;
        }

        private void OnAddLoginClick(object sender, EventArgs e)
        {
            string loginName;
            Color color;
            _component.AddLoginNameMarkupColor(out loginName, out color);
            ListViewItem item = new ListViewItem(loginName);
            item.UseItemStyleForSubItems = false;
            item.SubItems.Add(new ListViewItem.ListViewSubItem(item, string.Empty, Color.Black, color, item.Font));
            _listViewLoginNameMarkupColor.Items.Add(item);
            item.BeginEdit();
        }

        private void OnRemoveClick(object sender, EventArgs e)
        {
            foreach (ListViewItem item in _listViewLoginNameMarkupColor.SelectedItems)
            {
                _component.RemoveLoginNameMarkupColor(item.Text);
				item.Remove(); // only remove the item if no markup properties are returned by component
            }
        }

        private void OnSetToDefaultClick(object sender, EventArgs e)
        {
            foreach (ListViewItem item in _listViewLoginNameMarkupColor.SelectedItems)
            {
                _component.SetDefaultLoginNameMarkupColor(item.Text);
				item.SubItems[1].BackColor = _component.GetLoginNameMarkupColor(item.Text);
            }
        }

        private void OnSelectAllClick(object sender, EventArgs e)
        {
            _listViewLoginNameMarkupColor.Focus();
            foreach (ListViewItem item in _listViewLoginNameMarkupColor.Items)
                item.Selected = true;
        }

        private void OnListViewLoginNameMarkupColorKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Delete:
                    OnRemoveClick(sender, e);
                    break;
                case Keys.A:
                    if (e.Modifiers == Keys.Control)
                        OnSelectAllClick(sender, e);
                    break;
            }
        }
    }
}
