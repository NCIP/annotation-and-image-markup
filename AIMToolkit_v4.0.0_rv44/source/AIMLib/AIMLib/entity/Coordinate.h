/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_Coordinate_Class_
#define _AIMLib_Coordinate_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API Coordinate
	{
	public:
		Coordinate();
		Coordinate(const Coordinate& coordinate);
		Coordinate& operator=(const Coordinate& coordinate);
		virtual ~Coordinate();

		int GetDimensionIndex() const;
		int GetPosition() const;

		void SetDimensionIndex(int newValue);
		void SetPosition(int newValue);

	private:
		int _dimensionIndex;
		int _position;
	};
	
	typedef std::vector<Coordinate> CoordinateVector;
}
#endif // _AIMLib_Coordinate_Class_
