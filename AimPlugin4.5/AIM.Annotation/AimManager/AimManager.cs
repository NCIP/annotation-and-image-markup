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
using System.Diagnostics;
using System.IO;
using System.Linq;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.StudyManagement;

using AIM.Annotation.TemplateTree;
using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager
{
	public enum AimVersion
	{
		Unknown = -1,
		AimVersion3,
		AimVersion4
	}

	public class AimManager
	{
		private static volatile AimManager _instance;
		private static readonly object _syncRoot = new Object();

		public static AimVersion DefaultAimVersion = AimVersion.AimVersion4;
		public static AimVersion[] SupportedAimVersions = new[]
			{
				DefaultAimVersion
			};
		public static string AimModality = "SR";

		public static AimManager Instance
		{
			get
			{
				if (_instance == null)
				{
					lock (_syncRoot)
					{
						if (_instance == null)
							_instance = new AimManager();
					}
				}
				return _instance;
			}
		}

		private AimManager()
		{
		}

		/// <summary>
		/// Saves given instances to temp files and performs requested operation on each of the saved file.
		/// NOTE: The temp file must me manually deleted during post save operation or it will stay in the temp folder.
		/// <exception cref="AimManagerException">AimManagerException</exception> can be thrown if save of an annotation fails.
		/// </summary>
		/// <param name="aimAnnotationReferences">List of annotation containers to save</param>
		/// <param name="postSaveProcessor">Operation to perform on each saved temp file</param>
		public void WriteDicomAnnotationsToTempFiles(List<IAimObjectReference> aimAnnotationReferences, Action<string> postSaveProcessor)
		{
			if (aimAnnotationReferences == null)
				return;

			var aim3Annotations = aimAnnotationReferences.Where(aimObject => aimObject != null && aimObject.AimVersion == AimVersion.AimVersion3).ToList();
			if (aim3Annotations.Any())
			{
				using (var aim3NativeHelper = new Aim3.Aim3NativeDcmHelper())
				{
					foreach (var aim3Annotation in aim3Annotations)
					{
						var tempFileName = aim3NativeHelper.WriteAnnotationToTempFile(aim3Annotation);
						if (tempFileName != null && postSaveProcessor != null)
							postSaveProcessor(tempFileName);
						else if (tempFileName != null)
						{
							// TODO - delete temp file?
						}
					}
				}
			}
			var aim4Annotations = aimAnnotationReferences.Where(aimObject => aimObject != null && aimObject.AimVersion == AimVersion.AimVersion4).ToList();
			if (aim4Annotations.Any())
			{
				using (var aim4NativeHelper = new Aim4.Aim4NativeDcmHelper())
				{
					foreach (var aim4Annotation in aim4Annotations)
					{
						var tempFileName = aim4NativeHelper.WriteAnnotationToTempFile(aim4Annotation);
						if (tempFileName != null && postSaveProcessor != null)
							postSaveProcessor(tempFileName);
						else if (tempFileName != null)
						{
							// TODO - delete temp file?
						}
					}
				}
			}

			if (aim3Annotations.Count + aim4Annotations.Count != aimAnnotationReferences.Count)
			{
				Platform.Log(LogLevel.Error, "AimManager.WriteDicomAnnotationsToTempFiles: not all annotations can be saved to DICOM files.");
				throw new NotImplementedException("Cannot save some of the annotations to DICOM files. Unknown version of AIM was encountered?");
			}
		}

		/// <summary>
		/// Writes annotation to folder
		/// </summary>
		/// <param name="aimAnnotationReferences">List of annotations to write</param>
		/// <param name="folderPath">Complete folder path</param>
		/// <returns>List of complete file names that are written to the folder</returns>
		public string[] WriteXmlAnnotationsToFolder(List<IAimObjectReference> aimAnnotationReferences, string folderPath)
		{
			Platform.CheckForNullReference(aimAnnotationReferences, "aimAnnotationReferences");
			Platform.CheckForEmptyString(folderPath, "folderPath");

			string[] createdFiles = null;

			var aim3Annotations = (from aimInstance in aimAnnotationReferences where aimInstance != null && aimInstance.AimVersion == AimVersion.AimVersion3 select ((Aim3.Aim3ObjectReference) aimInstance).AimAnnotation).ToList();
			if (aim3Annotations.Any())
			{
				using (var aim3NativeHelper = new Aim3.Aim3NativeXmlHelper())
				{
					createdFiles = aim3NativeHelper.WriteXmlAnnotationsToFolder(aim3Annotations, folderPath);
				}
			}

			var aim4Annotations = (from aimInstance in aimAnnotationReferences where aimInstance != null && aimInstance.AimVersion == AimVersion.AimVersion4 select ((Aim4.Aim4ObjectReference)aimInstance).AnnotationCollection).ToList();
			if (aim4Annotations.Any())
			{
				using (var aim4NativeHelper = new Aim4.Aim4NativeXmlHelper())
				{
					createdFiles = aim4NativeHelper.WriteXmlAnnotationsToFolder(aim4Annotations, folderPath);
				}
			}

			var unknownAimVersion = aimAnnotationReferences.Where(aimInstance => aimInstance != null && aimInstance.AimVersion != AimVersion.AimVersion3 && aimInstance.AimVersion != AimVersion.AimVersion4).ToList();
			if (unknownAimVersion.Any())
			{
				Platform.Log(LogLevel.Error, "AimManager.WriteXmlAnnotationsToFolder: not all annotations can be saved to XML files [" + unknownAimVersion.Count + "].");
				throw new NotImplementedException("Cannot save some of the annotations to XML files [" + unknownAimVersion.Count + "]. Unknown version of AIM was encountered?");
			}

			return createdFiles;
		}

		public Dictionary<string, string> WriteXmlAnnotationsToString(List<IAimObjectReference> aimAnnotationReferences)
		{
			Platform.CheckForNullReference(aimAnnotationReferences, "aimAnnotationReferences");

			var writtenAnnotations = new Dictionary<string, string>();

			var aim3Annotations = (from aimInstance in aimAnnotationReferences where aimInstance != null && aimInstance.AimVersion == AimVersion.AimVersion3 select ((Aim3.Aim3ObjectReference)aimInstance).AimAnnotation).ToList();
			if (aim3Annotations.Any())
			{
				using (var aim3NativeHelper = new Aim3.Aim3NativeXmlHelper())
				{
					foreach (var annotation in aim3Annotations)
					{
						writtenAnnotations.Add(annotation.UniqueIdentifier, aim3NativeHelper.WriteXmlAnnotationToString(annotation));
					}
				}
			}

			var aim4Annotations = (from aimInstance in aimAnnotationReferences where aimInstance != null && aimInstance.AimVersion == AimVersion.AimVersion4 select ((Aim4.Aim4ObjectReference)aimInstance).AnnotationCollection).ToList();
			if (aim4Annotations.Any())
			{
				using (var aim4NativeHelper = new Aim4.Aim4NativeXmlHelper())
				{
					foreach (var annotation in aim4Annotations)
					{
						writtenAnnotations.Add((annotation.UniqueIdentifier ?? Aim4.AimNativeConverter.NewUid).Uid, aim4NativeHelper.WriteXmlAnnotationToString(annotation));
					}
				}
			}

			var unknownAimVersion = aimAnnotationReferences.Where(aimInstance => aimInstance != null && aimInstance.AimVersion != AimVersion.AimVersion3 && aimInstance.AimVersion != AimVersion.AimVersion4).ToList();
			if (unknownAimVersion.Any())
			{
				Platform.Log(LogLevel.Error, "AimManager.WriteXmlAnnotationsToString: not all annotations can be saved to XML string [" + unknownAimVersion.Count + "].");
				throw new NotImplementedException("Cannot save some of the annotations to XML string [" + unknownAimVersion.Count + "]. Unknown version of AIM was encountered?");
			}

			return writtenAnnotations;
		}

		public string GetAimAnnotationHtml(IAimAnnotationInstance aimAnnotationInstance)
		{
			if (aimAnnotationInstance == null)
				return null;

			switch (aimAnnotationInstance.AimVersion)
			{
				case AimVersion.AimVersion3:
					return Aim3.AimHtmlFormatter.GetAimHtml((Aim3.Aim3AnnotationInstance)aimAnnotationInstance);
				case AimVersion.AimVersion4:
					return Aim4.AimHtmlFormatter.GetAimHtml((Aim4.Aim4AnnotationInstance)aimAnnotationInstance);
				default:
					Debug.Assert(false, "AimManager.GetAimAnnotationHtml: Unexpected AIM version");
					break;
			}

			return null;
		}

		public AimTemplateTree AimAnnotationToTemplateTree(IAimAnnotationInstance aimAnnotation, AimTemplateTree startingTree)
		{
			if (aimAnnotation == null)
				return null;

			switch (aimAnnotation.AimVersion)
			{
				case AimVersion.AimVersion3:
					return Aim3.AimTemplateConverter.AimAnnotationToAimTemplateTree((Aim3.Aim3AnnotationInstance)aimAnnotation, startingTree);
				case AimVersion.AimVersion4:
					return Aim4.AimTemplateConverter.AimAnnotationToAimTemplateTree((Aim4.Aim4AnnotationInstance)aimAnnotation, startingTree);
				default:
					Debug.Assert(false, "AimManager.AimAnnotationToTemplateTree: Unexpected AIM version");
					break;
			}

			return null;
		}

		// Creates new AIM Annotation object that is NOT saved to a permanent storage
		internal List<IAimObjectReference> CreateAimAnnotations(IList<IPresentationImage> presentationImages, AimAnnotationCreationContext creationContext,
														   IList<IGraphic> selectedMarkup, out List<IGraphic> annotationsGraphic)
		{
			switch (DefaultAimVersion)
			{
				case AimVersion.AimVersion3:
					{
						var annotations = Aim3.AimNativeConverter.CreateAimAnnotations(presentationImages, creationContext, selectedMarkup, out annotationsGraphic);
						if (annotations != null)
						{
							return (from annotationInstance in annotations where annotationInstance != null select new Aim3.Aim3ObjectReference(annotationInstance)).Cast<IAimObjectReference>().ToList();
						}
					}
					break;
				case AimVersion.AimVersion4:
					{
						var annotations = Aim4.AimNativeConverter.CreateAimAnnotations(presentationImages, creationContext, selectedMarkup, out annotationsGraphic);
						if (annotations != null)
							return new List<IAimObjectReference> { new Aim4.Aim4ObjectReference(annotations) };
					}
					break;
				default:
					Debug.Assert(false, "AimManager.CreateAimAnnotation: Unexpected AIM version");
					break;
			}

			annotationsGraphic = null;
			return null;
		}

		/// <summary>
		/// Reads given AIM XML documents into memory
		/// </summary>
		/// <param name="aimVersion">Version of AIM given files are expected to be</param>
		/// <param name="filePaths">List of AIM XML documents on disk</param>
		/// <returns>Returns a dictionary of AIM file names mapped to the AIM XML document content</returns>
		public Dictionary<string, string> ReadXmlAnnotationsToMemory(AimVersion aimVersion, List<string> filePaths)
		{
			var uidToAnnotationDictionary = new Dictionary<string, string>();

			if (filePaths.IsNullOrEmpty())
				return uidToAnnotationDictionary;

			switch (aimVersion)
			{
				case AimVersion.AimVersion3:
					{
						using (var aim3NativeHelper = new Aim3.Aim3NativeXmlHelper())
						{
							foreach (var filePath in filePaths)
							{
								var annotations = aim3NativeHelper.ReadAnnotationsFromFile(filePath);
								if (annotations != null)
								{
									Debug.Assert(annotations.Count < 2, "AIM 3 XML Annotation document cannot have more than one annotation");
									foreach (var annotation in annotations.Where(ann => ann != null))
									{
										var strAnnotation = aim3NativeHelper.WriteXmlAnnotationToString(annotation);
										if (!String.IsNullOrEmpty(strAnnotation))
											uidToAnnotationDictionary.Add(filePath, strAnnotation);
									}
								}
							}
						}
					}
					break;
				case AimVersion.AimVersion4:
					{
						using (var aim4NativeHelper = new Aim4.Aim4NativeXmlHelper())
						{
							foreach (var filePath in filePaths)
							{
								var annotation = aim4NativeHelper.ReadAnnotationFromFile(filePath);
								if (annotation != null)
								{
									var strAnnotation = aim4NativeHelper.WriteXmlAnnotationToString(annotation);
									if (!String.IsNullOrEmpty(strAnnotation))
										uidToAnnotationDictionary.Add(filePath, strAnnotation);
								}
							}
						}
					}
					break;
				default:
					Debug.Assert(false, "AimManager.ReadXmlAnnotationsToMemory: Unexpected AIM version");
					break;
			}

			return uidToAnnotationDictionary;
		}

		public IAimObjectReference ReadXmlAnnotationFromString(AimVersion aimVersion, string xmlString)
		{
			IAimObjectReference aimObjectReference = null;
			switch (aimVersion)
			{
					case AimVersion.AimVersion3:
					{
						using (var aim3NativeHelper = new Aim3.Aim3NativeXmlHelper())
						{
							aimObjectReference = aim3NativeHelper.ReadAnnotationFromString(xmlString);
						}
					}
					break;
					case AimVersion.AimVersion4:
					{
						using (var aim4NativeHelper = new Aim4.Aim4NativeXmlHelper())
						{
							aimObjectReference = aim4NativeHelper.ReadAnnotationFromString(xmlString);
						}
					}
					break;
				default:
					Debug.Assert(false, "AimManager.ReadXmlAnnotationFromString: Unexpected AIM version");
					break;
			}

			return aimObjectReference;
		}

		// Populates given IPresentationImage with graphics from the given annotation
		internal bool ReadGraphicsFromAnnotation(IAimDocumentInstance annotationDoc, IPresentationImage presentationImage)
		{
			if (annotationDoc == null)
				return false;

			Platform.CheckForNullReference(presentationImage, "presentationImage");

			var isRead = false;
			switch (annotationDoc.AimVersion)
			{
				case AimVersion.AimVersion3:
					var aim3AnnotationDoc = (Aim3.Aim3DocumentInstance) annotationDoc;
					foreach (var annotation in aim3AnnotationDoc.AimAnnotations.OfType<Aim3.Aim3AnnotationInstance>())
					{
						isRead |= Aim3.AimNativeConverter.ReadGraphicsFromAnnotation(annotation, presentationImage);
					}
					break;
				case AimVersion.AimVersion4:
					var aim4AnnotationDoc = (Aim4.Aim4DocumentInstance) annotationDoc;
					foreach (var annotation in aim4AnnotationDoc.AimAnnotations.OfType<Aim4.Aim4AnnotationInstance>())
					{
						isRead |= Aim4.AimNativeConverter.ReadGraphicsFromAnnotation(annotation, presentationImage);
					}
					break;
				default:
					Debug.Assert(false, "AimManager.ReadGraphicsFromAnnotation: Unexpected AIM version");
					break;
			}

			return isRead;
		}

		public static List<string> ConvertAnnotationsFromXmlToDicomFiles(AimVersion aimVersion, List<string> xmlAnnotationsFilePathNames, IBackgroundTaskContext context, out List<string> invalidFiles)
		{
			Platform.CheckForNullReference(xmlAnnotationsFilePathNames, "xmlAnnotationsFilePathNames");

			var convertedAnnotations = new List<string>();
			invalidFiles = new List<string>();

			switch (aimVersion)
			{
					case AimVersion.AimVersion3:
					{
						int cnt = 0;
						using (var aim3NativeXmlHelper = new Aim3.Aim3NativeXmlHelper())
						{
							using (var aim3NativeDcmHelper = new Aim3.Aim3NativeDcmHelper())
							{
								foreach (string aimFile in xmlAnnotationsFilePathNames.Where(pathName => pathName != null))
								{
									// Read XML file
									ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count, String.Format("Reading file {0}", Path.GetFileName(aimFile)));
									var annotations = aim3NativeXmlHelper.ReadAnnotationsFromFile(aimFile);

									if (annotations.IsNullOrEmpty())
									{
										Platform.Log(LogLevel.Info, "No annotation is read from file {0}", Path.GetFileName(aimFile));
										invalidFiles.Add(Path.GetFileName(aimFile));
									}
									else
									{
										// Write to temp file
										ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count,
														   String.Format("Read {0} annotations from file {1}", annotations.Count, Path.GetFileName(aimFile)));
										int dcmFileCnt = 0;
										foreach (var annotation in annotations)
										{
											ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count,
															   String.Format("Writing converted annotation to temporary file [{0} of {1}]", ++dcmFileCnt, annotations.Count));

											var tempFileName = aim3NativeDcmHelper.WriteAnnotationToTempFile(annotation);
											convertedAnnotations.Add(tempFileName);

											ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count,
															   String.Format("Wrote converted annotation to file {0} [{1} of {2}]", tempFileName, dcmFileCnt, annotations.Count));
										}
									}
									if (context != null && context.CancelRequested)
									{
										break;
									}
									cnt++;
								}
							}
						}
					}
					break;
					case AimVersion.AimVersion4:
					{
						int cnt = 0;
						using (var aim4NativeXmlHelper = new Aim4.Aim4NativeXmlHelper())
						{
							using (var aim4NativeDcmHelper = new Aim4.Aim4NativeDcmHelper())
							{
								foreach (string aimFile in xmlAnnotationsFilePathNames.Where(pathName => pathName != null))
								{
									// Read XML file
									ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count, String.Format("Reading file {0}", Path.GetFileName(aimFile)));
									var annotation = aim4NativeXmlHelper.ReadAnnotationFromFile(aimFile);

									if (annotation == null)
									{
										Platform.Log(LogLevel.Info, "No annotation is read from file {0}", Path.GetFileName(aimFile));
										invalidFiles.Add(Path.GetFileName(aimFile));
									}
									else
									{
										// Write to temp file
										ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count,
										                   String.Format("Read annotation collection from file {0}", Path.GetFileName(aimFile)));

										var tempFileName = aim4NativeDcmHelper.WriteAnnotationToTempFile(annotation);
										convertedAnnotations.Add(tempFileName);

										ReportTaskProgress(context, cnt, xmlAnnotationsFilePathNames.Count,
										                   String.Format("Wrote converted annotation collection to file {0}", tempFileName));
									}
									if (context != null && context.CancelRequested)
									{
										break;
									}
									cnt++;
								}
							}
						}
					}
					break;
				default:
					Debug.Assert(false, "AimManager.ConvertAnnotationsFromXmlToDicomFiles: Unexpected AIM version");
					break;
			}

			return convertedAnnotations;
		}

		private static void ReportTaskProgress(IBackgroundTaskContext context, int index, int total, string message)
		{
			if (context != null)
				context.ReportProgress(new BackgroundTaskProgress(index, total, message));
		}

		public List<IAimDocumentInstance> LoadLocalAnnotationsForStudy(string studyInstanceUid)
		{
			return AimCache.Instance.GetAnnotationsForStudy(studyInstanceUid);
		}

		public static AimVersion GetAimVersionFromSop(Sop sopInstance)
		{
			var docConceptSeq = sopInstance[DicomTags.ConceptNameCodeSequence].Values as DicomSequenceItem[];
			if (docConceptSeq != null && docConceptSeq.Length > 0 && docConceptSeq[0][DicomTags.CodeValue].ToString() == "zzz001")
			{
				// Checking Coding Scheme Version of the  AIM SR Container should be enough
				if (docConceptSeq[0][DicomTags.CodingSchemeVersion].ToString() == "04")
					return AimVersion.AimVersion4;
				if (docConceptSeq[0][DicomTags.CodingSchemeVersion].ToString() == "03")
					return AimVersion.AimVersion3;
			}
			else
			{
				Platform.Log(LogLevel.Debug,
							 "Failed to find AIM SR version number. Is this unsupported AIM version or not an AIM SR? [SOPInstanceUID=" +
							 sopInstance.SopInstanceUid + "]");
			}
			return AimVersion.Unknown;
		}

		public static IDataProvider GetDataProvider(IAimAnnotationInstance annotationInstance)
		{
			if (annotationInstance == null)
				return null;

			IDataProvider dataProvider = null;
			switch (annotationInstance.AimVersion)
			{
				case AimVersion.AimVersion3:
					dataProvider = new Aim3.DataProvider(((Aim3.Aim3AnnotationInstance)annotationInstance).AimAnnotation);
					break;
				case AimVersion.AimVersion4:
					var aim4AnnotationInstance = (Aim4.Aim4AnnotationInstance) annotationInstance;
					var aim4DocumentInstance = (Aim4.Aim4DocumentInstance) aim4AnnotationInstance.ParentAimDocument;
					dataProvider = new Aim4.DataProvider(aim4AnnotationInstance.AimAnnotationEntity, aim4DocumentInstance.Person, aim4DocumentInstance.User);
					break;
				default:
					Debug.Assert(false, "Cannot get converter for unknown annotation version: " + annotationInstance.AimVersion);
					break;
			}

			return dataProvider;
		}

		public static List<IDataProvider> GetDataProviders(IAimObjectReference aimObjectReference)
		{
			if (aimObjectReference == null)
				return null;

			List<IDataProvider> dataProviders = null;
			switch (aimObjectReference.AimVersion)
			{
				case AimVersion.AimVersion3:
					return new List<IDataProvider> {new Aim3.DataProvider(((Aim3.Aim3ObjectReference) aimObjectReference).AimAnnotation)};
				case AimVersion.AimVersion4:
					var aim4AnnotationCollection = ((Aim4.Aim4ObjectReference) aimObjectReference).AnnotationCollection;
					var aim4ImageAnnotationCollection = aim4AnnotationCollection as aim4_dotnet.ImageAnnotationCollection;
					if (aim4ImageAnnotationCollection != null)
					{
						dataProviders = aim4ImageAnnotationCollection.ImageAnnotations.Select(
							imageAnnotation => new Aim4.DataProvider(imageAnnotation, aim4ImageAnnotationCollection.Person, aim4ImageAnnotationCollection.User))
						                                             .Cast<IDataProvider>().ToList();
					}
					else
					{
						var aim4AnnotationOfAnnotationCollection = aim4AnnotationCollection as aim4_dotnet.AnnotationOfAnnotationCollection;
						if (aim4AnnotationOfAnnotationCollection != null)
						{
							dataProviders = aim4AnnotationOfAnnotationCollection.AnnotationOfAnnotations.Select(
								annOfAnnotation => new Aim4.DataProvider(annOfAnnotation, null, aim4AnnotationOfAnnotationCollection.User)).Cast<IDataProvider>().ToList();
						}
					}
					break;
				default:
					Debug.Assert(false, "Cannot get converter for unknown annotation version: " + aimObjectReference.AimVersion);
					break;
			}

			return dataProviders;
		}
	}
}
