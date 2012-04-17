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

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms.Template
{
	public partial class ComponentQuestionControl : UserControl
	{
		public event EventHandler<ComponentChangedEventArgs> ComponentChanged;

		private readonly SimpleQuestionControl _simpleQuestion;
		private readonly ComponentQuestionType _componentType;
		private readonly Annotation.Template.Component _component;
		private List<StandardValidTerm> _selectedValidTerms;
		private double? _confidence;
		private readonly Dictionary<int, List<aim_dotnet.AnatomicEntityCharacteristic>> _selectedAnatomicEntityCharacteristics;
		private readonly Dictionary<int, List<aim_dotnet.ImagingObservationCharacteristic>> _selectedImagingObservationCharacteristics;

		private bool _fireChangeEvent = true;

		public ComponentQuestionControl(Annotation.Template.Component component)
		{
			Platform.CheckForNullReference(component, "Component");

			InitializeComponent();

			_component = component;
			_selectedAnatomicEntityCharacteristics = new Dictionary<int, List<aim_dotnet.AnatomicEntityCharacteristic>>();
			_selectedImagingObservationCharacteristics = new Dictionary<int, List<aim_dotnet.ImagingObservationCharacteristic>>();

			var hasConfidence = false;
			if (component.AnatomicEntity != null)
			{
				_componentType = ComponentQuestionType.AnatomicEntity;
				hasConfidence = component.AnatomicEntity.AnnotatorConfidence;
			}
			else if (component.ImagingObservation != null)
			{
				_componentType = ComponentQuestionType.ImagingObservation;
				hasConfidence = component.ImagingObservation.AnnotatorConfidence;
			}
			else if (component.Inference != null)
			{
				_componentType = ComponentQuestionType.Inference;
				hasConfidence = component.Inference.AnnotatorConfidence;
			}
			else if (component.Calculation != null)
			{
				_componentType = ComponentQuestionType.Calculation;
			}
			else if (component.GeometricShapeSpecified)
				_componentType = ComponentQuestionType.GeometricShape;
			else
				Debug.Assert(false, "Unknown component type");

			var initialSelectionList = InitialSelection;
			var ptX = 0;
			var ptY = 0;
			var tabIndex = 0;

			SuspendLayout();

			List<string> staticDisplayItems = null;
			if (_componentType == ComponentQuestionType.GeometricShape && component.GeometricShapeSpecified)
			{
				staticDisplayItems = new List<string>();
				staticDisplayItems.Add(
					component.GeometricShape.ToString() +
					" Min: " + component.MinCardinality + 
					" Max: " + component.MaxCardinality);
			}
			if (component.Calculation != null && component.Calculation.CalculationTypes.Count > 0)
			{
				staticDisplayItems = new List<string>();
				foreach (var calculationType in component.Calculation.CalculationTypes)
					staticDisplayItems.Add(calculationType.CodeMeaning);
			}

			_simpleQuestion = new SimpleQuestionControl(
				component.Label,
				ComponentUtilities.ValidTermToStandardValidTerm(component.QuestionType),
				component.ExplanatoryText,
				ComponentUtilities.AllowedTermsToValidTermList(component.AllowedTerm),
				null,
				initialSelectionList,
				component.MinCardinality,
				component.MaxCardinality,
				component.ItemNumber,
				hasConfidence,
				true,
				component.ShouldDisplay,
				staticDisplayItems);
			_simpleQuestion.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			_simpleQuestion.Location = new Point(ptX, ptY);
			_simpleQuestion.Name = "_simpleQuestion";
			_simpleQuestion.Size = new Size(Width - ptX, _simpleQuestion.Height);
			_simpleQuestion.TabIndex = tabIndex++;
			_simpleQuestion.SelectedResponseChanged += OnAllowedTermSelected;
			ptX += 10;
			ptY += _simpleQuestion.Height;
			BorderStyle = BorderStyle.FixedSingle;

			Controls.Add(_simpleQuestion);
			Height += _simpleQuestion.Height;

			SelectedValidTerms = initialSelectionList;

			const int groupShiftX = 10;
			switch(ComponentType)
			{
				case ComponentQuestionType.AnatomicEntity:
					{
						var anatomicEntityCharacteristics =
							CollectionUtils.Sort(component.AnatomicEntity.AnatomicEntityCharacteristic, (aec1, aec2) => aec1.ItemNumber.CompareTo(aec2.ItemNumber));
						string prevGroupLabel = null;
						var labelCount = 0;
						var questionControlCount = 0;
						foreach (var anatomicEntityCharacteristic in anatomicEntityCharacteristics)
						{
							var curGroupLabel = anatomicEntityCharacteristic.GroupLabel == null ? null : anatomicEntityCharacteristic.GroupLabel.Trim();
							if (!string.IsNullOrEmpty(curGroupLabel))
							{
								if (prevGroupLabel != curGroupLabel)
								{
									var groupLabel = new Label();
									groupLabel.Text = curGroupLabel;
									groupLabel.Font = new Font(groupLabel.Font.FontFamily, 9.0F, FontStyle.Bold);
									groupLabel.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
									groupLabel.Location = new Point(ptX, ptY);
									groupLabel.Name = string.Format("groupLabel{0}", labelCount++);
									groupLabel.Size = new Size(Width - ptX, groupLabel.Height);
									groupLabel.AutoEllipsis = true;
									groupLabel.TextAlign = ContentAlignment.MiddleLeft;

									Controls.Add(groupLabel);
									Height += groupLabel.Height;
									ptY += groupLabel.Height;
								}
								ptX += groupShiftX;
							}
							prevGroupLabel = curGroupLabel;

							var anatomicEntityCtrl = new AnatomicEntityCharacteristicCtrl(anatomicEntityCharacteristic);
							anatomicEntityCtrl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
							anatomicEntityCtrl.Margin = new Padding(4);
							anatomicEntityCtrl.Location = new Point(ptX, ptY);
							anatomicEntityCtrl.Name = string.Format("anatomicEntityCtrl{0}", questionControlCount++);
							anatomicEntityCtrl.Size = new Size(Width - ptX, anatomicEntityCtrl.Height);
							anatomicEntityCtrl.TabIndex = tabIndex++;
							anatomicEntityCtrl.AnatomicEntityCharacteristicChanged += OnAnatomicEntityCharacteristicChanged;
							anatomicEntityCtrl.SizeChanged += OnQuestionDetailsCtrlSizeChanged;
							ptY += anatomicEntityCtrl.Height;

							Controls.Add(anatomicEntityCtrl);
							Height += anatomicEntityCtrl.Height;

							_selectedAnatomicEntityCharacteristics[anatomicEntityCtrl.QuestionNumber] = anatomicEntityCtrl.SelectedAnatomicEntityCharacteristics;
							Debug.Assert(_selectedAnatomicEntityCharacteristics[anatomicEntityCtrl.QuestionNumber] != null);

							if (!string.IsNullOrEmpty(curGroupLabel))
								ptX -= groupShiftX;
						}
					}
					break;
				case ComponentQuestionType.ImagingObservation:
					{
						var imagingObservationCharacteristics =
							CollectionUtils.Sort(component.ImagingObservation.ImagingObservationCharacteristic, (iec1, iec2) => iec1.ItemNumber.CompareTo(iec2.ItemNumber));
						string prevGroupLabel = null;
						var labelCount = 0;
						var questionControlCount = 0;
						foreach (var imagingObservationCharacteristic in imagingObservationCharacteristics)
						{
							var curGroupLabel = imagingObservationCharacteristic.GroupLabel == null ? null : imagingObservationCharacteristic.GroupLabel.Trim();
							if (!string.IsNullOrEmpty(curGroupLabel))
							{
								if (prevGroupLabel != curGroupLabel)
								{
									var groupLabel = new Label();
									groupLabel.Text = curGroupLabel;
									groupLabel.Font = new Font(groupLabel.Font.FontFamily, 9.0F, FontStyle.Bold);
									groupLabel.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
									groupLabel.Location = new Point(ptX, ptY);
									groupLabel.Name = string.Format("groupLabel{0}", labelCount++);
									groupLabel.Size = new Size(Width - ptX, groupLabel.Height);
									groupLabel.AutoEllipsis = true;
									groupLabel.TextAlign = ContentAlignment.MiddleLeft;

									Controls.Add(groupLabel);
									Height += groupLabel.Height;
									ptY += groupLabel.Height;
								}
								ptX += groupShiftX;
							}
							prevGroupLabel = curGroupLabel;

							var imagingObservationCtrl = new ImagingObservationCharacteristicCtrl(imagingObservationCharacteristic);
							imagingObservationCtrl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
							imagingObservationCtrl.Margin = new Padding(4);
							imagingObservationCtrl.Location = new Point(ptX, ptY);
							imagingObservationCtrl.Name = string.Format("imagingObservationCtrl{0}", questionControlCount++);
							imagingObservationCtrl.Size = new Size(Width - ptX, imagingObservationCtrl.Height);
							imagingObservationCtrl.TabIndex = tabIndex++;
							imagingObservationCtrl.ImagingObservationCharacteristicChanged += OnImagingObservationCharacteristicChanged;
							imagingObservationCtrl.SizeChanged += OnQuestionDetailsCtrlSizeChanged;
							ptY += imagingObservationCtrl.Height;

							Controls.Add(imagingObservationCtrl);
							Height += imagingObservationCtrl.Height;

							_selectedImagingObservationCharacteristics[imagingObservationCtrl.QuestionNumber] = imagingObservationCtrl.SelectedImagingObservationCharacteristics;
							Debug.Assert(_selectedImagingObservationCharacteristics[imagingObservationCtrl.QuestionNumber] != null);

							if (!string.IsNullOrEmpty(curGroupLabel))
								ptX -= groupShiftX;
						}
					}
					break;
				case ComponentQuestionType.Calculation:
					break;
				case ComponentQuestionType.GeometricShape:
					break;
			}

			ResumeLayout(false);
			PerformLayout();
		}

		private List<StandardValidTerm> InitialSelection
		{
			get
			{
				List<StandardValidTerm> initialSelectionList = null;
				if (_componentType == ComponentQuestionType.GeometricShape)
				{
					initialSelectionList = new List<StandardValidTerm> {
						new StandardValidTerm(new StandardCodeSequence("geoShape", _component.GeometricShape.ToString(), "AIM TMP"))
					};
				}
				else if (_componentType == ComponentQuestionType.Calculation)
				{
					initialSelectionList = new List<StandardValidTerm>();
					var requiredSelectedCount = _component.MaxCardinality - _component.MinCardinality + 1;
					foreach (var calculationType in _component.Calculation.CalculationTypes)
					{
						if (initialSelectionList.Count < requiredSelectedCount)
							initialSelectionList.Add(ComponentUtilities.ValidTermToStandardValidTerm(calculationType));
					}
				}
				else if (!_component.ShouldDisplay && _component.AllowedTerm != null)
				{
					initialSelectionList = ComponentUtilities.AllowedTermsToValidTermList(_component.AllowedTerm);
					var count = 0;
					CollectionUtils.Remove(initialSelectionList,
					                       (StandardValidTerm validTerm) =>
					                       count++ > _component.MaxCardinality - _component.MinCardinality);
				}

				return initialSelectionList;
			}
		}

		private ComponentQuestionType ComponentType
		{
			get { return _componentType; }
		}

		public int QuestionNumber
		{
			get { return _simpleQuestion.QuestionNumber; }
		}

		private List<StandardValidTerm> SelectedValidTerms
		{
			get
			{
				return _selectedValidTerms ??
					   (_component.MinCardinality == 0 ? new List<StandardValidTerm> { new StandardValidTerm(AimAnnotationComponent.NullCodeValue) } : new List<StandardValidTerm>());
			}
			set { _selectedValidTerms = value; }
		}

		public void Reset()
		{
			_fireChangeEvent = false;
			SelectedValidTerms = InitialSelection;
			_simpleQuestion.Reset(SelectedValidTerms);

			CollectionUtils.ForEach(Controls,
			                        ctrl =>
			                        	{
			                        		if (ctrl is AnatomicEntityCharacteristicCtrl)
			                        			((AnatomicEntityCharacteristicCtrl) ctrl).Reset();
			                        		else if (ctrl is ImagingObservationCharacteristicCtrl)
			                        			((ImagingObservationCharacteristicCtrl) ctrl).Reset();
			                        	});
			_fireChangeEvent = true;

			FireComponentChangedEvent();
		}

		public void UpdateDependentData()
		{
			FireComponentChangedEvent();
		}

		private void OnLoadComponentQuestionControl(object sender, EventArgs e)
		{
			System.Threading.SynchronizationContext.Current.Post(
				delegate
				{
					if (InitialSelection != null)
						FireComponentChangedEvent();
				}, null);
		}

		private void OnAllowedTermSelected(object sender, ResponseChangedEventArgs e)
		{
			SelectedValidTerms = e.Responses;
			_confidence = e.Confidence;

			FireComponentChangedEvent();
		}

		private void OnAnatomicEntityCharacteristicChanged(object sender, AnatomicEntityCharacteristicEventArgs e)
		{
			Debug.Assert(e.NewAnatomicEntityCharacteristic != null);
			_selectedAnatomicEntityCharacteristics[e.QuestionNumber] = e.NewAnatomicEntityCharacteristic;

			FireComponentChangedEvent();
		}

		private void OnImagingObservationCharacteristicChanged(object sender, ImagingObservationCharacteristicEventArgs e)
		{
			Debug.Assert(e.NewImagingObservationCharacteristic != null);
			_selectedImagingObservationCharacteristics[e.QuestionNumber] = e.NewImagingObservationCharacteristic;

			FireComponentChangedEvent();
		}

		private void OnQuestionDetailsCtrlSizeChanged(object sender, EventArgs e)
		{
			var senderCtrl = sender as Control;
			if (senderCtrl == null)
				return;

			Control nextControl = null;
			CollectionUtils.ForEach<Control>(Controls,
			                                 ctrl => nextControl =
			                                         ctrl.Location.Y > senderCtrl.Location.Y
			                                         	? (nextControl == null ? ctrl : (ctrl.Location.Y < nextControl.Location.Y ? ctrl : nextControl))
			                                         	: nextControl);
			if (nextControl == null)
			{
				var requiredHeight = senderCtrl.Location.Y + senderCtrl.Height;
				if (Math.Abs(Height - (requiredHeight)) > 5)
				{
					Height = requiredHeight;
				}
			}
			else
			{
				var requiredAdjustment = nextControl.Location.Y - senderCtrl.Location.Y - senderCtrl.Height;
				if (Math.Abs(requiredAdjustment) > 5)
				{
					CollectionUtils.ForEach<Control>(Controls,
					                                 ctrl =>
					                                 	{
					                                 		if (ctrl.Location.Y > senderCtrl.Location.Y)
					                                 			ctrl.Location = new Point(ctrl.Location.X, ctrl.Location.Y - requiredAdjustment);
					                                 	});
					Height -= requiredAdjustment;
				}
			}
		}

		private bool HasRequiredSelectedTerms()
		{
			switch (ComponentType)
			{
				case ComponentQuestionType.AnatomicEntity:
				case ComponentQuestionType.ImagingObservation:
					return SelectedValidTerms.Count >= Math.Min(_component.AllowedTerm.Count, _component.MinCardinality) &&
							   SelectedValidTerms.Count <= _component.MaxCardinality;
				case ComponentQuestionType.Inference:
				case ComponentQuestionType.Calculation:
				case ComponentQuestionType.GeometricShape:
					break;
				default:
					Debug.Assert(false, "Unknown component type");
					break;
			}

			return true;
		}

		private void FireComponentChangedEvent()
		{
			if (!_fireChangeEvent)
				return;

			if (ComponentType == ComponentQuestionType.AnatomicEntity)
			{
				var anatomicEntities = new List<aim_dotnet.AnatomicEntity>();
				var isValid = HasRequiredSelectedTerms();
				if (isValid)
				{
					foreach (var validTerm in SelectedValidTerms)
					{
						var anatomicEntity = CodeUtils.ToAnatomicEntity(CodeUtils.ToStandardCodeSequence(validTerm), _simpleQuestion.Label);
						anatomicEntity.AnnotatorConfidence = _confidence;
						var anatomicEntityCharacteristicIndecies =
							CollectionUtils.Sort(_selectedAnatomicEntityCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
						foreach (var characteristicIndex in anatomicEntityCharacteristicIndecies)
						{
							var index = characteristicIndex;
							var templateAnatomicEntityCharacteristic =
								CollectionUtils.SelectFirst(_component.AnatomicEntity.AnatomicEntityCharacteristic,
								                            item => item.ItemNumber == index);
							isValid = templateAnatomicEntityCharacteristic != null &&
							          _selectedAnatomicEntityCharacteristics[characteristicIndex].Count >=
							          Math.Min(templateAnatomicEntityCharacteristic.AllowedTerm.Count, templateAnatomicEntityCharacteristic.MinCardinality) &&
							          _selectedAnatomicEntityCharacteristics[characteristicIndex].Count <= templateAnatomicEntityCharacteristic.MaxCardinality;
							if (!isValid)
								break;

							anatomicEntity.AnatomicEntityCharacteristicCollection =
								CollectionUtils.Concat<aim_dotnet.AnatomicEntityCharacteristic>(
									anatomicEntity.AnatomicEntityCharacteristicCollection ?? new List<aim_dotnet.AnatomicEntityCharacteristic>(),
									_selectedAnatomicEntityCharacteristics[characteristicIndex]
									);
						}
						if (!isValid)
							break;

						anatomicEntities.Add(anatomicEntity);
					}

					if (!isValid)
						anatomicEntities.Clear();
				}
				EventsHelper.Fire(ComponentChanged, this, new ComponentChangedEventArgs(QuestionNumber, anatomicEntities));
			}
			else if (ComponentType == ComponentQuestionType.ImagingObservation)
			{
				var imagingObservations = new List<aim_dotnet.ImagingObservation>();
				var isValid = HasRequiredSelectedTerms();
				if (isValid)
				{
					foreach (var validTerm in SelectedValidTerms)
					{
						var imagingObservation = CodeUtils.ToImagingObservation(CodeUtils.ToStandardCodeSequence(validTerm), _simpleQuestion.Label);
						imagingObservation.AnnotatorConfidence = _confidence;

						var imagingObservationCharacteristicIndecies =
							CollectionUtils.Sort(_selectedImagingObservationCharacteristics.Keys, (i1, i2) => i1.CompareTo(i2));
						foreach (var characteristicIndex in imagingObservationCharacteristicIndecies)
						{
							var index = characteristicIndex;
							var templateImagingObservationCharacteristic =
								CollectionUtils.SelectFirst(_component.ImagingObservation.ImagingObservationCharacteristic,
								                            item => item.ItemNumber == index);
							isValid = templateImagingObservationCharacteristic != null &&
							          _selectedImagingObservationCharacteristics[characteristicIndex].Count >=
							          Math.Min(templateImagingObservationCharacteristic.AllowedTerm.Count, templateImagingObservationCharacteristic.MinCardinality) &&
							          _selectedImagingObservationCharacteristics[characteristicIndex].Count <= templateImagingObservationCharacteristic.MaxCardinality;
							if (!isValid)
								break;

							imagingObservation.ImagingObservationCharacteristicCollection =
								CollectionUtils.Concat<aim_dotnet.ImagingObservationCharacteristic>(
									imagingObservation.ImagingObservationCharacteristicCollection ?? new List<aim_dotnet.ImagingObservationCharacteristic>(),
									_selectedImagingObservationCharacteristics[characteristicIndex]
									);
						}
						if (!isValid)
							break;

						imagingObservations.Add(imagingObservation);
					}

					if (!isValid)
						imagingObservations.Clear();
				}
				EventsHelper.Fire(ComponentChanged, this, new ComponentChangedEventArgs(QuestionNumber, imagingObservations));
			}
			else if (ComponentType == ComponentQuestionType.Inference)
			{
				var inferences = new List<aim_dotnet.Inference>();
				foreach (var validTerm in SelectedValidTerms)
				{
					var inference = CodeUtils.ToInference(CodeUtils.ToStandardCodeSequence(validTerm));
					inference.AnnotatorConfidence = _confidence;
					inference.ImageEvidence = true;
					inferences.Add(inference);
				}

				EventsHelper.Fire(ComponentChanged, this, new ComponentChangedEventArgs(QuestionNumber, inferences));
			}
			else if (ComponentType == ComponentQuestionType.Calculation)
			{
				var calculations = new List<aim_dotnet.Calculation>();
				foreach (var validTerm in SelectedValidTerms)
				{
					var calculation = CodeUtils.ToCalculation(CodeUtils.ToStandardCodeSequence(validTerm));
					calculations.Add(calculation);
				}

				EventsHelper.Fire(ComponentChanged, this, new ComponentChangedEventArgs(QuestionNumber, calculations));
			}
			else if (ComponentType == ComponentQuestionType.GeometricShape)
			{
				var circle = new aim_dotnet.Circle();
				EventsHelper.Fire(ComponentChanged, this, new ComponentChangedEventArgs(QuestionNumber, new List<aim_dotnet.GeometricShape> { circle }));
			}
			else
				Debug.Assert(false, "Unknown component type in the Allowed Term");
		}
	}

	public class ComponentChangedEventArgs : EventArgs
	{
		public int ItemNumber { get; private set; }

		public List<aim_dotnet.AnatomicEntity> AnatomicEntities { get; private set; }
		public List<aim_dotnet.ImagingObservation> ImagingObservations { get; private set; }
		public List<aim_dotnet.Inference> Inferences { get; private set; }
		public List<aim_dotnet.Calculation> Calculations { get; private set; }
		public List<aim_dotnet.GeometricShape> GeometricShapes { get; private set; }

		public ComponentChangedEventArgs(int itemNumber, List<aim_dotnet.AnatomicEntity> anatomicEntities)
		{
			ItemNumber = itemNumber;
			AnatomicEntities = anatomicEntities;
		}

		public ComponentChangedEventArgs(int itemNumber, List<aim_dotnet.ImagingObservation> imagingObservations)
		{
			ItemNumber = itemNumber;
			ImagingObservations = imagingObservations;
		}

		public ComponentChangedEventArgs(int itemNumber, List<aim_dotnet.Inference> inferences)
		{
			ItemNumber = itemNumber;
			Inferences = inferences;
		}

		public ComponentChangedEventArgs(int itemNumber, List<aim_dotnet.Calculation> calculations)
		{
			ItemNumber = itemNumber;
			Calculations = calculations;
		}

		public ComponentChangedEventArgs(int itemNumber, List<aim_dotnet.GeometricShape> geometricShapes)
		{
			ItemNumber = itemNumber;
			GeometricShapes = geometricShapes;
		}
	}
}
