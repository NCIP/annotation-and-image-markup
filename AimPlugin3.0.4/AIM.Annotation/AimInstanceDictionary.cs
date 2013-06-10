#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

using ClearCanvas.Dicom.DataStore;

namespace AIM.Annotation
{
    internal class AimSopInstanceInformation
    {
        private readonly string _studyInstanceUID;
        private readonly string _seriesInstanceUID;
        private readonly string _sopInstanceUID;
        private readonly string _instanceFileName;

        public AimSopInstanceInformation(string studyInstanceUID, string seriesInstanceUID, string sopInstanceUID, string instanceFileName)
        {
            _studyInstanceUID = studyInstanceUID;
            _seriesInstanceUID = seriesInstanceUID;
            _sopInstanceUID = sopInstanceUID;
            _instanceFileName = instanceFileName;
        }

        public string StudyInstanceUID
        {
            get { return _studyInstanceUID; }
        }

        public string SeriesInstanceUID
        {
            get { return _seriesInstanceUID; }
        }

        public string SOPInstanceUID
        {
            get { return _sopInstanceUID; }
        }

        public string InstanceFileName
        {
            get { return _instanceFileName; }
        }
    }

    /// <summary>
    /// Contains mapping information for available Annotation instances
    /// </summary>
    internal class AimInstanceDictionary : IEnumerable<ISopInstance>
    {
        // Dictionary:
        // Study Instance UID -> Series Instance UID -> SOP Istance UID -> SOP Instance File Path Name
        private readonly Dictionary<string, Dictionary<string, Dictionary<string, string>>> _studyDictionary;

        public AimInstanceDictionary()
        {
            _studyDictionary = new Dictionary<string, Dictionary<string, Dictionary<string, string>>>();
        }

        public void Add(string studyInstanceUID, string seriesInstanceUID, string sopInstanceUID, string instanceFileName)
        {
            if (studyInstanceUID == null || seriesInstanceUID == null || sopInstanceUID == null || instanceFileName == null)
                return;

            if (ContainsStudy(studyInstanceUID))
            {
                if (_studyDictionary[studyInstanceUID].ContainsKey(seriesInstanceUID))
                {
                    if (_studyDictionary[studyInstanceUID][seriesInstanceUID].ContainsKey(sopInstanceUID))
                    {
                        Debug.Assert(false, "Given annotation instance has been previously recorded: " + sopInstanceUID);
                        return;
                    }
                }
                else
                    _studyDictionary[studyInstanceUID].Add(seriesInstanceUID, new Dictionary<string, string>());
            }
            else
            {
                _studyDictionary.Add(studyInstanceUID, new Dictionary<string, Dictionary<string, string>>());
                _studyDictionary[studyInstanceUID].Add(seriesInstanceUID, new Dictionary<string, string>());
            }

            _studyDictionary[studyInstanceUID][seriesInstanceUID].Add(sopInstanceUID, instanceFileName);
        }

        public void Remove(string studyInstanceUID, string seriesInstanceUID, string sopInstanceUID)
        {
            if (studyInstanceUID == null || seriesInstanceUID == null || sopInstanceUID == null)
                return;

            if (ContainsInstance(studyInstanceUID, seriesInstanceUID, sopInstanceUID))
            {
                _studyDictionary[studyInstanceUID][seriesInstanceUID].Remove(sopInstanceUID);
                if (_studyDictionary[studyInstanceUID][seriesInstanceUID].Count == 0)
                    _studyDictionary[studyInstanceUID].Remove(seriesInstanceUID);
                if (_studyDictionary[studyInstanceUID].Count == 0)
                    _studyDictionary.Remove(studyInstanceUID);
            }
        }

        public void Clear()
        {
            foreach (var studyInfo in _studyDictionary.Values)
            {
                foreach (var seriesInfo in studyInfo.Values)
                {
                    seriesInfo.Clear();
                }
                studyInfo.Clear();
            }
            _studyDictionary.Clear();
        }

        public bool ContainsStudy(string studyInstanceUID)
        {
            if (studyInstanceUID == null)
                return false;

            return _studyDictionary.ContainsKey(studyInstanceUID);
        }

        public bool ContainsSeries(string studyInstanceUID, string seriesInstanceUID)
        {
            if (seriesInstanceUID == null)
                return false;

            return ContainsStudy(studyInstanceUID) && _studyDictionary[studyInstanceUID].ContainsKey(seriesInstanceUID);
        }

        public bool ContainsInstance(string studyInstanceUID, string seriesInstanceUID, string sopInstanceUID)
        {
            if (sopInstanceUID == null)
                return false;

            return ContainsSeries(studyInstanceUID, seriesInstanceUID) && _studyDictionary[studyInstanceUID][seriesInstanceUID].ContainsKey(sopInstanceUID);
        }

        public int Count()
        {
            var count = 0;
            foreach(var studyInstanceInfo in _studyDictionary.Values)
            {
                Debug.Assert(studyInstanceInfo != null);
                foreach (var seriesInfo in studyInstanceInfo.Values)
                {
                    Debug.Assert(seriesInfo != null);
                    count += seriesInfo.Count;
                }
            }
            return count;
        }

        public string SopInstanceFileName(string studyInstanceUID, string seriesInstanceUID, string sopInstanceUID)
        {
            return ContainsInstance(studyInstanceUID, seriesInstanceUID, sopInstanceUID) ? _studyDictionary[studyInstanceUID][seriesInstanceUID][sopInstanceUID] : null;
        }

        IEnumerator<ISopInstance> IEnumerable<ISopInstance>.GetEnumerator()
        {
            using (var reader = DataAccessLayer.GetIDataStoreReader())
            {
                foreach(var studyUID in _studyDictionary.Keys)
                {
                    var studyInfo = _studyDictionary[studyUID];
                    Debug.Assert(studyInfo != null);
                    foreach (var seriesInstanceUID in studyInfo.Keys)
                    {
                        var seriesInfo = studyInfo[seriesInstanceUID];
                        Debug.Assert(seriesInfo != null);
                        foreach (var sopInstanceUID in seriesInfo.Keys)
                        {
                            foreach (var sopInstance in reader.GetStudy(studyUID).GetSopInstances())
                            {
                                if (sopInstance.SopInstanceUid != sopInstanceUID)
                                    continue;
                                yield return sopInstance;
                                break;
                            }
                        }
                    }
                }
            }
        }

        public IEnumerator GetEnumerator()
        {
            return ((IEnumerable<ISopInstance>) this).GetEnumerator();
        }

        public List<AimSopInstanceInformation> this[string studyInstanceUID]
        {
            get
            {
                List<AimSopInstanceInformation> sopInstanceList = null;
                if (ContainsStudy(studyInstanceUID))
                {
                    sopInstanceList = new List<AimSopInstanceInformation>();
                    foreach (var seriesInstanceUID in _studyDictionary[studyInstanceUID].Keys)
                    {
                        foreach (var sopInstanceUID in _studyDictionary[studyInstanceUID][seriesInstanceUID].Keys)
                            sopInstanceList.Add(
                                new AimSopInstanceInformation(studyInstanceUID, seriesInstanceUID, sopInstanceUID,
                                                              _studyDictionary[studyInstanceUID][seriesInstanceUID][sopInstanceUID]));
                    }
                }

                return sopInstanceList;
            }
        }
    }
}
