/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_AnnotationOfAnnotationCollection_Class_
#define _AIMLib_AnnotationOfAnnotationCollection_Class_

namespace aim_lib
{
	class AIMLIB_API AnnotationOfAnnotationCollection : public AnnotationCollection
	{
	public:
		AnnotationOfAnnotationCollection(void);
		AnnotationOfAnnotationCollection(const AnnotationOfAnnotationCollection& annotationCollection);
		virtual ~AnnotationOfAnnotationCollection(void);
		virtual AnnotationOfAnnotationCollection* Clone() const;

		virtual AnnotationCollectionType GetAnnotationCollectionType() const;
		virtual void ClearAnnotations();

		const AnnotationOfAnnotationVector& GetAnnotationOfAnnotations() const;
		void SetAnnotationOfAnnotations(const AnnotationOfAnnotationVector& newVal);                                                               
	protected:
		AnnotationOfAnnotationVector _annotationOfAnnotationCollection;
	};
}
#endif // _AIMLib_AnnotationOfAnnotationCollection_Class_
