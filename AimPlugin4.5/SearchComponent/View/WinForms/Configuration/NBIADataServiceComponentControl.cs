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
using System.Windows.Forms;
using ClearCanvas.Desktop.View.WinForms;
using ClearCanvas.Common.Utilities;
using System.Collections.Specialized;
using SearchComponent.Configuration;

namespace SearchComponent.View.WinForms.Configuration
{
	/// <summary>
	/// Provides a Windows Forms user-interface for <see cref="AIMTCGAComponent"/>.
	/// </summary>
	public partial class NBIADataServiceComponentControl : ApplicationComponentUserControl
	{
		private readonly NBIADataServiceComponent _component;

		readonly AutoCompleteStringCollection accs_a;
		readonly AutoCompleteStringCollection accs_b;
		bool _accsCheck = true; //true for accs_a, false for accs_b

		/// <summary>
		/// Constructor.
		/// </summary>
		public NBIADataServiceComponentControl(NBIADataServiceComponent component)
			: base(component)
		{
			InitializeComponent();
			_component = component;
			

			// TODO Fix data binding to string collection of recent URLs list

			//_nbiaDataServiceComboBox.DataSource = _component.NbiaDataServiceUrlList;
			//_nbiaDataServiceComboBox.DataBindings.Add("DataSource", _component, "NbiaDataServiceUrlList", false, DataSourceUpdateMode.OnPropertyChanged);
			//nbiaDataServiceComboBox.DataBindings.Add("Text", _component, "NbiaDataServiceUrl", false, DataSourceUpdateMode.OnPropertyChanged);

			//_nbiaDataServiceTransferUrlComboBox.DataBindings.Add("DataSource", _component, "NbiaDataServiceTransferUrlList", false, DataSourceUpdateMode.OnPropertyChanged);

			//_nbiaDataServiceComboBox.AutoCompleteMode = AutoCompleteMode.Suggest;
			//_nbiaDataServiceComboBox.AutoCompleteSource = AutoCompleteSource.ListItems;

			_nbiaDataServiceRetrieveUrlComboBox.DataBindings.Add("Text", _component, "NbiaDataServiceUrl", false, DataSourceUpdateMode.OnPropertyChanged);
			_nbiaDataServiceTransferUrlComboBox.DataBindings.Add("Text", _component, "NbiaDataServiceTransferUrl", false, DataSourceUpdateMode.OnPropertyChanged);

			//accs_a = new AutoCompleteStringCollection();
			//accs_b = new AutoCompleteStringCollection();

			//_nbiaDataServiceComboBox.AutoCompleteMode = AutoCompleteMode.Suggest;
			//_nbiaDataServiceComboBox.AutoCompleteSource = AutoCompleteSource.CustomSource;
			//_nbiaDataServiceComboBox.AutoCompleteCustomSource = accs_a;
			//_nbiaDataServiceComboBox.TextChanged += OnTextChanged;
		}

		private void _aimTCGAServiceComboBox_KeyDown(object sender, KeyEventArgs e)
		{
			//if (_nbiaDataServiceComboBox.DroppedDown && _nbiaDataServiceComboBox.SelectedIndex != -1 && e.KeyCode == Keys.Delete)
			//{
			//    e.Handled = true;
			//    StringCollection sl = new StringCollection();
			//    sl.AddRange(CollectionUtils.ToArray<string>(_component.NbiaDataServiceUrlList));
			//    sl.RemoveAt(_nbiaDataServiceComboBox.SelectedIndex);

			//    _component.NbiaDataServiceUrlList = sl;
			//}
		}

		private void _btnSave_Click(object sender, EventArgs e)
		{
			_component.SaveRequested = true;
		}

		private void OnTextChanged(object sender, EventArgs e)
		{
			//_nbiaDataServiceComboBox.DroppedDown = false;

			//string text = _nbiaDataServiceComboBox.Text;

			//if (_accsCheck)
			//{
			//    accs_b.Clear();
			//    accs_b.AddRange(GetNameSuggestions(text));
			//    _accsCheck = false;
			//}
			//else
			//{
			//    accs_a.Clear();
			//    accs_a.AddRange(GetNameSuggestions(text));
			//    _accsCheck = true;
			//}

			//_nbiaDataServiceComboBox.AutoCompleteCustomSource = _accsCheck ? accs_a : accs_b;
		}

		private string[] GetNameSuggestions(string text)
		{
			return CollectionUtils.Select(_component.NbiaDataServiceUrlList, (string p) => p.StartsWith(text)).ToArray();
		}

		private void OnKeyPress(object sender, KeyPressEventArgs e)
		{
			// hand-rolled autocomplete code

			// Code from comments at http://www.codeproject.com/KB/combobox/csautocomplete.aspx
			ComboBox cb = (ComboBox)sender; //ComboBox
			if (Char.IsControl(e.KeyChar))
				return;

			string toFind = cb.Text.Substring(0, cb.SelectionStart) + e.KeyChar;
			int index = cb.FindStringExact(toFind);
			if (index == -1)
				index = cb.FindString(toFind);
			if (index == -1)
				return;
			cb.SelectedIndex = index;
			cb.SelectionStart = toFind.Length;
			cb.SelectionLength = cb.Text.Length - cb.SelectionStart;
			e.Handled = true;

		}
	}
}
