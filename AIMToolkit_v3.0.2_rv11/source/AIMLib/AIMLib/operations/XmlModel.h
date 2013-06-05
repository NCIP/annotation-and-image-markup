/*
  Classname: XmlModel

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_XmlModel_Class)
#define _AIMLib_XmlModel_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API XmlModel : public BaseModel
	{
	public:
		XmlModel(void);
		~XmlModel(void);

		// Write to XML file
		void WriteAnnotationToFile(const Annotation& annotation, const std::string& fileName);
		void WriteAnnotationsToFile(const AnnotationPtrVector& annotations, const std::string& fileName);

		// Write xml to char buffer
		std::string::size_type WriteAnnotationToXmlString(Annotation* pAnnotation, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize);
		std::string::size_type WriteAnnotationsToXmlString(const AnnotationPtrVector& annotations, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize);

		Annotation::AnnotationKind ReadAnnotationFromFile(Annotation** ppAnnotation, const std::string& fileName);
		Annotation::AnnotationKind ReadAnnotationFromXmlString(Annotation** ppAnnotation, const std::string& xmlIn);

		// Read from XML file
		int ReadAnnotationsFromFile(const std::string& fileName);
		Annotation* GetNextAnnotation(Annotation** pAnnotation);

	protected:
		std::string _xmlFileName;
		//AnnotationPtrVector::size_type _currentAnnotation; // current index into _annotations collection
		//AnnotationPtrVector _annotations;
	};
}

#endif // _AIMLib_XmlModel_Class