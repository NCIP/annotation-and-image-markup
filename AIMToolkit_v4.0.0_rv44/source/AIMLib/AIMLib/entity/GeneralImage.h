/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_GeneralImage_Class_
#define _AIMLib_GeneralImage_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API GeneralImage
	{
	public:
		GeneralImage(void);
		GeneralImage(const GeneralImage& generalImage);
		virtual ~GeneralImage(void);
		GeneralImage& operator=(const GeneralImage& generalImage); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		GeneralImage* Clone() const;

		const std::string& GetPatientOrientationColumn() const;
		const std::string& GetPatientOrientationRow() const;

		void SetPatientOrientationColumn(const std::string& newVal);
		void SetPatientOrientationRow(const std::string& newVal);

	protected:
		std::string _patientOrientationColumn;
		std::string _patientOrientationRow;
	};
}
#endif // _AIMLib_GeneralImage_Class_
