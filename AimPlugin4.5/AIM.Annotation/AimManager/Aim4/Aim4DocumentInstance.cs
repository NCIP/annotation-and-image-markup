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
using System.Diagnostics;
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class Aim4DocumentInstance : IAimDocumentInstance
	{
		private readonly aim4_dotnet.AnnotationCollection _annotationCollection;
		private volatile List<IAimAnnotationInstance> _annotations;

		internal Aim4DocumentInstance(aim4_dotnet.AnnotationCollection annotationCollection, string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid)
		{
			Platform.CheckForEmptyString(studyInstanceUid, "studyInstanceUid");
			Platform.CheckForEmptyString(seriesInstanceUid, "seriesInstanceUid");
			Platform.CheckForEmptyString(sopInstanceUid, "sopInstanceUid");
			Platform.CheckForNullReference(annotationCollection, "annotationCollection");

			_annotationCollection = annotationCollection;

			StudyInstanceUid = studyInstanceUid;
			SeriesInstanceUid = seriesInstanceUid;
			SopInstanceUid = sopInstanceUid;
		}

		public AimVersion AimVersion
		{
			get
			{
				return AimVersion.AimVersion4;
			}
		}

		public List<IAimAnnotationInstance> AimAnnotations
		{
			get
			{
				if (_annotations == null)
				{
					_annotations = new List<IAimAnnotationInstance>();
					if (IsImageAnnotation)
					{
						var imageAnnotationCollection = (aim4_dotnet.ImageAnnotationCollection) _annotationCollection;
						if (imageAnnotationCollection.ImageAnnotations != null)
						{
							foreach (var imageAnnotation in imageAnnotationCollection.ImageAnnotations)
							{
								_annotations.Add(new Aim4ImageAnnotationInstance(this, imageAnnotation.UniqueIdentifier));
							}
						}
					}
					else if (IsAnnotationOfAnnotation)
					{
						var annotationOfAnnotationCollection = (aim4_dotnet.AnnotationOfAnnotationCollection)_annotationCollection;
						if (annotationOfAnnotationCollection != null)
						{
							foreach (var annotationOfAnnotation in annotationOfAnnotationCollection.AnnotationOfAnnotations)
							{
								_annotations.Add(new Aim4AnnotationInstance(this, annotationOfAnnotation.UniqueIdentifier));
							}
						}
					}
					else
					{
						Debug.Assert(false, "AIM4: Unexpected Annotation Collection type: " + _annotationCollection.GetType().Name);
					}
				}

				return _annotations;
			}
		}

		public string StudyInstanceUid { get; private set; }

		public string SeriesInstanceUid { get; private set; }

		public string SopInstanceUid { get; private set; }

		public bool IsImageAnnotation
		{
			get { return _annotationCollection is aim4_dotnet.ImageAnnotationCollection; }
		}

		public bool IsAnnotationOfAnnotation
		{
			get { return _annotationCollection is aim4_dotnet.AnnotationOfAnnotationCollection; }
		}

		public string UserLoginName
		{
			get { return _annotationCollection.User == null ? null : _annotationCollection.User.LoginName; }
		}

		public DateTime DateTime
		{
			get { return _annotationCollection.DateTime; }
		}

		public AimDocumentInstanceList ParentDocumentInstanceList { get; set; }

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is Aim4DocumentInstance))
				return false;

			var aimDocInstance = (Aim4DocumentInstance) obj;

			return StudyInstanceUid == aimDocInstance.StudyInstanceUid && SeriesInstanceUid == aimDocInstance.SeriesInstanceUid
			       && SopInstanceUid == aimDocInstance.SopInstanceUid;
		}

		public override int GetHashCode()
		{
			return 0x256E197F ^ StudyInstanceUid.GetHashCode() ^ SeriesInstanceUid.GetHashCode() ^ SopInstanceUid.GetHashCode();
		}

		internal aim4_dotnet.AnnotationCollection AnnotationCollection
		{
			get { return _annotationCollection; }
		}

		internal aim4_dotnet.User User
		{
			get { return _annotationCollection.User; }
		}

		internal aim4_dotnet.Person Person
		{
			get { return IsImageAnnotation ? ((aim4_dotnet.ImageAnnotationCollection) _annotationCollection).Person : null; }
		}
	}
}
