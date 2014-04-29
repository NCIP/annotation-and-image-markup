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
using System.Linq;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.StudyManagement;

namespace AIM.Annotation.Graphics
{
	internal class AimGraphicHelpers
	{
		/// <summary>
		/// Performs given operation on the images in the given Image Viewer
		/// </summary>
		/// <param name="imageViewer">reference to <code>IImageViewer</code> that the operation has to be performed on</param>
		/// <param name="stopOnFirstMatch">when <code>true</code>, will return after the first successful predicate operation.</param>
		/// <param name="predicate">Operation to execute on each <code>IPresentationImage</code></param>
		/// <returns><code>true</code> if at least one of predicate runs succeeded and <code>false</code> - if all failed</returns>
		public static bool ImageViewerImageOperation(IImageViewer imageViewer, bool stopOnFirstMatch, Func<IPresentationImage, bool> predicate)
		{
			return ImageViewerImageOperation(imageViewer, stopOnFirstMatch, predicate, false);
		}

		/// <summary>
		/// Performs given operation on the images in the given Image Viewer
		/// </summary>
		/// <param name="imageViewer">reference to <code>IImageViewer</code> that the operation has to be performed on</param>
		/// <param name="stopOnFirstMatch">when <code>true</code>, will return after the first successful predicate operation.</param>
		/// <param name="predicate">Operation to execute on each <code>IPresentationImage</code></param>
		/// <param name="displayedImagesOnly">when<code>true</code>, will only operated on visible <code>DisplaySet</code>s</param>
		/// <returns><code>true</code> if at least one of predicate run succeeded and <code>false</code> - if all failed</returns>
		public static bool ImageViewerImageOperation(IImageViewer imageViewer, bool stopOnFirstMatch, Func<IPresentationImage, bool> predicate, bool displayedImagesOnly)
		{
			if (imageViewer == null)
				throw new ArgumentNullException("imageViewer");

			if (predicate == null)
				throw new ArgumentNullException("predicate");

			bool predicateWorked = false;

			// Go through displayed images first
			foreach (IImageBox imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
			{
				if (imageBox.DisplaySet == null || imageBox.DisplaySet.PresentationImages == null || imageBox.DisplaySet.PresentationImages.Count == 0)
					continue;

				foreach (var presentationImage in imageBox.DisplaySet.PresentationImages)
				{
					predicateWorked |= predicate(presentationImage);
					if (predicateWorked && stopOnFirstMatch)
						return true;
				}
			}

			if (!displayedImagesOnly)
			{
				// Go through other available images
				foreach (IImageSet imageSet in imageViewer.LogicalWorkspace.ImageSets)
				{
					foreach (IDisplaySet displaySet in imageSet.DisplaySets)
					{
						if (displaySet.PresentationImages.Count == 0)
							continue;

						foreach (var presentationImage in displaySet.PresentationImages)
						{
							predicateWorked |= predicate(presentationImage);
							if (predicateWorked && stopOnFirstMatch)
								return true;
						}
					}
				}
			}
			return predicateWorked;
		}

		/// <summary>
		/// Find requested image in the ImageViewer and makes it selected. Will load a series if it's not loaded.
		/// </summary>
		/// <param name="imageViewer">ImageViewer that hosts the requested image</param>
		/// <param name="sopInstanceUid">SOP Instance UID of the image</param>
		/// <param name="frameNumber">image frame number (1 - first image)</param>
		/// <returns>Returns requested image or <code>null</code> if the image is not found.</returns>
		public static IPresentationImage SelectImage(IImageViewer imageViewer, string sopInstanceUid, int frameNumber)
		{
			// Search displayed images first
			foreach (var imageBox in imageViewer.PhysicalWorkspace.ImageBoxes)
			{
				if (imageBox.DisplaySet == null || imageBox.DisplaySet.PresentationImages == null || imageBox.DisplaySet.PresentationImages.Count == 0)
					continue;

				var presentationImage = imageBox.DisplaySet.PresentationImages.Cast<IImageSopProvider>().FirstOrDefault(
						pi => pi.ImageSop.SopInstanceUid == sopInstanceUid && pi.Frame.FrameNumber == frameNumber) as IPresentationImage;

				if (presentationImage == null)
					continue;

				try
				{
					// Unselect selected in a different image box
					if (!imageBox.Selected)
						UnselectCurrentGraphics(imageViewer.PhysicalWorkspace.SelectedImageBox);

					imageBox.TopLeftPresentationImage = presentationImage;
					imageBox.Tiles[0].Select();
					imageBox.Draw();

					return presentationImage;
				}
				catch (Exception ex)
				{
					ExceptionHandler.Report(ex, imageViewer.DesktopWindow);
				}
			}

			// Search other available images
			foreach (var imageSet in imageViewer.LogicalWorkspace.ImageSets)
			{

				foreach (var displaySet in imageSet.DisplaySets)
				{
					var presentationImage = displaySet.PresentationImages.Cast<IImageSopProvider>().FirstOrDefault(
							pi => pi.ImageSop.SopInstanceUid == sopInstanceUid && pi.Frame.FrameNumber == frameNumber) as IPresentationImage;

					if (presentationImage == null)
						continue;
					try
					{
						var targetImageBox = imageViewer.PhysicalWorkspace.SelectedImageBox ??
												   (imageViewer.PhysicalWorkspace.ImageBoxes.Count > 0 ? imageViewer.PhysicalWorkspace.ImageBoxes[0] : null);
						if (targetImageBox == null)
						{
							imageViewer.DesktopWindow.ShowMessageBox("Failed to find available display", MessageBoxActions.Ok);
							Platform.Log(LogLevel.Error, "Failed to locate a target ImageBox to display selected image.");
							return null;
						}

						var targetDisplaySet = displaySet.CreateFreshCopy();
						var targetPresentationImage = targetDisplaySet.PresentationImages.Cast<IImageSopProvider>().FirstOrDefault(
							pi => pi.ImageSop.SopInstanceUid == sopInstanceUid && pi.Frame.FrameNumber == frameNumber) as IPresentationImage;
						if (targetPresentationImage == null)
						{
							imageViewer.DesktopWindow.ShowMessageBox("Failed to find required image", MessageBoxActions.Ok);
							Platform.Log(LogLevel.Error, "Failed to locate a target PresentationImage in a new DisplaySet.");
							return null;
						}

						// Unselect selected in a different image box
						if (!targetImageBox.Selected)
							UnselectCurrentGraphics(imageViewer.PhysicalWorkspace.SelectedImageBox);

						targetImageBox.DisplaySet = targetDisplaySet;
						targetImageBox.TopLeftPresentationImage = targetPresentationImage;
						targetImageBox.Tiles[0].Select();
						targetImageBox.Draw();

						return targetPresentationImage;
					}
					catch (Exception ex)
					{
						ExceptionHandler.Report(ex, imageViewer.DesktopWindow);
					}
				}
			}

			return null;
		}

		private static void UnselectCurrentGraphics(IImageBox imageBox)
		{
			if (imageBox == null)
				return;

			if (imageBox.TopLeftPresentationImage != null)
			{
				imageBox.TopLeftPresentationImage.SelectedGraphic = null;
				imageBox.Draw();
			}
		}
	}
}
