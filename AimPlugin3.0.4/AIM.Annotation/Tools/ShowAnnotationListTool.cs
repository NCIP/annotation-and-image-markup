//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;

namespace AIM.Annotation.Tools
{
	[MenuAction("showAnnotationList", "global-menus/MenuAnnotation/ShowAnnotationListMenu", "ShowAnnotationList")]
	[ButtonAction("showAnnotationList", "global-toolbars/ToolbarMyTools/ShowAnnotationListButton", "ShowAnnotationList")]
	[KeyboardAction("showAnnotationList", "imageviewer-keyboard/ShowAnnotationListTool", "ShowAnnotationList", KeyStroke = XKeys.Alt | XKeys.H)]
	[Tooltip("showAnnotationList", "TooltipShowAnnotationList")]
	[IconSet("showAnnotationList", IconScheme.Colour, "Icons.ShowAnnotationListToolSmall.png", "Icons.ShowAnnotationListToolMedium.png", "Icons.ShowAnnotationListToolLarge.png")]
	[EnabledStateObserver("showAnnotationList", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class ShowAnnotationListTool : ImageViewerTool
	{
		private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public ShowAnnotationListTool()
		{
		}

		private IShelf ComponentShelf
		{
			get
			{
				if (_shelves.ContainsKey(Context.DesktopWindow))
					return _shelves[Context.DesktopWindow];

				return null;
			}
		}

		/// <summary>
		/// Called by the framework when the user clicks the "apply" menu item or toolbar button.
		/// </summary>
		public void ShowAnnotationList()
		{
			if (ComponentShelf == null)
			{
				try
				{
					IDesktopWindow desktopWindow = this.Context.DesktopWindow;

					IShelf shelf = AimAnnotationsListComponent.Launch(desktopWindow);
					shelf.Closed += delegate
					{
						_shelves.Remove(desktopWindow);
					};

					_shelves[Context.DesktopWindow] = shelf;
				}
				catch (Exception e)
				{
					ExceptionHandler.Report(e, Context.DesktopWindow);
				}
			}
			else
			{
				ComponentShelf.Show();
			}
		}
	}
}
