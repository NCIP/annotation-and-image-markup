/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_AnnotationOfAnnotation_Class_
#define _AIMLib_AnnotationOfAnnotation_Class_

#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API AnnotationOfAnnotation : public AnnotationEntity
	{
	public:
		AnnotationOfAnnotation(void);
		AnnotationOfAnnotation(const AnnotationOfAnnotation& annotationOfAnnotation);
		AnnotationOfAnnotation& operator=(const AnnotationOfAnnotation& annotationOfAnnotation);
		virtual ~AnnotationOfAnnotation(void);

		virtual AnnotationType GetAnnotationType() const;

		const AdjudicationObservation* GetAdjudicationObservation() const;
		const AnnotationOfAnnotationStatementPtrVector& GetAnnotationOfAnnotationStatementCollection() const;

		void SetAdjudicationObservation(const AdjudicationObservation* newVal);
		void SetAnnotationOfAnnotationStatementCollection(const AnnotationOfAnnotationStatementPtrVector& newVal);
	protected:
		std::auto_ptr<AdjudicationObservation> _adjudicationObservation;
		AnnotationOfAnnotationStatementPtrVector _annotationOfAnnotationStatementCollection;
	};
	
	typedef std::vector<AnnotationOfAnnotation> AnnotationOfAnnotationVector;
}
#endif // _AIMLib_AnnotationOfAnnotation_Class_
