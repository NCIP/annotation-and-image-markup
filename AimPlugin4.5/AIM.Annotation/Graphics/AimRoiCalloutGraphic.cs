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

using System.Collections.Generic;
using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.RoiGraphics.Analyzers;

namespace AIM.Annotation.Graphics
{
	internal class AimRoiCalloutGraphic : RoiCalloutGraphic
	{
		/// <summary>
		/// Constructs a new instance of <see cref="AimRoiCalloutGraphic"/> with all <see cref="IRoiAnalyzer"/>s extending <see cref="RoiAnalyzerExtensionPoint"/>.
		/// </summary>
		public AimRoiCalloutGraphic()
		{
			AllowRename = false;
		}

		/// <summary>
		/// Constructs a new instance of <see cref="AimRoiCalloutGraphic"/> with the specified <see cref="IRoiAnalyzer"/>s.
		/// </summary>
		/// <param name="analyzers"></param>
		public AimRoiCalloutGraphic(IEnumerable<IRoiAnalyzer> analyzers)
			: base(analyzers)
		{
			AllowRename = false;
		}

		/// <summary>
		/// Cloning constructor.
		/// </summary>
		/// <param name="source">The source object from which to clone.</param>
		/// <param name="context">The cloning context object.</param>
		protected AimRoiCalloutGraphic(RoiCalloutGraphic source, ICloningContext context) : base(source, context)
		{
			context.CloneFields(source, this);
		}

		protected override void OnParentPresentationImageChanged(ClearCanvas.ImageViewer.IPresentationImage oldParentPresentationImage, ClearCanvas.ImageViewer.IPresentationImage newParentPresentationImage)
		{
			base.OnParentPresentationImageChanged(oldParentPresentationImage, newParentPresentationImage);

			// Update callout text and calculations
			// Interestingly, before overwrite, update only required for newly created annotations' graphics
			//if (SynchronizationContext.Current == null)
			this.Update();
		}
	}
}
