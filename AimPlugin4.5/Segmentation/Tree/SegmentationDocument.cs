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
using System.Linq;
using System.Runtime.Serialization;
using Segmentation.DICOM;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents segmentation objects stored on the document level
    /// </summary>
    public class SegmentationDocument
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public SegmentationDocument() : this(null)
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        public SegmentationDocument(SegmentationDocumentIod segmentationDocumentIod)
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());

            SegmentationDocumentIod = segmentationDocumentIod;
        }

        /// <summary>
        /// Gets or sets SegmentationDocumentIod object that this document represents.
        /// This value is null for unsaved documents
        /// </summary>
        public SegmentationDocumentIod SegmentationDocumentIod { get; private set; }

        /// <summary>
        /// Gets or sets the SOP Instance UID of the segmentation document
        /// </summary>
        [DataMember]
        public string SopInstanceUid { get; set; }

        /// <summary>
        /// Gets or sets the content label
        /// </summary>
        [DataMember]
        public string ContentLabel { get; set; }

        /// <summary>
        /// Gets or sets the UID of the image series that contains this segmentation document
        /// </summary>
        [DataMember]
        public string SeriesInstanceUid { get; set; }

        /// <summary>
        /// Gets or sets the description of the image series that contains 
        /// this segmentation document
        /// </summary>
        [DataMember]
        public string SeriesDescription { get; set; }

        /// <summary>
        /// Gets or sets the image series number of this segmentation document
        /// </summary>
        [DataMember]
        public int SeriesNumber { get; set; }

        /// <summary>
        /// Gets a collection of objects representing individually segmented regions
        /// </summary>
        [DataMember]
        public ObservableCollection<Seg> Segs { get; private set; }

            /// <summary>
        /// Gets or sets the date and time of when this segmentation document was created
        /// </summary>
        [DataMember]
        public DateTime CreationDateTime { get; set; }

        /// <summary>
        /// Gets or sets the segmentation UID of the segmentation object from which this
        /// segmentation was created
        /// </summary>
        [DataMember]
        public string PreviousSegmentationUid { get; set; }

        /// <summary>
        /// Gets or sets the name and login of the user that created the segmentation
        /// </summary>
        [DataMember]
        public UserInfo UserInfo { get; set; }

        /// <summary>
        /// Gets whether this segmentation document has been saved
        /// </summary>
        public bool Saved
        {
            get { return !String.IsNullOrEmpty(SeriesInstanceUid); }
        }

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (Segs == null)
                Segs = new ObservableCollection<Seg>();
            Segs.CollectionChanged += SegsCollectionChanged;
        }

        /// <summary>
        /// Gets or sets the count used to keep track of the number of unlabeled Seg objects
        /// </summary>
        private int NoLabelCounter { get; set; }

        private void SegsCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            var addedSegs = new List<Seg>();
            if (e.NewItems != null)
                addedSegs.AddRange(e.NewItems.Cast<Seg>());
            var removedSegs = new List<Seg>(); 
            if (e.OldItems != null)
                removedSegs.AddRange(e.OldItems.Cast<Seg>());

            foreach (var seg in addedSegs)
            {
                seg.DocumentContentLabel = ContentLabel;

                if (String.IsNullOrEmpty(seg.Label.Trim()))
                {
                    if (seg.NoLabelNumber == 0)
                    {
                        NoLabelCounter++;
                        seg.NoLabelNumber = NoLabelCounter;
                    }

                }
            }
        }
    }
}
