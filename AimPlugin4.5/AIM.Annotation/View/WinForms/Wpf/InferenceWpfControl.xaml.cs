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
    /// Interaction logic for InferenceWpfControl.xaml
    /// </summary>
    public partial class InferenceWpfControl : UserControl, IValidTreeControl
    {
        public AimTemplateTreeInferenceNode Inference { get; private set; }

        private Dictionary<AimTemplateTreeAllowedTerm, CheckBox> CheckBoxControls { get; set; }

        public NodeConfidenceWpfControl NodeConfidenceWpfControl { get; private set; }

        private readonly Brush _originalBackground;

        private int MaxNumberOfAnswers
        {
            get { return Math.Max(1, Math.Min(Inference.AllowedTerms.Count, Inference.MaxCardinality)); }
        }

        public InferenceWpfControl(AimTemplateTreeInferenceNode inference)
        {
            Inference = inference;
            InitializeComponent();

            _originalBackground = Background;

            // Hide the allowed terms control that is not being used
            if (MaxNumberOfAnswers > 1)
            {
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;

                var cardinalityString = String.Empty;

                if (Inference.MinCardinality > 0 && Inference.MaxCardinality >= Inference.AllowedTerms.Count)
                    cardinalityString = "Select at least " + Inference.MinCardinality;
                else if (Inference.MaxCardinality < Inference.AllowedTerms.Count && Inference.MinCardinality <= 0)
                    cardinalityString = "Select less than " + (Inference.MaxCardinality + 1);
                else if (Inference.MinCardinality > 0 && Inference.MaxCardinality < Inference.AllowedTerms.Count)
                    cardinalityString = "Select at least " + Inference.MinCardinality + " and less than " +
                                        (Inference.MaxCardinality + 1);

                if (!String.IsNullOrEmpty(cardinalityString))
                    ((TextBlock)_label.Content).Text += Environment.NewLine + cardinalityString;
            }
            else
            {
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
            }

            // Add confidence control
            if (Inference.ShouldDisplay && Inference.HasConfidence)
            {
                NodeConfidenceWpfControl = new NodeConfidenceWpfControl(Inference);
                _stackPanel.Children.Add(NodeConfidenceWpfControl);
            }

            Loaded += InferenceWpfControlLoaded;

            Inference.SelectedAllowedTermsChanged += SelectedAllowedTermsCollectionChanged;
            CheckBoxControls = new Dictionary<AimTemplateTreeAllowedTerm, CheckBox>();

            if (!Inference.ShouldDisplay)
            {
                this.Visibility = Visibility.Hidden;
                this.Height = 0;
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

            if (Inference.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = Inference.SelectedAllowedTerms[0];
        }

        void InferenceWpfControlLoaded(object sender, EventArgs e)
        {
            Inference.SkippedChanged += InferenceSkippedChanged;
            Inference.NodeReset += InferenceNodeReset;

            UpdateSkipped();
        }

        void InferenceNodeReset(object sender, EventArgs e)
        {
            foreach (var key in CheckBoxControls.Keys)
                CheckBoxControls[key].IsChecked = key.Selected;
            if (Inference.SelectedAllowedTerms.Count > 0)
                _comboBox.SelectedItem = Inference.SelectedAllowedTerms[0];
            else
                _comboBox.SelectedItem = null;

            if (Inference.MaxCardinality == 1 && Inference.MinCardinality == 1 && Inference.AllowedTerms.Count == 1)
                Inference.AllowedTerms[0].Selected = true;

            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.Reset();

            UpdateSkipped();
        }

        private void UpdateSkipped()
        {
            IsEnabled = !Inference.Skipped;
        }

        void InferenceSkippedChanged(object sender, EventArgs e)
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
                if (Inference.SelectedAllowedTerms.Contains(term))
                    ((CheckBox)sender).IsChecked = true;
                CheckBoxControls.Add(term, (CheckBox)sender);
            }
        }

        private void ComboBoxSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (MaxNumberOfAnswers <= 1 &&
                Inference.SelectedAllowedTerms.Count > 0 &&
                Inference.SelectedAllowedTerms[0] != _comboBox.SelectedItem)
                Inference.ClearSelectedAllowedTerms();
            if (_comboBox.SelectedItem != null)
                ((AimTemplateTreeAllowedTerm)_comboBox.SelectedItem).Selected = true;
        }


        private void ComboBoxInitialized(object sender, EventArgs e)
        {
            if (Inference.SelectedAllowedTerms.Count > 0 && Inference.MaxCardinality == 1)
            {
                var comboBox = sender as ComboBox;

                if (comboBox != null)
                    comboBox.SelectedItem = Inference.SelectedAllowedTerms[0];
            }
        }

        private void OnToolTipOpening(object sender, ToolTipEventArgs e)
        {
            WpfUtils.OnToolTipOpening(sender, e);
        }

        public void NotifyIfInvalid()
        {
            if (!Inference.Valid)
                Background = new SolidColorBrush(Color.FromRgb(255, 255, 0));
        }

        public void UpdateValid()
        {
            if (Inference.Valid)
                Background = _originalBackground;
        }

        public List<IValidTreeControl> ChildControls
        {
            get { return new List<IValidTreeControl>(); }
        }

        public string NodeName
        {
            get { return Inference.Label; }
        }

        public bool Valid
        {
            get { return Inference.Valid; }
        }
    }
}
