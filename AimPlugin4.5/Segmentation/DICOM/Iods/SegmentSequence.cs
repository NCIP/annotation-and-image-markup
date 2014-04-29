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
using ClearCanvas.Dicom.Iod.Sequences;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// Segment Sequence as defined in DICOM PS 3.3-2011, Table C.8.20-2
	/// </summary>
	public class SegmentSequence : SequenceIodBase
	{
		#region Constructors
		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentSequence"/> class.
		/// </summary>
		public SegmentSequence() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentSequence"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public SegmentSequence(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }
		#endregion

		/// <summary>
		/// Initializes the underlying collection to implement the module or sequence using default values.
		/// </summary>
		public virtual void InitializeAttributes()
		{
			SegmentNumber = 1;
			SegmentLabel = " ";
			SegmentDescription = null;
			SegmentAlgorithmType = "MANUAL";
			AnatomicRegionSequence = null;
			SegmentedPropertyCategoryCodeSequence = null;
			SegmentedPropertyTypeCodeSequence = null;
			RecomendedDisplayCIELabValue = null;
		}

		/// <summary>
		/// Gets or sets SegmentNumber. Type 1.
		/// </summary>
		public int SegmentNumber
		{
			get { return DicomAttributeProvider[DicomTags.SegmentNumber].GetInt32(0, 1); }
			set
			{
				if (value < 1)
					throw new ArgumentOutOfRangeException("value", "SegmentNumber cannot be less than 1");
				DicomAttributeProvider[DicomTags.SegmentNumber].SetInt32(0, value);
			}
		}

		/// <summary>
		/// Gets or sets SegmentLabel. Type 1.
		/// </summary>
		public string SegmentLabel
		{
			get { return DicomAttributeProvider[DicomTags.SegmentLabel].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", "Segment Label cannot be empty");
				DicomAttributeProvider[DicomTags.SegmentLabel].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets SegmentDescription. Type 3.
		/// </summary>
		public string SegmentDescription
		{
			get { return DicomAttributeProvider[DicomTags.SegmentDescription].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					DicomAttributeProvider[DicomTags.SegmentDescription].SetNullValue();
				else
					DicomAttributeProvider[DicomTags.SegmentDescription].SetStringValue(value);
			}
		}

		/// <summary>
		/// Gets or sets SegmentAlgorithmType. Type 1.
		/// </summary>
		public string SegmentAlgorithmType
		{
			get { return DicomAttributeProvider[DicomTags.SegmentAlgorithmType].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					throw new ArgumentNullException("value", "SegmentAlgorithmType cannot be empty");
				DicomAttributeProvider[DicomTags.SegmentAlgorithmType].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets SegmentDescription. Type 1C.
		/// Name of algorithm used to generate the segment. Required if Segment Algorithm Type is not MANUAL.
		/// </summary>
		/// <value>The value of segment algorithm name</value>
		public string SegmentAlgorithmName
		{
			get { return DicomAttributeProvider[DicomTags.SegmentAlgorithmName].GetString(0, string.Empty); }
			set
			{
				if (string.IsNullOrEmpty(value))
					DicomAttributeProvider[DicomTags.SegmentAlgorithmName].SetNullValue();
				else
					DicomAttributeProvider[DicomTags.SegmentAlgorithmName].SetString(0, value);
			}
		}

		/// <summary>
		/// Gets or sets AnatomicRegionSequence. Type 3
		/// </summary>
		public AnatomicRegionSequenceItem[] AnatomicRegionSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.AnatomicRegionSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new AnatomicRegionSequenceItem[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new AnatomicRegionSequenceItem(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.AnatomicRegionSequence] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				DicomAttributeProvider[DicomTags.AnatomicRegionSequence].Values = result;
			}
		}

		public AnatomicRegionSequenceItem CreateAnatomicRegionSequence()
		{
			AnatomicRegionSequenceItem iodBase = new AnatomicRegionSequenceItem(new DicomSequenceItem());
			return iodBase;
		}

		/// <summary>
		/// Gets or sets SegmentedPropertyCategoryCodeSequence. Type 1
		/// </summary>
		/// <remarks>Only a single value in the sequence is supported</remarks>
		public CodeSequenceMacro[] SegmentedPropertyCategoryCodeSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.SegmentedPropertyCategoryCodeSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new CodeSequenceMacro[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new CodeSequenceMacro(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.SegmentedPropertyCategoryCodeSequence] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				DicomAttributeProvider[DicomTags.SegmentedPropertyCategoryCodeSequence].Values = result;
			}
		}

		public CodeSequenceMacro CreateSegmentedPropertyCategoryCodeSequence()
		{
			CodeSequenceMacro iodBase = new CodeSequenceMacro(new DicomSequenceItem());
			return iodBase;
		}

		/// <summary>
		/// Gets or sets SegmentedPropertyCategoryCodeSequence. Type 1
		/// </summary>
		/// <remarks>Only a single value in the sequence is supported</remarks>
		public SegmentedPropertyTypeCodeSequenceItem[] SegmentedPropertyTypeCodeSequence
		{
			get
			{
				var dicomAttribute = DicomAttributeProvider[DicomTags.SegmentedPropertyTypeCodeSequence];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new SegmentedPropertyTypeCodeSequenceItem[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new SegmentedPropertyTypeCodeSequenceItem(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					DicomAttributeProvider[DicomTags.SegmentedPropertyTypeCodeSequence] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				DicomAttributeProvider[DicomTags.SegmentedPropertyTypeCodeSequence].Values = result;
			}
		}

		public SegmentedPropertyTypeCodeSequenceItem CreateSegmentedPropertyTypeCodeSequence()
		{
			SegmentedPropertyTypeCodeSequenceItem iodBase = new SegmentedPropertyTypeCodeSequenceItem(new DicomSequenceItem());
			return iodBase;
		}

		/// <summary>
		/// Gets or sets RecomendedDisplayCIELabValue. Type 3.
		/// </summary>
		public CIELabColor? RecomendedDisplayCIELabValue
		{
			get
			{
				DicomAttribute attribute = DicomAttributeProvider[DicomTags.RecommendedDisplayCielabValue];
				if (attribute.IsEmpty || attribute.IsNull)
					return null;

				var values = attribute.Values as ushort[];
				if (values != null && values.Length >= 3)
					return new CIELabColor(values[0], values[1], values[2]);

				return null;
			}
			set
			{
				if (!value.HasValue)
					DicomAttributeProvider[DicomTags.RecommendedDisplayCielabValue] = null;
				else
					DicomAttributeProvider[DicomTags.RecommendedDisplayCielabValue].Values = value.Value.ToArray();
			}
		}

		/// <summary>
		/// Gets an enumeration of <see cref="DicomTag"/>s used by this module.
		/// </summary>
		public static IEnumerable<uint> DefinedTags
		{
			get
			{
				yield return DicomTags.SegmentNumber;
				yield return DicomTags.SegmentLabel;
				yield return DicomTags.SegmentDescription;
				yield return DicomTags.SegmentAlgorithmType;
				yield return DicomTags.SegmentAlgorithmName;
				yield return DicomTags.AnatomicRegionSequence;
				yield return DicomTags.SegmentedPropertyCategoryCodeSequence;
				yield return DicomTags.SegmentedPropertyTypeCodeSequence;
				yield return DicomTags.RecommendedDisplayCielabValue;
			}
		}
	}


	public class SegmentedPropertyTypeCodeSequenceItem : CodeSequenceMacro
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentedPropertyTypeCodeSequenceItem"/> class.
		/// </summary>
		public SegmentedPropertyTypeCodeSequenceItem()
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="SegmentedPropertyTypeCodeSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public SegmentedPropertyTypeCodeSequenceItem(DicomSequenceItem dicomSequenceItem)
			: base(dicomSequenceItem)
		{
		}

		// TODO: remove when tag (0062,0011) is added to the DicomTags collection
		// (0062,0011) from CP-1258 (2013-06-18)
		public static DicomTag SegmentedPropertyTypeModifierCodeSequenceDicomTag =
			new DicomTag(DicomTag.GetTagValue(0x0062, 0x0011), "Segmented Property Type Modifier Code Sequence", "SegmentedPropertyTypeModifierCodeSequence",
						 DicomVr.SQvr, false, 1, 1, false);

		public CodeSequenceMacro[] SegmentedPropertyTypeModifierCodeSequence
		{
			get
			{
				// TODO: fix the tag value!!! Cannot find SegmentedPropertyTypeModifierCodeSequence (0062,0011) anywhere
				var dicomAttribute = DicomAttributeProvider[SegmentedPropertyTypeModifierCodeSequenceDicomTag];
				if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
				{
					return null;
				}

				var result = new CodeSequenceMacro[dicomAttribute.Count];
				var items = (DicomSequenceItem[])dicomAttribute.Values;
				for (int n = 0; n < items.Length; n++)
					result[n] = new CodeSequenceMacro(items[n]);

				return result;
			}
			set
			{
				if (value == null || value.Length == 0)
				{
					// TODO: fix the tag value!!!
					DicomAttributeProvider[SegmentedPropertyTypeModifierCodeSequenceDicomTag] = null;
					return;
				}

				var result = new DicomSequenceItem[value.Length];
				for (int n = 0; n < value.Length; n++)
					result[n] = value[n].DicomSequenceItem;

				// TODO: fix the tag value!!!
				DicomAttributeProvider[SegmentedPropertyTypeModifierCodeSequenceDicomTag].Values = result;
			}
		}
	}
}
