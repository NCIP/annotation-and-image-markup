//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Text;

namespace AIM.Annotation.View.WinForms
{
	internal class ValidTermListItem
	{
		private readonly StandardValidTerm _value;

		public ValidTermListItem(StandardValidTerm newValue)
		{
			_value = newValue;
		}

		public StandardValidTerm Value
		{
			get { return _value; }
		}

		public override string ToString()
		{
			//return _value == null ? "------" : _value.CodeMeaning;
			return ToDisplayString();
		}

		private string ToDisplayString()
		{
			if (_value == null)
				return "------";

			if (_value.StandardValidTerms == null || _value.StandardValidTerms.Count == 0)
				return _value.StandardCodeSequence.CodeMeaning;

			return CodeUtils.ToStringBuilder(_value, new StringBuilder()).ToString();
		}
	}
}
