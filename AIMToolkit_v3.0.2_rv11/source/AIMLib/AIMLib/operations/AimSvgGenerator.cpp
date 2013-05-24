/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../model/AimHeaders.h"
#include "AimSvgGenerator.h"

#include <cmath>

using namespace aim_lib;

AimSvgGenerator::AimSvgGenerator(void)
{
}

AimSvgGenerator::~AimSvgGenerator(void)
{
}

const std::string AimSvgGenerator::GetAimModelSvg(const ImageAnnotation& imgAnnotation)
{
	std::string xmlToReturn;
	int nestingLevel = 0;

	AppendLine(xmlToReturn, "<svg>");
	// TODO

	GeoShapePtrVector ptrGeoShapes = const_cast<ImageAnnotation&>(imgAnnotation).GetGeometricShapeCollection();

	if (ptrGeoShapes.size() > 0)
	{
		for(GeoShapePtrVector::iterator iter = ptrGeoShapes.begin(); iter < ptrGeoShapes.end(); iter++)
		{
			GeometricShape* pGeoShape = (*iter);
			if (pGeoShape != NULL)
			{
				if (pGeoShape->GetTypeName() == C_SHAPE_NAME_CIRCLE)
				{
					Circle* pCircle = (Circle*)pGeoShape;
					ConvertCircleToSvg(*pCircle, xmlToReturn, 1);
				}
				else if (pGeoShape->GetTypeName() == C_SHAPE_NAME_POINT)
				{
					Point* pPoint = (Point*)pGeoShape;
					ConvertPointToSvg(*pPoint, xmlToReturn, 1);
				}
				else if (pGeoShape->GetTypeName() == C_SHAPE_NAME_MULTIPOINT)
				{
					ConvertMultiPointToSvg(*((MultiPoint*)pGeoShape), xmlToReturn, 1);
				}
				else if (pGeoShape->GetTypeName() == C_SHAPE_NAME_ELLIPSE)
				{
					ConvertEllipseToSvg(*((Ellipse*)pGeoShape), xmlToReturn, 1);
				}
				else if (pGeoShape->GetTypeName() == C_SHAPE_NAME_POLYLINE)
				{
					ConvertPolylineToSvg(*((Polyline*)pGeoShape), xmlToReturn, 1);
				}
				else
				{
					assert(false); // we got an unknown shape type
				}
			}
		}
	}
	else
	{
		// TODO - do we need some kind of "No data" message?
	}

	AppendLine(xmlToReturn, "</svg>");

	return xmlToReturn;
}

std::string& AimSvgGenerator::AppendLine(std::string &strBuffer, const std::string &strToAppend, int nestingLevel/* = 0*/)
{
	const static std::string nestingPadding = "\t";
	const static std::string newLineChar = "\n";

	for(int i=0; i < nestingLevel; i++)
		strBuffer.append(nestingPadding);

	strBuffer.append(strToAppend).append(newLineChar);

	return strBuffer;
}

void AimSvgGenerator::ConvertCircleToSvg(aim_lib::Circle &circle, std::string &strBuffer, int nestingLevel)
{
	// TODO
	// <circle cx="150" cy="100" r="50" />

	// FIXME - sort out 2D/3D stuff
	//SpatialCoordinate center2d = circle.GetCenter();
	//SpatialCoordinate radiusPoint = circle.GetRadiusPoint();
	//assert(center2d.GetZ() == 0); // We're dealing with 2D coordinates for now
	//long rad = (long)ceil(sqrt(pow(double(radiusPoint.GetX() - center2d.GetX()), 2) +
	//	pow(double(radiusPoint.GetY() - center2d.GetY()), 2)));

	//const static int bufLen = 256;
	//char buf[bufLen];
	//int strLength = sprintf_s(buf, bufLen, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" />", center2d.GetX(), center2d.GetY(), rad);
	//assert(strLength < bufLen);

	//this->AppendLine(strBuffer, buf, nestingLevel);
}

void AimSvgGenerator::ConvertPointToSvg(const Point& point, std::string &strBuffer, int nestingLevel)
{
	std::string xmlToReturn;

	// TODO

}

void AimSvgGenerator::ConvertMultiPointToSvg(aim_lib::MultiPoint &multiPoin, std::string &strBuffer, int nestingLevel)
{
	// TODO
}

void AimSvgGenerator::ConvertEllipseToSvg(aim_lib::Ellipse &ellipse, std::string &strBuffer, int nestingLevel)
{
	// TODO
}

void AimSvgGenerator::ConvertPolylineToSvg(aim_lib::Polyline &polyline, std::string &strBuffer, int nestingLevel)
{
	// TODO
}
