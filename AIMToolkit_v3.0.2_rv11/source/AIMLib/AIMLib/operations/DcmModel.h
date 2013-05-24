/*
  Classname: DcmModel

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_DcmModel_Class)
#define _AIMLib_DcmModel_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API DcmModel : public BaseModel
	{
	public:
		// UID prefix to be used whenever AIMLib generates new UID
		DcmModel(const std::string& uidPrefix = _defaultUIDPrefix);
		~DcmModel(void);

		// Writes annotation to DICOM SR file
		void WriteAnnotationToFile(const Annotation& annotation, const std::string& fileName);
		void WriteAnnotationsToFile(const AnnotationPtrVector& annotations, const std::string& fileName);
		//void WriteAnnotationToFile(const Annotation& annotation, const DicomTagCollection& headerValues, const std::string& fileName);
		//void WriteAnnotationsToFile(const AnnotationPtrVector& annotations, const DicomTagCollection& headerValues, const std::string& fileName);

		// Reads annotation from DICOM SR file
		void ReadAnnotationFromFile(Annotation** pAnnotation, const std::string& fileName);

		int ReadAnnotationsFromFile(const std::string& fileName);
		Annotation* GetNextAnnotation(Annotation** pAnnotation);

	private:
		//AnnotationPtrVector::size_type _currentAnnotation;
		//AnnotationPtrVector _annotations;

		std::string _uidPrefix; // vendor-specific UID prefix

		static const std::string _defaultUIDPrefix;
	};
}
#endif // _AIMLib_DcmModel_Class