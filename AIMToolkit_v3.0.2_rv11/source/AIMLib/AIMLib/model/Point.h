/*
  Classname: Point

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_6D7D7B09_44EB_4a7e_A7CE_AFD71D3B2F2C__INCLUDED_)
#define EA_6D7D7B09_44EB_4a7e_A7CE_AFD71D3B2F2C__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API Point : public GeometricShape
	{

	public:
		Point();
		virtual ~Point();
		virtual Point* Clone() const;

		const SpatialCoordinate& GetCenter();
		void SetCenter(const SpatialCoordinate& spatialCoordinate);

	protected:
		enum PointCoordinateIndex
		{
			CenterPoint = 0
		};
	};
}
#endif // !defined(EA_6D7D7B09_44EB_4a7e_A7CE_AFD71D3B2F2C__INCLUDED_)
