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
using ClearCanvas.Common;

namespace AIM.Annotation.AimManager.Aim4
{
	internal class Aim4NativeXmlHelper : IAimNativeHelper
	{
		private aim4_dotnet.XmlModel _xmlModel;

		private aim4_dotnet.XmlModel Model
		{
			get { return _xmlModel ?? (_xmlModel = new aim4_dotnet.XmlModel()); }
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
			get { return AimVersion.AimVersion4; }
		}

		public bool WriteAnnotationToFile(aim4_dotnet.AnnotationCollection annotation, string filePathName)
		{
			try
			{
				Model.WriteAnnotationCollectionToFile(annotation, filePathName);
				return true;
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to save annotation to file \"{0}\"", filePathName);
			}

			return false;
		}

		// Writes all annotations to a given folder. Returns paths and names of annotation files written.
		public string[] WriteXmlAnnotationsToFolder(List<aim4_dotnet.AnnotationCollection> annotations, string folderPath)
		{
			List<string> savedFileNames = new List<string>();
			foreach (var annotation in annotations)
			{
				if (annotation == null)
					continue;

				string xmlFileName = null;
				string fileName = string.IsNullOrEmpty(annotation.UniqueIdentifier == null ? null : annotation.UniqueIdentifier.Uid)
									  ? System.IO.Path.GetFileNameWithoutExtension(System.IO.Path.GetRandomFileName())
									  : annotation.UniqueIdentifier.Uid;
				try
				{
					xmlFileName = string.Format("{0}.xml", System.IO.Path.Combine(folderPath, fileName));
					Model.WriteAnnotationCollectionToFile(annotation, xmlFileName);
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

		public string WriteXmlAnnotationToString(Aim4ObjectReference @object)
		{
			return WriteXmlAnnotationToString(@object.AnnotationCollection);
		}

		public string WriteXmlAnnotationToString(aim4_dotnet.AnnotationCollection annotationCollection)
		{
			try
			{
				return Model.WriteAnnotationCollectionToXmlString(annotationCollection);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to convert annotation to xml.");
			}

			return null;
		}

		public Aim4ObjectReference ReadAnnotationFromFile(string filePathName)
		{
			try
			{
				var annotation = Model.ReadAnnotationCollectionFromFile(filePathName);
				if (annotation != null)
					return new Aim4ObjectReference(annotation);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 4 XML annotation from file " + filePathName, ex);
			}

			return null;
		}

		public Aim4ObjectReference ReadAnnotationFromString(string xmlString)
		{
			try
			{
				var annotation = Model.ReadAnnotationCollectionFromXmlString(xmlString);
				if (annotation != null)
					return new Aim4ObjectReference(annotation);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 4 XML annotation from XML string:\n" + xmlString, ex);
			}

			return null;
		}
	}


	internal class Aim4NativeDcmHelper : IAimNativeHelper
	{
		private aim4_dotnet.DcmModel _dcmModel;

		private aim4_dotnet.DcmModel Model
		{
			get { return _dcmModel ?? (_dcmModel = new aim4_dotnet.DcmModel()); }
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
			get { return AimVersion.AimVersion4; }
		}

		public string WriteAnnotationToTempFile(IAimObjectReference aimObjectReference)
		{
			Platform.CheckForNullReference(aimObjectReference, "aimObjectReference");

			if (aimObjectReference.AimVersion != AimVersion.AimVersion4)
				return null;

			var aim4ObjectReference = aimObjectReference as Aim4ObjectReference;
			if (aim4ObjectReference == null)
				throw new AimManagerException("AIM4 helper cannot operate on non-AIM4 objects");

			string tempFileName = System.IO.Path.GetTempFileName();
			try
			{
				Model.WriteAnnotationCollectionToFile(aim4ObjectReference.AnnotationCollection, tempFileName);
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

		public aim4_dotnet.AnnotationCollection ReadAnnotationsFromFile(string filePathName)
		{
			try
			{
				return Model.ReadAnnotationCollectionFromFile(filePathName);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, "Failed to read AIM 4 annotation from file " + filePathName, ex);
			}

			return null;
		}
	}
}
