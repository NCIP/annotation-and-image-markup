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
using System.Runtime.Serialization;

namespace Segmentation.Tree
{
    /// <summary>
    /// Represents a CIELab color value
    /// </summary>
    public class LabColor
    {
        /// <summary>
        /// Gets or sets the lightness value of the lab color
        /// </summary>
        [DataMember]
        public double L { get; set; }

        /// <summary>
        /// Gets or sets the a* color-opponent dimension of the lab color
        /// </summary>
        [DataMember]
        public double a { get; set; }

        /// <summary>
        /// Get ors sets the b* color-opponent dimension of the lab color
        /// </summary>
        [DataMember]
        public double b { get; set; }

        public static LabColor FromRgbColor(Color color)
        {
            int red = color.R;
            int green = color.G;
            int blue = color.B;

            // normalize red, green, blue values
            double rLinear = red/255.0;
            double gLinear = green/255.0;
            double bLinear = blue/255.0;

            // convert to a sRGB form
            double r = (rLinear > 0.04045)
                           ? Math.Pow((rLinear + 0.055)/(
                                                            1 + 0.055), 2.2)
                           : (rLinear/12.92);
            double g = (gLinear > 0.04045)
                           ? Math.Pow((gLinear + 0.055)/(
                                                            1 + 0.055), 2.2)
                           : (gLinear/12.92);
            double b = (bLinear > 0.04045)
                           ? Math.Pow((bLinear + 0.055)/(
                                                            1 + 0.055), 2.2)
                           : (bLinear/12.92);

            var xyz = new CieXyz(
                (r*0.4124 + g*0.3576 + b*0.1805),
                (r*0.2126 + g*0.7152 + b*0.0722),
                (r*0.0193 + g*0.1192 + b*0.9505)
                );
            double x = xyz.X;
            double y = xyz.Y;
            double z = xyz.Z;

            return new LabColor
                       {
                           L = 116.0*Fxyz(y/CieXyz.D65.Y) - 16,
                           a = 500.0*(Fxyz(x/CieXyz.D65.X) - Fxyz(y/CieXyz.D65.Y)),
                           b = 200.0*(Fxyz(y/CieXyz.D65.Y) - Fxyz(z/CieXyz.D65.Z))
                       };
        }

        public Color ToRgbColor()
        {
            double delta = 6.0 / 29.0;

            double fy = (L + 16) / 116.0;
            double fx = fy + (a / 500.0);
            double fz = fy - (b / 200.0);

            var xyz = new CieXyz(
                (fx > delta) ? CieXyz.D65.X * (fx * fx * fx) : (fx - 16.0 / 116.0) * 3 * (
                    delta * delta) * CieXyz.D65.X,
                (fy > delta) ? CieXyz.D65.Y * (fy * fy * fy) : (fy - 16.0 / 116.0) * 3 * (
                    delta * delta) * CieXyz.D65.Y,
                (fz > delta) ? CieXyz.D65.Z * (fz * fz * fz) : (fz - 16.0 / 116.0) * 3 * (
                    delta * delta) * CieXyz.D65.Z
                );
            double x = xyz.X;
            double y = xyz.Y;
            double z = xyz.Z;

            double[] Clinear = new double[3];
            Clinear[0] = x*3.2410 - y*1.5374 - z*0.4986; // red
            Clinear[1] = -x*0.9692 + y*1.8760 - z*0.0416; // green
            Clinear[2] = x*0.0556 - y*0.2040 + z*1.0570; // blue

            for(int i=0; i<3; i++)
            {
                Clinear[i] = (Clinear[i]<=0.0031308)? 12.92*Clinear[i] : (
                    1+0.055)* Math.Pow(Clinear[i], (1.0/2.4)) - 0.055;
            }

            return Color.FromArgb(
                Convert.ToInt32( Double.Parse(String.Format("{0:0.00}",
                    Clinear[0]*255.0)) ),
                Convert.ToInt32( Double.Parse(String.Format("{0:0.00}",
                    Clinear[1]*255.0)) ),
                Convert.ToInt32( Double.Parse(String.Format("{0:0.00}",
                    Clinear[2]*255.0)) )
                );
        }

        /// <summary>
        /// XYZ to L*a*b* transformation function.
        /// </summary>
        private static double Fxyz(double t)
        {
            return ((t > 0.008856) ? Math.Pow(t, (1.0/3.0)) : (7.787*t + 16.0/116.0));
        }

        #region Nested type: CieXyz

        private struct CieXyz
        {
            /// <summary>
            /// Gets an empty CieXyz structure.
            /// </summary>
            public static readonly CieXyz Empty = new CieXyz();

            /// <summary>
            /// Gets the CIE D65 (white) structure.
            /// </summary>
            public static readonly CieXyz D65 = new CieXyz(0.9505, 1.0, 1.0890);


            private double x;
            private double y;
            private double z;

            public CieXyz(double x, double y, double z)
            {
                this.x = (x > 0.9505) ? 0.9505 : ((x < 0) ? 0 : x);
                this.y = (y > 1.0) ? 1.0 : ((y < 0) ? 0 : y);
                this.z = (z > 1.089) ? 1.089 : ((z < 0) ? 0 : z);
            }

            /// <summary>
            /// Gets or sets X component.
            /// </summary>
            public double X
            {
                get { return x; }
                set { x = (value > 0.9505) ? 0.9505 : ((value < 0) ? 0 : value); }
            }

            /// <summary>
            /// Gets or sets Y component.
            /// </summary>
            public double Y
            {
                get { return y; }
                set { y = (value > 1.0) ? 1.0 : ((value < 0) ? 0 : value); }
            }

            /// <summary>
            /// Gets or sets Z component.
            /// </summary>
            public double Z
            {
                get { return z; }
                set { z = (value > 1.089) ? 1.089 : ((value < 0) ? 0 : value); }
            }

            public static bool operator ==(CieXyz item1, CieXyz item2)
            {
                return (
                           item1.X == item2.X
                           && item1.Y == item2.Y
                           && item1.Z == item2.Z
                       );
            }

            public static bool operator !=(CieXyz item1, CieXyz item2)
            {
                return (
                           item1.X != item2.X
                           || item1.Y != item2.Y
                           || item1.Z != item2.Z
                       );
            }

            public override bool Equals(Object obj)
            {
                if (obj == null || GetType() != obj.GetType()) return false;

                return (this == (CieXyz) obj);
            }

            public override int GetHashCode()
            {
                return X.GetHashCode() ^ Y.GetHashCode() ^ Z.GetHashCode();
            }
        }

        #endregion
    }
}