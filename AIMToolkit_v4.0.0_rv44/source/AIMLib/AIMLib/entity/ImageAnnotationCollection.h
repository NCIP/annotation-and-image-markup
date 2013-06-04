/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImageAnnotationCollection_Class_
#define _AIMLib_ImageAnnotationCollection_Class_

#include <memory>

namespace aim_lib
{
	class AIMLIB_API ImageAnnotationCollection : public AnnotationCollection
	{
	public:
		ImageAnnotationCollection(void);
		ImageAnnotationCollection(const ImageAnnotationCollection& annotationCollection);
		virtual ~ImageAnnotationCollection(void);
		virtual ImageAnnotationCollection* Clone() const;
		virtual AnnotationCollectionType GetAnnotationCollectionType() const;
		virtual void ClearAnnotations();

		const Person* GetPerson() const;
		const ImageAnnotationVector& GetImageAnnotations() const;

		void SetPerson(const Person* newVal);
		void SetImageAnnotations(const ImageAnnotationVector& newVal);
	protected:
		std::auto_ptr<Person> _person;
		ImageAnnotationVector _imageAnnotationCollection;
	};
}
#endif // _AIMLib_ImageAnnotationCollection_Class_
