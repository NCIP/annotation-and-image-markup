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
using System.Text;
using ClearCanvas.Common;
using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class DataProvider : IDataProvider
	{
		private readonly aim4_dotnet.AnnotationEntity _annotation;
		private readonly aim4_dotnet.Person _person;
		private readonly aim4_dotnet.User _user;

		internal DataProvider(aim4_dotnet.AnnotationEntity annotation, aim4_dotnet.Person person, aim4_dotnet.User user)
		{
			Platform.CheckForNullReference(annotation, "Annotation");

			_annotation = annotation;
			_person = person;
			_user = user;
		}

		public AimDetails AimAnnotationDetails
		{
			get
			{
				var imageAnnotation = _annotation as aim4_dotnet.ImageAnnotation;

				return new AimDetails(
					_annotation.UniqueIdentifier.Uid,
					GetSeriesUid(),
					_annotation.Name,
					//new TemplateTree.StandardValidTerm(new TemplateTree.StandardCodeSequence(_annotation.CodeValue, _annotation.CodeMeaning, _annotation.CodingSchemeDesignator, _annotation.CodingSchemeVersion), null),
					AimTemplateConverter.ToStandardValidTerm(_annotation.TypeCode),
					_annotation.DateTime,
					AnatomicEntities,
					ImagingObservations,
					_annotation.Comment,
					GetStudyUid(),
					GetSeriesUid(),
					imageAnnotation == null,
					_person == null ? null : new PersonInfo(_person.Name, _person.Id, _person.BirthDate, _person.Sex, _person.EthnicGroup),
					_user == null
						? null
						: new TemplateTree.UserInfo
							{
								Name = _user.Name,
								LoginName = _user.LoginName,
								RoleInTrial = _user.RoleInTrial,
								NumberWithinRoleOfClinicalTrial = _user.NumberWithinRoleOfClinicalTrial == null ? -1 : _user.NumberWithinRoleOfClinicalTrial.Value
							}
					);
			}
		}

		private aim4_dotnet.ImageStudy AimStudyFromAnnotation()
		{
			var imageAnnotation = _annotation as aim4_dotnet.ImageAnnotation;

			if (imageAnnotation == null || imageAnnotation.ImageReferenceEntityCollection.Count == 0)
				return null;

			var dicomImageReference = imageAnnotation.ImageReferenceEntityCollection[0] as aim4_dotnet.DicomImageReferenceEntity;
			if (dicomImageReference == null)
				return null;

			if (dicomImageReference.ImageStudy == null || dicomImageReference.ImageStudy.ImageSeries == null ||
				dicomImageReference.ImageStudy.ImageSeries.ImageCollection == null || dicomImageReference.ImageStudy.ImageSeries.ImageCollection.Count == 0)
				return null;

			return dicomImageReference.ImageStudy;
		}

		public string GetStudyUid()
		{
			var imageStudy = AimStudyFromAnnotation();
			return imageStudy == null ? null : imageStudy.InstanceUid.Uid;
		}

		public string GetSeriesUid()
		{
			var imageStudy = AimStudyFromAnnotation();
			return imageStudy == null || imageStudy.ImageSeries == null ? null : imageStudy.ImageSeries.InstanceUid.Uid;
		}

		public IList<TemplateTree.StandardValidTerm> AnatomicEntities
		{
			get
			{
				return _annotation.ImagingPhysicalEntityCollection == null
						   ? null
						   : _annotation.ImagingPhysicalEntityCollection.FindAll(iphe => iphe != null).ConvertAll(obs => AimTemplateConverter.ToStandardValidTerm(obs.TypeCode)).AsReadOnly();
			}
		}

		public IList<TemplateTree.StandardValidTerm> ImagingObservations
		{
			get
			{
				return _annotation.ImagingObservationEntityCollection.IsNullOrEmpty()
						   ? null
						   : _annotation.ImagingObservationEntityCollection.FindAll(io => io != null).ConvertAll(obs => AimTemplateConverter.ToStandardValidTerm(obs.TypeCode)).AsReadOnly();
			}
		}

		public IList<TemplateTree.StandardValidTerm> Inferences
		{
			get
			{
				return _annotation.InferenceEntityCollection.IsNullOrEmpty()
						   ? null
						   : _annotation.InferenceEntityCollection.ConvertAll(obs => AimTemplateConverter.ToStandardValidTerm(obs.TypeCode)).AsReadOnly();
			}
		}

		public string[] CalculationDescriptions
		{
			get
			{
				StringBuilder sb = new StringBuilder();
				string lineFeed = Environment.NewLine + "    ";

				foreach (var calculation in _annotation.CalculationEntityCollection)
				{
					if (sb.Length > 0)
						sb.Append(Environment.NewLine);

					int cnt = 0;
					if (calculation.TypeCode != null)
					{
						foreach (var code in calculation.TypeCode.Where(code => code != null))
						{
							if (cnt++ > 0)
								sb.Append(" ");
							sb.Append(code.CodeMeaning);
						}
					}
					if (cnt > 0)
						sb.AppendFormat("/{0}:", calculation.Description);
					else
						sb.AppendFormat("{0}:", calculation.Description);
					foreach (var calculationResult in calculation.CalculationResultCollection)
					{
						sb.Append(lineFeed);
						if (calculationResult is aim4_dotnet.CompactCalculationResult)
						{
							sb.AppendFormat("Compact Value = {0}", ((aim4_dotnet.CompactCalculationResult) calculationResult).Value);
						}
						else
						{
							var extendedCalcResult = (aim4_dotnet.ExtendedCalculationResult) calculationResult;
							if (extendedCalcResult.DimensionCollection != null && extendedCalcResult.DimensionCollection.Count > 1)
								sb.Append("<Multidimensional Result Value>"); // skip multidimensional results
							else
							{
								// Display only scalar results
								if (extendedCalcResult.CalculationDataCollection.Count == 1 && extendedCalcResult.CalculationDataCollection[0] != null)
									sb.AppendFormat("{0} {1}", extendedCalcResult.CalculationDataCollection[0].Value, calculationResult.UnitOfMeasure);
								else
									sb.Append("<Cannot display non-scalar results>"); // could be a vector here
							}
						}
					}
				}

				return sb.ToString().Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
			}
		}
	}
}
