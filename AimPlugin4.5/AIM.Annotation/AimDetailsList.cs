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
using System.Collections.ObjectModel;
using System.Text;

using ClearCanvas.Common;

namespace AIM.Annotation
{
	// TODO - convert to a proper Component/Control combo?
	/// <summary>
	/// Contains display data for the AimDetailsListControl
	/// </summary>
	public class AimDetailsList : ObservableCollection<AimDetails>
	{
		public AimDetailsList() : base() {}
		public AimDetailsList(List<AimDetails> list) : base(list) { }
		public AimDetailsList(IEnumerable<AimDetails> list) : base(list) { }
	}

	public class PersonInfo
	{
		public PersonInfo(string name, string id, DateTime? birthDate, string sex, string ethnicGroup)
		{
			Platform.CheckForEmptyString(name, "name");
			Platform.CheckForEmptyString(id, "id");

			Name = name;
			Id = id;
			BirthDate = birthDate;
			Sex = sex;
			EthnicGroup = ethnicGroup;
		}

		public string Name { get; private set; }
		public string Id { get; private set; }
		public DateTime? BirthDate { get; private set; }
		public string Sex { get; private set; }
		public string EthnicGroup { get; private set; }
	}

	public class AimDetails
	{
		private readonly string _annotationUid;
		private readonly string _annotationSeriesUid;
		private readonly string _name;
		private readonly TemplateTree.StandardValidTerm _typeCode;
		private readonly DateTime _creattionDateTime;
		private readonly IList<TemplateTree.StandardValidTerm> _anatomicEntities;
		private readonly IList<TemplateTree.StandardValidTerm> _imagingObservations;
		private readonly string _comment;
		private readonly string _dicomStudyInstanceUid;
		private readonly string _dicomSeriesInstanceUid;
		private readonly bool _isImageAnnotation;
		private readonly PersonInfo _personInfo;
		private readonly TemplateTree.UserInfo _userInfo;

		public AimDetails(string annotationUid, string annotationSeriesUid, string name, TemplateTree.StandardValidTerm typeCode, DateTime creattionDateTime,
		                  IList<TemplateTree.StandardValidTerm> anatomicEntities, IList<TemplateTree.StandardValidTerm> imagingObservations, string comment,
		                  string dicomStudyInstanceUid, string dicomSeriesInstanceUid, bool isImageAnnotation, PersonInfo personInfo, TemplateTree.UserInfo userInfo)
		{
			Platform.CheckForEmptyString(annotationUid, "annotationUid");
			Platform.CheckForEmptyString(name, "name");
			Platform.CheckForNullReference(typeCode, "TypeCode");

			_annotationUid = annotationUid;
			_annotationSeriesUid = annotationSeriesUid;
			_name = name;
			_typeCode = typeCode;
			_creattionDateTime = creattionDateTime;
			_anatomicEntities = anatomicEntities;
			_imagingObservations = imagingObservations;
			_comment = comment;
			_dicomStudyInstanceUid = dicomStudyInstanceUid;
			_dicomSeriesInstanceUid = dicomSeriesInstanceUid;
			_isImageAnnotation = isImageAnnotation;
			_personInfo = personInfo;
			_userInfo = userInfo;
		}

		public string AnnotationUid
		{
			get { return _annotationUid; }
		}

		public string AnnotationSeriesUid
		{
			get { return _annotationSeriesUid; }
		}

		public string Name
		{
			get { return _name; }
		}

		public TemplateTree.StandardValidTerm TypeCode
		{
			get { return _typeCode; }
		}

		public DateTime CreationDateTime
		{
			get { return _creattionDateTime; }
		}

		public IList<TemplateTree.StandardValidTerm> AnatomicEntities
		{
			get { return _anatomicEntities; }
		}

		public IList<TemplateTree.StandardValidTerm> ImagingObservations
		{
			get { return _imagingObservations; }
		}

		public string Comment
		{
			get { return _comment ?? ""; }
		}

		public string ToolTipText
		{
			get
			{
				var toolTipText = new StringBuilder();

				toolTipText.AppendFormat("{0}\n{1}\n{2}\n{3}\n{4}", Name, CreationDateTime.ToString(),TypeCode.StandardCodeSequence.CodeValue, TypeCode.StandardCodeSequence.CodeMeaning, Comment);

				return toolTipText.ToString();
			}
		}

		public string DicomStudyInstanceUid
		{
			get { return _dicomStudyInstanceUid; }
		}

		public string DicomSeriesInstanceUid
		{
			get { return _dicomSeriesInstanceUid; }
		}

		public bool IsImageAnnotation
		{
			get { return _isImageAnnotation; }
		}

		public PersonInfo PersonInfo
		{
			get { return _personInfo; }
		}

		public TemplateTree.UserInfo UserInfo
		{
			get { return _userInfo; }
		}
	}
}
