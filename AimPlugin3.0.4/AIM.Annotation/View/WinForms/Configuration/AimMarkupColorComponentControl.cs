//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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

            var bindingSource = new BindingSource();
            bindingSource.DataSource = _component;

            _checkBoxRandomMarkupColor.DataBindings.Add("Checked", _component, "UseRandomDefaultMarkupColor", true, DataSourceUpdateMode.OnPropertyChanged);
            OnRandomMarkupColorCheckedChanged(null, new EventArgs());
            PopulateLoginNameMarkupColorListView();
            Load += OnAimMarkupColorComponentControlParentChanged;
        }

        private void OnAimMarkupColorComponentControlParentChanged(object sender, EventArgs e)
        {
            ((Form)TopLevelControl).Activated += OnAimMarkupColorComponentControlActivated;
        }

        private void OnAimMarkupColorComponentControlActivated(object sender, EventArgs e)
        {
            if (!_activated)    
            {
                _activated = true;
                if (AimRoiGraphic.SelectedAimRoiGraphic != null)
                {
                    var aimGraphic = AimRoiGraphic.SelectedAimRoiGraphic.ParentGraphic as AimGraphic;
                    if (aimGraphic != null)
                    {
                        var username = aimGraphic.AimAnnotation.User.LoginName.ToLower();
                        var items = _listViewLoginNameMarkupColor.Items.Find(username, false);
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
        	foreach (var userMarkupProperties in _component.AvailableUserMarkupProperties)
        	{
				var item = new ListViewItem(userMarkupProperties.Key);
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
            using (var colorDialog = new ColorDialog())
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
            var info = _listViewLoginNameMarkupColor.HitTest(new Point(e.X, e.Y));
            if (info.SubItem != null && info.Item.SubItems.IndexOf(info.SubItem) == 1)
            {
                OpenColorDialogForSubitem(info.Item, info.SubItem);
            }
        }

        private void OpenColorDialogForSubitem(ListViewItem item, ListViewItem.ListViewSubItem subItem)
        {
            using (var colorDialog = new ColorDialog())
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
            var colors = new List<int>();
            foreach (var color in _component.GetSavedColors())
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
            var item = new ListViewItem(loginName);
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
				item.Remove();
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
