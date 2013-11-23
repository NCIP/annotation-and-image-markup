/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
