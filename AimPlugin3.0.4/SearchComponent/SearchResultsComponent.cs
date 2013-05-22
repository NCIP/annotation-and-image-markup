//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	[ExtensionPoint]
	public sealed class SearchResultsComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	public interface ISearchResultsToolContext : IToolContext
	{
		ISelection Selection { get; }
		event EventHandler SelectionChanged;

		IDesktopWindow DesktopWindow { get; }
		ClickHandlerDelegate DefaultActionHandler { get; set; }
		ITableColumnCollection Columns { get; }
	}

	[AssociateView(typeof(SearchResultsComponentViewExtensionPoint))]
	public class SearchResultsComponent : ApplicationComponent
	{
		private class ToolContext : ISearchResultsToolContext
		{
			private readonly SearchResultsComponent _parent;

			public ToolContext(SearchResultsComponent parent)
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

			public IDesktopWindow DesktopWindow
			{
				get { return _parent.Host.DesktopWindow; }	
			}

			public ClickHandlerDelegate DefaultActionHandler
			{
				get { return _parent.DefaultActionHandler; }
				set { _parent.DefaultActionHandler = value; }
			}

			public ITableColumnCollection Columns
			{
				get { return _parent.Table.Columns; }
			}
		}

		private ToolSet _toolSet;
		private readonly IExtensionPoint _toolExtensionPoint;
		private readonly string _menuSite;
		private readonly string _toolbarSite;
		private readonly string _toolsNamespace;

		private ActionModelRoot _toolbarModel;
		private ActionModelRoot _menuModel;

		private readonly ITable _table;

		private string _title = "Search Results";
		private string _errorMessage;
		private ISelection _selection;
		private event EventHandler _selectionChanged;

	    private ClickHandlerDelegate _defaultActionHandler;

		internal SearchResultsComponent(string toolbarSite, string menuSite, string toolsNamespace, IExtensionPoint toolExtensionPoint, ITable table)
		{
			_toolbarSite = toolbarSite;
			_menuSite = menuSite;
			_toolsNamespace = toolsNamespace;
			_toolExtensionPoint = toolExtensionPoint;
			_table = table;
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

		public string ErrorMessage
		{
			get { return _errorMessage; }	
			set
			{
				string newValue = StringUtilities.NullIfEmpty(value == null ? null : value.Trim());
				if (_errorMessage != newValue)
				{
					_errorMessage = newValue;
					if (_errorMessage != null)
						NotifyPropertyChanged("ErrorMessage");
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

		public override void Start()
		{
			_toolSet = new ToolSet(_toolExtensionPoint, new ToolContext(this));
			_toolbarModel = ActionModelRoot.CreateModel(_toolsNamespace, _toolbarSite, _toolSet.Actions);
			_menuModel = ActionModelRoot.CreateModel(_toolsNamespace, _menuSite, _toolSet.Actions);

			base.Start();
		}

		public ITable Table
		{
			get { return _table; }
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
	}
}
