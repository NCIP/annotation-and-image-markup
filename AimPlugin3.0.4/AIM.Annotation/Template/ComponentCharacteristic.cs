//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class ComponentCharacteristic
	{
		private int _minCardinality;

		public ComponentCharacteristic()
		{
			AllowedTerm = new List<AllowedTerm1>();
		}

		[XmlAttribute("label")]
		public string Label { get; set; }

		[XmlAttribute("minCardinality")]
		public int MinCardinality
		{
			get { return Math.Max(0, _minCardinality); }
			set
			{
				System.Diagnostics.Debug.Assert(value >= 0, "Component Characteristic MinCardinality value is less than zero. Will be set to zero automatically.");
				_minCardinality = value;
			}
		}

		[XmlAttribute("maxCardinality")]
		public int MaxCardinality { get; set; }

		[XmlAttribute("itemNumber")]
		public int ItemNumber { get; set; }

		[XmlAttribute("shouldDisplay")]
		public bool ShouldDisplay { get; set; }

		[XmlAttribute("explanatoryText")]
		public string ExplanatoryText { get; set; }

		[XmlAttribute("authors")]
		public string Authors { get; set; }

		[XmlAttribute("groupLabel")]
		public string GroupLabel { get; set; }

		[XmlElement("AllowedTerm", Namespace = TemplateContainer.Namespace, Type = typeof(AllowedTerm1))]
		public List<AllowedTerm1> AllowedTerm { get; set; }
	}
}
