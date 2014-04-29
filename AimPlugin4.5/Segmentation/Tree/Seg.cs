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

using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Runtime.Serialization;
using Segmentation.Graphics;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents a segmented region
    /// </summary>
    public class Seg : INotifyPropertyChanged
    {
        // Default lab color of yellow
        //private LabColor _color = new LabColor {L = 97, a = -22, b = 94};
        private Color _color = Color.FromArgb(255, 255, 0);

        // Default opacity of 35% per TASK7_SEG_RNR_002
        public static float DefaultOpacity = 0.35f;
        private float _opacity = .35f;

        private double? _pixelIntensityMean;
        private double? _pixelIntensityStandardDeviation;
        private Category _selectedCategory;
        private double? _volume;

        /// <summary>
        /// Constructor
        /// </summary>
        public Seg() : this(true, null) { }

        /// <summary>
        /// Constructor
        /// </summary>
        public Seg(bool editable, SegmentImageData segmentImageData)
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());

            Editable = editable;
            SegmentImageData = segmentImageData;
        }

        public SegmentImageData SegmentImageData { get; private set; }

        /// <summary>
        /// Gets a collection of category coded terms read from the configuration file
        /// </summary>
        public List<Category> AvailableCategories { get; internal set; }

        /// <summary>
        /// Gets or sets the category of this segmented region
        /// </summary>
        [DataMember]
        public Category SelectedCategory
        {
            get { return _selectedCategory; }
            set
            {
                if (_selectedCategory != value)
                {
                    //Type Type = null;
                    if (_selectedCategory != null)
                    {
                        //Type = _selectedCategory.SelectedType;
                        _selectedCategory.PropertyChanged -= SelectedCategoryOnPropertyChanged;
                        //_selectedCategory.SelectedType = null;
                    }
                    _selectedCategory = value;
                    if (_selectedCategory != null)
                    {
                        _selectedCategory.PropertyChanged += SelectedCategoryOnPropertyChanged;
                        //_selectedCategory.SelectedType = Type;
                        //_selectedCategory.OnPropertyChanged("SelectedType");
                    }
                    OnPropertyChanged("SelectedCategory");
                    OnPropertyChanged("Valid");
                }
            }
        }

        /// <summary>
        /// Gets or sets the segmented region's label or name
        /// </summary>
        [DataMember]
        public string Label { get; set; }

        /// <summary>
        /// Gets the name of the Seg object as displayed in the GUI and menus
        /// </summary>
        public string DisplayLabel
        {
            get
            {
                var label = "NOLABEL";
                if (Label != null)
                    label = Label.Trim();

                var contentLabel = string.Empty;
                if (DocumentContentLabel != null)
                    contentLabel = DocumentContentLabel.Trim();
                if (!string.IsNullOrEmpty(contentLabel) && contentLabel != label && !string.IsNullOrEmpty(label))
                    label = contentLabel + "." + label;
                if (!string.IsNullOrEmpty(contentLabel) && string.IsNullOrEmpty(label))
                    label = contentLabel;
                if (string.IsNullOrEmpty(label))
                    label = "NOLABEL" + NoLabelNumber;

                // Distinguish between editable ROI polygon Segs and pixel
                // image Segs that have already been created
                if (Editable)
                    label += "*";

                return label;
            }
        }

        /// <summary>
        /// Gets or sets the number used to label this Seg object when the label is otherwise empty
        /// </summary>
        public int NoLabelNumber { get; set; }

        /// <summary>
        /// Gets or sets the segmented region's description or caption
        /// </summary>
        [DataMember]
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the segmented region's number relative to the other regions
        /// </summary>
        [DataMember]
        public int SegmentationNumber { get; set; }

        /// <summary>
        /// Gets or sets the image series instance UID containing this segmented region
        /// </summary>
        [DataMember]
        public string ImageSeriesUid { get; set; }

        /// <summary>
        /// Gets or sets the parent document content label
        /// </summary>
        public string DocumentContentLabel { get; set; }

        public double? Volume
        {
            get { return _volume; }
            set
            {
                _volume = value;
                OnPropertyChanged("Volume");
            }
        }

        public double? PixelIntensityMean
        {
            get { return _pixelIntensityMean; }
            set
            {
                _pixelIntensityMean = value;
                OnPropertyChanged("PixelIntensityMean");
            }
        }

        public double? PixelIntensityStandardDeviation
        {
            get { return _pixelIntensityStandardDeviation; }
            set
            {
                _pixelIntensityStandardDeviation = value;
                OnPropertyChanged("PixelIntensityStandardDeviation");
            }
        }

        /// <summary>
        /// Gets or sets the color of the segmented region in lab values
        /// </summary>
        [DataMember]
        public Color Color
        {
            get { return _color; }
            set
            {
                _color = value;
                foreach (ISegGraphic graphic in SegGraphics)
                    graphic.Color = value;
            }
        }

        /// <summary>
        /// Gets or sets whether the Seg can be edited to create new DICOM segmentations
        /// </summary>
        public bool Editable { get; private set; }

        /// <summary>
        /// Gets or sets the opacity of the segmented regions
        /// </summary>
        [DataMember]
        public float Opacity
        {
            get { return _opacity; }

            // Use SegmentationComponent.SelectedSegOpacity
            internal set
            {
                _opacity = value;
                OnPropertyChanged("Opacity");
                foreach (SegFrameImageGraphic pixelSegGraphic in SegGraphics.OfType<SegFrameImageGraphic>())
                    pixelSegGraphic.Alpha = Opacity;
            }
        }

        public bool ShowOpacitySlider
        {
            get { return SegGraphics.Any() || !Editable; }
        }

        [DataMember]
        public ObservableCollection<PolygonalRoiSegGraphic> SegGraphics { get; private set; }

        public bool Valid
        {
            get
            {
                return Editable &&
                       SelectedCategory != null &&
                       SelectedCategory.Valid &&
                       SegGraphics.Count > 0;
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        private void SelectedCategoryOnPropertyChanged(object sender, PropertyChangedEventArgs propertyChangedEventArgs)
        {
            if (propertyChangedEventArgs.PropertyName == "Valid")
            {
                OnPropertyChanged("Valid");
            }
        }

        internal void OnCreatingSeg()
        {
            Editable = false;
            OnPropertyChanged("Editable");
            OnPropertyChanged("ShowOpacitySlider");
        }

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (SegGraphics == null)
                SegGraphics = new ObservableCollection<PolygonalRoiSegGraphic>();
            SegGraphics.CollectionChanged += RoisCollectionChanged;
        }

        private void RoisCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            var addedSegs = new List<ISegGraphic>();
            if (e.NewItems != null)
                addedSegs.AddRange(e.NewItems.Cast<ISegGraphic>());
            var removedSegs = new List<ISegGraphic>();
            OnPropertyChanged("Valid");
        }

        internal virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}