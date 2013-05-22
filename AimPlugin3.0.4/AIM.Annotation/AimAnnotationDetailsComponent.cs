//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Text;
using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;

using AIM.Annotation.Graphics;

namespace AIM.Annotation
{
	[ExtensionPoint]
	public sealed class AimAnnotationDetailsComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	[AssociateView(typeof(AimAnnotationDetailsComponentViewExtensionPoint))]
	public class AimAnnotationDetailsComponent : ApplicationComponent
	{
		private aim_dotnet.ImageAnnotation _selectedAnnotation;

		private readonly IDesktopWindow _desktopWindow;
		private IImageViewer _activeViewer;
		private bool _isImageViewerActive;

		public AimAnnotationDetailsComponent(IDesktopWindow desktopWindow)
		{
			_desktopWindow = desktopWindow;
		}

		internal static IShelf Launch(IDesktopWindow desktopWindow)
		{
			var component = new AimAnnotationDetailsComponent(desktopWindow);
			var shelf = LaunchAsShelf(
				desktopWindow,
				component,
				"AIM Annotation Details",
				"AimDetails",
				ShelfDisplayHint.DockRight | ShelfDisplayHint.DockAutoHide);

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
				_activeViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
				_activeViewer.EventBroker.TileSelected -= OnTileSelected;
			}

			_activeViewer = viewer;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected += OnImageBoxSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
				_activeViewer.EventBroker.TileSelected += OnTileSelected;
			}
			// Update selected graphic
			SetSelectedGraphic(_activeViewer == null || _activeViewer.SelectedPresentationImage == null
										? null
										: _activeViewer.SelectedPresentationImage.SelectedGraphic);

			IsImageViewerActive = _activeViewer != null;
		}

		private static IImageViewer CastToImageViewer(Workspace workspace)
		{
			IImageViewer viewer = null;
			if (workspace != null)
				viewer = ImageViewerComponent.GetAsImageViewer(workspace);

			return viewer;
		}

		private void OnImageBoxSelected(object sender, ImageBoxSelectedEventArgs e)
		{
			if (e.SelectedImageBox == null || e.SelectedImageBox.SelectedTile == null || e.SelectedImageBox.SelectedTile.PresentationImage == null)
				SetSelectedGraphic(null);
			else
				SetSelectedGraphic(e.SelectedImageBox.SelectedTile.PresentationImage.SelectedGraphic);
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			SetSelectedGraphic(e.SelectedGraphic);
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			if (e.SelectedTile != null)
			{
				if (e.SelectedTile.ParentImageBox.Tiles.Count > 1)
					SetSelectedGraphic(e.SelectedTile.PresentationImage == null ? null : e.SelectedTile.PresentationImage.SelectedGraphic);
			}
		}

		private void SetSelectedGraphic(ISelectableGraphic graphic)
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

		public aim_dotnet.ImageAnnotation SelectedAnnotation
		{
			get { return _selectedAnnotation; }
			set
			{
				if (_selectedAnnotation == value)
					return;

				_selectedAnnotation = value;

				NotifyPropertyChanged("AnatomicEntities");
				NotifyPropertyChanged("ImagingObservations");
				NotifyPropertyChanged("CalculationDescriptions");
				NotifyPropertyChanged("AllDetailsHtml");
			}
		}

		public IList<aim_dotnet.ICodeSequence> AnatomicEntities
		{
			get
			{
				if (SelectedAnnotation == null || SelectedAnnotation.AnatomyEntityCollection == null)
					return null;

				return SelectedAnnotation.AnatomyEntityCollection.ConvertAll(obs => obs as aim_dotnet.ICodeSequence).AsReadOnly();
			}
		}

		public IList<aim_dotnet.ICodeSequence> ImagingObservations
		{
			get
			{
				if (SelectedAnnotation == null || SelectedAnnotation.ImagingObservationCollection == null)
					return null;

				return SelectedAnnotation.ImagingObservationCollection.ConvertAll(obs => obs as aim_dotnet.ICodeSequence).AsReadOnly();
			}
		}

		public string[] CalculationDescriptions
		{
			get
			{
				if (SelectedAnnotation == null || SelectedAnnotation.CalculationCollection == null)
					return null;

				var sb = new StringBuilder();
				var lineFeed = Environment.NewLine + "    ";

				foreach (var calculation in SelectedAnnotation.CalculationCollection)
				{
					if (sb.Length > 0)
						sb.Append(Environment.NewLine);

					sb.AppendFormat("{0}/{1}:", calculation.CodeMeaning, calculation.Description);
					foreach (var calculationResult in calculation.CalculationResultCollection)
					{
						sb.Append(lineFeed);
						if (calculationResult.NumberOfDimensions > 1)
							sb.Append("<Multidimensional Result Value>");
						else
						{
							if (calculationResult.CalculationDataCollection.Count == 1 && calculationResult.CalculationDataCollection[0] != null)
								sb.AppendFormat("{0} {1}", calculationResult.CalculationDataCollection[0].Value, calculationResult.UnitOfMeasure);
							else
								sb.Append("<Cannot display non-scalar results>");
						}
					}
				}

				return sb.ToString().Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
			}
			set { }
		}

		public string AllDetailsHtml
		{
			get { return Tools.AimHtmlFormatter.GetAimHtml(SelectedAnnotation); }
		}
	}
}
