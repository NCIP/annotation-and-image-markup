#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

using ClearCanvas.Common.Utilities;

using AIM.Annotation.Template;

namespace AIM.Annotation.View.WinForms.Template
{
	internal partial class ImagingObservationCharacteristicCtrl : UserControl, IComponentQuestionDetails
	{
		internal event EventHandler<ImagingObservationCharacteristicEventArgs> ImagingObservationCharacteristicChanged;
		private readonly SimpleQuestionControl _simpleQuestion;
		private double? _confidence;
		private readonly List<AllowedTerm1> _availableQuantifications;
		private readonly bool _shouldDisplay;
		private readonly int _minCardinality;
		private readonly int _maxCardinality;
		private readonly Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>> _selectedCharacteristicQuantifications =
			new Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>>();

		private bool _fireChangeEvent = true;

		public ImagingObservationCharacteristicCtrl(ImagingObservationCharacteristic imagingObservationCharacteristic)
		{
			InitializeComponent();

			Debug.Assert(imagingObservationCharacteristic != null, "ImagingObservationCharacteristic must exist");

			_availableQuantifications = imagingObservationCharacteristic.AllowedTerm;
			_shouldDisplay = imagingObservationCharacteristic.ShouldDisplay;
			_minCardinality = imagingObservationCharacteristic.MinCardinality;
			_maxCardinality = imagingObservationCharacteristic.MaxCardinality;

			var initialSelectionList = InitialSelection;

			SuspendLayout();

			_simpleQuestion = new SimpleQuestionControl(
				imagingObservationCharacteristic.Label,
				ComponentUtilities.ValidTermToStandardValidTerm(imagingObservationCharacteristic.QuestionType),
				imagingObservationCharacteristic.ExplanatoryText,
				ComponentUtilities.AllowedTerms1ToValidTermList(_availableQuantifications),
				null,
				initialSelectionList,
				_minCardinality,
				_maxCardinality,
				imagingObservationCharacteristic.ItemNumber,
				imagingObservationCharacteristic.AnnotatorConfidence,
				true,
				_shouldDisplay);
			_simpleQuestion.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			_simpleQuestion.Margin = new Padding(4);
			_simpleQuestion.Location = new Point(0, 0);
			_simpleQuestion.Name = "_simpleQuestion";
			_simpleQuestion.Size = new Size(Width, _simpleQuestion.Height);
			_simpleQuestion.TabIndex = 0;
			_simpleQuestion.SelectedResponseChanged += OnSelectedImagingObservationCharacteristicChanged;

			Controls.Add(_simpleQuestion);
			Height += _simpleQuestion.Height;

			CreateQiantificationDetailsControls(initialSelectionList);

			ResumeLayout(false);
			PerformLayout();
		}

		#region IComponentQuestionDetails Members

		public ComponentQuestionType QuestionType
		{
			get { return ComponentQuestionType.ImagingObservation; }
		}

		public int QuestionNumber
		{
			get { return _simpleQuestion.QuestionNumber; }
		}

		#endregion

		private IEnumerable<CharacteristicQuantificationDetailsControl> QuantificationDetailsControls
		{
			get
			{
				foreach (Control control in Controls)
				{
					if (control is CharacteristicQuantificationDetailsControl)
						yield return (CharacteristicQuantificationDetailsControl)control;
				}
			}
		}

		private List<StandardValidTerm> InitialSelection
		{
			get
			{
				List<StandardValidTerm> initialSelectionList = null;
				if (!_shouldDisplay && _availableQuantifications != null)
				{
					initialSelectionList = ComponentUtilities.AllowedTerms1ToValidTermList(_availableQuantifications);
					var count = 0;
					CollectionUtils.Remove(initialSelectionList,
					                       (StandardValidTerm codeSequence) =>
					                       count++ > _maxCardinality - _minCardinality);
				}

				return initialSelectionList;
			}
		}

		private void CreateQiantificationDetailsControls(List<StandardValidTerm> selectedAllowedTerms)
		{
			if (selectedAllowedTerms == null)
				return;

			var ptX = _simpleQuestion.Location.X + 15;
			var ptY = _simpleQuestion.Location.Y + _simpleQuestion.Height;
			var tabIndex = _simpleQuestion.TabIndex + 1;

			foreach (var codeSequence in selectedAllowedTerms)
			{
				foreach (var quantification in _availableQuantifications)
				{
					if (codeSequence.StandardCodeSequence.CodeValue == quantification.CodeValue && codeSequence.StandardCodeSequence.CodeMeaning == quantification.CodeMeaning &&
						codeSequence.StandardCodeSequence.CodingSchemeDesignator == quantification.CodingSchemeDesignator && codeSequence.StandardCodeSequence.CodingSchemeVersion == quantification.CodingSchemeVersion)
					{
						if (quantification.CharacteristicQuantification != null)
						{
							_selectedCharacteristicQuantifications[codeSequence] = null;
							var charQuantification = new CharacteristicQuantificationDetailsControl(codeSequence, quantification.CharacteristicQuantification);
							charQuantification.Anchor = AnchorStyles.Left | AnchorStyles.Right;
							charQuantification.Margin = new Padding(4);
							charQuantification.Location = new Point(ptX, ptY);
							charQuantification.Name = string.Format("charQuantification{0}", tabIndex);
							charQuantification.Size = new Size(Width - ptX, charQuantification.Height);
							charQuantification.TabIndex = tabIndex++;
							charQuantification.CharacteristicQuantificationChanged += OnCharacteristicQuantificationChanged;
							ptY += charQuantification.Height;

							Controls.Add(charQuantification);
							Height += charQuantification.Height;
						}
						break;
					}
				}
			}
		}

		public void Reset()
		{
			_fireChangeEvent = false;
			_simpleQuestion.Reset(InitialSelection);
			foreach (var detailsControl in QuantificationDetailsControls)
			{
				detailsControl.Reset();
			}
			_fireChangeEvent = true;
			FireImagingObservationCharacteristicChangedEvent();
		}

		private void OnSelectedImagingObservationCharacteristicChanged(object sender, ResponseChangedEventArgs e)
		{
			_selectedCharacteristicQuantifications.Clear();
			_confidence = e.Confidence;

			SuspendLayout();

			var oldQuantificationDetailsControls = new List<CharacteristicQuantificationDetailsControl>(QuantificationDetailsControls);
			foreach (var detailsControl in oldQuantificationDetailsControls)
			{
				detailsControl.CharacteristicQuantificationChanged -= OnCharacteristicQuantificationChanged;
				Controls.Remove(detailsControl);
				Height -= detailsControl.Height;
			}
			CollectionUtils.ForEach(oldQuantificationDetailsControls, ctrl => ctrl.Dispose());
			oldQuantificationDetailsControls.Clear();

			CreateQiantificationDetailsControls(e.Responses);

			ResumeLayout(false);
			PerformLayout();

			FireImagingObservationCharacteristicChangedEvent();
		}

		private void OnCharacteristicQuantificationChanged(object sender, CharacteristicQuantificationDetailsControl.CharacteristicQuantificationChangedEventArgs e)
		{
			Debug.Assert(e.ParentCharacteristicCode != null, "Code for the parent characteristic cannot be null");

			_selectedCharacteristicQuantifications[e.ParentCharacteristicCode] = e.CharacteristicQuantifications;

			FireImagingObservationCharacteristicChangedEvent();
		}

		public List<aim_dotnet.ImagingObservationCharacteristic> SelectedImagingObservationCharacteristics
		{
			get
			{
				var imagingObservationCharacteristics = new List<aim_dotnet.ImagingObservationCharacteristic>();
				if (_selectedCharacteristicQuantifications.Count > 0)
				{
					foreach (var selectedCharacteristicQuantification in _selectedCharacteristicQuantifications)
					{
						if (selectedCharacteristicQuantification.Value == null || selectedCharacteristicQuantification.Value.Count == 0)
						{
							imagingObservationCharacteristics.Clear();
							break;
						}
						var characteristicCode = CodeUtils.ToStandardCodeSequence(selectedCharacteristicQuantification.Key);
						imagingObservationCharacteristics.Add(
							new aim_dotnet.ImagingObservationCharacteristic
								{
									CodeValue = characteristicCode.CodeValue,
									CodeMeaning = characteristicCode.CodeMeaning,
									CodingSchemeDesignator = characteristicCode.CodingSchemeDesignator,
									CodingSchemeVersion = characteristicCode.CodingSchemeVersion,
									Label = _simpleQuestion.Label,
									AnnotatorConfidence = _confidence,
									CharacteristicQuantificationCollection = selectedCharacteristicQuantification.Value
								});
					}
				}
				else
				{
					if (_simpleQuestion.SelectedAnswers == null)
					{
						if (_minCardinality == 0)
						{
							imagingObservationCharacteristics.Add(
								new aim_dotnet.ImagingObservationCharacteristic
									{
										CodeValue = AimAnnotationComponent.NullCodeValue.CodeValue,
										CodeMeaning = AimAnnotationComponent.NullCodeValue.CodeMeaning,
										CodingSchemeDesignator = AimAnnotationComponent.NullCodeValue.CodingSchemeDesignator,
										CodingSchemeVersion = AimAnnotationComponent.NullCodeValue.CodingSchemeVersion,
										Label = _simpleQuestion.Label
									});
						}
					}
					else
					{
						foreach (var validTerm in _simpleQuestion.SelectedAnswers)
						{
							var codeSequence = CodeUtils.ToStandardCodeSequence(validTerm);
							imagingObservationCharacteristics.Add(
								new aim_dotnet.ImagingObservationCharacteristic
									{
										CodeValue = codeSequence.CodeValue,
										CodeMeaning = codeSequence.CodeMeaning,
										CodingSchemeDesignator = codeSequence.CodingSchemeDesignator,
										CodingSchemeVersion = codeSequence.CodingSchemeVersion,
										Label = _simpleQuestion.Label,
										AnnotatorConfidence = _confidence
									});
						}
					}
				}

				return imagingObservationCharacteristics;
			}
		}

		private void FireImagingObservationCharacteristicChangedEvent()
		{
			if (!_fireChangeEvent)
				return;
			EventsHelper.Fire(ImagingObservationCharacteristicChanged, this,
							  new ImagingObservationCharacteristicEventArgs(QuestionNumber, SelectedImagingObservationCharacteristics));
		}
	}

	internal class ImagingObservationCharacteristicEventArgs : EventArgs
	{
		public int QuestionNumber { get; private set; }
		public List<aim_dotnet.ImagingObservationCharacteristic> NewImagingObservationCharacteristic { get; private set; }

		public ImagingObservationCharacteristicEventArgs(int questionNumber, List<aim_dotnet.ImagingObservationCharacteristic> imagingObservationCharacteristics)
		{
			QuestionNumber = questionNumber;
			NewImagingObservationCharacteristic = imagingObservationCharacteristics;
		}
	}
}
