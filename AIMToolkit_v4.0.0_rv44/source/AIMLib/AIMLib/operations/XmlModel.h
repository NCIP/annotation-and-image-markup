/*
*  Copyright Northwestern University
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
		void WriteAnnotationCollectionToFile(const AnnotationCollection* pAnnotationCollection, const std::string& fileName);

		// Write xml to char buffer
		std::string::size_type WriteAnnotationCollectionToXmlString(const AnnotationCollection* pAnnotationCollection, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize);

		// Read from XML file
		AnnotationCollection* ReadAnnotationCollectionFromFile(const std::string& fileName);
		AnnotationCollection* ReadAnnotationCollectionFromXmlString(const std::string& xmlIn);

	protected:
		std::string _xmlFileName;
	};
}

#endif // _AIMLib_XmlModel_Class