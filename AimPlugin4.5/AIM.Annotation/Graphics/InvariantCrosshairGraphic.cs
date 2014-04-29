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

using System.Collections.Generic;
using System.Drawing;
using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.Mathematics;

namespace AIM.Annotation.Graphics
{
	class InvariantCrosshairGraphic : CompositeGraphic, IVectorGraphic
	{
		[CloneIgnore]
		private InvariantLinePrimitive _left;

		[CloneIgnore]
		private InvariantLinePrimitive _right;

		[CloneIgnore]
		private InvariantLinePrimitive _top;

		[CloneIgnore]
		private InvariantLinePrimitive _bottom;

		private PointF _point = PointF.Empty;
		private float _length = 15f;
		private float _gapLength = 5f;

		/// <summary>
		/// Constructs a new crosshair graphic with fixed screen size.
		/// </summary>
		public InvariantCrosshairGraphic()
		{
			Initialize();
		}

		/// <summary>
		/// Cloning constructor.
		/// </summary>
		protected InvariantCrosshairGraphic(InvariantCrosshairGraphic source, ICloningContext context)
		{
			context.CloneFields(source, this);
		}

		private void Initialize()
		{
			if (_left == null)
			{
				Graphics.Add(_left = new InvariantLinePrimitive());
				_left.InvariantBottomRight = PointF.Empty;
			}

			if (_right == null)
			{
				Graphics.Add(_right = new InvariantLinePrimitive());
				_right.InvariantBottomRight = PointF.Empty;
			}

			if (_top == null)
			{
				Graphics.Add(_top = new InvariantLinePrimitive());
				_top.InvariantBottomRight = PointF.Empty;
			}

			if (_bottom == null)
			{
				Graphics.Add(_bottom = new InvariantLinePrimitive());
				_bottom.InvariantBottomRight = PointF.Empty;
			}

			RecomputeCrosshair();
		}

		[OnCloneComplete]
		private void OnCloneComplete()
		{
			IList<IGraphic> lines = CollectionUtils.Select(base.Graphics,
														   delegate(IGraphic test) { return test is InvariantLinePrimitive; });

			_left = lines[0] as InvariantLinePrimitive;
			_right = lines[1] as InvariantLinePrimitive;
			_top = lines[2] as InvariantLinePrimitive;
			_bottom = lines[3] as InvariantLinePrimitive;

			Initialize();
		}

		/// <summary>
		/// Gets or sets the colour.
		/// </summary>
		public Color Color
		{
			get { return _left.Color; }
			set { _left.Color = _right.Color = _bottom.Color = _top.Color = value; }
		}

		/// <summary>
		/// Gets or sets the line style.
		/// </summary>
		public LineStyle LineStyle
		{
			get { return _left.LineStyle; }
			set { _left.LineStyle = _right.LineStyle = _top.LineStyle = _bottom.LineStyle = value; }
		}

		/// <summary>
		/// Gets or sets the location that the crosshair points to.
		/// </summary>
		/// <remarks>
		/// <para>This property specifies the point that the crosshair points to,
		/// as well as the point to which it is fixed. As the parent zoom changes,
		/// the screen size of crosshair will remain the same, and this point will
		/// remain pointing to the same location in the parent graphic.</para>
		/// <para>This property can be specified in either source or destination
		/// coordinates depending on the value of
		/// <see cref="IGraphic.CoordinateSystem"/>.</para>
		/// </remarks>
		public PointF Point
		{
			get
			{
				if (base.CoordinateSystem == CoordinateSystem.Source)
					return _point;
				return base.SpatialTransform.ConvertToDestination(_point);
			}
			set
			{
				if (base.CoordinateSystem == CoordinateSystem.Destination)
					value = base.SpatialTransform.ConvertToSource(value);

				if (!FloatComparer.AreEqual(_point, value))
				{
					_point = value;
					RecomputeCrosshair();
				}
			}
		}

		/// <summary>
		/// Gets or sets the length of the crosshair.
		/// </summary>
		/// <remarks>
		/// The length of the crosshair is the altitude along the shaft of the triangle formed by the crosshair.
		/// </remarks>
		public float Length
		{
			get { return _length; }
			set
			{
				if (!FloatComparer.AreEqual(_length, value))
				{
					_length = value;
					RecomputeCrosshair();
				}
			}
		}

		/// <summary>
		/// Gets or sets the lenghts of space between crosshair lines
		/// </summary>
		public float GapLength
		{
			get { return _gapLength; }
			set
			{
				if (!FloatComparer.AreEqual(_gapLength, value))
				{
					_gapLength = value;
					RecomputeCrosshair();
				}
			}
		}

		/// <summary>
		/// Gets the point on the crosshair closest to the specified <paramref name="point"/>.
		/// </summary>
		public override PointF GetClosestPoint(PointF point)
		{
			PointF shortestPoint = new PointF();
			double shortestDistance = Vector.DistanceFromPointToLine(point, _left.TopLeft, _left.BottomRight, ref shortestPoint);

			PointF pointR = new PointF();
			double distanceR = Vector.DistanceFromPointToLine(point, _right.TopLeft, _right.BottomRight, ref pointR);
			if (distanceR < shortestDistance)
			{
				shortestDistance = distanceR;
				shortestPoint = pointR;
			}

			PointF pointT = new PointF();
			double distanceT = Vector.DistanceFromPointToLine(point, _top.TopLeft, _top.BottomRight, ref pointT);
			if (distanceT < shortestDistance)
			{
				shortestDistance = distanceT;
				shortestPoint = pointT;
			}

			PointF pointB = new PointF();
			double distanceB = Vector.DistanceFromPointToLine(point, _bottom.TopLeft, _bottom.BottomRight, ref pointB);
			if (distanceB < shortestDistance)
				shortestPoint = pointB;

			return shortestPoint;
		}

		/// <summary>
		/// Recomputes the shape and positioning of the crosshair's line graphics.
		/// </summary>
		protected void RecomputeCrosshair()
		{
			CoordinateSystem = CoordinateSystem.Source;
			try
			{
				PointF anchor = Point;

				_left.Location = anchor;
				_left.InvariantTopLeft = new PointF(-_length - _gapLength, 0);
				_left.InvariantBottomRight = new PointF(-_gapLength, 0);

				_right.Location = anchor;
				_right.InvariantTopLeft = new PointF(_gapLength, 0);
				_right.InvariantBottomRight = new PointF(_length + _gapLength, 0);

				_bottom.Location = anchor;
				_bottom.InvariantTopLeft = new PointF(0, -_gapLength);
				_bottom.InvariantBottomRight = new PointF(0, -_length - _gapLength);

				_top.Location = anchor;
				_top.InvariantTopLeft = new PointF(0, _length + _gapLength);
				_top.InvariantBottomRight = new PointF(0, _gapLength);
			}
			finally
			{
				ResetCoordinateSystem();
			}
		}
	}
}
