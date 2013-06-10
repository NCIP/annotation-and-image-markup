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
	public class TagValue
	{
		[XmlElement("CodedValue", Namespace = TemplateContainer.Namespace)]
		public CodedTerm CodedValue { get; set; }

		[XmlElement("StringValue", Namespace = TemplateContainer.Namespace)]
		public string StringValue { get; set; }
	}
}
