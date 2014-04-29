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
using System.Linq;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;
using ClearCanvas.ImageViewer.StudyManagement;

namespace AIM.Annotation
{
	[MenuAction("show", "global-menus/MenuAnnotation/AIMAnnotationMenu", "Show")]
	[ButtonAction("show", BUTTON_ACTION_PATH, "Show")]
	[Tooltip("show", "AIMAnnotationTooltip")]
	[IconSet("show", "Icons.AIMAnnotationToolSmall.png", "Icons.AIMAnnotationToolMedium.png", "Icons.AIMAnnotationToolLarge.png")]

	[EnabledStateObserver("show", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class AimAnnotationTool : ImageViewerTool
	{
		private const string BUTTON_ACTION_PATH = "global-toolbars/ToolbarStandard/AIMAnnotationButton";

		// List of created shelves
		private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();
		private IDesktopWindow _desktopWindow;

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		public AimAnnotationTool()
		{
			_desktopWindow = null;
		}

		/// <summary>
		/// Called by the framework to initialize this tool.
		/// </summary>
		public override void Initialize()
		{
			base.Initialize();

			this.ImageViewer.EventBroker.DisplaySetChanged += OnDisplaySetChanged;
		}

		/// <summary>
		/// Called when the tool is disposed.
		/// </summary>
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				// TODO - Auto-save new annotations here?

				this.ImageViewer.EventBroker.DisplaySetChanged -= OnDisplaySetChanged;
			}

			base.Dispose(disposing);
		}

		public static bool StartAimAnnotationTool(IImageViewer currentImageViewer)
		{
			if (currentImageViewer == null)
				return false;

			var actionPath = new ActionPath(BUTTON_ACTION_PATH, new ResourceResolver(typeof(AimAnnotationTool), true));
			IActionSet actionSet = currentImageViewer.ExportedActions.Select(action => action.Path.LocalizedPath == actionPath.LocalizedPath);
			if (actionSet != null)
			{
				foreach (IAction action in actionSet)
				{
					ClickAction clickAction = action as ClickAction;
					if (clickAction != null)
					{
						clickAction.Click();
						return true;
					}
				}
			}

			return false;
		}

		public void Show()
		{
			// check if a layout component is already displayed
			if (_shelves.ContainsKey(this.Context.DesktopWindow))
			{
				_shelves[this.Context.DesktopWindow].Activate();
			}
			else
			{
				BlockingOperation.Run(delegate
										{
											_desktopWindow = this.Context.DesktopWindow;

											AimAnnotationComponent aimComponent = AimAnnotationComponent.Create(Context.DesktopWindow, false);

											IShelf shelf = ApplicationComponent.LaunchAsShelf(
												_desktopWindow,
												aimComponent,
												SR.TitleAIMCreater,
												"AIM Annotation",
												ShelfDisplayHint.DockRight | ShelfDisplayHint.DockAutoHide);

											shelf.Closed += OnShelfClosed;
											_shelves[_desktopWindow] = shelf;
										});
			}
		}

		private void OnShelfClosed(object sender, ClosedEventArgs e)
		{
			// We need to cache the owner DesktopWindow (_desktopWindow) because this tool is an 
			// ImageViewer tool, disposed when the viewer component is disposed.  Shelves, however,
			// exist at the DesktopWindow level and there can only be one of each type of shelf
			// open at the same time per DesktopWindow (otherwise things look funny).  Because of 
			// this, we need to allow this event handling method to be called after this tool has
			// already been disposed (e.g. viewer workspace closed), which is why we store the 
			// _desktopWindow variable.

			_shelves[_desktopWindow].Closed -= OnShelfClosed;
			_shelves.Remove(_desktopWindow);
			_desktopWindow = null;
		}

		private void OnDisplaySetChanged(object sender, DisplaySetChangedEventArgs e)
		{
			Console.WriteLine("OnDisplaySetChanged");

			// TODO - add/remove DisplaySet.PresentationImages.ItemAdded event handlers

			if (e.NewDisplaySet != null && e.NewDisplaySet.Visible)
			{
				Dictionary<string, int> uidCnt = new Dictionary<string, int>();
				foreach (var imageSopPrivider in e.NewDisplaySet.PresentationImages.OfType<IImageSopProvider>().Where(imageSopPrivider => imageSopPrivider != null))
				{
					if (imageSopPrivider != null)
					{
						string studyInstanceUID = imageSopPrivider.ImageSop.StudyInstanceUid;
						if (uidCnt.ContainsKey(studyInstanceUID))
							uidCnt[studyInstanceUID] += 1;
						else
							uidCnt[studyInstanceUID] = 1;
					}
				}

				// 1. Init annotation objects
				var aimAnnotations = new List<AimManager.IAimDocumentInstance>();
				foreach (string studyInstanceUid in uidCnt.Keys)
				{
					var studyAnnotations = AimManager.AimManager.Instance.LoadLocalAnnotationsForStudy(studyInstanceUid);
					if (studyAnnotations != null)
						aimAnnotations.AddRange(studyAnnotations);
				}

				// 2. put markup on the images
				foreach (var annotation in aimAnnotations)
				{
					foreach (IPresentationImage img in e.NewDisplaySet.PresentationImages)
					{
						AimManager.AimManager.Instance.ReadGraphicsFromAnnotation(annotation, img);
					}
				}
			}
		}
	}
}
