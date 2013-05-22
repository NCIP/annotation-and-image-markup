//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using ClearCanvas.Common.Utilities;

using Component = AIM.Annotation.Template.Component;

namespace AIM.Annotation.View.WinForms.Template
{
	public partial class ComponentContainerControl : UserControl, INotifyPropertyChanged
	{
		public event EventHandler IsValidChanged;

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion

		private readonly Dictionary<int, List<aim_dotnet.AnatomicEntity>> _anatomicEntities = new Dictionary<int, List<aim_dotnet.AnatomicEntity>>();
		private readonly Dictionary<int, List<aim_dotnet.ImagingObservation>> _imagingObservations = new Dictionary<int, List<aim_dotnet.ImagingObservation>>();
		private readonly Dictionary<int, List<aim_dotnet.Inference>> _inferences = new Dictionary<int, List<aim_dotnet.Inference>>();
		private readonly Dictionary<int, List<aim_dotnet.Calculation>> _calculations = new Dictionary<int, List<aim_dotnet.Calculation>>();
		private readonly Dictionary<int, List<aim_dotnet.GeometricShape>> _geometricShapes = new Dictionary<int, List<aim_dotnet.GeometricShape>>();
		private Annotation.Template.Template _template;
		private readonly Label _lblEmptyTemplate;
		private bool _fireChangeEvent = true;
		private ComponentContainerScrollMessageFiler _filter;
		private bool _filterInstalled;

		public ComponentContainerControl()
		{
			InitializeComponent();

			SuspendLayout();

			_lblEmptyTemplate =
				new Label
					{
						Text = @"No template is selected or template is empty",
						Location = new Point(10, 10),
						AutoSize = true
					};

			Controls.Add(_lblEmptyTemplate);

			ResumeLayout(false);
			PerformLayout();

			HandleDestroyed += OnHandleDestroyed;
		}

		public Annotation.Template.Template SelectedTemplate
		{
			get { return _template; }
			set
			{
				if (_template != value)
				{
					_template = value;
					SuspendLayout();

					if (Controls.Contains(_lblEmptyTemplate))
						Controls.Remove(_lblEmptyTemplate);

					var oldComponentQuestionControls = new List<ComponentQuestionControl>(ComponentQuestionControls);
					foreach (var component in oldComponentQuestionControls)
					{
						component.ComponentChanged -= OnComponentDataChanged;
						component.SizeChanged -= OnControlSizeChanged;
						Controls.Remove(component);
					}
					Controls.Clear();

					AutoScrollPosition = new Point(0, 0);
					_anatomicEntities.Clear();
					_imagingObservations.Clear();
					_inferences.Clear();
					_calculations.Clear();
					_geometricShapes.Clear();

					if (_template == null || _template.Components == null || _template.Components.Count == 0)
					{
						Controls.Add(_lblEmptyTemplate);
					}
					else
					{
						var ptX = Margin.Left;
						var ptY = Margin.Top;
						var tabIndex = 0;

						var sortedComponents = CollectionUtils.Sort(_template.Components, (comp1, comp2) => comp1.ItemNumber.CompareTo(comp2.ItemNumber));
						string prevGroupLabel = null;
						var labelCount = 0;
						foreach (var component in sortedComponents)
						{
							const int groupShiftX = 10;
							var widthDecrement = 0;
							var curGroupLabel = component.GroupLabel == null ? null : component.GroupLabel.Trim();
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
									ptY += groupLabel.Height;
								}
								ptX += groupShiftX;
								widthDecrement = groupShiftX;
							}
							prevGroupLabel = curGroupLabel;

							var componentQuestionControl = new ComponentQuestionControl(component);
							componentQuestionControl.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
							componentQuestionControl.Margin = new Padding(4);
							componentQuestionControl.Location = new Point(ptX, ptY);
							componentQuestionControl.Name = string.Format("componentQuestionControl{0}", tabIndex);
							componentQuestionControl.Size = new Size(Width - Margin.Horizontal - widthDecrement, componentQuestionControl.Height);
							componentQuestionControl.TabIndex = tabIndex++;
							componentQuestionControl.ComponentChanged += OnComponentDataChanged;
							componentQuestionControl.SizeChanged += OnControlSizeChanged;
							ptY += componentQuestionControl.Height + 3;

							Controls.Add(componentQuestionControl);

							if (!string.IsNullOrEmpty(curGroupLabel))
								ptX -= groupShiftX;

							var oldFireChangeEvent = _fireChangeEvent;
							_fireChangeEvent = false;
							_fireChangeEvent = oldFireChangeEvent;
						}
					}
					ResumeLayout(false);
					PerformLayout();

					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedAnatomicEntities"));
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedImagingObservations"));
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedInferences"));
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedCalculations"));
					EventsHelper.Fire(IsValidChanged, this, EventArgs.Empty);
				}
			}
		}

		public bool IsValid
		{
			get
			{
				foreach (var component in SelectedTemplate.Components)
				{
					var curItemNumber = component.ItemNumber;
					if (!CollectionUtils.Contains(_anatomicEntities.Keys, itemNumber => itemNumber == curItemNumber) &&
						!CollectionUtils.Contains(_imagingObservations.Keys, itemNumber => itemNumber == curItemNumber) &&
						!CollectionUtils.Contains(_inferences.Keys, itemNumber => itemNumber == curItemNumber) &&
						!CollectionUtils.Contains(_calculations.Keys, itemNumber => itemNumber == curItemNumber) &&
						!CollectionUtils.Contains(_geometricShapes.Keys, itemNumber => itemNumber == curItemNumber))
						return false;
				}
				return true;
			}
			set { }
		}

		public List<aim_dotnet.AnatomicEntity> SelectedAnatomicEntities
		{
			get { return SortDictionaryAndFlattend(_anatomicEntities); }
			set { }
		}

		public List<aim_dotnet.ImagingObservation> SelectedImagingObservations
		{
			get { return SortDictionaryAndFlattend(_imagingObservations); }
			set { }
		}

		public List<aim_dotnet.Inference> SelectedInferences
		{
			get { return SortDictionaryAndFlattend(_inferences); }
			set { }
		}

		public List<aim_dotnet.Calculation> SelectedCalculations
		{
			get { return null; }
			set { }
		}

		public List<aim_dotnet.GeometricShape> SelectedGeometricShapes
		{
			get { return null; }
			set { }
		}

		public List<T> SortDictionaryAndFlattend<T>(Dictionary<int, List<T>> dictionary)
		{
			if (dictionary == null)
				return null;

			var sortedList = new List<T>();
			var dictKeys = CollectionUtils.Sort(dictionary.Keys, (i1, i2) => i1.CompareTo(i2));
			foreach (var idx in dictKeys)
			{
				sortedList = CollectionUtils.Concat<T>(
					new[]
						{
							sortedList,
							dictionary[idx]
						});
			}
			return sortedList;
		}

		private IEnumerable<ComponentQuestionControl> ComponentQuestionControls
		{
			get
			{
				foreach (Control component in Controls)
				{
					if (component is ComponentQuestionControl)
						yield return (ComponentQuestionControl)component;
				}
			}
		}

		public void Reset()
		{
			var oldFireChangeEvent = _fireChangeEvent;
			_fireChangeEvent = false;

			foreach (var questionControl in ComponentQuestionControls)
				questionControl.Reset();

			_fireChangeEvent = oldFireChangeEvent;
			if (_fireChangeEvent)
			{
				EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedAnatomicEntities"));
				EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedImagingObservations"));
				EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedInferences"));
				EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedCalculations"));
				EventsHelper.Fire(IsValidChanged, this, EventArgs.Empty);
			}
		}

		private void OnControlSizeChanged(object sender, EventArgs e)
		{
			var senderCtrl = sender as Control;
			if (senderCtrl == null)
				return;

			var nextCtrlY = 0;
			CollectionUtils.ForEach<Control>(
				Controls,
				ctrl =>
					{
						if (senderCtrl.Location.Y < ctrl.Location.Y)
							nextCtrlY = nextCtrlY == 0 ? ctrl.Location.Y : Math.Min(nextCtrlY, ctrl.Location.Y);
					});

			if (nextCtrlY > 0)
			{
				var requiredAdjustment = nextCtrlY - senderCtrl.Location.Y - senderCtrl.Height;
				if (Math.Abs(requiredAdjustment) > 5)
				{
					CollectionUtils.ForEach<Control>(
						Controls,
						ctrl =>
							{
								if (ctrl.Location.Y > senderCtrl.Location.Y)
									ctrl.Location = new Point(ctrl.Location.X, ctrl.Location.Y - requiredAdjustment);
							});
				}
			}
		}

		private void OnComponentDataChanged(object sender, ComponentChangedEventArgs e)
		{
			if (e.AnatomicEntities != null)
			{
				if (e.AnatomicEntities.Count > 0)
					_anatomicEntities[e.ItemNumber] = e.AnatomicEntities;
				else
					_anatomicEntities.Remove(e.ItemNumber);

				if (_fireChangeEvent)
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedAnatomicEntities"));
			}
			else if (e.ImagingObservations != null)
			{
				if (e.ImagingObservations.Count > 0)
					_imagingObservations[e.ItemNumber] = e.ImagingObservations;
				else
					_imagingObservations.Remove(e.ItemNumber);

				if (_fireChangeEvent)
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedImagingObservations"));
			}
			else if (e.Inferences != null)
			{
				if (e.Inferences.Count > 0)
					_inferences[e.ItemNumber] = e.Inferences;
				else
					_inferences.Remove(e.ItemNumber);

				if (_fireChangeEvent)
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedInferences"));
			}
			else if (e.Calculations != null)
			{
				if (e.Calculations.Count > 0)
					_calculations[e.ItemNumber] = e.Calculations;
				else
					_calculations.Remove(e.ItemNumber);

				if (_fireChangeEvent)
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedCalculations"));
			}
			else if (e.GeometricShapes != null)
			{
				if (e.GeometricShapes.Count > 0)
					_geometricShapes[e.ItemNumber] = e.GeometricShapes;
				else
					_geometricShapes.Remove(e.ItemNumber);

				if (_fireChangeEvent)
					EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("SelectedGeometricShapes"));
			}

			if (_fireChangeEvent)
				EventsHelper.Fire(IsValidChanged, this, EventArgs.Empty);
		}


		#region Mouse Wheel Scrolling Support

		private bool _lastNotificationWasGotFocus = false;

		protected override void OnControlAdded(ControlEventArgs e)
		{
			SubscribeEvents(e.Control);
			base.OnControlAdded(e);
		}

		protected override void OnControlRemoved(ControlEventArgs e)
		{
			UnsubscribeEvents(e.Control);
			base.OnControlRemoved(e);
		}

		private void SubscribeEvents(Control control)
		{
			control.GotFocus += OnControlGotFocus;
			control.LostFocus += OnControlLostFocus;
			control.ControlAdded += OnControlAdded;
			control.ControlRemoved += OnControlRemoved;

			foreach (Control innerControl in control.Controls)
			{
				SubscribeEvents(innerControl);
			}
		}

		private void UnsubscribeEvents(Control control)
		{
			control.GotFocus -= OnControlGotFocus;
			control.LostFocus -= OnControlLostFocus;
			control.ControlAdded -= OnControlAdded;
			control.ControlRemoved -= OnControlRemoved;

			foreach (Control innerControl in control.Controls)
			{
				UnsubscribeEvents(innerControl);
			}
		}

		private void OnControlAdded(object sender, ControlEventArgs e)
		{
			SubscribeEvents(e.Control);
		}

		private void OnControlRemoved(object sender, ControlEventArgs e)
		{
			UnsubscribeEvents(e.Control);
		}

		protected override void OnGotFocus(EventArgs e)
		{
			CheckContainsFocus();
			base.OnGotFocus(e);
		}

		protected override void OnLostFocus(EventArgs e)
		{
			CheckLostFocus();
			base.OnLostFocus(e);
		}

		private void OnControlGotFocus(object sender, EventArgs e)
		{
			CheckContainsFocus();
		}

		private void OnControlLostFocus(object sender, EventArgs e)
		{
			CheckLostFocus();
		}

		private void CheckContainsFocus()
		{
			if (_lastNotificationWasGotFocus == false)
			{
				_lastNotificationWasGotFocus = true;
				OnContainsFocus();
			}
		}

		private void CheckLostFocus()
		{
			if (ContainsFocus == false)
			{
				_lastNotificationWasGotFocus = false;
				OnLostFocus();
			}
		}

		private void OnContainsFocus()
		{
			if (!_filterInstalled)
			{
				if (_filter == null)
					_filter = new ComponentContainerScrollMessageFiler(this);

				Application.AddMessageFilter(_filter);
				_filterInstalled = true;
			}
		}

		private void OnLostFocus()
		{
			if (_filterInstalled)
			{
				Application.RemoveMessageFilter(_filter);
				_filterInstalled = false;
			}
		}

		private void OnHandleDestroyed(object sender, EventArgs e)
		{
			if (_filterInstalled)
			{
				Application.RemoveMessageFilter(_filter);
				_filterInstalled = false;
				_filter = null;
			}
		}
		#endregion
	}

	internal class ComponentContainerScrollMessageFiler : IMessageFilter
	{
		[DllImport("user32.dll", CharSet = CharSet.Auto)]
		private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp);

		private const int WM_MOUSEWHEEL = 0x20A;
		private readonly ComponentContainerControl _containerControl;
		
		public ComponentContainerScrollMessageFiler(ComponentContainerControl containerControl)
		{
			_containerControl = containerControl;
		}

		public bool PreFilterMessage(ref Message m)
		{
			switch(m.Msg)
			{
				case WM_MOUSEWHEEL:
					var cursorPos = Cursor.Position;
					if (_containerControl.RectangleToScreen(_containerControl.ClientRectangle).Contains(cursorPos))
					{
						var ctrl = Control.FromHandle(m.HWnd);
						if ((ctrl == null ||
							 ((ctrl is ComboBox || ctrl is CheckedListBox || ctrl is TextBox) && 
							 !ctrl.RectangleToScreen(ctrl.ClientRectangle).Contains(cursorPos))) && 
							 !(ctrl is ComboBox && ((ComboBox)ctrl).DroppedDown))
						{
							SendMessage(_containerControl.Handle, m.Msg, m.WParam, m.LParam);
							return true;
						}
					}
					break;
			}

			return false;
		}
	}
}
