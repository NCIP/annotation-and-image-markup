/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "stdafx.h"

#include "dcmtk/ofstd/ofcond.h"

#include "model/AimHeaders.h"
#include "AIMUtil.h"
#include "AIMCodes.h"

using namespace aim_lib;

// Initialize static values
const DSRCodedEntryValue AIMCodes::EmptyCodedEntryValue = DSRCodedEntryValue();
const DSRSpatialCoordinatesValue AIMCodes::EmptySpatialCoordinateValue = DSRSpatialCoordinatesValue();
const DSRImageReferenceValue AIMCodes::EmptyImageReferenceValue = DSRImageReferenceValue();
const DSRNumericMeasurementValue AIMCodes::EmptyNumericMeasurementValue = DSRNumericMeasurementValue();

// Initialize static lookup tables
// Calculation Result Types
//const AIMCodes::CalcResultTypeMap AIMCodes::_calculationResultTypes = AIMCodes::InitializeCalculationResultTypes();
// Organizational Role Types
const AIMCodes::StringMap AIMCodes::_organizationalRoles = AIMCodes::InitializeOrganizationalRoles();
// Performing Role Types
const AIMCodes::StringMap AIMCodes::_performingRoles = AIMCodes::InitializePerformingRoles();
// UCUM Units
const AIMCodes::StringMap AIMCodes::_ucumUnits = AIMCodes::InitializeUcumUnits();
// Segmentation Types
//const AIMCodes::SegmentationTypeMap AIMCodes::_segmentationTypes = AIMCodes::InitializeSegmentationTypes();

AIMCodes::AIMCodes(void)
{
}

AIMCodes::~AIMCodes(void)
{
}

const DSRCodedEntryValue AIMCodes::GetCalculationResultTypeValue(CalculationResultType calculationResultType)
{
	// initialize map on the first use
	static CalcResultTypeMap calcResultTypes = AIMCodes::InitializeCalculationResultTypes();

	CalcResultTypeMap::const_iterator iterValue = calcResultTypes.find(calculationResultType);
	//CalcResultTypeMap::const_iterator iterValue = _calculationResultTypes.find(calculationResultType);

	if (iterValue != calcResultTypes.end())
//	if (iterValue != _calculationResultTypes.end())
		return iterValue->second;

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for Calculation Result Type(" << calculationResultType << ") was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const DSRCodedEntryValue AIMCodes::GetOrganizationalRoleValue(const std::string& organizationalRoleName)
{
	return AIMCodes::GetMappedValue(_organizationalRoles, "DCM", organizationalRoleName);
}

const DSRCodedEntryValue AIMCodes::GetPerformingRoleValue(const std::string& performingRoleName)
{
	return AIMCodes::GetMappedValue(_performingRoles, "DCM", performingRoleName);
}

const DSRCodedEntryValue AIMCodes::GetUcumCodeValue(const std::string& unitAbbreviation)
{
	return AIMCodes::GetMappedValue(_ucumUnits, "DCM", unitAbbreviation);
}

const DSRCodedEntryValue AIMCodes::GetCharacteristicQuantificationTypeValue(CharacteristicQuantification::E_QuantificationType charQuantificationType)
{
	static CharQuantificationTypeMap charQuantificationTypes = AIMCodes::InitializeCharQuantificationTypes();

	CharQuantificationTypeMap::const_iterator iterValue = charQuantificationTypes.find(charQuantificationType);

	if (iterValue != charQuantificationTypes.end())
		return iterValue->second;

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for characteristic quantification type(" << charQuantificationType << ") was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const DSRCodedEntryValue AIMCodes::GetComparisonOperatorTypeValue(ComparisonOperatorType comparisonOperatorType)
{
	static ComparisonOperatorTypeMap comparisonOperatorTypes = AIMCodes::InitializeComparisonOperatorTypes();

	ComparisonOperatorTypeMap::const_iterator iterValue = comparisonOperatorTypes.find(comparisonOperatorType);

	if (iterValue != comparisonOperatorTypes.end())
		return iterValue->second;

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for comparison operator type(" << comparisonOperatorType << ") was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const ComparisonOperatorType AIMCodes::GetComparisonOperatorType(const DSRCodedEntryValue& comparisonOperatorCode)
{
	static ComparisonOperatorTypeMap comparisonOperatorTypes = AIMCodes::InitializeComparisonOperatorTypes();

	for (ComparisonOperatorTypeMap::const_iterator iter = comparisonOperatorTypes.begin(); iter != comparisonOperatorTypes.end(); iter++)
	{
		if (iter->second.getCodeValue() == comparisonOperatorCode.getCodeValue())
			return iter->first;
	}

	assert(false); // Code Value is not found!
	std::cout << "Error: Mapping for comparison operator code (" << comparisonOperatorCode.getCodeValue() << ") was not found" << std::endl;

	return InvalidComparisonOperatorType;
}

const DSRCodedEntryValue AIMCodes::GetBooleanCodeValue(bool boolValue)
{
	static BooleanTypeMap booleanTypes = AIMCodes::InitializeBooleanTypes();

	return booleanTypes[boolValue];
}

const DSRCodedEntryValue AIMCodes::GetMappedValue(const AIMCodes::StringMap& lookupMap, const std::string& codingScheme, const std::string& lookupValue)
{
	StringMap::const_iterator iterValue = lookupMap.find(lookupValue);

	if (iterValue != lookupMap.end())
		return DSRCodedEntryValue(iterValue->second.data(), codingScheme.data(), iterValue->first.data());

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for coding scheme(" << codingScheme << ") lookup value(" << lookupValue << "} was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const DSRCodedEntryValue AIMCodes::GetMappedValue(const AIMCodes::String2PairMap& lookupMap, const std::string& lookupValue)
{
	String2PairMap::const_iterator iterValue = lookupMap.find(lookupValue);

	if (iterValue != lookupMap.end())
		return DSRCodedEntryValue(iterValue->second.first.data(), iterValue->second.second.data(), iterValue->first.data());

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for lookup value(" << lookupValue << "} was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const AIMCodes::CalcResultTypeMap AIMCodes::InitializeCalculationResultTypes()
{
	CalcResultTypeMap calculationResultTypesRels;

//	calculationResultTypesRels[Scalar]	= "crt001";
	calculationResultTypesRels[Vector]		= CreateAimCodedEntryValue("crt002", "Vector");
	calculationResultTypesRels[Histogram]	= CreateAimCodedEntryValue("crt003", "Histogram");
	calculationResultTypesRels[Matrix]		= CreateAimCodedEntryValue("crt004", "Matrix");
	calculationResultTypesRels[Array]		= CreateAimCodedEntryValue("crt005", "Array");

	return calculationResultTypesRels;
}

const AIMCodes::StringMap AIMCodes::InitializeOrganizationalRoles()
{
	StringMap organizationalRolesRels;

	// CID 7452
	organizationalRolesRels["Physician"]				= "121081";
	organizationalRolesRels["Nurse"]					= "121082";
	organizationalRolesRels["Technologist"]				= "121083";
	organizationalRolesRels["Radiographer"]				= "121084";
	organizationalRolesRels["Intern"]					= "121085";
	organizationalRolesRels["Resident"]					= "121086";
	organizationalRolesRels["Registrar"]				= "121087";
	organizationalRolesRels["Fellow"]					= "121088";
	organizationalRolesRels["Attending [Consultant]"]	= "121089";
	organizationalRolesRels["Scrub nurse"]				= "121090";
	organizationalRolesRels["Surgeon"]					= "121091";
	organizationalRolesRels["Sonologist"]				= "121092";
	organizationalRolesRels["Sonographer"]				= "121093";
	organizationalRolesRels["Radiation Physicist"]		= "121105";

	return organizationalRolesRels;
}

const AIMCodes::StringMap AIMCodes::InitializePerformingRoles()
{
	StringMap performingRolesRels;

	// CID 7453
	performingRolesRels["Performing"]	= "121094";
	performingRolesRels["Referring"]	= "121095";
	performingRolesRels["Requesting"]	= "121096";
	performingRolesRels["Recording"]	= "121097";
	performingRolesRels["Verifying"]	= "121098";
	performingRolesRels["Assisting"]	= "121099";
	performingRolesRels["Circulating"]	= "121100";
	performingRolesRels["Standby"]		= "121101";

	return performingRolesRels;
}

const AIMCodes::StringMap AIMCodes::InitializeUcumUnits()
{
	StringMap ucumUnitsRels;

	// Code Value  -- Code Meaning
	ucumUnitsRels["m"]		= "meter";
	ucumUnitsRels["m2"]		= "m^2"; // meter square
	ucumUnitsRels["mm"]		= "mm";
	ucumUnitsRels["mm2"]	= "mm^2"; // mm square
	ucumUnitsRels["cm"]		= "cm"; // centimeter
	ucumUnitsRels["cm2"]	= "cm^2"; // centimeter square
	ucumUnitsRels["Hz"]		= "Hz";
	ucumUnitsRels["s"]		= "s"; // second
	ucumUnitsRels["ms"]		= "ms"; // millisecond
	ucumUnitsRels["min"]	= "minute";
	ucumUnitsRels["h"]		= "hour";
	ucumUnitsRels["d"]		= "day";
	ucumUnitsRels["wk"]		= "week";
	ucumUnitsRels["mo"]		= "month";
	ucumUnitsRels["a"]		= "Year";
	ucumUnitsRels["g"]		= "gram";
	ucumUnitsRels["mg"]		= "mg"; // milligram
	ucumUnitsRels["kg"]		= "kg"; // kilogram
	ucumUnitsRels["rad"]	= "radian";
	ucumUnitsRels["deg"]	= "degrees";
	ucumUnitsRels["pixel"]	= "pixel";
	ucumUnitsRels["HU"]		= "hounsfield";
	ucumUnitsRels["%"]		= "Percent";  // percent
	ucumUnitsRels["1"]		= "ratio"; // non-dimensional unit
	ucumUnitsRels["Cel"]	= "°C"; // degree centigrade
	ucumUnitsRels["l"]		= "l"; // litter
	ucumUnitsRels["ml"]		= "ml"; // milliliter


	return ucumUnitsRels;
}

const AIMCodes::CharQuantificationTypeMap AIMCodes::InitializeCharQuantificationTypes()
{
	CharQuantificationTypeMap charQuantificationTypes;

	// [Code Value] = "Code meaning"
	charQuantificationTypes[CharacteristicQuantification::QT_Numerical]			= CreateAimCodedEntryValue("chq001", "Numerical");
	charQuantificationTypes[CharacteristicQuantification::QT_Quantile]			= CreateAimCodedEntryValue("chq002", "Quantile");
	charQuantificationTypes[CharacteristicQuantification::QT_Non_Quantifiable]	= CreateAimCodedEntryValue("chq003", "Non-Quantifiable");
	charQuantificationTypes[CharacteristicQuantification::QT_Scale]				= CreateAimCodedEntryValue("chq004", "Scale");
	charQuantificationTypes[CharacteristicQuantification::QT_Interval]			= CreateAimCodedEntryValue("chq005", "Interval");

	return charQuantificationTypes;
}

const AIMCodes::ComparisonOperatorTypeMap AIMCodes::InitializeComparisonOperatorTypes()
{
	ComparisonOperatorTypeMap comparisonOperatorTypes;

	// [Code Value] = "Code meaning"
	comparisonOperatorTypes[None]				= EmptyCodedEntryValue;
	comparisonOperatorTypes[Equal]				= DSRCodedEntryValue("G-A214", "SRT", "Equal");
	comparisonOperatorTypes[NotEqual]			= DSRCodedEntryValue("C1546806", "NCI", "Not equal condition applied to comparisons");
	comparisonOperatorTypes[LessThan]			= DSRCodedEntryValue("C61585", "NCI", "A statement about the relative size or order of two objects specifying that an object of interest is smaller than another object in quantity or measure or value or status");
	comparisonOperatorTypes[LessThanEqual]		= DSRCodedEntryValue("C61586", "NCI", "A statement about the relative size or order of two objects specifying that either both objects are the same in quantity or measure or value or status or that the object of interest is smaller than the other object in one of these ways");
	comparisonOperatorTypes[GreaterThan]		= DSRCodedEntryValue("C61584", "NCI", "A statement about the relative size or order of two objects specifying that an object of interest exceeds another object in quantity or measure or value or status");
	comparisonOperatorTypes[GreaterThanEqual]	= DSRCodedEntryValue("C61583", "NCI", "A statement about the relative size or order of two objects specifying that either both objects are the same in quantity or measure or value or status or that the object of interest exceeds the other object in one of these ways");

	return comparisonOperatorTypes;
}

const AIMCodes::BooleanTypeMap AIMCodes::InitializeBooleanTypes()
{
	static BooleanTypeMap booleanTypes;

	booleanTypes[true]	= DSRCodedEntryValue("R-0038D", "SRT", "Yes");
	booleanTypes[false]	= DSRCodedEntryValue("R-00339", "SRT", "No");

	return booleanTypes;
}

const DSRCodedEntryValue AIMCodes::CreateCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion)
{
	if (codingSchemeVersion.length() > 0)
		return DSRCodedEntryValue(codeValue.c_str(), codingSchemeDesignator.c_str(), codingSchemeVersion.c_str(), codeMeaning.c_str());
	return DSRCodedEntryValue(codeValue.c_str(), codingSchemeDesignator.c_str(), codeMeaning.c_str());
}

const DSRCodedEntryValue AIMCodes::CreateAimCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning)
{
	return CreateCodedEntryValue(codeValue, codeMeaning, AIM_CODING_SCHEME_DESIGNATOR, AIM_CODING_SCHEME_VERSION);
}

//const AIMCodes::StringMap AIMCodes::InitializeAcquisitionModalities()
//{
//	StringMap modalities;
//
//	// CID 29
//	modalities["EPS"]		= "Cardiac Electrophysiology";
//	modalities["CR"]		= "Computed Radiography";
//	modalities["CT"]		= "Computed Tomography";
//	modalities["DX"]		= "Digital Radiography";
//	modalities["ECG"]		= "Electrocardiography";
//	modalities["ES"]		= "Endoscopy";
//	modalities["XC"]		= "External-camera Photography";
//	modalities["GM"]		= "General Microscopy";
//	modalities["HD"]		= "Hemodynamic Waveform";
//	modalities["IO"]		= "Intra-oral Radiography";
//	modalities["IVUS"]		= "Intravascular Ultrasound";
//	modalities["MR"]		= "Magnetic Resonance";
//	modalities["MG"]		= "Mammography";
//	modalities["NM"]		= "Nuclear Medicine";
//	modalities["OCT"]		= "Optical Coherence Tomography";
//	modalities["OPM"]		= "Ophthalmic Mapping";
//	modalities["OP"]		= "Ophthalmic Photography";
//	modalities["OPR"]		= "Ophthalmic Refraction";
//	modalities["OPV"]		= "Ophthalmic Visual Field";
//	modalities["PX"]		= "Panoramic X-Ray";
//	modalities["PT"]		= "Positron emission tomography";
//	modalities["RF"]		= "Radiofluoroscopy";
//	modalities["RG"]		= "Radiographic imaging";
//	modalities["RTIMAGE"]	= "Radiotherapy Image";
//	modalities["REG"]		= "Registration";
//	modalities["SEG"]		= "Segmentation";
//	modalities["SM"]		= "Slide Microscopy";
//	modalities["US"]		= "Ultrasound";
//	modalities["XA"]		= "X-Ray Angiography";
//
//	return modalities;
//}
