#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;

namespace AIM.Annotation.Tools
{
	[MenuAction("apply", "global-menus/MenuAnnotation/ShowAnnotationDetailsMenu", "Apply")]
	[ButtonAction("apply", "global-toolbars/ToolbarMyTools/ShowAnnotationDetailsButton", "Apply")]
	[KeyboardAction("apply", "imageviewer-keyboard/ShowAnnotationDetailsTool", "Apply", KeyStroke = XKeys.Alt | XKeys.U)]
	[Tooltip("apply", "TooltipShowAnnotationDetails")]
	[IconSet("apply", IconScheme.Colour, "Icons.ShowAnnotationDetailsToolSmall.png", "Icons.ShowAnnotationDetailsToolMedium.png", "Icons.ShowAnnotationDetailsToolLarge.png")]
	[EnabledStateObserver("apply", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class ShowAnnotationDetailsTool : ImageViewerTool
	{
		private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public ShowAnnotationDetailsTool()
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
		public void Apply()
		{
			if (ComponentShelf == null)
			{
				try
				{
					IDesktopWindow desktopWindow = this.Context.DesktopWindow;

					IShelf shelf = AimAnnotationDetailsComponent.Launch(desktopWindow);
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
