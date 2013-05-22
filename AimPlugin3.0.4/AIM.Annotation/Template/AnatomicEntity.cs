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
	public class AnatomicEntity
	{
		private bool _annotatorConfidence;
		private List<AnatomicEntityCharacteristic> _anatomicEntityCharacteristic = new List<AnatomicEntityCharacteristic>();

		[XmlAttribute("annotatorConfidence")]
		public bool AnnotatorConfidence
		{
			get { return _annotatorConfidence; }
			set { _annotatorConfidence = value; }
		}

		[XmlElement("AnatomicEntityCharacteristic", Namespace = TemplateContainer.Namespace)]
		public List<AnatomicEntityCharacteristic> AnatomicEntityCharacteristic
		{
			get { return _anatomicEntityCharacteristic; }
			set { _anatomicEntityCharacteristic = value; }
		}
	}
}
