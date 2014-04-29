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
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class Aim4ImageAnnotationInstance : Aim4AnnotationInstance, IAimImageAnnotationInstace
	{
		internal Aim4ImageAnnotationInstance(Aim4DocumentInstance aim4Document, aim4_dotnet.iso_21090.II annotationUid)
			: base(aim4Document, annotationUid)
		{
			Platform.CheckTrue(IsImageAnnotation, "IsImageAnnotation");
		}

		public string ImageStudyUid
		{
			get
			{
				var imageAnnotation = (aim4_dotnet.ImageAnnotation)AimAnnotationEntity;
				return imageAnnotation.ImageReferenceEntityCollection.OfType<aim4_dotnet.DicomImageReferenceEntity>()
									  .Select(dicomImageRef => dicomImageRef.ImageStudy.InstanceUid.Uid)
									  .FirstOrDefault();
			}
		}

		public string ImageSeriesUid
		{
			get
			{
				var imageAnnotation = (aim4_dotnet.ImageAnnotation)AimAnnotationEntity;
				return imageAnnotation.ImageReferenceEntityCollection.OfType<aim4_dotnet.DicomImageReferenceEntity>()
									  .Select(dicomImageRef => dicomImageRef.ImageStudy.ImageSeries.InstanceUid.Uid)
									  .FirstOrDefault();
			}
		}

		public string FirstImageSopInstanceUid
		{
			get
			{
				var imageAnnotation = (aim4_dotnet.ImageAnnotation) AimAnnotationEntity;
				foreach (var entity in imageAnnotation.ImageReferenceEntityCollection)
				{
					var dicomImageRef = entity as aim4_dotnet.DicomImageReferenceEntity;
					if (dicomImageRef != null && dicomImageRef.ImageStudy != null && dicomImageRef.ImageStudy.ImageSeries != null)
						foreach (var image in dicomImageRef.ImageStudy.ImageSeries.ImageCollection)
						{
							if (image != null)
								return image.SopInstanceUid.Uid;
						}
				}
				return null;
			}
		}

		// Frame number of the image that has the first markup in the annotation
		public int FirstFrameNumber
		{
			get
			{
				var imageAnnotation = (aim4_dotnet.ImageAnnotation) AimAnnotationEntity;
				if (imageAnnotation.MarkupEntityCollection != null)
				{
					foreach (var entity in imageAnnotation.MarkupEntityCollection)
					{
						aim4_dotnet.TwoDimensionGeometricShapeEntity geoShape2D = null;
						if (entity is aim4_dotnet.TwoDimensionGeometricShapeEntity)
							geoShape2D = (aim4_dotnet.TwoDimensionGeometricShapeEntity) entity;
						else if (entity is aim4_dotnet.TextAnnotationEntity)
							geoShape2D = ((aim4_dotnet.TextAnnotationEntity) entity).GeometricShapeEntity as aim4_dotnet.TwoDimensionGeometricShapeEntity;

						// TODO - figure out FrameNumber for projection of ThreeDimensionGeometricShapes as well

						if (geoShape2D != null && geoShape2D.ReferencedFrameNumber != null)
							return geoShape2D.ReferencedFrameNumber.Value;
					}
				}
				
				return 1;
			}
		}
	}
}
