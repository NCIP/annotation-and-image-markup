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

using System.Drawing;

using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using AIM.Annotation.AimManager;

namespace AIM.Annotation.Graphics
{
	public interface IAimGraphic : IGraphic
	{
		IAimAnnotationInstance AimAnnotation { get; }
		string AnnotationUid { get; }
		Color Color { get; set; }
		string UserLoginName { get; }
	}

	// This is a simple wrapper to differentiate AIM Annotations from plain markup.
	[Cloneable]
	public class AimGraphic : DecoratorCompositeGraphic /*ControlGraphic*/, IAimGraphic
	{
		private readonly IAimAnnotationInstance _annotationInstance;
		private Color _color = Color.Gray;
		private readonly int _shapeIdentifier;
		private readonly IGraphic _graphic;

		public AimGraphic(IGraphic graphic, IAimAnnotationInstance annotationInstance, int shapeIdentifier)
			: base(graphic)
		{
			_annotationInstance = annotationInstance;
			_shapeIdentifier = shapeIdentifier;
			_graphic = graphic;
		}

		/// <summary>
		/// Cloning constructor.
		/// </summary>
		/// <param name="aimGraphic">The source object from which to clone.</param>
		/// <param name="context">The cloning context object.</param>
		protected AimGraphic(AimGraphic aimGraphic, ICloningContext context): base(aimGraphic.DecoratedGraphic)
		{
			context.CloneFields(aimGraphic, this);
		}

		#region IAimGraphic Members

		public IAimAnnotationInstance AimAnnotation
		{
			get { return _annotationInstance; }
		}

		public string AnnotationUid
		{
			get { return AimAnnotation.UniqueIdentifier; }
		}

		public int ShapeIdentifier
		{
			get { return _shapeIdentifier; }
		}

		public Color Color
		{
			get { return _color; }
			set
			{
				if (_color != value)
				{
					_color = value;
					if (this.DecoratedGraphic is IControlGraphic)
						((IControlGraphic)this.DecoratedGraphic).Color = _color;
					UpdateColor(_graphic, value);
				}
			}
		}

		public string UserLoginName
		{
			get { return this.AimAnnotation == null ? null : this.AimAnnotation.UserLoginName.ToLowerInvariant(); }
		}

		public IGraphic Graphic { get { return _graphic; } }

		private static void UpdateColor(IGraphic graphic, Color color)
		{
			StandardStatefulGraphic statefulGraphic = graphic as StandardStatefulGraphic;

			if (statefulGraphic != null)
				statefulGraphic.InactiveColor = color;

			if (graphic is IControlGraphic)
			{
				IControlGraphic controlGraphic = (IControlGraphic)graphic;
				controlGraphic.Color = color;
			}
			else if (graphic is IVectorGraphic)
			{
				((IVectorGraphic)graphic).Color = color;
			}

			if (graphic is CompositeGraphic)
			{
				foreach (IGraphic childGraphic in ((CompositeGraphic)graphic).Graphics)
					UpdateColor(childGraphic, color);
			}
		}

		#endregion
	}
}
