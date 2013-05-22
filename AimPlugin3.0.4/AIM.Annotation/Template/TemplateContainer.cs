//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Xml.Serialization;
using System.Collections.Generic;

namespace AIM.Annotation.Template
{
	[XmlRoot("TemplateContainer", Namespace = TemplateContainer.Namespace)]
	[Serializable]
	public class TemplateContainer
	{
		public const string Namespace = "gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate";

		private List<Tag> _tags;
		private string _authors;
		private DateTime _creationDate;

		public TemplateContainer()
		{
			Template = new List<Template>();
		}

		[XmlElement("Template", Namespace = TemplateContainer.Namespace)]
		public List<Template> Template { get; set; }

		[XmlArray("Tags", IsNullable = false, Namespace = TemplateContainer.Namespace)]
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

		[XmlAttribute("name", Namespace="")]
		public string Name { get; set; }

		[XmlAttribute("version", Namespace="")]
		public string Version { get; set; }

		[XmlAttribute("description", Namespace="")]
		public string Description { get; set; }

		[XmlAttribute("uid", Namespace = "")]
		public string Uid { get; set; }

		[XmlAttribute("authors", Namespace = "")]
		public string Authors
		{
			get { return _authors; }
			set
			{
				_authors = value;
				AuthorsSpecified = true;
			}
		}

		[XmlIgnore]
		public bool AuthorsSpecified { get; set; }

		[XmlAttribute("creationDate", Namespace = "", DataType = "date")]
		public DateTime CreationDate
		{
			get { return _creationDate; }
			set {
				_creationDate = value;
				CreationDateSpecified = true;
			}
		}

		[XmlIgnore]
		public bool CreationDateSpecified { get; set; }
	}
}
