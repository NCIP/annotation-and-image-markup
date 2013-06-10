#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

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
