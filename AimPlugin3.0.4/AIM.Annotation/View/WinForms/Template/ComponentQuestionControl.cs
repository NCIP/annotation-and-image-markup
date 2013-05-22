//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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
