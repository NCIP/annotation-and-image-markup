//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Dicom.DataStore;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Services.ServerTree;
using ClearCanvas.ImageViewer.StudyManagement;

namespace AIM.Annotation
{
	internal static class AimLoadHelper
	{
		public static List<aim_dotnet.Annotation> LoadAimAnnotations(IEnumerable<string> studyInstanceUids)
		{
			var annotationList = new List<aim_dotnet.Annotation>();
			using (var dcmModel = new aim_dotnet.DcmModel())
			{
				foreach (var studyInstanceUID in studyInstanceUids)
				{
					var aimInstanceDictionary = GetAimInstanceDictionaryForStudy(studyInstanceUID);
					var annotationSopsInfo = aimInstanceDictionary[studyInstanceUID];
					if (annotationSopsInfo == null)
						continue;

					foreach (var information in annotationSopsInfo)
					{
						try
						{
							annotationList.AddRange(dcmModel.ReadAnnotationsFromFile(information.InstanceFileName));
						}
						catch (Exception ex)
						{
							Platform.Log(LogLevel.Error, ex);
						}
					}
				}
			}

			return annotationList.Count > 0 ? annotationList : null;
		}

		public static AimInstanceDictionary GetAimInstanceDictionaryForStudy(string studyInstanceUID)
		{
			var annotationDictionary = new AimInstanceDictionary();
			var studyAnnotations = RetrieveAnnotationsInformationForStudy(studyInstanceUID);

			if (studyAnnotations == null || studyAnnotations.Count == 0)
				return annotationDictionary;

			using (var reader = DataAccessLayer.GetIDataStoreReader())
			{
				foreach (var studyItem in studyAnnotations)
				{
					var study = reader.GetStudy(studyItem.StudyInstanceUid) as ClearCanvas.Dicom.DataStore.Study;
					if (study != null)
					{
						var allSeries = study.GetSeries();
						foreach (var series in allSeries)
						{
							if (series != null && series.Modality == "SR")
							{
								var sopInstances = series.GetSopInstances();
								foreach (var sopInstance in sopInstances)
								{
									if (sopInstance != null)
									{
										var fileUri = sopInstance.GetLocationUri();
										if (fileUri.IsFile)
											annotationDictionary.Add(study.StudyInstanceUid, series.SeriesInstanceUid, sopInstance.SopInstanceUid, fileUri.LocalDiskPath);
									}
								}
							}
						}
					}
				}
			}
			return annotationDictionary;
		}

		private static StudyItemList RetrieveAnnotationsInformationForStudy(string studyInstanceUID)
		{
			var queryParams = new QueryParameters();
			queryParams.Add("PatientsName", "");
			queryParams.Add("ReferringPhysiciansName", "");
			queryParams.Add("PatientId", "");
			queryParams.Add("AccessionNumber", "");
			queryParams.Add("StudyDescription", "");
			queryParams.Add("ModalitiesInStudy", "SR");
			queryParams.Add("StudyDate", "");
			queryParams.Add("StudyInstanceUid", studyInstanceUID);

			var serverTree = new ServerTree();
			var failedServerInfo = new List<KeyValuePair<string, Exception>>();
			var localDataStoreList = new List<IServerTreeNode>();
			localDataStoreList.Add(serverTree.RootNode.LocalDataStoreNode);

			return Query(queryParams, failedServerInfo, localDataStoreList);
		}

		private static StudyItemList Query(QueryParameters queryParams, List<KeyValuePair<string, Exception>> failedServerInfo, List<IServerTreeNode> servers)
		{
			var aggregateStudyItemList = new StudyItemList();
			foreach (var serverNode in servers)
			{
				try
				{
					StudyItemList serverStudyItemList;

					if (serverNode.IsLocalDataStore)
					{
						serverStudyItemList = ImageViewerComponent.FindStudy(queryParams, null, "DICOM_LOCAL");
					}
					else if (serverNode.IsServer)
					{
						var server = (Server)serverNode;
						var ae = new ApplicationEntity(
							server.Host,
							server.AETitle,
							server.Name,
							server.Port,
							server.IsStreaming,
							server.HeaderServicePort,
							server.WadoServicePort);

						serverStudyItemList = ImageViewerComponent.FindStudy(queryParams, ae, "DICOM_REMOTE");
					}
					else
					{
						throw new Exception("Server is not queryable");
					}

					aggregateStudyItemList.AddRange(serverStudyItemList);
				}
				catch (Exception e)
				{
					failedServerInfo.Add(new KeyValuePair<string, Exception>(serverNode.Name, e));
				}
			}
			return aggregateStudyItemList;
		}
	}
}
