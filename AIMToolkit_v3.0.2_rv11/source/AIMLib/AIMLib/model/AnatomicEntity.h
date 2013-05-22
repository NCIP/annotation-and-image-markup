/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_BC0DE86A_6A89_4e3a_A977_FEDCA7497405__INCLUDED_)
#define EA_BC0DE86A_6A89_4e3a_A977_FEDCA7497405__INCLUDED_

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API AnatomicEntity
	{

	public:
		AnatomicEntity();
		AnatomicEntity(const AnatomicEntity& anatomicEntity);
		virtual ~AnatomicEntity();
		AnatomicEntity& operator=(const AnatomicEntity& pAnatomicEntity); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		AnatomicEntity* Clone() const;

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		double* GetAnnotatorConfidence() const;
		const std::string& GetLabel() const;
		bool GetIsPresent() const;
		const AnatomicEntityCharacteristicVector& GetAnatomicEntityCharacteristicCollection() const;
		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetAnnotatorConfidence(double* newVal);
		void SetLabel(const std::string& newVal);
		void SetIsPresent(bool newVal);
		void SetAnatomicEntityCharacteristicCollection(const AnatomicEntityCharacteristicVector& newVal);

	private:
		int _cagridId;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::auto_ptr<double> _annotatorConfidence;
		std::string _label;
		bool _isPresent;
		AnatomicEntityCharacteristicVector _anatomicEntityCharacteristicCollection;
	};

	typedef std::vector<AnatomicEntity> AnatomicEntityVector;

}
#endif // !defined(EA_BC0DE86A_6A89_4e3a_A977_FEDCA7497405__INCLUDED_)
