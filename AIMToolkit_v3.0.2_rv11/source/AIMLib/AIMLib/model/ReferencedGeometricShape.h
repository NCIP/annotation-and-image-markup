/*
  Classname: ReferencedGeometricShape

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLIB_REFERENCED_GEOMETRIC_SHAPE_INCLUDED_)
#define _AIMLIB_REFERENCED_GEOMETRIC_SHAPE_INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ReferencedGeometricShape
	{
	public:
		ReferencedGeometricShape(void);
		ReferencedGeometricShape(const ReferencedGeometricShape& refGeoShape);
		~ReferencedGeometricShape(void);
		ReferencedGeometricShape& operator=(const ReferencedGeometricShape& refGeoShape); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ReferencedGeometricShape* Clone() const;

		int GetReferencedShapeIdentifier() const;
		void SetReferencedShapeIdentifier(int newVal);

	protected:
		int _cagridId;
		int _referencedShapeIdentifier;
	};

	typedef std::vector<ReferencedGeometricShape> ReferencedGeometricShapeVector;
}
#endif // !defined(_AIMLIB_REFERENCED_GEOMETRIC_SHAPE_INCLUDED_)
