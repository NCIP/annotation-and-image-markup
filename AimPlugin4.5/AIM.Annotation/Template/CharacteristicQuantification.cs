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

using System.Xml.Serialization;
using System.Collections.Generic;

namespace AIM.Annotation.Template
{
	public enum CharacteristicQuantificationType
	{
		Numerical,
		Quantile,
		NonQuantifiable,
		Scale,
		Interval
	}

	public class CharacteristicQuantification
	{
		public CharacteristicQuantification()
		{
			NonQuantifiable = new List<NonQuantifiable>();
			Interval = new List<Interval>();
			Numerical = new List<Numerical>();
		}

		[XmlAttribute("name")]
		public string Name { get; set; }

		[XmlAttribute("annotatorConfidence")]
		public bool AnnotatorConfidence { get; set; }

		[XmlElement("Scale", Namespace = TemplateContainer.Namespace)]
		public Scale Scale { get; set; }

		[XmlElement("Numerical", Namespace = TemplateContainer.Namespace)]
		public List<Numerical> Numerical { get; set; }

		[XmlElement("Interval", Namespace = TemplateContainer.Namespace)]
		public List<Interval> Interval { get; set; }

		[XmlElement("Quantile", Namespace = TemplateContainer.Namespace)]
		public Quantile Quantile { get; set; }

		[XmlElement("NonQuantifiable", Namespace = TemplateContainer.Namespace)]
		public List<NonQuantifiable> NonQuantifiable { get; set; }
	}
}
