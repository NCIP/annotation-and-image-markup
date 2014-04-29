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
    [DataContract(Name = "ImagingObservation")]
    public sealed class AimTemplateTreeImagingObservationNode : AimTemplateTreeNode
    {
        [DataMember]
        public List<AimTemplateTreeAllowedTerm> AllowedTerms { get; private set; }

        public ReadOnlyCollection<AimTemplateTreeAllowedTerm> SelectedAllowedTerms
        {
            get
            {
                return new ReadOnlyCollection<AimTemplateTreeAllowedTerm>(
                    AllowedTerms.Where(term => term.Selected).ToList());
            }
        }

        public event EventHandler<NotifyCollectionChangedEventArgs> SelectedAllowedTermsChanged;

        [DataMember]
        public List<AimTemplateTreeImagingObservationCharacteristicNode> ImagingObservationCharacteristicTreeNodes { get; private set; }

        public ReadOnlyCollection<AimTemplateTreeImagingObservationCharacteristicNode> SelectedImagingObservationCharacteristicTreeNodes
        {
            get
            {
                return new ReadOnlyCollection<AimTemplateTreeImagingObservationCharacteristicNode>(ImagingObservationCharacteristicTreeNodes.Where(aec => aec.Valid).ToList());
            }
        }

        public override bool Valid
        {
            get
            {
                bool valid = !(SelectedAllowedTerms.Count < MinCardinality || SelectedAllowedTerms.Count > MaxCardinality);

                if (SelectedImagingObservationCharacteristicTreeNodes.Count < ImagingObservationCharacteristicTreeNodes.Count)
                    valid = false;

                return valid;
            }
        }

        public override IEnumerable<AimTemplateTreeNode> ChildNodes
        {
            get
            {
                return ImagingObservationCharacteristicTreeNodes.Cast<AimTemplateTreeNode>().OrderBy<AimTemplateTreeNode, int>(node => node.ItemNumber);
            }
        }

        public AimTemplateTreeImagingObservationNode(
            string label,
            int itemNumber,
            string explanatoryText,
            int minCardinality,
            int maxCardinality,
            bool shouldDisplay,
            string groupLabel,
            StandardValidTerm questionType,
            bool hasConfidence,
            List<AimTemplateTreeAllowedTerm> allowedTerms,
            List<AimTemplateTreeImagingObservationCharacteristicNode> imagingObservationCharacteristicTreeNodes,
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
            HasConfidence = hasConfidence;
            AllowedTerms = allowedTerms;
            ImagingObservationCharacteristicTreeNodes = imagingObservationCharacteristicTreeNodes;

            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            foreach (var term in AllowedTerms)
                term.SelectedChanged += TermSelectedChanged;

            foreach (var characteristic in ImagingObservationCharacteristicTreeNodes)
            {
                characteristic.AimTemplateTreeNodeValueChanged += OnAimTemplateTreeNodeValueChanged;
                characteristic.AimTemplateTreeNodeValueSelected += OnAimTemplateTreeNodeValueSelected;
                characteristic.AimTemplateTreeStatusChanged += OnAimTemplateTreeStatusChanged;
            }

            if (MaxCardinality == 1 && MinCardinality == 1 && AllowedTerms.Count == 1)
                AllowedTerms[0].Selected = true;

            if (!ShouldDisplay && DefaultAnswers != null && DefaultAnswers.Count > 0)
                foreach (var defaultAnswer in DefaultAnswers)
                    defaultAnswer.Selected = true;
        }

        void TermSelectedChanged(object sender, EventArgs e)
        {
            var term = sender as AimTemplateTreeAllowedTerm;
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

        public List<AimTemplateTreeAllowedTerm> DefaultAnswers
        {
            get
            {
                if (AllowedTerms.Count > 0)
                    return AllowedTerms.Where(term => term.DefaultAnswer).ToList();
                return null;
            }
        }

        public void ClearSelectedAllowedTerms()
        {
            foreach (var term in AllowedTerms)
                if (term.Selected)
                    term.Selected = false;
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
                    answer.Selected = true;
            }
            else
            {
                if (MinCardinality > 0)
                    OnAimTemplateTreeStatusChanged(this, new StatusChangedEventArgs(
                        "Template Error:  Missing default answer for " + Label,
                        StatusChangedEventArgs.MessageTypes.Error));
            }
        }

        public override void Reset()
        {
            ClearSelectedAllowedTerms();
            foreach (var characteristic in ImagingObservationCharacteristicTreeNodes)
                characteristic.Reset();

            if (MaxCardinality == 1 && MinCardinality == 1 && AllowedTerms.Count == 1)
                AllowedTerms[0].Selected = true;


            if (!ShouldDisplay && DefaultAnswers != null && DefaultAnswers.Count > 0)
                foreach (var defaultAnswer in DefaultAnswers)
                    defaultAnswer.Selected = true;

            base.Reset();
        }
    }
}
