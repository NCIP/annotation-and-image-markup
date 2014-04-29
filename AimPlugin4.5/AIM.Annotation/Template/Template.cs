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

		// TODO FIXME: this still creates empty <Tags /> element when collection is empty
		[XmlArray("Tags", IsNullable = false)]
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
