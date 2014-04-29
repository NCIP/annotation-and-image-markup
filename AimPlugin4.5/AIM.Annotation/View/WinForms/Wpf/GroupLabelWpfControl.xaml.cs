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
using System.Windows;
using System.Windows.Controls;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for GroupLabelWpfControl.xaml
    /// </summary>
    public partial class GroupLabelWpfControl : UserControl, IValidTreeControl
    {
        public List<AimTemplateTreeNode> TreeNodes { get; private set; }

        private List<IValidTreeControl> NodeControls { get; set; } 

        public string Header
        {
            get { return _label.Text; }
            set { _label.Text = value; }
        }

        public GroupLabelWpfControl(List<AimTemplateTreeNode> treeNodes)
        {
            TreeNodes = treeNodes;

            NodeControls = new List<IValidTreeControl>();

            InitializeComponent();

            var visible = false;

            foreach (var treeNode in TreeNodes)
            {
                if (treeNode.ShouldDisplay)
                    visible = true;

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
                if (treeNode is AimTemplateTreeAnatomicEntityCharacteristicNode)
                {
                    var aecControl =
                        new AnatomicEntityCharacteristicWpfControl(
                            (AimTemplateTreeAnatomicEntityCharacteristicNode) treeNode);
                    _stackPanel.Children.Add(aecControl);
                    NodeControls.Add(aecControl);
                }
                if (treeNode is AimTemplateTreeImagingObservationCharacteristicNode)
                {
                    var iocControl =
                        new ImagingObservationCharacteristicWpfControl(
                            (AimTemplateTreeImagingObservationCharacteristicNode)treeNode);
                    _stackPanel.Children.Add(iocControl);
                    NodeControls.Add(iocControl);
                }
            }

            if (!visible)
            {
                Visibility = Visibility.Hidden;
                Height = 0;
            }
        }

        public void NotifyIfInvalid()
        {
        }

        public void UpdateValid()
        {
            foreach (var child in ChildControls)
                child.UpdateValid();
        }

        public List<IValidTreeControl> ChildControls
        {
            get { return NodeControls; }
        }

        public string NodeName
        {
            get { return Header; }
        }

        public bool Valid
        {
            get
            {
                return true;
            }
        }
    }
}
