#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;

using AIMTCGAService;
using DataServiceUtil;

namespace SearchComponent
{
	internal partial class AIMSearchCoordinator
	{
		private class AIMSearchCommand : SearchCommand
		{
			private readonly AIMQueryParameters _aimQueryParameters;

			public AIMSearchCommand(AIMQueryParameters queryParameters)
			{
				_aimQueryParameters = queryParameters;
			}

			public override void Execute()
			{
				List<AIMSearchResult> results = new List<AIMSearchResult>();
				List<aim_dotnet.Annotation> annotations = null;
				try
				{
					if (_aimQueryParameters.AnnotationType == AnnotationType.ImageAnnotation)
					{
						AIMTCGAImageAnnotation aimService = new AIMTCGAImageAnnotation();
						annotations = aimService.getImageAnnotationInfoList(_aimQueryParameters);
					}
					else if (_aimQueryParameters.AnnotationType == AnnotationType.AnnotationOfAnnotation)
					{
						AIMTCGAAnnotationOfAnnotation aimService = new AIMTCGAAnnotationOfAnnotation();
						annotations = aimService.getAnnotationOfAnnotationInfoList(_aimQueryParameters);
					}
				}
				catch (GridServicerException ex)
				{
					SetError(string.Format("{0}. Contact your system administrator", ex.Message));
				}
				if (annotations != null)
				{
					foreach (aim_dotnet.Annotation annotation in annotations)
					{
						AIMSearchResult result = new AIMSearchResult();
						result.RetrievedAnnotation = annotation;
						if (annotation.AnatomyEntityCollection != null)
						{
							foreach (aim_dotnet.AnatomicEntity anatomicEntity in annotation.AnatomyEntityCollection)
							{
								AnatomicEntity ae = new AnatomicEntity();
								ae.CodeValue = anatomicEntity.CodeValue;
								ae.CodeMeaning = anatomicEntity.CodeMeaning;
								ae.CodingSchemeDesignator = anatomicEntity.CodingSchemeDesignator;
								result.AnatomicEntities.Add(ae);

								if (anatomicEntity.AnatomicEntityCharacteristicCollection != null)
								{
									foreach (aim_dotnet.AnatomicEntityCharacteristic characteristic in anatomicEntity.AnatomicEntityCharacteristicCollection)
									{
										AnatomicEntityCharacteristic aec = new AnatomicEntityCharacteristic();
										aec.CodeValue = characteristic.CodeValue;
										aec.CodeMeaning = characteristic.CodeMeaning;
										aec.CodingSchemeDesignator = characteristic.CodingSchemeDesignator;
										result.AnatomicEntityCharacteristics.Add(aec);
									}
								}
							}
						}
						if (annotation.ImagingObservationCollection != null)
						{
							foreach (aim_dotnet.ImagingObservation imagingObservation in annotation.ImagingObservationCollection)
							{
								ImagingObservation io = new ImagingObservation();
								io.CodeValue = imagingObservation.CodeValue;
								io.CodeMeaning = imagingObservation.CodeMeaning;
								io.CodingSchemeDesignator = imagingObservation.CodingSchemeDesignator;
								result.ImagingObservations.Add(io);

								if (imagingObservation.ImagingObservationCharacteristicCollection != null)
								{
									foreach (aim_dotnet.ImagingObservationCharacteristic characteristic in imagingObservation.ImagingObservationCharacteristicCollection)
									{
										ImagingObservationCharacteristic ioc = new ImagingObservationCharacteristic();
										ioc.CodeValue = characteristic.CodeValue;
										ioc.CodeMeaning = characteristic.CodeMeaning;
										ioc.CodingSchemeDesignator = characteristic.CodingSchemeDesignator;
										ioc.Comment = characteristic.Comment;
										result.ImagingObservationCharacteristics.Add(ioc);
									}
								}
							}
						}
						if (annotation.User != null)
						{
							User user = new User();
							user.Name = annotation.User.Name;
							user.LoginName = annotation.User.LoginName;
							user.RoleInTrial = annotation.User.RoleInTrial;
							user.NumberWithinRoleInClinicalTrial = annotation.User.NumberWithinRoleOfClinicalTrial;
							result.User = user;
						}
						if (annotation is aim_dotnet.ImageAnnotation)
						{
							aim_dotnet.ImageAnnotation imageAnnotation = (aim_dotnet.ImageAnnotation)annotation;

							// Study Instance UID
							if (imageAnnotation.ImageReferenceCollection != null && imageAnnotation.ImageReferenceCollection.Count > 0)
							{
								aim_dotnet.DICOMImageReference dicomImageReference =
									imageAnnotation.ImageReferenceCollection[0] as aim_dotnet.DICOMImageReference;
								if (dicomImageReference != null)
									result.Study.StudyInstanceUid = dicomImageReference.Study.InstanceUID;
							}

							if (imageAnnotation.Patient != null)
							{
								result.Patient.PatientId = imageAnnotation.Patient.Id.ToString();
								result.Patient.PatientsName = imageAnnotation.Patient.Name;
								result.Patient.PatientsSex = imageAnnotation.Patient.Sex;
								result.Patient.PatientBirthDate = imageAnnotation.Patient.BirthDate;
							}

							foreach (aim_dotnet.ImageReference imageReference in imageAnnotation.ImageReferenceCollection)
							{
								if (imageReference is aim_dotnet.DICOMImageReference)
								{
									aim_dotnet.DICOMImageReference dicomImageReference = (aim_dotnet.DICOMImageReference)imageReference;
									result.Series.SeriesInstanceUid = ((dicomImageReference.Study ?? new aim_dotnet.ImageStudy()).Series ?? new aim_dotnet.ImageSeries()).InstanceUID;
								}
							}
						}

						results.Add(result);
					}
				}

				AddResultsToTable(results);

				OnCommandExecuted();
			}
		}
	}
}
