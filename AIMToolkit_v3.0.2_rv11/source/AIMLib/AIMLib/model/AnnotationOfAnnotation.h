/*
  Classname: AnnotationOfAnnotation

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_639148C8_3750_48cc_AC86_D056799FB5C9__INCLUDED_)
#define EA_639148C8_3750_48cc_AC86_D056799FB5C9__INCLUDED_

#include <string>

namespace aim_lib
{
	class AIMLIB_API AnnotationOfAnnotation : public Annotation
	{
	public:
		AnnotationOfAnnotation();
		AnnotationOfAnnotation(const AnnotationOfAnnotation& annotationOfAnnotaion);
		virtual ~AnnotationOfAnnotation();

		virtual AnnotationKind GetAnnotationKind() const;

		const ReferencedAnnotationVector& GetReferencedAnnotationCollection() const;
		void SetReferencedAnnotationCollection(const ReferencedAnnotationVector& referencedAnnotationCollection);

	private:
		ReferencedAnnotationVector _referenceAnnotationCollection;

	};
}
#endif // !defined(EA_639148C8_3750_48cc_AC86_D056799FB5C9__INCLUDED_)
