//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;
using System.Collections.Generic;

namespace AIM.Annotation.Template
{
	public enum CharacteristicQuantificationType
	{
		Numerical,
		Quantile,
		NonQuantifiable,
		Scale,
		Interval
	}

	public class CharacteristicQuantification
	{
		public CharacteristicQuantification()
		{
			NonQuantifiable = new List<NonQuantifiable>();
			Interval = new List<Interval>();
			Numerical = new List<Numerical>();
		}

		[XmlAttribute("name")]
		public string Name { get; set; }

		[XmlAttribute("annotatorConfidence")]
		public bool AnnotatorConfidence { get; set; }

		[XmlElement("Scale", Namespace = TemplateContainer.Namespace)]
		public Scale Scale { get; set; }

		[XmlElement("Numerical", Namespace = TemplateContainer.Namespace)]
		public List<Numerical> Numerical { get; set; }

		[XmlElement("Interval", Namespace = TemplateContainer.Namespace)]
		public List<Interval> Interval { get; set; }

		[XmlElement("Quantile", Namespace = TemplateContainer.Namespace)]
		public Quantile Quantile { get; set; }

		[XmlElement("NonQuantifiable", Namespace = TemplateContainer.Namespace)]
		public List<NonQuantifiable> NonQuantifiable { get; set; }
	}
}
