/*
  Classname: ImagingObservation

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_A923645E_7C49_48b9_9266_ABBE504D7BFC__INCLUDED_)
#define EA_A923645E_7C49_48b9_9266_ABBE504D7BFC__INCLUDED_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API ImagingObservation
	{
	public:
		ImagingObservation();
		ImagingObservation(const ImagingObservation& imgObservation);
		virtual ~ImagingObservation();
		ImagingObservation& operator=(const ImagingObservation& pImagingObservation); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagingObservation* Clone() const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		const std::string& GetComment() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		bool GetIsPresent() const;
		const ReferencedGeometricShape* GetReferencedGeometricShape() const;
		const ImagingObservationCharacteristicVector& GetImagingObservationCharacteristicCollection() const;
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetComment(const std::string& newVal);
		void SetAnnotatorConfidence(double* newVal);
		void SetLabel(const std::string& newVal);
		void SetIsPresent(bool newVal);
		void SetReferencedGeometricShape(const ReferencedGeometricShape* refGeoShape);
		void SetImagingObservationCharacteristicCollection(const ImagingObservationCharacteristicVector& newVal);

	private:
		int _cagridId;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::string _comment;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;
		bool _isPresent;
		std::auto_ptr<ReferencedGeometricShape> _referencedGeometricShape;

		ImagingObservationCharacteristicVector _imagingObservationCharachteristicCollection;
	};

	typedef std::vector<ImagingObservation> ImagingObservationVector;
}
#endif // !defined(EA_A923645E_7C49_48b9_9266_ABBE504D7BFC__INCLUDED_)
