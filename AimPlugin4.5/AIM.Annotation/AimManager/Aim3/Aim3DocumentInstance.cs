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
using System.Linq;
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim3
{
	internal class Aim3DocumentInstance : IAimDocumentInstance
	{
		private readonly List<aim_dotnet.Annotation> _aimAnnotations;
		private volatile List<IAimAnnotationInstance> _annotations;

		internal Aim3DocumentInstance(List<aim_dotnet.Annotation> aimAnnotation, string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid)
		{
			Platform.CheckForEmptyString(studyInstanceUid, "studyInstanceUid");
			Platform.CheckForEmptyString(seriesInstanceUid, "seriesInstanceUid");
			Platform.CheckForEmptyString(sopInstanceUid, "sopInstanceUid");
			Platform.CheckForNullReference(aimAnnotation, "aimAnnotation");

			_aimAnnotations = aimAnnotation;

			StudyInstanceUid = studyInstanceUid;
			SeriesInstanceUid = seriesInstanceUid;
			SopInstanceUid = sopInstanceUid;
		}

		public AimVersion AimVersion
		{
			get
			{
				return AimVersion.AimVersion3;
			}
		}

		public List<IAimAnnotationInstance> AimAnnotations
		{
			get
			{
				if (_annotations == null)
				{
					_annotations = new List<IAimAnnotationInstance>();
					foreach (var nativeAnnotation in Annotations)
					{
						if (nativeAnnotation == null)
							continue;
						_annotations.Add(new Aim3AnnotationInstance(this, nativeAnnotation.UniqueIdentifier));
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
			get { return _aimAnnotations.FirstOrDefault() is aim_dotnet.ImageAnnotation; }
		}

		public bool IsAnnotationOfAnnotation
		{
			get { return _aimAnnotations.FirstOrDefault() is aim_dotnet.AnnotationOfAnnotation; }
		}

		public string UserLoginName
		{
			get
			{
				var annotation = _aimAnnotations.FirstOrDefault();
				return annotation == null || annotation.User == null ? null : annotation.User.LoginName;
			}
		}

		public DateTime DateTime
		{
			get
			{
				var annotation = _aimAnnotations.FirstOrDefault();
				return annotation != null ? annotation.DateTime : new DateTime();
			}
		}

		public AimDocumentInstanceList ParentDocumentInstanceList { get; set; }

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is Aim3DocumentInstance))
				return false;

			var aimDocInstance = (Aim3DocumentInstance)obj;

			return StudyInstanceUid == aimDocInstance.StudyInstanceUid && SeriesInstanceUid == aimDocInstance.SeriesInstanceUid
				   && SopInstanceUid == aimDocInstance.SopInstanceUid;
		}

		public override int GetHashCode()
		{
			return 0x256D197F ^ StudyInstanceUid.GetHashCode() ^ SeriesInstanceUid.GetHashCode() ^ SopInstanceUid.GetHashCode();
		}

		internal List<aim_dotnet.Annotation> Annotations
		{
			get { return _aimAnnotations; }
		}
	}
}
