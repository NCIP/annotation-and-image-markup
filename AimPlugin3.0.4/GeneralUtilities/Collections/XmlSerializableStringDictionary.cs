//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace GeneralUtilities.Collections
{
	///
	/// This class implements XML Serializable String Dictionary
	/// Use this class in Settings and whenever XML Serialization is required
	/// 
	[XmlRoot("dictionary")]
	public class XmlSerializableStringDictionary : Dictionary<String, String>, IXmlSerializable
	{
		#region IXmlSerializable Members

        public XmlSerializableStringDictionary()
        { }

        public XmlSerializableStringDictionary(IDictionary<String, String> dictionary) : base(dictionary) { }

		public System.Xml.Schema.XmlSchema GetSchema()
		{
			return null;
		}

		public void ReadXml(System.Xml.XmlReader reader)
		{
			var keySerializer = new XmlSerializer(typeof(string));
			var valueSerializer = new XmlSerializer(typeof(string));
			var wasEmpty = reader.IsEmptyElement;
			reader.Read();

			if (wasEmpty)
				return;
			while (reader.NodeType != System.Xml.XmlNodeType.EndElement)
			{
				reader.ReadStartElement("item");
				reader.ReadStartElement("key");
				var key = (string)keySerializer.Deserialize(reader);
				reader.ReadEndElement();
				reader.ReadStartElement("value");
				var value = (string)valueSerializer.Deserialize(reader);
				reader.ReadEndElement();
				Add(key, value);
				reader.ReadEndElement();
				reader.MoveToContent();
			}
			reader.ReadEndElement();

		}

		public void WriteXml(System.Xml.XmlWriter writer)
		{
			var keySerializer = new XmlSerializer(typeof(string));
			var valueSerializer = new XmlSerializer(typeof(string));
			foreach (string key in Keys)
			{
				writer.WriteStartElement("item");
				writer.WriteStartElement("key");
				keySerializer.Serialize(writer, key);
				writer.WriteEndElement();
				writer.WriteStartElement("value");
				string value = this[key];
				valueSerializer.Serialize(writer, value);
				writer.WriteEndElement();
				writer.WriteEndElement();
			}
		}

		#endregion
	}
}
