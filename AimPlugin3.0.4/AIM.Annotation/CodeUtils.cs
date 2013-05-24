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

using System.Text;
using AnatomicEntity = aim_dotnet.AnatomicEntity;
using AnatomicEntityCharacteristic = aim_dotnet.AnatomicEntityCharacteristic;
using ImagingObservation = aim_dotnet.ImagingObservation;
using ImagingObservationCharacteristic = aim_dotnet.ImagingObservationCharacteristic;
using Inference = aim_dotnet.Inference;
using Calculation = aim_dotnet.Calculation;

namespace AIM.Annotation
{
	public class CodeUtils
	{
		private const string COLLAPSED_VALID_TERM_CODING_SCHEME_DESIGNATOR = "AIM3-COMPAT";

		public static AnatomicEntity ToAnatomicEntity(StandardCodeSequence codeSequence, string label)
		{
			return codeSequence == null
					? null
					: new AnatomicEntity
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion,
							Label = label
						};
		}



		public static AnatomicEntityCharacteristic ToAnatomicEntityCharacteristic(StandardCodeSequence codeSequence, string label)
		{
			return codeSequence == null
					? null
					: new AnatomicEntityCharacteristic
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion,
							Label = label
						};
		}

		public static ImagingObservation ToImagingObservation(StandardCodeSequence codeSequence, string label)
		{
			return codeSequence == null
					? null
					: new ImagingObservation
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion,
							Label = label
						};
		}

		public static ImagingObservationCharacteristic ToImagingObservationCharacteristic(StandardCodeSequence codeSequence, string label)
		{
			return codeSequence == null
					? null
					: new ImagingObservationCharacteristic
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion,
							Label = label
						};
		}

		public static Inference ToInference(StandardCodeSequence codeSequence)
		{
			return codeSequence == null
					? null
					: new Inference
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion
						};
		}

		public static Calculation ToCalculation(StandardCodeSequence codeSequence)
		{
			return codeSequence == null
					? null
					: new Calculation
						{
							CodeValue = codeSequence.CodeValue,
							CodeMeaning = codeSequence.CodeMeaning,
							CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
							CodingSchemeVersion = codeSequence.CodingSchemeVersion
						};
		}

		public static StandardCodeSequence ToStandardCodeSequence(AnatomicEntity anatomicEntity)
		{
			return anatomicEntity == null
					? null
					:
						new StandardCodeSequence(anatomicEntity.CodeValue, anatomicEntity.CodeMeaning, anatomicEntity.CodingSchemeDesignator,
												 anatomicEntity.CodingSchemeVersion);
		}

		public static StandardCodeSequence ToStandardCodeSequence(AnatomicEntityCharacteristic anatomicEntityCharacteristic)
		{
			return anatomicEntityCharacteristic == null
					? null
					:
						new StandardCodeSequence(anatomicEntityCharacteristic.CodeValue, anatomicEntityCharacteristic.CodeMeaning,
												 anatomicEntityCharacteristic.CodingSchemeDesignator,
												 anatomicEntityCharacteristic.CodingSchemeVersion);
		}

		public static StandardCodeSequence ToStandardCodeSequence(ImagingObservation imagingObservation)
		{
			return imagingObservation == null
					? null
					:
						new StandardCodeSequence(imagingObservation.CodeValue, imagingObservation.CodeMeaning, imagingObservation.CodingSchemeDesignator,
												 imagingObservation.CodingSchemeVersion);
		}

		public static StandardCodeSequence ToStandardCodeSequence(ImagingObservationCharacteristic imagingObservationCharacteristic)
		{
			return imagingObservationCharacteristic == null
					? null
					:
						new StandardCodeSequence(imagingObservationCharacteristic.CodeValue, imagingObservationCharacteristic.CodeMeaning, imagingObservationCharacteristic.CodingSchemeDesignator,
												 imagingObservationCharacteristic.CodingSchemeVersion);
		}

		public static StandardCodeSequence ToStandardCodeSequence(Inference inference)
		{
			return inference == null
					? null
					:
						new StandardCodeSequence(inference.CodeValue, inference.CodeMeaning, inference.CodingSchemeDesignator,
												 inference.CodingSchemeVersion);
		}

		private static readonly char[] HEX_DIGIT = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		/// <summary>
		/// Create 8 char alphanumeric string from a given string
		/// of alphanumerical <paramref name="val"/> string
		/// </summary>
		public static string ToHex(string val)
		{
			var valToInt = val.GetHashCode();
			var ch8 = new char[8];
			for (var i = 8; --i >= 0; valToInt >>= 4)
			{
				ch8[i] = HEX_DIGIT[valToInt & 0xf];
			}
			return new string(ch8);
		}

		/// <summary>
		/// Recursively flattens a hierarchy of valid terms into a single StandardCodeSequence
		/// by concatenating the codeValue and codeMeaning fields.
		/// </summary>
		/// <param name="standardValidTerm"></param>
		/// <returns></returns>
		private static StandardCodeSequence CollapseStandardValidTerm(StandardValidTerm standardValidTerm)
		{
			var codeValue = standardValidTerm.StandardCodeSequence.CodeValue;
			var codingSchemeDesignator = standardValidTerm.StandardCodeSequence.CodingSchemeDesignator;
			var codingSchemeVersion = standardValidTerm.StandardCodeSequence.CodingSchemeVersion;
			var codeMeaning = standardValidTerm.StandardCodeSequence.CodeMeaning;
			const string delimiter = ", ";

			if (standardValidTerm.StandardValidTerms.Count > 0)
				codingSchemeDesignator = COLLAPSED_VALID_TERM_CODING_SCHEME_DESIGNATOR;

			foreach (var childStandardValidTerm in standardValidTerm.StandardValidTerms)
			{
				var standardCodeSequence = CollapseStandardValidTerm(childStandardValidTerm);
				if (!string.IsNullOrEmpty(standardCodeSequence.CodeValue))
					codeValue += delimiter + standardCodeSequence.CodeValue;
				if (!string.IsNullOrEmpty(standardCodeSequence.CodeMeaning))
					codeMeaning += delimiter + standardCodeSequence.CodeMeaning;
			}

			return new StandardCodeSequence(codeValue, codeMeaning, codingSchemeDesignator, codingSchemeVersion);
		}

		/// <summary>
		/// Returns a StandardCodeSequence from a recursively collapsed or flatted StandardValidTerm.
		/// </summary>
		/// <param name="standardValidTerm"></param>
		/// <returns></returns>
		public static StandardCodeSequence ToStandardCodeSequence(StandardValidTerm standardValidTerm)
		{
			const int codeValueLength = 16;
			const int codeMeaningLength = 64;

			var standardCodeSequence = CollapseStandardValidTerm(standardValidTerm);
			var codeValue = standardCodeSequence.CodeValue;
			var codeMeaning = standardCodeSequence.CodeMeaning;
			var codingSchemeDesignator = standardCodeSequence.CodingSchemeDesignator;
			var codingSchemeVersion = standardCodeSequence.CodingSchemeVersion;

			if (standardValidTerm.StandardValidTerms.Count > 0)
			{
				codeValue = ToHex(codeValue);
				if (codeValue.Length > codeValueLength)
					codeValue = codeValue.Substring(0, codeValueLength);
				if (codeMeaning.Length > codeMeaningLength)
					codeMeaning = codeMeaning.Substring(0, codeMeaningLength);
			}

			return new StandardCodeSequence(
				codeValue,
				codeMeaning,
				codingSchemeDesignator,
				codingSchemeVersion);
		}

		/// <summary>
		/// Recursevely traverses given <paramref name="validTerm"/> and appends Code Meanings to the given <paramref name="sb"/>.
		/// This effectively flattens <paramref name="validTerm"/> to a string.
		/// </summary>
		/// <param name="validTerm">Standard Valid Term to traverse</param>
		/// <param name="sb">String Builder taht receives the values</param>
		public static StringBuilder ToStringBuilder(StandardValidTerm validTerm, StringBuilder sb)
		{
			if (validTerm == null || sb == null)
				return sb;

			if (sb.Length > 0)
				sb.Append(" ");
			sb.Append(validTerm.StandardCodeSequence.CodeMeaning);
			foreach (var standardValidTerm in validTerm.StandardValidTerms)
				ToStringBuilder(standardValidTerm, sb);

			return sb;
		}
	}
}
