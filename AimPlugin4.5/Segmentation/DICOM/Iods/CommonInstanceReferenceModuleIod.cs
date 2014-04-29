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
using ClearCanvas.Dicom.Iod.Sequences;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// Common Instance Reference Module
	/// </summary>
	/// <remarks>As defined by PS 3.3-2011, Section C.12.2 (Table C.12-8)</remarks>
	public class CommonInstanceReferenceModuleIod : IodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="CommonInstanceReferenceModuleIod"/> class.
		/// </summary>	
		public CommonInstanceReferenceModuleIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="CommonInstanceReferenceModuleIod"/> class.
		/// </summary>
		public CommonInstanceReferenceModuleIod(IDicomAttributeProvider dicomAttributeProvider) : base(dicomAttributeProvider) { }

		/// <summary>
		/// Gets an enumeration of <see cref="DicomTag"/>s used by this module.
		/// </summary>
		public static IEnumerable<uint> DefinedTags
		{
			get
			{
				yield return DicomTags.ReferencedSeriesSequence;
				yield return DicomTags.StudiesContainingOtherReferencedInstancesSequence;
			}
		}

		/// <summary>
		/// Initializes the underlying collection to implement the module or sequence using default values.
		/// </summary>
		public void InitializeAttributes()
		{
			// TODO - ?
		}

		/// <summary>
		/// Gets or sets the value of ReferencedSeriesSequence in the underlying collection. Type 1.
		/// </summary>
		public ReferencedSeriesSequenceIod[] ReferencedSeriesSequence
		{
			get { return this.GetSequenceValues<CommonInstanceReferenceModuleIod, ReferencedSeriesSequenceIod>(DicomTags.ReferencedSeriesSequence); }
			set { this.SetSequenceValues(DicomTags.ReferencedSeriesSequence, value, true); }
		}

		/// <summary>
		/// Gets or sets the value of StudiesContainingOtherReferencedInstancesSequence in the underlying collection. Type 1C.
		/// </summary>
		public StudiesContainingOtherReferencedInstancesSequenceItem[] StudiesContainingOtherReferencedInstancesSequence
		{
			get { return this.GetSequenceValues<CommonInstanceReferenceModuleIod, StudiesContainingOtherReferencedInstancesSequenceItem>(DicomTags.StudiesContainingOtherReferencedInstancesSequence); }
			set { this.SetSequenceValues(DicomTags.StudiesContainingOtherReferencedInstancesSequence, value); }
		}
	}

	/// <summary>
	/// StudiesContainingOtherReferencedInstancesSequence
	/// </summary>
	/// <remarks>As defined in the PS 3.3-2011, Section C.12.2 (Table C.12-8)</remarks>
	public class StudiesContainingOtherReferencedInstancesSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="StudiesContainingOtherReferencedInstancesSequenceItem"/> class.
		/// </summary>
		public StudiesContainingOtherReferencedInstancesSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="StudiesContainingOtherReferencedInstancesSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public StudiesContainingOtherReferencedInstancesSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		/// Gets or sets the value of StudyInstanceUid in the underlying collection. Type 1.
		/// </summary>
		public string StudyInstanceUid
		{
			get { return DicomAttributeProvider[DicomTags.StudyInstanceUid].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", "StudyInstanceUid is Type 1 Required.");
				DicomAttributeProvider[DicomTags.StudyInstanceUid].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the value of ReferencedSeriesSequence in the underlying collection. Type 1.
		/// </summary>
		public ReferencedSeriesSequenceIod[] ReferencedSeriesSequence
		{
			get { return this.GetSequenceValues<StudiesContainingOtherReferencedInstancesSequenceItem, ReferencedSeriesSequenceIod>(DicomTags.ReferencedSeriesSequence); }
			set { this.SetSequenceValues(DicomTags.ReferencedSeriesSequence, value, true); }
		}
	}
}
