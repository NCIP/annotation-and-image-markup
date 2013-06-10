#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;

namespace SearchComponent
{
	[ExtensionPoint]
	public sealed class NBIASearchCriteriaComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	[AssociateView(typeof(NBIASearchCriteriaComponentViewExtensionPoint))]
	public class NBIASearchCriteriaComponent : ApplicationComponent
	{
		private string _patientId = "";
		private string _patientsName = "";
		private string _patientsSex = "";
		private DateTime? _patientsBirthDate = null;
		private string _project = "";
		private string _protocolId = "";
		private string _protocolName = "";
		private readonly List<string> _searchModalities;
		private string _siteName = "";
		private string _siteId = "";
		private string _sliceThickness = "";
		private string _studyInstanceUid = "";
		private bool _enabled = true;

		private readonly NBIASearchCoordinator _coordinator;

		internal NBIASearchCriteriaComponent(NBIASearchCoordinator coordinator)
		{
			_coordinator = coordinator;
			_coordinator.SetSearchCriteriaComponent(this);
			_searchModalities = new List<string>();
		}

		public string PatientId
		{
			get { return _patientId; }
			set
			{
				if (_patientId != value)
				{
					_patientId = value;
					NotifyPropertyChanged("PatientId");
				}
			}
		}

		public string PatientsName
		{
			get { return _patientsName; }
			set
			{
				if (_patientsName != value)
				{
					_patientsName = value;
					NotifyPropertyChanged("PatientsName");
				}
			}
		}

		public string PatientsSex
		{
			get { return _patientsSex; }
			set
			{
				if (_patientsSex != value)
				{
					_patientsSex = value;
					NotifyPropertyChanged("PatientsSex");
				}
			}
		}

		public DateTime? PatientsBirthDate
		{
			get { return _patientsBirthDate; }
			set
			{
				if (_patientsBirthDate != value)
				{
					_patientsBirthDate = value;
					NotifyPropertyChanged("PatientsBirthDate");
				}
			}
		}

		public string Project
		{
			get { return _project; }
			set
			{
				if (_project != value)
				{
					_project = value;
					NotifyPropertyChanged("Project");
				}
			}
		}

		public string ProtocolName
		{
			get { return _protocolName; }
			set
			{
				if (_protocolName != value)
				{
					_protocolName = value;
					NotifyPropertyChanged("ProtocolName");
				}
			}
		}

		public string ProtocolId
		{
			get { return _protocolId; }
			set
			{
				if (_protocolId != value)
				{
					_protocolId = value;
					NotifyPropertyChanged("ProtocolId");
				}
			}
		}

		public ICollection<string> AvailableSearchModalities
		{
			get { return StandardModalities.Modalities; }
		}

		public IList<string> SearchModalities
		{
			get { return _searchModalities; }
			set
			{
				_searchModalities.Clear();

				if (value != null)
					_searchModalities.AddRange(value);

				NotifyPropertyChanged("SearchModalities");
			}
		}
		
		public string SiteName
		{
			get { return _siteName; }
			set
			{
				if (_siteName != value)
				{
					_siteName = value;
					NotifyPropertyChanged("SiteName");
				}
			}
		}

		public string SiteId
		{
			get { return _siteId; }
			set
			{
				if (_siteId != value)
				{
					_siteId = value;
					NotifyPropertyChanged("SiteId");
				}
			}
		}

		public string SliceThickness
		{
			get { return _sliceThickness; }
			set
			{
				if (_sliceThickness != value)
				{
					_sliceThickness = value;
					NotifyPropertyChanged("SliceThickness");
				}
			}
		}

		public string StudyInstanceUid
		{
			get { return _studyInstanceUid; }
			set
			{
				if (_studyInstanceUid != value)
				{
					_studyInstanceUid = value;
					NotifyPropertyChanged("StudyInstanceUid");
				}
			}
		}

		public bool Enabled
		{
			get { return _enabled; }	
			set
			{
				if (_enabled != value)
				{
					_enabled = value;
					NotifyPropertyChanged("Enabled");
					NotifyPropertyChanged("CancelEnabled");
				}
			}
		}

		public bool CancelEnabled
		{
			get { return !Enabled; }	
		}

		public bool ResetEnabled
		{
			get { return Enabled; }
		}

		public void Search()
		{
			_coordinator.PerformSearch();
		}

		public void Cancel()
		{
			_coordinator.CancelSearch();
		}

		public void Reset()
		{
			this.PatientId = string.Empty;
			this.PatientsName = string.Empty;
			this.PatientsSex = string.Empty;
			this.PatientsBirthDate = null;

			this.Project = string.Empty;
			this.ProtocolName = string.Empty;
			this.ProtocolId = string.Empty;

			this.SearchModalities = null;
			this.SiteId = string.Empty;
			this.SiteName = string.Empty;

			this.SliceThickness = string.Empty;
			this.StudyInstanceUid = string.Empty;

			_coordinator.Reset();
		}
	}
}
