/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_DcmModel_Class_
#define _AIMLib_DcmModel_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API DcmModel : public BaseModel
	{
	public:
		// UID prefix to be used whenever AIMLib generates new UID
		DcmModel(const std::string& uidPrefix = _defaultUIDPrefix);
		~DcmModel(void);

		// Reads annotation from DICOM SR file
		virtual AnnotationCollection* ReadAnnotationCollectionFromFile(const std::string& fileName);
		// Writes annotation to DICOM SR file
		virtual void WriteAnnotationCollectionToFile(const AnnotationCollection* pAnnotationCollection, const std::string& fileName);

	private:
		std::string _uidPrefix; // vendor-specific UID prefix

		static const std::string _defaultUIDPrefix;
	};
}
#endif // _AIMLib_DcmModel_Class_
