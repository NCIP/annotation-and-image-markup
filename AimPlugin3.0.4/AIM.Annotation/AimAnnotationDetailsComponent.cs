#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

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
