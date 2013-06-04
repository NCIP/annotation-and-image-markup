/*
  Classname: AimSvgGenerator

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_AimSvgGenerator_Class)
#define _AIMLib_AimSvgGenerator_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API AimSvgGenerator
	{
	public:
		AimSvgGenerator(void);
		~AimSvgGenerator(void);

		const std::string GetAimModelSvg(const ImageAnnotation& annotation);

	protected:
		void ConvertCircleToSvg(Circle& circle, std::string& strBuffer, int nestingLevel);
		void ConvertPointToSvg(const Point& point, std::string& strBuffer, int nestingLevel);
		void ConvertMultiPointToSvg(MultiPoint& multiPoin, std::string& strBuffer, int nestingLevel);
		void ConvertEllipseToSvg(Ellipse& ellipse, std::string& strBuffer, int nestingLevel);
		void ConvertPolylineToSvg(Polyline& polyline, std::string& strBuffer, int nestingLevel);

		std::string& AppendLine(std::string& strBuffer, const std::string& strToAppend, int nestingLevel = 0);
	};
}
#endif // _AIMLib_AimSvgGenerator_Class
