/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_00665BAB_53D0_46cd_BD27_79B170A67269__INCLUDED_)
#define EA_00665BAB_53D0_46cd_BD27_79B170A67269__INCLUDED_

#include <string>
#include <ctime>
#include <memory>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_IMAGE_ANNOTATION_NAME			std::string("ImageAnnotation")
#define C_ANNOTATATION_ANNOTATION_NAME	std::string("AnnotationOfAnnotation")

	class AIMLIB_API Annotation : public AimBase
	{
	public:
		enum AnnotationKind {
			AK_ImageAnnotation,
			AK_AnnotationOfAnnotation,
			AK_Unknown
		};

		virtual ~Annotation();

		virtual AnnotationKind GetAnnotationKind() const = 0;

		const std::string& GetAimVersion() const;
		const std::string& GetUniqueIdentifier() const;
		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		const std::string& GetName() const;
		const std::string& GetComment() const;
		const DateTime& GetDateTime() const;
		const std::string& GetPrecedentReferencedAnnotationUID() const;
		const User* GetUser() const;
		const Equipment* GetEquipment() const;
		const AimStatus* GetAimStatus() const;
		const AnatomicEntityVector& GetAnatomicEntityCollection() const;
		const ImagingObservationVector& GetImagingObservationCollection() const;
		const CalculationVector& GetCalculationCollection() const;
		const InferenceVector& GetInferenceCollection() const;
		void SetAimVersion(const std::string& newVal);
		void SetUniqueidentifier(const std::string& newVal);
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetName(const std::string& newVal);
		void SetComment(const std::string& newVal);
		void SetDateTime(const DateTime& newVal);
		void SetPrecedentReferencedAnnotationUID(const std::string& newVal);
		void SetUser(const User* user);
		void SetEquipment(const Equipment* equipment);
		void SetAimStatus(const AimStatus* aimStatus);
		void SetAnatomicEntityCollection(const AnatomicEntityVector& anatomicEntity);
		void SetImagingObservationCollection(const ImagingObservationVector& imagingObservation);
		void SetCalculationCollection(const CalculationVector& calculation);
		void SetInferenceCollection(const InferenceVector& inferences);

	protected:
		Annotation(const std::string& typeName);
		Annotation(const Annotation& annotation);

		int _cagridId;
		std::string _uniqueIdentifier;
		std::string _aimVersion;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		/**
		* UTF Date and Time that the annotation wa created
		*/
		DateTime _dateTime;
		/**
		* Human readable colloquial name of the annotation not guaranteed to be unique
		*/
		std::string _name;
		std::string _comment;
		std::string _precedentReferencedAnnotationUID;
		std::auto_ptr<User> _user;
		std::auto_ptr<Equipment> _equipment;
		std::auto_ptr<AimStatus> _aimStatus;
		AnatomicEntityVector _anatomicEntityCollection;
		ImagingObservationVector _imagingObservationCollection;
		CalculationVector _calculationCollection;
		InferenceVector _inferenceCollection;
	};

	typedef std::vector<Annotation*> AnnotationPtrVector;
}
#endif // !defined(EA_00665BAB_53D0_46cd_BD27_79B170A67269__INCLUDED_)
