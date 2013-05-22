//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace AIM.Annotation.View.WinForms
{
	internal class CodeSequenceListItem
	{
		private readonly StandardCodeSequence _value;

		public CodeSequenceListItem(StandardCodeSequence newValue)
		{
			_value = newValue;
		}

		public StandardCodeSequence Value
		{
			get { return _value; }
		}

		public override string ToString()
		{
			return _value == null ? "------" : _value.CodeMeaning;
		}
	}
}
