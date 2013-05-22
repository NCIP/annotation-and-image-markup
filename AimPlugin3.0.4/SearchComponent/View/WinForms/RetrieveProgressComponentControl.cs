//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections;
using System.Windows.Forms;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

namespace SearchComponent.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="RetrieveProgressComponent"/>.
    /// </summary>
    public partial class RetrieveProgressComponentControl : ApplicationComponentUserControl
    {
        private readonly RetrieveProgressComponent _component;

        /// <summary>
        /// Constructor.
        /// </summary>
        public RetrieveProgressComponentControl(RetrieveProgressComponent component)
            :base(component)
        {
			_component = component;
            InitializeComponent();

			ClearCanvasStyle.SetTitleBarStyle(_titleBar);

			_titleBar.DataBindings.Add("Text", _component, "Title", true, DataSourceUpdateMode.OnPropertyChanged);

			_tableView.Table = _component.Table;
			_tableView.ToolbarModel = _component.ToolbarModel;
			_tableView.MenuModel = _component.MenuModel;
			_tableView.SelectionChanged += OnSelectionChanged;
			_tableView.ItemDoubleClicked += OnItemDoubleClicked;
		}

		private static ISelection ReverseSelection(ISelection selection)
		{
			ArrayList list = new ArrayList();

			if (selection != null && selection.Items != null)
			{
				foreach (object o in selection.Items)
					list.Add(o);

				list.Reverse();
			}

			return new Selection(list);
		}

		private void OnSelectionChanged(object sender, EventArgs e)
		{
			_component.SetSelection(ReverseSelection(_tableView.Selection));
		}

		private void OnItemDoubleClicked(object sender, EventArgs e)
		{
			_component.ItemDoubleClick();
		}
	}
}
