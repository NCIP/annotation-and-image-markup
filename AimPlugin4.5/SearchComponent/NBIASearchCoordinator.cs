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

			// Get user parameters
			NBIAQueryParameters queryParameters = new NBIAQueryParameters();
			// Study
			queryParameters.StudyInstanceUID = this.CreateQueryDataForLikePredicate(_criteriaComponent.StudyInstanceUid);
			// Patient
			queryParameters.PatientId = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientId);
			queryParameters.PatientName = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientsName);
			queryParameters.PatientSex = this.CreateQueryDataForLikePredicate(_criteriaComponent.PatientsSex);
			if (_criteriaComponent.PatientsBirthDate.HasValue)
			{
				string bdValue = _criteriaComponent.PatientsBirthDate.Value.ToString("yyyy-MM-dd hh:mm:ss.f");
				queryParameters.PatientBirthDate = new QueryData(bdValue, QueryPredicate.LIKE);
			}
			// Trial Data Provenance
			queryParameters.ProjectName = this.CreateQueryDataForLikePredicate(_criteriaComponent.Project);
			// Clinical Trial Protocol
			queryParameters.ProtocolId = this.CreateQueryDataForLikePredicate(_criteriaComponent.ProtocolId);
			queryParameters.ProtocolName = this.CreateQueryDataForLikePredicate(_criteriaComponent.ProtocolName);
			// Clinical Trial Site
			queryParameters.SiteId = this.CreateQueryDataForLikePredicate(_criteriaComponent.SiteId);
			queryParameters.SiteName = this.CreateQueryDataForLikePredicate(_criteriaComponent.SiteName);
			// Series
			if (_criteriaComponent.SearchModalities.Count > 0)
				queryParameters.Modality = new QueryData(_criteriaComponent.SearchModalities[0], QueryPredicate.EQUAL_TO);
			// Image
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
