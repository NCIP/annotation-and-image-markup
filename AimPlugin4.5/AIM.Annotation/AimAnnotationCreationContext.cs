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
using ClearCanvas.Common;

namespace AIM.Annotation
{
	internal class AimAnnotationCreationContext
	{
		internal enum AnnotationKind
		{
			ImageAnnotation,
			AnnotationOfAnnotation
		}

		private readonly AnnotationKind _annotationKind;
		private readonly TemplateTree.StandardCodeSequence _annotationTypeCode;
		private readonly TemplateTree.AimTemplateTree _templateTree;
		private readonly int _seriesNumber;
		private string _annotationComment;
		private bool _includeCalculations;
		private Dictionary<string, HashSet<int>> _sopInstanceUidAndFrameNumber; // if specified, annotation is created for these SOP Instances with the specified frame numbers only. The images must belong to the same series.

		public AimAnnotationCreationContext(AnnotationKind annotationKind, TemplateTree.StandardCodeSequence annotationTypeCode, TemplateTree.AimTemplateTree templateTree, int seriesNumber)
		{
			Platform.CheckForNullReference(annotationTypeCode, "annotationTypeCode");
			Platform.CheckForNullReference(templateTree, "templateTree");

			_annotationKind = annotationKind;
			_annotationTypeCode = annotationTypeCode;
			_templateTree = templateTree;
			_seriesNumber = seriesNumber;
			_includeCalculations = true;
		}

		public bool IncludeCalculations
		{
			get { return _includeCalculations; }
			set { _includeCalculations = value; }
		}

		public AnnotationKind SelectedAnnotationKind
		{
			get { return _annotationKind; }
		}

		public TemplateTree.StandardCodeSequence AnnotationTypeCode
		{
			get { return _annotationTypeCode; }
		}

		public TemplateTree.AimTemplateTree TemplateTree
		{
			get { return _templateTree; }
		}

		public int SeriesNumber
		{
			get { return _seriesNumber; }
		}

		public Dictionary<string, HashSet<int>> SopInstanceUidAndFrameNumbers
		{
			get { return _sopInstanceUidAndFrameNumber ?? ( _sopInstanceUidAndFrameNumber = new Dictionary<string, HashSet<int>>()); }
			set { _sopInstanceUidAndFrameNumber = value; }
		}

		public string AnnotationName
		{
			get { return _templateTree.AnnotationName; }
		}

		public string AnnotationComment
		{
			get { return _annotationComment; }
			set { _annotationComment = value; }
		}

		public TemplateTree.UserInfo AnnotationUser
		{
			get { return _templateTree.UserInfo; }
		}
	}
}
