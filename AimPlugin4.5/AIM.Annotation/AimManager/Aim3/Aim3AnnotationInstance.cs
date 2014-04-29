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
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim3
{
	internal class Aim3AnnotationInstance : IAimAnnotationInstance
	{
		// TODO: switch to using WeakReference after implementing cache of loaded annotations
		//private readonly WeakReference _parentAimDocument;
		private readonly Aim3DocumentInstance _parentAimDocument;

		internal Aim3AnnotationInstance(Aim3DocumentInstance aim3Document, string annotationUid)
		{
			Platform.CheckForNullReference(aim3Document, "aim3Document");
			Platform.CheckForEmptyString(annotationUid, "annotationUid");

			AimAnnotation = aim3Document.Annotations.Find(annotation => annotation != null && annotation.UniqueIdentifier == annotationUid);

			if (AimAnnotation == null)
				throw new ArgumentException("AIM3: failed to initialize Annotation Instance from the collection");

			//_parentAimDocument = new WeakReference(aim3Document); // TODO
			_parentAimDocument = aim3Document;
		}

		#region IAimAnnotationInstance Members

		public AimVersion AimVersion
		{
			get { return AimVersion.AimVersion3; }
		}

		public IAimDocumentInstance ParentAimDocument
		{
			// TODO
			//get { return _parentAimDocument.Target as IAimDocumentInstance; }
			get { return _parentAimDocument; }
		}

		public string UniqueIdentifier
		{
			get { return AimAnnotation.UniqueIdentifier; }
		}

		public string UserLoginName
		{
			get { return ParentAimDocument.UserLoginName; }
		}

		public bool IsImageAnnotation
		{
			get { return AimAnnotation is aim_dotnet.ImageAnnotation; }
		}

		public bool IsAnnotationOfAnnotation
		{
			get { return AimAnnotation is aim_dotnet.AnnotationOfAnnotation; }
		}

		#endregion

		internal aim_dotnet.Annotation AimAnnotation { get; private set; }
	}
}
