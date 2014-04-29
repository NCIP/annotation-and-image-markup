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
using ClearCanvas.ImageViewer.Common;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.Imaging;
using Segmentation.Tree;

namespace Segmentation.Graphics
{
    /// <summary>
    /// A dynamically created 1-bit bitmap overlay plane <see cref="IGraphic"/>.
    /// </summary>
    [Cloneable]
    public class SegFrameImageGraphic : CompositeGraphic, ISegGraphic
    {
        private readonly int _frameIndex;
        private readonly int _index;
        [CloneIgnore] private readonly GrayscaleImageGraphic _overlayGraphic;
        private float _alpha;
        private Color _color;


        public SegFrameImageGraphic(int rows, int columns, float xLocation, float yLocation, Color color, int frameIndex,
                                    int index, string label, string description, byte[] pixelData,
                                    SegmentationDocumentReference segmentationDocumentReference)
        {
            Platform.CheckPositive(rows, "rows");
            Platform.CheckPositive(columns, "columns");
            Platform.CheckNonNegative(frameIndex, "frameIndex");

            _index = index;
            _frameIndex = frameIndex;
            Label = string.IsNullOrEmpty(label) ? string.Empty : label;
            Description = string.IsNullOrEmpty(description) ? string.Empty : description;
            SegmentationDocumentReference = segmentationDocumentReference;

            // new empty pixel buffer
            if (pixelData == null)
                pixelData = MemoryManager.Allocate<byte>(rows*columns);

            _overlayGraphic = new GrayscaleImageGraphic(
                rows, columns, // the reported overlay dimensions
                8, // bits allocated is always 8
                8, // overlays always have bit depth of 1, but we upconverted the data
                7, // the high bit is now 7 after upconverting
                false, false, // overlays aren't signed and don't get inverted
                1, 0, // overlays have no rescale
                pixelData); // the upconverted overlay data

            _overlayGraphic.SpatialTransform.TranslationX = xLocation;
            _overlayGraphic.SpatialTransform.TranslationY = yLocation;

            Color = color;
            Graphics.Add(_overlayGraphic);
        }

        public SegFrameImageGraphic(
            int rows,
            int columns,
            Color color,
            int frameIndex,
            int index,
            string label,
            string description,
            byte[] pixelData,
            SegmentationDocumentReference segmentationDocumentReference) :
                this(
                rows,
                columns,
                0,
                0,
                color,
                frameIndex,
                index,
                label,
                description,
                pixelData,
                segmentationDocumentReference)
        {
        }

        public SegFrameImageGraphic(int rows, int columns, Color color) :this(
            rows,
            columns,
            color,
            0,
            -1,
            String.Empty,
            String.Empty,
            null,
            null)
        {
        }

        internal GrayscaleImageGraphic OverlayGraphic { get { return _overlayGraphic; } }

        /// <summary>
        /// Gets or sets the presence of the overlay pixel at the specified coordinate.
        /// </summary>
        /// <param name="point">The coordinate of the pixel.</param>
        public bool this[Point point]
        {
            get { return this[point.X, point.Y]; }
            set { this[point.X, point.Y] = value; }
        }

        /// <summary>
        /// Gets or sets the presence of the overlay pixel at the specified coordinate.
        /// </summary>
        /// <param name="x">The x-coordinate of the pixel.</param>
        /// <param name="y">The y-coordinate of the pixel.</param>
        public bool this[int x, int y]
        {
            get { return OverlayPixelData[y*Columns + x] > 0; }
            set { OverlayPixelData[y*Columns + x] = value ? (byte) 0xFF : (byte) 0x00; }
        }

        public float Alpha

        {
            get { return _alpha; }
            set
            {
                _alpha = value;
                Color = Color.FromArgb((int) (_alpha*255), Color);
                Draw();
            }
        }

        /// <summary>
        /// Gets the raw overlay pixel data as an 8-bit grayscale pixel data buffer.
        /// </summary>
        protected byte[] OverlayPixelData
        {
            get { return _overlayGraphic != null ? _overlayGraphic.PixelData.Raw : null; }
        }

        /// <summary>
        /// Gets the overlay group index in which the overlay was encoded.
        /// </summary>
        public int Index
        {
            get { return _index; }
        }

        /// <summary>
        /// Gets the frame index of this overlay frame within the original overlay data.
        /// </summary>
        public int FrameIndex
        {
            get { return _frameIndex; }
        }

        /// <summary>
        /// Gets the label or name of the overlay plane.
        /// </summary>
        public string Label { get; protected set; }

        /// <summary>
        /// Gets the description of the overlay plane.
        /// </summary>
        public string Description { get; protected set; }

        /// <summary>
        /// Gets the location of the top left corner of the overlay relative to the image.
        /// </summary>
        public PointF Origin
        {
            get
            {
                if (_overlayGraphic == null)
                    return new PointF(1, 1);
                return new PointF(_overlayGraphic.SpatialTransform.TranslationX + 1,
                                  _overlayGraphic.SpatialTransform.TranslationY + 1);
            }
            protected set
            {
                if (_overlayGraphic != null)
                {
                    _overlayGraphic.SpatialTransform.TranslationX = value.X - 1;
                    _overlayGraphic.SpatialTransform.TranslationY = value.Y - 1;
                }
            }
        }

        /// <summary>
        /// Gets the number of rows in the overlay plane.
        /// </summary>
        public int Rows
        {
            get { return _overlayGraphic != null ? _overlayGraphic.Rows : 0; }
        }

        /// <summary>
        /// Gets the number of columns in the overlay plane.
        /// </summary>
        public int Columns
        {
            get { return _overlayGraphic != null ? _overlayGraphic.Columns : 0; }
        }

        /// <summary>
        /// Gets or sets reference to the Segmentation document this graphic is loaded from
        /// </summary>
        /// <value>Reference to the Segmentation document this graphic is loaded from or null if the graphic is not based on an existing document</value>
        public SegmentationDocumentReference SegmentationDocumentReference { get; protected set; }

        #region Voi Lut

        [Cloneable(true)]
        private class OverlayVoiLut : ComposableVoiLut
        {
            private readonly int _maxOutputValue;
            private readonly int _presentationValue;
            private double _maxInputValue;

            public OverlayVoiLut(int presentationValue, int maxOutputValue)
            {
                _presentationValue = presentationValue;
                _maxOutputValue = maxOutputValue;
            }

            public override double MinInputValue { get; set; }

            public override double MaxInputValue
            {
                get { return _maxInputValue; }
                set { _maxInputValue = value; }
            }

            public override double MinOutputValue
            {
                get { return 0; }
                protected set { }
            }

            public override double MaxOutputValue
            {
                get { return _maxOutputValue; }
                protected set { }
            }

            public override double this[double index]
            {
                get { return (int) Math.Round((index/_maxInputValue)*_presentationValue); }
            }

            public override string GetKey()
            {
                return String.Format("OverlayVoi_{0}_{1}_{2}", MinInputValue, MaxInputValue, _presentationValue);
            }

            public override string GetDescription()
            {
                return "Overlay Voi";
            }
        }

        #endregion

        #region Color Map

        [Cloneable(true)]
        private class AlphaSegColorMap : ColorMap
        {
            private Color _color = Color.Yellow;

            public AlphaSegColorMap(Color color)
            {
                _color = color;
            }

            public void CreateNew()
            {
                Create();
            }

            protected override void Create()
            {
                for (int i = MinInputValue; i <= MaxInputValue; i++)
                    this[i] = Color.FromArgb((int) (i*(_color.A/255f)), _color).ToArgb();
            }

            private string GetDescriptionBase()
            {
                return string.Format("OverlayColorMap_{0}_{1}_{2}", _color.R, _color.G, _color.B);
            }

            public override string GetDescription()
            {
                return string.Format("{0}[alpha={1}]", GetDescriptionBase(), _color.A);
            }

            public override string GetKey()
            {
                return string.Format("{0}[alpha={1}]", base.GetKey(), _color.A);
            }
        }

        #endregion

        #region ISegGraphic Members

        public Color Color
        {
            get { return _color; }
            set
            {
                //if (_color == value)
                //    return;

                _color = value;
                UpdateLuts();
                Draw();
            }
        }

        public string ImageSopInstanceUid { get; set; }
        public int ImageFrameNumber { get; set; }
        public int ImageNumber { get; set; }

        public int GraphicHashCode
        {
            get { return GetHashCode(); }
        }

        string ISegGraphic.Label
        {
            get { return Label; }
            set { Label = value; }
        }

        #endregion

        public void UpdateLuts()
        {
            if (_overlayGraphic == null)
                return;

            _overlayGraphic.VoiLutManager.InstallVoiLut(new OverlayVoiLut(255, 255));
            _overlayGraphic.ColorMapManager.InstallColorMap(new AlphaSegColorMap(_color));
            ((AlphaSegColorMap) _overlayGraphic.ColorMap).CreateNew();
        }
    }
}