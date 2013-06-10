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
	public class AllowedTerm : ValidTerm
	{
		public AllowedTerm()
		{
			NonQuantifiable = new List<NonQuantifiable>();
		}

		[XmlElement("NonQuantifiable", Namespace = TemplateContainer.Namespace)]
		public List<NonQuantifiable> NonQuantifiable { get; set; }
	}
}
