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
using System.Diagnostics;
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class Aim4AnnotationInstance : IAimAnnotationInstance
	{
		// TODO: switch to using WeakReference after implementing cache of loaded annotations
		//private readonly WeakReference _parentAimDocument;
		private readonly Aim4DocumentInstance _parentAimDocument;

		internal Aim4AnnotationInstance(Aim4DocumentInstance aim4Document, aim4_dotnet.iso_21090.II annotationUid)
		{
			Platform.CheckForNullReference(aim4Document, "aim4Document");
			Platform.CheckForNullReference(annotationUid, "annotationUid");

			if (aim4Document.IsImageAnnotation)
			{
				var imageAnnotationCollection = (aim4_dotnet.ImageAnnotationCollection) aim4Document.AnnotationCollection;
				if (imageAnnotationCollection.ImageAnnotations != null)
				{
					AimAnnotationEntity =
						imageAnnotationCollection.ImageAnnotations.Find(imageAnnotation => imageAnnotation != null && Equals(imageAnnotation.UniqueIdentifier, annotationUid));
				}
			}
			else if (aim4Document.IsAnnotationOfAnnotation)
			{
				var annotationOfAnnotationCollection = (aim4_dotnet.AnnotationOfAnnotationCollection) aim4Document.AnnotationCollection;
				if (annotationOfAnnotationCollection.AnnotationOfAnnotations != null)
				{
					AimAnnotationEntity =
						annotationOfAnnotationCollection.AnnotationOfAnnotations.Find(
							annOfAnnotation => annOfAnnotation != null && Equals(annOfAnnotation.UniqueIdentifier, annotationUid));
				}
			}
			else
			{
				Debug.Assert(false, "Unexpected Annotation Collection type: " + aim4Document.GetType().Name);
			}

			if (AimAnnotationEntity == null)
				throw new ArgumentException("AIM4: failed to initialize Annotation Instance from the collection");

			//_parentAimDocument = new WeakReference(aim4Document); // TODO
			_parentAimDocument = aim4Document;
		}

		#region IAimAnnotationInstance Members

		public AimVersion AimVersion
		{
			get { return AimVersion.AimVersion4; }
		}

		public IAimDocumentInstance ParentAimDocument
		{
			// TODO
			//get { return _parentAimDocument.Target as IAimDocumentInstance; }
			get { return _parentAimDocument; }
		}

		public string UniqueIdentifier
		{
			get { return AimAnnotationEntity.UniqueIdentifier.Uid; }
		}

		public string UserLoginName
		{
			get { return ParentAimDocument.UserLoginName; }
		}

		public bool IsImageAnnotation
		{
			get { return AimAnnotationEntity is aim4_dotnet.ImageAnnotation; }
		}

		public bool IsAnnotationOfAnnotation
		{
			get { return AimAnnotationEntity is aim4_dotnet.AnnotationOfAnnotation; }
		}

		#endregion

		protected internal aim4_dotnet.AnnotationEntity AimAnnotationEntity { get; private set; }

	}
}
