#region License

// Copyright (c) 2007 - 2014, Northwestern University, Vladimir Kleper, Skip Talbot
// and Pattanasak Mongkolwat.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//   Neither the name of the National Cancer Institute nor Northwestern University
//   nor the names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

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

		// TODO FIXME: this still creates empty <Tags /> element when collection is empty
		[XmlArray("Tags", IsNullable = false, Namespace = TemplateContainer.Namespace)]
		[XmlArrayItem(IsNullable = false, ElementName = "Tag")]
		//[XmlElement("Tags", Namespace = TemplateContainer.Namespace)]
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
			get { return this._creationDate; }
			set {
				_creationDate = value;
				CreationDateSpecified = true;
			}
		}

		[XmlIgnore]
		public bool CreationDateSpecified { get; set; }
	}
}
