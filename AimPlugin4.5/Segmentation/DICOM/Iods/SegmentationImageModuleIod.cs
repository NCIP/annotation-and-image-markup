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
using ClearCanvas.Dicom.Iod.Macros;

namespace Segmentation.DICOM.Iods
{
	public class SegmentationImageModuleIod : IodBase, IContentIdentificationMacro
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentationImageModuleIod"/> class.
		/// </summary>
		public SegmentationImageModuleIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentationImageModuleIod"/> class.
		/// </summary>
		public SegmentationImageModuleIod(IDicomAttributeProvider dicomAttributeProvider) : base(dicomAttributeProvider) { }

		/// <summary>
		/// Gets the dicom attribute collection as a dicom sequence item.
		/// </summary>
		/// <value>The dicom sequence item.</value>
		DicomSequenceItem IIodMacro.DicomSequenceItem
		{
			get { return DicomAttributeProvider as DicomSequenceItem; }
			set { DicomAttributeProvider = value; }
		}

		/// <summary>
		/// Gets an enumeration of <see cref="DicomTag"/>s used by this module.
		/// </summary>
		public static IEnumerable<uint> DefinedTags
		{
			get
			{
				yield return DicomTags.ImageType;
				yield return DicomTags.InstanceNumber;
				yield return DicomTags.ContentLabel;
				yield return DicomTags.ContentDescription;
				yield return DicomTags.AlternateContentDescriptionSequence;
				yield return DicomTags.ContentCreatorsName;
				yield return DicomTags.ContentCreatorsIdentificationCodeSequence;
				yield return DicomTags.SamplesPerPixel;
				yield return DicomTags.PhotometricInterpretation;
				yield return DicomTags.PixelRepresentation;
				yield return DicomTags.BitsAllocated;
				yield return DicomTags.BitsStored;
				yield return DicomTags.HighBit;
				yield return DicomTags.LossyImageCompression;
				yield return DicomTags.LossyImageCompressionRatio;
				yield return DicomTags.LossyImageCompressionMethod;
				yield return DicomTags.SegmentationType;
				yield return DicomTags.SegmentationFractionalType;
				yield return DicomTags.MaximumFractionalValue;
				yield return DicomTags.SegmentSequence;
			}
		}

		/// <summary>
		/// Initializes the underlying collection to implement the module or sequence using default values.
		/// </summary>
		public virtual void InitializeAttributes()
		{
			ImageType = "DERIVED\\PRIMARY";
			InstanceNumber = 1;
			ContentLabel = " ";
			ContentDescription = null;
			AlternateContentDescriptionSequence = null;
			ContentCreatorsName = null;
			ContentCreatorsIdentificationCodeSequence = null;
			SamplesPerPixel = 1;
			PhotometricInterpretation = PhotometricInterpretation.Monochrome2;
			PixelRepresentation = 0;
			BitsAllocated = 1;
			BitsStored = 1;
			HighBit = 0;
			LossyImageCompression = "00";
			SegmentationType = SegmentationType.BINARY;
			SegmentationFractionalType = SegmentationFractionalType.None;
		}

		/// <summary>
		/// Gets or sets the type of the image.
		/// </summary>
		/// <value>The type of the image.</value>
		public string ImageType
		{
			get { return DicomAttributeProvider[DicomTags.ImageType].GetString(0, String.Empty); }
			set { DicomAttributeProvider[DicomTags.ImageType].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets the value of InstanceNumber in the underlying collection. Type 1.
		/// </summary>
		public int InstanceNumber
		{
			get { return DicomAttributeProvider[DicomTags.InstanceNumber].GetInt32(0, 0); }
			set { DicomAttributeProvider[DicomTags.InstanceNumber].SetInt32(0, value); }
		}

		/// <summary>
		/// Gets or sets the value of ContentLabel in the underlying collection. Type 1.
		/// </summary>
		public string ContentLabel
		{
			get { return DicomAttributeProvider[DicomTags.ContentLabel].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", @"ContentLabel is Type 1 Required.");
				DicomAttributeProvider[DicomTags.ContentLabel].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the value of ContentDescription in the underlying collection. Type 2.
		/// </summary>
		public string ContentDescription
		{
			get { return DicomAttributeProvider[DicomTags.ContentDescription].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					DicomAttributeProvider[DicomTags.ContentDescription].SetNullValue();
				else
					DicomAttributeProvider[DicomTags.ContentDescription].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets AlternateContentDescriptionSequence. Type 3.
		/// </summary>
		public AlternateContentDescriptionSequenceItem[] AlternateContentDescriptionSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.AlternateContentDescriptionSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new AlternateContentDescriptionSequenceItem[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new AlternateContentDescriptionSequenceItem(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.AlternateContentDescriptionSequence] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				DicomAttributeProvider[DicomTags.AlternateContentDescriptionSequence].Values = result;
			}
		}


		/// <summary>
		/// Gets or sets the value of ContentCreatorsName in the underlying collection. Type 2.
		/// </summary>
		public string ContentCreatorsName
		{
			get { return DicomAttributeProvider[DicomTags.ContentCreatorsName].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					DicomAttributeProvider[DicomTags.ContentCreatorsName].SetNullValue();
				else
					DicomAttributeProvider[DicomTags.ContentCreatorsName].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the value of ContentCreatorsIdentificationCodeSequence in the underlying collection. Type 3.
		/// </summary>
		public PersonIdentificationMacro ContentCreatorsIdentificationCodeSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.ContentCreatorsIdentificationCodeSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}
				return new PersonIdentificationMacro(((DicomSequenceItem[])dicomAttribute.Values)[0]);
			}
			set
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.ContentCreatorsIdentificationCodeSequence];
				if (value == null)
					DicomAttributeProvider[DicomTags.ContentCreatorsIdentificationCodeSequence] = null;
				else
					dicomAttribute.Values = new[] { value.DicomSequenceItem };
			}
		}

		/// <summary>
		/// Gets or sets the samples per pixel.  Number of samples (planes) in this image. Type 1.
		/// <para>Possible values for Segmentation Image Module is 1.</para>
		/// </summary>
		/// <value>The samples per pixel.</value>
		public ushort SamplesPerPixel
		{
			get { return DicomAttributeProvider[DicomTags.SamplesPerPixel].GetUInt16(0, 0); }
			set
			{
				if (1 != value)
					throw new ArgumentOutOfRangeException("value", @"SamplesPerPixel has to be 1");
				DicomAttributeProvider[DicomTags.SamplesPerPixel].SetUInt16(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the photometric interpretation. Type 1.
		/// <para>Possible value for Segmentation Image Module is MONOCHROME2.</para>
		/// </summary>
		/// <value>The photometric interpretation.</value>
		public PhotometricInterpretation PhotometricInterpretation
		{
			get { return PhotometricInterpretation.FromCodeString(DicomAttributeProvider[DicomTags.PhotometricInterpretation].GetString(0, String.Empty)); }
			set
			{
				if (!PhotometricInterpretation.Monochrome2.Equals(value))
					throw new ArgumentOutOfRangeException("value", @"PhotometricInterpretation has to be MONOCHROME2");
				DicomAttributeProvider[DicomTags.PhotometricInterpretation].SetStringValue(value.Code);
			}
		}

		/// <summary>
		/// Gets or sets the pixel representation. Data representation of the pixel samples. 
		/// Each sample shall have the same pixel representation. Enumerated values:
		///		0000H = unsigned integer
		///		0001H = 2's compliment
		/// <para>Possible values for Segmentation Image Module is 0000H.</para>
		/// </summary>
		/// <value>The pixel representation.</value>
		public ushort PixelRepresentation
		{
			get { return DicomAttributeProvider[DicomTags.PixelRepresentation].GetUInt16(0, 0); }
			set
			{
				if (0 != value)
					throw new ArgumentOutOfRangeException("value", @"PixelRepresentation has to be 0 (0000H)");
				DicomAttributeProvider[DicomTags.PixelRepresentation].SetUInt16(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the bits allocated. Number of bits allocated for each pixel sample. Type 1.
		/// Each sample shall have the same number of bits allocated.
		/// See Section C.8.20.2.1 and PS 3.5 for further explanation.
		/// <para>Possible values for Segmentation Image Module: 1 if Segmentation Type is BINARY, else 8.</para>
		/// </summary>
		/// <value>The bits allocated.</value>
		public ushort BitsAllocated
		{
			get { return DicomAttributeProvider[DicomTags.BitsAllocated].GetUInt16(0, 0); }
			set
			{
				switch (SegmentationType)
				{
					case SegmentationType.Invalid:
						if (1 != value && 8 != value)
							throw new ArgumentOutOfRangeException("value", @"BitsAllocated has to be 1 or 8");
						break;
					case SegmentationType.BINARY:
						if (value != 1)
							throw new ArgumentOutOfRangeException("value", @"BitsAllocated has to be 1 for BINARY segmentation type.");
						break;
					default:
						if (8 != value)
							throw new ArgumentOutOfRangeException("value", @"BitsAllocated has to be 8 for non-BINARY segmentation type.");
						break;
				}
				DicomAttributeProvider[DicomTags.BitsAllocated].SetUInt16(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the bits stored. Number of bits stored for each pixel sample. Type 1.
		/// Each sample shall have the same number of bits stored.
		/// See Section C.8.20.2.1 and PS 3.5 for further explanation,
		/// <para>Possible values for Segmentation Image Module: 1 if Segmentation Type is BINARY, else 8.</para>
		/// </summary>
		/// <value>The bits stored.</value>
		public ushort BitsStored
		{
			get { return DicomAttributeProvider[DicomTags.BitsStored].GetUInt16(0, 0); }
			set
			{
				switch (SegmentationType)
				{
					case SegmentationType.Invalid:
						if (1 != value && 8 != value)
							throw new ArgumentOutOfRangeException("value", @"BitsStored has to be 1 or 8");
						break;
					case SegmentationType.BINARY:
						if (value != 1)
							throw new ArgumentOutOfRangeException("value", @"BitsStored has to be 1 for BINARY segmentation type.");
						break;
					default:
						if (8 != value)
							throw new ArgumentOutOfRangeException("value", @"BitsStored has to be 8 for non-BINARY segmentation type.");
						break;
				}
				DicomAttributeProvider[DicomTags.BitsStored].SetUInt16(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the high bit. Most significant bit for pixel sample data. Type 1.
		/// Each sample shall have the same high bit.
		/// See Section C.8.20.2.1 and PS 3.5 for further explanation.
		/// <para>Possible values for Segmentation Image Module: 0 if Segmentation Type is BINARY, else 7.</para>
		/// </summary>
		/// <value>The high bit.</value>
		public ushort HighBit
		{
			get { return DicomAttributeProvider[DicomTags.HighBit].GetUInt16(0, 0); }
			set
			{
				switch (SegmentationType)
				{
					case SegmentationType.Invalid:
						if (0 != value && 7 != value)
							throw new ArgumentOutOfRangeException("value", @"HighBit has to be 0 or 7");
						break;
					case SegmentationType.BINARY:
						if (0 != value)
							throw new ArgumentOutOfRangeException("value", @"HighBit has to be 0 for BINARY segmentation type.");
						break;
					default:
						if (7 != value)
							throw new ArgumentOutOfRangeException("value", @"HighBit has to be 7 for non-BINARY segmentation type.");
						break;
				}
				DicomAttributeProvider[DicomTags.HighBit].SetUInt16(0, value);
			}
		}

		/// <summary>
		/// Gets or sets the lossy image compression. Type 1.
		/// <para>00 = Image has NOT been subjected to lossy compression.</para>
		/// 	<para>01 = Image has been subjected to lossy compression.</para>
		/// </summary>
		/// <value>The lossy image compression. Default value is 00.</value>
		public string LossyImageCompression
		{
			get { return DicomAttributeProvider[DicomTags.LossyImageCompression].GetString(0, String.Empty); }
			set { DicomAttributeProvider[DicomTags.LossyImageCompression].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets the lossy image compression ratio. Type 1C.
		/// Describes the approximate lossy compression ratio(s) that have been applied to this image.
		/// </summary>
		/// <value>The lossy image compression ration. See C.7.6.1.1.5 for further explanation.</value>
		public float LossyImageCompressionRatio
		{
			get { return DicomAttributeProvider[DicomTags.LossyImageCompressionRatio].GetFloat32(0, 0.0F); }
			set { DicomAttributeProvider[DicomTags.LossyImageCompressionRatio].SetFloat32(0, value); }
		}

		/// <summary>
		/// Gets or sets the lossy image compression method label. Type 1C.
		/// A label for the lossy compression method(s) that have been applied to this image.
		/// </summary>
		/// <value>The lossy image compression method label. See C.7.6.1.1.5 for further explanation.</value>
		public string LossyImageCompressionMethod
		{
			get { return DicomAttributeProvider[DicomTags.LossyImageCompressionMethod].GetString(0, String.Empty); }
			set { DicomAttributeProvider[DicomTags.LossyImageCompressionMethod].SetString(0, value); }
		}

		/// <summary>
		/// Get or set the value of SegmentationType in the underlying collection. Type 1.
		/// </summary>
		public SegmentationType SegmentationType
		{
			get { return ParseEnum(DicomAttributeProvider[DicomTags.SegmentationType].GetString(0, string.Empty), SegmentationType.Invalid); }
			set
			{
				if (value == SegmentationType.Invalid)
					throw new ArgumentOutOfRangeException("value", @"SegmentationType cannot be invalid.");
				SetAttributeFromEnum(DicomAttributeProvider[DicomTags.SegmentationType], value);
			}
		}

		/// <summary>
		/// Get or set the value of SegmentationFractionalType in the underlying collection. Type 1C.
		/// </summary>
		public SegmentationFractionalType SegmentationFractionalType
		{
			get { return ParseEnum(DicomAttributeProvider[DicomTags.SegmentationFractionalType].GetString(0, string.Empty), SegmentationFractionalType.None); }
			set { SetAttributeFromEnum(DicomAttributeProvider[DicomTags.SegmentationType], value); }
		}

		/// <summary>
		/// Gets or sets the MaximumFractionalValue in the underlying collection. Type 1C.
		/// </summary>
		public ushort MaximumFractionalValue
		{
			get { return DicomAttributeProvider[DicomTags.MaximumFractionalValue].GetUInt16(0, 0); }
			set { DicomAttributeProvider[DicomTags.MaximumFractionalValue].SetUInt16(0, value); }
		}

		/// <summary>
		/// Gets or sets SegmentSequence. Type 1
		/// </summary>
		public SegmentSequence[] SegmentSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.SegmentSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new SegmentSequence[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new SegmentSequence(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.SegmentSequence] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				DicomAttributeProvider[DicomTags.SegmentSequence].Values = result;
			}
		}

		public SegmentSequence CreateSegmentSequence()
		{
			SegmentSequence iodBase = new SegmentSequence(new DicomSequenceItem());
			iodBase.InitializeAttributes();
			return iodBase;
		}
	}


	/// <summary>
	/// AlternateContentDescription Sequence
	/// </summary>
	/// <remarks>As defined in PS 3.3-2011, Section 10.9 (Table 10-12)</remarks>
	public class AlternateContentDescriptionSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="AlternateContentDescriptionSequenceItem"/> class.
		/// </summary>
		public AlternateContentDescriptionSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="AlternateContentDescriptionSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public AlternateContentDescriptionSequenceItem(DicomSequenceItem dicomSequenceItem)
			: base(dicomSequenceItem) { }

		/// <summary>
		/// Gets or sets the value of ContentDescription in the underlying collection. Type 1.
		/// </summary>
		public string ContentDescription
		{
			get { return DicomAttributeProvider[DicomTags.ContentDescription].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", @"ContentDescription is Type 1 Required.");

				DicomAttributeProvider[DicomTags.ContentDescription].SetString(0, value);
			}
		}

		public CodeSequenceMacro LanguageCodeSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.LanguageCodeSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}
				return new CodeSequenceMacro(((DicomSequenceItem[])dicomAttribute.Values)[0]);
			}
			set
			{
				if (null == value)
					throw new ArgumentNullException("value", @"LanguageCodeSequence is Type 1 Required");

				var dicomAttribute = DicomAttributeProvider[DicomTags.LanguageCodeSequence];
				dicomAttribute.Values = new[] { value.DicomSequenceItem };
			}
		}
	}
}
