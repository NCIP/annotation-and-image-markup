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
using ClearCanvas.Dicom.Iod.Macros;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// HL7v2HierarchicDesignator Macro
	/// </summary>
	/// <remarks>Defined per PS 3.3-2011, Section 10.14, Table 10-17</remarks>
	public class HL7v2HierarchicDesignatorMacroIod : SequenceIodBase, IIodMacro
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="HL7v2HierarchicDesignatorMacroIod"/> class.
		/// </summary>
		public HL7v2HierarchicDesignatorMacroIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="HL7v2HierarchicDesignatorMacroIod"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public HL7v2HierarchicDesignatorMacroIod(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		#region IIodMacro Members

		public void InitializeAttributes()
		{
			LocalNamespaceEntityId = "";
			UniversalEntityId = "";
			UniversalEntityIdType = UniversalEntityIdType.None;
		}

		#endregion

		public string LocalNamespaceEntityId
		{
			get { return DicomAttributeProvider[DicomTags.LocalNamespaceEntityId].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.LocalNamespaceEntityId].SetString(0, value); }
		}

		public string UniversalEntityId
		{
			get { return DicomAttributeProvider[DicomTags.UniversalEntityId].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.UniversalEntityId].SetString(0, value); }
		}

		public UniversalEntityIdType UniversalEntityIdType
		{
			get { return ParseEnum(DicomAttributeProvider[DicomTags.UniversalEntityIdType].GetString(0, string.Empty), UniversalEntityIdType.None); }
			set { SetAttributeFromEnum(DicomAttributeProvider[DicomTags.UniversalEntityIdType], value); }
		}
	}

	/// <summary>
	/// UniversalEntityIdType as defined by PS 3.3-2011, Section 10-14, Table 10-17
	/// </summary>
	public enum UniversalEntityIdType
	{
		/// <summary>
		/// Represents an Internet dotted name. Either in ASCII or as integers
		/// </summary>
		DNS,

		/// <summary>
		/// Represents an IEEE Extended Unique Identifier
		/// </summary>
		EUI64,

		/// <summary>
		/// Represents an International Standards Organization Object Identifier
		/// </summary>
		ISO,

		/// <summary>
		/// Represents a Uniform Resource Identifier
		/// </summary>
		URI,

		/// <summary>
		/// Represents the DCE Universal Unique Identifier
		/// </summary>
		UUID,

		/// <summary>
		/// Represents an X.400 MHS identifier
		/// </summary>
		X400,

		/// <summary>
		/// Represents an X.500 directory name
		/// </summary>
		X500,

		/// <summary>
		/// Represents unknown or not set value
		/// </summary>
		None
	}
}
