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
using System.Security;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	[DropDownAction("toggle", NBIAExplorer.ToolbarSite + "/ToolToggleColumn", "ToggleMenuModel")]
	[IconSet("toggle", "Icons.NbiaRetrieveColumnsToolSmall.png", "Icons.NbiaRetrieveColumnsToolMedium.png", "Icons.NbiaRetrieveColumnsToolLarge.png")]

	[ExtensionOf(typeof(NBIASearchResultsToolExtensionPoint))]
	public class NbiaRetrieveColumnsTool : SearchBaseTool
	{
		private const string TOGGLE_DROPDOWN_SITE = "toggle-button-dropdown";

		private IActionSet _actions;

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public NbiaRetrieveColumnsTool()
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
				return ActionModelRoot.CreateModel(typeof(NbiaRetrieveColumnsTool).FullName, TOGGLE_DROPDOWN_SITE, this.Actions);
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
				// Let's come up with the action name
				string actionName = columnName.Replace("&", "").Replace("<", "_").Replace(">", "_").Replace("\"", "").Replace("'", "").Replace(' ', '_');
				ButtonAction buttonAction = new ButtonAction(
					string.Format("{0}:toggle_{1}", thisType.FullName, actionName),
					new ActionPath(string.Format("{0}/{1}", TOGGLE_DROPDOWN_SITE, actionName),
								   resolver), ClickActionFlags.CheckAction, resolver);
				buttonAction.Label = columnName;
				buttonAction.Checked = !SearchSettings.Default.NbiaSearchHiddenColumns.Contains(escapedColumnName);
				//			buttonAction.GroupHint = new GroupHint("SearchComponent.NbiaRetrieve.ColumnSettings");
				TableColumnBase<NBIASearchResult> column = (TableColumnBase<NBIASearchResult>)tableColumn;
				buttonAction.SetClickHandler(delegate
												{
													bool wasChecked = buttonAction.Checked;
													buttonAction.Checked = !wasChecked;
													column.Visible = !wasChecked;
													if (buttonAction.Checked)
													{
														while (SearchSettings.Default.NbiaSearchHiddenColumns.IndexOf(escapedColumnName) != -1)
															SearchSettings.Default.NbiaSearchHiddenColumns.Remove(escapedColumnName);
													}
													else
													{
														SearchSettings.Default.NbiaSearchHiddenColumns.Add(escapedColumnName);
													}
													SearchSettings.Default.Save();
												});

				actions.Add(buttonAction);
			}

			return new ActionSet(actions);
		}
	}
}
