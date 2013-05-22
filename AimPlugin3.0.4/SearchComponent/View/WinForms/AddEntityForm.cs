//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using ClearCanvas.Common.Utilities;

namespace SearchComponent.View.WinForms
{
	public partial class AddEntityForm : Form
	{
		private readonly IList<ICodeSequenceItem> _allItems;

		public AddEntityForm(IList<ICodeSequenceItem> codeSequenceItems)
		{
			InitializeComponent();

			_allItems = new List<ICodeSequenceItem>(codeSequenceItems);
			_items.DataSource = codeSequenceItems;

			_items.DoubleClick += OnItemDoubleClick;
			base.AcceptButton = _search;
			base.CancelButton = _cancel;
		}

		public IEnumerable<ICodeSequenceItem> SelectedItems
		{
			get
			{
				foreach (DataGridViewRow row in _items.SelectedRows)
				{
					yield return row.DataBoundItem as ICodeSequenceItem;
				}
			}
		}

		private void OnItemDoubleClick(object sender, EventArgs e)
		{
			Close();
		}

		private void _ok_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void _cancel_Click(object sender, EventArgs e)
		{
            _items.ClearSelection();
			this.Close();
		}

		private void _search_Click(object sender, EventArgs e)
		{
			_items.DataSource = CollectionUtils.Select(_allItems,
				delegate(ICodeSequenceItem item)
				{
					return (item.CodeMeaning ?? "").Contains(_searchText.Text) ||
						(item.CodeValue ?? "").Contains(_searchText.Text) ||
						(item.CodingSchemeDesignator ?? "").Contains(_searchText.Text);
				});
		}
	}
}
