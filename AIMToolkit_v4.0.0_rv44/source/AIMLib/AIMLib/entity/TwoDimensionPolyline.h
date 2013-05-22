/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TwoDimensionPolyline_Class_
#define _AIMLib_TwoDimensionPolyline_Class_

namespace aim_lib
{
	class AIMLIB_API TwoDimensionPolyline : public TwoDimensionGeometricShapeEntity
	{
	public:
		TwoDimensionPolyline();
		TwoDimensionPolyline(const TwoDimensionPolyline& polyline);
		virtual ~TwoDimensionPolyline();
		virtual TwoDimensionPolyline* Clone() const;

		virtual const TwoDimensionShapeType GetShapeType() const;
	};
}
#endif // _AIMLib_TwoDimensionPolyline_Class_
