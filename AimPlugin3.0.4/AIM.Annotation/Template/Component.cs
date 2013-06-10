#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class Component
	{
		private int _minCardinality;
		private GeometricShape _geometricShape;

		public Component()
		{
			AllowedTerm = new List<AllowedTerm>();
		}

		[XmlAttribute("label")]
		public string Label { get; set; }

		[XmlAttribute("minCardinality")]
		public int MinCardinality
		{
			get { return Math.Max(0, _minCardinality); }
			set
			{
				System.Diagnostics.Debug.Assert(value >= 0, "Component MinCardinality value is less than zero. Will be set to zero automatically.");
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

		[XmlElement("QuestionType")]
		public ValidTerm QuestionType { get; set; }

		[XmlElement("AnatomicEntity", Namespace = TemplateContainer.Namespace)]
		public AnatomicEntity AnatomicEntity { get; set; }

		[XmlElement("ImagingObservation", Namespace = TemplateContainer.Namespace)]
		public ImagingObservation ImagingObservation { get; set; }

		[XmlElement("Inference", Namespace = TemplateContainer.Namespace)]
		public Inference Inference { get; set; }

		[XmlElement("AllowedTerm", Namespace = TemplateContainer.Namespace, Type = typeof(AllowedTerm))]
		public List<AllowedTerm> AllowedTerm { get; set; }

		[XmlElement("Calculation", Namespace = TemplateContainer.Namespace)]
		public Calculation Calculation { get; set; }

		[XmlElement("GeometricShape")]
		public GeometricShape GeometricShape
		{
			get { return _geometricShape; }
			set
			{
				_geometricShape = value;
				GeometricShapeSpecified = true;
			}
		}

		[XmlIgnore]
		public bool GeometricShapeSpecified { get; set; }
	}
}
