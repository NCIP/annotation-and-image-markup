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
using System.Runtime.Serialization;

namespace AIM.Annotation.TemplateTree
{
    [DataContract(Name = "QuantileQuantification")]
    public class AimTemplateTreeQuantileQuantification : AimTemplateTreeCharacteristicQuantification
    {
        [DataMember]
        public Quantile Quantile { get; private set; }

        private int? _selectedBin;

        [DataMember]
        public int? SelectedBin
        {
            get { return _selectedBin; }
            set
            {
                if (_selectedBin != value)
                {
                    if (SelectedNonQuantifiable != null && value != null)
                        SelectedNonQuantifiable = null;
                    _selectedBin = value;
                    OnCharacteristicQuantificationChanged();
                    OnCharacteristicQuenatificationSelected(Quantile);
                }
            }
        }

        public override StandardCodedTerm SelectedNonQuantifiable
        {
            get
            {
                return base.SelectedNonQuantifiable;
            }
            set
            {
                if (SelectedBin != null && value != null)
                    SelectedBin = null;
                base.SelectedNonQuantifiable = value;
            }
        }

        public AimTemplateTreeQuantileQuantification(
            Quantile quantile,
            string name,
            bool hasConfidence,
            int characteristicQuantificationIndex,
            List<StandardCodedTerm> nonQuantifiables) :
            base(name, hasConfidence, characteristicQuantificationIndex, nonQuantifiables)
        {
            Quantile = quantile;
        }

        public override bool Valid
        {
            get { return SelectedBin != null || base.Valid; }
        }

        public override void Reset()
        {
            SelectedBin = null;
            base.Reset();
        }

        public override void Skip()
        {
            base.Skip();

            if (Quantile.DefaultBin == null && DefaultNonQuantifiable == null)
                OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                    "Template Error:  Missing default answer for " + Name,
                    StatusChangedEventArgs.MessageTypes.Error));

            SelectedBin = Quantile.DefaultBin;
        }
    }
}
