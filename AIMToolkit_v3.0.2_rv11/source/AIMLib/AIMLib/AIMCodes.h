/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_AIMCodes_Class)
#define _AIMLib_AIMCodes_Class

#include <string>
#include <map>
#include <vector>

//#include "dcmtk/ofstd/ofcond.h"
#include "dcmtk/dcmsr/dsrdoc.h"


namespace aim_lib 
{
	// private coding scheme designator used for internal codes
	#define AIM_CODING_SCHEME_DESIGNATOR "99NCIAIM"
	// coding scheme version
	#define AIM_CODING_SCHEME_VERSION "03"
	// name of the private coding scheme
	#define AIM_CODING_SCHEME_NAME "AIM Coding Scheme"
	// organization responsible for the private coding scheme
	#define AIM_RESPONSIBLE_ORGANIZATION "Northwestern University, Department of Raiology, Imaging and Informatics Section, Chicago, IL, USA"


	class AIMCodes
	{
	public:
		AIMCodes(void);
		~AIMCodes(void);

		static const DSRCodedEntryValue GetCalculationResultTypeValue(CalculationResultType calculationResultType);
		static const DSRCodedEntryValue GetOrganizationalRoleValue(const std::string& organizationalRoleName);
		static const DSRCodedEntryValue GetPerformingRoleValue(const std::string& performmingRoleName);
		static const DSRCodedEntryValue GetUcumCodeValue(const std::string& unitAbbreviation);
		static const DSRCodedEntryValue GetCharacteristicQuantificationTypeValue(CharacteristicQuantification::E_QuantificationType charQuantificationType);
		static const DSRCodedEntryValue GetComparisonOperatorTypeValue(ComparisonOperatorType comparisonOperatorType);
		static const ComparisonOperatorType GetComparisonOperatorType(const DSRCodedEntryValue& comparisonOperatorCode);
		static const DSRCodedEntryValue GetBooleanCodeValue(bool boolValue);

		static const DSRCodedEntryValue EmptyCodedEntryValue; // returned when no matching value is found in the map
		static const DSRSpatialCoordinatesValue EmptySpatialCoordinateValue; // empty spatial coordinate
		static const DSRImageReferenceValue EmptyImageReferenceValue; // empty image reference
		static const DSRNumericMeasurementValue EmptyNumericMeasurementValue; // empty numeric value
		
		// Creates DSRCodedEntryValue with the given arguments
		static const DSRCodedEntryValue CreateCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion = _T(""));

		// Creates AIM's DSRCodedEntryValue:
		// (codingSchemeDesignator = AIM_CODING_SCHEME_DESIGNATOR; codingScemeVersion = AIM_CODING_SCHEME_VERSION)
		static const DSRCodedEntryValue CreateAimCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning);

	protected:
		// These are typedef'ed maps used during various code lookups
		typedef std::map<std::string, std::string> StringMap; // used when all codes belong to the same Coding Scheme
		typedef std::map<std::string, std::pair<std::string, std::string> > String2PairMap; // used when codes come from different Coding Schemes
		typedef std::map<CalculationResultType, DSRCodedEntryValue> CalcResultTypeMap;
		typedef std::map<CharacteristicQuantification::E_QuantificationType, DSRCodedEntryValue> CharQuantificationTypeMap;
		typedef std::map<ComparisonOperatorType, DSRCodedEntryValue> ComparisonOperatorTypeMap;
		typedef std::map<bool, DSRCodedEntryValue> BooleanTypeMap;

		// Do actual lookup
		static const DSRCodedEntryValue GetMappedValue(const StringMap& lookupMap, const std::string& codingScheme, const std::string& lookupValue);
		static const DSRCodedEntryValue GetMappedValue(const String2PairMap& lookupMap, const std::string& lookupValue);

		// Calculation Result Types
		static const CalcResultTypeMap InitializeCalculationResultTypes();
//		static const CalcResultTypeMap _calculationResultTypes;

		// Organizational Roles - BCID(7452)
		static const StringMap InitializeOrganizationalRoles();
		static const StringMap _organizationalRoles;

		// Performing Roles - BCID(7453)
		static const StringMap InitializePerformingRoles();
		static const StringMap _performingRoles;

		// UCUM Units
		static const StringMap InitializeUcumUnits();
		static const StringMap _ucumUnits;

		// Characteristic Quantification Types - aimcid013
		static const CharQuantificationTypeMap InitializeCharQuantificationTypes();

		// Comparison Operator Types
		static const ComparisonOperatorTypeMap InitializeComparisonOperatorTypes();

		// Boolean
		static const BooleanTypeMap InitializeBooleanTypes();
	};
}

#endif // _AIMLib_AIMCodes_Class
