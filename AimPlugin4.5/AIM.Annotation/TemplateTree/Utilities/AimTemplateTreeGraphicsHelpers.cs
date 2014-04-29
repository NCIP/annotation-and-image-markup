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
using System.Drawing;
using System.Linq;
using AIM.Annotation.Graphics;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.Graphics;

namespace AIM.Annotation.TemplateTree.Utilities
{
	internal static class AimTemplateTreeGraphicsHelpers
	{
		internal static List<IGraphic> PopulateImageViewerWithSavedMarkup(List<IMarkup> markupList, IImageViewer imageViewer)
		{
			var graphics = new List<IGraphic>();
			foreach (var markup in markupList)
			{
				foreach (var box in imageViewer.PhysicalWorkspace.ImageBoxes)
				{
					if (box.DisplaySet == null)
						continue;

					var imageSop =
						box.DisplaySet.PresentationImages.Cast<IImageSopProvider>().FirstOrDefault(
						pi => pi.ImageSop.SopInstanceUid == markup.PresentationImageUid && pi.Frame.FrameNumber == markup.FrameNumber);

					var selectedPresentationImage = imageSop as IPresentationImage;
					if (selectedPresentationImage == null)
						continue;

					var graphicsProvider = selectedPresentationImage as IOverlayGraphicsProvider;
					if (graphicsProvider != null)
					{
						if (markup is MarkupEllipse)
						{
							var markupEllipse = (MarkupEllipse)markup;
							var ellipsePrimitive = new EllipsePrimitive();
							var roiGraphic = new RoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(
								new MoveControlGraphic(ellipsePrimitive))));
							var boundableGraphic = roiGraphic.Subject as BoundableGraphic;

							markup.GraphicHashcode = roiGraphic.GetHashCode();
							graphics.Add(roiGraphic);
							graphicsProvider.OverlayGraphics.Add(roiGraphic);

							if (boundableGraphic != null)
							{
								roiGraphic.Suspend(); // prevent callout location calculation until all points are set
								roiGraphic.Name = markup.Name;
								ellipsePrimitive.BottomRight = markupEllipse.BottomRight;
								ellipsePrimitive.TopLeft = markupEllipse.TopLeft;
								roiGraphic.State = roiGraphic.CreateInactiveState();
								roiGraphic.Resume(true); // Force callout location calculation
								roiGraphic.Callout.TextLocation = markupEllipse.CalloutLocation;
							}
						}
						else if (markup is MarkupPolygonal)
						{
							var markupPolygon = (MarkupPolygonal)markup;

							var polyline = new PolylineGraphic(true);
							foreach (var point in markupPolygon.Vertices)
								polyline.Points.Add(point);
							var roiGraphic = new RoiGraphic(new PolygonControlGraphic(true, new MoveControlGraphic(polyline)));

							markup.GraphicHashcode = roiGraphic.GetHashCode();
							graphics.Add(roiGraphic);
							graphicsProvider.OverlayGraphics.Add(roiGraphic);

							//if (boundableGraphic != null)
							{
								roiGraphic.Suspend(); // prevent callout location calculation until all points are set
								roiGraphic.Name = markup.Name;
								roiGraphic.State = roiGraphic.CreateInactiveState();
								roiGraphic.Resume(true); // Force callout location calculation
								roiGraphic.Callout.TextLocation = markupPolygon.CalloutLocation;
							}
						}
						else if (markup is MarkupRectangle)
						{
							var markupRectangle = (MarkupRectangle)markup;
							var rectanglePrimitive = new RectanglePrimitive();
							var roiGraphic = new RoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(
								new MoveControlGraphic(rectanglePrimitive))));
							var boundableGraphic = roiGraphic.Subject as BoundableGraphic;

							markup.GraphicHashcode = roiGraphic.GetHashCode();
							graphics.Add(roiGraphic);
							graphicsProvider.OverlayGraphics.Add(roiGraphic);

							if (boundableGraphic != null)
							{
								roiGraphic.Suspend(); // prevent callout location calculation until all points are set
								roiGraphic.Name = markup.Name;
								rectanglePrimitive.BottomRight = markupRectangle.BottomRight;
								rectanglePrimitive.TopLeft = markupRectangle.TopLeft;
								roiGraphic.State = roiGraphic.CreateInactiveState();
								roiGraphic.Resume(true); // Force callout location calculation
								roiGraphic.Callout.TextLocation = markupRectangle.CalloutLocation;
							}
						}
						else if (markup is MarkupProtractor)
						{
							var markupProtractor = (MarkupProtractor)markup;

							var protractorGraphic = new ProtractorGraphic();
							foreach (var point in markupProtractor.Points)
								protractorGraphic.Points.Add(point);
							var roiGraphic = new RoiGraphic(new VerticesControlGraphic(new MoveControlGraphic(protractorGraphic)));

							markup.GraphicHashcode = roiGraphic.GetHashCode();
							graphics.Add(roiGraphic);
							graphicsProvider.OverlayGraphics.Add(roiGraphic);

							roiGraphic.Suspend(); // prevent callout location calculation until all points are set
							roiGraphic.Name = markup.Name;
							roiGraphic.State = roiGraphic.CreateInactiveState();
							roiGraphic.Resume(true); // Force callout location calculation
							roiGraphic.Callout.TextLocation = markupProtractor.CalloutLocation;
						}
						else if (markup is MarkupLinear)
						{
							var markupLinear = (MarkupLinear)markup;

							var polylineGraphic = new PolylineGraphic();
							foreach (var point in markupLinear.Vertices)
								polylineGraphic.Points.Add(point);
							var roiGraphic = new RoiGraphic(new VerticesControlGraphic(new MoveControlGraphic(polylineGraphic)));

							markup.GraphicHashcode = roiGraphic.GetHashCode();
							graphics.Add(roiGraphic);
							graphicsProvider.OverlayGraphics.Add(roiGraphic);

							roiGraphic.Suspend(); // prevent callout location calculation until all points are set
							roiGraphic.Name = markup.Name;
							roiGraphic.State = roiGraphic.CreateInactiveState();
							roiGraphic.Resume(true); // Force callout location calculation
							roiGraphic.Callout.TextLocation = markupLinear.CalloutLocation;
						}
						else if (markup is MarkupPoint)
						{
							var markupPoint = (MarkupPoint)markup;

							IGraphic calloutGraphic;
							if (markupPoint.UseCrosshair)
							{
								calloutGraphic = new UserCrosshairCalloutGraphic
								{
									AnchorPoint = markupPoint.Point,
									TextLocation = markupPoint.CalloutLocation,
									Text = markupPoint.CalloutText,
									ShowShaft = !String.IsNullOrEmpty(markupPoint.CalloutText),
									LineStyle = LineStyle.Dot
								};

							}
							else
							{
								calloutGraphic = new UserCalloutGraphic
								{
									AnchorPoint = markupPoint.Point,
									TextLocation = markupPoint.CalloutLocation,
									Text = markupPoint.CalloutText,
									ShowArrowhead = true,
									LineStyle = LineStyle.Solid
								};
							}

							var statefulGraphic = new StandardStatefulGraphic(calloutGraphic);
							statefulGraphic.State = statefulGraphic.CreateInactiveState();

							var contextGraphic = new ContextMenuControlGraphic(typeof(ClearCanvas.ImageViewer.Tools.Standard.TextCalloutTool).FullName, "basicgraphic-menu", null, statefulGraphic);
							contextGraphic.Actions = new ToolSet(new GraphicToolExtensionPoint(), new GraphicToolContext(contextGraphic)).Actions;

							//if (markupPoint.Name != "RemoveForCalloutPlacement")
							{
								markup.GraphicHashcode = contextGraphic.GetHashCode();
								graphics.Add(contextGraphic);
								graphicsProvider.OverlayGraphics.Add(contextGraphic);
								//selectedPresentationImage.Draw();
							}
						}
					}

					box.TopLeftPresentationImage = selectedPresentationImage;
					box.Tiles[0].Select();
					box.Draw();

					break;
				}
			}
			return graphics;
		}

		internal static IMarkup GraphicToIMarkup(IGraphic graphic)
		{
			if (graphic == null || graphic.ParentPresentationImage == null)
				return null;

			var markup = DoGraphicToIMarkup(graphic);

			if (markup != null)
			{
				var sopInstanceUid = string.Empty;
				var frameNumber = 1;

				try
				{
					if (graphic.ParentPresentationImage is IImageSopProvider)
					{
						var imageSopProvider = graphic.ParentPresentationImage as IImageSopProvider;

						sopInstanceUid = imageSopProvider.ImageSop.SopInstanceUid;
						frameNumber = imageSopProvider.Frame.FrameNumber;
					}
					else if (!string.IsNullOrEmpty(graphic.ParentPresentationImage.Uid))
						sopInstanceUid = graphic.ParentPresentationImage.Uid;
				}
				catch (Exception)
				{
				}
				markup.PresentationImageUid = sopInstanceUid;
				markup.FrameNumber = frameNumber;
				markup.IncludeInAnnotation = true;
				markup.GraphicHashcode = graphic.GetHashCode();
			}

			return markup;
		}

		private static IMarkup DoGraphicToIMarkup(IGraphic graphic)
		{
			if (graphic == null || graphic.ParentPresentationImage == null)
				return null;

			IMarkup markup = null;
			var roiGraphic = graphic as RoiGraphic;
			if (roiGraphic != null)
			{
				if (roiGraphic.Roi is EllipticalRoi)
				{
					var ellipse = roiGraphic.Roi as EllipticalRoi;

					markup = new MarkupEllipse
					{
						TopLeft = new PointF(ellipse.BoundingBox.Left, ellipse.BoundingBox.Top),
						BottomRight = new PointF(ellipse.BoundingBox.Right, ellipse.BoundingBox.Bottom),
						Name = graphic.Name,
						GraphicHashcode = graphic.GetHashCode(),
						CalloutLocation = roiGraphic.Callout.TextLocation
					};
				}

				else if (roiGraphic.Roi is PolygonalRoi)
				{
					var polygon = roiGraphic.Roi as PolygonalRoi;

					markup = new MarkupPolygonal
					{
						Name = graphic.Name,
						Vertices = polygon.Polygon.Vertices == null ? null : new List<PointF>(polygon.Polygon.Vertices),
						GraphicHashcode = graphic.GetHashCode(),
						CalloutLocation = roiGraphic.Callout.TextLocation
					};
				}

				else if (roiGraphic.Roi is RectangularRoi)
				{
					var rectangularRoi = roiGraphic.Roi as RectangularRoi;

					markup = new MarkupRectangle
					{
						TopLeft = new PointF(rectangularRoi.BoundingBox.Left, rectangularRoi.BoundingBox.Top),
						BottomRight = new PointF(rectangularRoi.BoundingBox.Right, rectangularRoi.BoundingBox.Bottom),
						Name = graphic.Name,
						GraphicHashcode = graphic.GetHashCode(),
						CalloutLocation = roiGraphic.Callout.TextLocation
					};
				}

				else if (roiGraphic.Roi is ProtractorRoi)
				{
					var protractorRoi = roiGraphic.Roi as ProtractorRoi;

					markup = new MarkupProtractor
					{
						TopLeft = new PointF(protractorRoi.BoundingBox.Left, protractorRoi.BoundingBox.Top),
						BottomRight = new PointF(protractorRoi.BoundingBox.Right, protractorRoi.BoundingBox.Bottom),
						Name = graphic.Name,
						Points = protractorRoi.Points == null ? null : new List<PointF>(protractorRoi.Points),
						GraphicHashcode = graphic.GetHashCode(),
						CalloutLocation = roiGraphic.Callout.TextLocation
					};
				}
				else if (roiGraphic.Roi is LinearRoi)
				{
					var linearRoi = roiGraphic.Roi as LinearRoi;

					markup = new MarkupLinear
					{
						Vertices = linearRoi.Points == null ? null : new List<PointF>(linearRoi.Points),
						Name = graphic.Name,
						GraphicHashcode = graphic.GetHashCode(),
						CalloutLocation = roiGraphic.Callout.TextLocation
					};
				}

				if (markup != null)
					markup.CaptionText = roiGraphic.Roi.GetType().Name + Environment.NewLine + roiGraphic.Callout.Text;
			}
			else if (graphic is UserCalloutGraphic)
			{
				var userCalloutGraphic = graphic as UserCalloutGraphic;
				markup = new MarkupPoint
				{
					Name = graphic.Name,
					CaptionText = userCalloutGraphic.Text,
					CalloutText = userCalloutGraphic.Text,
					CalloutLocation = userCalloutGraphic.TextLocation,
					Point = userCalloutGraphic.AnchorPoint,
					GraphicHashcode = graphic.GetHashCode()
				};
			}
			else if (graphic is CrosshairCalloutGraphic)
			{
				var userCalloutGraphic = graphic as CrosshairCalloutGraphic;
				markup = new MarkupPoint
				{
					Name = graphic.Name,
					CaptionText = userCalloutGraphic.Text,
					CalloutText = userCalloutGraphic.Text,
					CalloutLocation = userCalloutGraphic.TextLocation,
					Point = userCalloutGraphic.AnchorPoint,
					UseCrosshair = true,
					GraphicHashcode = graphic.GetHashCode()
				};
			}
			else if (graphic is InvariantTextPrimitive)
			{
				var textGraphic = (InvariantTextPrimitive)graphic;
				markup = new MarkupPoint
				{
					Name = graphic.Name,
					CaptionText = textGraphic.Text,
					CalloutText = textGraphic.Text,
					CalloutLocation = textGraphic.Location,
					Point = textGraphic.Location,
					UseCrosshair = false,
					GraphicHashcode = graphic.GetHashCode()
				};
			}
			else if (graphic is ContextMenuControlGraphic)
			{
				markup = DoGraphicToIMarkup(((ContextMenuControlGraphic)graphic).Subject);
			}
			else if (graphic is AimGraphic)
			{
				markup = DoGraphicToIMarkup(((AimGraphic)graphic).Graphic);
				// Fix name - not all composite graphics may have the Name set correctly
				if (markup != null)
					markup.Name = ((AimGraphic)graphic).Graphic.Name;
			}
			else if (graphic is StandardStatefulGraphic)
			{
				markup = DoGraphicToIMarkup(((StandardStatefulGraphic)graphic).Subject);
			}
			else if (graphic is SegFrameImageGraphic)
			{
				// NO-OP
				// TODO: implement IMarkup for this type of graphic if we ever need to have segmentation graphic in the TemplateTree 
			}
			else
				System.Diagnostics.Debug.Assert(false, "Could not create Markup from " + graphic.GetType().Name);

			return markup;
		}
	}
}
