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
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace SearchComponent.View.WinForms
{
	public partial class ModalityPicker : UserControl
	{
		private CheckedListBox _modalityPicker;

		private List<string> _availableModalities;
		private SortedList<string, string> _checkedModalities;

		private bool _availableModalitiesSet;

		public ModalityPicker()
		{
			InitializeComponent();

			_modalityPicker = new CheckedListBox();
			_modalityPicker.BorderStyle = BorderStyle.None;
			_modalityPicker.CheckOnClick = true;
			_modalityPicker.SelectionMode = SelectionMode.One;

			// We don't sort the list automatically, because we want the "Clear" item at the top.
			_modalityPicker.Sorted = false;
			_modalityPicker.ItemCheck += new ItemCheckEventHandler(OnModalityPickerItemCheck);

			_contextMenuStrip.Items.Add(new ToolStripControlHost(_modalityPicker));

			//_showModalityListButton.Image = IconFactory.CreateIcon("ExpandRight.png", new ResourceResolver(this.GetType().Assembly));

			_availableModalitiesSet = false;
			_availableModalities = new List<string>();
			_checkedModalities = new SortedList<string, string>();
		}

		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		[Browsable(false)]
		public IList<string> CheckedModalities
		{
			get
			{
				return _checkedModalities.Keys;
			}
			set
			{
				SetCheckedModalities(value);
			}
		}

		public string LabelText
		{
			get { return _label.Text; }
			set { _label.Text = value; }
		}

		public void SetAvailableModalities(ICollection<string> modalities)
		{
			if (_availableModalitiesSet || modalities == null || modalities.Count == 0)
				throw new InvalidOperationException("Cannot reset modalities");

			_availableModalitiesSet = true;

			SortedList<string, string> sorter = new SortedList<string, string>();
			if (modalities != null)
			{
				foreach (string modality in modalities)
				{
					if (!sorter.ContainsKey(modality))
						sorter.Add(modality, modality);
				}
			}

			_availableModalities.Clear();
			_availableModalities.Add("Clear");
			_availableModalities.AddRange(sorter.Keys);

			_modalityPicker.Items.Clear();
			_modalityPicker.Items.AddRange(_availableModalities.ToArray());

			this.CheckedModalities = new List<string>();
		}

		private void SetCheckedModalities(IList<string> modalities)
		{
			if (!_availableModalitiesSet)
				return;

			List<string> checkedModalities = new List<string>();
			if (modalities != null)
				checkedModalities.AddRange(modalities);

			_checkedModalities.Clear();

			foreach (string checkedModality in checkedModalities)
			{
				if (!_checkedModalities.ContainsKey(checkedModality))
					_checkedModalities.Add(checkedModality, checkedModality);
			}

			//skip the 'Clear' selection.
			for (int index = 1; index < _modalityPicker.Items.Count; ++index)
			{
				string modality = (string)_modalityPicker.Items[index];
				_modalityPicker.SetItemChecked(index, _checkedModalities.ContainsKey(modality));
			}

			UpdateText();
		}

		private void OnModalityPickerItemCheck(object sender, ItemCheckEventArgs e)
		{
			if (e.Index == 0) // "Clear" item
			{
				e.NewValue = CheckState.Unchecked;
				this.CheckedModalities = new List<string>();
				return;
			}

			if (e.NewValue == CheckState.Checked)
			{
				foreach (int i in _modalityPicker.CheckedIndices)
					_modalityPicker.SetItemChecked(i, false);
			}

			string itemModality = (string)_modalityPicker.Items[e.Index];

			if (e.NewValue == CheckState.Unchecked)
			{
				if (_checkedModalities.ContainsKey(itemModality))
					_checkedModalities.Remove(itemModality);
			}
			else
			{
				if (!_checkedModalities.ContainsKey(itemModality))
					_checkedModalities.Add(itemModality, itemModality);
			}

			UpdateText();
		}

		private void UpdateText()
		{
			string newText = "";
			foreach (string checkedModality in _checkedModalities.Keys)
			{
				newText += checkedModality + @", ";
			}

			if (newText.Length > 0)
				newText = newText.Remove(newText.Length - 2);

			this._modalitiesString.Text = newText;
		}

		private void OnShowModalityListClick(object sender, EventArgs e)
		{
			_contextMenuStrip.Show(_showModalityListButton, new Point(0, _showModalityListButton.Height), ToolStripDropDownDirection.BelowRight);
		}
	}
}
