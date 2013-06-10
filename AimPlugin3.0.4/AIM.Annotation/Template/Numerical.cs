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
	public class Numerical
	{
		private ComparisonOperator _operator;

		public Numerical()
		{
			OperatorSpecified = false;
		}

		[XmlAttribute("value")]
		public double Value { get; set; }

		[XmlAttribute("ucumString")]
		public string UcumString { get; set; }

		[XmlAttribute("operator", Namespace = TemplateContainer.Namespace)]
		public ComparisonOperator Operator
		{
			get { return _operator; }
			set
			{
				_operator = value;
				OperatorSpecified = true;
			}
		}

		[XmlIgnore]
		public bool OperatorSpecified { get; set; }
	}
}
