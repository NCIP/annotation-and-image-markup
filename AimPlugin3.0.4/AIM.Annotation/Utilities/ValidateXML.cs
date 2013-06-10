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
using System.Reflection;
using System.Xml;
using System.Xml.Schema;

namespace AIM.Annotation.Utilities
{
    class ValidateXML
    {
        static ValidationResult vResult;

        static public ValidationResult Initialize(string xmlSchemaResourceName, string xmlTargetNamespace, string xmlDocumentFilename)
        {
			vResult = new ValidationResult();
            XmlSchema schema;
            var assembly = Assembly.GetExecutingAssembly();
            var stream = assembly.GetManifestResourceStream(xmlSchemaResourceName);
            var aimSettings = new XmlReaderSettings();
            aimSettings.Schemas.Add(xmlTargetNamespace, XmlReader.Create(stream));
            aimSettings.ValidationType = ValidationType.Schema;
            aimSettings.ValidationEventHandler += booksSettingsValidationEventHandler;

            var books = XmlReader.Create(xmlDocumentFilename, aimSettings);

            try 
            {
                while (books.Read()) { }
                stream.Seek(0, SeekOrigin.Begin);
                schema = XmlSchema.Read(XmlReader.Create(stream), booksSettingsValidationEventHandler);
                vResult.ValidatedVersion = schema.Version;
                Console.WriteLine("DONE");
            } 
            catch (XmlException xmlEx)
            {
                vResult.Exception = xmlEx;
                Console.Write("ERROR: ");
                Console.WriteLine(xmlEx.Message);
            }
 
            if (vResult.Exception != null)
                vResult.Validated = false;
            else
                vResult.Validated = true;

            return vResult;

        }

        static void booksSettingsValidationEventHandler(object sender, ValidationEventArgs e)
        {
            if (e.Severity == XmlSeverityType.Warning)
            {
                Console.Write("WARNING: ");
                Console.WriteLine(e.Message);
                vResult.Exception = e.Exception;
            }
            else if (e.Severity == XmlSeverityType.Error)
            {
                Console.Write("ERROR: ");
                Console.WriteLine(e.Message);
                vResult.Exception = e.Exception;
            }
        }

        public static string ReadFile(string file)
        {
            try
            {
                var xml = string.Empty;
                using (var reader = new StreamReader(file))
                {
                    xml = reader.ReadToEnd();
                    reader.Close();
                }
                return xml;
            }
            catch { }
            return null;
        }

    }
}
