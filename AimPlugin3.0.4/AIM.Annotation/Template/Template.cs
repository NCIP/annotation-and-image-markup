#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Xml.Serialization;
using System.Collections.Generic;

namespace AIM.Annotation.Template
{
	public class Template
	{
		private List<Tag> _tags;
		private ModalityType _modality;
		private DateTime _creationDate;
		private PrecedingAnnotationRequest _precedingAnnotation;

		public Template()
		{
			Components = new List<Component>();
		}

		[XmlElement("Component")]
		public List<Component> Components { get; set; }

		[XmlArray("Tags", IsNullable = false)]
		[XmlArrayItem(IsNullable = false, ElementName = "Tag")]
		public List<Tag> Tags
		{
			get { return _tags; }
			set
			{
				_tags = value;
				TagsSpecified = true;
			}
		}

		[XmlIgnore]
		public bool TagsSpecified { get; set; }

		[XmlAttribute("name")]
		public string Name { get; set; }

		[XmlAttribute("version")]
		public string Version { get; set; }

		[XmlAttribute("description")]
		public string Description { get; set; }

		[XmlAttribute("uid")]
		public string Uid { get; set; }

		[XmlAttribute("codeValue")]
		public string CodeValue { get; set; }

		[XmlAttribute("codeMeaning")]
		public string CodeMeaning { get; set; }

		[XmlAttribute("codingSchemeDesignator")]
		public string CodingSchemeDesignator { get; set; }

		[XmlAttribute("codingSchemeVersion")]
		public string CodingSchemeVersion { get; set; }

		[XmlAttribute("modality")]
		public ModalityType Modality
		{
			get { return _modality; }
			set
			{
				_modality = value;
				ModalitySpecified = true;
			}
		}

		[XmlIgnore]
		public bool ModalitySpecified { get; set; }

		[XmlAttribute("authors")]
		public string Authors { get; set; }

		[XmlAttribute("creationDate", DataType = "date")]
		public DateTime CreationDate
		{
			get { return _creationDate; }
			set 
			{
				_creationDate = value;
				CreationDateSpecified = true;
			}
		}

		[XmlIgnore]
		public bool CreationDateSpecified { get; set; }

		[XmlAttribute("precedingAnnotation")]
		public PrecedingAnnotationRequest PrecedingAnnotation
		{
			get { return _precedingAnnotation; }
			set
			{
				_precedingAnnotation = value;
				PrecedingAnnotationSpecified = true;
			}
		}

		[XmlIgnore]
		public bool PrecedingAnnotationSpecified { get; set; }
	}
}
