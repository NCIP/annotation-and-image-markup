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

using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.RoiGraphics;
using AIM.Annotation.Configuration;

namespace AIM.Annotation.Graphics
{
	public class AimRoiGraphic : RoiGraphic
	{
		private static AimRoiGraphic _selectedAimRoiGraphic = null;

		public AimRoiGraphic(IGraphic roi) : base(roi) { }
		public AimRoiGraphic(IGraphic roi, IAnnotationCalloutLocationStrategy strategy) : base(roi, strategy) { }

		public static AimRoiGraphic SelectedAimRoiGraphic
		{
			get
			{
				return _selectedAimRoiGraphic;
			}
		}

		public override IActionSet GetExportedActions(string site, ClearCanvas.ImageViewer.InputManagement.IMouseInformation mouseInformation)
		{
			IResourceResolver resolver = new ResourceResolver(this.GetType(), true);
			string @namespace = this.GetType().FullName;

			MenuAction hideAction = new MenuAction(@namespace + ":toggle", new ActionPath(site + "/MenuSetMarkupColorForUser", resolver), ClickActionFlags.None, resolver);
			//hideAction.GroupHint = new GroupHint("Tools.Measurements.Display");
			hideAction.Label = "Set User Markup Color";
			hideAction.Persistent = true;
			hideAction.SetClickHandler(OpenAimMarkupColorOptions);

			IActionSet actions = new ActionSet(new IAction[] { hideAction });
			IActionSet other = base.GetExportedActions(site, mouseInformation);
			if (other != null)
				actions = actions.Union(other);

			return actions;
		}

		protected override ICalloutGraphic CreateCalloutGraphic()
		{
			return new AimRoiCalloutGraphic();
		}

		public string UserLoginName
		{
			get
			{
				var aimGraphic = this.ParentGraphic as AimGraphic;
				return aimGraphic == null ? null : aimGraphic.UserLoginName;
			}
		}

		private void OpenAimMarkupColorOptions()
		{
			_selectedAimRoiGraphic = this;
			ClearCanvas.Desktop.Configuration.ConfigurationDialog.Show(this.ImageViewer.DesktopWindow, AimMarkupColorComponent.Path);
			_selectedAimRoiGraphic = null;
		}

		/// <summary>
		/// Convenience method to create a common elliptical, interactive region of interest.
		/// </summary>
		/// <returns>A new interactive region of interest graphic.</returns>
		public static AimRoiGraphic CreateEllipse()
		{
			AimRoiGraphic roiGraphic = new AimRoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(new MoveControlGraphic(new EllipsePrimitive()))));
			roiGraphic.State = roiGraphic.CreateInactiveState();
			return roiGraphic;
		}

		/// <summary>
		/// Convenience method to create a common rectangular, interactive region of interest.
		/// </summary>
		/// <returns>A new interactive region of interest graphic.</returns>
		public static AimRoiGraphic CreateRectangle()
		{
			AimRoiGraphic roiGraphic = new AimRoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(new MoveControlGraphic(new RectanglePrimitive()))));
			roiGraphic.State = roiGraphic.CreateInactiveState();
			return roiGraphic;
		}

		/// <summary>
		/// Convenience method to create a common polygonal, interactive region of interest.
		/// </summary>
		/// <returns>A new interactive region of interest graphic.</returns>
		public static AimRoiGraphic CreatePolygon()
		{
			AimRoiGraphic roiGraphic = new AimRoiGraphic(new PolygonControlGraphic(true, new MoveControlGraphic(new PolylineGraphic(true))));
			roiGraphic.State = roiGraphic.CreateInactiveState();
			return roiGraphic;
		}
	}
}
