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
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// FrameExtractionModule
	/// </summary>
	/// <remarks>As defined by DICOM PS 3.3-2011, Section C.12.3 (Table C.12-9)</remarks>
	public class FrameExtractionModuleIod : IodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="FrameExtractionModuleIod"/> class.
		/// </summary>	
		public FrameExtractionModuleIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FrameExtractionModuleIod"/> class.
		/// </summary>
		public FrameExtractionModuleIod(IDicomAttributeProvider dicomAttributeProvider) : base(dicomAttributeProvider) { }

		/// <summary>
		/// Gets an enumeration of <see cref="DicomTag"/>s used by this module.
		/// </summary>
		public static IEnumerable<uint> DefinedTags
		{
			get { yield return DicomTags.FrameExtractionSequence; }
		}

		/// <summary>
		/// Gets or sets FrameExtraction Sequence value. Type 1.
		/// </summary>
		public FrameExtractionSequenceItem[] FrameExtractionSequence
		{
			get { return this.GetSequenceValues<FrameExtractionModuleIod, FrameExtractionSequenceItem>(DicomTags.FrameExtractionSequence); }
			set { this.SetSequenceValues(DicomTags.FrameExtractionSequence, value, true); }
		}
	}

	public class FrameExtractionSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="FrameExtractionSequenceItem"/> class.
		/// </summary>
		public FrameExtractionSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FrameExtractionSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public FrameExtractionSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		/// Gets or sets MultiFrameSourceSopInstanceUid. Type 1.
		/// </summary>
		public string MultiFrameSourceSopInstanceUid
		{
			get { return DicomAttributeProvider[DicomTags.MultiFrameSourceSopInstanceUid].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", "MultiFrameSourceSopInstanceUid is Type 1 Required.");
				DicomAttributeProvider[DicomTags.MultiFrameSourceSopInstanceUid].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets SimpleFrameList. Type 1C.
		/// </summary>
		/// <remarks>Either this value or <see cref="CalculatedFrameList"/> or <see cref="TimeRange"/> can be set</remarks>
		public uint[] SimpleFrameList
		{
			get { return (uint[])DicomAttributeProvider[DicomTags.SimpleFrameList].Values; }
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.SimpleFrameList] = null;
					return;
				}
				DicomAttributeProvider[DicomTags.SimpleFrameList].Values = value;
			}
		}

		// TODO. Finish implementation:

		/// <summary>
		/// Gets or sets CalculatedFrameList. Type 1C.
		/// </summary>
		/// <remarks>Either this value or <see cref="SimpleFrameList"/> or <see cref="TimeRange"/> can be set</remarks>
		public uint[] CalculatedFrameList
		{
			get { return (uint[])DicomAttributeProvider[DicomTags.CalculatedFrameList].Values; }
			set { throw new NotImplementedException("CalculatedFrameList"); }
		}

		/// <summary>
		/// Gets or sets TimeRange. Type 1C.
		/// </summary>
		/// <remarks>Either this value or <see cref="SimpleFrameList"/> or <see cref="CalculatedFrameList"/> can be set</remarks>
		public uint[] TimeRange
		{
			get { return (uint[])DicomAttributeProvider[DicomTags.TimeRange].Values; }
			set { throw new NotImplementedException("TimeRange"); }
		}
	}
}
