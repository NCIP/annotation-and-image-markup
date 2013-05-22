//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;

using ClearCanvas.Common.Utilities;

using AIM.Annotation.Template;

namespace AIM.Annotation.View.WinForms.Template
{
	internal partial class CharacteristicQuantificationDetailsControl : UserControl
	{
		internal event EventHandler<CharacteristicQuantificationChangedEventArgs> CharacteristicQuantificationChanged;

		private readonly StandardValidTerm _characteristicCode;
		private readonly CharacteristicQuantificationType _quantificationType;
		private readonly ConfidenceControl _confidenceControl;
		private object _selectedItem;
		private string _scaleComment;
		private string _scaleDescription;
		private bool _fireChangeEvent = true;

		public CharacteristicQuantificationDetailsControl(StandardValidTerm characteristicCode, CharacteristicQuantification characteristicQuantification)
		{
			InitializeComponent();

			_characteristicCode = characteristicCode;
			_txtName.Text = string.IsNullOrEmpty(characteristicQuantification.Name) ? @"Name is missing" : characteristicQuantification.Name;
			_quantificationType = IdentifyCharQuantificationType(characteristicQuantification);

			SuspendLayout();

			InitializeCharQuantificationControls(characteristicQuantification);

			if (characteristicQuantification.AnnotatorConfidence)
			{
				_confidenceControl = InitializeConfidenceControl();
				Controls.Add(_confidenceControl);
				Height += _confidenceControl.Height;
			}

			ResumeLayout(false);
			PerformLayout();
		}

		private CharacteristicQuantificationType IdentifyCharQuantificationType(CharacteristicQuantification characteristicQuantification)
		{
			Debug.Assert(characteristicQuantification.Numerical != null ||
				characteristicQuantification.Quantile != null ||
				characteristicQuantification.NonQuantifiable != null ||
				characteristicQuantification.Scale != null ||
				characteristicQuantification.Interval != null);

			if (characteristicQuantification.Numerical != null && characteristicQuantification.Numerical.Count != 0)
				return CharacteristicQuantificationType.Numerical;

			if (characteristicQuantification.Quantile != null)
				return CharacteristicQuantificationType.Quantile;

			if (characteristicQuantification.Scale!= null)
				return CharacteristicQuantificationType.Scale;

			if (characteristicQuantification.Interval!= null && characteristicQuantification.Interval.Count != 0)
				return CharacteristicQuantificationType.Interval;

			if (characteristicQuantification.NonQuantifiable != null)
				return CharacteristicQuantificationType.NonQuantifiable;

			return CharacteristicQuantificationType.NonQuantifiable;
		}

		private void InitializeCharQuantificationControls(CharacteristicQuantification characteristicQuantification)
		{
			var selectionItems = new List<object>();
			if (characteristicQuantification.NonQuantifiable != null && characteristicQuantification.NonQuantifiable.Count > 0)
			{

				selectionItems.Add(new CodeSequenceListItem(null));
				foreach (var nonQuantifiable in characteristicQuantification.NonQuantifiable)
				{
					selectionItems.Add(new CodeSequenceListItem(
											new StandardCodeSequence(nonQuantifiable.CodeValue, nonQuantifiable.CodeMeaning, nonQuantifiable.CodingSchemeDesignator,
																	 nonQuantifiable.CodingSchemeVersion)));
				}
			}

			switch(CharacteristicQuantificationType)
			{
				case CharacteristicQuantificationType.Numerical:
					{
						foreach (var numerical in characteristicQuantification.Numerical)
						{
							selectionItems.Add(new NumericalListItem(numerical.Value, numerical.Operator, numerical.UcumString));
						}
					}
					break;
				case CharacteristicQuantificationType.Quantile:
					{
						for (var i = 0; i < characteristicQuantification.Quantile.Bins; i++ )
						{
							selectionItems.Add(new QuantileListItem(i));
						}
					}
					break;
				case CharacteristicQuantificationType.Scale:
					{
						_scaleComment = characteristicQuantification.Scale.Comment;
						_scaleDescription = characteristicQuantification.Scale.Description;
						foreach (var ordinalLevel in characteristicQuantification.Scale.OrdinalLevel)
						{
							selectionItems.Add(new ScaleListItem(ordinalLevel.IntegerValue, ordinalLevel.Description));
						}
					}
					break;
				case CharacteristicQuantificationType.Interval:
					{
						foreach (var interval in characteristicQuantification.Interval)
						{
							selectionItems.Add(new IntervalListItem(interval.MinValue, interval.MaxValue, interval.MinOperator, interval.MaxOperator, interval.UcumString));
						}
					}
					break;
				case CharacteristicQuantificationType.NonQuantifiable:
					break;
			}

			var lastControl = LastControl;
			var ptX = _lblName.Location.X;
			var ptY = lastControl.Location.Y + lastControl.Height + lastControl.Margin.Bottom;

			var ddlQuantificationItems = new ComboBox();
			ddlQuantificationItems.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			ddlQuantificationItems.DropDownStyle = ComboBoxStyle.DropDownList;
			ddlQuantificationItems.FormattingEnabled = true;
			ddlQuantificationItems.Margin = new Padding(4);
			ddlQuantificationItems.Location = new System.Drawing.Point(ptX, ptY + ddlQuantificationItems.Margin.Top);
			ddlQuantificationItems.Name = "_ddlQuantificationItems";
			ddlQuantificationItems.Size = new System.Drawing.Size(Width - Margin.Horizontal, ddlQuantificationItems.Height);
			ddlQuantificationItems.TabIndex = lastControl.TabIndex + 1;

			foreach (var item in selectionItems)
				ddlQuantificationItems.Items.Add(item);
			if (ddlQuantificationItems.Items.Count > 0)
				ddlQuantificationItems.SelectedIndex = 0;
			ddlQuantificationItems.DropDown += OnDropDown;
			ddlQuantificationItems.SelectedIndexChanged += OnSelectedIndexChanged;

			Controls.Add(ddlQuantificationItems);
			Height += ddlQuantificationItems.Height + ddlQuantificationItems.Margin.Top;
		}

		private ConfidenceControl InitializeConfidenceControl()
		{
			int ptX, ptY, tabIndex;
			var lastControl = LastControl;
            Debug.Assert(lastControl != null, "Failed to locate previous control");
			if (lastControl == null)
			{
				ptX = 3;
				ptY = Margin.Top;
				tabIndex = 0;
			}
			else
			{
				ptX = _lblName.Location.X;
				ptY = lastControl.Location.Y + lastControl.Height;
				tabIndex = lastControl.TabIndex + 1;
			}

			var confidenceControl = new ConfidenceControl();
			confidenceControl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			confidenceControl.Location = new System.Drawing.Point(ptX, ptY);
			confidenceControl.TabIndex = tabIndex;
			confidenceControl.Size = new System.Drawing.Size(Width - Margin.Horizontal - ptX, confidenceControl.Height);
			confidenceControl.ConfidenceChanged += OnConfidenceChanged;
			return confidenceControl;
		}

		public CharacteristicQuantificationType CharacteristicQuantificationType
		{
			get { return _quantificationType; }
		}

		private Control LastControl
		{
			get
			{
				var maxY = 0;
				var lastControl = Controls.Count > 0 ? Controls[0] : null;
				CollectionUtils.ForEach(Controls, delegate(Control ctrl)
				{
					if (ctrl.Location.Y > maxY)
					{
						maxY = ctrl.Location.Y;
						lastControl = ctrl;
					}
				});

				return lastControl;
			}
		}

		public void Reset()
		{
			var hasChanges = false;
			_fireChangeEvent = false;

			CollectionUtils.ForEach(Controls,
									delegate(Control ctrl)
									{
										if (ctrl is ComboBox)
										{
											var cmbBox = (ComboBox)ctrl;
											if (cmbBox.Items.Count > 0 && cmbBox.SelectedIndex != 0)
											{
												hasChanges = true;
												cmbBox.SelectedIndex = 0;
											}
										}
									});
			if (_confidenceControl != null && _confidenceControl.Value != 1.0d)
			{
				hasChanges = true;
				_confidenceControl.Value = 1.0d;
			}
			_fireChangeEvent = true;

			if (hasChanges)
				FireSelectedAnswerChanged();
		}

		private void OnDropDown(object sender, EventArgs e)
		{
			var cmbBox = sender as ComboBox;
			if (cmbBox != null)
				cmbBox.DropDownWidth = AimWinFormsUtil.CalculateComboBoxDropdownWidth(cmbBox);
		}

		private void OnSelectedIndexChanged(object sender, EventArgs e)
		{
			var cmb = sender as ComboBox;
			_selectedItem = cmb == null ? null : cmb.SelectedItem;

			FireSelectedAnswerChanged();
		}

		private void OnItemCheck(object sender, ItemCheckEventArgs e)
		{
			SynchronizationContext.Current.Post(
				delegate
				{ FireSelectedAnswerChanged(); }
				, null);
		}

		private void OnConfidenceChanged(object sender, EventArgs e)
		{
			FireSelectedAnswerChanged();
		}

		private double? ConfidenceValue
		{
			get
			{
				return _confidenceControl != null ? _confidenceControl.Value : new double?();
			}
		}

		private void FireSelectedAnswerChanged()
		{
			if (!_fireChangeEvent)
				return;

			var confidence = ConfidenceValue;
			var selectedQuantifications = _selectedItem == null ? null : new List<aim_dotnet.ICharacteristicQuantification>();
			if (selectedQuantifications != null)
			{
				if (_selectedItem is CodeSequenceListItem)
				{
					var codeSequence = ((CodeSequenceListItem) _selectedItem).Value;
					if (codeSequence != null)
					{
						selectedQuantifications.Add(
							new aim_dotnet.NonQuantifiable
								{
									Name = _txtName.Text,
									CodeValue = codeSequence.CodeValue,
									CodeMeaning = codeSequence.CodeMeaning,
									CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
									CodingSchemeVersion = codeSequence.CodingSchemeVersion,
									AnnotatorConfidence = confidence
								}
							);
					}
				}
				else
				{
					switch (CharacteristicQuantificationType)
					{
						case CharacteristicQuantificationType.Numerical:
							{
								if (_selectedItem is NumericalListItem)
								{
									var numListItem = (NumericalListItem) _selectedItem;
									selectedQuantifications.Add(
										new aim_dotnet.Numerical
											{
												Name = _txtName.Text,
												Value = numListItem.Value,
												Operator = AimTemplateOpertorToAimSchema(numListItem.ComparisonOperator),
												UcumString = numListItem.UcumString,
												AnnotatorConfidence = confidence
											});
								}
								else
									Debug.Assert(false, "Unexpected list item type");
							}
							break;
						case CharacteristicQuantificationType.Quantile:
							{
								if (_selectedItem is QuantileListItem)
								{
									var quantileListItem = (QuantileListItem) _selectedItem;
									selectedQuantifications.Add(
										new aim_dotnet.Quantile
											{
												Name = _txtName.Text,
												Bin = quantileListItem.Bin,
												AnnotatorConfidence = confidence
											});
								}
								else
									Debug.Assert(false, "Unexpected list item type");
							}
							break;
						case CharacteristicQuantificationType.Scale:
							{
								if (_selectedItem is ScaleListItem)
								{
									var scaleListItem = (ScaleListItem) _selectedItem;
									selectedQuantifications.Add(
										new aim_dotnet.Scale
											{
												Name = _txtName.Text,
												Value = scaleListItem.Value.ToString(),
												Description = string.IsNullOrEmpty(scaleListItem.Description) ? _scaleDescription : scaleListItem.Description,
												Comment = _scaleComment,
												AnnotatorConfidence = confidence
											});
								}
								else
									Debug.Assert(false, "Unexpected list item type");
							}
							break;
						case CharacteristicQuantificationType.Interval:
							{
								if (_selectedItem is IntervalListItem)
								{
									var intervallListItem = (IntervalListItem) _selectedItem;
									selectedQuantifications.Add(
										new aim_dotnet.Interval
											{
												Name = _txtName.Text,
												MinValue = intervallListItem.MinValue,
												MaxValue = intervallListItem.MaxValue,
												MinOperator = AimTemplateOpertorToAimSchema(intervallListItem.MinOperator),
												MaxOperator = AimTemplateOpertorToAimSchema(intervallListItem.MaxOperator),
												UcumString = intervallListItem.UcumString,
												AnnotatorConfidence = confidence
											});
								}
								else
									Debug.Assert(false, "Unexpected list item type");
							}
							break;
						case CharacteristicQuantificationType.NonQuantifiable:
							break;
					}
				}
			}

			EventsHelper.Fire(CharacteristicQuantificationChanged, this, new CharacteristicQuantificationChangedEventArgs(_characteristicCode, selectedQuantifications));
		}

		private aim_dotnet.ComparisonOperatorIdentifier AimTemplateOpertorToAimSchema(ComparisonOperator? comparisonOperator)
		{
			if (comparisonOperator.HasValue)
			{
				switch (comparisonOperator.Value)
				{
					case ComparisonOperator.Equal:
						return aim_dotnet.ComparisonOperatorIdentifier.Equal;
					case ComparisonOperator.NotEqual:
						return aim_dotnet.ComparisonOperatorIdentifier.NotEqual;
					case ComparisonOperator.LessThan:
						return aim_dotnet.ComparisonOperatorIdentifier.LessThan;
					case ComparisonOperator.LessThanEqual:
						return aim_dotnet.ComparisonOperatorIdentifier.LessThanEqual;
					case ComparisonOperator.GreaterThan:
						return aim_dotnet.ComparisonOperatorIdentifier.GreaterThan;
					case ComparisonOperator.GreaterThanEqual:
						return aim_dotnet.ComparisonOperatorIdentifier.GreaterThanEqual;
					default:
						Debug.Assert(false, "Unknown operator in AIM Template schema");
						break;
				}
			}
			return aim_dotnet.ComparisonOperatorIdentifier.None;
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
		}

		internal class NumericalListItem : ComparableListItem
		{
			public double Value { get; set; }
			public ComparisonOperator? ComparisonOperator { get; set; }
			public string UcumString { get; set; }

			internal NumericalListItem(double value, string ucumString)
			{
				Value = value;
				UcumString = ucumString;
			}

			internal NumericalListItem(double value, ComparisonOperator comparisonOperator, string ucumString)
			{
				Value = value;
				ComparisonOperator = comparisonOperator;
				UcumString = ucumString;
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
			public double MinValue { get; set; }
			public double MaxValue { get; set; }
			public ComparisonOperator MinOperator { get; set; }
			public ComparisonOperator MaxOperator { get; set; }
			public string UcumString { get; set; }

			internal IntervalListItem(double minValue, double maxValue, ComparisonOperator minOperator, ComparisonOperator maxOperator, string ucumString)
			{
				MinValue = minValue;
				MaxValue = maxValue;
				MinOperator = minOperator;
				MaxOperator = maxOperator;
				UcumString = ucumString;
			}

			public override string ToString()
			{
				Debug.Assert(MinValue <= MaxValue, "AIM Template: MinValue of an interval is greater than MaxValue");
				if (MinValue == MaxValue)
				{
					Debug.Assert(MinOperator == MaxOperator, "AIM Template: Comparison operators don't match for equal interval values");
					return string.Format("{0} {1} ({2})", OperatorToString(MinOperator, true), MinValue, UcumString);
				}

				if (MinValue == double.MinValue)
					return string.Format("{0} {1} ({2})", OperatorToString(MaxOperator, true), MaxValue, UcumString);

				if (MaxValue == double.MaxValue)
					return string.Format("{0} {1} ({2})", OperatorToString(MinOperator, true), MinValue, UcumString);

				if (MinOperator == ComparisonOperator.Equal || MinOperator == ComparisonOperator.NotEqual ||
					MinOperator == ComparisonOperator.LessThan || MinOperator == ComparisonOperator.LessThanEqual ||
					MaxOperator == ComparisonOperator.Equal || MaxOperator == ComparisonOperator.NotEqual ||
					MaxOperator == ComparisonOperator.GreaterThan || MaxOperator == ComparisonOperator.GreaterThanEqual)
				{
					Debug.Assert(false, "AIM Template: Invalid use of interval operators");
				}
				return string.Format("{0} {1} ({2}) and {3} {4} ({5})",
				                     OperatorToString(MinOperator, true), MinValue, UcumString,
				                     OperatorToString(MaxOperator, false), MaxValue, UcumString);
			}
		}

		internal class QuantileListItem
		{
			private readonly int _bin;

			internal QuantileListItem(int bin)
			{
				_bin = bin;
			}

			public int Bin
			{
				get { return _bin; }
			}

			public override string ToString()
			{
				return string.Format("Bin {0}", _bin);
			}
		}

		internal class ScaleListItem
		{
			private readonly int _value;
			private readonly string _description;

			public ScaleListItem(int value, string description)
			{
				_value = value;
				_description = description;
			}

			public string Description
			{
				get { return _description; }
			}

			public int Value
			{
				get { return _value; }
			}

			public override string ToString()
			{
				if (string.IsNullOrEmpty(_description))
					return string.Format("{0}", _value);

				return string.Format("{0} ({1})", _value, _description);
			}
		}

		internal class CharacteristicQuantificationChangedEventArgs : EventArgs
		{
			public List<aim_dotnet.ICharacteristicQuantification> CharacteristicQuantifications { get; private set; }
			public StandardValidTerm ParentCharacteristicCode { get; private set; }

			internal CharacteristicQuantificationChangedEventArgs(StandardValidTerm characteristicCode, List<aim_dotnet.ICharacteristicQuantification> characteristicQuantifications)
			{
				ParentCharacteristicCode = characteristicCode;
				CharacteristicQuantifications = characteristicQuantifications;
			}
		}
	}
}
