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
using System.Windows.Controls;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for TemplateWpfControl.xaml
    /// </summary>
    public partial class TemplateWpfControl : UserControl
    {
        public TemplateWpfControl(AimAnnotationComponent component, AimAnnotationComponentWpfControl parentComponentControl)
        {
            Component = component;

            NodeControls = new List<IValidTreeControl>();

            if (component.AimTemplateTree != null)
            {
                TreeNodes = new List<AimTemplateTreeNode>(component.AimTemplateTree.TemplateNodes);
                TreeNodes.Sort(new TemplateTreeNodeOrderComparer());
            }
            else
            {
                TreeNodes = new List<AimTemplateTreeNode>();
            }

            InitializeComponent();

            _stackPanel.Children.Add(new AnnotationNameWpfControl(Component));

            var groupedNodes = new List<AimTemplateTreeNode>();

            foreach (AimTemplateTreeNode treeNode in TreeNodes)
            {
                // Start or add to group label control
                if (!String.IsNullOrEmpty(treeNode.GroupLabel))
                {
                    if (groupedNodes.Count > 0 && treeNode.GroupLabel == groupedNodes[0].GroupLabel)
                        groupedNodes.Add(treeNode);
                    else
                    {
                        // Finish and add the group label control
                        if (groupedNodes.Count > 0)
                        {
                            var groupLabel = new GroupLabelWpfControl(groupedNodes)
                                                 {
                                                     Header = groupedNodes[0].GroupLabel
                                                 };
                            _stackPanel.Children.Add(groupLabel);
                            NodeControls.Add(groupLabel);
                        }

                        groupedNodes = new List<AimTemplateTreeNode> { treeNode };
                    }
                }
                else
                {
                    // Finish and add the group label control
                    if (groupedNodes.Count > 0)
                    {
                        var groupLabel = new GroupLabelWpfControl(groupedNodes)
                                             {
                                                 Header = groupedNodes[0].GroupLabel
                                             };
                        groupedNodes.Clear();
                        _stackPanel.Children.Add(groupLabel);
                        NodeControls.Add(groupLabel);
                    }

                    if (treeNode is AimTemplateTreeAnatomicEntityNode)
                    {
                        var anatomicEntityControl =
                            new AnatomicEntityWpfControl((AimTemplateTreeAnatomicEntityNode)treeNode);
                        _stackPanel.Children.Add(anatomicEntityControl);
                        NodeControls.Add(anatomicEntityControl);
                    }
                    if (treeNode is AimTemplateTreeImagingObservationNode)
                    {
                        var imagingObservationControl =
                            new ImagingObservationWpfControl((AimTemplateTreeImagingObservationNode)treeNode);
                        _stackPanel.Children.Add(imagingObservationControl);
                        NodeControls.Add(imagingObservationControl);
                    }
                    if (treeNode is AimTemplateTreeInferenceNode)
                    {
                        var inferenceControl =
                            new InferenceWpfControl((AimTemplateTreeInferenceNode)treeNode);
                        _stackPanel.Children.Add(inferenceControl);
                        NodeControls.Add(inferenceControl);
                    }
                    if (treeNode is AimTemplateTreeGeometricShapeNode)
                    {
                        var geometricShapeControl =
                            new GeometricShapeWpfControl((AimTemplateTreeGeometricShapeNode)treeNode);
                        _stackPanel.Children.Add(geometricShapeControl);
                        NodeControls.Add(geometricShapeControl);
                    }
                    if (treeNode is AimTemplateTreeCalculationNode)
                    {
                        var calculationControl =
                            new CalculationWpfControl((AimTemplateTreeCalculationNode)treeNode);
                        _stackPanel.Children.Add(calculationControl);
                        NodeControls.Add(calculationControl);
                    }
                }
            }

            // Finish and add the group label control
            if (groupedNodes.Count > 0)
            {
                var groupLabel = new GroupLabelWpfControl(groupedNodes)
                                     {
                                         Header = groupedNodes[0].GroupLabel
                                     };
                _stackPanel.Children.Add(groupLabel);
                NodeControls.Add(groupLabel);
            }
        }

        public AimAnnotationComponent Component { get; private set; }

        public List<AimTemplateTreeNode> TreeNodes { get; private set; }

        private List<IValidTreeControl> NodeControls { get; set; }


        public IValidTreeControl FindInvalidControl()
        {
            IValidTreeControl invalidControl = null;
            foreach (IValidTreeControl node in NodeControls)
            {
                invalidControl = FindInvalidControl(node);
                if (invalidControl != null)
                    break;
            }
            return invalidControl;
        }

        internal ControlMarkupCount FindControlWithMissingMarkup()
        {
            ControlMarkupCount missingMarkupControl = null;
            _unusedMarkup = new List<IMarkup>(Component.AimTemplateTree.Markup);

            foreach (var node in NodeControls)
            {
                missingMarkupControl = FindControlWithMissingMarkup(node);
                if (missingMarkupControl != null)
                    break;
            }
            return missingMarkupControl;
        }

        private List<IMarkup> _unusedMarkup; 

        internal class ControlMarkupCount
        {
            public GeometricShapeWpfControl GeometricShapeWpfControl { get; set; }
            public int MarkupCount { get; set; }
        }

        private ControlMarkupCount FindControlWithMissingMarkup(IValidTreeControl node)
        {
            ControlMarkupCount missingMarkupControl = null;

            if (node is GeometricShapeWpfControl)
            {
                var geometricShapeControl = node as GeometricShapeWpfControl;

                int numberOfMissingMarkup = NumberOfMissingMarkupRequiredByControl(geometricShapeControl);
                if (numberOfMissingMarkup > 0)
                    return new ControlMarkupCount
                               {
                                   GeometricShapeWpfControl = geometricShapeControl,
                                   MarkupCount = numberOfMissingMarkup
                               };
            }
            if (node.ChildControls != null)
                foreach (var child in node.ChildControls)
                {
                    missingMarkupControl = FindControlWithMissingMarkup(child);
                    if (missingMarkupControl != null)
                        break;
                }

            return missingMarkupControl;
        }

        public int NumberOfMissingMarkupRequiredByControl(GeometricShapeWpfControl geometricShapeControl)
        {
            for (int i = 0; i < geometricShapeControl.GeometricShape.MinCardinality; i++)
            {
                switch (geometricShapeControl.GeometricShape.GeometricShape)
                {
                    case AimTemplateTreeGeometricShapeNode.GeometricShapes.MultiPoint:
                        if (_unusedMarkup.OfType<MarkupLinear>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupLinear>().FirstOrDefault());
                        else if (_unusedMarkup.OfType<MarkupProtractor>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupProtractor>().FirstOrDefault());
                        else
                            return geometricShapeControl.GeometricShape.MinCardinality - i;
                        break;
                    case AimTemplateTreeGeometricShapeNode.GeometricShapes.Polyline:
                        if (_unusedMarkup.OfType<MarkupRectangle>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupRectangle>().FirstOrDefault());
                        else if (_unusedMarkup.OfType<MarkupPolygonal>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupPolygonal>().FirstOrDefault());
                        else
                            return geometricShapeControl.GeometricShape.MinCardinality - i;
                        break;
                    case AimTemplateTreeGeometricShapeNode.GeometricShapes.Circle:
                        if (_unusedMarkup.OfType<MarkupEllipse>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupEllipse>().FirstOrDefault());
                        else
                            return geometricShapeControl.GeometricShape.MinCardinality - i;
                        break;
                    case AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipse:
                        if (_unusedMarkup.OfType<MarkupEllipse>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupEllipse>().FirstOrDefault());
                        else
                            return geometricShapeControl.GeometricShape.MinCardinality - i;
                        break;
                    case AimTemplateTreeGeometricShapeNode.GeometricShapes.Point:
                        if (_unusedMarkup.OfType<MarkupPoint>().Any())
                            _unusedMarkup.Remove(_unusedMarkup.OfType<MarkupPoint>().FirstOrDefault());
                        else
                            return geometricShapeControl.GeometricShape.MinCardinality - i;
                        break;
                }
            }
            return 0;
        }

        private IValidTreeControl FindInvalidControl(IValidTreeControl node)
        {
            IValidTreeControl invalidControl = null;

            if (node.ChildControls != null)
                foreach (IValidTreeControl child in node.ChildControls)
                {
                    if (!child.Valid)
                    {
                        invalidControl = FindInvalidControl(child);
                        break;
                    }
                }

            if (invalidControl == null && !node.Valid && !(node is GeometricShapeWpfControl))
                invalidControl = node;

            return invalidControl;
        }

        private void UpdateGeometricShapeControlValidity(IValidTreeControl control)
        {
            if (control is GeometricShapeWpfControl)
            {
                var geometricShapeControl = control as GeometricShapeWpfControl;
                if (NumberOfMissingMarkupRequiredByControl(geometricShapeControl) == 0)
                    geometricShapeControl.Valid = true;
            }

            if (control.ChildControls != null)
                foreach (var child in control.ChildControls)
                    UpdateGeometricShapeControlValidity(child);
        }

        public void UpdateValid()
        {
            if (Component != null &&
                Component.AimTemplateTree != null &&
                Component.AimTemplateTree.Markup != null)
            {
                _unusedMarkup = new List<IMarkup>(Component.AimTemplateTree.Markup);
                foreach (IValidTreeControl control in NodeControls)
                {
                    UpdateGeometricShapeControlValidity(control);
                    control.UpdateValid();
                }
            }
        }

        #region Nested type: TemplateTreeNodeOrderComparer

        private class TemplateTreeNodeOrderComparer : IComparer<AimTemplateTreeNode>
        {
            #region IComparer<AimTemplateTreeNode> Members

            public int Compare(AimTemplateTreeNode x, AimTemplateTreeNode y)
            {
                return x.ItemNumber.CompareTo(y.ItemNumber);
            }

            #endregion
        }

        #endregion
    }
}
