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

namespace AIM.Annotation.TemplateTree
{
    [DataContract(Name = "ImagingObservationCharacteristic")]
    public sealed class AimTemplateTreeImagingObservationCharacteristicNode : AimTemplateTreeNode
    {
        [DataMember]
        public List<CharacteristicQuantificationAllowedTerm> CharacteristicQuantificationAllowedTerms { get; private set; }

        public ReadOnlyCollection<CharacteristicQuantificationAllowedTerm> SelectedCharacteristicQuantificationAllowedTerms
        {
            get
            {
                return new ReadOnlyCollection<CharacteristicQuantificationAllowedTerm>(
                    CharacteristicQuantificationAllowedTerms.Where(term => term.Selected).ToList());
            }
        }

        public event EventHandler<NotifyCollectionChangedEventArgs> SelectedAllowedTermsChanged;

        public override bool Valid
        {
            get
            {
                bool valid = true;
                foreach (var term in SelectedCharacteristicQuantificationAllowedTerms)
                    foreach (var quantification in term.CharacteristicQuantifications)
                        if (!quantification.Valid)
                            valid = false;
                if (SelectedCharacteristicQuantificationAllowedTerms.Count < MinCardinality ||
                    SelectedCharacteristicQuantificationAllowedTerms.Count > MaxCardinality)
                    valid = false;
                return valid;
            }
        }

        public override IEnumerable<AimTemplateTreeNode> ChildNodes { get { return null; } }

        public AimTemplateTreeImagingObservationCharacteristicNode(
            string label,
            int itemNumber,
            string explanatoryText,
            int minCardinality,
            int maxCardinality,
            bool shouldDisplay,
            string groupLabel,
            StandardValidTerm questionType,
            bool hasConfidence,
            List<CharacteristicQuantificationAllowedTerm> characteristicQuantificationAllowedTerms,
            string id) :
            base(
                label,
                itemNumber,
                explanatoryText,
                minCardinality,
                maxCardinality,
                shouldDisplay,
                groupLabel,
                questionType,
                id)
        {
            CharacteristicQuantificationAllowedTerms = characteristicQuantificationAllowedTerms;
            HasConfidence = hasConfidence;

            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            foreach (var term in CharacteristicQuantificationAllowedTerms)
                term.SelectedChanged += TermSelectedChanged;

            foreach (var term in CharacteristicQuantificationAllowedTerms)
                foreach (var quantification in term.CharacteristicQuantifications)
                {
                    quantification.CharacteristicQuantificationChanged += OnAimTemplateTreeNodeValueChanged;
                    quantification.CharacteristicQuantificationSelected += OnAimTemplateTreeNodeValueSelected;
                    quantification.AimTemplateTreeStatusChanged += OnAimTemplateTreeStatusChanged;
                }

            if (MaxCardinality == 1 && MinCardinality == 1 && CharacteristicQuantificationAllowedTerms.Count == 1)
                CharacteristicQuantificationAllowedTerms[0].Selected = true;

            if (!ShouldDisplay && DefaultAnswers != null && DefaultAnswers.Count > 0)
                Skip();
        }

        protected override void OnAimTemplateTreeNodeValueSelected(object sender, StandardCodedTermsSelectedEventArgs e)
        {
            base.OnAimTemplateTreeNodeValueSelected(this, e);
        }

        void TermSelectedChanged(object sender, EventArgs e)
        {
            var term = sender as CharacteristicQuantificationAllowedTerm;
            if (term != null)
            {
                var addedTerms = new List<IStandardCodedTerm>();
                var removedTerms = new List<IStandardCodedTerm>();
                var action = NotifyCollectionChangedAction.Add;
                if (term.Selected)
                    addedTerms.Add(term);
                else if (!term.Selected)
                {
                    removedTerms.Add(term);
                    action = NotifyCollectionChangedAction.Remove;
                }

                if (SelectedAllowedTermsChanged != null)
                    SelectedAllowedTermsChanged(this, new NotifyCollectionChangedEventArgs(action, term));
                OnAimTemplateTreeNodeValueSelected(this, new StandardCodedTermsSelectedEventArgs(addedTerms, removedTerms));
                OnAimTemplateTreeNodeValueChanged(this, new EventArgs());
            }
        }

        public List<CharacteristicQuantificationAllowedTerm> DefaultAnswers
        {
            get
            {
                if (CharacteristicQuantificationAllowedTerms.Count > 0)
                    return CharacteristicQuantificationAllowedTerms.Where(term => term.DefaultAnswer).ToList();
                return null;
            }
        }

        public override void Skip()
        {
            base.Skip();

            if (DefaultAnswers != null && DefaultAnswers.Count > 0)
            {
                if (MinCardinality > DefaultAnswers.Count)
                    OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                        "Template Error:  Missing default answer for " + Label,
                        StatusChangedEventArgs.MessageTypes.Error));

                ClearSelectedAllowedTerms();

                foreach (var answer in DefaultAnswers)
                {
                    answer.Selected = true;
                    answer.Skip();
                }
            }
            else
            {
                if (MinCardinality > 0)
                    OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                        "Template Error:  Missing default answer for " + Label,
                        StatusChangedEventArgs.MessageTypes.Error));
            }
        }

        public void ClearSelectedAllowedTerms()
        {
            foreach (var term in CharacteristicQuantificationAllowedTerms)
                if (term.Selected)
                    term.Selected = false;
        }

        public override void Reset()
        {
            ClearSelectedAllowedTerms();
            foreach (var term in CharacteristicQuantificationAllowedTerms)
                foreach (var quantification in term.CharacteristicQuantifications)
                    quantification.Reset();

            if (MaxCardinality == 1 && MinCardinality == 1 && CharacteristicQuantificationAllowedTerms.Count == 1)
                CharacteristicQuantificationAllowedTerms[0].Selected = true;

            if (!ShouldDisplay && DefaultAnswers != null && DefaultAnswers.Count > 0)
                Skip();

            base.Reset();
        }
    }
}
