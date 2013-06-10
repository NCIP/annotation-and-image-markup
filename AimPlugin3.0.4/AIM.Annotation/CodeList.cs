#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;

using ClearCanvas.Common.Utilities;

namespace AIM.Annotation
{

	public class StandardValidTerm
	{
		private readonly StandardCodeSequence _standardCodeSequence;
		private readonly List<StandardValidTerm> _standardValidTerms;

		public StandardCodeSequence StandardCodeSequence { get { return _standardCodeSequence; } }

		public List<StandardValidTerm> StandardValidTerms { get { return _standardValidTerms; } } 

		public StandardValidTerm(StandardCodeSequence standardCodeSequence)
		{
			_standardCodeSequence = standardCodeSequence;
			_standardValidTerms = new List<StandardValidTerm>();
		}

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is StandardValidTerm))
				return false;

			var validTerm = (StandardValidTerm)obj;
			return (_standardCodeSequence == null
						? validTerm._standardCodeSequence == null
						: _standardCodeSequence.Equals(validTerm._standardCodeSequence)) &&
				   (_standardValidTerms == null
						? validTerm._standardValidTerms == null
						: CollectionUtils.Equal<StandardValidTerm>(_standardValidTerms, validTerm._standardValidTerms, true));

		}

		public override int GetHashCode()
		{
			var hashCode = _standardCodeSequence == null ? "".GetHashCode() : _standardCodeSequence.GetHashCode();
			if (_standardValidTerms != null)
				CollectionUtils.ForEach(_standardValidTerms, term => { if (term != null) hashCode ^= term.GetHashCode(); });
			return hashCode;
		}
	}

	public class StandardCodeSequence
    {
        private readonly string _codeValue;
        private readonly string _codeMeaning;
        private readonly string _codingSchemeDesignator;
        private readonly string _codingSchemeVersion;

        public StandardCodeSequence(string codeValue, string codeMeaning, string codingSchemeDesignator) :
            this(codeValue, codeMeaning, codingSchemeDesignator, null)
        {
        }

        public StandardCodeSequence(string codeValue, string codeMeaning, 
            string codingSchemeDesignator, string codingSchemeVersion)
        {
            _codeValue = codeValue;
            _codeMeaning = codeMeaning;
            _codingSchemeDesignator = codingSchemeDesignator;
            _codingSchemeVersion = codingSchemeVersion;
        }

        public string CodeValue
        {
            get { return _codeValue; }
        }

        public string CodeMeaning
        {
            get { return _codeMeaning; }
        }

        public string CodingSchemeDesignator
        {
            get { return _codingSchemeDesignator; }
        }

        public string CodingSchemeVersion
        {
            get { return _codingSchemeVersion; }
        }

        public override string ToString()
        {
            return string.Format("{0}({1})", CodeMeaning, CodeValue);
        }

        public override bool Equals(object obj)
        {
            if (obj == null || !(obj is StandardCodeSequence))
                return false;

        	var objCode = (StandardCodeSequence) obj;
        	return _codeValue == objCode._codeValue && _codeMeaning == objCode._codeMeaning && _codingSchemeDesignator == objCode._codingSchemeDesignator &&
        	       _codingSchemeVersion == objCode._codingSchemeVersion;
        }

        public override int GetHashCode()
        {
            return (CodeValue ?? "").GetHashCode() ^ (CodeMeaning ?? "").GetHashCode() ^ (CodingSchemeDesignator ?? "").GetHashCode() ^
                   (CodingSchemeVersion ?? "").GetHashCode();
        }
    }

	public class CodeList
	{
		public static StandardCodeSequence CalculationCodeForLength = new StandardCodeSequence("G-A22A", "Length", "SRT");
		public static StandardCodeSequence CalculationCodeForArea = new StandardCodeSequence("G-A166", "Area", "SRT");
		public static StandardCodeSequence CalculationCodeForMean = new StandardCodeSequence("R-00317", "Mean", "SRT");
		public static StandardCodeSequence CalculationCodeForStandardDeviation = new StandardCodeSequence("R-10047", "Standard Deviation", "SRT");
		public static StandardCodeSequence CalculationCodeForAngle = new StandardCodeSequence("XXX", "Angle", "AIM_TCGA");
	}
}
