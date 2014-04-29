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
using ClearCanvas.Dicom.Iod;
using ClearCanvas.Dicom.Iod.Sequences;

namespace Segmentation.DICOM.Iods
{
	// TODO - based on CC's class. Use CC's class instead of this when that class is fixed.

	/// <summary>
	/// ReferencedSeriesSequenceIod
	/// </summary>
	/// <remarks>As defined in PS 3.3-2011, Section 10.4 (Table 10-4)</remarks>
	public class ReferencedSeriesSequenceIod : SequenceIodBase
	{
		#region Constructors
		/// <summary>
		/// Initializes a new instance of the <see cref="ReferencedSeriesSequenceIod"/> class.
		/// </summary>
		public ReferencedSeriesSequenceIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="ReferencedSeriesSequenceIod"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public ReferencedSeriesSequenceIod(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }
		#endregion

		#region Public Properties

		/// <summary>
		/// Unique identifier of the Series containing the referenced Instances. Type 1.
		/// </summary>
		/// <value>The series instance uid.</value>
		public string SeriesInstanceUid
		{
			get { return DicomAttributeProvider[DicomTags.SeriesInstanceUid].GetString(0, String.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", "SeriesInstanceUid is Type 1 Required.");
				DicomAttributeProvider[DicomTags.SeriesInstanceUid].SetString(0, value);
			}
		}

		/// <summary>
		/// Sequence of Items each providing a reference to an Instance that is part of the
		/// Series defined by Series Instance UID (0020,000E) in the enclosing Item. 
		/// One or more Items shall be present.
		/// </summary>
		/// <value>The referenced film session sequence list.</value>
		public ReferencedInstanceSequenceIod[] ReferencedInstanceSequence
		{
			get { return this.GetSequenceValues<ReferencedSeriesSequenceIod, ReferencedInstanceSequenceIod>(DicomTags.ReferencedInstanceSequence); }
			set { this.SetSequenceValues(DicomTags.ReferencedInstanceSequence, value, true); }
		}
		#endregion
	}
}
