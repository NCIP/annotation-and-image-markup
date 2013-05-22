//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using DataServiceUtil;

namespace SearchComponent
{
	internal partial class NBIASearchCoordinator : SearchCoordinator<NBIASearchResult>
	{
		private NBIASearchCriteriaComponent _criteriaComponent;

		public NBIASearchCoordinator()
		{}

		public void SetSearchCriteriaComponent(NBIASearchCriteriaComponent criteriaComponent)
		{
			_criteriaComponent = criteriaComponent;
		}

		public void PerformSearch()
		{
			_criteriaComponent.Enabled = false;

			NBIAQueryParameters queryParameters = new NBIAQueryParameters();
			queryParameters.StudyInstanceUID = this.CreateQueryDataForLikePredicate(_criteriaComponent.StudyInstanceUid);
			queryParameters.PatientId = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientId);
			queryParameters.PatientName = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientsName);
			queryParameters.PatientSex = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientsSex);
			if (_criteriaComponent.PatientsBirthDate.HasValue)
			{
				string bdValue = _criteriaComponent.PatientsBirthDate.Value.ToString("yyyy-MM-dd hh:mm:ss.f");
				queryParameters.PatientBirthDate = new QueryData(bdValue, QueryPredicate.LIKE);
			}
			queryParameters.ProjectName = this.CreateQueryDataForLikePredicate(_criteriaComponent.Project);
			queryParameters.ProtocolId = this.CreateQueryDataForLikePredicate(_criteriaComponent.ProtocolId);
			queryParameters.ProtocolName = this.CreateQueryDataForLikePredicate(_criteriaComponent.ProtocolName);
			queryParameters.SiteId = this.CreateQueryDataForLikePredicate(_criteriaComponent.SiteId);
			queryParameters.SiteName = this.CreateQueryDataForLikePredicate(_criteriaComponent.SiteName);
			if (_criteriaComponent.SearchModalities.Count > 0)
				queryParameters.Modality = new QueryData(_criteriaComponent.SearchModalities[0], QueryPredicate.EQUAL_TO);
			if (!string.IsNullOrEmpty(_criteriaComponent.SliceThickness))
				queryParameters.SliceThickness = new QueryData(_criteriaComponent.SliceThickness, QueryPredicate.GREATER_THAN_EQUAL_TO);
			QueryForStudiesCommand searchCommand = new QueryForStudiesCommand(queryParameters);
			base.PerformSearch(searchCommand);
		}

		protected override void OnQueryComplete()
		{
			base.OnQueryComplete();

			_criteriaComponent.Enabled = true;
		}

		private QueryData CreateQueryDataForLikePredicate(string input)
		{
			if (string.IsNullOrEmpty((input ?? "").Trim()))
				return null;

			return new QueryData(input.Trim(), QueryPredicate.LIKE);
		}
	}
}
