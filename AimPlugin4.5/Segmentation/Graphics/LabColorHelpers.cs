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
using ClearCanvas.Dicom.Iod;

namespace Segmentation.Graphics
{
    public static class LabColorHelpers
    {
        public static CIELabColor RgbColorToCIELabColor(Color rgbColor)
        {
            var labColor = new Rgb {R = rgbColor.R, B = rgbColor.B, G = rgbColor.G}.To<Lab>();
            return new CIELabColor
                       {
                           L = LDoubleToUshort(labColor.L),
                           A = ABDoubleToUShort(labColor.A),
                           B = ABDoubleToUShort(labColor.B)
                       };
        }

        public static Color CIELabColorToRgbColor(CIELabColor labColor)
        {
            var rgbColor = new Lab
                               {
                                   L = LUShortToDouble(labColor.L),
                                   A = ABUShortToDouble(labColor.A),
                                   B = ABUShortToDouble(labColor.B)
                               }.To<Rgb>();
            return Color.FromArgb(
                (int) Math.Round(rgbColor.R),
                (int) Math.Round(rgbColor.G),
                (int) Math.Round(rgbColor.B)
                );
        }

        private static ushort LDoubleToUshort(double l)
        {
            return (ushort) Math.Round(((l/100d)*0xffff));
        }

        private static double LUShortToDouble(ushort l)
        {
            return ((double)l)/0xffff*100d;
        }

        private static ushort ABDoubleToUShort(double ab)
        {
            return (ushort) Math.Round((ab + 128)/255*0xffff);
        }

        private static double ABUShortToDouble(ushort ab)
        {
            return ((double)ab) / 0xffff * 255d - 128;
        }


        #region Nested type: ColorSpace

        /// <summary>
        /// Abstract ColorSpace class, defines the To method that converts between any IColorSpace.
        /// </summary>
        private abstract class ColorSpace : IColorSpace
        {
            #region IColorSpace Members

            public abstract void Initialize(IRgb color);
            public abstract IRgb ToRgb();

            /// <summary>
            /// Convert any IColorSpace to any other IColorSpace
            /// </summary>
            /// <typeparam name="T">Must implement IColorSpace, new()</typeparam>
            /// <returns></returns>
            public T To<T>() where T : IColorSpace, new()
            {
                if (typeof (T) == GetType())
                {
                    return (T) MemberwiseClone();
                }

                var newColorSpace = new T();
                newColorSpace.Initialize(ToRgb());

                return newColorSpace;
            }

            #endregion
        }

        #endregion

        #region Nested type: IColorSpace

        /// <summary>
        /// Defines the public methods for all color spaces
        /// </summary>
        private interface IColorSpace
        {
            /// <summary>
            /// Initialize settings from an Rgb object
            /// </summary>
            /// <param name="color"></param>
            void Initialize(IRgb color);

            /// <summary>
            /// Convert the color space to Rgb, you should probably using the "To" method instead. Need to figure out a way to "hide" or otherwise remove this method from the public interface.
            /// </summary>
            /// <returns></returns>
            IRgb ToRgb();

            /// <summary>
            /// Convert any IColorSpace to any other IColorSpace.
            /// </summary>
            /// <typeparam name="T">IColorSpace type to convert to</typeparam>
            /// <returns></returns>
            T To<T>() where T : IColorSpace, new();
        }

        #endregion

        #region Nested type: ILab

        private interface ILab : IColorSpace
        {
            double L { get; set; }
            double A { get; set; }
            double B { get; set; }
        }

        #endregion

        #region Nested type: IRgb

        private interface IRgb : IColorSpace
        {
            double R { get; set; }
            double G { get; set; }
            double B { get; set; }
        }

        #endregion

        #region Nested type: IXyz

        private interface IXyz : IColorSpace
        {
            double X { get; set; }
            double Y { get; set; }
            double Z { get; set; }
        }

        #endregion

        #region Nested type: Lab

        private class Lab : ColorSpace, ILab
        {
            #region ILab Members

            public double L { get; set; }
            public double A { get; set; }
            public double B { get; set; }

            public override void Initialize(IRgb color)
            {
                LabConverter.ToColorSpace(color, this);
            }

            public override IRgb ToRgb()
            {
                return LabConverter.ToColor(this);
            }

            #endregion
        }

        #endregion

        #region Nested type: LabConverter

        private static class LabConverter
        {
            internal static void ToColorSpace(IRgb color, ILab item)
            {
                var xyz = new Xyz();
                xyz.Initialize(color);

                IXyz white = XyzConverter.WhiteReference;
                double x = PivotXyz(xyz.X/white.X);
                double y = PivotXyz(xyz.Y/white.Y);
                double z = PivotXyz(xyz.Z/white.Z);

                item.L = Math.Max(0, 116*y - 16);
                item.A = 500*(x - y);
                item.B = 200*(y - z);
            }

            internal static IRgb ToColor(ILab item)
            {
                double y = (item.L + 16.0)/116.0;
                double x = item.A/500.0 + y;
                double z = y - item.B/200.0;

                IXyz white = XyzConverter.WhiteReference;
                double x3 = x*x*x;
                double z3 = z*z*z;
                var xyz = new Xyz
                              {
                                  X = white.X*(x3 > XyzConverter.Epsilon ? x3 : (x - 16.0/116.0)/7.787),
                                  Y =
                                      white.Y*
                                      (item.L > (XyzConverter.Kappa*XyzConverter.Epsilon)
                                           ? Math.Pow(((item.L + 16.0)/116.0), 3)
                                           : item.L/XyzConverter.Kappa),
                                  Z = white.Z*(z3 > XyzConverter.Epsilon ? z3 : (z - 16.0/116.0)/7.787)
                              };

                return xyz.ToRgb();
            }

            private static double PivotXyz(double n)
            {
                return n > XyzConverter.Epsilon ? CubicRoot(n) : (XyzConverter.Kappa*n + 16)/116;
            }

            private static double CubicRoot(double n)
            {
                return Math.Pow(n, 1.0/3.0);
            }
        }

        #endregion

        #region Nested type: Rgb

        private class Rgb : ColorSpace, IRgb
        {
            #region IRgb Members

            public double R { get; set; }
            public double G { get; set; }
            public double B { get; set; }

            public override void Initialize(IRgb color)
            {
                RgbConverter.ToColorSpace(color, this);
            }

            public override IRgb ToRgb()
            {
                return RgbConverter.ToColor(this);
            }

            #endregion
        }

        #endregion

        #region Nested type: RgbConverter

        private static class RgbConverter
        {
            internal static void ToColorSpace(IRgb color, IRgb item)
            {
                item.R = color.R;
                item.G = color.G;
                item.B = color.B;
            }

            internal static IRgb ToColor(IRgb item)
            {
                return item;
            }
        }

        #endregion

        #region Nested type: Xyz

        private class Xyz : ColorSpace, IXyz
        {
            #region IXyz Members

            public double X { get; set; }
            public double Y { get; set; }
            public double Z { get; set; }

            public override void Initialize(IRgb color)
            {
                XyzConverter.ToColorSpace(color, this);
            }

            public override IRgb ToRgb()
            {
                return XyzConverter.ToColor(this);
            }

            #endregion
        }

        #endregion

        #region Nested type: XyzConverter

        private static class XyzConverter
        {
            #region Constants/Helper methods for Xyz related spaces

            // TODO: Hard-coded!
            internal const double Epsilon = 0.008856; // Intent is 216/24389
            internal const double Kappa = 903.3; // Intent is 24389/27

            static XyzConverter()
            {
                WhiteReference = new Xyz
                                     {
                                         X = 95.047,
                                         Y = 100.000,
                                         Z = 108.883
                                     };
            }

            internal static IXyz WhiteReference { get; private set; }

            internal static double CubicRoot(double n)
            {
                return Math.Pow(n, 1.0/3.0);
            }

            #endregion

            internal static void ToColorSpace(IRgb color, IXyz item)
            {
                double r = PivotRgb(color.R/255.0);
                double g = PivotRgb(color.G/255.0);
                double b = PivotRgb(color.B/255.0);

                // Observer. = 2°, Illuminant = D65
                item.X = r*0.4124 + g*0.3576 + b*0.1805;
                item.Y = r*0.2126 + g*0.7152 + b*0.0722;
                item.Z = r*0.0193 + g*0.1192 + b*0.9505;
            }

            internal static IRgb ToColor(IXyz item)
            {
                // (Observer = 2°, Illuminant = D65)
                double x = item.X/100.0;
                double y = item.Y/100.0;
                double z = item.Z/100.0;

                double r = x*3.2406 + y*-1.5372 + z*-0.4986;
                double g = x*-0.9689 + y*1.8758 + z*0.0415;
                double b = x*0.0557 + y*-0.2040 + z*1.0570;

                r = r > 0.0031308 ? 1.055*Math.Pow(r, 1/2.4) - 0.055 : 12.92*r;
                g = g > 0.0031308 ? 1.055*Math.Pow(g, 1/2.4) - 0.055 : 12.92*g;
                b = b > 0.0031308 ? 1.055*Math.Pow(b, 1/2.4) - 0.055 : 12.92*b;

                return new Rgb
                           {
                               R = ToRgb(r),
                               G = ToRgb(g),
                               B = ToRgb(b)
                           };
            }

            private static double ToRgb(double n)
            {
                double result = 255.0*n;
                if (result < 0) return 0;
                if (result > 255) return 255;
                return result;
            }

            private static double PivotRgb(double n)
            {
                return (n > 0.04045 ? Math.Pow((n + 0.055)/1.055, 2.4) : n/12.92)*100.0;
            }
        }

        #endregion
    }
}