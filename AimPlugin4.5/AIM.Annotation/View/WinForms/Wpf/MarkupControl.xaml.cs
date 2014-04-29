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
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
	/// <summary>
	/// Interaction logic for MarkupControl.xaml
	/// </summary>
	public partial class MarkupControl : UserControl
	{

		protected AimAnnotationComponent Component { get; private set; }
		public ObservableCollection<MarkupListViewItem> MarkupListViewItems { get; private set; }

		public MarkupControl(AimAnnotationComponent component)
		{
			Component = component;
			MarkupListViewItems = new ObservableCollection<MarkupListViewItem>();

			InitializeComponent();

			Component.AimTemplateTreeMarkupChanged += OnAimTemplateTreeMarkupChanged;
			Loaded += MarkupControlLoaded;
		}

		protected void MarkupControlLoaded(object sender, RoutedEventArgs e)
		{
			InitializeList();
		}

		private void InitializeList()
		{
			MarkupListViewItems.Clear();
			if (Component.AimTemplateTree != null)
			{
				foreach (var markup in Component.AimTemplateTree.Markup)
				{
					MarkupListViewItems.Add(new MarkupListViewItem(markup));
				}
			}
		}

		protected void OnAimTemplateTreeMarkupChanged(object sender, EventArgs e)
		{
			InitializeList();
		}

		private void CheckBoxChecked(object sender, RoutedEventArgs e)
		{
			var checkBox = sender as CheckBox;

			if (checkBox != null && checkBox.IsChecked.HasValue)
			{
				var markupListViewItem = checkBox.Tag as MarkupListViewItem;
				if (markupListViewItem != null)
				{
					Component.SelectMarkup(markupListViewItem.Markup, checkBox.IsChecked.Value);
				}
			}
		}

		private void CheckBoxInitialized(object sender, EventArgs e)
		{
			var checkBox = sender as CheckBox;
			if (checkBox != null)
			{
				var markupListViewItem = checkBox.Tag as MarkupListViewItem;
				if (markupListViewItem != null)
					checkBox.IsChecked = markupListViewItem.Checked;
			}
		}

		private void CheckBoxUnloaded(object sender, RoutedEventArgs e)
		{
		}

		public class MarkupListViewItem
		{
			public MarkupListViewItem(IMarkup markup)
			{
				Markup = markup;
			}

			public IMarkup Markup { get; private set; }

			public string Text
			{
				get
				{
					return Markup.CaptionText;
				}
				private set { }
			}

			public bool Checked
			{
				get { return Markup.IncludeInAnnotation; }
				set { Markup.IncludeInAnnotation = value; }
			}
		}
	}
}
