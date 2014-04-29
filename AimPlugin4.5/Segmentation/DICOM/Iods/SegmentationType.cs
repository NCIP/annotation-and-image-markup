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

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// Segmentation Type enum as per DICOM PS 3.3-2011, C.8.20.2.3
	/// </summary>
	/// <remarks><see cref="FRACTIONAL"/> should be further qualified with <see cref="SegmentationFractionalType"/> value</remarks>
	public enum SegmentationType
	{
		/// <summary>
		/// Represents invalid value.
		/// </summary>
		Invalid,
		
		/// <summary>
		/// BINARY segmentation type
		/// </summary>
		BINARY,

		/// <summary>
		/// FRACTIONAL segmentation type
		/// </summary>
		FRACTIONAL
	}

	/// <summary>
	/// Segmentation Fractional Type per DICOM PS 3.3-2011, C.8.20.2.3
	/// </summary>
	public enum SegmentationFractionalType
	{
		/// <summary>
		/// Represents the null value.
		/// </summary>
		None,

		/// <summary>
		/// PROBABILITY segmentation fractional type
		/// </summary>
		PROBABILITY,

		/// <summary>
		/// OCCUPANCY segmentation fractional type
		/// </summary>
		OCCUPANCY
	}
}
