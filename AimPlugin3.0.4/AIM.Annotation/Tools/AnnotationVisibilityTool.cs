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

        public AnnotationVisibilityTool() {  }

		public override void Initialize()
		{
			base.Initialize();
			Context.Viewer.EventBroker.ImageDrawing += OnImageDrawing;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
				Context.Viewer.EventBroker.ImageDrawing -= OnImageDrawing;
			base.Dispose(disposing);
		}

		private void OnImageDrawing(object sender, ImageDrawingEventArgs e)
		{
			if (e.PresentationImage != null)
			{
				var graphicsProvider = e.PresentationImage as IOverlayGraphicsProvider;
				if (graphicsProvider != null && graphicsProvider.OverlayGraphics != null)
				{
					var aimSettings = AimSettings.Default;
					foreach (var overlayGraphic in graphicsProvider.OverlayGraphics)
					{
						if (overlayGraphic is AimGraphic)
						{
							var aimGraphic = (AimGraphic) overlayGraphic;
							var userName = aimGraphic.UserLoginName;
							aimGraphic.Visible = !_displayMarkupPerUser.ContainsKey(userName) || _displayMarkupPerUser[userName];
							aimGraphic.Color = aimSettings.GetAimGraphicColorForUser(userName);
						}
					}
				}
			}
		}

        private Dictionary<String, List<AimGraphic>> GetAimUserGraphics()
        {
            var userGraphics = new Dictionary<string, List<AimGraphic>>();
            foreach (ImageBox imageBox in Context.Viewer.PhysicalWorkspace.ImageBoxes)
            {
                foreach (Tile tile in imageBox.Tiles)
                {
                    var graphicsProvider = tile.PresentationImage as IOverlayGraphicsProvider;
                    if (graphicsProvider != null)
                    {
                        foreach (var graphic in graphicsProvider.OverlayGraphics)
                        {
                            var aimGraphic = graphic as AimGraphic;
                            if (aimGraphic != null)
                            {
                                var user = aimGraphic.UserLoginName;
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
            var aimUserGraphics = GetAimUserGraphics();
            var actionsList = new List<IAction>();
            const string path = "imageviewer-contextmenu/Visible AIM Users/";
            var resolver = new ResourceResolver(GetType(), true);
            foreach (var aimUser in aimUserGraphics.Keys)
            {
                if (aimUserGraphics.Count > 0)
                {
                    var user = aimUser;
                    var action = new MenuAction(aimUser, new ActionPath(path + aimUser, resolver), ClickActionFlags.CheckAction, resolver);
                    action.Checked = aimUserGraphics[aimUser][0].Visible;
                    action.Enabled = true;
                    action.Persistent = false;
                    action.Label = aimUser;
                    actionsList.Add(action);
                    action.SetClickHandler(
                        delegate
                        {
                        	var visible = !action.Checked;
                        	_displayMarkupPerUser[user] = visible;
                            action.Checked = visible;
                        	SelectedPresentationImage.Draw();
                        });
                }
            }
            return new ActionSet(actionsList);
        }
    }
}
