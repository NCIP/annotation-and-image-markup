#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

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
