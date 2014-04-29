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
using System.Diagnostics;
using System.Linq;
using System.Windows.Controls;
using System.Windows.Media;
using AIM.Annotation.TemplateTree;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for CharacteristicQuantificationDetailsWpfControl.xaml
    /// </summary>
    public partial class CharacteristicQuantificationDetailsWpfControl : UserControl, IValidTreeControl
    {
        private readonly CharacteristicQuantificationTypes _quantificationType;
        private QuantificationConfidenceWpfControl _quantificationConfidenceControl;
        private object _selectedItem;

        // Scale-specific values
        private string _scaleComment; // TODO - Do we need to display this?
        private string _scaleDescription; // TODO - schema fix - either scale or Ordinal Level description is needed. For now, will use this is each scale's description is missing

        private bool _fireChangeEvent = true;

        private readonly Brush _originalBackground;

        private AimTemplateTreeCharacteristicQuantification CharacteristicQuantification { get; set; }

        private Control _quantificationControl;

        public CharacteristicQuantificationDetailsWpfControl(AimTemplateTreeCharacteristicQuantification characteristicQuantification)
        {
            CharacteristicQuantification = characteristicQuantification;

            InitializeComponent();

            _originalBackground = Background;

            _charQuantifiactionName.Text = string.IsNullOrEmpty(characteristicQuantification.Name) ? @"Characteristic name is missing:" : "Characteristic for " + characteristicQuantification.Name + ":";
            _quantificationType = IdentifyCharQuantificationType();

            Loaded += CharacteristicQuantificationDetailsWpfControlLoaded;
        }

        void CharacteristicQuantificationDetailsWpfControlLoaded(object sender, System.Windows.RoutedEventArgs e)
        {
            InitializeCharQuantificationControls();

            if (CharacteristicQuantification.HasConfidence)
            {
                _quantificationConfidenceControl = InitializeConfidenceControl();
                _stackPanel.Children.Add(_quantificationConfidenceControl);
            }

            CharacteristicQuantification.CharacteristicQuantificationReset += CharacteristicQuantificationCharacteristicQuantificationReset;
        }

        void CharacteristicQuantificationCharacteristicQuantificationReset(object sender, EventArgs e)
        {
            if (_quantificationControl != null)
            {
                if (_quantificationControl is ComboBox)
                {
                    var comboBox = _quantificationControl as ComboBox;

                    var defaultItem = comboBox.Items.Cast<ComparableListItem>().FirstOrDefault(term => term.Default);
                    // Disabled auto selecting default answer - make preference in future version
                    //comboBox.SelectedItem = defaultItem; 
                }
            }

            if (_quantificationConfidenceControl != null)
                _quantificationConfidenceControl.Reset();
        }


        public enum CharacteristicQuantificationTypes
        {
            Numerical,
            Quantile,
            NonQuantifiable,
            Scale,
            Interval
        }

        private CharacteristicQuantificationTypes IdentifyCharQuantificationType()
        {
            if (CharacteristicQuantification is AimTemplateTreeNumericalQuantification)
                return CharacteristicQuantificationTypes.Numerical;

            if (CharacteristicQuantification is AimTemplateTreeQuantileQuantification)
                return CharacteristicQuantificationTypes.Quantile;

            if (CharacteristicQuantification is AimTemplateTreeScaleQuantification)
                return CharacteristicQuantificationTypes.Scale;

            if (CharacteristicQuantification is AimTemplateTreeIntervalQuantification)
                return CharacteristicQuantificationTypes.Interval;

            return CharacteristicQuantificationTypes.NonQuantifiable;
        }

        private void InitializeCharQuantificationControls()
        {
            // NOTE:
            // All values are displayed in a single DropDown for now (single selection only)
            // Will need to account for cardinality and have complex logic to show/hide/enable various controls depending on the cardinality values

            var selectionItems = new List<ComparableListItem>();

            ComparableListItem selectedItem = null;
            ComparableListItem defaultItem = null;

            if (CharacteristicQuantification.NonQuantifiables != null && CharacteristicQuantification.NonQuantifiables.Count > 0)
            {
                // Hide blank list box item
                //selectionItems.Add(new CodeSequenceListItem(null));

                foreach (var nonQuantifiable in CharacteristicQuantification.NonQuantifiables)
                {
                    var listItem = new CodeSequenceListItem(
                        new StandardCodedTerm(
                            nonQuantifiable.DefaultAnswer,
                            nonQuantifiable.NextId,
                            nonQuantifiable.NoMoreQuestions,
                            nonQuantifiable.CodeValue,
                            nonQuantifiable.CodeMeaning,
                            nonQuantifiable.CodingSchemeDesignator,
                            nonQuantifiable.CodingSchemeVersion));
                    selectionItems.Add(listItem);

                    if (CharacteristicQuantification.SelectedNonQuantifiable != null && listItem.Value.Equals(CharacteristicQuantification.SelectedNonQuantifiable))
                        selectedItem = listItem;
                    else if (nonQuantifiable.DefaultAnswer)
                        defaultItem = listItem;
                }
            }

            switch (CharacteristicQuantificationType)
            {
                case CharacteristicQuantificationTypes.Numerical:
                    {
                        var numericalQuantification =
                            CharacteristicQuantification as
                            AimTemplateTreeNumericalQuantification;
                        foreach (var numerical in numericalQuantification.Numericals)
                        {
                            var listItem = new NumericalListItem(numerical);
                            selectionItems.Add(listItem);
                            if (numericalQuantification.SelectedNumerical != null && numericalQuantification.SelectedNumerical.Value.Equals(numerical))
                                selectedItem = listItem;
                            else if (numerical.DefaultAnswer)
                                defaultItem = listItem;
                        }
                    }
                    break;
                case CharacteristicQuantificationTypes.Quantile:
                    {
                        var quantileQuantification =
                            CharacteristicQuantification as AimTemplateTreeQuantileQuantification;
                        for (int i = 0; i < quantileQuantification.Quantile.Bins; i++)
                        {
                            var listItem = new QuantileListItem(i);
                            selectionItems.Add(listItem);
                            if (quantileQuantification.SelectedBin != null && quantileQuantification.SelectedBin == i)
                                selectedItem = listItem;
                            else if (quantileQuantification.Quantile.DefaultBin != null && quantileQuantification.Quantile.DefaultBin.Value == i)
                                defaultItem = listItem;
                        }
                    }
                    break;
                case CharacteristicQuantificationTypes.Scale:
                    {
                        var scale =
                            CharacteristicQuantification as AimTemplateTreeScaleQuantification;

                        foreach (var scaleLevel in scale.Scale.ScaleLevels)
                        {
                            var listItem = new ScaleListItem(scaleLevel);
                            selectionItems.Add(listItem);
                            if (scale.SelectedScaleLevel != null && scale.SelectedScaleLevel.Equals(scaleLevel))
                                selectedItem = listItem;
                            else if (scaleLevel.DefaultAnswer)
                                defaultItem = listItem;
                        }
                    }
                    break;
                case CharacteristicQuantificationTypes.Interval:
                    {
                        var intervalQuantification =
                            CharacteristicQuantification as AimTemplateTreeIntervalQuantification;
                        foreach (var interval in intervalQuantification.Intervals)
                        {
                            var listItem = new IntervalListItem(interval);
                            selectionItems.Add(listItem);
                            if (intervalQuantification.SelectedInterval != null && intervalQuantification.SelectedInterval.Equals(interval))
                                selectedItem = listItem;
                            else if (interval.DefaultAnswer)
                                defaultItem = listItem;
                        }
                    }
                    break;
                case CharacteristicQuantificationTypes.NonQuantifiable:
                    break; // all done
            }

            // FIXME
            // A single DropDown for now for all items
            //

            var ddlQuantificationItems = new ComboBox();


            foreach (object item in selectionItems)
            {
                ddlQuantificationItems.Items.Add(item);
            }

            if (selectedItem != null)
                ddlQuantificationItems.SelectedItem = selectedItem;

            ddlQuantificationItems.SelectionChanged += QuantificationItemsSelectionChanged;

            if (selectedItem == null && ddlQuantificationItems.Items.Count == 1)
            {
                defaultItem = (ComparableListItem)ddlQuantificationItems.Items[0];
                defaultItem.Default = true;
            }

            // Add control
            _stackPanel.Children.Add(ddlQuantificationItems);
            _quantificationControl = ddlQuantificationItems;
        }

        private void QuantificationItemsSelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            var comboBox = (ComboBox)sender;

            if (comboBox.SelectedItem != null)
            {
                if (comboBox.SelectedItem is CodeSequenceListItem)
                {
                    var codeSequenceListItem = comboBox.SelectedItem as CodeSequenceListItem;
                    CharacteristicQuantification.SelectedNonQuantifiable = codeSequenceListItem.Value;
                }
                else
                {
                    CharacteristicQuantification.SelectedNonQuantifiable = null;
                
                    if (CharacteristicQuantification is AimTemplateTreeQuantileQuantification)
                    {
                        var quantile = comboBox.SelectedItem as QuantileListItem;
                        if (quantile != null)
                            ((AimTemplateTreeQuantileQuantification)
                             CharacteristicQuantification).SelectedBin = quantile.Bin;
                    }
                    if (CharacteristicQuantification is AimTemplateTreeScaleQuantification)
                    {
                        var scale = comboBox.SelectedItem as ScaleListItem;

                        if (scale != null)
                            ((AimTemplateTreeScaleQuantification)
                             CharacteristicQuantification).SelectedScaleLevel = scale.ScaleLevel;
                    }
                    if (CharacteristicQuantification is AimTemplateTreeIntervalQuantification)
                    {
                        var interval = comboBox.SelectedItem as IntervalListItem;
                        if (interval != null)
                            ((AimTemplateTreeIntervalQuantification)
                             CharacteristicQuantification).SelectedInterval = interval.Interval;
                    }
                    if (CharacteristicQuantification is AimTemplateTreeNumericalQuantification)
                    {
                        var numerical = comboBox.SelectedItem as NumericalListItem;
                        if (numerical != null)
                            ((AimTemplateTreeNumericalQuantification)
                             CharacteristicQuantification).SelectedNumerical = numerical.Numerical;
                    }
                }
            }
        }

        private QuantificationConfidenceWpfControl InitializeConfidenceControl()
        {
            var confidenceControl = new QuantificationConfidenceWpfControl(CharacteristicQuantification);

            return confidenceControl;
        }

        public CharacteristicQuantificationTypes CharacteristicQuantificationType
        {
            get { return _quantificationType; }
        }

        private double? ConfidenceValue
        {
            get { return CharacteristicQuantification.ConfidenceValue; }
        }

        internal abstract class ComparableListItem
        {
            internal static string OperatorToString(ComparisonOperator daOperator, bool capFirst)
            {
                switch (daOperator)
                {
                    case ComparisonOperator.Equal:
                        return capFirst ? "Equal to" : "equal to";
                    case ComparisonOperator.NotEqual:
                        return capFirst ? "Not equal to" : "not equal to";
                    case ComparisonOperator.LessThan:
                        return capFirst ? "Less than" : "less than";
                    case ComparisonOperator.LessThanEqual:
                        return capFirst ? "Less than or equal" : "less than or equal";
                    case ComparisonOperator.GreaterThan:
                        return capFirst ? "Greater than" : "greater than";
                    case ComparisonOperator.GreaterThanEqual:
                        return capFirst ? "Greater than or equal" : "greater than or equal";
                }

                return capFirst ? "Invalid" : "invalid";
            }

            public bool Default { get; set; }
        }

        internal class NumericalListItem : ComparableListItem
        {
            public double Value { get; private set; }
            public ComparisonOperator? ComparisonOperator { get; private set; }
            public string UcumString { get; private set; }
            public Numerical Numerical { get; private set; }

            internal NumericalListItem(Numerical numerical)
            {
                Value = numerical.Value;
                if (numerical.OperatorSpecified)
                    ComparisonOperator = numerical.Operator;
                UcumString = numerical.UcumString;
                Numerical = numerical;
            }

            public override string ToString()
            {
                return string.Format("{0}{1} ({2})",
                                     ComparisonOperator.HasValue
                                        ? string.Format("{0} ", OperatorToString(ComparisonOperator.Value, true))
                                        : "",
                                     Value, UcumString);
            }
        }

        internal class IntervalListItem : ComparableListItem
        {
            public double MinValue { get; private set; }
            public double MaxValue { get; private set; }
            public ComparisonOperator MinOperator { get; private set; }
            public ComparisonOperator MaxOperator { get; private set; }
            public string UcumString { get; private set; }
            public Interval Interval { get; private set; }

            internal IntervalListItem(Interval interval)
            {
                MinValue = interval.MinValue;
                MaxValue = interval.MaxValue;
                MinOperator = interval.MinOperator;
                MaxOperator = interval.MaxOperator;
                UcumString = interval.UcumString;
                Interval = interval;
            }

            public override string ToString()
            {
                Debug.Assert(MinValue <= MaxValue, "AIM Template: MinValue of an interval is greater than MaxValue");

                // Min and max are the same
                if (MinValue == MaxValue)
                {
                    Debug.Assert(MinOperator == MaxOperator, "AIM Template: Comparison operators don't match for equal interval values");

                    return string.Format("{0} {1} ({2})", OperatorToString(MinOperator, true), MinValue, UcumString);
                }

                if (MinValue == double.MinValue)
                    return string.Format("{0} {1} ({2})", OperatorToString(MaxOperator, true), MaxValue, UcumString);

                if (MaxValue == double.MaxValue)
                    return string.Format("{0} {1} ({2})", OperatorToString(MinOperator, true), MinValue, UcumString);

                // Min and max are both valid values
                if (MinOperator == ComparisonOperator.Equal || MinOperator == ComparisonOperator.NotEqual ||
                    MinOperator == ComparisonOperator.LessThan || MinOperator == ComparisonOperator.LessThanEqual ||
                    MaxOperator == ComparisonOperator.Equal || MaxOperator == ComparisonOperator.NotEqual ||
                    MaxOperator == ComparisonOperator.GreaterThan || MaxOperator == ComparisonOperator.GreaterThanEqual)
                {
                    //Debug.Assert(false, "AIM Template: Invalid use of interval operators");
                }
                return string.Format("{0} {1} ({2}) and {3} {4} ({5})",
                                     OperatorToString(MinOperator, true), MinValue, UcumString,
                                     OperatorToString(MaxOperator, false), MaxValue, UcumString);
            }
        }

        internal class QuantileListItem : ComparableListItem
        {
            internal QuantileListItem(int bin)
            {
                Bin = bin;
            }

            public int Bin { get; private set; }

            public override string ToString()
            {
                return string.Format("Bin {0}", Bin);
            }
        }

        internal class ScaleListItem : ComparableListItem
        {
            public ScaleListItem(ScaleLevel scaleLevel)
            {
                Value = scaleLevel.Value;
                Description = scaleLevel.ValueDescription;
                ScaleLevel = scaleLevel;
            }

            public string Description { get; private set; }
            public string Value { get; private set; }
            public ScaleLevel ScaleLevel { get; private set; }

            public override string ToString()
            {
                if (string.IsNullOrEmpty(Description))
                    return string.Format("{0}", Value);

                return string.Format("{0} ({1})", Value, Description);
            }
        }

        internal class CodeSequenceListItem : ComparableListItem
        {
            private readonly StandardCodedTerm _value;

            public CodeSequenceListItem(StandardCodedTerm newValue)
            {
                _value = newValue;
            }

            public TemplateTree.StandardCodedTerm Value
            {
                get { return _value; }
            }

            public override string ToString()
            {
                return _value == null ? "------" : _value.CodeMeaning;
            }
        }

        public void NotifyIfInvalid()
        {
            if (!CharacteristicQuantification.Valid)
                Background = new SolidColorBrush(Color.FromRgb(255, 255, 0));
        }

        public void UpdateValid()
        {
            if (CharacteristicQuantification.Valid)
                Background = _originalBackground;
        }

        public List<IValidTreeControl> ChildControls
        {
            get { return new List<IValidTreeControl>(); }
        }

        public string NodeName
        {
            get { return CharacteristicQuantification.Name; }
        }

        public bool Valid
        {
            get { return CharacteristicQuantification.Valid; }
        }
    }
}
