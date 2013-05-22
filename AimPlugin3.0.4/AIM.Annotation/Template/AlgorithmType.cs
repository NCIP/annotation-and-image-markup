//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class AlgorithmType : CodedTerm	
	{
		[XmlAttribute("uniqueIdentifier")]
		public string UniqueIdentifier { get; set; }

		[XmlAttribute("description")]
		public string Description { get; set; }

		[XmlAttribute("mathML")]
		public string MathMl { get; set; }

		[XmlAttribute("algorithmName")]
		public string AlgorithmName { get; set; }

		[XmlAttribute("algorithmVersion")]
		public string AlgorithmVersion { get; set; }
	}
}
