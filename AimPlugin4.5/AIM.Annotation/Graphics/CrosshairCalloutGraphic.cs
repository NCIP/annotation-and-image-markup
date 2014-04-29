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
using System.Drawing;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InputManagement;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.Mathematics;
using ClearCanvas.ImageViewer.Rendering;


namespace AIM.Annotation.Graphics
{
	[Cloneable]
	public class CrosshairCalloutGraphic : CompositeGraphic, ICalloutGraphic, IMemorable, IMouseButtonHandler, IExportedActionsProvider, ICursorTokenProvider
	{
		#region Private fields

		private event EventHandler _textLocationChanged;
		private event EventHandler _anchorPointChanged;

		[CloneIgnore]
		private IControlGraphic _textControlGraphic;

		[CloneIgnore]
		private IControlGraphic _pointControlGraphic;

		[CloneIgnore]
		private CrosshairGraphic _lineGraphic;

		#endregion

		/// <summary>
		/// Instantiates a new instance of <see cref="CalloutGraphic"/>.
		/// </summary>
		protected CrosshairCalloutGraphic() : base()
		{
			Initialize();
		}

		/// <summary>
		/// Instantiates a new instance of <see cref="CalloutGraphic"/>.
		/// </summary>
		/// <param name="text">The label text to display on the callout.</param>
		public CrosshairCalloutGraphic(string text) : this()
		{
			this.Text = text;
		}

		/// <summary>
		/// Cloning constructor.
		/// </summary>
		protected CrosshairCalloutGraphic(CrosshairCalloutGraphic source, ICloningContext context)
			: base()
		{
			context.CloneFields(source, this);
		}

		/// <summary>
		/// Gets the underlying <see cref="ITextGraphic"/> representing the text display of the callout.
		/// </summary>
		protected ITextGraphic TextGraphic
		{
			get { return _textControlGraphic.Subject as InvariantTextPrimitive; }
		}

		/// <summary>
		/// Gets the <see cref="IControlGraphic"/> controlling the <see cref="TextGraphic"/>.
		/// </summary>
		protected IControlGraphic TextControlGraphic
		{
			get { return _textControlGraphic; }
		}

		/// <summary>
		/// Gets the underlying <see cref="IPointGraphic"/> representing the anchor point of the callout.
		/// </summary>
		protected IPointGraphic PointGraphic
		{
			get { return _pointControlGraphic.Subject as AnchorPointGraphic; }
		}

		/// <summary>
		/// Gets the <see cref="IControlGraphic"/> controlling the M<see cref="PointGraphic"/>.
		/// </summary>
		protected IControlGraphic PointControlGraphic
		{
			get { return _pointControlGraphic; }
		}

		/// <summary>
		/// Gets or sets the callout text.
		/// </summary>
		public string Text
		{
			get { return this.TextGraphic.Text; }
			set { this.TextGraphic.Text = value; }
		}

		/// <summary>
		/// Gets or sets the location of the center of the text.
		/// </summary>
		/// <remarks>
		/// This property is in either source or destination coordinates depending on the value of <see cref="IGraphic.CoordinateSystem"/>.
		/// </remarks>
		public PointF TextLocation
		{
			get { return this.TextGraphic.Location; }
			set { this.TextGraphic.Location = value; }
		}

		/// <summary>
		/// Gets or sets the point where the callout is anchored.
		/// </summary>
		/// <remarks>
		/// This property is in either source or destination coordinates depending on the value of <see cref="IGraphic.CoordinateSystem"/>.
		/// </remarks>
		public PointF AnchorPoint
		{
			get { return this.PointGraphic.Point; }
			set { this.PointGraphic.Point = value; }
		}

		/// <summary>
		/// Gets the point where the callout line attaches to the text graphic.
		/// </summary>
		/// <remarks>
		/// The attachment point of the callout line is automatically
		/// calculated so that it appears as though it starts
		/// from the center of the text label.
		/// </remarks>
		public PointF AttachmentPoint
		{
			get { return _lineGraphic.StartPoint; }
		}

		/// <summary>
		/// Gets or sets the font name used to display the callout text.
		/// </summary>
		/// <remarks>
		/// The default font is Arial.
		/// </remarks>
		public string FontName
		{
			get { return this.TextGraphic.Font; }
			set { this.TextGraphic.Font = value; }
		}

		/// <summary>
		/// Gets or sets the font size in points used to display the callout text.
		/// </summary>
		/// <remarks>
		/// The default font size is 10 points.
		/// </remarks>
		public float FontSize
		{
			get { return this.TextGraphic.SizeInPoints; }
			set { this.TextGraphic.SizeInPoints = value; }
		}

		/// <summary>
		/// Gets or sets the line style.
		/// </summary>
		public LineStyle LineStyle
		{
			get { return _lineGraphic.LineStyle; }
			set { _lineGraphic.LineStyle = value; }
		}

		/// <summary>
		/// Gets or sets a value indicating whether or not to show an arrowhead on the end of the callout line.
		/// </summary>
		public bool ShowCrosshair
		{
			get { return _lineGraphic.ShowCrosshair; }
			set { _lineGraphic.ShowCrosshair = value; }
		}

		/// <summary>
		/// Gets or sets whether the line connecting the text callout to the crosshair is visible
		/// </summary>
		public bool ShowShaft
		{
			get { return _lineGraphic.ShaftVisible; }
			set
			{
				_lineGraphic.ShaftVisible = value;
				_textControlGraphic.Visible = value;
				TextGraphic.Visible = value;
			}
		}

		/// <summary>
		/// Gets the bounding rectangle of the text portion of the callout.
		/// </summary>
		/// <remarks>
		/// This property is in either source or destination coordinates depending on the value of <see cref="IGraphic.CoordinateSystem"/>.
		/// </remarks>
		public RectangleF TextBoundingBox
		{
			get { return _textControlGraphic.BoundingBox; }
		}

		/// <summary>
		/// Gets or sets the colour.
		/// </summary>
		public Color Color
		{
			get { return _lineGraphic.Color; }
			set
			{
				if (_lineGraphic.Color != value)
				{
					_lineGraphic.Color = _textControlGraphic.Color = this.TextGraphic.Color = this.PointGraphic.Color = value;
					this.OnColorChanged();
				}
			}
		}

		/// <summary>
		/// Occurs when the value of the <see cref="ICalloutGraphic.TextLocation"/> property changes.
		/// </summary>
		public event EventHandler TextLocationChanged
		{
			add { _textLocationChanged += value; }
			remove { _textLocationChanged -= value; }
		}

		/// <summary>
		/// Occurs when the value of the <see cref="ICalloutGraphic.AnchorPoint"/> property changes.
		/// </summary>
		public event EventHandler AnchorPointChanged
		{
			add { _anchorPointChanged += value; }
			remove { _anchorPointChanged -= value; }
		}

		#region Initialization

		private void Initialize()
		{
			if (_textControlGraphic == null)
			{
				_textControlGraphic = InitializeTextControlGraphic(new InvariantTextPrimitive());
				_textControlGraphic.Name = "Text";
				_textControlGraphic.Color = System.Drawing.Color.Yellow;
				this.Graphics.Add(_textControlGraphic);
			}

			this.TextGraphic.VisualStateChanged += OnTextVisualStateChanged;

			if (_pointControlGraphic == null)
			{
				_pointControlGraphic = InitializePointControlGraphic(new AnchorPointGraphic());
				_pointControlGraphic.Name = "Point";
				this.Graphics.Add(_pointControlGraphic);
			}

			if (_lineGraphic == null)
			{
				_lineGraphic = new CrosshairGraphic(false);
				_lineGraphic.Name = "Line";
				_lineGraphic.Color = System.Drawing.Color.Yellow;
				_lineGraphic.LineStyle = LineStyle.Dash;
				Graphics.Add(_lineGraphic);
			}
		}

		/// <summary>
		/// Releases all resources used by this <see cref="CompositeGraphic"/>.
		/// </summary>
		protected override void Dispose(bool disposing)
		{
			TextGraphic.VisualStateChanged -= OnTextVisualStateChanged;
			base.Dispose(disposing);
		}

		/// <summary>
		/// Initializes the control chain for the text graphic portion of the callout.
		/// </summary>
		/// <remarks>
		/// The default implementation creates a <see cref="MoveControlGraphic"/> to allow the user to independently control moving the text portion.
		/// </remarks>
		/// <param name="textGraphic">The text graphic to be controlled.</param>
		/// <returns>A control graphic chain controlling the text graphic.</returns>
		protected virtual IControlGraphic InitializeTextControlGraphic(ITextGraphic textGraphic)
		{
			return new MoveControlGraphic(textGraphic);
		}

		/// <summary>
		/// Initializes the control chain for the anchor point of the callout.
		/// </summary>
		/// <remarks>
		/// The default implementation creates a pass-through <see cref="ControlGraphic"/> that has no user-interactive control methods of its own.
		/// </remarks>
		/// <param name="pointGraphic">The anchor point to be controlled.</param>
		/// <returns>A control graphic chain controlling the anchor point.</returns>
		protected virtual IControlGraphic InitializePointControlGraphic(IPointGraphic pointGraphic)
		{
			return new NullControlGraphic(pointGraphic);
		}

		[OnCloneComplete]
		private void OnCloneComplete()
		{
			_textControlGraphic = (CollectionUtils.SelectFirst(base.Graphics,
			                                                   delegate(IGraphic test) { return test.Name == "Text"; }) as IControlGraphic);

			_pointControlGraphic = (CollectionUtils.SelectFirst(base.Graphics,
			                                                    delegate(IGraphic test) { return test.Name == "Point"; }) as IControlGraphic);

			_lineGraphic = CollectionUtils.SelectFirst(base.Graphics,
			                                           delegate(IGraphic test) { return test.Name == "Line"; }) as CrosshairGraphic;

			Platform.CheckForNullReference(_lineGraphic, "_lineGraphic");
			Platform.CheckForNullReference(_pointControlGraphic, "_pointControlGraphic");
			Platform.CheckForNullReference(_textControlGraphic, "_textControlGraphic");

			Initialize();
		}

		#endregion

		#region Event Handlers

		/// <summary>
		/// Gets the point on the text graphic closest to the specified point in either source or destination coordinates.
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		private PointF GetTextClosestPoint(PointF point)
		{
			// force the text graphic to update its bounding box
			//_textControlGraphic.Draw();

			RectangleF boundingBox = _textControlGraphic.BoundingBox;
			boundingBox.Inflate(3, 3);

			PointF topLeft = new PointF(boundingBox.Left, boundingBox.Top);
			PointF topRight = new PointF(boundingBox.Right, boundingBox.Top);
			PointF bottomLeft = new PointF(boundingBox.Left, boundingBox.Bottom);
			PointF bottomRight = new PointF(boundingBox.Right, boundingBox.Bottom);
			PointF geoCenter = Vector.Midpoint(topLeft, bottomRight);
			PointF intersectionPoint;

			if (Vector.IntersectLineSegments(geoCenter, point, topLeft, topRight, out intersectionPoint))
				return intersectionPoint;

			if (Vector.IntersectLineSegments(geoCenter, point, bottomLeft, bottomRight, out intersectionPoint))
				return intersectionPoint;

			if (Vector.IntersectLineSegments(geoCenter, point, topLeft, bottomLeft, out intersectionPoint))
				return intersectionPoint;

			if (Vector.IntersectLineSegments(geoCenter, point, topRight, bottomRight, out intersectionPoint))
				return intersectionPoint;

			return point;
		}

		/// <summary>
		/// Fires the <see cref="Graphic.Drawing"/> event.  Should be called by an <see cref="IRenderer"/>
		/// for each object just before it is drawn/rendered, hence the reason it is public.
		/// </summary>
		public override void OnDrawing()
		{
			// resynchronize endpoints of the connecting line just before every draw...
			// small overhead price to pay for ensuring the callout line is always correct whether you moved the graphic or zoomed in/out
			this.CoordinateSystem = CoordinateSystem.Destination;
			this._lineGraphic.StartPoint = this.GetTextClosestPoint(this.AnchorPoint);
			this._lineGraphic.EndPoint = this.AnchorPoint;
			this.ResetCoordinateSystem();

			base.OnDrawing();
		}

		private void OnTextVisualStateChanged(object sender, VisualStateChangedEventArgs e)
		{
			switch (e.PropertyName)
			{
				case "Text":
					this.OnTextChanged();
					break;
				case "Location":
					this.OnTextLocationChanged();
					break;
			}
		}

		/// <summary>
		/// Called when the value of <see cref="Color"/> changes.
		/// </summary>
		protected virtual void OnColorChanged()
		{
			NotifyVisualStateChanged("Color");
		}

		/// <summary>
		/// Called when the value of <see cref="Text"/> changes.
		/// </summary>
		protected virtual void OnTextChanged()
		{
			NotifyVisualStateChanged("Text");
		}

		/// <summary>
		/// Called when the value of <see cref="TextLocation"/> changes.
		/// </summary>
		protected virtual void OnTextLocationChanged()
		{
			EventsHelper.Fire(_textLocationChanged, this, EventArgs.Empty);
			NotifyVisualStateChanged("TextLocation");
		}

		/// <summary>
		/// Called when the value of <see cref="AnchorPoint"/> changes.
		/// </summary>
		protected virtual void OnAnchorPointChanged()
		{
			EventsHelper.Fire(_anchorPointChanged, this, EventArgs.Empty);
			NotifyVisualStateChanged("AnchorPoint");
		}

		#endregion

		#region IMemorable Members

		/// <summary>
		/// Creates a memento of this object.
		/// </summary>
		/// <returns></returns>
		public virtual object CreateMemento()
		{
		    return new object();
		}

		/// <summary>
		/// Sets a memento for this object.
		/// </summary>
		/// <param name="memento"></param>
		public virtual void SetMemento(object memento)
		{
		}

		#endregion

		#region IMouseButtonHandler Members

		/// <summary>
		/// Called by the framework each time a mouse button is pressed.
		/// </summary>
		/// <remarks>
		/// As a general rule, if the <see cref="IMouseButtonHandler"/> object did anything as a result of this call, it must 
		/// return true.  If false is returned, <see cref="IMouseButtonHandler.Start"/> is called on other <see cref="IMouseButtonHandler"/>s
		/// until one returns true.
		/// </remarks>
		/// <returns>
		/// True if the <see cref="IMouseButtonHandler"/> did something as a result of the call, 
		/// and hence would like to receive capture.  Otherwise, false.
		/// </returns>
		bool IMouseButtonHandler.Start(IMouseInformation mouseInformation)
		{
			return _textControlGraphic.Start(mouseInformation) || _pointControlGraphic.Start(mouseInformation);
		}

		/// <summary>
		/// Called by the framework when the mouse has moved.
		/// </summary>
		/// <remarks>
		/// A button does not necessarily have to be down for this message to be called.  The framework can
		/// call it any time the mouse moves.
		/// </remarks>
		/// <returns>True if the message was handled, otherwise false.</returns>
		bool IMouseButtonHandler.Track(IMouseInformation mouseInformation)
		{
			return _textControlGraphic.Track(mouseInformation) || _pointControlGraphic.Track(mouseInformation);
		}

		/// <summary>
		/// Called by the framework when the mouse button is released.
		/// </summary>
		/// <returns>
		/// True if the framework should <b>not</b> release capture, otherwise false.
		/// </returns>
		bool IMouseButtonHandler.Stop(IMouseInformation mouseInformation)
		{
			return _textControlGraphic.Stop(mouseInformation) || _pointControlGraphic.Stop(mouseInformation);
		}

		/// <summary>
		/// Called by the framework to let <see cref="IMouseButtonHandler"/> perform any necessary cleanup 
		/// when capture is going to be forcibly released.
		/// </summary>
		/// <remarks>
		/// It is important that this method is implemented correctly and doesn't simply do nothing when it is inappropriate
		/// to do so, otherwise odd behaviour may be experienced.
		/// </remarks>
		void IMouseButtonHandler.Cancel()
		{
			_textControlGraphic.Cancel();
			_pointControlGraphic.Cancel();
		}

		/// <summary>
		/// Allows the <see cref="IMouseButtonHandler"/> to override certain default framework behaviour.
		/// </summary>
		MouseButtonHandlerBehaviour IMouseButtonHandler.Behaviour
		{
			get { return _textControlGraphic.Behaviour; }
		}

		#endregion

		#region IExportedActionsProvider Members

		/// <summary>
		/// Gets a set of exported <see cref="IAction"/>s.
		/// </summary>
		/// <param name="site">The action model site at which the actions should reside.</param>
		/// <param name="mouseInformation">The mouse input when the action model was requested, such as in response to a context menu request.</param>
		/// <returns>A set of exported <see cref="IAction"/>s.</returns>
		public virtual IActionSet GetExportedActions(string site, IMouseInformation mouseInformation)
		{
			if (_textControlGraphic.HitTest(mouseInformation.Location))
				return _textControlGraphic.GetExportedActions(site, mouseInformation);
			if (_pointControlGraphic.HitTest(mouseInformation.Location))
				return _pointControlGraphic.GetExportedActions(site, mouseInformation);
			return new ActionSet();
		}

		#endregion

		#region ICursorTokenProvider Members

		/// <summary>
		/// Gets the cursor token to be shown at the current mouse position.
		/// </summary>
		public virtual CursorToken GetCursorToken(Point point)
		{
			if (_textControlGraphic.HitTest(point))
				return _textControlGraphic.GetCursorToken(point);
			if (_pointControlGraphic.HitTest(point))
				return _pointControlGraphic.GetCursorToken(point);
			return null;
		}

		#endregion

		#region NullControlGraphic Class

		[Cloneable]
		private class NullControlGraphic : ControlGraphic
		{
			public NullControlGraphic(IGraphic graphic) : base(graphic) {}

			/// <summary>
			/// Cloning constructor.
			/// </summary>
			/// <param name="source">The source object from which to clone.</param>
			/// <param name="context">The cloning context object.</param>
			protected NullControlGraphic(NullControlGraphic source, ICloningContext context)
				: base(source, context)
			{
				context.CloneFields(source, this);
			}
		}

		#endregion

		#region AnchorPointGraphic Class

		[Cloneable(true)]
		private class AnchorPointGraphic : Graphic, IPointGraphic
		{
			public event EventHandler PointChanged;

			private PointF _point;

			public AnchorPointGraphic() : base() {}

			public Color Color
			{
				get { return Color.Empty; }
				set { }
			}

			public LineStyle LineStyle
			{
				get { return LineStyle.Solid; }
				set { }
			}

			public PointF Point
			{
				get
				{
					if (this.CoordinateSystem == CoordinateSystem.Destination)
						return this.SpatialTransform.ConvertToDestination(_point);
					return _point;
				}
				set
				{
					if (this.CoordinateSystem == CoordinateSystem.Destination)
						value = this.SpatialTransform.ConvertToSource(value);

					if (!FloatComparer.AreEqual(_point, value))
					{
						_point = value;
						EventsHelper.Fire(PointChanged, this, EventArgs.Empty);
						base.NotifyVisualStateChanged("Point");
					}
				}
			}

			public override RectangleF BoundingBox
			{
				get { return new RectangleF(this.Point, SizeF.Empty); }
			}

			public override PointF GetClosestPoint(PointF point)
			{
				return this.Point;
			}

			public override bool HitTest(Point point)
			{
				return FloatComparer.AreEqual(_point, this.SpatialTransform.ConvertToSource(point));
			}

			public override void Move(SizeF delta)
			{
				this.Point += delta;
			}
		}

		#endregion
	}
}
