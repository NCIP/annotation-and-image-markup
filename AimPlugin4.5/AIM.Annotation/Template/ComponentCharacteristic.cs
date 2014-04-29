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
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	public class ComponentCharacteristic
	{
		private int _minCardinality;

		public ComponentCharacteristic()
		{
			AllowedTerm = new List<AllowedTerm1>();
		}

		[XmlAttribute("label")]
		public string Label { get; set; }

		[XmlAttribute("minCardinality")]
		public int MinCardinality
		{
			get { return Math.Max(0, this._minCardinality); }
			set
			{
				System.Diagnostics.Debug.Assert(value >= 0, "Component Characteristic MinCardinality value is less than zero. Will be set to zero automatically.");
				this._minCardinality = value;
			}
		}

		[XmlAttribute("maxCardinality")]
		public int MaxCardinality { get; set; }

		[XmlAttribute("itemNumber")]
		public int ItemNumber { get; set; }

		[XmlAttribute("shouldDisplay")]
		public bool ShouldDisplay { get; set; }

		[XmlAttribute("explanatoryText")]
		public string ExplanatoryText { get; set; }

		[XmlAttribute("authors")]
		public string Authors { get; set; }

		[XmlAttribute("groupLabel")]
		public string GroupLabel { get; set; }

		[XmlElement("AllowedTerm", Namespace = TemplateContainer.Namespace, Type = typeof(AllowedTerm1))]
		public List<AllowedTerm1> AllowedTerm { get; set; }
	}
}
