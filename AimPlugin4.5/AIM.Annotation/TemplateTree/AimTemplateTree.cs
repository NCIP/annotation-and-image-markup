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
    [DataContract]
    [KnownType(typeof (AimTemplateTreeNode))]
    [KnownType(typeof (AimTemplateTreeAnatomicEntityNode))]
    [KnownType(typeof (AimTemplateTreeAnatomicEntityCharacteristicNode))]
    [KnownType(typeof (AimTemplateTreeImagingObservationNode))]
    [KnownType(typeof (AimTemplateTreeImagingObservationCharacteristicNode))]
    [KnownType(typeof (AimTemplateTreeInferenceNode))]
    [KnownType(typeof (AimTemplateTreeGeometricShapeNode))]
    [KnownType(typeof (AimTemplateTreeCalculationNode))]
    [KnownType(typeof (AimTemplateTreeValidTerm))]
    [KnownType(typeof (AimTemplateTreeIntervalQuantification))]
    [KnownType(typeof (AimTemplateTreeScaleQuantification))]
    [KnownType(typeof (AimTemplateTreeQuantileQuantification))]
    [KnownType(typeof (AimTemplateTreeNumericalQuantification))]
    [KnownType(typeof (Interval))]
    [KnownType(typeof (Scale))]
    [KnownType(typeof (ScaleLevel))]
    [KnownType(typeof (Numerical))]
    [KnownType(typeof (Quantile))]
    [KnownType(typeof (IMarkup))]
    [KnownType(typeof (MarkupRectangle))]
    [KnownType(typeof (MarkupEllipse))]
    [KnownType(typeof (MarkupPolygonal))]
    [KnownType(typeof (MarkupProtractor))]
    [KnownType(typeof (MarkupPoint))]
    [KnownType(typeof (MarkupLinear))]
    [KnownType(typeof (AimTemplateTreeGeometricShapeNode.GeometricShapes))]
    [KnownType(typeof (ScaleType))]
    public class AimTemplateTree
    {
        private readonly string _aimTemplateTreeVersion = "1.0";

        private string _selectedTemplateContainerUid;

        private string _selectedTemplateUid;

        public AimTemplateTree()
        {
            // Because the constructor isn't called during deserialization
            Initialize(new StreamingContext());
        }

        public string AimTemplateTreeVersion
        {
            get { return _aimTemplateTreeVersion; }
        }

        [DataMember]
        public string SelectedTemplateContainerUid
        {
            get { return _selectedTemplateContainerUid; }
            internal set
            {
                if (_selectedTemplateContainerUid != value)
                {
                    _selectedTemplateContainerUid = value;
                    if (SelectedTemplateContainerUidChanged != null)
                        SelectedTemplateContainerUidChanged(this, new EventArgs());
                }
            }
        }

        [DataMember]
        public string SelectedTemplateUid
        {
            get { return _selectedTemplateUid; }
            set
            {
                if (_selectedTemplateUid != value)
                {
                    _selectedTemplateUid = value;
                    if (SelectedTemplateUidChanged != null)
                        SelectedTemplateUidChanged(this, new EventArgs());
                }
            }
        }

        [DataMember]
        public ObservableCollection<AimTemplateTreeNode> TemplateNodes { get; set; }

        [DataMember]
        public DateTime CreationDate { get; set; }

        [DataMember]
        public string TemplateName { get; set; }

        [DataMember]
        public string AnnotationName { get; set; }

        [DataMember]
        public string TemplateDescription { get; set; }

        [DataMember]
        public string TemplateAuthors { get; set; }

        [DataMember]
        public UserInfo UserInfo { get; set; }

        [DataMember]
        public StandardCodeSequence StandardCodeSequence { get; set; }

        [DataMember]
        public List<IMarkup> Markup { get; private set; }

        [DataMember]
        public string PrecedentReferencedAnnotationUid { get; set; }

        [DataMember]
        public string AnnotationUid { get; set; }

        public event EventHandler SelectedTemplateContainerUidChanged;
        public event EventHandler SelectedTemplateUidChanged;
        public event EventHandler<StandardCodedTermsSelectedEventArgs> AimTemplateTreeNodeValueSelected;
        public event EventHandler AimTemplateTreeNodeValueChanged;
        public event EventHandler<StatusChangedEventArgs> AimTemplateTreeStatusChanged;

        [OnDeserialized]
        private void Initialize(StreamingContext streamingContext)
        {
            if (TemplateNodes == null)
                TemplateNodes = new ObservableCollection<AimTemplateTreeNode>();
            TemplateNodes.CollectionChanged += NodesCollectionChanged;

            if (Markup == null)
                Markup = new List<IMarkup>();

            foreach (AimTemplateTreeNode node in TemplateNodes)
            {
                node.AimTemplateTreeNodeValueSelected += OnAimTemplateTreeNodeValueSelected;
                node.AimTemplateTreeNodeValueChanged += OnAimTemplateTreeNodeValueChanged;
                node.AimTemplateTreeStatusChanged += OnAimTemplateTreeStatusChanged;
            }
        }

        private void NodesCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            var addedTerms = new List<AimTemplateTreeNode>();
            if (e.NewItems != null)
                addedTerms.AddRange(e.NewItems.Cast<AimTemplateTreeNode>());
            var removedTerms = new List<AimTemplateTreeNode>();

            foreach (AimTemplateTreeNode node in addedTerms)
            {
                if (node != null)
                {
                    node.AimTemplateTreeNodeValueSelected += OnAimTemplateTreeNodeValueSelected;
                    node.AimTemplateTreeNodeValueChanged += OnAimTemplateTreeNodeValueChanged;
                    node.AimTemplateTreeStatusChanged += OnAimTemplateTreeStatusChanged;
                }
            }
            foreach (AimTemplateTreeNode node in removedTerms)
            {
                if (node != null)
                {
                    node.AimTemplateTreeNodeValueSelected -= OnAimTemplateTreeNodeValueSelected;
                    node.AimTemplateTreeNodeValueChanged -= OnAimTemplateTreeNodeValueChanged;
                    node.AimTemplateTreeStatusChanged -= OnAimTemplateTreeStatusChanged;
                }
            }
        }

        private void OnAimTemplateTreeStatusChanged(object sender, StatusChangedEventArgs e)
        {
            if (AimTemplateTreeStatusChanged != null)
                AimTemplateTreeStatusChanged(sender, e);
        }

        private void OnAimTemplateTreeNodeValueChanged(object sender, EventArgs e)
        {
            if (AimTemplateTreeNodeValueChanged != null)
                AimTemplateTreeNodeValueChanged(sender, e);
        }

        private void OnAimTemplateTreeNodeValueSelected(object sender, StandardCodedTermsSelectedEventArgs e)
        {
            var node = sender as AimTemplateTreeNode;

            if (node != null)
            {
                if (AimTemplateTreeNodeValueSelected != null)
                    AimTemplateTreeNodeValueSelected(this,
                                                     new StandardCodedTermsSelectedEventArgs(e.AddedSelectedTerms,
                                                                                             e.RemovedSelectedTerms));

                foreach (IStandardCodedTerm allowedTerm in e.AddedSelectedTerms)
                {
                    if (allowedTerm != null)
                    {
                        if (!String.IsNullOrEmpty(allowedTerm.NextId))
                            SkipTo(node.NodeId, allowedTerm.NextId);
                        if (allowedTerm.NoMoreQuestions)
                            SkipToEnd(node.NodeId);
                    }
                }

                foreach (IStandardCodedTerm allowedTerm in e.RemovedSelectedTerms)
                {
                    if (allowedTerm != null)
                    {
                        if (!String.IsNullOrEmpty(allowedTerm.NextId))
                            UnskipTo(node.NodeId, allowedTerm.NextId);
                        if (allowedTerm.NoMoreQuestions)
                            UnskipToEnd(node.NodeId);
                    }
                }
            }
        }


        private IEnumerable<AimTemplateTreeNode> FlattenTree()
        {
            IOrderedEnumerable<AimTemplateTreeNode> sortedNodes = TemplateNodes.OrderBy(node => node.ItemNumber);
            var flattenedNodes = new List<AimTemplateTreeNode>();
            foreach (AimTemplateTreeNode node in sortedNodes)
            {
                flattenedNodes.Add(node);
                flattenedNodes.AddRange(FlattenNode(node));
            }
            return flattenedNodes;
        }

        private IEnumerable<AimTemplateTreeNode> FlattenNode(AimTemplateTreeNode node)
        {
            IEnumerable<AimTemplateTreeNode> childNodes = node.ChildNodes;
            var flattenedNodes = new List<AimTemplateTreeNode>();
            if (childNodes != null)
                foreach (AimTemplateTreeNode childNode in childNodes)
                {
                    flattenedNodes.Add(childNode);
                    flattenedNodes.AddRange(FlattenNode(childNode));
                }
            return flattenedNodes;
        }

        private void SkipTo(string startNodeId, string endNodeId)
        {
            bool started = false;
            IEnumerable<AimTemplateTreeNode> flattenedNodes = FlattenTree();
            foreach (AimTemplateTreeNode node in flattenedNodes)
            {
                if (node.NodeId == endNodeId)
                    return;

                if (started)
                {
                    node.Skip();
                }

                if (node.NodeId == startNodeId)
                    started = true;
            }
        }

        private void SkipToEnd(string startNodeId)
        {
            bool started = false;
            IEnumerable<AimTemplateTreeNode> flattenedNodes = FlattenTree();
            foreach (AimTemplateTreeNode node in flattenedNodes)
            {
                if (started)
                    node.Skip();

                if (node.NodeId == startNodeId)
                    started = true;
            }
        }

        private void UnskipTo(string startNodeId, string endNodeId)
        {
            bool started = false;
            IEnumerable<AimTemplateTreeNode> flattenedNodes = FlattenTree();
            foreach (AimTemplateTreeNode node in flattenedNodes)
            {
                if (node.NodeId == endNodeId)
                    return;

                if (started)
                {
                    node.Unskip();
                }

                if (node.NodeId == startNodeId)
                    started = true;
            }
        }

        private void UnskipToEnd(string startNodeId)
        {
            bool started = false;
            IEnumerable<AimTemplateTreeNode> flattenedNodes = FlattenTree();
            foreach (AimTemplateTreeNode node in flattenedNodes)
            {
                if (started)
                    node.Unskip();

                if (node.NodeId == startNodeId)
                    started = true;
            }
        }

        public void Reset()
        {
            foreach (AimTemplateTreeNode node in TemplateNodes)
                node.Reset();

            AnnotationUid = null;
            PrecedentReferencedAnnotationUid = null;
            Markup.Clear();
        }

        public bool HasRequiredMarkup()
        {
            var unusedMarkup = new List<IMarkup>(Markup);

            foreach (
                AimTemplateTreeGeometricShapeNode geometricShape in
                    FlattenTree().OfType<AimTemplateTreeGeometricShapeNode>())
            {
                if (!geometricShape.Skipped)
                {
                    for (int i = 0; i < geometricShape.MinCardinality; i++)
                    {
                        switch (geometricShape.GeometricShape)
                        {
                            case AimTemplateTreeGeometricShapeNode.GeometricShapes.MultiPoint:
                                if (unusedMarkup.OfType<MarkupLinear>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupLinear>().FirstOrDefault());
                                else if (unusedMarkup.OfType<MarkupProtractor>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupProtractor>().FirstOrDefault());
                                else
                                    return false;
                                break;
                            case AimTemplateTreeGeometricShapeNode.GeometricShapes.Polyline:
                                if (unusedMarkup.OfType<MarkupRectangle>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupRectangle>().FirstOrDefault());
                                else if (unusedMarkup.OfType<MarkupPolygonal>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupPolygonal>().FirstOrDefault());
                                else
                                    return false;
                                break;
                            case AimTemplateTreeGeometricShapeNode.GeometricShapes.Circle:
                                if (unusedMarkup.OfType<MarkupEllipse>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupEllipse>().FirstOrDefault());
                                else
                                    return false;
                                break;
                            case AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipse:
                                if (unusedMarkup.OfType<MarkupEllipse>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupEllipse>().FirstOrDefault());
                                else
                                    return false;
                                break;
                            case AimTemplateTreeGeometricShapeNode.GeometricShapes.Point:
                                if (unusedMarkup.OfType<MarkupPoint>().Any())
                                    unusedMarkup.Remove(unusedMarkup.OfType<MarkupPoint>().FirstOrDefault());
                                else
                                    return false;
                                break;
                        }
                    }  
                }
            }
            return true;
        }

        public bool ValidForImageAnnotationCreation()
        {
            bool valid = HasRequiredMarkup();
            if (valid)
                foreach (AimTemplateTreeNode node in TemplateNodes)
                    if (!node.Valid)
                        valid = false;
            return valid;
        }
    }
}
