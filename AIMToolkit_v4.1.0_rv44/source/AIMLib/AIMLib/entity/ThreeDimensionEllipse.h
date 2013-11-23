/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#ifndef _AIMLib_ThreeDimensionEllipse_Class_
#define _AIMLib_ThreeDimensionEllipse_Class_

namespace aim_lib
{
	/*
	ELLIPSE = an ellipse defined by four (x,y,z) triplets, the first two triplets specifying the endpoints of the
	major axis and the second two triplets specifying the endpoints of the minor axis.
	*/
	class AIMLIB_API ThreeDimensionEllipse : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionEllipse();
		ThreeDimensionEllipse(const ThreeDimensionEllipse& ellipse);
		virtual ~ThreeDimensionEllipse();
		virtual ThreeDimensionEllipse* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;

		const ThreeDimensionSpatialCoordinateVector& GetEllipseCollection();
		const ThreeDimensionSpatialCoordinate& GetMajorAxisPoint1() const;
		const ThreeDimensionSpatialCoordinate& GetMajorAxisPoint2() const;
		const ThreeDimensionSpatialCoordinate& GetMinorAxisPoint1() const;
		const ThreeDimensionSpatialCoordinate& GetMinorAxisPoint2() const;

		void SetEllipseCollection(const ThreeDimensionSpatialCoordinateVector& ellipseCollection);
		void SetMajorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMajorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMinorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMinorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal);
	protected:
		enum EllipseCoordinateIndex
		{
			MajorAxis1 = 0,
			MajorAxis2 = 1,
			MinorAxis1 = 2,
			MinorAxis2 = 3
		};
	};
}
#endif // _AIMLib_ThreeDimensionEllipse_Class_
