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
using ClearCanvas.Dicom.Iod;
using ClearCanvas.Dicom.Iod.Macros;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// Specimen Module
	/// </summary>
	/// <remarks>As defined by PS 3.3-2011, Section C.7.6.22 (Table C.7.6.22-1)</remarks>
	public class SpecimenModuleIod : IodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenModuleIod"/> class.
		/// </summary>	
		public SpecimenModuleIod() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenModuleIod"/> class.
		/// </summary>
		public SpecimenModuleIod(IDicomAttributeProvider dicomAttributeProvider) : base(dicomAttributeProvider) { }

		/// <summary>
		/// Gets an enumeration of <see cref="DicomTag"/>s used by this module.
		/// </summary>
		public static IEnumerable<uint> DefinedTags
		{
			get
			{
				yield return DicomTags.ContainerIdentifier;
				yield return DicomTags.IssuerOfTheContainerIdentifierSequence;
				yield return DicomTags.AlternateContainerIdentifierSequence;
				yield return DicomTags.ContainerTypeCodeSequence;
				yield return DicomTags.ContainerDescription;
				yield return DicomTags.ContainerComponentSequence;
				yield return DicomTags.SpecimenDescriptionSequence;
			}
		}

		/// <summary>
		/// Initializes the underlying collection to implement the module or sequence using default values.
		/// </summary>
		public void InitializeAttributes()
		{
			ContainerIdentifier = "";
			IssuerOfTheContainterIdentifier = null;
			AlternateContainerIdentifierSequence = null;
			ContainerTypeCodeSequence = null;
			ContainerDescription = null;
			ContainerComponentSequence = null;
			SpecimenDescriptionSequence = null; // ?
		}

		/// <summary>
		/// Gets or sets Container Identifier value. Type 1.
		/// </summary>
		public string ContainerIdentifier
		{
			get { return DicomAttributeProvider[DicomTags.ContainerIdentifier].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ContainerIdentifier].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets IssuerOfTheContainterIdentifier value. Type 2.
		/// </summary>
		public HL7v2HierarchicDesignatorMacroIod IssuerOfTheContainterIdentifier
		{
			get { return this.GetSingleValueFromSequence<SpecimenModuleIod, HL7v2HierarchicDesignatorMacroIod>(DicomTags.IssuerOfTheContainerIdentifierSequence); }
			set { this.SetSingleValueInSequence(DicomTags.IssuerOfTheContainerIdentifierSequence, value); }
		}

		/// <summary>
		/// Gets or sets AlternateContainerIdentifierSequence values. Type 3.
		/// </summary>
		/// <value>Sequence of alternate identifiers for the container that contains the specimen(s) being imaged. One or more Items are permitted in this sequence.</value>
		public AlternateContainerIdentifierSequenceItem[] AlternateContainerIdentifierSequence
		{
			get { return this.GetSequenceValues<SpecimenModuleIod, AlternateContainerIdentifierSequenceItem>(DicomTags.AlternateContainerIdentifierSequence); }
			set { this.SetSequenceValues(DicomTags.AlternateContainerIdentifierSequence, value); }
		}

		/// <summary>
		/// Gets or sets IssuerOfTheContainterIdentifier value. Type 2.
		/// </summary>
		public CodeSequenceMacro ContainerTypeCodeSequence
		{
			get { return this.GetSingleValueFromSequence<SpecimenModuleIod, CodeSequenceMacro>(DicomTags.ContainerTypeCodeSequence); }
			set { this.SetSingleValueInSequence(DicomTags.ContainerTypeCodeSequence, value); }
		}

		/// <summary>
		/// Gets or sets Container Description value. Type 3.
		/// </summary>
		public string ContainerDescription
		{
			get { return DicomAttributeProvider[DicomTags.ContainerDescription].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ContainerDescription].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets Container Component Sequence value. Type 3.
		/// </summary>
		/// <remarks>One or more items are permitted in this sequence</remarks>
		public ContainerComponentSequenceItem[] ContainerComponentSequence
		{
			get { return this.GetSequenceValues<SpecimenModuleIod, ContainerComponentSequenceItem>(DicomTags.ContainerComponentSequence); }
			set { this.SetSequenceValues(DicomTags.ContainerComponentSequence, value); }
		}

		/// <summary>
		/// Gets or sets Specimen Description Sequence value. Type 1.
		/// </summary>
		public SpecimenDescriptionSequenceItem[] SpecimenDescriptionSequence
		{
			get { return this.GetSequenceValues<SpecimenModuleIod, SpecimenDescriptionSequenceItem>(DicomTags.SpecimenDescriptionSequence); }
			set { this.SetSequenceValues(DicomTags.SpecimenDescriptionSequence, value); }
		}
	}


	public class AlternateContainerIdentifierSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="AlternateContainerIdentifierSequenceItem"/> class.
		/// </summary>
		public AlternateContainerIdentifierSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="AlternateContainerIdentifierSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public AlternateContainerIdentifierSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		/// Gets or sets Container Identifier value. Type 1.
		/// </summary>
		public string ContainerIdentifier
		{
			get { return DicomAttributeProvider[DicomTags.ContainerIdentifier].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ContainerIdentifier].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets IssuerOfTheContainterIdentifier value. Type 2.
		/// </summary>
		public HL7v2HierarchicDesignatorMacroIod IssuerOfTheContainterIdentifier
		{
			get { return this.GetSingleValueFromSequence<AlternateContainerIdentifierSequenceItem, HL7v2HierarchicDesignatorMacroIod>(DicomTags.IssuerOfTheContainerIdentifierSequence); }
			set { this.SetSingleValueInSequence(DicomTags.IssuerOfTheContainerIdentifierSequence, value); }
		}
	}

	public class ContainerComponentSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="ContainerComponentSequenceItem"/> class.
		/// </summary>
		public ContainerComponentSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="ContainerComponentSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public ContainerComponentSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		/// Gets or sets ContainerComponentTypeCodeSequence value. Type 1.
		/// </summary>
		public CodeSequenceMacro ContainerComponentTypeCodeSequence
		{
			get { return this.GetSingleValueFromSequence<ContainerComponentSequenceItem, CodeSequenceMacro>(DicomTags.ContainerComponentTypeCodeSequence); }
			set { this.SetSingleValueInSequence(DicomTags.ContainerComponentTypeCodeSequence, value); }
		}

		/// <summary>
		///  Gets or sets Manufacturer value. Type 3
		/// </summary>
		public string Manufacturer
		{
			get { return DicomAttributeProvider[DicomTags.Manufacturer].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.Manufacturer].SetString(0, value); }
		}

		/// <summary>
		///  Gets or sets ManufacturersModelName value. Type 3
		/// </summary>
		public string ManufacturersModelName
		{
			get { return DicomAttributeProvider[DicomTags.ManufacturersModelName].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ManufacturersModelName].SetString(0, value); }
		}

		/// <summary>
		///  Gets or sets ContainerComponentId value. Type 3
		/// </summary>
		/// <value>Manufacturer’s identifier of the container component, e.g., Lot Number and/or Version.</value>
		public string ContainerComponentId
		{
			get { return DicomAttributeProvider[DicomTags.ContainerComponentId].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ContainerComponentId].SetString(0, value); }
		}

		/// <summary>
		///  Gets or sets ContainerComponentLength value. Type 3
		/// </summary>
		/// <value>Length in mm of container component.</value>
		public double? ContainerComponentLength
		{
			get
			{
				double result;
				if (DicomAttributeProvider[DicomTags.ContainerComponentLength].TryGetFloat64(0, out result))
					return result;
				return null;
			}
			set
			{
				if (value.HasValue)
					DicomAttributeProvider[DicomTags.ContainerComponentLength].SetFloat64(0, value.Value);
				else
					DicomAttributeProvider[DicomTags.ContainerComponentLength] = null;
			}
		}

		/// <summary>
		///  Gets or sets ContainerComponentWidth value. Type 3
		/// </summary>
		/// <value>Width in mm of container component.</value>
		public double? ContainerComponentWidth
		{
			get
			{
				double result;
				if (DicomAttributeProvider[DicomTags.ContainerComponentWidth].TryGetFloat64(0, out result))
					return result;
				return null;
			}
			set
			{
				if (value.HasValue)
					DicomAttributeProvider[DicomTags.ContainerComponentWidth].SetFloat64(0, value.Value);
				else
					DicomAttributeProvider[DicomTags.ContainerComponentWidth] = null;
			}
		}

		/// <summary>
		///  Gets or sets ContainerComponentDiameter value. Type 3
		/// </summary>
		/// <value>Diameter in mm of container component for cylindrical or circular components..</value>
		public double? ContainerComponentDiameter
		{
			get
			{
				double result;
				if (DicomAttributeProvider[DicomTags.ContainerComponentDiameter].TryGetFloat64(0, out result))
					return result;
				return null;
			}
			set
			{
				if (value.HasValue)
					DicomAttributeProvider[DicomTags.ContainerComponentDiameter].SetFloat64(0, value.Value);
				else
					DicomAttributeProvider[DicomTags.ContainerComponentDiameter] = null;
			}
		}

		/// <summary>
		///  Gets or sets ContainerComponentThickness value. Type 3
		/// </summary>
		/// <value>Thickness in mm of container component.</value>
		public double? ContainerComponentThickness
		{
			get
			{
				double result;
				if (DicomAttributeProvider[DicomTags.ContainerComponentThickness].TryGetFloat64(0, out result))
					return result;
				return null;
			}
			set
			{
				if (value.HasValue)
					DicomAttributeProvider[DicomTags.ContainerComponentThickness].SetFloat64(0, value.Value);
				else
					DicomAttributeProvider[DicomTags.ContainerComponentThickness] = null;
			}
		}

		/// <summary>
		///  Gets or sets material of container component. Type 3
		/// </summary>
		public ContainerComponentMaterial ContainerComponentMaterial
		{
			get { return ParseEnum(DicomAttributeProvider[DicomTags.ContainerComponentMaterial].GetString(0, string.Empty), ContainerComponentMaterial.NONE); }
			set { SetAttributeFromEnum(DicomAttributeProvider[DicomTags.PhotometricInterpretation], value); }
		}

		/// <summary>
		///  Gets or sets ContainerComponentDescription value. Type 3
		/// </summary>
		public string ContainerComponentDescription
		{
			get { return DicomAttributeProvider[DicomTags.ContainerComponentDescription].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.ContainerComponentDescription].SetString(0, value); }
		}
	}

	/// <summary>
	/// Values of container component material as defined by PS 3.3-2011, Section C.7.6.22 (Table C.7.6.22-1)
	/// </summary>
	public enum ContainerComponentMaterial
	{
		/// <summary>
		/// Glass material
		/// </summary>
		GLASS,

		/// <summary>
		/// Plastic material
		/// </summary>
		PLASTIC,

		/// <summary>
		/// Metal material
		/// </summary>
		METAL,

		/// <summary>
		/// Unknown material
		/// </summary>
		NONE
	}

	public class SpecimenDescriptionSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenDescriptionSequenceItem"/> class.
		/// </summary>
		public SpecimenDescriptionSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenDescriptionSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public SpecimenDescriptionSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		///  Gets or sets SpecimenIdentifier value. Type 1
		/// </summary>
		public string SpecimenIdentifier
		{
			get { return DicomAttributeProvider[DicomTags.SpecimenIdentifier].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.SpecimenIdentifier].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets IssuerOfTheSpecimenIdentifierSequence value. Type 2.
		/// </summary>
		public HL7v2HierarchicDesignatorMacroIod IssuerOfTheSpecimenIdentifierSequence
		{
			get { return this.GetSingleValueFromSequence<SpecimenDescriptionSequenceItem, HL7v2HierarchicDesignatorMacroIod>(DicomTags.IssuerOfTheSpecimenIdentifierSequence); }
			set { this.SetSingleValueInSequence(DicomTags.IssuerOfTheSpecimenIdentifierSequence, value); }
		}

		/// <summary>
		///  Gets or sets SpecimenUid value. Type 1
		/// </summary>
		public string SpecimenUid
		{
			get { return DicomAttributeProvider[DicomTags.SpecimenUid].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.SpecimenUid].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets SpecimenTypeCodeSequence value. Type 3.
		/// </summary>
		public CodeSequenceMacro SpecimenTypeCodeSequence
		{
			get { return this.GetSingleValueFromSequence<SpecimenDescriptionSequenceItem, CodeSequenceMacro>(DicomTags.SpecimenTypeCodeSequence); }
			set { this.SetSingleValueInSequence(DicomTags.SpecimenTypeCodeSequence, value); }
		}

		/// <summary>
		///  Gets or sets SpecimenShortDescription value. Type 3
		/// </summary>
		public string SpecimenShortDescription
		{
			get { return DicomAttributeProvider[DicomTags.SpecimenShortDescription].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.SpecimenShortDescription].SetString(0, value); }
		}

		/// <summary>
		///  Gets or sets SpecimenDetailedDescription value. Type 3.
		/// </summary>
		public string SpecimenDetailedDescription
		{
			get { return DicomAttributeProvider[DicomTags.SpecimenDetailedDescription].GetString(0, string.Empty); }
			set { DicomAttributeProvider[DicomTags.SpecimenDetailedDescription].SetString(0, value); }
		}

		/// <summary>
		/// Gets or sets SpecimenPreparationSequence items. Type 2.
		/// </summary>
		/// <remarks>Zero or more Items shall be included in this sequence.</remarks>
		public SpecimenPreparationSequenceItem[] SpecimenPreparationSequence
		{
			get { return this.GetSequenceValues<SpecimenDescriptionSequenceItem, SpecimenPreparationSequenceItem>(DicomTags.SpecimenPreparationSequence); }
			set { this.SetSequenceValues(DicomTags.SpecimenPreparationSequence, value); }
		}

		/// <summary>
		/// Gets or sets PrimaryAnatomicStructure macro value. Type 3.
		/// </summary>
		public PrimaryAnatomicStructureMacro PrimaryAnatomicStructure
		{
			// TODO - test if this works
			get { return new PrimaryAnatomicStructureMacro(DicomSequenceItem); }
			set { new PrimaryAnatomicStructureMacro(DicomSequenceItem).PrimaryAnatomicStructureSequence = value == null ? null : value.PrimaryAnatomicStructureSequence; }
		}

		/// <summary>
		/// Gets or sets SpecimenLocalizationContentItemSequence values. Type 1C.
		/// </summary>
		/// <remarks>One or more Items shall be included in this sequence. Required if multiple specimens present in the image. May be present otherwise.</remarks>
		public ContentItemMacro[] SpecimenLocalizationContentItemSequence
		{
			get { return this.GetSequenceValues<SpecimenDescriptionSequenceItem, ContentItemMacro>(DicomTags.SpecimenLocalizationContentItemSequence); }
			set { this.SetSequenceValues(DicomTags.SpecimenLocalizationContentItemSequence, value); }
		}
	}

	public class SpecimenPreparationSequenceItem : SequenceIodBase
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenPreparationSequenceItem"/> class.
		/// </summary>
		public SpecimenPreparationSequenceItem() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="SpecimenPreparationSequenceItem"/> class.
		/// </summary>
		/// <param name="dicomSequenceItem">The dicom sequence item.</param>
		public SpecimenPreparationSequenceItem(DicomSequenceItem dicomSequenceItem) : base(dicomSequenceItem) { }

		/// <summary>
		/// Gets of sets SpecimenPreparationStepContentItemSequence values. Type 1.
		/// </summary>
		/// <remarks>One or more Items shall be included in this sequence.</remarks>
		public ContentItemMacro[] SpecimenPreparationStepContentItemSequence
		{
			get { return this.GetSequenceValues<SpecimenPreparationSequenceItem, ContentItemMacro>(DicomTags.SpecimenPreparationStepContentItemSequence); }
			set { this.SetSequenceValues(DicomTags.SpecimenPreparationStepContentItemSequence, value); }
		}
	}
}
