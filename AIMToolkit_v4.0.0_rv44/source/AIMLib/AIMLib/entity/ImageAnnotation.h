/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImageAnnotation_Class_
#define _AIMLib_ImageAnnotation_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImageAnnotation : public AnnotationEntity
	{
	public:
		ImageAnnotation(void);
		ImageAnnotation(const ImageAnnotation& imageAnnotation);
		ImageAnnotation& operator=(const ImageAnnotation& imageAnnotation);
		virtual ~ImageAnnotation(void);

		virtual AnnotationType GetAnnotationType() const;

		const ImageAnnotationStatementPtrVector& GetImageAnnotationStatementCollection() const;
		const ImageReferenceEntityPtrVector& GetImageReferenceEntityCollection() const;
		const MarkupEntityPtrVector& GetMarkupEntityCollection() const;
		const SegmentationEntityPtrVector& GetSegmentationEntityCollection() const;

		void SetImageAnnotationStatementCollection(const ImageAnnotationStatementPtrVector& newVal);
		void SetImageReferenceEntityCollection(const ImageReferenceEntityPtrVector& newVal);
		void SetMarkupEntityCollection(const MarkupEntityPtrVector& newVal);
		void SetSegmentationEntityCollection(const SegmentationEntityPtrVector& newVal);

	protected:
		ImageAnnotationStatementPtrVector _imageAnnotationStatementCollection; 
		ImageReferenceEntityPtrVector _imageReferenceEntityCollection;
		MarkupEntityPtrVector _markupEntityCollection;
		SegmentationEntityPtrVector _segmentationEntityCollection;
	};

	typedef std::vector<ImageAnnotation> ImageAnnotationVector;
}
#endif // _AIMLib_ImageAnnotation_Class_
