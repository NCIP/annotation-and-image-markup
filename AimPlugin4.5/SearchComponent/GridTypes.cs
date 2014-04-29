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
using ClearCanvas.Common.Utilities;

namespace SearchComponent
{
	public interface ICodeSequenceItem
	{
		string CodeValue { get; }
		string CodeMeaning { get; }
		string CodingSchemeDesignator { get; }
	}

	[Cloneable]
	public class AnatomicEntity : ICodeSequenceItem, IEquatable<AnatomicEntity>
	{
		private static List<AnatomicEntity> _avaliableAnatomicEntities;

		public AnatomicEntity()
		{ }

		protected AnatomicEntity(string codeValue, string codeMeaning, string codingSchemeDesignator)
		{
			_codeValue = codeValue;
			_codeMeaning = codeMeaning;
			_codingSchemeDesignator = codingSchemeDesignator;
		}

		private string _codeValue;
		public string CodeValue
		{
			get { return _codeValue; }
			set { _codeValue = value; }
		}


		private string _codeMeaning;
		public string CodeMeaning
		{
			get { return _codeMeaning; }
			set { _codeMeaning = value; }
		}

		private string _codingSchemeDesignator;
		public string CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator; }
			set { _codingSchemeDesignator = value; }
		}

		public static List<AnatomicEntity> GetAllAvailableEntities()
		{
			if (_avaliableAnatomicEntities == null)
				_avaliableAnatomicEntities = CreateAvailableAnatomicEntities();

			return _avaliableAnatomicEntities;
		}

		private static List<AnatomicEntity> CreateAvailableAnatomicEntities()
		{
			List<AnatomicEntity> daList = new List<AnatomicEntity>();
			daList.Add(new AnatomicEntity("77", "occipital lobe", "VASARI"));
			daList.Add(new AnatomicEntity("73", "frontal lobe", "VASARI"));
			daList.Add(new AnatomicEntity("76", "parietal lobe", "VASARI"));
			daList.Add(new AnatomicEntity("79", "brain stem", "VASARI"));
			daList.Add(new AnatomicEntity("78", "cerebellum", "VASARI"));
			daList.Add(new AnatomicEntity("75", "insula", "VASARI"));
			daList.Add(new AnatomicEntity("74", "temporal lobe", "VASARI"));
			return daList;
		}

		public override bool Equals(object obj)
		{
			if (obj is AnatomicEntity)
				return Equals((AnatomicEntity)obj);

			return base.Equals(obj);
		}

		#region IEquatable<AnatomicEntity> Members

		public bool Equals(AnatomicEntity other)
		{
			if (other == null)
				return false;

			return other.CodeValue == CodeValue;
		}

		#endregion

		public override string ToString()
		{
			return string.Format("[{0}], [{1}], [{2}]", this.CodeValue ?? "", this.CodeMeaning ?? "", this.CodingSchemeDesignator ?? "");
		}
	}

	[Cloneable]
	public class AnatomicEntityCharacteristic : ICodeSequenceItem, IEquatable<AnatomicEntityCharacteristic>
	{
		private static List<AnatomicEntity> _avaliableAnatomicEntities;

		public AnatomicEntityCharacteristic()
		{ }

		protected AnatomicEntityCharacteristic(string codeValue, string codeMeaning, string codingSchemeDesignator)
		{
			_codeValue = codeValue;
			_codeMeaning = codeMeaning;
			_codingSchemeDesignator = codingSchemeDesignator;
		}

		private string _codeValue;
		public string CodeValue
		{
			get { return _codeValue; }
			set { _codeValue = value; }
		}


		private string _codeMeaning;
		public string CodeMeaning
		{
			get { return _codeMeaning; }
			set { _codeMeaning = value; }
		}

		private string _codingSchemeDesignator;
		public string CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator; }
			set { _codingSchemeDesignator = value; }
		}

		public override bool Equals(object obj)
		{
			if (obj is AnatomicEntityCharacteristic)
				return Equals((AnatomicEntityCharacteristic)obj);

			return base.Equals(obj);
		}

		#region IEquatable<AnatomicEntity> Members

		public bool Equals(AnatomicEntityCharacteristic other)
		{
			if (other == null)
				return false;

			return other.CodeValue == CodeValue;
		}

		#endregion

		public override string ToString()
		{
			return string.Format("[{0}], [{1}], [{2}]", this.CodeValue ?? "", this.CodeMeaning ?? "", this.CodingSchemeDesignator ?? "");
		}
	}


	[Cloneable]
	public class ImagingObservation : ICodeSequenceItem, IEquatable<ImagingObservation>
	{
		private static List<ImagingObservation> _availableImagingObservations;

		public ImagingObservation()
		{
		}

		protected ImagingObservation(string codeValue, string codeMeaning, string codingSchemeDesignator)
		{
			_codeValue = codeValue;
			_codeMeaning = codeMeaning;
			_codingSchemeDesignator = codingSchemeDesignator;
		}

		private string _codeValue;
		public string CodeValue
		{
			get { return _codeValue; }
			set { _codeValue = value; }
		}

		private string _codeMeaning;
		public string CodeMeaning
		{
			get { return _codeMeaning; }
			set { _codeMeaning = value; }
		}

		private string _codingSchemeDesignator;
		public string CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator; }
			set { _codingSchemeDesignator = value; }
		}

		public override bool Equals(object obj)
		{
			if (obj is ImagingObservation)
				return Equals((ImagingObservation)obj);

			return base.Equals(obj);
		}

		#region IEquatable<ImagingObservation> Members

		public bool Equals(ImagingObservation other)
		{
			if (other == null)
				return false;

			return other.CodeValue == CodeValue;
		}

		#endregion

		public override string ToString()
		{
			return string.Format("[{0}], [{1}], [{2}]", this.CodeValue ?? "", this.CodeMeaning ?? "", this.CodingSchemeDesignator ?? "");
		}

		public static List<ImagingObservation> GetAllAvailableObservations()
		{
			if (_availableImagingObservations == null)
				_availableImagingObservations = CreateAvailableImagingObservations();

			return _availableImagingObservations;
		}

		private static List<ImagingObservation> CreateAvailableImagingObservations()
		{
			List<ImagingObservation> daList = new List<ImagingObservation>();
			daList.Add(new ImagingObservation("94", "ependymal invasion absent", "VASARI"));
			daList.Add(new ImagingObservation("93", "ependymal invasion present", "VASARI"));
			daList.Add(new ImagingObservation("71", "smooth non-enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("70", "non-enhancing margin not applicable", "VASARI"));
			daList.Add(new ImagingObservation("72", "irregular non-enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("92", "infiltrative T1/FLAIR ratio", "VASARI"));
			daList.Add(new ImagingObservation("90", "expansive T1/FLAIR ratio", "VASARI"));
			daList.Add(new ImagingObservation("95", "T1/FLAIR ratio not applicable", "VASARI"));
			daList.Add(new ImagingObservation("91", "mixed T1/FLAIR ratio", "VASARI"));
			daList.Add(new ImagingObservation("59", "greater than 95% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("57", "34-67% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("56", "6-33% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("58", "68-95% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("55", "less than 5% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("54", "no enhancement", "VASARI"));
			daList.Add(new ImagingObservation("53", "enhancement indeterminate", "VASARI"));
			daList.Add(new ImagingObservation("60", "100% enhancement", "VASARI"));
			daList.Add(new ImagingObservation("52", "proportion of enhancement not applicable", "VASARI"));
			daList.Add(new ImagingObservation("64", "center epicenter", "VASARI"));
			daList.Add(new ImagingObservation("66", "left epicenter", "VASARI"));
			daList.Add(new ImagingObservation("65", "right epicenter", "VASARI"));
			daList.Add(new ImagingObservation("61", "ncet tumor does cross midline", "VASARI"));
			daList.Add(new ImagingObservation("63", "ncet tumor crosses midline not applicable", "VASARI"));
			daList.Add(new ImagingObservation("62", "ncet tumor does not cross midline", "VASARI"));
			daList.Add(new ImagingObservation("3", "enhancing tumor crosses midline not applicable", "VASARI"));
			daList.Add(new ImagingObservation("1", "enhancing tumor does cross midline", "VASARI"));
			daList.Add(new ImagingObservation("2", "enhancing tumor does not cross midline", "VASARI"));
			daList.Add(new ImagingObservation("34", "100% edema", "VASARI"));
			daList.Add(new ImagingObservation("32", "68-95% edema", "VASARI"));
			daList.Add(new ImagingObservation("28", "no edema", "VASARI"));
			daList.Add(new ImagingObservation("33", "greater than 95% edema", "VASARI"));
			daList.Add(new ImagingObservation("31", "34-67% edema", "VASARI"));
			daList.Add(new ImagingObservation("29", "less than 5% edema", "VASARI"));
			daList.Add(new ImagingObservation("27", "edema indeterminate", "VASARI"));
			daList.Add(new ImagingObservation("30", "6-33% edema", "VASARI"));
			daList.Add(new ImagingObservation("49", "68-95% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("48", "34-67% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("43", "proportion of necrosis not applicable", "VASARI"));
			daList.Add(new ImagingObservation("46", "less than 5% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("45", "no necrosis", "VASARI"));
			daList.Add(new ImagingObservation("44", "necrosis indeterminate", "VASARI"));
			daList.Add(new ImagingObservation("51", "100% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("50", "greater than 95% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("47", "6-33% necrosis", "VASARI"));
			daList.Add(new ImagingObservation("19", "no ncet", "VASARI"));
			daList.Add(new ImagingObservation("23", "68-95% ncet", "VASARI"));
			daList.Add(new ImagingObservation("24", "greater than 95% ncet", "VASARI"));
			daList.Add(new ImagingObservation("17", "proportion of ncet not applicable", "VASARI"));
			daList.Add(new ImagingObservation("20", "less than 5% ncet", "VASARI"));
			daList.Add(new ImagingObservation("25", "100% ncet", "VASARI"));
			daList.Add(new ImagingObservation("18", "ncet indeterminate", "VASARI"));
			daList.Add(new ImagingObservation("22", "34-67% ncet", "VASARI"));
			daList.Add(new ImagingObservation("21", "6-33% ncet", "VASARI"));
			daList.Add(new ImagingObservation("10", "poorly-defined enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("12", "enhancing margin definition not applicable", "VASARI"));
			daList.Add(new ImagingObservation("11", "well-defined enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("80", "no enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("81", "thin enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("82", "thick enhancing margin", "VASARI"));
			daList.Add(new ImagingObservation("15", "multicentric", "VASARI"));
			daList.Add(new ImagingObservation("16", "multifocal", "VASARI"));
			daList.Add(new ImagingObservation("14", "gliomatosis", "VASARI"));
			daList.Add(new ImagingObservation("13", "morphology region not applicable", "VASARI"));
			daList.Add(new ImagingObservation("69", "marked/avid enhancement", "VASARI"));
			daList.Add(new ImagingObservation("68", "mild/minimal enhancement", "VASARI"));
			daList.Add(new ImagingObservation("67", "no enhancement", "VASARI"));
			daList.Add(new ImagingObservation("6", "deep wm invasion present", "VASARI"));
			daList.Add(new ImagingObservation("7", "deep wm invasion absent", "VASARI"));
			daList.Add(new ImagingObservation("84", "tumor", "VASARI"));
			daList.Add(new ImagingObservation("87", "speech receptive center involvement", "VASARI"));
			daList.Add(new ImagingObservation("89", "vision center involvement", "VASARI"));
			daList.Add(new ImagingObservation("88", "motor center involvement", "VASARI"));
			daList.Add(new ImagingObservation("86", "speech motor center involvement", "VASARI"));
			daList.Add(new ImagingObservation("85", "no eloquent brain involvement", "VASARI"));
			return daList;
		}
	}

	[Cloneable]
	public class ImagingObservationCharacteristic : ICodeSequenceItem, IEquatable<ImagingObservationCharacteristic>
	{
		private static List<ImagingObservationCharacteristic> _availableImagingObservations;

		public ImagingObservationCharacteristic()
		{
		}

		protected ImagingObservationCharacteristic(string codeValue, string codeMeaning, string codingSchemeDesignator)
		{
			_codeValue = codeValue;
			_codeMeaning = codeMeaning;
			_codingSchemeDesignator = codingSchemeDesignator;
		}

		private string _codeValue;
		public string CodeValue
		{
			get { return _codeValue; }
			set { _codeValue = value; }
		}

		private string _codeMeaning;
		public string CodeMeaning
		{
			get { return _codeMeaning; }
			set { _codeMeaning = value; }
		}

		private string _codingSchemeDesignator;
		public string CodingSchemeDesignator
		{
			get { return _codingSchemeDesignator; }
			set { _codingSchemeDesignator = value; }
		}

		private string _comment;
		public string Comment
		{
			get { return _comment; }
			set { _comment = value; }
		}

		public override bool Equals(object obj)
		{
			if (obj is ImagingObservation)
				return Equals((ImagingObservation)obj);

			return base.Equals(obj);
		}

		#region IEquatable<ImagingObservation> Members

		public bool Equals(ImagingObservationCharacteristic other)
		{
			if (other == null)
				return false;

			return other.CodeValue == CodeValue;
		}

		#endregion

		public override string ToString()
		{
			return string.Format("[{0}], [{1}], [{2}]", this.CodeValue ?? "", this.CodeMeaning ?? "", this.CodingSchemeDesignator ?? "");
		}
	}

	[Cloneable]
	public class TrialDataProvenance
	{
		public TrialDataProvenance()
		{ }

		private string project;
		public string Project
		{
			get { return project; }
			set { project = value; }
		}
	}

	[Cloneable]
	public class ClinicalTrialProtocol
	{
		public ClinicalTrialProtocol()
		{ }

		private string protocolId;
		public string ProtocolId
		{
			get { return protocolId; }
			set { protocolId = value; }
		}

		private string protocolName;
		public string ProtocolName
		{
			get { return protocolName; }
			set { protocolName = value; }
		}
	}

	[Cloneable]
	public class ClinicalTrialSite
	{
		public ClinicalTrialSite()
		{ }

		private string siteId;
		public string SiteId
		{
			get { return siteId; }
			set { siteId = value; }
		}

		private string siteName;
		public string SiteName
		{
			get { return siteName; }
			set { siteName = value; }
		}
	}

	[Cloneable]
	public class Patient
	{
		public Patient()
		{ }

		private DateTime? patientBirthDate;
		public DateTime? PatientBirthDate
		{
			get { return patientBirthDate; }
			set { patientBirthDate = value; }
		}

		private string patientId;
		public string PatientId
		{
			get { return patientId; }
			set { patientId = value; }
		}

		private string patientsName;
		public string PatientsName
		{
			get { return patientsName; }
			set { patientsName = value; }
		}

		private string patientsSex;
		public string PatientsSex
		{
			get { return patientsSex; }
			set { patientsSex = value; }
		}
	}

	[Cloneable]
	public class User
	{
		public User() { }

		private int caGridId;
		public int CaGridId
		{
			get { return caGridId; }
			set { caGridId = value; }
		}

		private string name;
		public string Name
		{
			get { return name; }
			set { name = value; }
		}

		private string loginName;
		public string LoginName
		{
			get { return loginName; }
			set { loginName = value; }
		}

		private string roleInTrial;
		public string RoleInTrial
		{
			get { return roleInTrial; }
			set { roleInTrial = value; }
		}

		private int numberWithinRoleInClinicalTrial;
		public int NumberWithinRoleInClinicalTrial
		{
			get { return numberWithinRoleInClinicalTrial; }
			set { numberWithinRoleInClinicalTrial = value; }
		}
	}

	[Cloneable]
	public class Study
	{
		public Study()
		{ }

		private string studyInstanceUid;
		public string StudyInstanceUid
		{
			get { return studyInstanceUid; }
			set { studyInstanceUid = value; }
		}
	}

	[Cloneable]
	public class Series
	{
		public Series()
		{ }

		private string seriesInstanceUid;
		public string SeriesInstanceUid
		{
			get { return seriesInstanceUid; }
			set { seriesInstanceUid = value; }
		}

		private string modality;
		public string Modality
		{
			get { return modality; }
			set { modality = value; }
		}
	}

	[Cloneable]
	public class Image
	{
		public Image()
		{ }

		private string sopInstanceUid;
		public string SopInstanceUid
		{
			get { return sopInstanceUid; }
			set { sopInstanceUid = value; }
		}

		private string sliceThickness;
		public string SliceThickness
		{
			get { return sliceThickness; }
			set { sliceThickness = value; }
		}
	}
}
