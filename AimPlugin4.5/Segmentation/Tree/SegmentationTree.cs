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
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using Segmentation.Graphics;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents segmentations objects stored on the study level, which may
    /// be contained in one or more documents
    /// </summary>
    [DataContract]
    [KnownType(typeof (SegmentationDocument))]
    [KnownType(typeof (Seg))]
    [KnownType(typeof (CodedTerm))]
    [KnownType(typeof (Category))]
    [KnownType(typeof (Type))]
    [KnownType(typeof (TypeModifier))]
    [KnownType(typeof (AnatomicRegion))]
    [KnownType(typeof (AnatomicRegionModifier))]
    [KnownType(typeof (LabColor))]
    [KnownType(typeof (UserInfo))]
    [KnownType(typeof (ISegGraphic))]
    [KnownType(typeof (PolygonalRoiSegGraphic))]
    public class SegmentationTree : INotifyPropertyChanged
    {
        private Seg _selectedSeg;

        /// <summary>
        /// Constructor
        /// </summary>
        public SegmentationTree()
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        /// <summary>
        /// A collection of segmentation documents
        /// </summary>
        [DataMember]
        public ObservableCollection<SegmentationDocument> SegmentationDocuments { get; private set; }

        /// <summary>
        /// Gets a list of newly created segs from all segmentation documents available for 
        /// DICOM segmentation creation.
        /// (Usually the segs from the working segmentation document of the current study)
        /// </summary>
        public List<Seg> AllNewSegs
        {
            get
            {
                var segs = new List<Seg>();
                foreach (var segmentationDocument in SegmentationDocuments)
                    if (!segmentationDocument.Saved)
                        segs.AddRange(segmentationDocument.Segs);
                return segs;
            }
        }

        /// <summary>
        /// Gets a list of all segs from all segmentation documents in the tree
        /// </summary>
        public List<Seg> AllSegs
        {
            get
            {
                var segs = new List<Seg>();
                foreach (var segmentationDocument in SegmentationDocuments)
                    segs.AddRange(segmentationDocument.Segs);
                return segs;
            }
        }

        /// <summary>
        /// Gets or sets the study instance UID representing the study this segmentation container belongs to
        /// </summary>
        [DataMember]
        public string StudyInstanceUid { get; set; }

        /// <summary>
        /// Get or sets the study description representing the study this segmentation container belongs to
        /// </summary>
        [DataMember]
        public string StudyDescription { get; set; }

        /// <summary>
        /// Gets or sets the study ID representing the study this segmentation container belongs to
        /// </summary>
        [DataMember]
        public string StudyId { get; set; }

        public Seg SelectedSeg
        {
            get { return _selectedSeg; }
            set
            {
                if (_selectedSeg != value)
                {
                    if (_selectedSeg != null)
                        _selectedSeg.PropertyChanged -= SelectedSegOnPropertyChanged;
                    _selectedSeg = value;
                    if (_selectedSeg != null)
                        _selectedSeg.PropertyChanged += SelectedSegOnPropertyChanged;

                    OnPropertyChanged("SelectedSeg");
                    OnPropertyChanged("AllNewSegs");
                }
            }
        }

        internal void OnCreatingSeg()
        {
            _selectedSeg.OnCreatingSeg();
            // Refreshes seg name in WPF control
            var selectedSeg = SelectedSeg;
            SelectedSeg = null;
            OnPropertyChanged("SelectedSeg");
            SelectedSeg = selectedSeg;
            OnPropertyChanged("SelectedSeg");
        }

        private void SelectedSegOnPropertyChanged(object sender, PropertyChangedEventArgs propertyChangedEventArgs)
        {
            if (propertyChangedEventArgs.PropertyName == "Editable")
            {
                OnPropertyChanged("SelectedSeg");
            }
        }

        public SegmentationDocument WorkingSegmentationDocument { get; set; }

        public SegmentationDocument SelectedSegmentationDocument
        {
            get
            {
                if (_selectedSeg != null)
                    return SegmentationDocuments.FirstOrDefault(segmentation => segmentation.Segs.Contains(SelectedSeg));
                return null;
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (SegmentationDocuments == null)
                SegmentationDocuments = new ObservableCollection<SegmentationDocument>();
            SegmentationDocuments.CollectionChanged += DocumentSegmentationsCollectionChanged;
        }

        private void DocumentSegmentationsCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            var addedSegmentations = new List<SegmentationDocument>();
            if (e.NewItems != null)
                addedSegmentations.AddRange(e.NewItems.Cast<SegmentationDocument>());
            var removedSegmentations = new List<SegmentationDocument>();
            if (e.OldItems != null)
                removedSegmentations.AddRange(e.OldItems.Cast<SegmentationDocument>());

            foreach (SegmentationDocument segmentation in addedSegmentations)
            {
                if (segmentation != null)
                {
                    segmentation.Segs.CollectionChanged += SegsOnCollectionChanged;
                }
            }
            foreach (SegmentationDocument segmentation in removedSegmentations)
            {
                if (segmentation != null)
                {
                    segmentation.Segs.CollectionChanged -= SegsOnCollectionChanged;
                }
            }

            if (addedSegmentations.Count > 0 || removedSegmentations.Count > 0)
            {
                OnPropertyChanged("AllNewSegs");
                OnPropertyChanged("AllSegs");
            }
        }

        private void SegsOnCollectionChanged(object sender, NotifyCollectionChangedEventArgs notifyCollectionChangedEventArgs)
        {
            OnPropertyChanged("AllNewSegs");
            OnPropertyChanged("AllSegs");
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}