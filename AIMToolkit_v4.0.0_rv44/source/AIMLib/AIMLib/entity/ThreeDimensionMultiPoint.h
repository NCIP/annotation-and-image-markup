/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ThreeDimensionMultiPoint_Class_
#define _AIMLib_ThreeDimensionMultiPoint_Class_

namespace aim_lib
{
	/*
	MULTIPOINT = multiple locations each denoted by an (x,y,z) triplet; the points need not be coplanar.
	*/
	class AIMLIB_API ThreeDimensionMultiPoint : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionMultiPoint();
		ThreeDimensionMultiPoint(const ThreeDimensionMultiPoint& multiPoint);
		virtual ~ThreeDimensionMultiPoint();
		virtual ThreeDimensionMultiPoint* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;
	};
}
#endif // _AIMLib_ThreeDimensionMultiPoint_Class_
