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
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.StudyManagement;

using AIM.Annotation.Graphics;

namespace AIM.Annotation
{
	/// <summary>
	/// Extension point for views onto <see cref="AimAnnotationsListComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class AimAnnotationsListComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AimAnnotationsListComponent class.
	/// </summary>
	[AssociateView(typeof(AimAnnotationsListComponentViewExtensionPoint))]
	public class AimAnnotationsListComponent : ApplicationComponent
	{
		private readonly IDesktopWindow _desktopWindow;
		private IImageViewer _activeViewer;

		private aim_dotnet.ImageAnnotation _selectedAnnotation;

		private List<aim_dotnet.Annotation> _availableStudyAnnotations; // all annotations in the current study

		private bool _isImageViewerActive;
		private bool _isImageSelected;


		private event EventHandler _selectedStudyChanged;
		private event EventHandler _selectedImageChanged;
		private event EventHandler _selectedAnnotationChanged;

		public event EventHandler AvailableAnnotationsChanged;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimAnnotationsListComponent(IDesktopWindow desktopWindow)
		{
			_desktopWindow = desktopWindow;
		}

		public List<aim_dotnet.Annotation> AvailableAnnotations
		{
			get { return _availableStudyAnnotations; }
			set
			{
				if (_availableStudyAnnotations == value)
					return;

				_availableStudyAnnotations = value;

				EventsHelper.Fire(AvailableAnnotationsChanged, this, EventArgs.Empty);
				//NotifyPropertyChanged("AvailableAnnotations");
			}
		}

		public aim_dotnet.ImageAnnotation SelectedAnnotation
		{
			get { return _selectedAnnotation; }
			set
			{
				if (_selectedAnnotation == value)
					return;

				_selectedAnnotation = value;

				EventsHelper.Fire(_selectedAnnotationChanged, this, EventArgs.Empty);
				//NotifyPropertyChanged("SelectedAnnotation");
			}
		}

		public bool IsImageViewerActive
		{
			get { return _isImageViewerActive; }
			set
			{
				if (_isImageViewerActive == value)
					return;

				_isImageViewerActive = value;
				NotifyPropertyChanged("IsImageViewerActive");
			}
		}

		public bool IsImageSelected
		{
			get { return _isImageSelected; }
			set
			{
				if (_isImageSelected == value)
					return;

				_isImageSelected = value;
				NotifyPropertyChanged("IsImageSelected");
			}
		}

		public event EventHandler SelectedStudyChanged
		{
			add { _selectedStudyChanged += value;}
			remove { _selectedStudyChanged -= value; }
		}

		public event EventHandler SelectedImageChanged
		{
			add { _selectedImageChanged += value; }
			remove { _selectedImageChanged -= value; }
		}

		public event EventHandler SelectedAnnotationChanged
		{
			add { _selectedAnnotationChanged += value; }
			remove { _selectedAnnotationChanged -= value; }
		}

		internal static IShelf Launch(IDesktopWindow desktopWindow)
		{
			var component = new AimAnnotationsListComponent(desktopWindow);
			var shelf = LaunchAsShelf(
				desktopWindow,
				component,
				"Available AIM Annotations",
				"AimAnnotations",
				ShelfDisplayHint.DockLeft | ShelfDisplayHint.DockAutoHide);

			return shelf;
		}

		private void SetImageViewer(Workspace workspace)
		{
			var viewer = CastToImageViewer(workspace);
			if (viewer == _activeViewer)
				return;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected -= OnImageBoxSelected;
				_activeViewer.EventBroker.TileSelected -= OnTileSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
				_activeViewer.EventBroker.PresentationImageSelected -= OnPresentationImageSelected;
			}

			_activeViewer = viewer;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected += OnImageBoxSelected;
				_activeViewer.EventBroker.TileSelected += OnTileSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
				_activeViewer.EventBroker.PresentationImageSelected += OnPresentationImageSelected;
			}

			SetInitialSelections();
		}

		private static IImageViewer CastToImageViewer(Workspace workspace)
		{
			IImageViewer viewer = null;
			if (workspace != null)
				viewer = ImageViewerComponent.GetAsImageViewer(workspace);

			return viewer;
		}

		private void SetInitialSelections()
		{
			SetAvailableAnnotations();
			SetSelectedAnnotation(_activeViewer != null && _activeViewer.SelectedPresentationImage != null
										? _activeViewer.SelectedPresentationImage.SelectedGraphic
										: null);
			IsImageViewerActive = _activeViewer != null;

			EventsHelper.Fire(_selectedImageChanged, this, EventArgs.Empty);
		}

		private void OnImageBoxSelected(object sender, ImageBoxSelectedEventArgs e)
		{
			if (e.SelectedImageBox == null || e.SelectedImageBox.SelectedTile == null || e.SelectedImageBox.SelectedTile.PresentationImage == null)
				SetSelectedAnnotation(null);
			else
				SetSelectedAnnotation(e.SelectedImageBox.SelectedTile.PresentationImage.SelectedGraphic);
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			if (e.SelectedTile != null)
			{
				if (e.SelectedTile.ParentImageBox.Tiles.Count > 1)
					SetSelectedAnnotation(e.SelectedTile.PresentationImage == null ? null : e.SelectedTile.PresentationImage.SelectedGraphic);
			}
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			SetSelectedAnnotation(e.SelectedGraphic);
		}

		private void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs e)
		{
			SetSelectedAnnotation(e.SelectedPresentationImage == null ? null : e.SelectedPresentationImage.SelectedGraphic);
		}

		private void SetAvailableAnnotations()
		{
			if (_activeViewer == null)
			{
				AvailableAnnotations = null;
				return;
			}

			var studyUids = new HashSet<string>();
			foreach (var imageSet in _activeViewer.LogicalWorkspace.ImageSets)
			{
				foreach (var displaySet in imageSet.DisplaySets)
				{
					foreach (var image in displaySet.PresentationImages)
					{
						var imageSop = image as IImageSopProvider;
						if (imageSop != null)
							studyUids.Add(imageSop.ImageSop.StudyInstanceUid);
					}
				}
			}

			// Load & sort annotations by name
			var availableAnnotations = AimLoadHelper.LoadAimAnnotations(studyUids);
			AvailableAnnotations =
				availableAnnotations == null
					? null
					: CollectionUtils.Sort(availableAnnotations, (ann1, ann2) =>
						AimStudyFromAnnotation(ann1).Series.InstanceUID.CompareTo(AimStudyFromAnnotation(ann2).Series.InstanceUID));
		}

		private void SetSelectedAnnotation(ISelectableGraphic graphic)
		{
			var aimGraphic = graphic == null || graphic.ParentGraphic == null
										? null
										: graphic.ParentGraphic as IAimGraphic;
			SelectedAnnotation = aimGraphic == null ? null : aimGraphic.AimAnnotation;
		}

		public override void Start()
		{
			_desktopWindow.Workspaces.ItemActivationChanged += OnActiveWorkspaceChanged;
			SetImageViewer(_desktopWindow.ActiveWorkspace);

			base.Start();
		}

		public override void Stop()
		{
			_desktopWindow.Workspaces.ItemActivationChanged -= OnActiveWorkspaceChanged;
			SetImageViewer(null);

			base.Stop();
		}

		private void OnActiveWorkspaceChanged(object sender, ItemEventArgs<Workspace> e)
		{
			SetImageViewer(e.Item);

			if (_activeViewer != null && _activeViewer.PhysicalWorkspace != null)
				_activeViewer.PhysicalWorkspace.LayoutCompleted += OnPhysicalWorkspaceLayoutCompleted;
		}

		private void OnPhysicalWorkspaceLayoutCompleted(object sender, EventArgs e)
		{
			SetInitialSelections();
			_activeViewer.PhysicalWorkspace.LayoutCompleted -= OnPhysicalWorkspaceLayoutCompleted;
		}

		public void ShowImageWithAnnotation(string aimUid)
		{
			if (_activeViewer == null)
				return;

			aim_dotnet.Annotation annotationToShow = null;
			foreach (var annotation in AvailableAnnotations)
			{
				if (annotation.UniqueIdentifier == aimUid)
				{
					annotationToShow = annotation;
					break;
				}
			}

			if (annotationToShow == null)
			{
				_activeViewer.DesktopWindow.ShowMessageBox("Could not locate annotation (UID = " + aimUid + ").", MessageBoxActions.Ok);
				return;
			}

			var studyToOpen = AimStudyFromAnnotation(annotationToShow);
			if (studyToOpen == null)
			{
				_activeViewer.DesktopWindow.ShowMessageBox("Error reading image information (annotation UID = " + aimUid + ").", MessageBoxActions.Ok);
				return;
			}

			// Search displayed images first
			foreach (var imageBox in _activeViewer.PhysicalWorkspace.ImageBoxes)
			{
				if (imageBox.DisplaySet == null || imageBox.DisplaySet.PresentationImages == null || imageBox.DisplaySet.PresentationImages.Count == 0)
					continue;

				var imageSopProvider = imageBox.DisplaySet.PresentationImages[0] as IImageSopProvider;
				if (imageSopProvider == null)
					continue;

				if (imageSopProvider.ImageSop.StudyInstanceUid == studyToOpen.InstanceUID &&
				    imageSopProvider.ImageSop.SeriesInstanceUid == studyToOpen.Series.InstanceUID)
				{
					foreach (var presentationImage in imageBox.DisplaySet.PresentationImages)
					{
						imageSopProvider = presentationImage as IImageSopProvider;
						if (imageSopProvider == null)
							continue;
						if (imageSopProvider.ImageSop.SopInstanceUid == studyToOpen.Series.ImageCollection[0].SopInstanceUID)
						{
							try
							{
								imageBox.TopLeftPresentationImage = presentationImage;
								imageBox.Tiles[0].Select();
								SelectAimGraphic(presentationImage, aimUid);
								imageBox.Draw();

								return;
							}
							catch (Exception ex)
							{
								ExceptionHandler.Report(ex, _desktopWindow);
							}
						}
					}
				}
			}

			// Search other available images
			foreach (var imageSet in _activeViewer.LogicalWorkspace.ImageSets)
			{
				foreach (var displaySet in imageSet.DisplaySets)
				{
					if (displaySet.PresentationImages.Count > 0)
					{
						var imageSopProvider = displaySet.PresentationImages[0] as IImageSopProvider;
						if (imageSopProvider == null)
							continue;

						if (imageSopProvider.ImageSop.StudyInstanceUid == studyToOpen.InstanceUID &&
							imageSopProvider.ImageSop.SeriesInstanceUid == studyToOpen.Series.InstanceUID)
						{
							foreach (var presentationImage in displaySet.PresentationImages)
							{
								imageSopProvider = presentationImage as IImageSopProvider;
								if (imageSopProvider == null)
									continue;
								if (imageSopProvider.ImageSop.SopInstanceUid == studyToOpen.Series.ImageCollection[0].SopInstanceUID)
								{
									try
									{
										var targetImageBox = _activeViewer.PhysicalWorkspace.SelectedImageBox ??
										                           (_activeViewer.PhysicalWorkspace.ImageBoxes.Count > 0 ? _activeViewer.PhysicalWorkspace.ImageBoxes[0] : null);
										if (targetImageBox == null)
										{
											_activeViewer.DesktopWindow.ShowMessageBox("Failed to find available display", MessageBoxActions.Ok);
											Platform.Log(LogLevel.Error, "Failed to locate a target ImageBox to display requested annotation (aimUID=" + aimUid + ").");
											return;
										}

										var targetDisplaySet = displaySet.CreateFreshCopy();
										var targetPresentationImage = FindRequiredImage(targetDisplaySet.PresentationImages,
										                                                               studyToOpen.InstanceUID, studyToOpen.Series.InstanceUID,
										                                                               studyToOpen.Series.ImageCollection[0].SopInstanceUID);
										if (targetPresentationImage == null)
										{
											_activeViewer.DesktopWindow.ShowMessageBox("Failed to find required image", MessageBoxActions.Ok);
											Platform.Log(LogLevel.Error, "Failed to locate a target ImageBox to display requested annotation (aimUID=" + aimUid + ").");
											return;
										}

										targetImageBox.DisplaySet = targetDisplaySet;
										targetImageBox.TopLeftPresentationImage = targetPresentationImage;
										targetImageBox.Tiles[0].Select();
										SelectAimGraphic(targetPresentationImage, aimUid);
										targetImageBox.Draw();

										return;
									}
									catch (Exception ex)
									{
										ExceptionHandler.Report(ex, _desktopWindow);
									}
								}
							}
						}
					}
				}
			}
		}

		private IPresentationImage FindRequiredImage(PresentationImageCollection images, string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid)
		{
			return CollectionUtils.SelectFirst(
				images, image =>
				        	{
				        		var imageSopProvider = image as IImageSopProvider;
				        		return imageSopProvider != null && imageSopProvider.ImageSop.StudyInstanceUid == studyInstanceUid &&
				        		       imageSopProvider.ImageSop.SeriesInstanceUid == seriesInstanceUid && imageSopProvider.ImageSop.SopInstanceUid == sopInstanceUid;
				        	});
		}

		private void SelectAimGraphic(IPresentationImage presentationImage, string aimUid)
		{
			var imageGraphicsProvider = presentationImage as IOverlayGraphicsProvider;
			if (imageGraphicsProvider != null)
			{
				foreach (var graphic in imageGraphicsProvider.OverlayGraphics)
				{
					var aimGraphic = graphic as IAimGraphic;
					if (aimGraphic != null && aimGraphic.AimAnnotation.UniqueIdentifier == aimUid)
					{
						var decoratorGraphic = aimGraphic as IDecoratorGraphic;
						if (decoratorGraphic != null)
						{
							presentationImage.SelectedGraphic = decoratorGraphic.DecoratedGraphic as ISelectableGraphic;
							presentationImage.FocussedGraphic = decoratorGraphic.DecoratedGraphic as IFocussableGraphic;
							if (presentationImage.SelectedGraphic != null)
								presentationImage.SelectedGraphic.Selected = true;
							break;
						}
					}
				}
			}
		}

		private aim_dotnet.ImageStudy AimStudyFromAnnotation(aim_dotnet.Annotation annotation)
		{
			var imageAnnotation = annotation as aim_dotnet.ImageAnnotation;

			if (imageAnnotation == null || imageAnnotation.ImageReferenceCollection.Count == 0)
				return null;

			var dicomImageReference = imageAnnotation.ImageReferenceCollection[0] as aim_dotnet.DICOMImageReference;
			if(dicomImageReference == null)
				return null;

			if (dicomImageReference.Study == null || dicomImageReference.Study.Series == null ||
				dicomImageReference.Study.Series.ImageCollection == null || dicomImageReference.Study.Series.ImageCollection.Count == 0)
				return null;

			return dicomImageReference.Study;
		}

		public string GetSeriesUIDFromAimAnnotation(aim_dotnet.Annotation annotation)
		{
			return AimStudyFromAnnotation(annotation).Series.InstanceUID;
		}

		public Series GetSeriesFromUID(string seriesUID)
		{
			if (_activeViewer == null)
				return null;

			return _activeViewer.StudyTree.GetSeries(seriesUID);
		}
	}
}
