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

namespace SearchComponent
{
	[MenuAction("cancel",  RetrieveProgressComponent.MenuSite + "/RetrieveProgressToolCancel", "Cancel")]
	[ButtonAction("cancel", RetrieveProgressComponent.ToolbarSite + "/RetrieveProgressToolCancel", "Cancel")]
	[Tooltip("cancel", "Cancel Retrieve")]
	[IconSet("cancel", "Icons.RetrieveProgressToolCancelSmall.png", "Icons.RetrieveProgressToolCancelMedium.png", "Icons.RetrieveProgressToolCancelLarge.png")]

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
			// Enable when there is one or more selected items and at least one of the items is being retrieved
			this.Enabled = this.Context.Selection != null && this.Context.Selection.Item != null &&
						   CollectionUtils.Contains(this.Context.Selection.Items,
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
