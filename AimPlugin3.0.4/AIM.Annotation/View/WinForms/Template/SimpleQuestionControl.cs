//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Threading;
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms.Template
{
	internal partial class SimpleQuestionControl : UserControl
	{
		internal event EventHandler<ResponseChangedEventArgs> SelectedResponseChanged;
		private readonly Control _questionControl;
		private readonly ConfidenceControl _confidenceControl;
		private readonly int _questionNumber;
		private readonly StandardValidTerm _questionType;
		private List<StandardValidTerm> _selectedAnswers;
		private readonly int _maxNumberOfAnswers;
		private bool _fireChangeEvent = true;
		private readonly List<string> _staticDisplayItems;

		public SimpleQuestionControl(
			string label,
			StandardValidTerm questionType,
			string description,
			List<StandardValidTerm> answers,
			List<StandardCodeSequence> nonQuantifableAnswers,
			List<StandardValidTerm> initialSelection,
			int minCardinality, int maxCardinality,
			int questionNumber, bool hasConfidence,
			bool addFirstDefaultItem,
			bool shouldDisplay) :
			this(
				label,
				questionType,
				description,
				answers,
				nonQuantifableAnswers,
				initialSelection,
				minCardinality,
				maxCardinality,
				questionNumber,
				hasConfidence,
				addFirstDefaultItem,
				shouldDisplay,
				null) { }

		public SimpleQuestionControl(
			string label,
			StandardValidTerm questionType,
			string description,
			List<StandardValidTerm> answers,
			List<StandardCodeSequence> nonQuantifableAnswers,
			List<StandardValidTerm> initialSelection,
			int minCardinality, int maxCardinality,
			int questionNumber, bool hasConfidence,
			bool addFirstDefaultItem,
			bool shouldDisplay,
			List<string> staticDisplayItems)
		{
			Platform.CheckForNullReference(answers, "answers");

			InitializeComponent();

			_questionType = questionType;
			_lblEntity.Text = _questionType == null
								? label
								: CodeUtils.ToStringBuilder(_questionType, new StringBuilder()).ToString();
			_lblEntity.ToolTipText = SplitIntoLines(description);
			_lblEntity.ShowToolTipChanged += OnLabelShowToolTipChanged;
			_lblEntity.TabStop = false;

			_questionNumber = questionNumber;

			Debug.Assert(maxCardinality - minCardinality >= 0, "MinCardinality must be less or equal to MaxCardinality in a question");
			_maxNumberOfAnswers = Math.Max(1, Math.Min(answers.Count, maxCardinality));

			var availableAnswers = new List<StandardValidTerm>(answers);
			if (nonQuantifableAnswers != null)
			{
				Debug.Assert(false, "Non-quantifieables should not really be here");
				availableAnswers.InsertRange(0, ComponentUtilities.ToStandardValidTermList(nonQuantifableAnswers));
			}

			_selectedAnswers = initialSelection;
			_staticDisplayItems = staticDisplayItems;

			if (shouldDisplay)
			{
				SuspendLayout();

				_questionControl = InitializeResponseControl(availableAnswers, initialSelection, addFirstDefaultItem);
				Controls.Add(_questionControl);
				Height += _questionControl.Height + 3;

				if (hasConfidence)
				{
					_confidenceControl = InitializeConfidenceControl();
					Controls.Add(_confidenceControl);
					Height += _confidenceControl.Height + 3;
				}

				ResumeLayout(false);
				PerformLayout();
			}
			else
			{
				if (initialSelection == null || initialSelection.Count == 0)
					Platform.Log(LogLevel.Error,
								 "Template data error: no default values are provided for questions that are not going to be displayed. Template answers are never going to be valid");
			}
		}

		private Control InitializeResponseControl(List<StandardValidTerm> codeList, List<StandardValidTerm> initialSelection, bool addFirstDefault)
		{
			var ptX = _lblEntity.Location.X + 3;
			var ptY = _lblEntity.Location.Y + _lblEntity.Height;
			if (_staticDisplayItems != null)
			{
				var staticLines = String.Empty;
				foreach (var staticDisplayItem in _staticDisplayItems)
					staticLines += staticDisplayItem + Environment.NewLine;

				var label = new Label
				{
					Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right,
					Margin = new Padding(4),
					Location = new System.Drawing.Point(ptX, ptY),
					Name = "staticDisplayItemLabel"
				};
				label.AutoSize = true;
				label.Text = staticLines;

				return label;
			}

			if (_maxNumberOfAnswers > 1)
			{
				var chklistEntity = new CheckedListBox();
				chklistEntity.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
				chklistEntity.FormattingEnabled = true;
				chklistEntity.Margin = new Padding(4);
				chklistEntity.Location = new System.Drawing.Point(ptX, ptY);
				chklistEntity.IntegralHeight = false;
				chklistEntity.Name = "chklistEntity";
				var ctrlHeight = (codeList == null ? 1 : Math.Max(1, codeList.Count)) * (chklistEntity.ItemHeight + 2) + chklistEntity.ItemHeight / 2;
				chklistEntity.Size = new System.Drawing.Size(Width - ptX, ctrlHeight);
				chklistEntity.TabIndex = 1;
				chklistEntity.CheckOnClick = true;

				foreach (var validTerm in codeList)
				{
					var idx = chklistEntity.Items.Add(new ValidTermListItem(validTerm));
					var sequence = validTerm;
					if (initialSelection != null && CollectionUtils.Contains(initialSelection, cs => cs.Equals(sequence)))
						chklistEntity.SetItemChecked(idx, true);
				}
				chklistEntity.ItemCheck += OnItemCheck;

				return chklistEntity;
			}

			var ddlEntity = new ComboBox();
			ddlEntity.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			ddlEntity.DropDownStyle = ComboBoxStyle.DropDownList;
			ddlEntity.FormattingEnabled = true;
			ddlEntity.Margin = new Padding(4);
			ddlEntity.Location = new System.Drawing.Point(ptX, ptY);
			ddlEntity.Name = "ddlEntity";
			ddlEntity.Size = new System.Drawing.Size(Width - ptX, ddlEntity.Height);
			ddlEntity.TabIndex = 1;

			if (addFirstDefault)
				ddlEntity.Items.Add(new ValidTermListItem(null));
			foreach (var validTerm in codeList)
			{
				var idx = ddlEntity.Items.Add(new ValidTermListItem(validTerm));
				var term = validTerm;
				if (initialSelection != null && ddlEntity.SelectedIndex == -1 && CollectionUtils.Contains(initialSelection, cs => cs.Equals(term)))
					ddlEntity.SelectedIndex = idx;
			}

			if (ddlEntity.SelectedIndex == -1 && ddlEntity.Items.Count > 0)
				ddlEntity.SelectedIndex = 0;

			ddlEntity.DropDown += OnDropDown;
			ddlEntity.SelectedIndexChanged += OnSelectedIndexChanged;

			return ddlEntity;
		}

		private ConfidenceControl InitializeConfidenceControl()
		{
			var previousCtrl = _questionControl ?? _lblEntity;
			var ptX = previousCtrl.Location.X;
			var ptY = previousCtrl.Location.Y + previousCtrl.Height + 3;
			var confidenceControl = new ConfidenceControl();
			confidenceControl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			confidenceControl.Location = new System.Drawing.Point(ptX, ptY);
			confidenceControl.TabIndex = previousCtrl.TabIndex + 1;
			confidenceControl.Size = new System.Drawing.Size(Width - ptX, confidenceControl.Height);
			confidenceControl.ConfidenceChanged += OnConfidenceChanged;

			return confidenceControl;
		}

		public bool HasMoreThanOneAnswer
		{
			get
			{
				if (_questionControl is ComboBox)
					return ((ComboBox)_questionControl).Items.Count > 1;
				if (_questionControl is CheckedListBox)
					return ((CheckedListBox)_questionControl).Items.Count > 1;
				return false;
			}
		}

		public int QuestionNumber
		{
			get { return _questionNumber; }
		}

		public string Label
		{
			get { return _lblEntity.Text; }
		}

		public List<StandardValidTerm> SelectedAnswers
		{
			get { return _selectedAnswers; }
			set
			{
				if (_selectedAnswers == value)
					return;

				_selectedAnswers = value;

				FireSelectedAnswerChanged();
			}
		}

		public void Reset(List<StandardValidTerm> selectedItems)
		{
			var hasChanges = false;
			var itemsToSelect = selectedItems ?? new List<StandardValidTerm>();

			_fireChangeEvent = false;
			if (_questionControl != null)
			{
				if (_questionControl is ComboBox)
				{
					var cmbQuestion = (ComboBox)_questionControl;
					if (cmbQuestion.Items.Count > 0)
					{
						if (itemsToSelect.Count == 0 && cmbQuestion.SelectedIndex != 0)
						{
							hasChanges = true;
							cmbQuestion.SelectedIndex = 0;
						}
						else
						{
							var listItem = cmbQuestion.SelectedItem as ValidTermListItem;
							if (listItem == null || listItem.Value == null || !CollectionUtils.Contains(itemsToSelect, code => code.Equals(listItem.Value)))
							{
								for (var idx = 0; idx < cmbQuestion.Items.Count; idx++)
								{
									var item = cmbQuestion.Items[idx] as ValidTermListItem;
									if (item != null && item.Value != null && CollectionUtils.Contains(itemsToSelect, code => code.Equals(item.Value)))
									{
										hasChanges = true;
										cmbQuestion.SelectedIndex = idx;
										break;
									}
								}
							}
						}
					}
				}
				else if (_questionControl is CheckedListBox)
				{
					var chkBox = (CheckedListBox)_questionControl;
					while (chkBox.CheckedIndices.Count > 0)
					{
						hasChanges = true;
						chkBox.SetItemChecked(chkBox.CheckedIndices[0], false);
					}
					if (itemsToSelect.Count > 0)
					{
						for (var idx = 0; idx < chkBox.Items.Count; idx++)
						{
							var listItem = chkBox.Items[idx] as ValidTermListItem;
							if (listItem != null && listItem.Value != null && CollectionUtils.Contains(itemsToSelect, code => code.Equals(listItem.Value)))
							{
								hasChanges = true;
								chkBox.SetItemChecked(idx, true);
							}
						}
					}
				}
			}
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
			var cmbBox = sender as ComboBox;
			if (cmbBox != null)
			{
				var listItem = cmbBox.SelectedItem as ValidTermListItem;
				if (listItem != null && listItem.Value != null)
					SelectedAnswers = new List<StandardValidTerm> { listItem.Value };
				else
					SelectedAnswers = null;
			}
		}

		private void OnItemCheck(object sender, ItemCheckEventArgs e)
		{
			if (sender is CheckedListBox)
			{
				var checkedListBox = (CheckedListBox)sender;
				if (e.NewValue == CheckState.Checked && checkedListBox.CheckedItems.Count >= _maxNumberOfAnswers)
				{
					e.NewValue = e.CurrentValue;
				}
				else
				{
					SynchronizationContext.Current.Post(
						delegate
						{ ProcessCheckedItems(checkedListBox); }
						, null);
				}
			}
		}

		private void ProcessCheckedItems(CheckedListBox checkListBox)
		{
			Debug.Assert(checkListBox != null);

			List<StandardValidTerm> validTerms = null;
			if (checkListBox.CheckedItems.Count > 0)
			{
				validTerms = new List<StandardValidTerm>();
				foreach (var checkedItem in checkListBox.CheckedItems)
				{
					ValidTermListItem validTermListItem = checkedItem as ValidTermListItem;
					if (validTermListItem != null && validTermListItem.Value != null)
						validTerms.Add(validTermListItem.Value);
				}
			}
			SelectedAnswers = validTerms == null || validTerms.Count == 0 ? null : validTerms;
		}

		private void OnConfidenceChanged(object sender, EventArgs e)
		{
			FireSelectedAnswerChanged();
		}

		private void OnLabelShowToolTipChanged(object sender, EventArgs e)
		{
			_toolTip.SetToolTip(_lblEntity, _lblEntity.ShowToolTip ? _lblEntity.ToolTipText : null);
		}

		private void FireSelectedAnswerChanged()
		{
			if (!_fireChangeEvent)
				return;

			if (_confidenceControl == null)
				EventsHelper.Fire(SelectedResponseChanged, this, new ResponseChangedEventArgs(SelectedAnswers, QuestionNumber));
			else
			{
				var confidence = _confidenceControl.Value;
				{
					EventsHelper.Fire(SelectedResponseChanged, this, new ResponseChangedEventArgs(SelectedAnswers, QuestionNumber, confidence));
				}
			}
		}

		private string SplitIntoLines(string inLine)
		{
			if (string.IsNullOrEmpty(inLine))
				return null;

			const int maxLineLength = 90;
			var words = inLine.Trim().Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
			var sb = new StringBuilder();
			var len = 0;
			foreach (var word in words)
			{
				if (len + word.Length > maxLineLength)
				{
					sb.Append(Environment.NewLine);
					len = word.Length;
				}
				else
				{
					len += word.Length + 1;
					sb.Append(" ");
				}
				sb.Append(word);
			}
			return sb.ToString().Trim();
		}
	}

	internal class ResponseChangedEventArgs : EventArgs
	{
		public List<StandardValidTerm> Responses { get; private set; }
		public int QuestionNumber { get; private set; }
		public double? Confidence { get; private set; }

		public ResponseChangedEventArgs(List<StandardValidTerm> answers, int questionNumber)
		{
			Responses = answers == null ? null : new List<StandardValidTerm>(answers);
			QuestionNumber = questionNumber;
		}

		public ResponseChangedEventArgs(List<StandardValidTerm> answers, int questionNumber, double confidence)
		{
			Responses = answers == null ? null : new List<StandardValidTerm>(answers);
			QuestionNumber = questionNumber;
			Confidence = confidence;
		}
	}
}
