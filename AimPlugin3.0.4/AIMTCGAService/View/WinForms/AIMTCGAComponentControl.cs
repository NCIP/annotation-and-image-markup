//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Specialized;
using System.Windows.Forms;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.View.WinForms;

namespace AIMTCGAService.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="AIMTCGAComponent"/>.
    /// </summary>
    public partial class AIMTCGAComponentControl : ApplicationComponentUserControl
    {
        private readonly AIMTCGAComponent _component;

    	/// <summary>
        /// Constructor.
        /// </summary>
        public AIMTCGAComponentControl(AIMTCGAComponent component)
            : base(component)
        {
            InitializeComponent();
            _component = component;

			_aimTCGAServiceComboBox.DataBindings.Add("DataSource", _component, "AIMTCGAServiceList", false, DataSourceUpdateMode.OnPropertyChanged);
        	_aimTCGAServiceComboBox.DataBindings.Add("Text", _component, "AIMTCGAServiceUrl", false, DataSourceUpdateMode.OnPropertyChanged);
		}

		private void _aimTCGAServiceComboBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (_aimTCGAServiceComboBox.DroppedDown && _aimTCGAServiceComboBox.SelectedIndex != -1 && e.KeyCode == Keys.Delete)
			{
				e.Handled = true;
				var sl = new StringCollection();
				sl.AddRange(CollectionUtils.ToArray<string>(_component.AIMTCGAServiceList));
				sl.RemoveAt(_aimTCGAServiceComboBox.SelectedIndex);

				_component.AIMTCGAServiceList = sl;
			}
		}

		private void _btnSave_Click(object sender, EventArgs e)
		{
			_component.SaveRequested = true;
		}
    }
}
