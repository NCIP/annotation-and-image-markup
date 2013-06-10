#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using ClearCanvas.Common;
using DataServiceUtil;

namespace SearchComponent
{
	internal partial class AIMSearchCoordinator : SearchCoordinator<AIMSearchResult>
	{
		private AIMSearchCriteriaComponent _criteriaComponent;

		public AIMSearchCoordinator()
		{}

		public void SetSearchCriteriaComponent(AIMSearchCriteriaComponent criteriaComponent)
		{
			_criteriaComponent = criteriaComponent;
		}

		public void PerformSearch()
		{
			_criteriaComponent.Enabled = false;

            AIMQueryParameters aimQueryParameters = new AIMQueryParameters();
            if( !string.IsNullOrEmpty(_criteriaComponent.StudyInstanceUid))
				aimQueryParameters.StudyInstanceUidParameters.Add(new QueryData(_criteriaComponent.StudyInstanceUid.Trim(), QueryPredicate.LIKE));
            if (_criteriaComponent.AnnotationOfAnnotation)
                aimQueryParameters.AnnotationType = AnnotationType.AnnotationOfAnnotation;
            else if (_criteriaComponent.ImageAnnotation)
                aimQueryParameters.AnnotationType = AnnotationType.ImageAnnotation;
            else
                Platform.Log(LogLevel.Error, "Type of annotation cannot be retrieved from the user selection.");
		    foreach (AnatomicEntity anatomicEntity in _criteriaComponent.AnatomicEntities)
		    {
		        AimAnatomicEntityQueryData ae = new AimAnatomicEntityQueryData();
		        ae.CodeValue = new QueryData(anatomicEntity.CodeValue, QueryPredicate.LIKE);
		        ae.CodeMeaning = new QueryData(anatomicEntity.CodeMeaning, QueryPredicate.LIKE);
				ae.CodingSchemeDesignator = new QueryData(anatomicEntity.CodingSchemeDesignator, QueryPredicate.LIKE);
		        aimQueryParameters.AeQueryParameters.Add(ae);
		    }
			foreach (AnatomicEntityCharacteristic anatomicEntityCharacteristic in _criteriaComponent.AnatomicEntityCharacteristics)
			{
				AimAnatomicEntityCharacteristicQueryData aec = new AimAnatomicEntityCharacteristicQueryData();
				aec.CodeValue = new QueryData(anatomicEntityCharacteristic.CodeValue, QueryPredicate.LIKE);
				aec.CodeMeaning = new QueryData(anatomicEntityCharacteristic.CodeMeaning, QueryPredicate.LIKE);
				aec.CodingSchemeDesignator = new QueryData(anatomicEntityCharacteristic.CodingSchemeDesignator, QueryPredicate.LIKE);
				aimQueryParameters.AecQueryParameters.Add(aec);
			}
		    foreach (ImagingObservation imagingObservation in _criteriaComponent.ImagingObservations)
		    {
		        AimImagingObservationQueryData io = new AimImagingObservationQueryData();
				io.CodeValue = new QueryData(imagingObservation.CodeValue, QueryPredicate.LIKE);
				io.CodeMeaning = new QueryData(imagingObservation.CodeMeaning, QueryPredicate.LIKE);
				io.CodingSchemeDesignator = new QueryData(imagingObservation.CodingSchemeDesignator, QueryPredicate.LIKE);
                aimQueryParameters.ImQueryParameters.Add(io);
		    }
			foreach (ImagingObservationCharacteristic imagingObservation in _criteriaComponent.ImagingObservationCharacteristics)
			{
				AimImagingObservationCharacteristicQueryData ioc = new AimImagingObservationCharacteristicQueryData();
				ioc.CodeValue = new QueryData(imagingObservation.CodeValue, QueryPredicate.LIKE);
				ioc.CodeMeaning = new QueryData(imagingObservation.CodeMeaning, QueryPredicate.LIKE);
				ioc.CodingSchemeDesignator = new QueryData(imagingObservation.CodingSchemeDesignator, QueryPredicate.LIKE);
				aimQueryParameters.ImcQueryParameters.Add(ioc);
			}
			if (!string.IsNullOrEmpty(_criteriaComponent.User))
				aimQueryParameters.UserParameters.Add(new QueryData(_criteriaComponent.User.Trim(), QueryPredicate.LIKE));

			AIMSearchCommand searchCommand = new AIMSearchCommand(aimQueryParameters);
			base.PerformSearch(searchCommand);
		}

		protected override void OnQueryComplete()
		{
			base.OnQueryComplete();

			_criteriaComponent.Enabled = true;
		}
	}
}
