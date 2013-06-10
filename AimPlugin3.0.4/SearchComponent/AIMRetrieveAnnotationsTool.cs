#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer.Services.LocalDataStore;

namespace SearchComponent
{
	[MenuAction("apply", AIMExplorer.ToolbarSite + "/MenuRetrieveAnnotation", "Apply")]
	[ButtonAction("apply", AIMExplorer.MenuSite + "/ToolRetrieveAnnotation", "Apply")]
	[Tooltip("apply", "Retrieve Selected Annotation")]
	[IconSet("apply", IconScheme.Colour, "Icons.AIMRetrieveToolSmall.png", "Icons.AIMRetrieveToolMedium.png", "Icons.AIMRetrieveToolLarge.png")]
	[GroupHint("apply", "Tool.SearchComponent.AimRetrieve.Retrieve")]

	[EnabledStateObserver("apply", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(AIMSearchResultsToolExtensionPoint))]
	public class AIMRetrieveAnnotationsTool : AIMSearchToolBase
	{
		public AIMRetrieveAnnotationsTool()
		{
		}

		public void Apply()
		{
			ISelection selection = base.Context.Selection;
			if (selection == null || selection.Item == null)
				return;

			if (!LocalDataStoreActivityMonitor.IsConnected)
			{
				this.Context.DesktopWindow.ShowMessageBox(
					"Failed to save annotation. Not connected to the local data store. Is workstation service running?", MessageBoxActions.Ok);
				return;
			}

			this.RetrieveAnnotationsFromAimService(selection.Items);
		}
	}
}
