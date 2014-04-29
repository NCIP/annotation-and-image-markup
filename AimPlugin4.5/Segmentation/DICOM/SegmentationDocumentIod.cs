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
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod.Modules;
using Segmentation.DICOM.Iods;

namespace Segmentation.DICOM
{
	public class SegmentationDocumentIod
	{
		private readonly IDicomAttributeProvider _dicomAttributeProvider;
		private readonly PatientModuleIod _patientModule;
		private readonly ClinicalTrialSubjectModuleIod _clinicalTrialSubjectModule;
		private readonly GeneralStudyModuleIod _generalStudyModule;
		private readonly PatientStudyModuleIod _patientStudyModule;
		private readonly ClinicalTrialStudyModuleIod _clinicalTrialStudyModule;
		private readonly GeneralSeriesModuleIod _generalSeriesModule;
		private readonly SegmentationSeriesModuleIod _segmentationSeriesModule;
		private readonly ClinicalTrialSeriesModuleIod _clinicalTrialSeriesModule;
		private readonly FrameOfReferenceModuleIod _frameOfReferenceModule;
		private readonly GeneralEquipmentModuleIod _generalEquipmentModule;
		//private readonly EnhanceGeneralEquipmentModuleIod _enhanceGeneralEquipmentModule; - DON'T NEED THIS
		private readonly GeneralImageModuleIod _generalImageModule;
		private readonly ImagePixelMacroIod _imagePixelModule;
		private readonly SegmentationImageModuleIod _segmentationImageModule;
		private readonly MultiFrameFunctionalGroupsModuleIod _multiFrameFunctionalGroupsModule;
		private readonly MultiFrameDimensionModuleIod _multiFrameDimensionModule;
		private readonly SpecimenModuleIod _specimenModule;
		private readonly CommonInstanceReferenceModuleIod _commonInstanceReferenceModule;
		private readonly SopCommonModuleIod _sopCommonModule;
		private readonly FrameExtractionModuleIod _frameExtractionModule;
		
		public SegmentationDocumentIod() : this(new DicomAttributeCollection()) {}

		public SegmentationDocumentIod(IDicomAttributeProvider dicomAttributeProvider)
		{
			_dicomAttributeProvider = dicomAttributeProvider;
			_patientModule = new PatientModuleIod(_dicomAttributeProvider);
			_clinicalTrialSubjectModule = new ClinicalTrialSubjectModuleIod(_dicomAttributeProvider);
			_generalStudyModule = new GeneralStudyModuleIod(_dicomAttributeProvider);
			_patientStudyModule = new PatientStudyModuleIod(_dicomAttributeProvider);
			_clinicalTrialStudyModule = new ClinicalTrialStudyModuleIod(_dicomAttributeProvider);
			_generalSeriesModule = new GeneralSeriesModuleIod(_dicomAttributeProvider);
			_segmentationSeriesModule = new SegmentationSeriesModuleIod(_dicomAttributeProvider);
			_clinicalTrialSeriesModule = new ClinicalTrialSeriesModuleIod(_dicomAttributeProvider);
			_frameOfReferenceModule = new FrameOfReferenceModuleIod(_dicomAttributeProvider);
			_generalEquipmentModule = new GeneralEquipmentModuleIod(_dicomAttributeProvider);
			//_enhanceGeneralEquipmentModule = new EnhanceGeneralEquipmentModuleIod(_dicomAttributeProvider);
			_generalImageModule = new GeneralImageModuleIod(_dicomAttributeProvider);
			_imagePixelModule = new ImagePixelMacroIod(_dicomAttributeProvider);
			_segmentationImageModule = new SegmentationImageModuleIod(_dicomAttributeProvider);
			_multiFrameFunctionalGroupsModule = new MultiFrameFunctionalGroupsModuleIod(_dicomAttributeProvider);
			_multiFrameDimensionModule = new MultiFrameDimensionModuleIod(_dicomAttributeProvider);
			_specimenModule = new SpecimenModuleIod(_dicomAttributeProvider);
			_commonInstanceReferenceModule = new CommonInstanceReferenceModuleIod(_dicomAttributeProvider);
			_sopCommonModule = new SopCommonModuleIod(_dicomAttributeProvider);
			_frameExtractionModule = new FrameExtractionModuleIod(_dicomAttributeProvider);
		}

		#region Implemented Modules
		public PatientModuleIod PatientModuleIod
		{
			get { return _patientModule; }
		}

		public ClinicalTrialSubjectModuleIod ClinicalTrialSubjectModuleIod
		{
			get { return _clinicalTrialSubjectModule; }
		}

		public GeneralStudyModuleIod GeneralStudyModuleIod
		{
			get { return _generalStudyModule; }
		}

		public PatientStudyModuleIod PatientStudyModuleIod
		{
			get { return _patientStudyModule; }
		}

		public ClinicalTrialStudyModuleIod ClinicalTrialStudyModuleIod
		{
			get { return _clinicalTrialStudyModule; }
		}

		public GeneralSeriesModuleIod GeneralSeriesModuleIod
		{
			get { return _generalSeriesModule; }
		}

		public SegmentationSeriesModuleIod SegmentationSeriesModuleIod
		{
			get { return _segmentationSeriesModule; }
		}

		public ClinicalTrialSeriesModuleIod ClinicalTrialSeriesModuleIod
		{
			get { return _clinicalTrialSeriesModule; }
		}

		public FrameOfReferenceModuleIod FrameOfReferenceModuleIod
		{
			get { return _frameOfReferenceModule; }
		}

		public GeneralEquipmentModuleIod GeneralEquipmentModuleIod
		{
			get { return _generalEquipmentModule; }
		}

		public GeneralImageModuleIod GeneralImageModuleIod
		{
			get { return _generalImageModule; }
		}

		public ImagePixelMacroIod ImagePixelModuleIod
		{
			get { return _imagePixelModule; }
		}

		public SegmentationImageModuleIod SegmentationImageModuleIod
		{
			get { return _segmentationImageModule; }
		}

		public MultiFrameFunctionalGroupsModuleIod MultiFrameFunctionalGroupsModuleIod
		{
			get { return _multiFrameFunctionalGroupsModule; }
		}

		public MultiFrameDimensionModuleIod MultiFrameDimensionModuleIod
		{
			get { return _multiFrameDimensionModule; }
		}

		public SpecimenModuleIod SpecimenModuleIod
		{
			get { return _specimenModule; }
		}

		public CommonInstanceReferenceModuleIod CommonInstanceReferenceModuleIod
		{
			get { return _commonInstanceReferenceModule; }
		}

		public SopCommonModuleIod SopCommonModuleIod
		{
			get { return _sopCommonModule; }
		}

		public FrameExtractionModuleIod FrameExtractionModuleIod
		{
			get { return _frameExtractionModule; }
		}

		#endregion

		public string SopInstanceUid
		{
			get { return _sopCommonModule.SopInstanceUid; }
		}

		public DateTime? CreationDateTime
		{
			get { return _generalImageModule.ContentDateTime; }
			set { _generalImageModule.ContentDateTime = value; }
		}

		public string SeriesInstanceUid
		{
			get { return _generalSeriesModule.SeriesInstanceUid; }
			set { _generalSeriesModule.SeriesInstanceUid = value; }
		}

		public string SeriesDescription
		{
			get { return _generalSeriesModule.SeriesDescription; }
			set { _generalSeriesModule.SeriesDescription = value; }
		}

		public int? SeriesNumber
		{
			get { return _generalSeriesModule.SeriesNumber; }
			set { _generalSeriesModule.SeriesNumber = value; }
		}

		public string StudyInstanceUid
		{
			get { return _generalStudyModule.StudyInstanceUid; }
		}
	}
}
