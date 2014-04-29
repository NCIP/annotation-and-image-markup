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
	[IconSet("showAnnotationList", "Icons.ShowAnnotationListToolSmall.png", "Icons.ShowAnnotationListToolMedium.png", "Icons.ShowAnnotationListToolLarge.png")]
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
				if (_shelves.ContainsKey(this.Context.DesktopWindow))
					return _shelves[this.Context.DesktopWindow];

				return null;
			}
		}

		/// <summary>
		/// Called by the framework when the user clicks the "apply" menu item or toolbar button.
		/// </summary>
		public void ShowAnnotationList()
		{
			if (this.ComponentShelf == null)
			{
				BlockingOperation.Run(delegate
					{
						try
						{
							IDesktopWindow desktopWindow = this.Context.DesktopWindow;

							IShelf shelf = AimAnnotationsListComponent.Launch(desktopWindow);
							shelf.Closed += delegate
								{
									_shelves.Remove(desktopWindow);
								};

							_shelves[this.Context.DesktopWindow] = shelf;
						}
						catch (Exception e)
						{
							ExceptionHandler.Report(e, this.Context.DesktopWindow);
						}
					});
			}
			else
			{
				this.ComponentShelf.Show();
			}
		}
	}
}
