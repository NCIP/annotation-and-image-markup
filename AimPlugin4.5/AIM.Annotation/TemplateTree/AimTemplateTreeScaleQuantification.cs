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
using System.Linq;
using System.Runtime.Serialization;

namespace AIM.Annotation.TemplateTree
{
    [DataContract(Name = "ScaleQuantification")]
    public class AimTemplateTreeScaleQuantification : AimTemplateTreeCharacteristicQuantification
    {
        [DataMember]
        public Scale Scale { get; private set; }

        private ScaleLevel? _selectedScaleLevel;

        [DataMember]
        public ScaleLevel? SelectedScaleLevel
        {
            get { return _selectedScaleLevel; }
            set
            {
                if (SelectedNonQuantifiable != null && value != null)
                    SelectedNonQuantifiable = null;
                _selectedScaleLevel = value;
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
                if (SelectedScaleLevel != null && value != null)
                    SelectedScaleLevel = null;
                base.SelectedNonQuantifiable = value;
            }
        }

        public AimTemplateTreeScaleQuantification(
            Scale scale,
            string name,
            bool hasConfidence,
            int characteristicQuantificationIndex,
            List<StandardCodedTerm> nonQuantifiables) :
            base(name, hasConfidence, characteristicQuantificationIndex, nonQuantifiables)
        {
            Scale = scale;
        }

        public ScaleLevel? DefaultScaleLevel
        {
            get
            {
                if (Scale.ScaleLevels != null &&
                    Scale.ScaleLevels.Count > 0)
                {
                    var defaultLevels = Scale.ScaleLevels.Where(scaleLevel => scaleLevel.DefaultAnswer).ToList();
                    if (defaultLevels.Count > 0)
                        return defaultLevels[0];
                }

                return null;
            }
        }

        public override bool Valid
        {
            get { return SelectedScaleLevel != null || base.Valid; }
        }

        public override void Reset()
        {
            SelectedScaleLevel = null;
            base.Reset();
        }

        public override void Skip()
        {
            base.Skip();
            if (DefaultScaleLevel == null && DefaultNonQuantifiable == null)
                    OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                        "Template Error:  Missing default answer for " + Name,
                        StatusChangedEventArgs.MessageTypes.Error));

            SelectedScaleLevel = DefaultScaleLevel;
        }
    }
}
