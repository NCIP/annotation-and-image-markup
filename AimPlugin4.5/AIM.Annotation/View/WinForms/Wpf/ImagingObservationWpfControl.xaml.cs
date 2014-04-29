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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for ImagingObservationWpfControl.xaml
    /// </summary>
    public partial class ImagingObservationWpfControl : UserControl, IValidTreeControl
    {
        public AimTemplateTreeImagingObservationNode ImagingObservation { get; private set; }

        private Dictionary<AimTemplateTreeAllowedTerm, CheckBox> CheckBoxControls { get; set; }

        public NodeConfidenceWpfControl NodeConfidenceWpfControl { get; private set; }

        public List<IValidTreeControl> ChildControls { get; private set; }

        private readonly Brush _originalBackground;

        private int MaxNumberOfAnswers
        {
            get { return Math.Max(1, Math.Min(ImagingObservation.AllowedTerms.Count, ImagingObservation.MaxCardinality)); }
        }

        public ImagingObservationWpfControl(AimTemplateTreeImagingObservationNode imagingObservation)
        {
            ImagingObservation = imagingObservation;
            InitializeComponent();

            _originalBackground = Background;
            ChildControls = new List<IValidTreeControl>();

            // Hide the allowed terms control that is not being used
            if (MaxNumberOfAnswers > 1)
            {
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;

                var cardinalityString = String.Empty;

                if (ImagingObservation.MinCardinality > 0 && ImagingObservation.MaxCardinality >= ImagingObservation.AllowedTerms.Count)
                    cardinalityString = "Select at least " + ImagingObservation.MinCardinality;
                else if (ImagingObservation.MaxCardinality < ImagingObservation.AllowedTerms.Count && ImagingObservation.MinCardinality <= 0)
                    cardinalityString = "Select less than " + (ImagingObservation.MaxCardinality + 1);
                else if (ImagingObservation.MinCardinality > 0 && ImagingObservation.MaxCardinality < ImagingObservation.AllowedTerms.Count)
                    cardinalityString = "Select at least " + ImagingObservation.MinCardinality + " and less than " +
                                        (ImagingObservation.MaxCardinality + 1);

                if (!String.IsNullOrEmpty(cardinalityString))
                    ((TextBlock)_label.Content).Text += Environment.NewLine + cardinalityString;
            }
            else
            {
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
            }

            // Add confidence control
            if (ImagingObservation.ShouldDisplay && ImagingObservation.HasConfidence)
            {
                NodeConfidenceWpfControl = new NodeConfidenceWpfControl(ImagingObservation);
                _stackPanel.Children.Add(NodeConfidenceWpfControl);
            }

            var groupedNodes = new List<AimTemplateTreeNode>();

            foreach (var characteristic in imagingObservation.ImagingObservationCharacteristicTreeNodes)
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

                    var characteristicControl = new ImagingObservationCharacteristicWpfControl(characteristic);
                    _stackPanel.Children.Add(characteristicControl);
                    ChildControls.Add(characteristicControl);
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

            Loaded += ImagingObservationWpfControlLoaded;

            ImagingObservation.SelectedAllowedTermsChanged += SelectedAllowedTermsCollectionChanged;
            CheckBoxControls = new Dictionary<AimTemplateTreeAllowedTerm, CheckBox>();

            if (!ImagingObservation.ShouldDisplay)
            {
                _label.Visibility = Visibility.Hidden;
                _label.Height = 0;
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;
                if (imagingObservation.ImagingObservationCharacteristicTreeNodes.TrueForAll(item => !item.ShouldDisplay))
                {
                    Visibility = Visibility.Hidden;
                    Height = 0;
                }
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

            if (ImagingObservation.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = ImagingObservation.SelectedAllowedTerms[0];
        }

        void ImagingObservationWpfControlLoaded(object sender, EventArgs e)
        {
            ImagingObservation.SkippedChanged += ImagingObservationSkippedChanged;
            ImagingObservation.NodeReset += ImagingObservationNodeReset;

            UpdateSkipped();
        }

        void ImagingObservationNodeReset(object sender, EventArgs e)
        {
            foreach (var key in CheckBoxControls.Keys)
                CheckBoxControls[key].IsChecked = key.Selected;
            if (ImagingObservation.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = ImagingObservation.SelectedAllowedTerms[0];
            else
                _comboBox.SelectedItem = null;
            if (ImagingObservation.MaxCardinality == 1 && ImagingObservation.MinCardinality == 1 && ImagingObservation.AllowedTerms.Count == 1)
                _comboBox.SelectedItem = _comboBox.Items[0];

            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.Reset();

            UpdateSkipped();
        }

        private void UpdateSkipped()
        {
            _itemsControl.IsEnabled = !ImagingObservation.Skipped;
            _comboBox.IsEnabled = !ImagingObservation.Skipped;
            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.IsEnabled = !ImagingObservation.Skipped;
        }

        void ImagingObservationSkippedChanged(object sender, EventArgs e)
        {
            UpdateSkipped();
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
                if (ImagingObservation.SelectedAllowedTerms.Contains(term))
                    ((CheckBox)sender).IsChecked = true;
                CheckBoxControls.Add(term, (CheckBox)sender);
            }
        }

        private void ComboBoxSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (MaxNumberOfAnswers <= 1 &&
                ImagingObservation.SelectedAllowedTerms.Count > 0 &&
                ImagingObservation.SelectedAllowedTerms[0] != _comboBox.SelectedItem)
                ImagingObservation.ClearSelectedAllowedTerms();
            if (_comboBox.SelectedItem != null)
                ((AimTemplateTreeAllowedTerm) _comboBox.SelectedItem).Selected = true;
        }


        private void ComboBoxInitialized(object sender, EventArgs e)
        {
            if (ImagingObservation.SelectedAllowedTerms.Count > 0 && ImagingObservation.MaxCardinality == 1)
            {
                var comboBox = sender as ComboBox;

                if (comboBox != null)
                    comboBox.SelectedItem = ImagingObservation.SelectedAllowedTerms[0];
            }
        }

        private void OnToolTipOpening(object sender, ToolTipEventArgs e)
        {
            WpfUtils.OnToolTipOpening(sender, e);
        }

        public void NotifyIfInvalid()
        {
            if (!ImagingObservation.Valid)
                Background = new SolidColorBrush(Color.FromRgb(255, 255, 0));
        }

        public void UpdateValid()
        {
            if (ImagingObservation.Valid)
                Background = _originalBackground;
            foreach (var child in ChildControls)
                child.UpdateValid();
        }

        public string NodeName
        {
            get { return ImagingObservation.Label; }
        }

        public bool Valid
        {
            get { return ImagingObservation.Valid; }
        }
    }
}
