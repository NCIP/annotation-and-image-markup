#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Drawing;

using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;

namespace AIM.Annotation.Graphics
{
	public interface IAimGraphic : IGraphic
	{
		aim_dotnet.ImageAnnotation AimAnnotation { get; }
		Color Color { get; set; }
		string UserLoginName { get; }
	}

	// This is a simple wrapper to differentiate AIM Annotations from plain markup.
	[Cloneable]
	public class AimGraphic : DecoratorCompositeGraphic /*ControlGraphic*/, IAimGraphic
	{
		private readonly aim_dotnet.ImageAnnotation _imageAnnotation;
		private Color _color = Color.Gray;
		private readonly int _shapeIdentifier;
        private readonly IGraphic _graphic;

        public AimGraphic(IGraphic graphic, aim_dotnet.ImageAnnotation imageAnnotation, int shapeIdentifier)
            : base(graphic)
        {
            _imageAnnotation = imageAnnotation;
            _shapeIdentifier = shapeIdentifier;
            _graphic = graphic;
        }

		protected AimGraphic(AimGraphic aimGraphic, ICloningContext context): base(aimGraphic.DecoratedGraphic)
		{
			context.CloneFields(aimGraphic, this);
		}

		#region IAimGraphic Members

		public aim_dotnet.ImageAnnotation AimAnnotation
		{
			get { return _imageAnnotation; }
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
                    if (DecoratedGraphic is IControlGraphic)
                        ((IControlGraphic)DecoratedGraphic).Color = _color;
                    UpdateColor(_graphic, value);
				}
			}
		}

		public string UserLoginName
		{
			get { return AimAnnotation == null ? null : AimAnnotation.User.LoginName.ToLowerInvariant(); }
		}

		private static void UpdateColor(IGraphic graphic, Color color)
        {
            var statefulGraphic = graphic as StandardStatefulGraphic;
            if (statefulGraphic != null)
                statefulGraphic.InactiveColor = color;
            if (graphic is IControlGraphic)
            {
                var controlGraphic = (IControlGraphic)graphic;
                controlGraphic.Color = color;
            }
            else if (graphic is IVectorGraphic)
            {
                ((IVectorGraphic)graphic).Color = color;
            }
            if (graphic is CompositeGraphic)
            {
                foreach (var childGraphic in ((CompositeGraphic)graphic).Graphics)
                    UpdateColor(childGraphic, color);
            }
        }

		#endregion
	}
}
