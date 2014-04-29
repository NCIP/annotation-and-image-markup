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
using System.Runtime.Serialization;
using System.Text;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.TemplateTree
{
	[DataContract(Name = "StandardValidTerm")]
	public class StandardValidTerm
	{
		[DataMember]
		public StandardCodeSequence StandardCodeSequence { get; private set; }

		[DataMember]
		public List<StandardValidTerm> StandardValidTerms { get; private set; }

		public StandardValidTerm(StandardCodeSequence standardCodeSequence, List<StandardValidTerm> standardValidTerms)
		{
			StandardCodeSequence = standardCodeSequence;
			StandardValidTerms = standardValidTerms;
		}

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is StandardValidTerm))
				return false;

			StandardValidTerm validTerm = (StandardValidTerm)obj;
			return (StandardCodeSequence == null
						? validTerm.StandardCodeSequence == null
						: StandardCodeSequence.Equals(validTerm.StandardCodeSequence)) &&
				   (StandardValidTerms == null
						? validTerm.StandardValidTerms == null
						: CollectionUtils.Equal<StandardValidTerm>(StandardValidTerms, validTerm.StandardValidTerms, true));

		}

		public override int GetHashCode()
		{
			int hashCode = StandardCodeSequence == null ? "".GetHashCode() : StandardCodeSequence.GetHashCode();
			if (StandardValidTerms != null)
				CollectionUtils.ForEach(StandardValidTerms, term => { if (term != null) hashCode ^= term.GetHashCode(); });
			return hashCode;
		}

		public override string ToString()
		{
			var sb = new StringBuilder();
			sb.Append(StandardCodeSequence.CodeMeaning);
			foreach (var term in StandardValidTerms)
			{
				sb.Append(" ");
				sb.Append(term.ToString());
			}
			return sb.ToString();
		}
	}

	[DataContract(Name = "CodeSequence")]
	public class StandardCodeSequence
	{
		public StandardCodeSequence(string codeValue, string codeMeaning, string codingSchemeDesignator) :
			this(codeValue, codeMeaning, codingSchemeDesignator, null)
		{
		}

		public StandardCodeSequence(string codeValue, string codeMeaning,
			string codingSchemeDesignator, string codingSchemeVersion)
		{
			CodeValue = codeValue;
			CodeMeaning = codeMeaning;
			CodingSchemeDesignator = codingSchemeDesignator;
			CodingSchemeVersion = codingSchemeVersion;
		}

		[DataMember]
		public string CodeValue { get; private set; }

		[DataMember]
		public string CodeMeaning { get; private set; }

		[DataMember]
		public string CodingSchemeDesignator { get; private set; }

		[DataMember]
		public string CodingSchemeVersion { get; private set; }

		public override string ToString()
		{
			return string.Format("{0}({1})", this.CodeMeaning, this.CodeValue);
		}

		public override bool Equals(object obj)
		{
			if (obj == null || !(obj is StandardCodeSequence))
				return false;

			StandardCodeSequence objCode = (StandardCodeSequence)obj;
			return CodeValue == objCode.CodeValue && CodeMeaning == objCode.CodeMeaning && CodingSchemeDesignator == objCode.CodingSchemeDesignator &&
				   CodingSchemeVersion == objCode.CodingSchemeVersion;
		}

		public override int GetHashCode()
		{
			return (CodeValue ?? "").GetHashCode() ^ (CodeMeaning ?? "").GetHashCode() ^ (CodingSchemeDesignator ?? "").GetHashCode() ^
				   (CodingSchemeVersion ?? "").GetHashCode();
		}
	}

	[DataContract(Name = "CodedTerm")]
	public class StandardCodedTerm : StandardCodeSequence, IStandardCodedTerm
	{
		[DataMember]
		public bool DefaultAnswer { get; private set; }

		[DataMember]
		public string NextId { get; private set; }

		[DataMember]
		public bool NoMoreQuestions { get; private set; }

		public StandardCodedTerm(bool defaultAnswer, string nextId, bool noMoreQuestions, string codeValue, string codeMeaning, string codingSchemeDesignator, string codingSchemeVersion)
			: base(codeValue, codeMeaning, codingSchemeDesignator, codingSchemeVersion)
		{
			DefaultAnswer = defaultAnswer;
			NextId = nextId;
			NoMoreQuestions = noMoreQuestions;
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
