#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
