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
using System.Runtime.Serialization;

namespace AIM.Annotation.TemplateTree
{
    [DataContract(Name = "NumericalQuantification")]
    public class AimTemplateTreeNumericalQuantification : AimTemplateTreeCharacteristicQuantification
    {
        [DataMember]
        public List<Numerical> Numericals { get; private set; }

        private Numerical? _selectedNumerical;

        [DataMember]
        public Numerical? SelectedNumerical
        {
            get { return _selectedNumerical; }
            set
            {
                if (SelectedNonQuantifiable != null && value != null)
                    SelectedNonQuantifiable = null;
                _selectedNumerical = value;
                OnCharacteristicQuantificationChanged();
                if (value != null)
                    OnCharacteristicQuenatificationSelected(value);
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
                if (SelectedNumerical != null && value != null)
                    SelectedNumerical = null;
                base.SelectedNonQuantifiable = value;
            }
        }

        public Numerical? DefaultNumerical
        {
            get
            {
                if (Numericals.Count > 0)
                {
                    var defaultNumericals = Numericals.Where(numerical => numerical.DefaultAnswer).ToList();
                    if (defaultNumericals.Count > 0)
                        return defaultNumericals[0];
                }

                return null;
            }
        }

        public AimTemplateTreeNumericalQuantification(
            List<Numerical> numericals,
            string name,
            bool hasConfidence,
            int characteristicQuantificationIndex,
            List<StandardCodedTerm> nonQuantifiables) :
            base(name, hasConfidence, characteristicQuantificationIndex, nonQuantifiables)
        {
            Numericals = numericals;
        }

        public override bool Valid
        {
            get { return SelectedNumerical != null || base.Valid; }
        }

        public override void Reset()
        {
            SelectedNumerical = null;
            base.Reset();
        }

        public override void Skip()
        {
            base.Skip();
            if (DefaultNumerical == null && DefaultNonQuantifiable == null)
                OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                    "Template Error:  Missing default answer for " + Name,
                    StatusChangedEventArgs.MessageTypes.Error));

            SelectedNumerical = DefaultNumerical;
        }
    }
}
