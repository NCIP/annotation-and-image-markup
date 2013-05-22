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
	public class ChildComponents
	{
		public ChildComponents()
		{
			ComponentCharacteristic = new List<ComponentCharacteristic>();
			Component = new List<Component>();
		}

		[XmlElement("Component", Namespace = TemplateContainer.Namespace)]
		public List<Component> Component { get; set; }

		[XmlElement("ComponentCharacteristic", Namespace = TemplateContainer.Namespace)]
		public List<ComponentCharacteristic> ComponentCharacteristic { get; set; }
	}
}
