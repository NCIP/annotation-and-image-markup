/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(_AIMLib_AIMCodes_Class)
#define _AIMLib_AIMCodes_Class

#include <string>
#include <map>
#include <vector>

#include "dcmtk/dcmsr/dsrdoc.h"

namespace aim_lib 
{
	// private coding scheme designator used for internal codes
	#define AIM_CODING_SCHEME_DESIGNATOR "99NCIAIM"
	// coding scheme version
	#define AIM_CODING_SCHEME_VERSION "04"
	// name of the private coding scheme
	#define AIM_CODING_SCHEME_NAME "AIM Coding Scheme"
	// organization responsible for the private coding scheme
	#define AIM_RESPONSIBLE_ORGANIZATION "Northwestern University, Department of Raiology, Imaging and Informatics Section, Chicago, IL, USA"


	class AIMCodes
	{
	public:
		~AIMCodes(void);

		static const DSRCodedEntryValue GetCalculationResultTypeValue(CalculationResult::CalculationResultType calculationResultType);
		static const DSRCodedEntryValue GetOrganizationalRoleValue(const std::string& organizationalRoleName);
		static const DSRCodedEntryValue GetPerformingRoleValue(const std::string& performmingRoleName);
		static const DSRCodedEntryValue GetUcumCodeValue(const std::string& unitAbbreviation);
		static const DSRCodedEntryValue GetCharacteristicQuantificationTypeValue(CharacteristicQuantification::QuantificationType charQuantificationType);
		static const DSRCodedEntryValue GetComparisonOperatorTypeValue(ComparisonOperatorType comparisonOperatorType);
		static const ComparisonOperatorType GetComparisonOperatorType(const DSRCodedEntryValue& comparisonOperatorCode);
		static const DSRCodedEntryValue GetBooleanCodeValue(bool boolValue);
		static const DSRCodedEntryValue GetScaleTypeValue(Scale::ScaleType scaleType);
		static const Scale::ScaleType GetScaleType(const DSRCodedEntryValue& scaleTypeCode);
		static const DSRCodedEntryValue GetEntityValue(const std::string& entityClassName);
		static const std::string& GetEntityClassName(const DSRCodedEntryValue& entityCode);
		static const DSRCodedEntryValue GetStatementPredicateValue(const std::string& statementPredicateClassName);
		static const std::string& GetStatementPredicateClassName(const DSRCodedEntryValue& statementPredicateCode);

		static const DSRCodedEntryValue EmptyCodedEntryValue; // returned when no matching value is found in the map
		static const DSRSpatialCoordinatesValue EmptySpatialCoordinateValue; // empty 2D spatial coordinate
		static const DSRSpatialCoordinates3DValue EmptySpatialCoordinate3DValue; // empty 3D spatial coordinate
		static const DSRImageReferenceValue EmptyImageReferenceValue; // empty image reference
		static const DSRNumericMeasurementValue EmptyNumericMeasurementValue; // empty numeric value
		
		// Creates DSRCodedEntryValue with the given arguments
		static const DSRCodedEntryValue CreateCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion = _T(""));

		// Creates AIM's DSRCodedEntryValue:
		// (codingSchemeDesignator = AIM_CODING_SCHEME_DESIGNATOR; codingScemeVersion = AIM_CODING_SCHEME_VERSION)
		static const DSRCodedEntryValue CreateAimCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning);

		static DSRCodedEntryValue CreateCodedEntryValueFromCd(const iso_21090::CD& cd);
		static iso_21090::CD CreateCdFromCodedEntryValue(const DSRCodedEntryValue& dsrCode);

	protected:
		AIMCodes(void);

		// These are typedef'ed maps used during various code lookups
		typedef std::map<std::string, std::string> StringMap; // used when all codes belong to the same Coding Scheme
		typedef std::map<std::string, std::pair<std::string, std::string> > String2PairMap; // used when codes come from different Coding Schemes
		typedef std::map<std::string, DSRCodedEntryValue> String2CodedEntryValueMap;
		typedef std::map<CalculationResult::CalculationResultType, DSRCodedEntryValue> CalcResultTypeMap;
		typedef std::map<CharacteristicQuantification::QuantificationType, DSRCodedEntryValue> CharQuantificationTypeMap;
		typedef std::map<ComparisonOperatorType, DSRCodedEntryValue> ComparisonOperatorTypeMap;
		typedef std::map<bool, DSRCodedEntryValue> BooleanTypeMap;
		typedef std::map<Scale::ScaleType, DSRCodedEntryValue> ScaleTypeMap;

		template<typename T, typename M>
		static const M FindMapValue(const std::map<T,M>& theMap, const T& lookupValue, const M& defaultValue);

		template<typename T>
		static const T& FindMapKeyByCodeValue(const std::map<T,DSRCodedEntryValue>& theMap, const DSRCodedEntryValue& lookupValue, const T& defaultValue);

		// Do actual lookup
		static const DSRCodedEntryValue GetMappedValue(const StringMap& lookupMap, const std::string& codingScheme, const std::string& lookupValue);
		static const DSRCodedEntryValue GetMappedValue(const String2PairMap& lookupMap, const std::string& lookupValue);

		// Calculation Result Types
		static const CalcResultTypeMap InitializeCalculationResultTypes();

		// Organizational Roles - BCID(7452)
		static const StringMap InitializeOrganizationalRoles();

		// Performing Roles - BCID(7453)
		static const StringMap InitializePerformingRoles();

		// UCUM Units
		static const StringMap InitializeUcumUnits();

		// Characteristic Quantification Types - aimcid013
		static const CharQuantificationTypeMap InitializeCharQuantificationTypes();

		// Comparison Operator Types
		static const ComparisonOperatorTypeMap InitializeComparisonOperatorTypes();
		static const ComparisonOperatorTypeMap& GetComparisonOperatorTypes();

		// Boolean
		static const BooleanTypeMap InitializeBooleanTypes();

		// Scale Types - aimcid015
		static const ScaleTypeMap InitializeScaleTypes();
		static const ScaleTypeMap& GetScaleTypes();

		// Annotation Entities - aimcid016
		static const String2CodedEntryValueMap InitializeAnnotationEnities();
		static const String2CodedEntryValueMap& GetAnnotationEnities();

		// AIM Statements Predicates - aimcid017
		static const String2CodedEntryValueMap InitializeStatementPredicates();
		static const String2CodedEntryValueMap& GetStatementPredicates();

		static const std::string _emptyStr;
	};
}

#endif // _AIMLib_AIMCodes_Class
