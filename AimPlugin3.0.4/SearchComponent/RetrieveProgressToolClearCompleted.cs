#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;

namespace SearchComponent
{
	[MenuAction("clear",  RetrieveProgressComponent.MenuSite + "/RetrieveProgressToolClearCompleted", "ClearCompleted")]
	[ButtonAction("clear", RetrieveProgressComponent.ToolbarSite + "/RetrieveProgressToolClearCompleted", "ClearCompleted")]
	[Tooltip("clear", "Clear Completed Studies")]
	[IconSet("clear", IconScheme.Colour, "Icons.RetrieveProgressToolClearCompletedSmall.png", "Icons.RetrieveProgressToolClearCompletedMedium.png", "Icons.RetrieveProgressToolClearCompletedLarge.png")]

	[EnabledStateObserver("clear", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(RetrieveProgressToolExtensionPoint))]
	public class RetrieveProgressToolClearCompleted : RetrieveProgressToolBase
	{
		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public RetrieveProgressToolClearCompleted()
		{
		}

		/// <summary>
		/// Called by the framework to initialize this tool.
		/// </summary>
		public override void Initialize()
		{
			base.Initialize();

			this.Enabled = false;
			Context.ItemsChanged += OnItemsChanged;
		}

		protected void OnItemsChanged(object sender, ItemChangedEventArgs e)
		{
			if (e.ChangeType != ItemChangeType.ItemChanged)
				this.Enabled = CollectionUtils.Contains<RetrieveProgressResult>(this.Context.Items, delegate(RetrieveProgressResult result)
					{
						return result.Status == RetrieveStatus.Error ||
						       result.Status == RetrieveStatus.Completed ||
						       result.Status == RetrieveStatus.Canceled;
					});
		}

		protected override void OnSelectedItemChanged(object sender, EventArgs e)
		{
		}

		/// <summary>
		/// Called by the framework when the user clicks the "cancel" menu item or toolbar button.
		/// </summary>
		public void ClearCompleted()
		{
			bool checkNext;
			do
			{
				checkNext = false;
				foreach (RetrieveProgressResult result in Context.Items)
				{
					if (result.Status != RetrieveStatus.Queued && result.Status != RetrieveStatus.InProgress && result.Status != RetrieveStatus.CancelRequested)
					{
						RetrieveCoordinator.Coordinator.RemoveResult(result);
						checkNext = true;
						break;
					}
				}
				
			} while (checkNext);
		}

		private void ClearCompletedResult(RetrieveProgressResult result)
		{
			if (result.Status != RetrieveStatus.Queued || result.Status != RetrieveStatus.InProgress)
			{
				RetrieveCoordinator.Coordinator.RemoveResult(result);
			}
		}
	}
}
