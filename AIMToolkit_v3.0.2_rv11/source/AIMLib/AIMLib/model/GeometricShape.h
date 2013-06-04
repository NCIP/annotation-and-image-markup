/*
  Classname: GeometricShape

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_79F62C10_77C9_403b_AAFC_0F6585358882__INCLUDED_)
#define EA_79F62C10_77C9_403b_AAFC_0F6585358882__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_SHAPE_NAME_CIRCLE		std::string("Circle")
#define C_SHAPE_NAME_POINT		std::string("Point")
#define C_SHAPE_NAME_MULTIPOINT	std::string("Multipoint")
#define C_SHAPE_NAME_ELLIPSE	std::string("Ellipse")
#define C_SHAPE_NAME_POLYLINE	std::string("Polyline")

	class AIMLIB_API GeometricShape : public AimBase
	{
	public:
		enum E_ShapeType
		{
			SHT_Circle,
			SHT_Point,
			SHT_Multipoint,
			SHT_Ellipse,
			SHT_Polyline,
			SHT_Unknown = -1
		};

	public:
		GeometricShape& operator=(const GeometricShape& shape);
		virtual ~GeometricShape();
		virtual GeometricShape* Clone() const = 0;

		int GetShapeIdentifier() const;
		bool GetIncludeFlag() const;
		const std::string& GetLineColor() const;
		const std::string& GetLineOpacity() const;
		const std::string& GetLineStyle() const;
		const std::string& GetLineThickness() const;
		const SpatialCoordPtrVector& GetSpatialCoordinateCollection() const;
		void SetShapeIdentifier(int shapeIdentifier);
		void SetIncludeFlag(bool newVal);
		void SetLineColor(const std::string& newVal);
		void SetLineOpacity(const std::string& newVal);
		void SetLineStyle(const std::string& newVal);
		void SetLineThickness(const std::string& newVal);
		virtual void SetSpatialCoordinateCollection(const SpatialCoordPtrVector& spatialCoordinateCollection);

		const E_ShapeType GetShapeType() const;

	protected:
		GeometricShape(const std::string& typeName, long numOfPoints = -1);
		GeometricShape(const GeometricShape& shape);

		void FreeAllSpatialCoords();
		void ReplaceSpatialCoordinate(SpatialCoordPtrVector::size_type position, const SpatialCoordinate& newSpatialCoordinate);

		int _cagridId;
		int _shapeIdetifier;
		bool _includeFlag;
		std::string _lineColor;
		std::string _lineOpacity;
		std::string _lineStyle;
		std::string _lineThickness;
		SpatialCoordPtrVector _spatialCoordinateCollection;

		long _numOfPoints;
	};

	typedef std::vector<GeometricShape*> GeoShapePtrVector;

}
#endif // !defined(EA_79F62C10_77C9_403b_AAFC_0F6585358882__INCLUDED_)
