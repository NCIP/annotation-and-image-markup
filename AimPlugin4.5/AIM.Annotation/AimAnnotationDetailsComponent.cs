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

using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;

using AIM.Annotation.Graphics;

namespace AIM.Annotation
{
	/// <summary>
	/// Extension point for views onto <see cref="AimAnnotationDetailsComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class AimAnnotationDetailsComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// AimAnnotationDetailsComponents class.
	/// </summary>
	[AssociateView(typeof(AimAnnotationDetailsComponentViewExtensionPoint))]
	public class AimAnnotationDetailsComponent : ApplicationComponent
	{
		private AimManager.IAimAnnotationInstance _selectedAnnotation;
		private AimManager.IDataProvider _dataProvider;

		private readonly IDesktopWindow _desktopWindow;
		private IImageViewer _activeViewer;

		private bool _isImageViewerActive;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimAnnotationDetailsComponent(IDesktopWindow desktopWindow)
		{
			_desktopWindow = desktopWindow;
		}

		internal static IShelf Launch(IDesktopWindow desktopWindow)
		{
			AimAnnotationDetailsComponent component = new AimAnnotationDetailsComponent(desktopWindow);
			Shelf shelf = LaunchAsShelf(
				desktopWindow,
				component,
				"AIM Annotation Details",
				"AimDetails",
				ShelfDisplayHint.DockRight | ShelfDisplayHint.DockAutoHide);

			return shelf;
		}

		private void SetImageViewer(Workspace workspace)
		{
			IImageViewer viewer = CastToImageViewer(workspace);
			if (viewer == _activeViewer)
				return;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected -= OnImageBoxSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged -= OnGraphicSelectionChanged;
				_activeViewer.EventBroker.TileSelected -= OnTileSelected;
				_activeViewer.EventBroker.DisplaySetChanged -= OnDisplaySetChanged;
				_activeViewer.EventBroker.PresentationImageSelected -= OnPresentationImageSelected;
			}

			_activeViewer = viewer;

			if (_activeViewer != null)
			{
				_activeViewer.EventBroker.ImageBoxSelected += OnImageBoxSelected;
				_activeViewer.EventBroker.GraphicSelectionChanged += OnGraphicSelectionChanged;
				_activeViewer.EventBroker.TileSelected += OnTileSelected;
				_activeViewer.EventBroker.DisplaySetChanged += OnDisplaySetChanged;
				_activeViewer.EventBroker.PresentationImageSelected += OnPresentationImageSelected;
			}

			// Update selected graphic
			SetSelectedGraphic(_activeViewer == null || _activeViewer.SelectedPresentationImage == null
										? null
										: _activeViewer.SelectedPresentationImage.SelectedGraphic, "Image Viewer Changed");

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
				SetSelectedGraphic(null, "No image is selected");
			else
				SetSelectedGraphic(e.SelectedImageBox.SelectedTile.PresentationImage.SelectedGraphic, "An image is selected");
		}

		private void OnGraphicSelectionChanged(object sender, GraphicSelectionChangedEventArgs e)
		{
			SetSelectedGraphic(e.SelectedGraphic, e.SelectedGraphic == null ? null : (e.SelectedGraphic.ParentGraphic as IAimGraphic == null ? "IS NOT AIM!" : "IS AIM!"));
		}

		private void OnTileSelected(object sender, TileSelectedEventArgs e)
		{
			if (e.SelectedTile != null)
			{
				// NOTE: only do this if we have multiple tiles. For a 1x1 case, other events take care of 
				if (e.SelectedTile.ParentImageBox.Tiles.Count > 1)
					SetSelectedGraphic(e.SelectedTile.PresentationImage == null ? null : e.SelectedTile.PresentationImage.SelectedGraphic, "New Tile selected");
			}
		}
		
		private void OnDisplaySetChanged(object sender, DisplaySetChangedEventArgs displaySetChangedEventArgs)
		{
			// Display details for the newly selected AIM annotation if it's a part of selection
			if (displaySetChangedEventArgs.NewDisplaySet != null && displaySetChangedEventArgs.NewDisplaySet.Selected)
			{
				foreach (IPresentationImage presentationImage in displaySetChangedEventArgs.NewDisplaySet.PresentationImages)
				{
					if (presentationImage.SelectedGraphic != null && presentationImage.SelectedGraphic.Selected)
					{
						SetSelectedGraphic(presentationImage.SelectedGraphic, "Display set selected changed");
						break;
					}
				}
			}
			else if (displaySetChangedEventArgs.NewDisplaySet == null)
			{
				SetSelectedGraphic(null, "display set selection changed");
			}
		}

		private void OnPresentationImageSelected(object sender, PresentationImageSelectedEventArgs presentationImageSelectedEventArgs)
		{
			SetSelectedGraphic(
				presentationImageSelectedEventArgs.SelectedPresentationImage != null &&
				presentationImageSelectedEventArgs.SelectedPresentationImage.SelectedGraphic != null &&
				presentationImageSelectedEventArgs.SelectedPresentationImage.SelectedGraphic.Selected ?
				presentationImageSelectedEventArgs.SelectedPresentationImage.SelectedGraphic : null, "Presentation Image Selected");
		}

		private void SetSelectedGraphic(ISelectableGraphic graphic, string defaultText)
		{
			IAimGraphic aimGraphic = graphic == null || graphic.ParentGraphic == null
										? null
										: graphic.ParentGraphic as IAimGraphic;
			SelectedAnnotation = aimGraphic == null ? null : aimGraphic.AimAnnotation;
		}

		/// <summary>
		/// Called by the host to initialize the application component.
		/// </summary>
		public override void Start()
		{
			_desktopWindow.Workspaces.ItemActivationChanged += OnActiveWorkspaceChanged;

			SetImageViewer(_desktopWindow.ActiveWorkspace);

			base.Start();
		}

		/// <summary>
		/// Called by the host when the application component is being terminated.
		/// </summary>
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

		public AimManager.IAimAnnotationInstance SelectedAnnotation
		{
			get { return _selectedAnnotation; }
			set
			{
				if (_selectedAnnotation == value)
					return;

				_selectedAnnotation = value;
				_dataProvider = AimManager.AimManager.GetDataProvider(_selectedAnnotation);

				NotifyPropertyChanged("AnatomicEntities");
				NotifyPropertyChanged("ImagingObservations");
				NotifyPropertyChanged("CalculationDescriptions");
				NotifyPropertyChanged("AllDetailsHtml");
			}
		}

		public IList<TemplateTree.StandardValidTerm> AnatomicEntities
		{
			get
			{
				if (_dataProvider == null)
					return null;

				return _dataProvider.AnatomicEntities;
			}
		}

		public IList<TemplateTree.StandardValidTerm> ImagingObservations
		{
			get
			{
				if (_dataProvider == null)
					return null;

				return _dataProvider.ImagingObservations;
			}
		}

		//public IList<aim_dotnet.Calculation> Calculations
		//{
		//    get
		//    {
		//        if (SelectedAnnotation == null || SelectedAnnotation.CalculationCollection == null)
		//            return null;

		//        return SelectedAnnotation.CalculationCollection.AsReadOnly();
		//    }
		//}

		// Returns all calculation descriptions as an array of string for display
		public string[] CalculationDescriptions
		{
			get
			{
				if (_dataProvider == null)
					return null;

				return _dataProvider.CalculationDescriptions;
			}
			set { } // No op. Required for databinding
		}

		public string AllDetailsHtml
		{
			get { return AimManager.AimManager.Instance.GetAimAnnotationHtml(SelectedAnnotation); }
		}
	}
}
