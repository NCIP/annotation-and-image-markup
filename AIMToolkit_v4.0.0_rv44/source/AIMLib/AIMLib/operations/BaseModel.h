/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_BaseModel_Class_
#define _AIMLib_BaseModel_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API BaseModel
	{
	public:
		BaseModel(void);
		virtual ~BaseModel(void);

		// AIM model version
		static const char AIM_MODEL_VERSION[];

		// Read annotations from file
		virtual AnnotationCollection* ReadAnnotationCollectionFromFile(const std::string& fileName) = 0;

		// Write annotations to file
		virtual void WriteAnnotationCollectionToFile(const AnnotationCollection* annotationCollection, const std::string& fileName) = 0;

	protected:
		// Runs given collection through the ModelValidator. Throws exception if not valid.
		virtual void ValidateCollection(const AnnotationCollection& annotationCollection);
	};
}

#endif // _AIMLib_BaseModel_Class_
