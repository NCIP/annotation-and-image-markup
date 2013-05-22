//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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
