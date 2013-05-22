//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class Interval
	{
		[XmlAttribute("minValue")]
		public double MinValue { get; set; }

		[XmlAttribute("maxValue")]
		public double MaxValue { get; set; }

		[XmlAttribute("minOperator", Namespace = TemplateContainer.Namespace)]
		public ComparisonOperator MinOperator { get; set; }

		[XmlAttribute("maxOperator", Namespace = TemplateContainer.Namespace)]
		public ComparisonOperator MaxOperator { get; set; }

		[XmlAttribute("ucumString")]
		public string UcumString { get; set; }
	}
}
