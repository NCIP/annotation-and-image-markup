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

using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// FrameOfReference Module.
	/// </summary>
	/// <remarks>As defined in PS 3.3-2011, Section C.7.4.1 (Table C.7-6)</remarks>
	public class FrameOfReferenceModuleIod : IodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="FrameOfReferenceModuleIod"/> class.
		/// </summary>
		public FrameOfReferenceModuleIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FrameOfReferenceModuleIod"/> class.
		/// </summary>
		public FrameOfReferenceModuleIod(IDicomAttributeProvider dicomAttributeProvider) : base(dicomAttributeProvider) { }

		/// <summary>
		/// Gets or sets the value of FrameOfReferenceUid in the underlying collection.
		/// </summary>
		public string FrameOfReferenceUid
		{
			get { return DicomAttributeProvider[DicomTags.FrameOfReferenceUid].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.FrameOfReferenceUid].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets the value of PositionReferenceIndicator in the underlying collection.
		/// </summary>
		public string PositionReferenceIndicator
		{
			get { return DicomAttributeProvider[DicomTags.PositionReferenceIndicator].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.PositionReferenceIndicator].SetString(0, value); }
		}
	}
}
