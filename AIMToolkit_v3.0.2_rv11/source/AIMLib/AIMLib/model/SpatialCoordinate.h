/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_29368214_BC70_483a_BBE0_6EE2D4B42E46__INCLUDED_)
#define EA_29368214_BC70_483a_BBE0_6EE2D4B42E46__INCLUDED_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API SpatialCoordinate
	{
	public:
		enum SpatialCoordinateType
		{
			T_UNDEFINED_SPCOORD,
			T_2D_SPCOORD,
			T_3D_SPCOORD
		};

		virtual ~SpatialCoordinate();
		virtual SpatialCoordinate* Clone() const = 0;
		virtual const SpatialCoordinateType GetCoordinateType() const = 0;

		const int GetCoordinateIndex() const;
		void SetCoordinateIndex(int newVal);

		// Spatial Coordinates Sorting Predicate
		static bool SpatialCoordinateSortPredicate(const SpatialCoordinate* pCoord1, const SpatialCoordinate* pCoord2);

	protected:
		SpatialCoordinate();
		SpatialCoordinate(int coordinateIndex);
		SpatialCoordinate(const SpatialCoordinate& spatialCoordinate);

		int _cagridId;
		// NOTE: Sequential index of the coordinate in the collection of Spatial Coordinates.
		// DICOM maintains implicit coordinate order, by XML will need this for proper coordinate
		// sequencing.
		int _coordinateIndex;
	};

	typedef std::vector<SpatialCoordinate*> SpatialCoordPtrVector;

}
#endif // !defined(EA_29368214_BC70_483a_BBE0_6EE2D4B42E46__INCLUDED_)
