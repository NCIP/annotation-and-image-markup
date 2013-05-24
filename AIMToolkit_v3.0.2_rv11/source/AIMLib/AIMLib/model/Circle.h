/*
  Classname: Circle

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_403C1B1B_5D8C_4c6b_B943_2E6531B30076__INCLUDED_)
#define EA_403C1B1B_5D8C_4c6b_B943_2E6531B30076__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API Circle : public GeometricShape
	{

	public:
		Circle();
		virtual ~Circle();
		virtual Circle* Clone() const;

		const SpatialCoordinate& GetCenter() const;
		const SpatialCoordinate& GetRadiusPoint() const;
		void SetCenter(const SpatialCoordinate& center);
		void SetRadiusPoint(const SpatialCoordinate& radiusPoint);

	protected:
		enum CircleCoordinateIndex
		{
			CenterPoint = 0,
			CircumferencePoint = 1
		};

	};
}
#endif // !defined(EA_403C1B1B_5D8C_4c6b_B943_2E6531B30076__INCLUDED_)
