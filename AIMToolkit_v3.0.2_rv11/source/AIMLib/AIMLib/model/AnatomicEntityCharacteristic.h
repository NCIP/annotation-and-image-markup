/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#if !defined(_AIMLIB_ANATOMIC_ENTITY_CHARACTERISTIC_INCLUDED_)
#define _AIMLIB_ANATOMIC_ENTITY_CHARACTERISTIC_INCLUDED_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API AnatomicEntityCharacteristic
	{
	public:
		AnatomicEntityCharacteristic(void);
		AnatomicEntityCharacteristic(const AnatomicEntityCharacteristic& anatomicEntCharacteristic);
		virtual ~AnatomicEntityCharacteristic(void);
		AnatomicEntityCharacteristic& operator=(const AnatomicEntityCharacteristic& anatomicEntCharacteristic); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		AnatomicEntityCharacteristic* Clone() const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		const CharacteristicQuantificationPtrVector& GetCharacteristicQuantificationCollection() const;
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
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
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;

		CharacteristicQuantificationPtrVector _characteristicQuantificationCollection;
	};

	typedef std::vector<AnatomicEntityCharacteristic> AnatomicEntityCharacteristicVector;
}
#endif // !(defined(_AIMLIB_ANATOMIC_ENTITY_CHARACTERISTIC_INCLUDED_)
