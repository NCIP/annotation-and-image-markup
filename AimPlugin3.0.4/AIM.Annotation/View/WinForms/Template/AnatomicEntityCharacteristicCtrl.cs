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
using System.Drawing;
using System.Windows.Forms;

using ClearCanvas.Common.Utilities;

using AIM.Annotation.Template;

namespace AIM.Annotation.View.WinForms.Template
{
	internal partial class AnatomicEntityCharacteristicCtrl : UserControl, IComponentQuestionDetails
	{
		internal event EventHandler<AnatomicEntityCharacteristicEventArgs> AnatomicEntityCharacteristicChanged;
		private readonly SimpleQuestionControl _simpleQuestion;
		private double? _confidence;
		private readonly List<AllowedTerm1> _availableQuantifications;
		private readonly bool _shouldDisplay;
		private readonly int _minCardinality;
		private readonly int _maxCardinality;
		private readonly Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>> _selectedCharacteristicQuantifications =
			new Dictionary<StandardValidTerm, List<aim_dotnet.ICharacteristicQuantification>>();

		private bool _fireChangeEvent = true;

		public AnatomicEntityCharacteristicCtrl(AnatomicEntityCharacteristic anatomicEntityCharacteristic)
		{
			InitializeComponent();

			Debug.Assert(anatomicEntityCharacteristic != null, "AnatomicEntityCharacteristic must exist");

			_availableQuantifications = anatomicEntityCharacteristic.AllowedTerm;
			_shouldDisplay = anatomicEntityCharacteristic.ShouldDisplay;
			_minCardinality = anatomicEntityCharacteristic.MinCardinality;
			_maxCardinality = anatomicEntityCharacteristic.MaxCardinality;

			var initialSelectionList = InitialSelection;

			SuspendLayout();

			_simpleQuestion = new SimpleQuestionControl(
				anatomicEntityCharacteristic.Label,
				ComponentUtilities.ValidTermToStandardValidTerm(anatomicEntityCharacteristic.QuestionType),
				anatomicEntityCharacteristic.ExplanatoryText,
				ComponentUtilities.AllowedTerms1ToValidTermList(_availableQuantifications),
				null,
				initialSelectionList,
				_minCardinality,
				_maxCardinality,
				anatomicEntityCharacteristic.ItemNumber,
				anatomicEntityCharacteristic.AnnotatorConfidence,
				true,
				_shouldDisplay);
			_simpleQuestion.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			_simpleQuestion.Margin = new Padding(4);
			_simpleQuestion.Location = new Point(0, 0);
			_simpleQuestion.Name = "_simpleQuestion";
			_simpleQuestion.Size = new Size(Width, _simpleQuestion.Height);
			_simpleQuestion.TabIndex = 0;
			_simpleQuestion.SelectedResponseChanged += OnSelectedAnatomicEntityCharacteristicChanged;

			Controls.Add(_simpleQuestion);
			Height += _simpleQuestion.Height;

			CreateQiantificationDetailsControls(initialSelectionList);

			ResumeLayout(false);
			PerformLayout();
		}

		#region IComponentQuestionDetails Members

		public ComponentQuestionType QuestionType
		{
			get { return ComponentQuestionType.AnatomicEntity; }
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
			FireAnatomicEnityCharacteristicChangedEvent();
		}

		private void OnSelectedAnatomicEntityCharacteristicChanged(object sender, ResponseChangedEventArgs e)
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

			FireAnatomicEnityCharacteristicChangedEvent();
		}

		private void OnCharacteristicQuantificationChanged(object sender, CharacteristicQuantificationDetailsControl.CharacteristicQuantificationChangedEventArgs e)
		{
			Debug.Assert(e.ParentCharacteristicCode != null, "Code for the parent characteristic cannot be null");

			_selectedCharacteristicQuantifications[e.ParentCharacteristicCode] = e.CharacteristicQuantifications;

			FireAnatomicEnityCharacteristicChangedEvent();
		}

		public List<aim_dotnet.AnatomicEntityCharacteristic> SelectedAnatomicEntityCharacteristics
		{
			get
			{
				var anatomicEntityCharacteristics = new List<aim_dotnet.AnatomicEntityCharacteristic>();
				if (_selectedCharacteristicQuantifications.Count > 0)
				{
					foreach (var selectedCharacteristicQuantification in _selectedCharacteristicQuantifications)
					{
						if (selectedCharacteristicQuantification.Value == null || selectedCharacteristicQuantification.Value.Count == 0)
						{
							anatomicEntityCharacteristics.Clear();
							break;
						}
						var characteristicCode = CodeUtils.ToStandardCodeSequence(selectedCharacteristicQuantification.Key);
						anatomicEntityCharacteristics.Add(
							new aim_dotnet.AnatomicEntityCharacteristic
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
							anatomicEntityCharacteristics.Add(
								new aim_dotnet.AnatomicEntityCharacteristic
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
							anatomicEntityCharacteristics.Add(
								new aim_dotnet.AnatomicEntityCharacteristic
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

				return anatomicEntityCharacteristics;
			}
		}

		private void FireAnatomicEnityCharacteristicChangedEvent()
		{
			if (!_fireChangeEvent)
				return;
			EventsHelper.Fire(AnatomicEntityCharacteristicChanged, this,
							  new AnatomicEntityCharacteristicEventArgs(QuestionNumber, SelectedAnatomicEntityCharacteristics));
		}
	}

	internal class AnatomicEntityCharacteristicEventArgs : EventArgs
	{
		public int QuestionNumber { get; private set; }
		public List<aim_dotnet.AnatomicEntityCharacteristic> NewAnatomicEntityCharacteristic { get; private set; }

		public AnatomicEntityCharacteristicEventArgs(int questionNumber, List<aim_dotnet.AnatomicEntityCharacteristic> anatomicEntityCharacteristics)
		{
			QuestionNumber = questionNumber;
			NewAnatomicEntityCharacteristic = anatomicEntityCharacteristics;
		}
	}
}
