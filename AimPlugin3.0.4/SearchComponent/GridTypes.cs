#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
        private static List<AnatomicEntity> _avaliableAnatomicEnities;

		public AnatomicEntity()
		{}

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
            if (_avaliableAnatomicEnities == null)
                _avaliableAnatomicEnities = CreateAvailableAnatomicEnities();

		    return _avaliableAnatomicEnities;
		}

        private static List<AnatomicEntity> CreateAvailableAnatomicEnities()
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
		private static List<AnatomicEntity> _avaliableAnatomicEnities;

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
		{}

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
        {}

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
