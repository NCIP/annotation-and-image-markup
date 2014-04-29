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
using System.ComponentModel;
using System.Runtime.Serialization;
using Segmentation.Graphics;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents a coded segmentation category
    /// </summary>
    [DataContract]
    [KnownType(typeof(CodedTerm))]
    [KnownType(typeof(Type))]
    [KnownType(typeof(TypeModifier))]
    [KnownType(typeof(AnatomicRegion))]
    [KnownType(typeof(AnatomicRegionModifier))]
    public class Category : CodedTerm, INotifyPropertyChanged
    {
        private Type _selectedType;
        private AnatomicRegion _selectedAnatomicRegion;

        /// <summary>
        /// Constructor
        /// </summary>
        public Category()
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        /// <summary>
        /// Gets a collection of coded types available to this category
        /// </summary>
        [DataMember]
        public List<Type> Types { get; private set; }


        [DataMember]
        public bool AnatomicRegionRequired { get; set; }

        /// <summary>
        /// Gets a collection of coded anatomic regions available to this category
        /// </summary>
        [DataMember]
        public List<AnatomicRegion> AnatomicRegions { get; private set; }

            /// <summary>
        /// Gets the selected Type 
        /// </summary>
        [DataMember]
        public Type SelectedType
        {
            get { return _selectedType; }
            set
            {
                if (_selectedType != value)
                {
                    if (_selectedType != null)
                        _selectedType.PropertyChanged -= SelectedTypeOnPropertyChanged;
                    _selectedType = value;
                    if (_selectedType != null)
                        _selectedType.PropertyChanged += SelectedTypeOnPropertyChanged;
                    OnPropertyChanged("SelectedType");
                    OnPropertyChanged("Valid");
                }
            }
        }

        private void SelectedTypeOnPropertyChanged(object sender, PropertyChangedEventArgs propertyChangedEventArgs)
        {
            if (propertyChangedEventArgs.PropertyName == "Valid")
            {
                OnPropertyChanged("Valid");
            }
        }

        /// <summary>
        /// Gets or sets the anatomic region of this segmented region
        /// </summary>
        [DataMember]
        public AnatomicRegion SelectedAnatomicRegion
        {
            get { return _selectedAnatomicRegion; }
            set
            {
                if (_selectedAnatomicRegion != value)
                {
                    if (_selectedAnatomicRegion != null)
                        _selectedAnatomicRegion.PropertyChanged -= SelectedTypeOnPropertyChanged;
                    _selectedAnatomicRegion = value;
                    if (_selectedAnatomicRegion != null)
                        _selectedAnatomicRegion.PropertyChanged += SelectedTypeOnPropertyChanged;
                    OnPropertyChanged("SelectedAnatomicRegion");
                    OnPropertyChanged("Valid");
                }
            }
        }

        public bool ShowTypes
        {
            get { return Types.Count > 0; }
        }

        public bool ShowAnatomicRegions
        {
            get { return AnatomicRegionRequired && AnatomicRegions.Count > 0; }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (Types == null)
                Types = new List<Type>();
            if (AnatomicRegions == null)
                AnatomicRegions = new List<AnatomicRegion>();
        }

        internal virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        private bool TypeValid
        {
            get
            {
                return Types == null ||
                       Types.Count == 0 ||
                       (SelectedType != null &&
                       SelectedType.Valid);
            }
        }

        private bool AnatomicRegionValid
        {
            get
            {
                return AnatomicRegions == null ||
                       AnatomicRegions.Count == 0 ||
                       (SelectedAnatomicRegion != null &&
                       SelectedAnatomicRegion.Valid);
            }
        }

        public bool Valid
        {
            get { return TypeValid && AnatomicRegionValid; }
        }
    }
}