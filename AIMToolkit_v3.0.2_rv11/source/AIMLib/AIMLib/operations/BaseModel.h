/*
  Classname: BaseModel

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_BaseModel_Class)
#define _AIMLib_BaseModel_Class

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
		virtual int ReadAnnotationsFromFile(const std::string& fileName) = 0;
		// Iterator over read annotations
		virtual Annotation* GetNextAnnotation(Annotation** pAnnotation) = 0;

		// Write annotations to file
		virtual void WriteAnnotationToFile(const Annotation& annotation, const std::string& fileName) = 0;
		virtual void WriteAnnotationsToFile(const AnnotationPtrVector& annotations, const std::string& fileName) = 0;

	protected:
		virtual void ClearAnnotations();

	//	AnnotationPtrVector::size_type _currentAnnotation; // current index into _annotations collection
		AnnotationPtrVector _annotations; // list of annotations read from an AIM document
	};

}

#endif // _AIMLib_BaseModel_Class
