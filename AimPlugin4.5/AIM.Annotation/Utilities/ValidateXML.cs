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
using System.Xml;
using System.Xml.Schema;
using System.Reflection;
using System.IO;

namespace AIM.Annotation.Utilities
{
	class ValidateXML
	{
		static ValidationResult vResult;

		static public ValidationResult Initialize(string xmlSchemaResourceName, string xmlTargetNamespace, string xmlDocumentFilename)
		{
			vResult = new ValidationResult();
			XmlSchema schema;
			Assembly assembly = Assembly.GetExecutingAssembly();
			// you can use reflector to get the full namespace of your embedded resource here 
			Stream stream = assembly.GetManifestResourceStream(xmlSchemaResourceName);
			assembly.GetManifestResourceInfo(xmlSchemaResourceName);
			assembly.GetManifestResourceNames();
			XmlSchemaSet schemas = new XmlSchemaSet();
			XmlReaderSettings aimSettings = new XmlReaderSettings();
			aimSettings.Schemas.Add(xmlTargetNamespace, XmlReader.Create(stream));
			aimSettings.ValidationType = ValidationType.Schema;
			aimSettings.ValidationEventHandler += new ValidationEventHandler(booksSettingsValidationEventHandler);

			XmlReader books = XmlReader.Create(xmlDocumentFilename, aimSettings);

			try
			{
				while (books.Read()) { }
				// We have to read the 
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

			books.Close();
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
				string xml = string.Empty;
				using (StreamReader reader = new StreamReader(file))
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
