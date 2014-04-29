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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for AnatomicEntityWpfControl.xaml
    /// </summary>
    public partial class AnatomicEntityWpfControl : UserControl, IValidTreeControl
    {
        public AimTemplateTreeAnatomicEntityNode AnatomicEntity { get; private set; }

        private Dictionary<AimTemplateTreeAllowedTerm, CheckBox> CheckBoxControls { get; set; } 

        public NodeConfidenceWpfControl NodeConfidenceWpfControl { get; private set; }

        public List<IValidTreeControl> ChildControls { get; private set; } 

        private readonly Brush _originalBackground;

        private int MaxNumberOfAnswers
        {
            get { return Math.Max(1, Math.Min(AnatomicEntity.AllowedTerms.Count, AnatomicEntity.MaxCardinality)); }
        }

        public AnatomicEntityWpfControl(AimTemplateTreeAnatomicEntityNode anatomicEntity)
        {
            AnatomicEntity = anatomicEntity;
            InitializeComponent();

            ChildControls = new List<IValidTreeControl>();

            _originalBackground = Background;

            // Hide the allowed terms control that is not being used
            if (MaxNumberOfAnswers > 1)
            {
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;

                var cardinalityString = String.Empty;

                if (AnatomicEntity.MinCardinality > 0 && AnatomicEntity.MaxCardinality >= AnatomicEntity.AllowedTerms.Count)
                    cardinalityString = "Select at least " + AnatomicEntity.MinCardinality;
                else if (AnatomicEntity.MaxCardinality < AnatomicEntity.AllowedTerms.Count && AnatomicEntity.MinCardinality <= 0)
                    cardinalityString = "Select less than " + (AnatomicEntity.MaxCardinality + 1);
                else if (AnatomicEntity.MinCardinality > 0 && AnatomicEntity.MaxCardinality < AnatomicEntity.AllowedTerms.Count)
                    cardinalityString = "Select at least " + AnatomicEntity.MinCardinality + " and less than " +
                                        (AnatomicEntity.MaxCardinality + 1);

                if (!String.IsNullOrEmpty(cardinalityString))
                    ((TextBlock) _label.Content).Text += Environment.NewLine + cardinalityString;
            }
            else
            {
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
            }

            // Add confidence control
            if (AnatomicEntity.ShouldDisplay && AnatomicEntity.HasConfidence)
            {
                NodeConfidenceWpfControl = new NodeConfidenceWpfControl(AnatomicEntity);
                _stackPanel.Children.Add(NodeConfidenceWpfControl);
            }

            var characteristicNodes = anatomicEntity.AnatomicEntityCharacteristicTreeNodes.Cast<AimTemplateTreeNode>().ToList();
            characteristicNodes.AddRange(anatomicEntity.ImagingObservationCharacteristicTreeNodes.Cast<AimTemplateTreeNode>().ToList());

            characteristicNodes.Sort(new TemplateTreeNodeOrderComparer());

            var groupedNodes = new List<AimTemplateTreeNode>();

            foreach (var characteristic in characteristicNodes)
            {
                // Start or add to group label control
                if (!String.IsNullOrEmpty(characteristic.GroupLabel))
                {
                    if (groupedNodes.Count > 0 && characteristic.GroupLabel == groupedNodes[0].GroupLabel)
                        groupedNodes.Add(characteristic);
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
                            ChildControls.Add(groupLabel);
                        }

                        groupedNodes = new List<AimTemplateTreeNode> { characteristic };
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
                        ChildControls.Add(groupLabel);
                    }

                    if (characteristic is AimTemplateTreeAnatomicEntityCharacteristicNode)
                    {
                        var characteristicControl = new AnatomicEntityCharacteristicWpfControl(
                            (AimTemplateTreeAnatomicEntityCharacteristicNode)characteristic);
                        _stackPanel.Children.Add(characteristicControl);
                        ChildControls.Add(characteristicControl);
                    }

                    if (characteristic is AimTemplateTreeImagingObservationCharacteristicNode)
                    {
                        var characteristicControl = new ImagingObservationCharacteristicWpfControl(
                            (AimTemplateTreeImagingObservationCharacteristicNode)characteristic);
                        _stackPanel.Children.Add(characteristicControl);
                        ChildControls.Add(characteristicControl);
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
                ChildControls.Add(groupLabel);
            }

            Loaded += AnatomicEntityWpfControlLoaded;

            AnatomicEntity.SelectedAllowedTermsChanged += SelectedAllowedTermsCollectionChanged;
            CheckBoxControls = new Dictionary<AimTemplateTreeAllowedTerm, CheckBox>();

            if (!AnatomicEntity.ShouldDisplay)
            {
                _label.Visibility = Visibility.Hidden;
                _label.Height = 0;
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;
                if (characteristicNodes.TrueForAll(item => !item.ShouldDisplay))
                {
                    Visibility = Visibility.Hidden;
                    Height = 0;
                }
            }
        }

        private class TemplateTreeNodeOrderComparer : IComparer<AimTemplateTreeNode>
        {
            public int Compare(AimTemplateTreeNode x, AimTemplateTreeNode y)
            {
                return x.ItemNumber.CompareTo(y.ItemNumber);
            }
        }

        void SelectedAllowedTermsCollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var item in e.NewItems)
                {
                    var term = item as AimTemplateTreeAllowedTerm;
                    if (term != null && CheckBoxControls.ContainsKey(term))
                            CheckBoxControls[term].IsChecked = true;
                }
            }

            if (e.OldItems != null)
            {
                foreach (var item in e.OldItems)
                {
                    var term = item as AimTemplateTreeAllowedTerm;
                    if (term != null && CheckBoxControls.ContainsKey(term))
                        CheckBoxControls[term].IsChecked = false;
                }
            }

            if (AnatomicEntity.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = AnatomicEntity.SelectedAllowedTerms[0];
        }

        void AnatomicEntityWpfControlLoaded(object sender, EventArgs e)
        {
            AnatomicEntity.SkippedChanged += AnatomicEntitySkippedChanged;
            AnatomicEntity.NodeReset += AnatomicEntityNodeReset;

            UpdateEnabled();
        }

        void AnatomicEntityNodeReset(object sender, EventArgs e)
        {
            foreach (var key in CheckBoxControls.Keys)
                CheckBoxControls[key].IsChecked = key.Selected;
            if (AnatomicEntity.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = AnatomicEntity.SelectedAllowedTerms[0];
            else
                _comboBox.SelectedItem = null;

            if (AnatomicEntity.MaxCardinality == 1 && AnatomicEntity.MinCardinality == 1 && AnatomicEntity.AllowedTerms.Count == 1)
                _comboBox.SelectedItem = _comboBox.Items[0];

            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.Reset();

            UpdateEnabled();
        }

        private void UpdateEnabled()
        {
            _itemsControl.IsEnabled = !AnatomicEntity.Skipped;
            _comboBox.IsEnabled = !AnatomicEntity.Skipped;
            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.IsEnabled = !AnatomicEntity.Skipped;
            
        }

        void AnatomicEntitySkippedChanged(object sender, EventArgs e)
        {
            UpdateEnabled();
        }

        private void CheckBoxChecked(object sender, RoutedEventArgs e)
        {
            var term = ((CheckBox)sender).Content as AimTemplateTreeAllowedTerm;
            if (term != null)
                term.Selected = true;

        }

        private void CheckBoxUnchecked(object sender, RoutedEventArgs e)
        {
            var term = ((CheckBox)sender).Content as AimTemplateTreeAllowedTerm;
            if (term != null)
                term.Selected = false;
        }

        private void CheckBoxInitialized(object sender, EventArgs e)
        {
            var term = ((CheckBox)sender).Content as AimTemplateTreeAllowedTerm;
            if (term != null)
            {
                if (AnatomicEntity.SelectedAllowedTerms.Contains(term))
                    ((CheckBox)sender).IsChecked = true;
                CheckBoxControls.Add(term, (CheckBox)sender);
            }
        }

        private void ComboBoxSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (MaxNumberOfAnswers <= 1 &&
                AnatomicEntity.SelectedAllowedTerms.Count > 0 &&
                AnatomicEntity.SelectedAllowedTerms[0] != _comboBox.SelectedItem)
                AnatomicEntity.ClearSelectedAllowedTerms();
            if (_comboBox.SelectedItem != null)
                ((AimTemplateTreeAllowedTerm)_comboBox.SelectedItem).Selected = true;
        }


        private void ComboBoxInitialized(object sender, EventArgs e)
        {
            if (AnatomicEntity.SelectedAllowedTerms.Count > 0 && AnatomicEntity.MaxCardinality == 1)
            {
                var comboBox = sender as ComboBox;

                if (comboBox != null)
                    comboBox.SelectedItem = AnatomicEntity.SelectedAllowedTerms[0];
            }
        }

        private void OnToolTipOpening(object sender, ToolTipEventArgs e)
        {
            WpfUtils.OnToolTipOpening(sender, e);
        }

        public void NotifyIfInvalid()
        {
            if (!AnatomicEntity.Valid)
                Background = new SolidColorBrush(Color.FromRgb(255, 255, 0));
        }

        public void UpdateValid()
        {
            if (AnatomicEntity.Valid)
                Background = _originalBackground;
            foreach (var child in ChildControls)
                child.UpdateValid();
        }

        public string NodeName
        {
            get { return AnatomicEntity.Label; }
        }

        public bool Valid
        {
            get { return AnatomicEntity.Valid; }
        }
    }
}
