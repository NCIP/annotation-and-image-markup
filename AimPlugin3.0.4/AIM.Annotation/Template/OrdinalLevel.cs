#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Xml.Serialization;
using System.Collections.Generic;

namespace AIM.Annotation.Template
{
	public class OrdinalLevel
	{
		[XmlAttribute("integerValue")]
		public int IntegerValue { get; set; }

		[XmlAttribute("description")]
		public string Description { get; set; }
	}
}
