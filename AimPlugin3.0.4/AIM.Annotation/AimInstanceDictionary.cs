#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
