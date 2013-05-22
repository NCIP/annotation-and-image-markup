//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class ComponentCollection
	{
		private int _componentItemNumber;
		private int _itemNumber;

		public ComponentCollection()
		{
			ItemNumberSpecified = false;
			ComponentItemNumberSpecified = false;
		}

		[XmlAttribute("lable")]
		public string Label { get; set; }

		[XmlAttribute("componentItemNumber")]
		public int ComponentItemNumber
		{
			get { return _componentItemNumber; }
			set {
				_componentItemNumber = value;
				ComponentItemNumberSpecified = true;
			}
		}

		[XmlIgnore]
		public bool ComponentItemNumberSpecified { get; private set; }

		[XmlAttribute("itemNumber")]
		public int ItemNumber
		{
			get { return _itemNumber; }
			set {
				_itemNumber = value;
				ItemNumberSpecified = true;
			}
		}

		[XmlIgnore]
		public bool ItemNumberSpecified { get; private set; }
	}
}
