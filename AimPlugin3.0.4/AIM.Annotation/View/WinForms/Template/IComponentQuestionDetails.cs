#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;
using System.Linq;

using AIM.Annotation.Template;

namespace AIM.Annotation.View.WinForms.Template
{
	public enum ComponentQuestionType
	{
		AnatomicEntity,
		ImagingObservation,
		Inference,
		Calculation,
		GeometricShape
	}

	internal interface IComponentQuestionDetails
	{
		ComponentQuestionType QuestionType { get; }
		int QuestionNumber { get; }
	}

	internal class ComponentUtilities
	{
		public static List<StandardCodeSequence> AllowedTermsToCodeSequenceList(List<AllowedTerm> allowedTerms)
		{
			var standardValidTerms = AllowedTermsToValidTermList(allowedTerms);
			var codeSequences = standardValidTerms.Select(standardValidTerm => CodeUtils.ToStandardCodeSequence(standardValidTerm)).ToList();

			allowedTerms.ForEach(
				delegate(AllowedTerm term)
				{
					if (term.NonQuantifiable != null)
						term.NonQuantifiable.ForEach(nonQuantifiable => new StandardCodeSequence(nonQuantifiable.CodeValue, nonQuantifiable.CodeMeaning, nonQuantifiable.CodingSchemeDesignator, nonQuantifiable.CodingSchemeVersion));
				});

			return codeSequences;
		}

		public static List<StandardCodeSequence> AllowedTerms1ToCodeSequenceList(List<AllowedTerm1> allowedTerms1)
		{
			var standardValidTerms = AllowedTerms1ToValidTermList(allowedTerms1);
			return standardValidTerms.Select(standardValidTerm => CodeUtils.ToStandardCodeSequence(standardValidTerm)).ToList();
		}

		public static List<StandardValidTerm> AllowedTerms1ToValidTermList(List<AllowedTerm1> allowedTerms1)
		{
			var validTerms = new List<StandardValidTerm>();
			allowedTerms1.ForEach(
				delegate(AllowedTerm1 term)
				{
					var standardValidTerm = new StandardValidTerm(
						new StandardCodeSequence(term.CodeValue, term.CodeMeaning, term.CodingSchemeDesignator, term.CodingSchemeVersion)
						);
					foreach (var validTerm in term.ValidTerms)
						standardValidTerm.StandardValidTerms.Add(ValidTermToStandardValidTerm(validTerm));
					validTerms.Add(standardValidTerm);
				});
			return validTerms;
		}

		public static List<StandardValidTerm> AllowedTermsToValidTermList(List<AllowedTerm> allowedTerms1)
		{
			var validTerms = new List<StandardValidTerm>();
			allowedTerms1.ForEach(
				delegate(AllowedTerm term)
				{
					if (term.NonQuantifiable != null)
						term.NonQuantifiable.ForEach(
							delegate(NonQuantifiable nonQuantifiable)
								{
									var quantifiableValidTerm = new StandardValidTerm(
										new StandardCodeSequence(
											nonQuantifiable.CodeValue, 
											nonQuantifiable.CodeMeaning,
											nonQuantifiable.CodingSchemeDesignator,
											nonQuantifiable.CodingSchemeVersion));
									validTerms.Add(quantifiableValidTerm);
								});

					var standardValidTerm = new StandardValidTerm(
						new StandardCodeSequence(term.CodeValue, term.CodeMeaning, term.CodingSchemeDesignator, term.CodingSchemeVersion)
						);
					foreach (var validTerm in term.ValidTerms)
						standardValidTerm.StandardValidTerms.Add(ValidTermToStandardValidTerm(validTerm));
					validTerms.Add(standardValidTerm);
				});
			return validTerms;
		}

		public static StandardValidTerm ValidTermToStandardValidTerm(ValidTerm validTerm)
		{
			if (validTerm == null)
				return null;

			var standardValidTerm =
				new StandardValidTerm(
					new StandardCodeSequence(
						validTerm.CodeValue,
						validTerm.CodeMeaning,
						validTerm.CodingSchemeDesignator,
						validTerm.CodingSchemeVersion));

			foreach (var childValidTerm in validTerm.ValidTerms)
				standardValidTerm.StandardValidTerms.Add(ValidTermToStandardValidTerm(childValidTerm));

			return standardValidTerm;
		}

		public static List<StandardValidTerm> ToStandardValidTermList(List<StandardCodeSequence> standardCodeSequences)
		{
			if (standardCodeSequences == null)
				return null;

			var validTerms = new List<StandardValidTerm>(standardCodeSequences.Count);
			foreach (var standardCodeSequence in standardCodeSequences)
			{
				validTerms.Add(new StandardValidTerm(standardCodeSequence));
			}

			return validTerms;
		}
	}
}
