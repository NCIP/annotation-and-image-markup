#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

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
