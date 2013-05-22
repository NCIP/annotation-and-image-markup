//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class ComponentCharacteristicCollection
	{
		private int _componentCharacteristicItemNumber;
		private int _itemNumber;

		public ComponentCharacteristicCollection()
		{
			ComponentCharacteristicItemNumberSpecified = false;
			ItemNumberSpecified = false;
		}

		[XmlAttribute("lable")]
		public string Lable { get; set; }

		[XmlAttribute("componentCharacteristicItemNumber")]
		public int ComponentCharacteristicItemNumber
		{
			get { return _componentCharacteristicItemNumber; }
			set {
				_componentCharacteristicItemNumber = value;
				ComponentCharacteristicItemNumberSpecified = true;
			}
		}

		[XmlIgnore]
		public bool ComponentCharacteristicItemNumberSpecified { get; private set; }

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
