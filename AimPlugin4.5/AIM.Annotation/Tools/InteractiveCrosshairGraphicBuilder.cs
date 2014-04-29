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
using AIM.Annotation.Graphics;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InputManagement;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.ImageViewer.Tools.Standard;

namespace AIM.Annotation.Tools
{
	public class InteractiveCrosshairGraphicBuilder : InteractiveTextGraphicBuilder
	{
		private int _clickIndex = 0;

		public InteractiveCrosshairGraphicBuilder(UserCrosshairCalloutGraphic textCalloutGraphic) : base(textCalloutGraphic) { }

		internal new UserCrosshairCalloutGraphic Graphic
		{
			get { return (UserCrosshairCalloutGraphic)base.Graphic; }
		}

		protected override ITextGraphic FindTextGraphic()
		{
			IGraphic graphic = this.Graphic;
			while (graphic != null && !(graphic is UserCrosshairCalloutGraphic))
				graphic = graphic.ParentGraphic;
			if (graphic != null)
				return new TextGraphicProxy((UserCrosshairCalloutGraphic)graphic);
			return null;
		}

		public override bool Start(IMouseInformation mouseInformation)
		{
			if (_clickIndex == 0)
			{
				this.Graphic.CoordinateSystem = CoordinateSystem.Destination;
				this.Graphic.AnchorPoint = mouseInformation.Location;
				this.Graphic.TextLocation = mouseInformation.Location;
				this.Graphic.ResetCoordinateSystem();
			}
			else if (_clickIndex == 1)
			{
				this.NotifyGraphicComplete();
			}
			else
			{
				return false;
			}

			_clickIndex++;
			return true;
		}

		public override bool Track(IMouseInformation mouseInformation)
		{
			if (_clickIndex == 1)
			{
				this.Graphic.CoordinateSystem = CoordinateSystem.Destination;
				this.Graphic.TextLocation = mouseInformation.Location;
				this.Graphic.ResetCoordinateSystem();
				this.Graphic.Draw();
			}

			return true;
		}

		public override bool Stop(IMouseInformation mouseInformation)
		{
			return true;
		}

		/// <summary>
		/// Proxy class
		/// </summary>
		private class TextGraphicProxy : ITextGraphic
		{
			private readonly UserCrosshairCalloutGraphic _graphic;

			public TextGraphicProxy(UserCrosshairCalloutGraphic calloutGraphic)
			{
				this._graphic = calloutGraphic;
			}

			#region ITextGraphic Members

			public string Text
			{
				get { return this._graphic.Text; }
				set { this._graphic.Text = value; }
			}

			public float SizeInPoints
			{
				get { return this._graphic.FontSize; }
				set { this._graphic.FontSize = value; }
			}

			public string Font
			{
				get { return this._graphic.FontName; }
				set { this._graphic.FontName = value; }
			}

			public SizeF Dimensions
			{
				get { return this._graphic.TextBoundingBox.Size; }
			}

			public PointF Location
			{
				get { return this._graphic.TextLocation; }
				set { this._graphic.TextLocation = value; }
			}

			#endregion

			#region IVectorGraphic Members

			public Color Color
			{
				get { return this._graphic.Color; }
				set { this._graphic.Color = value; }
			}

			public LineStyle LineStyle
			{
				get { return this._graphic.LineStyle; }
				set { this._graphic.LineStyle = value; }
			}

			#endregion

			#region IGraphic Members

			public IGraphic ParentGraphic
			{
				get { return this._graphic.ParentGraphic; }
			}

			public IPresentationImage ParentPresentationImage
			{
				get { return this._graphic.ParentPresentationImage; }
			}

			public IImageViewer ImageViewer
			{
				get { return this._graphic.ImageViewer; }
			}

			public bool Visible
			{
				get { return this._graphic.Visible; }
				set { this._graphic.Visible = value; }
			}

			public RectangleF BoundingBox
			{
				get { return this._graphic.TextBoundingBox; }
			}

			public CoordinateSystem CoordinateSystem
			{
				get { return this._graphic.CoordinateSystem; }
				set { this._graphic.CoordinateSystem = value; }
			}

			public SpatialTransform SpatialTransform
			{
				get { return this._graphic.SpatialTransform; }
			}

			public string Name
			{
				get { return this._graphic.Name; }
				set { this._graphic.Name = value; }
			}

			public bool HitTest(Point point)
			{
				return this._graphic.HitTest(point);
			}

			public PointF GetClosestPoint(PointF point)
			{
				return this._graphic.GetClosestPoint(point);
			}

			public void Move(SizeF delta)
			{
				this._graphic.Move(delta);
			}

			public void ResetCoordinateSystem()
			{
				this._graphic.ResetCoordinateSystem();
			}

			IGraphic IGraphic.Clone()
			{
				throw new NotSupportedException("Cloning an IGraphic through a proxy can lead to invalid references.");
			}

			public Roi GetRoi()
			{
				return this._graphic.GetRoi();
			}

			public event VisualStateChangedEventHandler VisualStateChanged
			{
				add { this._graphic.VisualStateChanged += value; }
				remove { this._graphic.VisualStateChanged -= value; }
			}

			#endregion

			#region IDrawable Members

			public event EventHandler Drawing
			{
				add { this._graphic.Drawing += value; }
				remove { this._graphic.Drawing -= value; }
			}

			public void Draw()
			{
				this._graphic.Draw();
			}

			#endregion

			#region IDisposable Members

			public void Dispose()
			{
				this._graphic.Dispose();
			}

			#endregion
		}
	}
}
