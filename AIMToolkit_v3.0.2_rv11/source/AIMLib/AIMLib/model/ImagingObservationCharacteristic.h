/*
  Classname: ImagingObservationCharacteristic

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_E1A94461_5368_4ac7_8E5F_2F027802D84F__INCLUDED_)
#define EA_E1A94461_5368_4ac7_8E5F_2F027802D84F__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImagingObservationCharacteristic
	{
	public:
		ImagingObservationCharacteristic();
		ImagingObservationCharacteristic(const ImagingObservationCharacteristic& imgObsCharacteristics);
		virtual ~ImagingObservationCharacteristic();
		ImagingObservationCharacteristic& operator=(const ImagingObservationCharacteristic& pImgObsCharacteristic); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagingObservationCharacteristic* Clone() const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		const std::string& GetComment() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		const CharacteristicQuantificationPtrVector& GetCharacteristicQuantificationCollection() const;
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetComment(const std::string& newVal);
		void SetAnnotatorConfidence(double* pNewVal);
		void SetLabel(const std::string& newVal);
		void SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& charachteristicQuantifications);

	protected:
		void FreeAllCharacteristicQuantifications();

		int _cagridId;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::string _comment;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;

		CharacteristicQuantificationPtrVector _characteristicQuantificationCollection;
	};

	typedef std::vector<ImagingObservationCharacteristic> ImagingObservationCharacteristicVector;
}
#endif // !defined(EA_E1A94461_5368_4ac7_8E5F_2F027802D84F__INCLUDED_)
