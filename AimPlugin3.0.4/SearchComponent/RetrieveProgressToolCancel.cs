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
	[MenuAction("cancel",  RetrieveProgressComponent.MenuSite + "/RetrieveProgressToolCancel", "Cancel")]
	[ButtonAction("cancel", RetrieveProgressComponent.ToolbarSite + "/RetrieveProgressToolCancel", "Cancel")]
	[Tooltip("cancel", "Cancel Retrieve")]
	[IconSet("cancel", IconScheme.Colour, "Icons.RetrieveProgressToolCancelSmall.png", "Icons.RetrieveProgressToolCancelMedium.png", "Icons.RetrieveProgressToolCancelLarge.png")]

	[EnabledStateObserver("cancel", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(RetrieveProgressToolExtensionPoint))]
	public class RetrieveProgressToolCancel : RetrieveProgressToolBase
	{
		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public RetrieveProgressToolCancel()
		{
		}

		/// <summary>
		/// Called by the framework to initialize this tool.
		/// </summary>
		public override void Initialize()
		{
			base.Initialize();

			Context.ItemsChanged += OnItemsChanged;
		}

		private void OnItemsChanged(object sender, ItemChangedEventArgs e)
		{
			if (e.ChangeType == ItemChangeType.ItemChanged)
				this.UpdateEnabled();
		}

		protected override void OnSelectedItemChanged(object sender, EventArgs e)
		{
			this.UpdateEnabled();
		}

		private void UpdateEnabled()
		{
			this.Enabled = this.Context.Selection != null && this.Context.Selection.Item != null &&
			               CollectionUtils.Contains<RetrieveProgressResult>(this.Context.Selection.Items,
			                                                                delegate(RetrieveProgressResult result)
			                                                                	{
			                                                                		return result.Status == RetrieveStatus.InProgress || result.Status == RetrieveStatus.Queued;
			                                                                	});
		}

		/// <summary>
		/// Called by the framework when the user clicks the "cancel" menu item or toolbar button.
		/// </summary>
		public void Cancel()
		{
			if (this.Context.Selection == null || this.Context.Selection.Item == null)
				return;

			CollectionUtils.ForEach<RetrieveProgressResult>(this.Context.Selection.Items, CancelRetrieve);
		}

		private void CancelRetrieve(RetrieveProgressResult result)
		{
			if (result.Status == RetrieveStatus.InProgress || result.Status == RetrieveStatus.Queued)
			{
				RetrieveCoordinator.Coordinator.CancelRetrieve(result);
			}
		}
	}
}
