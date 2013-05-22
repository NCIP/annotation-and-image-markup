/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_3B3AACEB_9421_47e2_AA73_A6DB6F1E23D7__INCLUDED_)
#define EA_3B3AACEB_9421_47e2_AA73_A6DB6F1E23D7__INCLUDED_

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ReferencedAnnotation
	{
	public:
		ReferencedAnnotation();
		ReferencedAnnotation(const ReferencedAnnotation& referencedAnnoation);
		virtual ~ReferencedAnnotation();
		ReferencedAnnotation& operator=(const ReferencedAnnotation& referencedAnnotation); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor

		const std::string& GetReferencedAnnotationUID() const;
		AnnotationRole* GetAnnotationRole() const;
		void SetReferencedAnnotationUID(const std::string& newVal);
		void SetAnnotationRole(const AnnotationRole* pAnnotationRole);

	private:
		int _cagridId;
		std::string _referencedAnnotationUID;
		std::auto_ptr<AnnotationRole> _annotationRole;

	};

	typedef std::vector<ReferencedAnnotation>  ReferencedAnnotationVector;
}
#endif // !defined(EA_3B3AACEB_9421_47e2_AA73_A6DB6F1E23D7__INCLUDED_)
