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

using System.Linq;
using AIM.Annotation.AimManager;
using AIM.Annotation.Graphics;
using ClearCanvas.Common;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.StudyManagement;

namespace AIM.Annotation.Tools
{
	/// <summary>
	/// The tool keeps <code>AimActivityMonitor</code> alive while an ImageViewer is open and
	/// updates <code>ImageViewer</code> with new annotations obtained via an import tool or 
	/// by creating a new AIM Annotation.
	/// </summary>
	[ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
	public class AimAnnotationMonitorTool : ImageViewerTool
	{
		private IAimActivityMonitor _aimActivityMonitor;

		public AimAnnotationMonitorTool()
		{
		}

		public override void Initialize()
		{
			_aimActivityMonitor = AimActivityMonitor.Create(false);
			_aimActivityMonitor.StudyAnnotationsChanged += OnStudyAnnotationsChanged;

			base.Initialize();
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				_aimActivityMonitor.StudyAnnotationsChanged -= OnStudyAnnotationsChanged;
				_aimActivityMonitor.Dispose();
				_aimActivityMonitor = null;
			}

			base.Dispose(disposing);
		}

		protected override void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs e)
		{
			// NO-OP - prevent base functionality
		}

		protected override void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			// NO-OP - prevent base functionality
		}

		private void OnStudyAnnotationsChanged(object sender, StudyAimAnnotationsChangedEventArgs studyAimAnnotationsChangedEventArgs)
		{
			var imageViewer = Context.Viewer;
			if (imageViewer != null)
			{
				// 1. Remove deleted AIM Annotations from displayed images
				// 2. Add new AIM Annotations to displayed images
				AimGraphicHelpers.ImageViewerImageOperation(imageViewer, false, image =>
				{
					var imageSop = image as IImageSopProvider;
					if (imageSop != null && imageSop.ImageSop.StudyInstanceUid != studyAimAnnotationsChangedEventArgs.StudyInstanceUid)
						return false;

					var overlayGraphicsProvider = image as IOverlayGraphicsProvider;
					if (overlayGraphicsProvider == null)
						return false;

					var aimGraphics = overlayGraphicsProvider.OverlayGraphics.OfType<IAimGraphic>().ToList();

					bool graphicsUpdated = false;

					// Remove deleted annotations
					if (aimGraphics.Any() && studyAimAnnotationsChangedEventArgs.RemovedAnnotations != null)
					{
						var graphicsToDelete =
							aimGraphics.Where(
								aimGraphic =>
								studyAimAnnotationsChangedEventArgs.RemovedAnnotations.Any(
									aimDocumentInstance => aimDocumentInstance.SopInstanceUid == aimGraphic.AimAnnotation.ParentAimDocument.SopInstanceUid)).ToList();
						foreach (var aimGraphic in graphicsToDelete)
						{
							overlayGraphicsProvider.OverlayGraphics.Remove(aimGraphic);
							graphicsUpdated = true;
						}
					}

					// Add new annotations
					foreach (var aimDocumentInstance in studyAimAnnotationsChangedEventArgs.AddedAnnotations)
					{
						// This check is needed while we're not 100% sure that AIM caching works correctly
						if (aimGraphics.All(aimGraphic => aimDocumentInstance.SopInstanceUid != aimGraphic.AimAnnotation.ParentAimDocument.SopInstanceUid))
						{
							AimManager.AimManager.Instance.ReadGraphicsFromAnnotation(aimDocumentInstance, image);
							graphicsUpdated = true;
						}
					}

					if (graphicsUpdated && image.ParentDisplaySet.ImageBox.TopLeftPresentationImage == image)
						image.ParentDisplaySet.ImageBox.Draw(); // TODO - check that we are on the UI thread

					return graphicsUpdated;
				}, true);
			}

			// NOTE: sending new AIM SOP Instances to the original server where the study came from was done by DicomPublishingHelper
		}
	}
}
