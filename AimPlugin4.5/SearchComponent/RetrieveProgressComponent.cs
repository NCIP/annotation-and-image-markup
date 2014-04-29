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

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tables;
using ClearCanvas.Desktop.Tools;

namespace SearchComponent
{
	/// <summary>
	/// Extension point for views onto <see cref="RetrieveProgressComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class RetrieveProgressComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	public class RetrieveProgressToolExtensionPoint : ExtensionPoint<ITool>
	{
	}

	public interface IRetrieveProgressToolContext : IToolContext
	{
		ISelection Selection { get; }
		event EventHandler SelectionChanged;

		event EventHandler<ItemChangedEventArgs> ItemsChanged;
		IItemCollection Items { get; }

		IDesktopWindow DesktopWindow { get; }
		ClickHandlerDelegate DefaultActionHandler { get; set; }
	}

	/// <summary>
	/// RetrieveProgressComponent class.
	/// </summary>
	[AssociateView(typeof(RetrieveProgressComponentViewExtensionPoint))]
	public class RetrieveProgressComponent : ApplicationComponent
	{
		public const string MenuSite = "cagrid-retrieve-contextmenu";
		public const string ToolbarSite = "cagrid-retrieve-toolbar";
		internal static readonly string ToolNamespace = typeof(RetrieveProgressComponent).FullName;

		private class ToolContext : IRetrieveProgressToolContext
		{
			private readonly RetrieveProgressComponent _parent;

			public ToolContext(RetrieveProgressComponent parent)
			{
				_parent = parent;
			}

			public ISelection Selection
			{
				get { return _parent.Selection; }
			}

			public event EventHandler SelectionChanged
			{
				add { _parent.SelectionChanged += value; }
				remove { _parent.SelectionChanged -= value; }
			}

			public event EventHandler<ItemChangedEventArgs> ItemsChanged
			{
				add { _parent.ItemsChanged += value; }
				remove { _parent.ItemsChanged -= value; }
			}

			public IItemCollection Items
			{
				get { return _parent.Table.Items; }
			}

			public IDesktopWindow DesktopWindow
			{
				get { return _parent.Host.DesktopWindow; }
			}

			public ClickHandlerDelegate DefaultActionHandler
			{
				get { return _parent.DefaultActionHandler; }
				set { _parent.DefaultActionHandler = value; }
			}
		}

		private ToolSet _toolSet;
		private readonly IExtensionPoint _toolExtensionPoint;
		private readonly string _menuSite;
		private readonly string _toolbarSite;
		private readonly string _toolsNamespace;

		private ActionModelRoot _toolbarModel;
		private ActionModelRoot _menuModel;

//		private readonly ITable _table;

		private string _title = "Study Retrieve Progress";
		private ISelection _selection;
		private event EventHandler _selectionChanged;

	    private ClickHandlerDelegate _defaultActionHandler;

		internal RetrieveProgressComponent(string toolbarSite, string menuSite, string toolsNamespace, IExtensionPoint toolExtensionPoint, ITable table)
		{
			_toolbarSite = toolbarSite;
			_menuSite = menuSite;
			_toolsNamespace = toolsNamespace;
			_toolExtensionPoint = toolExtensionPoint;
	//		_table = table;
		}

		public ActionModelNode ToolbarModel
		{
			get { return _toolbarModel;}
		}

		public ActionModelNode MenuModel
		{
			get { return _menuModel;}
		}

		public string Title
		{
			get { return _title; }	
			set
			{
				if (_title != value)
				{
					_title = value;
					NotifyPropertyChanged("Title");
				}
			}
		}

		public ISelection Selection
		{
			get { return _selection; }
		}

		public event EventHandler SelectionChanged
		{
			add { _selectionChanged += value; }
			remove { _selectionChanged -= value; }
		}

		public event EventHandler<ItemChangedEventArgs> ItemsChanged
		{
			add { Table.Items.ItemsChanged += value; }
			remove { Table.Items.ItemsChanged -= value; }
		}

		public override void Start()
		{
			_toolSet = new ToolSet(_toolExtensionPoint, new ToolContext(this));
			_toolbarModel = ActionModelRoot.CreateModel(_toolsNamespace, _toolbarSite, _toolSet.Actions);
			_menuModel = ActionModelRoot.CreateModel(_toolsNamespace, _menuSite, _toolSet.Actions);

			base.Start();
		}

		public ITable Table
		{
			get { return RetrieveCoordinator.Coordinator.Table; }
		}

		internal ClickHandlerDelegate DefaultActionHandler
		{
			get { return _defaultActionHandler; }
			set { _defaultActionHandler += value; }
		}

		public void SetSelection(ISelection selection)
		{
			if (selection == null)
				selection = new Selection();

			if (!Equals(_selection, selection))
			{
				_selection = selection;
				EventsHelper.Fire(_selectionChanged, this, EventArgs.Empty);
			}
		}

		public void ItemDoubleClick()
		{
			if (DefaultActionHandler != null)
				DefaultActionHandler();
		}

		public override bool CanExit()
		{
			if (!base.CanExit())
				return false;

			bool retrieveInProgress = CollectionUtils.Contains<RetrieveProgressResult>
				(RetrieveCoordinator.Coordinator.Table.Items, delegate(RetrieveProgressResult result)
				{
					return result.Status == RetrieveStatus.InProgress ||
						   result.Status == RetrieveStatus.Queued;
				});

			return retrieveInProgress
					? this.Host.DesktopWindow.ShowMessageBox("You are retrieving one or more studies from the caGrid. Abandon retrieve and exist?",
															 MessageBoxActions.YesNo) == DialogBoxAction.Yes
					: true;
		}
	}
}
