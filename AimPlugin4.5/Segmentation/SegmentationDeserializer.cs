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
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod.FunctionalGroups;
using ClearCanvas.Dicom.Iod.Macros;
using ClearCanvas.Dicom.Iod.Modules;
using ClearCanvas.Dicom.Iod.Sequences;
using ClearCanvas.ImageViewer.StudyManagement;
using Segmentation.DICOM;
using Segmentation.DICOM.Iods;
using Segmentation.Tree;

namespace Segmentation
{
	public class SegmentationDeserializer
	{
		private readonly SegmentationDocumentIod _segDocumentIod;

		public SegmentationDeserializer(Sop sop)
		{
			_segDocumentIod = new SegmentationDocumentIod(sop.DataSource);
		}

		public SegmentationDocument DeserializeSegmenationDocument()
		{
			if (_segDocumentIod == null)
				return null;

			var segDocument = new SegmentationDocument(_segDocumentIod);

			segDocument.CreationDateTime = _segDocumentIod.CreationDateTime ?? DateTime.Now; // ??
			segDocument.SeriesInstanceUid = _segDocumentIod.SeriesInstanceUid;
			segDocument.SeriesDescription = _segDocumentIod.SeriesDescription;
			segDocument.SeriesNumber = _segDocumentIod.SeriesNumber ?? 0; // ??
			//segDocument.PreviousSegmentationUid = _segDocumentIod.PriorSegmentationUid;
			segDocument.SopInstanceUid = _segDocumentIod.SopInstanceUid;
			segDocument.ContentLabel = _segDocumentIod.SegmentationImageModuleIod.ContentLabel;

			//var userName = _segDocumentIod.GeneralSeriesModuleIod.OperatorsName;
			var userName = _segDocumentIod.SegmentationImageModuleIod.ContentCreatorsName;
			if (!string.IsNullOrEmpty(userName))
			{
				segDocument.UserInfo = new UserInfo
					{
						Name = userName,
						LoginName = userName // TODO - use _segDocumentIod.GeneralSeriesModuleIod.OperatorsName[1] when available
					};
			}

			var hasErrors = false;
			if (CanUnderstandSopInstance())
			{
				var segmentationImageModule = _segDocumentIod.SegmentationImageModuleIod;
				if (segmentationImageModule != null)
				{
					for (int i = 0; i < segmentationImageModule.SegmentSequence.Length; i++)
					{
						var seg = InitializeSegFromIod(i);
						if (seg == null)
							hasErrors = true;
						else
							segDocument.Segs.Add(seg);
					}
				}
			}

			if (hasErrors || segDocument.Segs.Count == 0)
			{
				var invalidSeg = new Seg(false, null);
				invalidSeg.Description = "Segmentation reading error(s) - see log for details";
				invalidSeg.Label = "Errors/Not Supported";
				segDocument.Segs.Add(invalidSeg);
			}

			return segDocument;
		}

		private Seg InitializeSegFromIod(int segmentIndex)
		{
			Debug.Assert(_segDocumentIod.SegmentationImageModuleIod.SegmentSequence != null, "SegmentSequence is not present");
			Debug.Assert(segmentIndex >= 0 && segmentIndex < _segDocumentIod.SegmentationImageModuleIod.SegmentSequence.Length, "segmentIndex is outside the boundaries of the SegmentSequence");

			var segmentImageData = new SegmentImageData();

			var segmentSequence = _segDocumentIod.SegmentationImageModuleIod.SegmentSequence[segmentIndex];
			var segmentNumber = segmentSequence.SegmentNumber; // This value can be a random int judging from what is out there

			var seg = new Seg(false, segmentImageData);
			seg.SegmentationNumber = segmentNumber;
			seg.Description = segmentSequence.SegmentDescription;
			seg.Label = segmentSequence.SegmentLabel;
			var labColor = segmentSequence.RecomendedDisplayCIELabValue;
			seg.Color = labColor == null ? UserInfo.GetGraphicColorForUser() : Graphics.LabColorHelpers.CIELabColorToRgbColor(labColor.Value);
			var refSeriesSequence = _segDocumentIod.CommonInstanceReferenceModuleIod.ReferencedSeriesSequence;
			if (refSeriesSequence != null && refSeriesSequence.Length > 0)
			{
				var refSeriesSequenceItem = refSeriesSequence[0];
				seg.ImageSeriesUid = refSeriesSequenceItem.SeriesInstanceUid;
				var refInstanceSequence = refSeriesSequenceItem.ReferencedInstanceSequence;
				if ( refInstanceSequence != null && refInstanceSequence.Length > 0)
				{
					segmentImageData.ReferencedSopClassUid = refInstanceSequence[0].ReferencedSopClassUid;
					segmentImageData.ReferencedSopInstanceUid = refInstanceSequence[0].ReferencedSopInstanceUid;
				}
			}
			seg.NoLabelNumber = segmentNumber;

			#region Category, Type, Anatomic Region and their modifiers

			var categoryCodeSequence = segmentSequence.SegmentedPropertyCategoryCodeSequence;
			if (categoryCodeSequence != null && categoryCodeSequence.Length > 0)
			{
				var categoryCode = categoryCodeSequence[0];
				seg.SelectedCategory = new Category
					{
						CodeValue = categoryCode.CodeValue,
						CodeMeaning = categoryCode.CodeMeaning,
						CodingSchemeDesignator = categoryCode.CodingSchemeDesignator
					};
				//if (!string.IsNullOrEmpty(categoryCode.CodingSchemeVersion))
				//    seg.SelectedCategory.CodingSchemeVersion = categoryCode.CodingSchemeVersion;

				var propertyTypeSequence = segmentSequence.SegmentedPropertyTypeCodeSequence;
				if (propertyTypeSequence != null && propertyTypeSequence.Length > 0)
				{
					var propertyType = propertyTypeSequence[0];
					seg.SelectedCategory.SelectedType = new Tree.Type
						{
							CodeValue = propertyType.CodeValue,
							CodeMeaning = propertyType.CodeMeaning,
							CodingSchemeDesignator = propertyType.CodingSchemeDesignator
						};
					//if (!string.IsNullOrEmpty(propertyType.CodingSchemeVersion))
					//    seg.SelectedCategory.SelectedType.CodingSchemeVersion = propertyType.CodingSchemeVersion;

					if (propertyType.SegmentedPropertyTypeModifierCodeSequence != null && propertyType.SegmentedPropertyTypeModifierCodeSequence.Length > 0)
					{
						var propertyTypeModifier = propertyType.SegmentedPropertyTypeModifierCodeSequence[0];
						seg.SelectedCategory.SelectedType.SelectedTypeModifier = new Tree.TypeModifier
							{
								CodeValue = propertyTypeModifier.CodeValue,
								CodeMeaning = propertyTypeModifier.CodeMeaning,
								CodingSchemeDesignator = propertyTypeModifier.CodingSchemeDesignator
							};
						//if (!string.IsNullOrEmpty(propertyTypeModifier.CodingSchemeVersion))
						//    seg.SelectedCategory.SelectedType.SelectedTypeModifier.CodingSchemeVersion = propertyTypeModifier.CodingSchemeVersion;
					}
				}

				var anatomicRegionSequence = segmentSequence.AnatomicRegionSequence;
				if (anatomicRegionSequence != null && anatomicRegionSequence.Length > 0)
				{
					var anatomicRegion = anatomicRegionSequence[0];
					seg.SelectedCategory.SelectedAnatomicRegion = new AnatomicRegion
						{
							CodeValue = anatomicRegion.CodeValue,
							CodeMeaning = anatomicRegion.CodeMeaning,
							CodingSchemeDesignator = anatomicRegion.CodingSchemeDesignator
						};
					//if (!string.IsNullOrEmpty(anatomicRegion.CodingSchemeVersion))
					//    seg.SelectedCategory.SelectedAnatomicRegion.CodingSchemeVersion = anatomicRegion.CodingSchemeVersion;

					var anatomicRegionModifierSequence = anatomicRegion.AnatomicRegionModifierSequence;
					if (anatomicRegionModifierSequence != null && anatomicRegionModifierSequence.Length > 0)
					{
						var anatomicRegionModifier = anatomicRegionModifierSequence[0];
						seg.SelectedCategory.SelectedAnatomicRegion.SelectedAnatomicRegionModifier = new AnatomicRegionModifier
							{
								CodeValue = anatomicRegionModifier.CodeValue,
								CodeMeaning = anatomicRegionModifier.CodeMeaning,
								CodingSchemeDesignator = anatomicRegionModifier.CodingSchemeDesignator
							};
						//if (!string.IsNullOrEmpty(anatomicRegionModifier.CodingSchemeVersion))
						//    seg.SelectedCategory.SelectedAnatomicRegion.SelectedAnatomicRegionModifier.CodingSchemeVersion = anatomicRegionModifier.CodingSchemeVersion;
					}
				}

				// Initialize lists of available values to make UI happy
				var category = seg.SelectedCategory;
				if (category.SelectedType != null)
				{
					if (category.SelectedType.SelectedTypeModifier != null)
						category.SelectedType.TypeModifiers.Add(category.SelectedType.SelectedTypeModifier);
					category.Types.Add(category.SelectedType);
				}
				if (category.SelectedAnatomicRegion != null)
				{
					if (category.SelectedAnatomicRegion.SelectedAnatomicRegionModifier != null)
						category.SelectedAnatomicRegion.AnatomicRegionModifiers.Add(category.SelectedAnatomicRegion.SelectedAnatomicRegionModifier);
					category.AnatomicRegions.Add(category.SelectedAnatomicRegion);
				}
				seg.AvailableCategories = new List<Category> {category};
			}

			#endregion Category, Type, Anatomic Region and their modifiers

			var imagePixelModuleIod = _segDocumentIod.ImagePixelModuleIod;
			segmentImageData.Rows = imagePixelModuleIod.Rows;
			segmentImageData.Columns = imagePixelModuleIod.Columns;

			var segmentationImageModuleIod = _segDocumentIod.SegmentationImageModuleIod;
			segmentImageData.SegmentationType = segmentationImageModuleIod.SegmentationType;
			segmentImageData.BitsAllocated = segmentationImageModuleIod.BitsAllocated;
			segmentImageData.BitsStored = segmentationImageModuleIod.BitsStored;
			segmentImageData.HighBit = segmentationImageModuleIod.HighBit;
			segmentImageData.SamplesPerPixel = segmentationImageModuleIod.SamplesPerPixel;

			segmentImageData.SegmentFrameData = GetSegmentFrameDataList(segmentNumber);

			// Required if Derivation Image Functional Group is not present
			segmentImageData.FrameOfReferenceUid = _segDocumentIod.FrameOfReferenceModuleIod.FrameOfReferenceUid;

			// Get all attributes for future Frame data extraction
			segmentImageData.DicomAttributeProvider = _segDocumentIod.MultiFrameFunctionalGroupsModuleIod.DicomAttributeProvider;

			// NOTE: Graphics is initialized during DataSet loading

			// NOTE: calculations will be initialized during SegmentationComponent initialization

			return seg;
		}

		private List<SegmentFrameData> GetSegmentFrameDataList(int segmentNumber)
		{
			var multiFrameFunctionalGroupsIod = _segDocumentIod.MultiFrameFunctionalGroupsModuleIod;

			var sharedFunctionalGroupsSequence = multiFrameFunctionalGroupsIod.SharedFunctionalGroupsSequence;
			var sharedSourceImageSequence = GetSourceImageSequence(sharedFunctionalGroupsSequence);
			var sharedPlanePositionSequenceItem = GetPlanePostitionSequenceItem(sharedFunctionalGroupsSequence);
			var sharedPlaneOrientationSequenceItem = GetPlaneOrientationSequenceItem(sharedFunctionalGroupsSequence);
			var sharedPixelMeasureSequenceItem = GetPixelMeasuresSequenceItem(sharedFunctionalGroupsSequence);
			var sharedSegmentIdentificationSequenceItem = GetSegmentIdentificationSequenceItem(sharedFunctionalGroupsSequence);

			if (sharedSegmentIdentificationSequenceItem != null)
			{
				// Only one segment in the current document. All frames belong to it.
				Debug.Assert(sharedSegmentIdentificationSequenceItem.ReferencedSegmentNumber == segmentNumber, "The only shared segment number must match");
			}

			var segmentFrames = new List<SegmentFrameData>();

			// NOTE: don't use multiFrameFunctionalGroupsIod.PerFrameFunctionalGroupsSequence !!! Too slow on large # of frames
			//for (int i = 0; i < multiFrameFunctionalGroupsIod.PerFrameFunctionalGroupsSequence.Length; i++)
			var numberOfFrames = multiFrameFunctionalGroupsIod.NumberOfFrames;
			for (var i = 0; i < numberOfFrames; i++)
			{
				// TODO VK: make this method return a Dictionary<frameNumber, List<SegmentFrameData>> so we only have to loop trough all frames ones!

				int referencedSegmentNumber = sharedSegmentIdentificationSequenceItem == null
												  ? GetPerFrameReferencedSegmentNumber(multiFrameFunctionalGroupsIod, i)
												  : sharedSegmentIdentificationSequenceItem.ReferencedSegmentNumber;
				Debug.Assert(referencedSegmentNumber >= 0, "Referenced Segment Number cannot be a negative value");

				// Ensure that frame data is for the current segment
				if (referencedSegmentNumber == segmentNumber)
				{
					var perFrameFunctionalGroupsSequenceItem = GetPerFrameFunctionalGroupsSequenceItem(multiFrameFunctionalGroupsIod, i);

					var frameContentSequenceItem = GetFrameContentSequenceItem(perFrameFunctionalGroupsSequenceItem);
					Debug.Assert(frameContentSequenceItem != null, "Frame Content Sequence Item is required for each segmentation frame");

					var sourceImageSequence = sharedSourceImageSequence ?? GetSourceImageSequence(perFrameFunctionalGroupsSequenceItem);
					var planePositionSequenceItem = sharedPlanePositionSequenceItem ?? GetPlanePostitionSequenceItem(perFrameFunctionalGroupsSequenceItem);
					var planeOrientationSequenceItem = sharedPlaneOrientationSequenceItem ?? GetPlaneOrientationSequenceItem(perFrameFunctionalGroupsSequenceItem);
					var pixelMeasureSequenceItem = sharedPixelMeasureSequenceItem ?? GetPixelMeasuresSequenceItem(perFrameFunctionalGroupsSequenceItem);

					var segmentFrameData = new SegmentFrameData(i + 1);
					if (sourceImageSequence != null && sourceImageSequence.Length > 0)
					{
						// TODO VK: Fix use of only the first value in the sequence if there is a real case when a single segmentation frame may apply to multiple Image SOP Instances

						segmentFrameData.ReferencedSopClassUid = sourceImageSequence[0].ReferencedSopClassUid;
						segmentFrameData.ReferencedSopInstanceUid = sourceImageSequence[0].ReferencedSopInstanceUid;
						var referencedFrameNumber = sourceImageSequence[0].ReferencedFrameNumber2;
						if (referencedFrameNumber != null && referencedFrameNumber.Length > 0)
							segmentFrameData.ReferencedFrameNumber = referencedFrameNumber[0];

						// Is this fires, greater care needs to be taken when selecting the correct source image(s)
						Debug.Assert(sourceImageSequence[0].ReferencedSegmentNumber2 == null || sourceImageSequence[0].ReferencedSegmentNumber2.Length == 0 ||
									 sourceImageSequence[0].ReferencedSegmentNumber2[0] == segmentNumber);

						if (sourceImageSequence.Length > 1)
							Platform.Log(LogLevel.Error, "Reading segmentation with multiple Source Image Sequence items. Unsupported!");
					}

					if (planePositionSequenceItem != null)
						segmentFrameData.ImagePositionPatient = planePositionSequenceItem.ImagePositionPatient;
					if (segmentFrameData.ImagePositionPatient == null)
						Platform.Log(LogLevel.Warn, "Read a segment (#{0}, frame={1}) without ImagePositionPatient", segmentNumber, i + 1);

					if (planeOrientationSequenceItem != null)
						segmentFrameData.ImageOrientationPatient = planeOrientationSequenceItem.ImageOrientationPatient;
					if (segmentFrameData.ImageOrientationPatient == null)
						Platform.Log(LogLevel.Warn, "Read a segment (#{0}, frame={1}) without ImageOrientationPatient", segmentNumber, i + 1);

					if (pixelMeasureSequenceItem != null)
					{
						segmentFrameData.PixelSpacing = pixelMeasureSequenceItem.PixelSpacing;
						segmentFrameData.SliceThickness = pixelMeasureSequenceItem.SliceThickness;
					}

					var dimensionIndexValues = frameContentSequenceItem.DimensionIndexValues;
					if (dimensionIndexValues != null && dimensionIndexValues.Length > 0)
						segmentFrameData.DimensionIndexValues = dimensionIndexValues;
					else
						Debug.Assert(false, "FIXME: Segmentations without explicitly defined dimensions are not supported for now. We use dimensions for frame sorting.");

					// This value is rarely set
					if (frameContentSequenceItem.InStackPositionNumber != null)
						segmentFrameData.InStackPositionNumber = frameContentSequenceItem.InStackPositionNumber.Value;

					segmentFrames.Add(segmentFrameData);
				}
			}

			// The tag is optional
			// Debug.Assert(!segmentFrames.GroupBy(item => item.InStackPositionNumber).Any(g => g.Count() > 1), "InStackPositionNumber for all frames must be unique within a segment");

			// Sort frames by dimension index values. See Multi-frame Dimension Module C.7.6.17, PS 3.3-2011 for ordering example
			segmentFrames.Sort((item1, item2) =>
				{
					if (item1.DimensionIndexValues != null && item2.DimensionIndexValues != null)
					{
						Debug.Assert(item1.DimensionIndexValues.Length == item2.DimensionIndexValues.Length,
									 "Segmentation object must have the same number of DimensionIndexValues");
						return CompareArrayContent(item1.DimensionIndexValues, item2.DimensionIndexValues);
					}

					// Here we're just desperate. This may or may not be a real value
					return Comparer<int>.Default.Compare(item1.InStackPositionNumber, item2.InStackPositionNumber);
				});

			return segmentFrames;
		}

		// Does element-wise array elements comparison. Ex: array with [3, 2, 9] comes before [3, 4, 5, 1]
		private static int CompareArrayContent<T>(T[] arr1, T[] arr2) where T : IComparable
		{
			if (arr1 == null)
				return arr2 != null ? -1 : 0;

			if (arr2 == null)
				return 1;

			var comparer = Comparer<T>.Default;
			for (var i = 0; i < arr1.Length; i++)
			{
				if (arr2.Length == i)
					return -1; // no more elements - shorter array wins

				var result = comparer.Compare(arr1[i], arr2[i]);
				if (result != 0)
					return result;
			}
			return arr1.Length != arr2.Length ? 1 : 0;
		}

		private static ImageSopInstanceReferenceMacro[] GetSourceImageSequence(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			var sharedDerivationSequenceFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<DerivationImageFunctionalGroup>();
			return sharedDerivationSequenceFunctionalGroup.HasValues()
						? (sharedDerivationSequenceFunctionalGroup.DerivationImageSequence.Length > 0
							  ? sharedDerivationSequenceFunctionalGroup.DerivationImageSequence[0].SourceImageSequence
							  : null)
						: null;
		}

		private static PlanePositionSequenceItem GetPlanePostitionSequenceItem(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			var sharedPlanePositionFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PlanePositionPatientFunctionalGroup>();
			return sharedPlanePositionFunctionalGroup.HasValues() ? sharedPlanePositionFunctionalGroup.PlanePositionSequence : null;
		}

		private static PlaneOrientationSequenceItem GetPlaneOrientationSequenceItem(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			var sharedPlaneOrientationFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PlaneOrientationPatientFunctionalGroup>();
			return sharedPlaneOrientationFunctionalGroup.HasValues() ? sharedPlaneOrientationFunctionalGroup.PlaneOrientationSequence : null;
		}

		private static PixelMeasuresSequenceItem GetPixelMeasuresSequenceItem(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			var sharedPixelMeasureFucntionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<PixelMeasuresFunctionalGroup>();
			return sharedPixelMeasureFucntionalGroup.HasValues() ? sharedPixelMeasureFucntionalGroup.PixelMeasuresSequence : null;
		}

		private static SegmentIdentificationSequenceItem GetSegmentIdentificationSequenceItem(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			var sharedSegmentationFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<SegmentationFunctionalGroup>();
			return sharedSegmentationFunctionalGroup.HasValues() ? sharedSegmentationFunctionalGroup.SegmentIdentificationSequence : null;
		}

		private static FrameContentSequenceItem GetFrameContentSequenceItem(FunctionalGroupsSequenceItem functionalGroupsSequenceItem)
		{
			// NOTE: only PerFrameFunctionalGroup will have this item
			var frameContentFunctionalGroup = functionalGroupsSequenceItem.GetFunctionalGroup<FrameContentFunctionalGroup>();
			return frameContentFunctionalGroup.HasValues() ? frameContentFunctionalGroup.FrameContentSequence : null;
		}

		/// <summary>
		/// Directly gets Per Frame <see cref="FunctionalGroupsSequenceItem"/> without creating the full PerFrameFunctionalGroupsSequence[] collection.
		/// </summary>
		/// <param name="multiFrameFunctionalGroupsModuleIod"><see cref="MultiFrameFunctionalGroupsModuleIod"/> of the segmentation IOD</param>
		/// <param name="frameIndex">frame index (0-based)</param>
		/// <returns>PerFrameFunctionalGroupsSequenceItem for the requested frame</returns>
		private static FunctionalGroupsSequenceItem GetPerFrameFunctionalGroupsSequenceItem(MultiFrameFunctionalGroupsModuleIod multiFrameFunctionalGroupsModuleIod,
																							int frameIndex)
		{
			var dicomAttribute = multiFrameFunctionalGroupsModuleIod.DicomAttributeProvider[DicomTags.PerFrameFunctionalGroupsSequence];
			if (dicomAttribute.IsNull || dicomAttribute.IsEmpty || frameIndex >= dicomAttribute.Count)
				return null;

			var item = ((DicomSequenceItem[])dicomAttribute.Values)[frameIndex];
			return new FunctionalGroupsSequenceItem(item);
		}

		/// <summary>
		/// Directly gets Per Frame <see cref="FunctionalGroupsSequenceItem"/> count without creating the full PerFrameFunctionalGroupsSequence[] collection.
		/// </summary>
		/// <param name="multiFrameFunctionalGroupsModuleIod"><see cref="MultiFrameFunctionalGroupsModuleIod"/> of the segmentation IOD</param>
		/// <returns></returns>
		private static long GetNumberOfPerFrameFinctionalGroupsSequenceItems(MultiFrameFunctionalGroupsModuleIod multiFrameFunctionalGroupsModuleIod)
		{
			var dicomAttribute = multiFrameFunctionalGroupsModuleIod.DicomAttributeProvider[DicomTags.PerFrameFunctionalGroupsSequence];
			if (dicomAttribute.IsNull || dicomAttribute.IsEmpty)
				return -1;

			return dicomAttribute.Count;
		}

		/// <summary>
		/// Directly gets Per Frame ReferencedSegmentNumber without creating the full PerFrameFunctionalGroupsSequence[] collection.
		/// </summary>
		/// <param name="multiFrameFunctionalGroupsModuleIod"><see cref="MultiFrameFunctionalGroupsModuleIod"/> of the segmentation IOD</param>
		/// <param name="frameIndex">frame index (0-based)</param>
		/// <returns>ReferencedSegmentNumber or -1</returns>
		private static int GetPerFrameReferencedSegmentNumber(MultiFrameFunctionalGroupsModuleIod multiFrameFunctionalGroupsModuleIod, int frameIndex)
		{
			var dicomAttribute = multiFrameFunctionalGroupsModuleIod.DicomAttributeProvider[DicomTags.PerFrameFunctionalGroupsSequence];
			if (dicomAttribute.IsNull || dicomAttribute.IsEmpty || frameIndex >= dicomAttribute.Count)
				return -1;

			var perFrameFunctionalGroupsSequenceItem = ((DicomSequenceItem[])dicomAttribute.Values)[frameIndex];
			if (perFrameFunctionalGroupsSequenceItem != null)
			{
				var dicomAttr1 = perFrameFunctionalGroupsSequenceItem.GetAttribute(DicomTags.SegmentIdentificationSequence);
				if (!dicomAttr1.IsNull && !dicomAttr1.IsEmpty)
				{
					var segmentIdentificationSequenceItem = ((DicomSequenceItem[])dicomAttr1.Values)[0];
					var dicomAttr2 = segmentIdentificationSequenceItem.GetAttribute(DicomTags.ReferencedSegmentNumber);
					if (!dicomAttr2.IsNull && !dicomAttr2.IsEmpty)
						return dicomAttr2.GetInt32(0, -1);
				}
			}
			return -1;
		}

		/// <summary>
		/// Cursory check to see if the given segmentation IOD is presently supported by the workstation
		/// </summary>
		/// <returns>true - if the the IOD passes the checks; false - otherwise</returns>
		/// <remarks>Detected error and warning details are written to the log</remarks>
		private bool CanUnderstandSopInstance()
		{
			var segmentationImageModule = _segDocumentIod.SegmentationImageModuleIod;
			var multiFrameFunctionalGroupsModuleIod = _segDocumentIod.MultiFrameFunctionalGroupsModuleIod;
			var sharedFunctionalGroupsSequence = multiFrameFunctionalGroupsModuleIod.SharedFunctionalGroupsSequence;
			//var perFrameFunctionalGroupsSequence = multiFrameFunctionalGroupsModuleIod.PerFrameFunctionalGroupsSequence; // too slow with large # of frames
			var numberOfPerFrameFunctionalGroupsSequenceItems = GetNumberOfPerFrameFinctionalGroupsSequenceItems(multiFrameFunctionalGroupsModuleIod);
			var errors = new List<string>();
			var warnings = new List<string>();

			// NOTE: These checks are to filter out presently unsupported Segmentations.
			// If a check is to be removed, make sure that the implementation can deal with such data!

			//if (segmentationImageModule.SamplesPerPixel != 1)
			//    errors.Add(string.Format("Samples Per Pixel is not 1 ({0})", segmentationImageModule.SamplesPerPixel));
			if (!ClearCanvas.Dicom.Iod.PhotometricInterpretation.Monochrome2.Equals(segmentationImageModule.PhotometricInterpretation))
				errors.Add(string.Format("Photometric Interpretation is not \"MONOCHROME2\" ({0})", segmentationImageModule.PhotometricInterpretation));
			switch (segmentationImageModule.BitsAllocated)
			{
				case 1:
					if (segmentationImageModule.BitsStored != 1 || segmentationImageModule.HighBit != 0)
						errors.Add(string.Format("Invalid segmentation object data: Bits Allocated = 1, Bits Stored = {0}, High Bit = {1}", segmentationImageModule.BitsStored,
						                         segmentationImageModule.HighBit));
					break;
				case 8:
					if (segmentationImageModule.BitsStored != 8 || segmentationImageModule.HighBit != 7)
						errors.Add(string.Format("Invalid segmentation object data: Bits Allocated = 8, Bits Stored = {0}, High Bit = {1}", segmentationImageModule.BitsStored,
						                         segmentationImageModule.HighBit));
					break;
				default:
					// All other values are invalid for Segmentation instances
					errors.Add(string.Format("Invalid segmentation object data: Bits Allocated = {0}, Bits Stored = {1}, High Bit = {2}",
					                         segmentationImageModule.BitsAllocated,
					                         segmentationImageModule.BitsStored,
					                         segmentationImageModule.HighBit));
					break;
			}
			if (segmentationImageModule.PixelRepresentation != 0)
				errors.Add(string.Format("Pixel Representation is not 0 [0000H] ({0})", segmentationImageModule.PixelRepresentation));
			if (segmentationImageModule.SegmentationType != SegmentationType.BINARY && segmentationImageModule.SegmentationType != SegmentationType.FRACTIONAL)
				errors.Add(string.Format("Invalid segmentation types cannot be displayed ({0})", segmentationImageModule.SegmentationType));
			var isPlainPositionFgPresent = false;
			if (sharedFunctionalGroupsSequence == null)
			{
				errors.Add(@"No Shared Functional Groups are present"); // assumed that at least one should exist
			}
			else
			{
				if (!sharedFunctionalGroupsSequence.GetFunctionalGroup<PixelMeasuresFunctionalGroup>().HasValues())
					errors.Add(@"Only valid cross-sectional (3D) imaging is supported (PixelMeasuresFunctionalGroup is absent)"); // projection radiograph and single slices are not supported for now

				isPlainPositionFgPresent = sharedFunctionalGroupsSequence.GetFunctionalGroup<PlanePositionPatientFunctionalGroup>().HasValues();
			}

			// We are supporting one SOP instance reference per frame for now.
			var getNumberOfSourceImageSequenceItems = new Func<FunctionalGroupsSequenceItem, int>(functionalGroupsSequenceItem =>
				{
					var item = functionalGroupsSequenceItem == null ? null : GetSourceImageSequence(functionalGroupsSequenceItem);
					return item != null ? item.Length : 0;
				});

			var numberOfSourceImageSequenceItems = getNumberOfSourceImageSequenceItems(sharedFunctionalGroupsSequence);

			var checkPlainPostitionFgPresence = !isPlainPositionFgPresent;
			var checkNumberOfSourceImageSequenceItems = numberOfSourceImageSequenceItems == 0;

			var numberOfFrames = multiFrameFunctionalGroupsModuleIod.NumberOfFrames;
			if (numberOfFrames == numberOfPerFrameFunctionalGroupsSequenceItems)
			{
				if (checkPlainPostitionFgPresence || checkNumberOfSourceImageSequenceItems)
				{
					if (checkPlainPostitionFgPresence)
						isPlainPositionFgPresent = true; // initial value

					// TODO VK: this is too slow for instances with large number of frames
					for (int i = 0; i < numberOfFrames; i++)
					{
						var perFrameFunctionalGroupsSequenceItem = GetPerFrameFunctionalGroupsSequenceItem(multiFrameFunctionalGroupsModuleIod, i);
						if (checkPlainPostitionFgPresence)
						{
							// Either ImagePositionPatient or DimensionIndexValues need to be present
							if (!perFrameFunctionalGroupsSequenceItem.GetFunctionalGroup<PlanePositionPatientFunctionalGroup>().HasValues())
							{
								var frameContentSequence = perFrameFunctionalGroupsSequenceItem.GetFunctionalGroup<FrameContentFunctionalGroup>().FrameContentSequence;
								if (frameContentSequence == null || frameContentSequence.DimensionIndexValues == null || frameContentSequence.DimensionIndexValues.Length == 0)
								{
									// projection radiograph and single slices are not supported for now
									errors.Add(string.Format("Only valid cross-sectional (3D) imaging is supported. No frame positioning information is present"));
									isPlainPositionFgPresent = false;
								}
							}
						}

						if (checkNumberOfSourceImageSequenceItems)
							numberOfSourceImageSequenceItems = Math.Max(numberOfSourceImageSequenceItems, getNumberOfSourceImageSequenceItems(perFrameFunctionalGroupsSequenceItem));
					}
				}
			}
			else
			{
				errors.Add(string.Format("Encoded value for number of frames ({0}) in the segmentation object does not match actual frame number ({1})",
										 numberOfFrames, numberOfPerFrameFunctionalGroupsSequenceItems));
			}
			if (!isPlainPositionFgPresent)
				errors.Add(@"Only valid cross-sectional (3D) imaging is supported (PlanePositionPatientFunctionalGroup is absent)"); // projection radiograph and single slices are not supported for now
			if (numberOfSourceImageSequenceItems > 1)
				errors.Add(@"Only segmentations with one explicit image reference is supported");

			if (warnings.Count > 0)
				Platform.Log(LogLevel.Info, string.Format("Segmentation Object (SOP Instance UID={0}) is being loaded with the following warnings: {1}", _segDocumentIod.SopInstanceUid, StringUtilities.Combine(warnings, ",\n\t- ")));

			if (errors.Count > 0)
			{
				Platform.Log(LogLevel.Error, string.Format("Segmentation Object (SOP Instance UID={0}) is not supported: {1}", _segDocumentIod.SopInstanceUid, StringUtilities.Combine(errors, ",\n\t- ")));
				return false;
			}
			return true;
		}
	}
}
