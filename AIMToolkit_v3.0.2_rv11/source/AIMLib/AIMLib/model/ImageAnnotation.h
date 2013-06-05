/*L
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#if !defined(EA_F006A3FC_7C5D_4991_A944_11205A5CF548__INCLUDED_)
#define EA_F006A3FC_7C5D_4991_A944_11205A5CF548__INCLUDED_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API ImageAnnotation : public Annotation
	{

	public:
		ImageAnnotation();
		ImageAnnotation(const ImageAnnotation& imageAnnotation);
		virtual ~ImageAnnotation();

		virtual AnnotationKind GetAnnotationKind() const;

		const Person& GetPatient() const;
		const SegmentationVector& GetSegmentationCollection() const;
		const GeoShapePtrVector& GetGeometricShapeCollection() const;
		const ImageReferencePtrVector& GetImageReferenceCollection() const;
		const TextAnnotationVector& GetTextAnnotationCollection() const;
		void SetPatient(const Person& patient);
		void SetSegmentationCollection(const SegmentationVector& segmentations);
		void SetGeometricShapeCollection(const GeoShapePtrVector& geometricShapes);
		void SetImageReferenceCollection(const ImageReferencePtrVector& imageReferences);
		void SetTextAnnotationCollection(const TextAnnotationVector& textAnnotations);

	private:
		void FreeAllShapes();
		void FreeAllImages();

		Person _patient;
		SegmentationVector _segmentationCollection;
		GeoShapePtrVector _geometricShapeCollection;
		ImageReferencePtrVector _imageReferenceCollection;
		TextAnnotationVector _textAnnotationCollection;
	};
}
#endif // !defined(EA_F006A3FC_7C5D_4991_A944_11205A5CF548__INCLUDED_)
