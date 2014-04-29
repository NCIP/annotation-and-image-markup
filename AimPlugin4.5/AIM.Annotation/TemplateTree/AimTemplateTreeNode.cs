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
    [DataContract]
    public abstract class AimTemplateTreeNode
    {
        private double _confidenceValue = 1;
        private string _explanatoryText;

        protected AimTemplateTreeNode(
            string label,
            int itemNumber,
            string explanatoryText,
            int minCardinality,
            int maxCardinality,
            bool shouldDisplay,
            string groupLabel,
            StandardValidTerm questionType,
            string id)
        {
            Label = label;
            ItemNumber = itemNumber;
            ExplanatoryText = explanatoryText;
            MinCardinality = minCardinality;
            MaxCardinality = maxCardinality;
            ShouldDisplay = shouldDisplay;
            GroupLabel = groupLabel;
            QuestionType = questionType;
            NodeId = id;
        }

        [DataMember]
        public string NodeId { get; private set; }

        [DataMember]
        public string Label { get; private set; }

        [DataMember]
        public int ItemNumber { get; private set; }

        [DataMember]
        public string ExplanatoryText
        {
            get { return string.IsNullOrEmpty(_explanatoryText) ? null : _explanatoryText; }
            private set { _explanatoryText = value; }
        }

        [DataMember]
        public int MinCardinality { get; private set; }

        [DataMember]
        public int MaxCardinality { get; private set; }

        [DataMember]
        public bool ShouldDisplay { get; private set; }

        [DataMember]
        public string GroupLabel { get; private set; }

        [DataMember]
        public virtual bool HasConfidence { get; protected set; }

        [DataMember]
        public double ConfidenceValue
        {
            get { return _confidenceValue; }
            set { _confidenceValue = value; }
        }

        [DataMember]
        public StandardValidTerm QuestionType { get; private set; }

        public virtual bool Valid
        {
            get { return true; }
        }

        [DataMember]
        private int SkipCounter { get; set; }

        public virtual bool Skipped
        {
            get { return SkipCounter > 0; }
        }

        public abstract IEnumerable<AimTemplateTreeNode> ChildNodes { get; }

        public event EventHandler SkippedChanged;
        public event EventHandler NodeReset;

        public event EventHandler AimTemplateTreeNodeValueChanged;
        public event EventHandler<StandardCodedTermsSelectedEventArgs> AimTemplateTreeNodeValueSelected;
        public event EventHandler<StatusChangedEventArgs> AimTemplateTreeStatusChanged;

        protected void OnAimTemplateTreeNodeValueChanged(object sender, EventArgs e)
        {
            if (AimTemplateTreeNodeValueChanged != null)
                AimTemplateTreeNodeValueChanged(sender, e);
        }

        protected virtual void OnAimTemplateTreeNodeValueSelected(object sender, StandardCodedTermsSelectedEventArgs e)
        {
            if (AimTemplateTreeNodeValueSelected != null)
                AimTemplateTreeNodeValueSelected(sender, e);
        }

        protected virtual void OnAimTemplateTreeStatusChanged(object sender, StatusChangedEventArgs e)
        {
            if (AimTemplateTreeStatusChanged != null)
                AimTemplateTreeStatusChanged(sender, e);
        }

        public virtual void Skip()
        {
            SkipCounter++;
            if (SkippedChanged != null)
                SkippedChanged(this, new EventArgs());
        }

        public virtual void Unskip()
        {
            SkipCounter--;
            if (SkipCounter < 0)
                SkipCounter = 0;
            if (SkippedChanged != null)
                SkippedChanged(this, new EventArgs());
        }


        public virtual void Reset()
        {
            ConfidenceValue = 1;

            if (NodeReset != null)
                NodeReset(this, new EventArgs());
        }
    }
}
