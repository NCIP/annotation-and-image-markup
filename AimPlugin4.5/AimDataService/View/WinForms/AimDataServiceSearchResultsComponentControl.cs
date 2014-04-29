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
using System.Collections;
using System.Windows.Forms;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;
using MessageBox = System.Windows.Forms.MessageBox;

namespace AimDataService.View.WinForms
{
	public partial class AimDataServiceSearchResultsComponentControl : ApplicationComponentUserControl
	{
		private readonly AimDataServiceSearchResultsComponent _component;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimDataServiceSearchResultsComponentControl(AimDataServiceSearchResultsComponent component)
			: base(component)
		{
			InitializeComponent();

			_component = component;

			ClearCanvasStyle.SetTitleBarStyle(_titleBar);
			_titleBar.DataBindings.Add("Text", _component, "Title", true, DataSourceUpdateMode.OnPropertyChanged);

			DataBindings.Add("ErrorMessage", _component, "ErrorMessage", true, DataSourceUpdateMode.OnPropertyChanged);

			_tableView.Table = _component.Table;
			_tableView.ToolbarModel = _component.ToolbarModel;
			_tableView.MenuModel = _component.MenuModel;
			_tableView.SelectionChanged += OnSelectionChanged;
			_tableView.ItemDoubleClicked += OnItemDoubleClicked;
		}

		private static ISelection ReverseSelection(ISelection selection)
		{
			var list = new ArrayList();

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

		public string ErrorMessage
		{
			set
			{
				if (!string.IsNullOrEmpty(value))
				{
					MessageBox.Show(this, _component.ErrorMessage, "Query Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
					_component.ErrorMessage = null; // clear message after it was shown
				}
			}
			get { return null; } // NOOP
		}
	}
}
