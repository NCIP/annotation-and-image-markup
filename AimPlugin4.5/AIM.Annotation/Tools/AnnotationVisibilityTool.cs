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
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;
using ClearCanvas.ImageViewer.Graphics;

using AIM.Annotation.Configuration;
using AIM.Annotation.Graphics;

namespace AIM.Annotation.Tools
{
	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class AnnotationVisibilityTool : ImageViewerTool
	{
		private readonly Dictionary<string, bool> _displayMarkupPerUser = new Dictionary<string, bool>();

		public AnnotationVisibilityTool() { }

		public override void Initialize()
		{
			base.Initialize();

			this.Context.Viewer.EventBroker.ImageDrawing += OnImageDrawing;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				this.Context.Viewer.EventBroker.ImageDrawing -= OnImageDrawing;
			}
			base.Dispose(disposing);
		}

		private void OnImageDrawing(object sender, ImageDrawingEventArgs e)
		{
			if (e.PresentationImage != null)
			{
				IOverlayGraphicsProvider graphicsProvider = e.PresentationImage as IOverlayGraphicsProvider;
				if (graphicsProvider != null && graphicsProvider.OverlayGraphics != null)
				{
					AimSettings aimSettings = AimSettings.Default;
					foreach (IGraphic overlayGraphic in graphicsProvider.OverlayGraphics)
					{
						if (overlayGraphic is AimGraphic)
						{
							AimGraphic aimGraphic = (AimGraphic) overlayGraphic;
							string userName = aimGraphic.UserLoginName;
							aimGraphic.Visible = !_displayMarkupPerUser.ContainsKey(userName) || _displayMarkupPerUser[userName];
							aimGraphic.Color = aimSettings.GetAimGraphicColorForUser(userName);
						}
					}
				}
			}
		}

		private Dictionary<String, List<AimGraphic>> GetAimUserGraphics()
		{
			Dictionary<String, List<AimGraphic>> userGraphics = new Dictionary<string, List<AimGraphic>>();
			foreach (ImageBox imageBox in Context.Viewer.PhysicalWorkspace.ImageBoxes)
			{
				foreach (Tile tile in imageBox.Tiles)
				{
					IOverlayGraphicsProvider graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
					if (graphicsProvider != null)
					{
						foreach (IGraphic graphic in graphicsProvider.OverlayGraphics)
						{
							AimGraphic aimGraphic = graphic as AimGraphic;
							if (aimGraphic != null)
							{
								string user = aimGraphic.UserLoginName;
								if (!userGraphics.ContainsKey(user))
									userGraphics.Add(user, new List<AimGraphic>());
								userGraphics[user].Add(aimGraphic);
							}
						}
					}
				}
			}
			return userGraphics;
		}

		public override IActionSet Actions { get { return base.Actions.Union(GetContextMenuActionSet()); } }

		private IActionSet GetContextMenuActionSet()
		{
			Dictionary<String, List<AimGraphic>> aimUserGraphics = GetAimUserGraphics();
			List<IAction> actionsList = new List<IAction>();
			String path = "imageviewer-contextmenu/Visible AIM Users/";
			ResourceResolver resolver = new ResourceResolver(GetType(), true);
			foreach (String aimUser in aimUserGraphics.Keys)
			{
				if (aimUserGraphics.Count > 0)
				{
					string user = aimUser;
					MenuAction action = new MenuAction(aimUser, new ActionPath(path + aimUser, resolver), ClickActionFlags.CheckAction, resolver);
					action.Checked = aimUserGraphics[aimUser][0].Visible;
					action.Enabled = true;
					action.Persistent = false;
					action.Label = aimUser;
					actionsList.Add(action);
					action.SetClickHandler(
						delegate
						{
							bool visible = !action.Checked;
							_displayMarkupPerUser[user] = visible;
							action.Checked = visible;
							this.SelectedPresentationImage.Draw();
						});
				}
			}
			return new ActionSet(actionsList);
		}
	}
}
