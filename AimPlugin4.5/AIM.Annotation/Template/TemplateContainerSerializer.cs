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
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace AIM.Annotation.Template {
	/// <summary>TemplateContainer Xml serialization utility.</summary>
	public class TemplateContainerSerializer {
		private XmlSerializer s = null;
		private Type type = null;

		/// <summary>Default constructor.</summary>
		public TemplateContainerSerializer() {
			this.type = typeof(TemplateContainer);
			this.s = new XmlSerializer(this.type);
			this.s.UnknownNode += OnUnknownNode;
			this.s.UnknownElement += OnUnknownElement;
			this.s.UnknownAttribute += OnUnknownAttribute;
		}

		private void OnUnknownAttribute(object sender, XmlAttributeEventArgs e)
		{
			Console.Out.WriteLine("Template Serializer. Unknown node is encountered in the tempalte: " + (e.Attr.ParentNode == null ? "" : e.Attr.ParentNode + ":") + e.Attr.Name);
		}

		private void OnUnknownElement(object sender, XmlElementEventArgs e)
		{
			Console.Out.WriteLine("Template Serializer. Unknown node is encountered in the tempalte: " + e.Element.Name);
		}

		private void OnUnknownNode(object sender, XmlNodeEventArgs e)
		{
			Console.Out.WriteLine("Template Serializer. Unknown node is encountered in the tempalte: " + e.Text);
		}


		/// <summary>Deserializes to an instance of TemplateContainer.</summary>
		/// <param name="xml">String xml.</param>
		/// <returns>TemplateContainer result.</returns>
		public TemplateContainer Deserialize(string xml) {
			TextReader reader = new StringReader(xml);
			return Deserialize(reader);
		}

		/// <summary>Deserializes to an instance of TemplateContainer.</summary>
		/// <param name="doc">XmlDocument instance.</param>
		/// <returns>TemplateContainer result.</returns>
		public TemplateContainer Deserialize(XmlDocument doc) {
			TextReader reader = new StringReader(doc.OuterXml);
			return Deserialize(reader);
		}

		/// <summary>Deserializes to an instance of TemplateContainer.</summary>
		/// <param name="reader">TextReader instance.</param>
		/// <returns>TemplateContainer result.</returns>
		public TemplateContainer Deserialize(TextReader reader) {
			TemplateContainer o = (TemplateContainer)s.Deserialize(reader);
			reader.Close();
			return o;
		}

		/// <summary>Serializes to an XmlDocument.</summary>
		/// <param name="templatecontainer">TemplateContainer to serialize.</param>
		/// <returns>XmlDocument instance.</returns>
		public XmlDocument Serialize(TemplateContainer templatecontainer) {
			string xml = StringSerialize(templatecontainer);
			XmlDocument doc = new XmlDocument();
			doc.PreserveWhitespace = true;
			doc.LoadXml(xml);
			//doc = Clean(doc); // Removes encoding XML Schema NS from the read document
			return doc;
		}

		private string StringSerialize(TemplateContainer templatecontainer)
		{
			TextWriter w = WriterSerialize(templatecontainer);
			string xml = w.ToString();
			w.Close();
			return xml.Trim();
		}

		private TextWriter WriterSerialize(TemplateContainer templatecontainer)
		{
			TextWriter w = new StringWriter();
			this.s = new XmlSerializer(this.type);
			s.Serialize(w, templatecontainer);
			w.Flush();
			return w;
		}

		private XmlDocument Clean(XmlDocument doc) {
			doc.RemoveChild(doc.FirstChild);
			XmlNode first = doc.FirstChild;
			foreach (XmlNode n in doc.ChildNodes) {
				if (n.NodeType == XmlNodeType.Element) {
					first = n;
					break;
				}
			}
			if (first.Attributes != null) {
				XmlAttribute a = null;
				a = first.Attributes["xmlns:xsd"];
				if (a != null) { first.Attributes.Remove(a); }
				a = first.Attributes["xmlns:xsi"];
				if (a != null) { first.Attributes.Remove(a); }
			}
			return doc;
		}

		/// <summary>Reads template container from stream.</summary>
		/// <param name="stream">template stream.</param>
		/// <returns></returns>
		public static TemplateContainer ReadStream(Stream stream) {
			TemplateContainerSerializer serializer = new TemplateContainerSerializer();
			try {
				string xml = string.Empty;
				using (StreamReader reader = new StreamReader(stream)) {
					xml = reader.ReadToEnd();
					reader.Close();
				}
				return serializer.Deserialize(xml);
			} catch {}
			return new TemplateContainer();
		}

		/// <summary>Reads config data from config file.</summary>
		/// <param name="file">Config file name.</param>
		/// <returns></returns>
		public static TemplateContainer ReadFile(string file) {
			TemplateContainerSerializer serializer = new TemplateContainerSerializer();
			try {
				string xml = string.Empty;
				using (StreamReader reader = new StreamReader(file)) {
					xml = reader.ReadToEnd();
					reader.Close();
				}
				return serializer.Deserialize(xml);
			} catch {}
			return new TemplateContainer();
		}

		/// <summary>Writes config data to config file.</summary>
		/// <param name="file">Config file name.</param>
		/// <param name="config">Config object.</param>
		/// <returns></returns>
		public static bool WriteFile(string file, TemplateContainer config) {
			bool ok = false;
			TemplateContainerSerializer serializer = new TemplateContainerSerializer();
			try {
				string xml = serializer.Serialize(config).OuterXml;
				using (StreamWriter writer = new StreamWriter(file, false)) {
					writer.Write(xml.Trim());
					writer.Flush();
					writer.Close();
				}
				ok = true;
			} catch {}
			return ok;
		}
	}
}
