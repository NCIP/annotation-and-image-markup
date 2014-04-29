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
using System.ComponentModel;
using System.Runtime.Serialization;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents the coded type of a segmentation category
    /// </summary>
    [DataContract]
    [KnownType(typeof(CodedTerm))]
    [KnownType(typeof(TypeModifier))]
    public class Type : CodedTerm, INotifyPropertyChanged
    {
        private TypeModifier _selectedTypeModifier;

        /// <summary>
        /// Constructor
        /// </summary>
        public Type()
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        /// <summary>
        /// Gets a collection of coded type modifiers
        /// </summary>
        [DataMember]
        public List<TypeModifier> TypeModifiers { get; private set; }

        /// <summary>
        /// Gets the selected type modifier
        /// </summary>
        [DataMember]
        public TypeModifier SelectedTypeModifier
        {
            get { return _selectedTypeModifier; }
            set
            {
                if (_selectedTypeModifier != value)
                {
                    _selectedTypeModifier = value;
                    OnPropertyChanged("SelectedAnatomicRegionModifier");
                    OnPropertyChanged("Valid");
                }
            }
        }

        public bool ShowModifiers
        {
            get { return TypeModifiers.Count > 0; }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (TypeModifiers == null)
                TypeModifiers = new List<TypeModifier>();
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public bool Valid
        {
            get
            {
                return TypeModifiers == null ||
                       TypeModifiers.Count == 0 ||
                       SelectedTypeModifier != null;
            }
        }
    }
}