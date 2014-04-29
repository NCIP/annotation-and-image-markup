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
using System.Linq;
using ClearCanvas.Common;
using ClearCanvas.Dicom.ServiceModel.Query;
using ClearCanvas.ImageViewer.Common;
using ClearCanvas.ImageViewer.Common.StudyManagement;
using ClearCanvas.ImageViewer.StudyManagement;
using GeneralUtilities.Collections;

namespace AIM.Annotation.AimManager
{
	internal class AimCache
	{
		private readonly Dictionary<string, WeakReference> _loadedStudies; // Map of Study Instance UID to WeakReference(List<IAimDocumentInstance>)

		private static readonly object _syncLock = new object();
		private static volatile AimCache _instance;

		public static AimCache Instance
		{
			get
			{
				if (_instance == null)
				{
					lock (_syncLock)
					{
						if (_instance == null)
							_instance = new AimCache();
					}
				}

				return _instance;
			}
		}

		private AimCache()
		{
			_loadedStudies = new Dictionary<string, WeakReference>();
		}

		public List<IAimDocumentInstance> GetAnnotationsForStudy(string studyInstanceUid)
		{
			lock (_syncLock)
			{
				if (_loadedStudies.ContainsKey(studyInstanceUid))
				{
					var studiesRef = _loadedStudies[studyInstanceUid];
					if (studiesRef.IsAlive)
						return ((AimDocumentInstanceList) studiesRef.Target).ToList();
				}

				var aimDocumentInstances = LoadLocalAimDocumentsForStudy(studyInstanceUid);
				// NOTE: Must add an entry for a loaded study; otherwise there would be no Update events
				_loadedStudies[studyInstanceUid] = new WeakReference(aimDocumentInstances == null ? null : new AimDocumentInstanceList(aimDocumentInstances));

				return aimDocumentInstances;
			}
		}

		// Updates cache and returns event args for AimActivityMonitor update event
		internal StudyAimAnnotationsChangedEventArgs UpdateCache(string studyUid)
		{
			// Update only already loaded studies
			if (!_loadedStudies.ContainsKey(studyUid))
				return null;

			// 1. Load study from source
			var aimDocumentInstances = LoadLocalAimDocumentsForStudy(studyUid);

			// 2. If there are changes from the previously loaded study, raise StudyAnnotationsChanged event
			List<IAimDocumentInstance> addedAimDocuments;
			List<IAimDocumentInstance> removedAimDocuments;
			lock (_syncLock)
			{
				var priorDocInstances = _loadedStudies.ContainsKey(studyUid) && _loadedStudies[studyUid].IsAlive
											? (AimDocumentInstanceList)_loadedStudies[studyUid].Target
											: null;

				addedAimDocuments = priorDocInstances.IsNullOrEmpty() || aimDocumentInstances == null
					? aimDocumentInstances
					: aimDocumentInstances.Except(priorDocInstances).ToList();
				removedAimDocuments = aimDocumentInstances.IsNullOrEmpty() || priorDocInstances == null
					? (priorDocInstances == null ? null : priorDocInstances.ToList())
					: priorDocInstances.Except(aimDocumentInstances).ToList();

				// Update collection reference in all new/removed annotations
				if (!addedAimDocuments.IsNullOrEmpty())
				{
					if (priorDocInstances == null)
					{
						_loadedStudies[studyUid] = new WeakReference(new AimDocumentInstanceList(addedAimDocuments));
					}
					else
					{
						priorDocInstances.AddRange(addedAimDocuments);
					}
				}
				if (removedAimDocuments != null)
				{
					Debug.Assert(priorDocInstances != null);
					priorDocInstances.Remove(removedAimDocuments);
				}
			}

			if (!addedAimDocuments.IsNullOrEmpty() || !removedAimDocuments.IsNullOrEmpty())
			{
				return new StudyAimAnnotationsChangedEventArgs(studyUid, removedAimDocuments, addedAimDocuments);
			}

			return null;
		}

		internal List<string> ClearCache()
		{
			lock (_syncLock)
			{
				// Return list of previously cached study UIDs
				var list = (from studyEntry in _loadedStudies where studyEntry.Value.IsAlive && !((List<IAimDocumentInstance>) studyEntry.Value.Target).IsNullOrEmpty() select studyEntry.Key).ToList();
				_loadedStudies.Clear();
				return list;
			}
		}

		///////////////////////////////////////////////////////////////////////
		// Instance Loading
		///////////////////////////////////////////////////////////////////////

		private struct AimFileInfo
		{
			public AimFileInfo(AimVersion aimVersion, string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid)
				: this()
			{
				AimVersion = aimVersion;
				StudyInstanceUid = studyInstanceUid;
				SeriesInstanceUid = seriesInstanceUid;
				SopInstanceUid = sopInstanceUid;
			}

			public AimVersion AimVersion { get; private set; }
			public string StudyInstanceUid { get; private set; }
			public string SeriesInstanceUid { get; private set; }
			public string SopInstanceUid { get; private set; }
		}

		// Loads annotations from local storage
		private List<IAimDocumentInstance> LoadLocalAimDocumentsForStudy(string studyInstanceUid)
		{
			var seriesIdentifier = new SeriesIdentifier { StudyInstanceUid = studyInstanceUid, Modality = AimManager.AimModality };
			var seriesEntryRequest = new GetSeriesEntriesRequest { Criteria = new SeriesEntry { Series = seriesIdentifier } };

			IList<SeriesEntry> entries = null;
			Platform.GetService<IStudyStoreQuery>(s => entries = s.GetSeriesEntries(seriesEntryRequest).SeriesEntries);

			var instanceToAimFileInfoMap = new Dictionary<string, AimFileInfo>();

			// Get all unique AE Titles for the study. Can study have more than one?
			// We only need to query each AETitle once, or there will be duplicates/errors.
			var studyAes = (from seriesEntry in entries where seriesEntry != null select seriesEntry.Series.RetrieveAE).GroupBy(ae => ae.AETitle).Select(ae1 => ae1.First()).OfType<IDicomServiceNode>().ToList();
			if (!studyAes.Any())
			{
				Platform.Log(LogLevel.Debug, "Study ({0}} has no SR (AIM Annotations) objects", studyInstanceUid);
				return null;
			}
			foreach (var studyAe in studyAes)
			{

				IStudyLoader studyLoader;
				try
				{
					studyLoader = studyAe.GetService<IStudyLoader>();
				}
				catch (Exception ex)
				{
					throw new AimManagerException("Cannot get study loader", ex);
				}

				int numberOfSops = studyLoader.Start(new StudyLoaderArgs(studyInstanceUid, null, new StudyLoaderOptions(true)));
				for (int i = 0; i < numberOfSops; i++)
				{
					using (var sop = studyLoader.LoadNextSop())
					{
						if (sop != null && sop.Modality == AimManager.AimModality)
						{
							var localSopDataSource = sop.DataSource as ILocalSopDataSource;
							if (localSopDataSource != null)
							{
								var filePathName = localSopDataSource.Filename;
								switch (AimManager.GetAimVersionFromSop(sop))
								{
									case AimVersion.AimVersion3:
										instanceToAimFileInfoMap.Add(filePathName,
																	 new AimFileInfo(AimVersion.AimVersion3, sop.StudyInstanceUid, sop.SeriesInstanceUid, sop.SopInstanceUid));
										break;
									case AimVersion.AimVersion4:
										instanceToAimFileInfoMap.Add(filePathName,
																	 new AimFileInfo(AimVersion.AimVersion4, sop.StudyInstanceUid, sop.SeriesInstanceUid, sop.SopInstanceUid));
										break;
								}
							}
						}
					}
				}
			}

			if (instanceToAimFileInfoMap.Any())
			{
				var aimDocumentInstances = new List<IAimDocumentInstance>();
				var aim4Instances = instanceToAimFileInfoMap.Where(instance => instance.Value.AimVersion == AimVersion.AimVersion4).ToList();
				if (aim4Instances.Any())
				{
					using (var dcmHelper = new Aim4.Aim4NativeDcmHelper())
					{
						foreach (var instanceInfo in aim4Instances)
						{
							var aimDocumentInstance = ReadAimDocumentFromDicomFile(dcmHelper,
																			instanceInfo.Key, instanceInfo.Value.StudyInstanceUid,
																			instanceInfo.Value.SeriesInstanceUid, instanceInfo.Value.SopInstanceUid);
							if (aimDocumentInstance != null)
								aimDocumentInstances.Add(aimDocumentInstance);
						}
					}
				}

				return aimDocumentInstances.Any() ? aimDocumentInstances : null;
			}

			return null;
		}

		// Helper. Reads an AIM document from file using a version-specific native AIM methods.
		private static IAimDocumentInstance ReadAimDocumentFromDicomFile(IAimNativeHelper aimNativeHelper, string filePathName,
																   string studyInstanceUid, string seriesInstanceUid, string sopInstanceUid)
		{
			Platform.CheckForNullReference(aimNativeHelper, "aimNativeHelper");
			Platform.CheckForEmptyString(filePathName, "filePathName");

			if (aimNativeHelper is Aim3.Aim3NativeDcmHelper)
			{
				var aim3NativeHelper = (Aim3.Aim3NativeDcmHelper)aimNativeHelper;
				var annotations = aim3NativeHelper.ReadAnnotationsFromFile(filePathName);
				if (annotations != null)
					return new Aim3.Aim3DocumentInstance(annotations, studyInstanceUid, seriesInstanceUid, sopInstanceUid);
			}
			else if (aimNativeHelper is Aim4.Aim4NativeDcmHelper)
			{
				var aim4NativeHelper = (Aim4.Aim4NativeDcmHelper)aimNativeHelper;
				var annotations = aim4NativeHelper.ReadAnnotationsFromFile(filePathName);
				if (annotations != null)
					return new Aim4.Aim4DocumentInstance(annotations, studyInstanceUid, seriesInstanceUid, sopInstanceUid);
			}
			else
			{
				Debug.Assert(false, "Unexpected type of IAimNativeHelper");
			}

			return null;
		}
	}
}
