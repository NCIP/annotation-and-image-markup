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
using System.Linq;
using System.ComponentModel;
using System.Runtime.Serialization;

namespace AIM.Annotation.TemplateTree
{
    [DataContract(Name = "CharacteristicQuantification")]
    public class AimTemplateTreeCharacteristicQuantification
    {
        public event EventHandler CharacteristicQuantificationChanged;
        public event EventHandler<StandardCodedTermsSelectedEventArgs> CharacteristicQuantificationSelected;
        public event EventHandler CharacteristicQuantificationReset;
        public event EventHandler<StatusChangedEventArgs> AimTemplateTreeStatusChanged;

        [DataMember]
        public string Name { get; private set; }

        [DataMember]
        public bool HasConfidence { get; private set; }

        private double _confidenceValue = 1;

        [DataMember]
        public double ConfidenceValue
        {
            get { return _confidenceValue; }
            set { _confidenceValue = value; }
        }

        [DataMember]
        public int CharacteristicQuantificationIndex { get; private set; }

        [DataMember]
        public List<StandardCodedTerm> NonQuantifiables { get; private set; }

        private StandardCodedTerm _selectedNonQuantifiable;

        [DataMember]
        public virtual StandardCodedTerm SelectedNonQuantifiable
        {
            get { return _selectedNonQuantifiable; }
            set
            {
                if (_selectedNonQuantifiable != value)
                {
                    _selectedNonQuantifiable = value;
                    OnCharacteristicQuantificationChanged();
                }
            }
        }

        public StandardCodedTerm DefaultNonQuantifiable
        {
            get
            {
                if (NonQuantifiables.Count > 0)
                    return NonQuantifiables.FirstOrDefault(nonQuantifiable => nonQuantifiable.DefaultAnswer);
                return null;
            }
        }

        public AimTemplateTreeCharacteristicQuantification(
            string name, 
            bool hasConfidence, 
            int characteristicQuantificationIndex, 
            List<StandardCodedTerm> nonQuantifiables)
        {
            Name = name;
            HasConfidence = hasConfidence;
            CharacteristicQuantificationIndex = characteristicQuantificationIndex;
            NonQuantifiables = nonQuantifiables;
        }

        public virtual bool Valid
        {
            get { return SelectedNonQuantifiable != null; }
        }

        protected void OnCharacteristicQuantificationChanged()
        {
            if (CharacteristicQuantificationChanged != null)
                CharacteristicQuantificationChanged(this, new EventArgs());
        }

        protected void OnCharacteristicQuenatificationSelected(IStandardCodedTerm selectedTerm)
        {
            if (CharacteristicQuantificationSelected != null)
                CharacteristicQuantificationSelected(this, new StandardCodedTermsSelectedEventArgs(
                    new BindingList<IStandardCodedTerm>{ selectedTerm },
                    new BindingList<IStandardCodedTerm>()
                    ));
        }

        protected virtual void OnAimTemplateTreeStatusChanged(object sender, StatusChangedEventArgs e)
        {
            if (AimTemplateTreeStatusChanged != null)
                AimTemplateTreeStatusChanged(sender, e);
        }

        public virtual void Reset()
        {
            ConfidenceValue = 1;

            SelectedNonQuantifiable = null;
            if (CharacteristicQuantificationReset != null)
                CharacteristicQuantificationReset(this, new EventArgs());
        }

        public virtual void Skip()
        {
            SelectedNonQuantifiable = DefaultNonQuantifiable;
        }
    }
}
