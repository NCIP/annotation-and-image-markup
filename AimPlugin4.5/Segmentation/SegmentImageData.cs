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
using ClearCanvas.Dicom;
using Segmentation.DICOM.Iods;

namespace Segmentation
{
	public class SegmentImageData
	{
		public SegmentImageData()
		{
			SegmentationType = SegmentationType.BINARY;
			SamplesPerPixel = 1;
			BitsAllocated = 1;
			BitsStored = 1;
			HighBit = 0;
		}

		// SOP Class UID of the segmented image
		public string ReferencedSopClassUid { get; set; }

		// SOP Instance UID of the segmented instance
		public string ReferencedSopInstanceUid { get; set; }

		#region Image Pixel Module and Segmentation Image Module

		public SegmentationType SegmentationType { get; set; }

		public int SamplesPerPixel { get; set; }

		public int Rows { get; set; }

		public int Columns { get; set; }

		public int BitsAllocated { get; set; }

		public int BitsStored { get; set; }

		public int HighBit { get; set; }

		// PixelData ?

		#endregion

		#region MultiFrameFunctionalGroups

		// List of frames that belong to this segment
		public List<SegmentFrameData> SegmentFrameData { get; set; }

		#endregion

		#region FrameOfReferenceModule

		public string FrameOfReferenceUid { get; set; }

		#endregion

		// Needed for PixelData extraction
		public IDicomAttributeProvider DicomAttributeProvider { get; set; }
	}

	public class SegmentFrameData
	{
		public SegmentFrameData(int frameNumber)
		{
			FrameNumber = frameNumber;
		}

		#region SourceImageSequence

		// SOP Class UID of the segmented image
		public string ReferencedSopClassUid { get; set; }

		// SOP Instance UID of the segmented instance
		public string ReferencedSopInstanceUid { get; set; }

		// Frame Number of the segmented image instance, if referencing multi-frame image; use 1 if the value is not set.
		public int? ReferencedFrameNumber { get; set; }

		#endregion

		/// <summary>
		/// Gets or sets frame number of the current frame data in the segmentation object
		/// </summary>
		public int FrameNumber { get; private set; }

		/// <summary>
		/// Gets or sets in-stack segment position number of the current frame
		/// </summary>
		public int InStackPositionNumber { get; set; }

		/// <summary>
		/// Gets or sets Image Position Patient
		/// </summary>
		/// <value>X, Y and Z coordinates of the frame's Image Position Patient or null</value>
		/// <remarks>Data comes from PlanePositionSequence</remarks>
		public double[] ImagePositionPatient { get; set; }

		/// <summary>
		/// Gets or sets Image Orientation Patient
		/// </summary>
		/// <value>The six values that define Image Orientation Patient or null</value>
		/// <remarks>Data comes from PlaneOrientationSequence</remarks>
		public double[] ImageOrientationPatient { get; set; }

		#region PixelMeasuresFunctionalGroup

		public double[] PixelSpacing { get; set; }

		public double? SliceThickness { get; set; }

		#endregion

		#region FrameContentSequence

		public uint[] DimensionIndexValues { get; set; }

		#endregion
	}
}
