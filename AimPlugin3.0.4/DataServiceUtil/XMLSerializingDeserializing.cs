//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace DataServiceUtil
{
	public class XMLSerializingDeserializing
	{
		/// <summary>
		/// Serializes an object into an Xml Document
		/// </summary>
		/// <param name="o">The object to serialize</param>
		/// <returns>An Xml Document consisting of said object's data</returns>
		public static XmlDocument Serialize(object o)
		{
			var s = new XmlSerializer(o.GetType());
			var ms = new MemoryStream();
			var writer = new XmlTextWriter(ms, new UTF8Encoding());
			writer.Formatting = Formatting.Indented;
			writer.IndentChar = ' ';
			writer.Indentation = 5;
			Exception caught = null;

			try
			{
				s.Serialize(writer, o);
				var xml = new XmlDocument();
				var xmlString = ASCIIEncoding.UTF8.GetString(ms.ToArray());
				xml.LoadXml(xmlString);
				return xml;
			}
			catch (Exception e)
			{
				caught = e;
			}
			finally
			{
				writer.Close();
				ms.Close();

				if (caught != null)
					throw caught;
			}
			return null;
		}

		/// <summary>
		/// Deserializes an xml document back into an object
		/// </summary>
		/// <param name="xml">The xml data to deserialize</param>
		/// <param name="type">The type of the object being deserialized</param>
		/// <returns>A deserialized object</returns>
		public static object Deserialize(XmlDocument xml, Type type)
		{
			var s = new XmlSerializer(type);
			var xmlString = xml.OuterXml;
			var buffer = ASCIIEncoding.UTF8.GetBytes(xmlString);
			var ms = new MemoryStream(buffer);
			XmlReader reader = new XmlTextReader(ms);
			Exception caught = null;

			try
			{
				object o = s.Deserialize(reader);
				return o;
			}

			catch (Exception e)
			{
				caught = e;
			}
			finally
			{
				reader.Close();

				if (caught != null)
					throw caught;
			}
			return null;
		}
	}
}
