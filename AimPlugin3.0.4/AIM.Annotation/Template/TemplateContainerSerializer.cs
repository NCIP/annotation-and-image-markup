#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace AIM.Annotation.Template {
	public class TemplateContainerSerializer {
		private XmlSerializer s;
		private readonly Type type;

		public TemplateContainerSerializer() {
			type = typeof(TemplateContainer);
			s = new XmlSerializer(type);
			s.UnknownNode += OnUnknownNode;
			s.UnknownElement += OnUnknownElement;
			s.UnknownAttribute += OnUnknownAttribute;
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

		public TemplateContainer Deserialize(string xml) {
			TextReader reader = new StringReader(xml);
			return Deserialize(reader);
		}

		public TemplateContainer Deserialize(XmlDocument doc) {
			TextReader reader = new StringReader(doc.OuterXml);
			return Deserialize(reader);
		}

		public TemplateContainer Deserialize(TextReader reader) {
			var o = (TemplateContainer)s.Deserialize(reader);
			reader.Close();
			return o;
		}

		public XmlDocument Serialize(TemplateContainer templatecontainer) {
			var xml = StringSerialize(templatecontainer);
			var doc = new XmlDocument();
			doc.PreserveWhitespace = true;
			doc.LoadXml(xml);
			return doc;
		}

		private string StringSerialize(TemplateContainer templatecontainer)
		{
			var w = WriterSerialize(templatecontainer);
			var xml = w.ToString();
			w.Close();
			return xml.Trim();
		}

		private TextWriter WriterSerialize(TemplateContainer templatecontainer)
		{
			TextWriter w = new StringWriter();
			s = new XmlSerializer(type);
			s.Serialize(w, templatecontainer);
			w.Flush();
			return w;
		}

		/// <summary>Reads template container from stream.</summary>
		/// <param name="stream">template stream.</param>
		/// <returns></returns>
		public static TemplateContainer ReadStream(Stream stream) {
			var serializer = new TemplateContainerSerializer();
			try {
				string xml;
				using (var reader = new StreamReader(stream)) {
					xml = reader.ReadToEnd();
					reader.Close();
				}
				return serializer.Deserialize(xml);
			} catch {}
			return new TemplateContainer();
		}

		public static TemplateContainer ReadFile(string file) {
			var serializer = new TemplateContainerSerializer();
			try {
				string xml;
				using (var reader = new StreamReader(file)) {
					xml = reader.ReadToEnd();
					reader.Close();
				}
				return serializer.Deserialize(xml);
			} catch {}
			return new TemplateContainer();
		}

		public static bool WriteFile(string file, TemplateContainer config) {
			var ok = false;
			var serializer = new TemplateContainerSerializer();
			try {
				var xml = serializer.Serialize(config).OuterXml;
				using (var writer = new StreamWriter(file, false)) {
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
