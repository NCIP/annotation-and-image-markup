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
using AIM.Annotation.Graphics;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.RoiGraphics;

namespace AIM.Annotation.AimManager
{
	// ====================================================================
	//
	//  Annotation creation and manipulation helpers
	//
	// ====================================================================

	internal static class AimHelpers
	{
		public static bool IsImageMarkupPresent(IPresentationImage image)
		{
			IOverlayGraphicsProvider currentOverlayGraphics = image as IOverlayGraphicsProvider;
			if (currentOverlayGraphics != null)
			{
				foreach (IGraphic graphic in currentOverlayGraphics.OverlayGraphics)
				{
					if (graphic is RoiGraphic)
						return true;

					ContextMenuControlGraphic contextMenuControlGraphic = graphic as ContextMenuControlGraphic;
					if (contextMenuControlGraphic != null && contextMenuControlGraphic.Subject != null)
					{
						UserCalloutGraphic userCalloutGraphic = contextMenuControlGraphic.Subject as UserCalloutGraphic;
						if (userCalloutGraphic != null)
							return true;

						InvariantTextPrimitive invariantTextPrimitive = contextMenuControlGraphic.Subject as InvariantTextPrimitive;
						if (invariantTextPrimitive != null)
							return true;

						UserCrosshairCalloutGraphic crosshairGraphic = contextMenuControlGraphic.Subject as UserCrosshairCalloutGraphic;
						if (crosshairGraphic != null)
							return true;
					}
				}
			}
			return false;
		}

		internal static string FormatPointCalloutText(string annotationName, string calloutText)
		{
			return string.IsNullOrEmpty(annotationName) ? calloutText : string.Format("{0}{1}{2}", annotationName, Environment.NewLine, calloutText);
		}
	}
}
