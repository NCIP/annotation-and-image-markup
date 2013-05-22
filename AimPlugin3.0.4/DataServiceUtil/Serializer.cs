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

namespace TCGA_GRID
{
    /// <summary>
    /// Provides serialization and file IO support for all domain
    /// classes in this namespace.
    /// </summary>
    public class Serializer
    {
        /// <summary>
        /// Returns the target namespace for the serializer.
        /// </summary>
        public static string TargetNamespace
        {
            get
            {
                return "http://Imaging.caBIG/1.0/edu.northwestern.radiology.qf";
            }
        }
        /// <summary>
        /// Returns the set of included namespaces for the serializer.
        /// </summary>
        /// <returns>
        /// The set of included namespaces for the serializer.
        /// </returns>
        public static XmlSerializerNamespaces GetNamespaces()
        {
            XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
            ns.Add("qf", "http://Imaging.caBIG/1.0/edu.northwestern.radiology.qf");
            ns.Add("xs", "http://www.w3.org/2001/XMLSchema");
            ns.Add("xsi", "http://www.w3.org/2001/XMLSchema-instance");
            return ns;
        }
        /// <summary>
        /// Serializes the <i>Obj</i> to an XML string.
        /// </summary>
        /// <param name="Obj">
        /// The object to serialize.</param>
        /// <param name="ObjType">The object type.</param>
        /// <returns>
        /// The serialized object XML string.
        /// </returns>
        /// <remarks>
        /// The <see cref="PrettyPrint" /> property provides
        /// an easy-to-read formatted XML string.
        /// </remarks>
        public static string ToXml(object Obj, System.Type ObjType)
        {
            XmlSerializer ser;
            ser = new XmlSerializer(ObjType, Serializer.TargetNamespace);
            MemoryStream memStream;
            memStream = new MemoryStream();
            XmlTextWriter xmlWriter;
            xmlWriter = new XmlTextWriter(memStream, Encoding.UTF8);
            if (Serializer.PrettyPrint)
            {
                xmlWriter.Formatting = Formatting.Indented;
                xmlWriter.Indentation = 1;
                xmlWriter.IndentChar = Convert.ToChar(9);
            }
            xmlWriter.Namespaces = true;
            ser.Serialize(xmlWriter, Obj, Serializer.GetNamespaces());
            xmlWriter.Close();
            memStream.Close();
            string xml;
            xml = Encoding.UTF8.GetString(memStream.GetBuffer());
            xml = xml.Substring(xml.IndexOf(Convert.ToChar(60)));
            xml = xml.Substring(0, (xml.LastIndexOf(Convert.ToChar(62)) + 1));
            return xml;
        }
        /// <summary>
        /// Creates an object from an XML string.
        /// </summary>
        /// <param name="Xml">
        /// XML string to serialize.</param>
        /// <param name="ObjType">The object type to create.</param>
        /// <returns>
        /// An object of type <i>ObjType</i>.
        /// </returns>
        public static object FromXml(string Xml, System.Type ObjType)
        {
            XmlSerializer ser;
            ser = new XmlSerializer(ObjType);
            StringReader stringReader;
            stringReader = new StringReader(Xml);
            XmlTextReader xmlReader;
            xmlReader = new XmlTextReader(stringReader);
            object obj;
            obj = ser.Deserialize(xmlReader);
            xmlReader.Close();
            stringReader.Close();
            return obj;
        }
        /// <summary>
        /// The member for the <see cref="PrettyPrint" />
        /// property.
        /// </summary>
        private static bool @__PrettyPrint;
        /// <summary>
        /// Get or sets the pretty print property.
        /// </summary>
        /// <remarks>
        /// If <b>true</b>, the XML output by the
        /// <see cref="ToXml" /> method is indented in
        /// a hierarchichal manner using one tab character
        /// per level, each level being on a new line. 
        /// If <b>false</b>, no indentation or newline
        /// characters are set in the output.
        /// </remarks>
        public static bool PrettyPrint
        {
            get
            {
                return Serializer.@__PrettyPrint;
            }
            set
            {
                Serializer.@__PrettyPrint = value;
            }
        }

        internal static string ToXml(QueryRequestCqlQuery arg, QueryRequestCqlQuery arg1)
        {
            throw new NotImplementedException();
        }
    }
}
