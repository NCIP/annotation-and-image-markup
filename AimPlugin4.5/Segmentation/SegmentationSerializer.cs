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

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod;
using ClearCanvas.Dicom.Iod.FunctionalGroups;
using ClearCanvas.Dicom.Iod.Macros;
using ClearCanvas.Dicom.Iod.Modules;
using ClearCanvas.Dicom.Iod.Sequences;
using ClearCanvas.Dicom.Utilities;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Common;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.Imaging;
using ClearCanvas.ImageViewer.Mathematics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.DICOM;
using Segmentation.DICOM.Iods;
using Segmentation.Graphics;
using Segmentation.Tree;
using ReferencedSeriesSequenceIod = Segmentation.DICOM.Iods.ReferencedSeriesSequenceIod;

namespace Segmentation
{
	public delegate IPresentationImage SegmentationSerializerCallback(string sopInstanceUid, int frameNumber);

	public class SegmentationSerializer
	{
		private readonly PrototypeSopInstanceFactory _sopInstanceFactory = new PrototypeSopInstanceFactory();
		private readonly SegmentationDocument _segDocument;

		public SegmentationSerializer(SegmentationDocument segDocument)
		{
			Platform.CheckForNullReference(segDocument, "segDocument");

			_segDocument = segDocument;
		}

		public DicomFile Serialize(SegmentationSerializerCallback callback)
		{
			Platform.CheckForNullReference(callback, "callback");

			Debug.Assert(!_segDocument.Saved, "Cannot serialize previously saved document");

			// TODO: validate that all Segs are coming from the same study!

			IPresentationImage firstIPresentationImage = null;
			if (_segDocument.Segs != null)
			{
				var oneSeg = _segDocument.Segs.FirstOrDefault(item => item != null && item.SegGraphics != null && item.SegGraphics.OfType<PolygonalRoiSegGraphic>().Any());
				if (oneSeg != null)
				{
					var polyGraphic = oneSeg.SegGraphics.OfType<PolygonalRoiSegGraphic>().First();
					firstIPresentationImage = callback(polyGraphic.ImageSopInstanceUid, polyGraphic.ImageFrameNumber);
				}
			}
			var firstImageSopProvider = firstIPresentationImage as IImageSopProvider;
			if (firstImageSopProvider == null)
				return null;

			var sourceSop = firstImageSopProvider.ImageSop; // source of the common DICOM attributes
			var dicomFile = _sopInstanceFactory.CreateFile(sourceSop);

			// NOTE. These modules are initialized by the factory:
			// patient IE
			// - PatientModule
			// - ClinicalTrialSubjectModule
			// study IE
			// - GeneralStudyModule
			// - PatientStudyModule
			// - ClinicalTrialStudyModule
			// equipment IE
			// - GeneralEquipmentModule

			// Data values
			const int instanceNumber = 1;
			var contentDateTime = DateTime.Now;

			var segDocumentIod = new SegmentationDocumentIod(dicomFile.DataSet);

			// PatientModule
			var patientModule = segDocumentIod.PatientModuleIod;
			// patientModule.PatientBreedDescription = null; // bug in CC code
			patientModule.DicomAttributeProvider[DicomTags.PatientBreedDescription].SetEmptyValue();

			// GeneralEquipmentModule
			var generalEquipmentModuleIod = segDocumentIod.GeneralEquipmentModuleIod;
			generalEquipmentModuleIod.DeviceSerialNumber = EnvironmentUtilities.MachineIdentifier;

			// GeneralSeriesModule
			var srcGeneralSeriesModuleIod = new GeneralSeriesModuleIod(sourceSop.DataSource);
			var generalSeriesModuleIod = segDocumentIod.GeneralSeriesModuleIod;
			generalSeriesModuleIod.SeriesDescription = _segDocument.SeriesDescription;
			generalSeriesModuleIod.SeriesNumber = _segDocument.SeriesNumber;
			generalSeriesModuleIod.Modality = Modality.Seg;
			generalSeriesModuleIod.SeriesInstanceUid = DicomUid.GenerateUid().UID;
			generalSeriesModuleIod.Laterality = srcGeneralSeriesModuleIod.Laterality;
			generalSeriesModuleIod.SeriesDateTime = _segDocument.CreationDateTime;
			generalSeriesModuleIod.PerformingPhysiciansName = srcGeneralSeriesModuleIod.PerformingPhysiciansName;
			generalSeriesModuleIod.PerformingPhysicianIdentificationSequence = srcGeneralSeriesModuleIod.PerformingPhysicianIdentificationSequence;
			generalSeriesModuleIod.ProtocolName = srcGeneralSeriesModuleIod.ProtocolName;
			{
				// General Description Code Sequence is missing from the GeneralSeriesModuleIod implementation
				var seriesDescriptionCodeSequence = new CodeSequenceMacro
					{
						CodeValue = "113076",
						CodeMeaning = "Segmentation",
						CodingSchemeDesignator = "DCM"
					};
				var result = new[] { seriesDescriptionCodeSequence.DicomSequenceItem };

				generalSeriesModuleIod.DicomAttributeProvider[DicomTags.SeriesDescriptionCodeSequence].Values = result;
			}
			string userDicomName = null;
			if (_segDocument.UserInfo != null && !string.IsNullOrEmpty(_segDocument.UserInfo.Name))
			{
				userDicomName = FormatDicomName(_segDocument.UserInfo.Name);
				if (userDicomName != null)
					generalSeriesModuleIod.OperatorsName = userDicomName;

				// NOTE: Login name is being ignored for now
			}
			generalSeriesModuleIod.BodyPartExamined = srcGeneralSeriesModuleIod.BodyPartExamined;
			generalSeriesModuleIod.PatientPosition = srcGeneralSeriesModuleIod.PatientPosition;
			generalSeriesModuleIod.RequestAttributesSequence = srcGeneralSeriesModuleIod.RequestAttributesSequence;
			//generalSeriesModuleIod.AnatomicalOrientationType = srcGeneralSeriesModuleIod.AnatomicalOrientationType;  // Not needed

			// FrameOfReferenceModule
			var srcFrameOfReferenceModuleIod = new FrameOfReferenceModuleIod(sourceSop.DataSource);
			segDocumentIod.FrameOfReferenceModuleIod.FrameOfReferenceUid = srcFrameOfReferenceModuleIod.FrameOfReferenceUid;
			segDocumentIod.FrameOfReferenceModuleIod.PositionReferenceIndicator = srcFrameOfReferenceModuleIod.PositionReferenceIndicator;

			// Initialize Segmentation Image Module first
			var segmentationImageModuleIod = segDocumentIod.SegmentationImageModuleIod;
			segmentationImageModuleIod.InitializeAttributes();

			// General Image Module and Segmentation Image Module
			var srcGeneralImageModuleIod = new GeneralImageModuleIod(sourceSop.DataSource);
			var generalImageModuleIod = segDocumentIod.GeneralImageModuleIod;
			generalImageModuleIod.InstanceNumber = instanceNumber;
			generalImageModuleIod.PatientOrientation = srcGeneralImageModuleIod.PatientOrientation;
			generalImageModuleIod.ContentDateTime = contentDateTime;
			generalImageModuleIod.ImageType = "DERIVED\\PRIMARY";
			generalImageModuleIod.AcquisitionNumber = srcGeneralImageModuleIod.AcquisitionNumber;
			generalImageModuleIod.AcquisitionDateTime = srcGeneralImageModuleIod.AcquisitionDateTime;
			generalImageModuleIod.QualityControlImage = srcGeneralImageModuleIod.QualityControlImage;
			generalImageModuleIod.BurnedInAnnotation = srcGeneralImageModuleIod.BurnedInAnnotation;
			generalImageModuleIod.RecognizableVisualFeatures = srcGeneralImageModuleIod.RecognizableVisualFeatures;
			generalImageModuleIod.LossyImageCompression = srcGeneralImageModuleIod.LossyImageCompression.HasValue && srcGeneralImageModuleIod.LossyImageCompression.Value;
			generalImageModuleIod.LossyImageCompressionMethod = srcGeneralImageModuleIod.LossyImageCompressionMethod;
			generalImageModuleIod.LossyImageCompressionRatio = srcGeneralImageModuleIod.LossyImageCompressionRatio;
			generalImageModuleIod.IrradiationEventUid = srcGeneralImageModuleIod.IrradiationEventUid;

			// Image Pixel Module and Segmentation Image Module
			var srcImagePixelModule = new ImagePixelMacroIod(sourceSop.DataSource);
			var imagePixelModule = segDocumentIod.ImagePixelModuleIod;
			imagePixelModule.Rows = srcImagePixelModule.Rows; // same height as the the image
			imagePixelModule.Columns = srcImagePixelModule.Columns; // same width as the image
			//imagePixelModule.PixelAspectRatio = srcImagePixelModule.PixelAspectRatio; // same as the image

			// Continue initialization of non-default values for the Segmentation Image Module
			segmentationImageModuleIod.ContentLabel = SanitizeDicomCsValue(_segDocument.ContentLabel);
			if (!string.IsNullOrEmpty(userDicomName))
				segmentationImageModuleIod.ContentCreatorsName = userDicomName;
			segmentationImageModuleIod.SegmentationType = SegmentationType.BINARY;

			// Per segmentation and per frame item initialization
			var docHasOneFrame = _segDocument.Segs.Where(item => item != null && item.SegGraphics != null).Sum(seg => seg.SegGraphics.OfType<PolygonalRoiSegGraphic>().Count()) == 1;
			var docHasOneSeg = _segDocument.Segs.Count(item => item != null && item.SegGraphics != null && item.SegGraphics.OfType<PolygonalRoiSegGraphic>().Any()) == 1;
			var multiFrameDimensionsModuleIod = segDocumentIod.MultiFrameDimensionModuleIod;
			multiFrameDimensionsModuleIod.InitializeAttributes();
			var segmentSequenceItems = new List<SegmentSequence>();
			var dimensionIndexSequenceItems = new List<DimensionIndexSequenceItem>();
			var dimensionOrganizationSequenceItems = new List<DimensionOrganizationSequenceItem>();
			var multiFrameFunctionalGroupsModuleIod = segDocumentIod.MultiFrameFunctionalGroupsModuleIod;
			multiFrameFunctionalGroupsModuleIod.InitializeAttributes();
			var perFrameFunctionalGroupSequenceItems = new List<FunctionalGroupsSequenceItem>();
			var frameBytesList = new List<byte[]>(); // list of pixel data for each frame
			var seriesUidToSopClassUidToSopInstanceUid = new Dictionary<string, Dictionary<string, HashSet<string>>>();
			var segmentNumber = 0;
			foreach (var seg in _segDocument.Segs)
			{
				segmentNumber++;
				Debug.Assert(segmentNumber == 1, "We're only supposed to create one Segment per document for now");

				// Segment Sequence initialization
				var segmentSequenceItemIod = segmentationImageModuleIod.CreateSegmentSequence();
				segmentSequenceItemIod.SegmentNumber = segmentNumber;
				segmentSequenceItemIod.SegmentLabel = seg.Label;
				segmentSequenceItemIod.SegmentDescription = seg.Description;
				segmentSequenceItemIod.SegmentAlgorithmType = "MANUAL";

				#region Category, Type, Anatomic Region, Anatomic Region Modifier

				var selectedCategory = seg.SelectedCategory;
				if (selectedCategory != null)
				{
					// Category
					var segmentedPropertyCategoryCodeSequenceItem = segmentSequenceItemIod.CreateSegmentedPropertyCategoryCodeSequence();
					segmentedPropertyCategoryCodeSequenceItem.CodeValue = selectedCategory.CodeValue;
					segmentedPropertyCategoryCodeSequenceItem.CodeMeaning = selectedCategory.CodeMeaning;
					segmentedPropertyCategoryCodeSequenceItem.CodingSchemeDesignator = selectedCategory.CodingSchemeDesignator;
					//if (!string.IsNullOrEmpty(selectedCategory.CodingSchemeVersion))
					//    segmentedPropertyCategoryCodeSequenceItem.CodingSchemeVersion = selectedCategory.CodingSchemeVersion;
					segmentSequenceItemIod.SegmentedPropertyCategoryCodeSequence = new[] { segmentedPropertyCategoryCodeSequenceItem };

					// Type
					if (selectedCategory.SelectedType != null)
					{
						var segmentedPropertyTypeCodeSequenceItem = segmentSequenceItemIod.CreateSegmentedPropertyTypeCodeSequence();
						segmentedPropertyTypeCodeSequenceItem.CodeValue = selectedCategory.SelectedType.CodeValue;
						segmentedPropertyTypeCodeSequenceItem.CodeMeaning = selectedCategory.SelectedType.CodeMeaning;
						segmentedPropertyTypeCodeSequenceItem.CodingSchemeDesignator = selectedCategory.SelectedType.CodingSchemeDesignator;
						//if (!string.IsNullOrEmpty(selectedCategory.SelectedType.CodingSchemeVersion))
						//    segmentedPropertyTypeCodeSequenceItem.CodingSchemeVersion = selectedCategory.SelectedType.CodingSchemeVersion;

						// Type modifier
						if (selectedCategory.SelectedType.SelectedTypeModifier != null)
						{
							var segmentedPropertyTypeModifierCodeSequenceItem = new CodeSequenceMacro();
							segmentedPropertyTypeModifierCodeSequenceItem.CodeValue = selectedCategory.SelectedType.SelectedTypeModifier.CodeValue;
							segmentedPropertyTypeModifierCodeSequenceItem.CodeMeaning = selectedCategory.SelectedType.SelectedTypeModifier.CodeMeaning;
							segmentedPropertyTypeModifierCodeSequenceItem.CodingSchemeDesignator = selectedCategory.SelectedType.SelectedTypeModifier.CodingSchemeDesignator;
							//if (!string.IsNullOrEmpty(selectedCategory.SelectedType.SelectedTypeModifier.CodingSchemeVersion))
							//    segmentedPropertyTypeModifierCodeSequenceItem.CodingSchemeVersion = selectedCategory.SelectedType.SelectedTypeModifier.CodingSchemeVersion;

							segmentedPropertyTypeCodeSequenceItem.SegmentedPropertyTypeModifierCodeSequence = new[] {segmentedPropertyTypeModifierCodeSequenceItem};
						}
						segmentSequenceItemIod.SegmentedPropertyTypeCodeSequence = new[] { segmentedPropertyTypeCodeSequenceItem };
					}

					// Anatomic Region
					var selectedAnatomicRegion = selectedCategory.SelectedAnatomicRegion;
					if (selectedAnatomicRegion != null)
					{
						var anatomicRegionSequenceItem = segmentSequenceItemIod.CreateAnatomicRegionSequence();
						anatomicRegionSequenceItem.CodeValue = selectedAnatomicRegion.CodeValue;
						anatomicRegionSequenceItem.CodeMeaning = selectedAnatomicRegion.CodeMeaning;
						anatomicRegionSequenceItem.CodingSchemeDesignator = selectedAnatomicRegion.CodingSchemeDesignator;
						//if (!string.IsNullOrEmpty(selectedAnatomicRegion.CodingSchemeVersion))
						//    anatomicRegionSequenceItem.CodingSchemeVersion = selectedAnatomicRegion.CodingSchemeVersion;

						// Anatomic region Modifier
						if (selectedAnatomicRegion.SelectedAnatomicRegionModifier != null)
						{
							var anatomicRegionModifierSequenceItem = new CodeSequenceMacro();
							anatomicRegionModifierSequenceItem.CodeValue = selectedAnatomicRegion.SelectedAnatomicRegionModifier.CodeValue;
							anatomicRegionModifierSequenceItem.CodeMeaning = selectedAnatomicRegion.SelectedAnatomicRegionModifier.CodeMeaning;
							anatomicRegionModifierSequenceItem.CodingSchemeDesignator = selectedAnatomicRegion.SelectedAnatomicRegionModifier.CodingSchemeDesignator;
							//if (!string.IsNullOrEmpty(selectedAnatomicRegion.SelectedAnatomicRegionModifier.CodingSchemeVersion))
							//    anatomicRegionModifierSequenceItem.CodingSchemeVersion = selectedAnatomicRegion.SelectedAnatomicRegionModifier.CodingSchemeVersion;

							anatomicRegionSequenceItem.AnatomicRegionModifierSequence = new[] { anatomicRegionModifierSequenceItem };
						}
						segmentSequenceItemIod.AnatomicRegionSequence = new[] { anatomicRegionSequenceItem };
					}
				}

				#endregion

				segmentSequenceItemIod.RecomendedDisplayCIELabValue = LabColorHelpers.RgbColorToCIELabColor(seg.Color);
				segmentSequenceItems.Add(segmentSequenceItemIod);

				// Dimension Organization Sequence item
				var dimensionOrganizationUid = DicomUid.GenerateUid().UID;
				var dimensionOrganizationSequenceItem = multiFrameDimensionsModuleIod.CreateDimensionOrganizationSequenceItem();
				dimensionOrganizationSequenceItem.DimensionOrganizationUid = dimensionOrganizationUid;
				dimensionOrganizationSequenceItems.Add(dimensionOrganizationSequenceItem);

				// Dimension Index Sequence items
				var dimensionIndexSequenceItem1 = multiFrameDimensionsModuleIod.CreateDimensionIndexSequenceItem();
				dimensionIndexSequenceItem1.DimensionIndexPointer = DicomTags.StackId;
				dimensionIndexSequenceItem1.FunctionalGroupPointer = DicomTags.FrameContentSequence;
				dimensionIndexSequenceItem1.DimensionOrganizationUid = dimensionOrganizationUid;
				dimensionIndexSequenceItem1.DimensionDescriptionLabel = "Stack ID";
				dimensionIndexSequenceItems.Add(dimensionIndexSequenceItem1);
				var dimensionIndexSequenceItem2 = multiFrameDimensionsModuleIod.CreateDimensionIndexSequenceItem();
				dimensionIndexSequenceItem2.DimensionIndexPointer = DicomTags.InStackPositionNumber;
				dimensionIndexSequenceItem2.FunctionalGroupPointer = DicomTags.FrameContentSequence;
				dimensionIndexSequenceItem2.DimensionOrganizationUid = dimensionOrganizationUid;
				dimensionIndexSequenceItem2.DimensionDescriptionLabel = "In Stack Position Number";
				dimensionIndexSequenceItems.Add(dimensionIndexSequenceItem2);

				var inStackPositionIndex = 0;

				var presentationImagePolygons = new Dictionary<IPresentationImage, List<PolygonalRoiSegGraphic>>();
				foreach (var polygonalSegGraphic in seg.SegGraphics.OfType<PolygonalRoiSegGraphic>())
				{
					var poly = polygonalSegGraphic.PolygonalRoiGraphic.Roi as PolygonalRoi;
					if (poly != null)
					{
						var currentPresentationImage = callback(polygonalSegGraphic.ImageSopInstanceUid, polygonalSegGraphic.ImageFrameNumber);
						if (presentationImagePolygons.ContainsKey(currentPresentationImage))
							presentationImagePolygons[currentPresentationImage].Add(polygonalSegGraphic);
						else
							presentationImagePolygons.Add(poly.PresentationImage, new List<PolygonalRoiSegGraphic> { polygonalSegGraphic });
					}
					else
					{
						Debug.Assert(false, "Encountered non-polygonal graphic during segmentation serialization");
					}
				}

				foreach (var presentationImage in presentationImagePolygons.Keys)
				{
					var currentImageSopProvider = presentationImage as IImageSopProvider;

					if (presentationImage == null)
					{
						Debug.Assert(false, "Failed to get IImageSopProvider for the current Segmentation graphic");
						continue;
					}

					Debug.Assert(presentationImagePolygons[presentationImage].FirstOrDefault().ImageFrameNumber ==
						currentImageSopProvider.Frame.FrameNumber,
								 "Stored frame number must match with the current SOP Instance's value");

					#region PerFrameFunctionalGroupSequenceItem

					// Initialize Per Frame Functional Groups here and groups
					var perFrameFunctionalGroupSequenceItem = multiFrameFunctionalGroupsModuleIod.CreatePerFrameFunctionalGroupsSequence();

					if (!docHasOneSeg)
					{
						// Pixel Measures Functional Group (per frame)
						InitializePixelMeasureFunctionalGroup(perFrameFunctionalGroupSequenceItem, currentImageSopProvider.Frame);

						// Initialize Segmentation Functional Group (per frame)
						InitializeSegmentationFunctionalGroup(perFrameFunctionalGroupSequenceItem, segmentNumber);

						// Plane Orientation (Patient) Functional Group
						InitializePlaneOrientationPatientFunctionalGroup(perFrameFunctionalGroupSequenceItem, currentImageSopProvider.Frame.ImageOrientationPatient);
					}
					if (!docHasOneFrame)
					{
						// Plain Position Patient Functional Group (per frame)
						InitializePlanePositionPatientFunctionalGroup(perFrameFunctionalGroupSequenceItem, currentImageSopProvider.Frame.ImagePositionPatient);

						// Derivation Image Functional Group (per frame)
						InitializeDerivationImageFunctionalGroup(perFrameFunctionalGroupSequenceItem, currentImageSopProvider.ImageSop, currentImageSopProvider.Frame.FrameNumber);
					}
					else
					{
						Debug.Assert(firstImageSopProvider.ImageSop.SeriesInstanceUid == currentImageSopProvider.Frame.SeriesInstanceUid &&
									 firstImageSopProvider.ImageSop.SopInstanceUid == currentImageSopProvider.ImageSop.SopInstanceUid,
									 "initial image reference and the single image reference must be the same");
					}

					// Initialize Frame Content Functional Group
					InitializeFrameContentFunctionalGroup(perFrameFunctionalGroupSequenceItem, segmentNumber, ++inStackPositionIndex);

					perFrameFunctionalGroupSequenceItems.Add(perFrameFunctionalGroupSequenceItem);

					#endregion PerFrameFunctionalGroupSequenceItem

					// Store referenced image info in a dictionary for later use
					{
						var currentSeriesInstanceUid = currentImageSopProvider.ImageSop.SeriesInstanceUid;
						var currentSopClassUid = currentImageSopProvider.ImageSop.SopClassUid;
						var currentSopInstanceUid = currentImageSopProvider.ImageSop.SopInstanceUid;
						if (!seriesUidToSopClassUidToSopInstanceUid.ContainsKey(currentSeriesInstanceUid))
							seriesUidToSopClassUidToSopInstanceUid.Add(currentSeriesInstanceUid, new Dictionary<string, HashSet<string>>());
						var sopClassToSopInstanceDic = seriesUidToSopClassUidToSopInstanceUid[currentSeriesInstanceUid];
						if (!sopClassToSopInstanceDic.ContainsKey(currentSopClassUid))
							sopClassToSopInstanceDic.Add(currentSopClassUid, new HashSet<string>());
						sopClassToSopInstanceDic[currentSopClassUid].Add(currentSopInstanceUid);
					}

					var polygons = new List<IList<PointF>>();

					// Get frame's pixel data here
					foreach (var polygonalSegGraphic in presentationImagePolygons[presentationImage])
					{
						var poly = polygonalSegGraphic.PolygonalRoiGraphic.Roi as PolygonalRoi;
						if (poly != null)
						{
							polygons.Add(poly.Polygon.Vertices);
						}
						else
						{
							Debug.Assert(false, "Encountered non-polygonal graphic during segmentation serialization");
						}
					}

					var grayscalePixelData = CreateFramePixelData(presentationImage, polygons);
					frameBytesList.Add(grayscalePixelData.Raw);
				}
			}

			segmentationImageModuleIod.SegmentSequence = segmentSequenceItems.ToArray();

			// Per Frame Functional Groups module
			multiFrameFunctionalGroupsModuleIod.PerFrameFunctionalGroupsSequence = perFrameFunctionalGroupSequenceItems.ToArray();

			#region SharedFunctionalGroupSequence

			// Shared Functional Group Sequence Item
			var sharedFunctionalGroupSequenceItem = multiFrameFunctionalGroupsModuleIod.CreateSharedFunctionalGroupsSequence();

			if (docHasOneSeg)
			{
				Debug.Assert(segmentNumber == 1, "This is for a single segment only");

				// Pixel Measures Functional Group (shared)
				InitializePixelMeasureFunctionalGroup(sharedFunctionalGroupSequenceItem, firstImageSopProvider.Frame);

				// Initialize Segmentation Functional Group (shared)
				InitializeSegmentationFunctionalGroup(sharedFunctionalGroupSequenceItem, segmentNumber);

				// Plane Orientation (Patient) Functional Group
				InitializePlaneOrientationPatientFunctionalGroup(sharedFunctionalGroupSequenceItem, firstImageSopProvider.Frame.ImageOrientationPatient);
			}

			if (docHasOneFrame)
			{
				// Plain Position Patient Functional Group
				InitializePlanePositionPatientFunctionalGroup(sharedFunctionalGroupSequenceItem, firstImageSopProvider.Frame.ImagePositionPatient);

				// Derivation Image Functional Group
				InitializeDerivationImageFunctionalGroup(sharedFunctionalGroupSequenceItem, firstImageSopProvider.ImageSop, firstImageSopProvider.Frame.FrameNumber);
			}

			multiFrameFunctionalGroupsModuleIod.SharedFunctionalGroupsSequence = sharedFunctionalGroupSequenceItem;

			#endregion SharedFunctionalGroupSequence

			// Multi-frame Dimensions module
			multiFrameDimensionsModuleIod.DimensionIndexSequence = dimensionIndexSequenceItems.ToArray();
			multiFrameDimensionsModuleIod.DimensionOrganizationSequence = dimensionOrganizationSequenceItems.ToArray();
			multiFrameDimensionsModuleIod.DimensionOrganizationType = "3D";

			// Multi-frame Functional Groups module
			multiFrameFunctionalGroupsModuleIod.SharedFunctionalGroupsSequence = sharedFunctionalGroupSequenceItem;
			multiFrameFunctionalGroupsModuleIod.PerFrameFunctionalGroupsSequence = perFrameFunctionalGroupSequenceItems.ToArray();
			multiFrameFunctionalGroupsModuleIod.NumberOfFrames = perFrameFunctionalGroupSequenceItems.Count;

			// Specimen Module
			var srcSpecimenModuleIod = new SpecimenModuleIod(sourceSop.DataSource);
			var specimenModuleIod = segDocumentIod.SpecimenModuleIod;
			//specimenModuleIod.ContainerIdentifier = srcSpecimenModuleIod.ContainerIdentifier;
			specimenModuleIod.IssuerOfTheContainterIdentifier = srcSpecimenModuleIod.IssuerOfTheContainterIdentifier;
			specimenModuleIod.AlternateContainerIdentifierSequence = srcSpecimenModuleIod.AlternateContainerIdentifierSequence;
			specimenModuleIod.ContainerTypeCodeSequence = srcSpecimenModuleIod.ContainerTypeCodeSequence;
			//specimenModuleIod.ContainerDescription = srcSpecimenModuleIod.ContainerDescription;
			specimenModuleIod.ContainerComponentSequence = srcSpecimenModuleIod.ContainerComponentSequence;
			specimenModuleIod.SpecimenDescriptionSequence = srcSpecimenModuleIod.SpecimenDescriptionSequence;

			// Common Instance Reference Module
			var referencedSeriesSequenceItems = new List<ReferencedSeriesSequenceIod>();
			foreach (
				var seriesToSopClassToSopInstanceDic in
					seriesUidToSopClassUidToSopInstanceUid.Where(seriesToSopClassToSopInstanceDic => seriesToSopClassToSopInstanceDic.Value != null))
			{
				var referencedSopInstances = new List<ReferencedInstanceSequenceIod>();
				foreach (var sopClassToSopInstanceDic in seriesToSopClassToSopInstanceDic.Value.Where(sopClassToSopInstanceDic => sopClassToSopInstanceDic.Value != null))
				{
					referencedSopInstances.AddRange(sopClassToSopInstanceDic.Value.Select(sopInstanceUid => new ReferencedInstanceSequenceIod
						{
							ReferencedSopClassUid = sopClassToSopInstanceDic.Key,
							ReferencedSopInstanceUid = sopInstanceUid
						}));
				}
				if (referencedSopInstances.Count > 0)
				{
					referencedSeriesSequenceItems.Add(new ReferencedSeriesSequenceIod
						{
							SeriesInstanceUid = seriesToSopClassToSopInstanceDic.Key,
							ReferencedInstanceSequence = referencedSopInstances.ToArray()
						});
				}
			}
			if (referencedSeriesSequenceItems.Count > 0)
			{
				var commonInstanceReferenceModuleIod = segDocumentIod.CommonInstanceReferenceModuleIod;
				commonInstanceReferenceModuleIod.InitializeAttributes();
				commonInstanceReferenceModuleIod.ReferencedSeriesSequence = referencedSeriesSequenceItems.ToArray();
			}

			// SOP Common Module
			var srcSopCommonModuleIod = new SopCommonModuleIod(sourceSop.DataSource);
			var sopCommonModuleIod = segDocumentIod.SopCommonModuleIod;
			sopCommonModuleIod.SopClass = SopClass.SegmentationStorage;
			sopCommonModuleIod.SopInstanceUid = DicomUid.GenerateUid().UID;
			//sopCommonModuleIod.SpecificCharacterSet = "UTF-8"; // TBD -it's ISO_IR 192 by default
			sopCommonModuleIod.InstanceCreationDateTime = contentDateTime;
			sopCommonModuleIod.InstanceCreatorUid = InstanceCreatorUid;
			sopCommonModuleIod.TimezoneOffsetFromUtc = contentDateTime.ToString("zzz", DateTimeFormatInfo.InvariantInfo);
			//sopCommonModuleIod.LongitudinalTemporalInformationModified = srcSopCommonModuleIod.LongitudinalTemporalInformationModified; // has a bug in CC

			// Pixel data
			{
				Debug.Assert(frameBytesList.TrueForAll(bytes => bytes.Length == frameBytesList[0].Length), "Allocated buffers for all frames must be of the same size");
				var byteBuffer = new byte[frameBytesList[0].Length * frameBytesList.Count];
				using (var stream = new MemoryStream(byteBuffer))
				{
					foreach (var frameBytes in frameBytesList)
						stream.Write(frameBytes, 0, frameBytes.Length);
				}
				// Byte Packing
				// TODO FIXME: we can do in-place byte packing without allocating the second array!
				var packetBuffer = new byte[(int) Math.Ceiling(byteBuffer.Length/8.0)];
				var numberOfFullBytes = byteBuffer.Length/8;
				for (var i = 0; i < numberOfFullBytes; i++)
				{
					var newByte = packetBuffer[i];
					for (var y = 0; y < 8; y++)
					{
						var bitMask = (byte) (1 << y);
						newByte = (byte) ((byteBuffer[8*i + y] & 0xFF) > 0 ? newByte | bitMask : newByte & ~bitMask);
					}
					packetBuffer[i] = newByte;
				}
				// last byte(s) TODO VK: handle padding for non-even number of bytes. make sure padded bits are initialized to 0
				if (numberOfFullBytes < packetBuffer.Length)
				{
					// Pack leftover bytes ( < 8)
					Debug.Assert(packetBuffer.Length - numberOfFullBytes == 1, "Wrong destination bytes count during packing");
					Debug.Assert(byteBuffer.Length - numberOfFullBytes*8 < 8, "Wrong leftover bytes count during packing");
					var newByte = packetBuffer[packetBuffer.Length - 1];
					for (var y = numberOfFullBytes * 8; y < byteBuffer.Length; y++)
					{
						var bitMask = (byte) (1 << (y%8));
						newByte = (byte) ((byteBuffer[y] & 0xFF) > 0 ? newByte | bitMask : newByte & ~bitMask);
					}
					packetBuffer[packetBuffer.Length - 1] = newByte;
				}
				var pdAttribute = new DicomAttributeOW(DicomTags.PixelData);
				using (var stream = pdAttribute.AsStream())
				{
					stream.Write(packetBuffer, 0, packetBuffer.Length);
				}

				multiFrameFunctionalGroupsModuleIod.DicomAttributeProvider[DicomTags.PixelData] = pdAttribute;
			}

			dicomFile.MediaStorageSopClassUid = SopClass.SegmentationStorageUid;
			dicomFile.MediaStorageSopInstanceUid = segDocumentIod.SopInstanceUid;

			// Update the original document with new values
			_segDocument.SeriesInstanceUid = segDocumentIod.SeriesInstanceUid;
			_segDocument.SopInstanceUid = segDocumentIod.SopInstanceUid;

			return dicomFile;
		}

		/// <summary>
		/// Returns a UID specific to the current version of the workstation.
		/// </summary>
		/// <remarks>Implementation is base on <see cref="DicomUid.GenerateUid"/></remarks>
		private static string InstanceCreatorUid
		{
			get
			{
				const string baseGuid = "299845947021397478953701210049992519024"; // base GUID for our implementation's UID

				var guidBytes = string.Format("0{0:N}", baseGuid);
				var bigInteger = BigInteger.Parse(guidBytes, NumberStyles.HexNumber);

				return new DicomUid(string.Format(CultureInfo.InvariantCulture, "2.25.{0}", bigInteger), "Instance UID", UidType.SOPInstance).UID;
			}
		}

		/// <summary>
		/// Initializes Pixel Measures Functional Group
		/// </summary>
		/// <param name="functionalGroupsSequenceItem">Functional Group Sequence Item that the newly initialized Pixel Measures Functional Group will belong</param>
		/// <param name="imageFrame"><see cref="Frame"/> that is a source of group's values</param>
		private static void InitializePixelMeasureFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem, Frame imageFrame)
		{
			var pixelSpacing = imageFrame.PixelSpacing;
			if (pixelSpacing.IsNull)
				return;

			var pixelMeasureFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PixelMeasuresFunctionalGroup>();
			var pixelMeasureSequence = pixelMeasureFunctionalGroup.CreatePixelMeasuresSequence();
			pixelMeasureSequence.PixelSpacing = new[] {pixelSpacing.Row, pixelSpacing.Column};
			pixelMeasureSequence.SliceThickness = imageFrame.SliceThickness;

			pixelMeasureFunctionalGroup.PixelMeasuresSequence = pixelMeasureSequence;
		}

		private static void InitializePlaneOrientationPatientFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem,
																			 ImageOrientationPatient imageOrientationPatient)
		{
			if (imageOrientationPatient.IsNull)
				return;

			var planeOrientationPatientFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PlaneOrientationPatientFunctionalGroup>();
			var planeOrientationPatientSequence = planeOrientationPatientFunctionalGroup.CreatePlaneOrientationSequence();
			planeOrientationPatientSequence.ImageOrientationPatient = new[]
				{
					imageOrientationPatient.RowX, imageOrientationPatient.RowY, imageOrientationPatient.RowZ, imageOrientationPatient.ColumnX,
					imageOrientationPatient.ColumnY, imageOrientationPatient.ColumnZ
				};

			planeOrientationPatientFunctionalGroup.PlaneOrientationSequence = planeOrientationPatientSequence;
		}

		private static void InitializePlanePositionPatientFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem,
																		  ImagePositionPatient imagePositionPatient)
		{
			if (imagePositionPatient.IsNull)
				return;

			var planePositionPatientFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PlanePositionPatientFunctionalGroup>();
			var planePositionSequence = planePositionPatientFunctionalGroup.CreatePlanePositionSequence();
			planePositionSequence.ImagePositionPatient = new[] { imagePositionPatient.X, imagePositionPatient.Y, imagePositionPatient.Z };

			planePositionPatientFunctionalGroup.PlanePositionSequence = planePositionSequence;
		}

		private static void InitializeDerivationImageFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem, ImageSop imageSop, int frameNumber)
		{
			var derivationImageFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<DerivationImageFunctionalGroup>();
			var derivationImageSequenceItem = derivationImageFunctionalGroup.CreateDerivationImageSequenceItem();
			var derivationCodeSequence = derivationImageSequenceItem.CreateDerivationCodeSequence();
			derivationCodeSequence.CodeValue = "113076";
			derivationCodeSequence.CodeMeaning = "Segmentation";
			derivationCodeSequence.CodingSchemeDesignator = "DCM";
			derivationImageSequenceItem.DerivationCodeSequence = derivationCodeSequence;
			var sourceImageSequenceItem = derivationImageSequenceItem.CreateSourceImageSequenceItem();
			sourceImageSequenceItem.ReferencedSopClassUid = imageSop.SopClassUid;
			sourceImageSequenceItem.ReferencedSopInstanceUid = imageSop.SopInstanceUid;
			if (frameNumber != 1)
				sourceImageSequenceItem.ReferencedFrameNumber2 = new[] {frameNumber};
			// TODO: FIXME: replace with stock implementation when available
			var purposeOfReferenceCodeSequence = new Func<CodeSequenceMacro>(() =>
				{
					var dicomAttribute = sourceImageSequenceItem.DicomAttributeProvider[DicomTags.PurposeOfReferenceCodeSequence];
					if (dicomAttribute.IsNull || dicomAttribute.IsEmpty)
					{
						var dicomSequenceItem = new DicomSequenceItem();
						dicomAttribute.Values = new[] {dicomSequenceItem};
						return new CodeSequenceMacro(dicomSequenceItem);
					}
					return new CodeSequenceMacro(((DicomSequenceItem[]) dicomAttribute.Values)[0]);
				}).Invoke();
			purposeOfReferenceCodeSequence.CodeValue = "121322";
			purposeOfReferenceCodeSequence.CodeMeaning = "Source image for image processing operation";
			purposeOfReferenceCodeSequence.CodingSchemeDesignator = "DCM";
			derivationImageSequenceItem.SourceImageSequence = new[] {sourceImageSequenceItem};

			derivationImageFunctionalGroup.DerivationImageSequence = new[] {derivationImageSequenceItem};
		}

		private static void InitializeSegmentationFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem, int segmentNumber)
		{
			var segmentationFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<SegmentationFunctionalGroup>();
			var segmentationIdentificationSequenceItem = segmentationFunctionalGroup.CreateSegmentIdentificationSequence();
			segmentationIdentificationSequenceItem.ReferencedSegmentNumber = segmentNumber;

			segmentationFunctionalGroup.SegmentIdentificationSequence = segmentationIdentificationSequenceItem;
		}

		private static void InitializeFrameContentFunctionalGroup(FunctionalGroupsSequenceItem functionalGroupsSequenceItem, int stackId, int inStackPositionNumber)
		{
			var frameContentFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<FrameContentFunctionalGroup>();
			var frameContentSequenceItem = frameContentFunctionalGroup.CreateFrameContentSequence();
			frameContentSequenceItem.DimensionIndexValues = new[] {(uint)stackId, (uint)inStackPositionNumber};
			frameContentSequenceItem.StackId = string.Format("Stack ID {0}", stackId);
			frameContentSequenceItem.InStackPositionNumber = inStackPositionNumber;

			frameContentFunctionalGroup.FrameContentSequence = frameContentSequenceItem;
		}

		// TODO - move to the Graphics helpers class?
		private static GrayscalePixelData CreateFramePixelData(IPresentationImage presentationImage, IEnumerable<IEnumerable<PointF>> polygons)
		{
			var imageGraphicProvider = presentationImage as IImageGraphicProvider;
			if (imageGraphicProvider == null)
				return null;

			var imageGraphic = imageGraphicProvider.ImageGraphic;
			// Unpacked
			var grayscalePixelData = new GrayscalePixelData(
				imageGraphic.Rows, imageGraphic.Columns, // image dimensions
				8, // bits allocated is 8
				8, // bits stored is 8
				7, // the high bit is 7
				false, // not signed
				MemoryManager.Allocate<byte>(imageGraphic.Rows * imageGraphic.Columns)); // new empty pixel buffer

			// Packing 1 bit at a time (Little Endean). See OverlayData for better example
			//var grayscalePixelData = new GrayscalePixelData(
			//    imageGraphic.Rows, imageGraphic.Columns, // image dimensions
			//    1, // bits allocated is 1
			//    1, // bits stored is 1
			//    1, // the high bit is 1
			//    false, // not signed
			//    MemoryManager.Allocate<byte>((int) Math.Ceiling(imageGraphic.Rows * imageGraphic.Columns/8.0))); // new empty pixel buffer

			var columns = imageGraphic.Columns;
			foreach (var polygon in polygons)
			{
				var verticesArray = polygon.ToArray();
				var boundingBox = RectangleUtilities.ComputeBoundingRectangle(verticesArray);

				// Convert vector polygon to raster on a per pixel basis
				imageGraphic.PixelData.ForEachPixel(
					delegate(int i, int x, int y, int pixelIndex)
					{
							// Unpacked
							var point = new PointF(x, y);
							var isPixelSet = grayscalePixelData.Raw[y * columns + x] == 0xFF ||
								(boundingBox.Contains(point) &&
								SegmentationGraphicsHelpers.IsInPolygon(verticesArray, point));
							grayscalePixelData.Raw[y * columns + x] = isPixelSet ? (byte)0xFF : (byte)0x00;

							// Packed
							//var mask = (byte) (1 << (pixelIndex%8));
							//var outPos = pixelIndex/8;
							//var curByte = grayscalePixelData.Raw[outPos];
							//var point = new PointF(x, y);
							//var isPixelSet = (boundingBox.Contains(point) && SegmentationGraphicsHelpers.IsInPolygon(verticesArray, point));
							//grayscalePixelData.Raw[outPos] = (byte)(isPixelSet ? curByte | mask : curByte & ~mask);
						}
					);
			}

			return grayscalePixelData;
		}

		/// <summary>
		/// Converts string to the upper case and removes all non alpha[A-Z], digits, space or underscore characters
		/// </summary>
		/// <param name="inputValue">the string to sanitize</param>
		/// <param name="defaultValue">default value when the <paramref name="inputValue"/> is null</param>
		/// <returns></returns>
		private static string SanitizeDicomCsValue(string inputValue, string defaultValue = " ")
		{
			if (defaultValue == null)
				defaultValue = " ";
			else if (defaultValue.Length > 16)
				defaultValue = defaultValue.Substring(0, 16);

			if (inputValue == null)
				return defaultValue;

			// Internet* claims that this should be faster than RegEx
			char[] arr = inputValue.ToUpper().ToCharArray();
			arr = Array.FindAll(arr, (c => (char.IsLetterOrDigit(c) || char.IsWhiteSpace(c) || c == '_')));
			if (arr.Length > 16)
				return new string(arr, 0, 16);
			return arr.Length > 0 ? new string(arr) : defaultValue;
		}

		/// <summary>
		/// Converts given name string to a proper DICOM name value:
		/// [lastName[^firstName[^middleName[^namePrefix[^nameSuffix]]]]
		/// </summary>
		/// <param name="inputName">Name to format, e.g. "John A. Smith" or "Smith, John A."</param>
		/// <returns>DICOM-formatted name of null</returns>
		/// <remarks>Most of this logic is bogus but it's "best effort" simple attempt to create a 
		/// DICOM name without lookup dictionaries or NLP</remarks>
		private static string FormatDicomName(string inputName)
		{
			// NOTE: More realistic parsing is available at:
			// http://stackoverflow.com/questions/103422/simple-way-to-parse-a-persons-name-into-its-component-parts

			var nameToParse = inputName == null ? null : inputName.Replace("\\", "");
			if (string.IsNullOrEmpty(nameToParse))
				return null;

			var sb = new StringBuilder();
			// assume that comma separates last name from the rest of the name parts
			var lastNameIdx = nameToParse.IndexOf(',');
			if (lastNameIdx >= 0)
			{
				sb.Append(nameToParse.Substring(0, lastNameIdx));
				nameToParse = nameToParse.Substring(lastNameIdx + 1);
			}
			// Split by any white-space character
			var splitName = nameToParse.Split((char[]) null, StringSplitOptions.RemoveEmptyEntries).ToList();
			if (splitName.Count > 0)
			{
				if (splitName.Count > (lastNameIdx == -1 ? 5 : 4))
				{
					// Locate last name
					if (lastNameIdx == -1)
					{
						// Bogus but why not: allocate 1/2 of strings to last name; leave last 2 for prefix and suffix
						lastNameIdx = splitName.Count/2 - 1;
						while (lastNameIdx < splitName.Count - 2)
						{
							if (sb.Length > 0)
								sb.Append(" ");
							sb.Append(splitName[lastNameIdx]);
							splitName.RemoveAt(lastNameIdx);
						}
					}
					sb.Append("^");
					// first name
					for (var i = 0; i < splitName.Count - 2; i++)
						sb.Append(" ").Append(splitName[i]);
					// prefix/suffix
					sb.Append("^^").Append(splitName[splitName.Count - 2]).Append("^").Append(splitName[splitName.Count - 1]);
				}
				else
				{
					// Locate last name
					if (lastNameIdx == -1)
					{
						switch (splitName.Count)
						{
							case 1:
								lastNameIdx = 0;
								break;
							case 2:
								lastNameIdx = 1;
								break;
							default:
								lastNameIdx = 2;
								break;
						}
						sb.Append(splitName[lastNameIdx]);
						splitName.RemoveAt(lastNameIdx);
					}
					// Assume the order is right
					foreach (var namePart in splitName)
					{
						sb.Append("^").Append(namePart);
					}
				}
			}
			return sb.ToString();
		}
	}
}
