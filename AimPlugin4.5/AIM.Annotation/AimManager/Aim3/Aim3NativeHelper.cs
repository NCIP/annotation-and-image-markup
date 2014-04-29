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
using System.Linq;
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim3
{
	internal class Aim3NativeXmlHelper : IAimNativeHelper
	{
		private aim_dotnet.XmlModel _xmlModel;

		private aim_dotnet.XmlModel Model
		{
			get { return _xmlModel ?? (_xmlModel = new aim_dotnet.XmlModel()); }
		}

		#region IDisposable Members

		public void Dispose()
		{
			if (_xmlModel != null)
			{
				_xmlModel.Dispose();
				_xmlModel = null;
			}
		}

		#endregion

		public AimVersion AimVersion
		{
			get { return AimVersion.AimVersion3; }
		}

		public bool WriteXmlAnnotationToFile(aim_dotnet.Annotation annotation, string filePathName)
		{
			try
			{
				Model.WriteAnnotationToFile(annotation, filePathName);
				return true;
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to save annotation to file \"{0}\"", filePathName);
			}

			return false;
		}

		// Writes all annotations to a given folder. Returns number of annotations written.
		public string[] WriteXmlAnnotationsToFolder(List<aim_dotnet.Annotation> annotations, string folderPath)
		{
			List<string> savedFileNames = new List<string>();
			foreach (var annotation in annotations)
			{
				if (annotation == null)
					continue;

				string xmlFileName = null;
				string fileName = string.IsNullOrEmpty(annotation.UniqueIdentifier)
									  ? System.IO.Path.GetFileNameWithoutExtension(System.IO.Path.GetRandomFileName())
									  : annotation.UniqueIdentifier;
				try
				{
					xmlFileName = string.Format("{0}.xml", System.IO.Path.Combine(folderPath, fileName));
					Model.WriteAnnotationToFile(annotation, xmlFileName);
					savedFileNames.Add(xmlFileName);
				}
				catch (Exception ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to save annotation to file \"{0}\"", xmlFileName);
					try
					{
						if (!string.IsNullOrEmpty(xmlFileName))
							System.IO.File.Delete(xmlFileName);
					}
					catch (Exception)
					{
					}
				}
			}

			return savedFileNames.ToArray();
		}

		internal string WriteXmlAnnotationToString(Aim3ObjectReference @object)
		{
			return WriteXmlAnnotationToString(@object.AimAnnotation);
		}

		internal string WriteXmlAnnotationToString(aim_dotnet.Annotation annotation)
		{
			try
			{
				return Model.WriteAnnotationToXmlString(annotation);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to convert annotation to xml.");
			}

			return null;
		}

		internal List<Aim3ObjectReference> ReadAnnotationsFromFile(string filePathName)
		{
			try
			{
				var annotations = Model.ReadAnnotationsFromFile(filePathName);
				if (annotations != null)
					return annotations.Select(annotation => new Aim3ObjectReference(annotation)).ToList();
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 3 annotations from XML file " + filePathName, ex);
			}

			return null;
		}

		internal Aim3ObjectReference ReadAnnotationFromString(string xmlString)
		{
			try
			{
				var annotation = Model.ReadAnnotationFromXmlString(xmlString);
				if (annotation != null)
					return new Aim3ObjectReference(annotation);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 3 annotations from XML string:\n" + xmlString, ex);
			}

			return null;
		}
	}

	internal class Aim3NativeDcmHelper : IAimNativeHelper
	{
		private aim_dotnet.DcmModel _dcmModel;

		private aim_dotnet.DcmModel Model
		{
			get { return _dcmModel ?? (_dcmModel = new aim_dotnet.DcmModel()); }
		}

		#region IDisposable Members

		public void Dispose()
		{
			if (_dcmModel != null)
			{
				_dcmModel.Dispose();
				_dcmModel = null;
			}
		}

		#endregion

		public AimVersion AimVersion
		{
			get { return AimVersion.AimVersion3; }
		}

		public string WriteAnnotationToTempFile(IAimObjectReference aimObjectReference)
		{
			Platform.CheckForNullReference(aimObjectReference, "aimObjectReference");

			if (aimObjectReference.AimVersion != AimVersion.AimVersion3)
				return null;

			var aim3ObjectReference = aimObjectReference as Aim3ObjectReference;
			if (aim3ObjectReference == null)
				throw new AimManagerException("AIM3 helper cannot operate on non-AIM3 objects");

			string tempFileName = System.IO.Path.GetTempFileName();
			try
			{
				Model.WriteAnnotationToFile(aim3ObjectReference.AimAnnotation, tempFileName);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to save annotation to temp file.", ex);
				try
				{
					System.IO.File.Delete(tempFileName);
				}
				catch
				{
				}
				throw new AimManagerException("Failed to save annotation to a temp file", ex);
			}

			return tempFileName;
		}

		public List<aim_dotnet.Annotation> ReadAnnotationsFromFile(string filePathName)
		{
			try
			{
				return Model.ReadAnnotationsFromFile(filePathName);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 3 annotations from file " + filePathName, ex);
			}

			return null;
		}
	}
}
