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
using System.Text;
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

			StandardValidTerm validTerm = (StandardValidTerm)obj;
			return (_standardCodeSequence == null
						? validTerm._standardCodeSequence == null
						: _standardCodeSequence.Equals(validTerm._standardCodeSequence)) &&
				   (_standardValidTerms == null
						? validTerm._standardValidTerms == null
						: CollectionUtils.Equal<StandardValidTerm>(_standardValidTerms, validTerm._standardValidTerms, true));

		}

		public override int GetHashCode()
		{
			int hashCode = _standardCodeSequence == null ? "".GetHashCode() : _standardCodeSequence.GetHashCode();
			if (_standardValidTerms != null)
				CollectionUtils.ForEach(_standardValidTerms, term => { if (term != null) hashCode ^= term.GetHashCode(); });
			return hashCode;
		}

		/// <summary>
		/// Recursively traverses given <paramref name="validTerm"/> and appends Code Meanings to the given <paramref name="sb"/>.
		/// This effectively flattens <paramref name="validTerm"/> to a string.
		/// </summary>
		/// <param name="validTerm">Standard Valid Term to traverse</param>
		/// <param name="sb">String Builder that receives the values</param>
		public static StringBuilder ToStringBuilder(StandardValidTerm validTerm, StringBuilder sb)
		{
			if (validTerm == null || sb == null)
				return sb;

			if (sb.Length > 0)
				sb.Append(" ");
			sb.Append(validTerm.StandardCodeSequence.CodeMeaning);
			// Traverse the tree in-order
			foreach (StandardValidTerm standardValidTerm in validTerm.StandardValidTerms)
				ToStringBuilder(standardValidTerm, sb);

			return sb;
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
			return string.Format("{0}({1})", this.CodeMeaning, this.CodeValue);
		}

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is StandardCodeSequence))
				return false;

			StandardCodeSequence objCode = (StandardCodeSequence)obj;
			return _codeValue == objCode._codeValue && _codeMeaning == objCode._codeMeaning && _codingSchemeDesignator == objCode._codingSchemeDesignator &&
				   _codingSchemeVersion == objCode._codingSchemeVersion;
		}

		public override int GetHashCode()
		{
			return (this.CodeValue ?? "").GetHashCode() ^ (this.CodeMeaning ?? "").GetHashCode() ^ (this.CodingSchemeDesignator ?? "").GetHashCode() ^
				   (this.CodingSchemeVersion ?? "").GetHashCode();
		}
	}

	public class CodeList
	{
		// just define calculation types that we use
		public static StandardCodeSequence CalculationCodeForLength = new StandardCodeSequence("G-A22A", "Length", "SRT");
		public static StandardCodeSequence CalculationCodeForArea = new StandardCodeSequence("G-A166", "Area", "SRT");
		public static StandardCodeSequence CalculationCodeForMean = new StandardCodeSequence("R-00317", "Mean", "SRT");
		public static StandardCodeSequence CalculationCodeForStandardDeviation = new StandardCodeSequence("R-10047", "Standard Deviation", "SRT");
		//     public static StandardCodeSequence CalculationCodeForStandardDeviation = new StandardCodeSequence("113061", "Standard Deviation", "DCM");
		public static StandardCodeSequence CalculationCodeForAngle = new StandardCodeSequence("XXX", "Angle", "AIM_TCGA"); // TODO VK
	}
}
