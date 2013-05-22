//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;
using aim_dotnet;

namespace AIM.Annotation
{
	internal class AimAnnotationCreationContext
	{
		private readonly AnnotationKind _annotationKind;
		private readonly StandardCodeSequence _annotationTypeCode;
		private readonly string _annotationName;
		private string _annotationComment;
		private bool _includeCalculations;
		private User _user; // annotation creator's information
		private List<string> _sopInstanceUIDs = null; // if specified, annotation is created for these images only. The images must belong to the same series.
		private List<AnatomicEntity> _anatomicEntities;
		private List<ImagingObservation> _imagingObservations;
		private List<Inference> _inferences;

		public AimAnnotationCreationContext(AnnotationKind annotationKind, StandardCodeSequence annotationTypeCode, string name)
		{
			_annotationKind = annotationKind;
			_annotationTypeCode = annotationTypeCode;
			_annotationName = name;
			_includeCalculations = true;
		}

		public bool includeCalculations
		{
			get { return _includeCalculations; }
			set { _includeCalculations = value; }
		}

		public AnnotationKind SelectedAnnotationKind
		{
			get { return _annotationKind; }
		}

		public StandardCodeSequence AnnotationTypeCode
		{
			get { return _annotationTypeCode; }
		}

		public List<string> SOPImageUIDs
		{
			get { return _sopInstanceUIDs ?? new List<string>(); }
			set { _sopInstanceUIDs = value == null ? null : new List<string>(value); }
		}

		public string AnnotationName
		{
			get { return _annotationName; }
		}

		public string AnnotationComment
		{
			get { return _annotationComment; }
			set { _annotationComment = value; }
		}

		public User AnnotationUser
		{
			get { return _user; }
			set { _user = value; }
		}

		public List<AnatomicEntity> SelectedAnatomicEntities
		{
			get { return _anatomicEntities; }
			set { _anatomicEntities = value == null || value.Count == 0 ? null : new List<AnatomicEntity>(value); }
		}

		public List<ImagingObservation> SelectedImagingObservations
		{
			get { return _imagingObservations; }
			set { _imagingObservations = value == null || value.Count == 0 ? null : new List<ImagingObservation>(value); }
		}

		public List<Inference> SelectedInferences
		{
			get { return _inferences; }
			set { _inferences = value == null || value.Count == 0 ? null : new List<Inference>(value); }
		}
	}
}
