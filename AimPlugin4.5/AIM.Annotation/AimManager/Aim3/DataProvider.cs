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
using System.Text;
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim3
{
	internal class DataProvider : IDataProvider
	{
		private readonly aim_dotnet.Annotation _annotation;

		internal DataProvider(aim_dotnet.Annotation annotation)
		{
			Platform.CheckForNullReference(annotation, "Annotation");

			_annotation = annotation;
		}

		public AimDetails AimAnnotationDetails
		{
			get
			{
				var imageAnnotation = _annotation as aim_dotnet.ImageAnnotation;
				var patient = imageAnnotation == null ? null : imageAnnotation.Patient;
				var userInfo = _annotation.User;

				return new AimDetails(
					_annotation.UniqueIdentifier,
					GetSeriesUid(),
					_annotation.Name,
					new TemplateTree.StandardValidTerm(
						new TemplateTree.StandardCodeSequence(_annotation.CodeValue, _annotation.CodeMeaning, _annotation.CodingSchemeDesignator, _annotation.CodingSchemeVersion),
						null),
					_annotation.DateTime,
					AnatomicEntities,
					ImagingObservations,
					_annotation.Comment,
					GetStudyUid(),
					GetSeriesUid(),
					imageAnnotation == null,
					patient == null ? null : new PersonInfo(patient.Name, patient.Id, patient.BirthDate, patient.Sex, patient.EthnicGroup),
					userInfo == null
						? null
						: new TemplateTree.UserInfo
							{
								Name = userInfo.Name,
								LoginName = userInfo.LoginName,
								RoleInTrial = userInfo.RoleInTrial,
								NumberWithinRoleOfClinicalTrial = userInfo.NumberWithinRoleOfClinicalTrial
							}
					);
			}
		}

		private aim_dotnet.ImageStudy AimStudyFromAnnotation()
		{
			var imageAnnotation = _annotation as aim_dotnet.ImageAnnotation;

			if (imageAnnotation == null || imageAnnotation.ImageReferenceCollection.Count == 0)
				return null;

			var dicomImageReference = imageAnnotation.ImageReferenceCollection[0] as aim_dotnet.DICOMImageReference;
			if (dicomImageReference == null)
				return null;

			if (dicomImageReference.Study == null || dicomImageReference.Study.Series == null ||
				dicomImageReference.Study.Series.ImageCollection == null || dicomImageReference.Study.Series.ImageCollection.Count == 0)
				return null;

			return dicomImageReference.Study;
		}

		public string GetStudyUid()
		{
			var imageStudy = AimStudyFromAnnotation();
			return imageStudy == null ? null : imageStudy.InstanceUID;
		}

		public string GetSeriesUid()
		{
			var imageStudy = AimStudyFromAnnotation();
			return imageStudy == null || imageStudy.Series == null ? null : imageStudy.Series.InstanceUID;
		}

		public IList<TemplateTree.StandardValidTerm> AnatomicEntities
		{
			get
			{
				return _annotation.AnatomyEntityCollection == null ?
					null :
					_annotation.AnatomyEntityCollection.ConvertAll(obs => new TemplateTree.StandardValidTerm(AimTemplateConverter.ToStandardCodeSequence(obs), null)).AsReadOnly();
			}
		}

		public IList<TemplateTree.StandardValidTerm> ImagingObservations
		{
			get
			{
				return _annotation.ImagingObservationCollection == null ?
					null :
					_annotation.ImagingObservationCollection.ConvertAll(obs => new TemplateTree.StandardValidTerm(AimTemplateConverter.ToStandardCodeSequence(obs), null)).AsReadOnly();
			}
		}

		public IList<TemplateTree.StandardValidTerm> Inferences
		{
			get
			{
				return _annotation.InferenceCollection == null ?
					null :
					_annotation.InferenceCollection.ConvertAll(obs => new TemplateTree.StandardValidTerm(AimTemplateConverter.ToStandardCodeSequence(obs), null)).AsReadOnly();
			}
		}

		public string[] CalculationDescriptions
		{
			get
			{
				StringBuilder sb = new StringBuilder();
				string lineFeed = Environment.NewLine + "    ";

				foreach (var calculation in _annotation.CalculationCollection)
				{
					if (sb.Length > 0)
						sb.Append(Environment.NewLine);

					sb.AppendFormat("{0}/{1}:", calculation.CodeMeaning, calculation.Description);
					foreach (aim_dotnet.CalculationResult calculationResult in calculation.CalculationResultCollection)
					{
						sb.Append(lineFeed);
						if (calculationResult.NumberOfDimensions > 1)
							sb.Append("<Multidimensional Result Value>"); // skip multidimensional results
						else
						{
							// Display only scalar results
							if (calculationResult.CalculationDataCollection.Count == 1 && calculationResult.CalculationDataCollection[0] != null)
								sb.AppendFormat("{0} {1}", calculationResult.CalculationDataCollection[0].Value, calculationResult.UnitOfMeasure);
							else
								sb.Append("<Cannot display non-scalar results>"); // could be a vector here
						}
					}
				}

				return sb.ToString().Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
			}
		}
	}
}
