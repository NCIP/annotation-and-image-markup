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
    /// Interaction logic for ImagingObservationCharacteristicWpfControl.xaml
    /// </summary>
    public partial class ImagingObservationCharacteristicWpfControl : UserControl, IValidTreeControl
    {
        public AimTemplateTreeImagingObservationCharacteristicNode Characteristic { get; private set; }

        public NodeConfidenceWpfControl NodeConfidenceWpfControl { get; private set; }

        private Dictionary<CharacteristicQuantificationAllowedTerm, CheckBox> CheckBoxControls { get; set; }

        private readonly Brush _originalBackground;

        private int MaxNumberOfAnswers
        {
            get { return Math.Max(1, Math.Min(
                Characteristic.CharacteristicQuantificationAllowedTerms.Count, 
                Characteristic.MaxCardinality)); }
        }

        public ImagingObservationCharacteristicWpfControl(AimTemplateTreeImagingObservationCharacteristicNode characteristic)
        {
            Characteristic = characteristic;
            InitializeComponent();

            _originalBackground = Background;
            ChildControls = new List<IValidTreeControl>();

            // Hide the allowed terms control that is not being used
            if (MaxNumberOfAnswers > 1)
            {
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;

                var cardinalityString = String.Empty;

                if (Characteristic.MinCardinality > 0 && Characteristic.MaxCardinality >= Characteristic.CharacteristicQuantificationAllowedTerms.Count)
                    cardinalityString = "Select at least " + Characteristic.MinCardinality;
                else if (Characteristic.MaxCardinality < Characteristic.CharacteristicQuantificationAllowedTerms.Count && Characteristic.MinCardinality <= 0)
                    cardinalityString = "Select less than " + (Characteristic.MaxCardinality + 1);
                else if (Characteristic.MinCardinality > 0 && Characteristic.MaxCardinality < Characteristic.CharacteristicQuantificationAllowedTerms.Count)
                    cardinalityString = "Select at least " + Characteristic.MinCardinality + " and less than " +
                                        (Characteristic.MaxCardinality + 1);

                if (!String.IsNullOrEmpty(cardinalityString))
                    ((TextBlock)_label.Content).Text += Environment.NewLine + cardinalityString;
            }
            else
            {
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
            }

            // Add confidence control
            if (Characteristic.ShouldDisplay && Characteristic.HasConfidence)
            {
                NodeConfidenceWpfControl = new NodeConfidenceWpfControl(Characteristic);
                _stackPanel.Children.Add(NodeConfidenceWpfControl);
            }

            ClearQuantificationDetailsControls();

            foreach (var term in Characteristic.SelectedCharacteristicQuantificationAllowedTerms)
            {
                foreach (var quantification in term.CharacteristicQuantifications)
                {
                    var characteristicControl = new CharacteristicQuantificationDetailsWpfControl(quantification);
                    _stackPanel.Children.Add(characteristicControl);
                    ChildControls.Add(characteristicControl);
                }
            }

            Loaded += AnatomicEntityCharacteristicWpfControlLoaded;

            Characteristic.SelectedAllowedTermsChanged += SelectedAllowedTermsCollectionChanged;
            CheckBoxControls = new Dictionary<CharacteristicQuantificationAllowedTerm, CheckBox>();

            if (!Characteristic.ShouldDisplay)
            {
                _label.Visibility = Visibility.Hidden;
                _label.Height = 0;
                _itemsControl.Visibility = Visibility.Hidden;
                _itemsControl.Height = 0;
                _comboBox.Visibility = Visibility.Hidden;
                _comboBox.Height = 0;
                if (Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Count == 0)
                {
                    Visibility = Visibility.Hidden;
                    Height = 0;
                }
            }
        }

        void AnatomicEntityCharacteristicWpfControlLoaded(object sender, RoutedEventArgs e)
        {
            Characteristic.SkippedChanged += CharacteristicSkippedChanged;
            Characteristic.NodeReset += CharacteristicNodeReset;

            UpdateSkipped();
        }

        void CharacteristicNodeReset(object sender, EventArgs e)
        {
            foreach (var key in CheckBoxControls.Keys)
                CheckBoxControls[key].IsChecked = key.Selected;
            if (Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Count > 0)
                _comboBox.SelectedItem = Characteristic.SelectedCharacteristicQuantificationAllowedTerms[0];
            else
                _comboBox.SelectedItem = null;

            // Moved to tree
            if (Characteristic.MaxCardinality == 1 && Characteristic.MinCardinality == 1 && Characteristic.CharacteristicQuantificationAllowedTerms.Count == 1)
                _comboBox.SelectedIndex = 0;

            if (NodeConfidenceWpfControl != null)
                NodeConfidenceWpfControl.Reset();

            UpdateSkipped();
        }

        private void UpdateSkipped()
        {
            IsEnabled = !Characteristic.Skipped;    
        }

        void CharacteristicSkippedChanged(object sender, EventArgs e)
        {
            UpdateSkipped();
        }

        void SelectedAllowedTermsCollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var item in e.NewItems)
                {
                    var term = item as CharacteristicQuantificationAllowedTerm;
                    if (term != null && CheckBoxControls.ContainsKey(term))
                        CheckBoxControls[term].IsChecked = true;
                }
            }

            if (e.OldItems != null)
            {
                foreach (var item in e.OldItems)
                {
                    var term = item as CharacteristicQuantificationAllowedTerm;
                    if (term != null && CheckBoxControls.ContainsKey(term))
                        CheckBoxControls[term].IsChecked = false;
                }
            }

            if (Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Count > 0)
            {
                _comboBox.SelectedItem = Characteristic.SelectedCharacteristicQuantificationAllowedTerms[0];
            }

            ClearQuantificationDetailsControls();

            foreach (var term in Characteristic.SelectedCharacteristicQuantificationAllowedTerms)
            {
                foreach (var quantification in term.CharacteristicQuantifications)
                {
                    var characteristicControl = new CharacteristicQuantificationDetailsWpfControl(quantification);
                    _stackPanel.Children.Add(characteristicControl);
                }
            }
        }

        private void ClearQuantificationDetailsControls()
        {
            var removedControls = new List<UIElement>();
            for (int index = 0; index < _stackPanel.Children.Count; index++)
            {
                var control = _stackPanel.Children[index];
                if (control is CharacteristicQuantificationDetailsWpfControl)
                    removedControls.Add(control);
            }

            foreach (var control in removedControls)
                _stackPanel.Children.Remove(control);
        }

        private void CheckBoxChecked(object sender, RoutedEventArgs e)
        {
            var term = ((CheckBox)sender).Content as CharacteristicQuantificationAllowedTerm;
            if (term != null)
                term.Selected = true;

        }

        private void CheckBoxUnchecked(object sender, RoutedEventArgs e)
        {
            var term = ((CheckBox)sender).Content as CharacteristicQuantificationAllowedTerm;
            if (term != null)
                term.Selected = false;
        }

        private void CheckBoxInitialized(object sender, EventArgs e)
        {
            var term = ((CheckBox)sender).Content as CharacteristicQuantificationAllowedTerm;
            if (term != null)
            {
                if (Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Contains(term))
                    ((CheckBox)sender).IsChecked = true;
                CheckBoxControls.Add(term, (CheckBox)sender);                
            }
        }

        private void ComboBoxSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
                if (MaxNumberOfAnswers <= 1 && 
                    Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Count > 0 &&
                    Characteristic.SelectedCharacteristicQuantificationAllowedTerms[0] != _comboBox.SelectedItem)
                    Characteristic.ClearSelectedAllowedTerms();
                if (_comboBox.SelectedItem != null)
                    ((CharacteristicQuantificationAllowedTerm)_comboBox.SelectedItem).Selected = true;
        }

        private void ComboBoxInitialized(object sender, EventArgs e)
        {
            if (Characteristic.SelectedCharacteristicQuantificationAllowedTerms.Count > 0)
            {
                var comboBox = sender as ComboBox;

                if (comboBox != null)
                    comboBox.SelectedItem = Characteristic.SelectedCharacteristicQuantificationAllowedTerms[0];
            }
        }

        private void OnToolTipOpening(object sender, ToolTipEventArgs e)
        {
            WpfUtils.OnToolTipOpening(sender, e);
        }

        public void NotifyIfInvalid()
        {
            if (!Characteristic.Valid)
                Background = new SolidColorBrush(Color.FromRgb(255, 255, 0));
        }

        public void UpdateValid()
        {
            if (Characteristic.Valid)
                Background = _originalBackground;
            foreach (var child in ChildControls)
                child.UpdateValid();
        }

        public List<IValidTreeControl> ChildControls { get; private set; }

        public string NodeName
        {
            get { return Characteristic.Label; }
        }

        public bool Valid
        {
            get { return Characteristic.Valid; }
        }
    }
}
