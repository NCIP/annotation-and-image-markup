//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class CodedTerm
	{
		private string _codingSchemeVersion;

		[XmlAttribute("codeValue")]
		public string CodeValue { get; set; }

		[XmlAttribute("codeMeaning")]
		public string CodeMeaning { get; set; }

		[XmlAttribute("codingSchemeDesignator")]
		public string CodingSchemeDesignator { get; set; }

		[XmlAttribute("codingSchemeVersion")]
		public string CodingSchemeVersion
		{
			get { return _codingSchemeVersion; }
			set
			{
				_codingSchemeVersion = value;
				CodingSchemeVersionSpecified = true;
			}
		}

		[XmlIgnore]
		public bool CodingSchemeVersionSpecified { get; set; }
	}
}
