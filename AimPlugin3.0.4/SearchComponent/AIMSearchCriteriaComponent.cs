//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;
using System.ComponentModel;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;

namespace SearchComponent
{
	[ExtensionPoint]
	public sealed class AIMSearchCriteriaComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	public enum ImagingObservationType
	{
		ImageAnnotation,
		AnnotationOfAnnotation
	}

	[AssociateView(typeof(AIMSearchCriteriaComponentViewExtensionPoint))]
	public class AIMSearchCriteriaComponent : ApplicationComponent
	{
		private readonly BindingList<AnatomicEntity> _anatomicEntities;
		private readonly BindingList<AnatomicEntityCharacteristic> _anatomicEntityCharacteristics;
		private readonly BindingList<ImagingObservation> _imagingObservations;
		private readonly BindingList<ImagingObservationCharacteristic> _imagingObservationCharacterisics;
		private string _studyInstanceUid = "";
		private string _user = "";
		private string _anatomicEntityCharacteristicQuantification = "";
		private ImagingObservationType _observationType;
		private bool _enabled = true;

		private readonly AIMSearchCoordinator _coordinator;

		internal AIMSearchCriteriaComponent(AIMSearchCoordinator coordinator)
		{
			_coordinator = coordinator;
			_coordinator.SetSearchCriteriaComponent(this);

			_anatomicEntities = new BindingList<AnatomicEntity>();
			_anatomicEntityCharacteristics = new BindingList<AnatomicEntityCharacteristic>();
			_imagingObservations = new BindingList<ImagingObservation>();
			_imagingObservationCharacterisics = new BindingList<ImagingObservationCharacteristic>();
		}

		public List<AnatomicEntity> GetAllAvailableEntities()
		{
			List <AnatomicEntity> entities = new List<AnatomicEntity>(AnatomicEntity.GetAllAvailableEntities());
			CollectionUtils.Remove(entities, delegate(AnatomicEntity entity) { return _anatomicEntities.Contains(entity); });
			return entities;
		}

		public List<ImagingObservation> GetAllAvailableObservations()
		{
			List<ImagingObservation> observations = new List<ImagingObservation>(ImagingObservation.GetAllAvailableObservations());
			CollectionUtils.Remove(observations, delegate(ImagingObservation observation) { return _imagingObservations.Contains(observation); });
			return observations;
		}

		public BindingList<AnatomicEntity> AnatomicEntities
		{
			get { return _anatomicEntities; }
		}

		public BindingList<AnatomicEntityCharacteristic> AnatomicEntityCharacteristics
		{
			get { return _anatomicEntityCharacteristics; }
		}

		public BindingList<ImagingObservation> ImagingObservations
		{
			get { return _imagingObservations; }
		}

		public BindingList<ImagingObservationCharacteristic> ImagingObservationCharacteristics
		{
			get { return _imagingObservationCharacterisics; }
		}

		public string StudyInstanceUid
		{
			get { return _studyInstanceUid; }
			set
			{
				if (value != _studyInstanceUid)
				{
					_studyInstanceUid = value;
					NotifyPropertyChanged("StudyInstanceUid");
				}
			}
		}

		public string AnatomicEntityCharacteristicQuantification
		{
			get { return _anatomicEntityCharacteristicQuantification; }
			set
			{
				_anatomicEntityCharacteristicQuantification = value;
				NotifyPropertyChanged("AnatomicEntityCharacteristicQuantification");
			}
		}

		public string User
		{
			get { return _user; }
			set 
			{ 
				_user = value;
				NotifyPropertyChanged("User");
			}
		}

		public bool ImageAnnotation
		{
			get { return _observationType == ImagingObservationType.ImageAnnotation; }
			set
			{
				if (value)
				{
					_observationType = ImagingObservationType.ImageAnnotation;
					NotifyPropertyChanged("AnnotationOfAnnotation");
					NotifyPropertyChanged("ImageAnnotation");
				}
			}
		}

		public bool AnnotationOfAnnotation
		{
			get { return _observationType == ImagingObservationType.AnnotationOfAnnotation; }
			set
			{
				if (value)
				{
					_observationType = ImagingObservationType.AnnotationOfAnnotation;
					NotifyPropertyChanged("ImageAnnotation");
					NotifyPropertyChanged("AnnotationOfAnnotation");
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
			this.StudyInstanceUid = string.Empty;
			this.User = string.Empty;

			_coordinator.Reset();
		}
	}
}
