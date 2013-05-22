//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Security;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	[DropDownAction("toggle", AIMExplorer.ToolbarSite + "/ToolToggleColumn", "ToggleMenuModel")]
	[IconSet("toggle", IconScheme.Colour, "Icons.AimRetrieveColumnsToolSmall.png", "Icons.AimRetrieveColumnsToolMedium.png", "Icons.AimRetrieveColumnsToolLarge.png")]

	[ExtensionOf(typeof(AIMSearchResultsToolExtensionPoint))]
	public class AimRetrieveColumnsTool : AIMSearchToolBase
	{
		private const string TOGGLE_DROPDOWN_SITE = "toggle-button-dropdown";

		private IActionSet _actions;

		public AimRetrieveColumnsTool()
		{
		}

		/// <summary>
		/// Called by the framework to initialize this tool.
		/// </summary>
		public override void Initialize()
		{
			base.Initialize();

			_actions = CreateActions();
		}

		public ActionModelNode ToggleMenuModel
		{
			get
			{
				return ActionModelRoot.CreateModel(typeof(AimRetrieveColumnsTool).FullName, TOGGLE_DROPDOWN_SITE, this.Actions);
			}
		}

		public override IActionSet Actions
		{
			get
			{
				return base.Actions.Union(_actions);
			}
		}

		private IActionSet CreateActions()
		{
			List<IAction> actions = new List<IAction>();
			Type thisType = this.GetType();
			IResourceResolver resolver = new ResourceResolver(thisType.Assembly);
			foreach (ITableColumn tableColumn in this.Context.Columns)
			{
				string columnName = tableColumn.Name;
				string escapedColumnName = SecurityElement.Escape(columnName);
				string actionName = columnName.Replace("&", "").Replace("<", "_").Replace(">", "_").Replace("\"", "").Replace("'", "").Replace(' ', '_');
				ButtonAction buttonAction = new ButtonAction(
					string.Format("{0}:toggle_{1}", thisType.FullName, actionName),
					new ActionPath(string.Format("{0}/{1}", TOGGLE_DROPDOWN_SITE, actionName),
					               resolver), ClickActionFlags.CheckAction, resolver);
				buttonAction.Label = columnName;
				buttonAction.Checked = !SearchSettings.Default.AimSearchHiddenColumns.Contains(escapedColumnName);
				TableColumnBase<AIMSearchResult> column = (TableColumnBase<AIMSearchResult>) tableColumn;
				buttonAction.SetClickHandler(delegate
				                             	{
				                             		bool wasChecked = buttonAction.Checked;
				                             		buttonAction.Checked = !wasChecked;
				                             		column.Visible = !wasChecked;
				                             		if (buttonAction.Checked)
				                             		{
				                             			while (SearchSettings.Default.AimSearchHiddenColumns.IndexOf(escapedColumnName) != -1)
				                             				SearchSettings.Default.AimSearchHiddenColumns.Remove(escapedColumnName);
				                             		}
				                             		else
				                             		{
				                             			SearchSettings.Default.AimSearchHiddenColumns.Add(escapedColumnName);
				                             		}
				                             		SearchSettings.Default.Save();
				                             	});

				actions.Add(buttonAction);
			}

			return new ActionSet(actions);
		}
	}
}
