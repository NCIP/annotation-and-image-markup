/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "stdafx.h"

#include "dcmtk/ofstd/ofcond.h"

#include "AimEnum.h"
#include "util/DateTime.h"
#include "AIMUtil.h"
#include "entity/CharacteristicQuantification.h"
#include "entity/Dimension.h"
#include "entity/CalculationResult.h"
#include "entity/CharacteristicQuantification.h"
#include "entity/Scale.h"
#include "AIMCodes.h"

#include "AimHeaders.h"

using namespace aim_lib;

// Initialize static values
const DSRCodedEntryValue AIMCodes::EmptyCodedEntryValue = DSRCodedEntryValue();
const DSRSpatialCoordinatesValue AIMCodes::EmptySpatialCoordinateValue = DSRSpatialCoordinatesValue();
const DSRSpatialCoordinates3DValue AIMCodes::EmptySpatialCoordinate3DValue = DSRSpatialCoordinates3DValue();
const DSRImageReferenceValue AIMCodes::EmptyImageReferenceValue = DSRImageReferenceValue();
const DSRNumericMeasurementValue AIMCodes::EmptyNumericMeasurementValue = DSRNumericMeasurementValue();

const std::string AIMCodes::_emptyStr = std::string();

#define _stringify(name) # name

AIMCodes::AIMCodes(void)
{
}

AIMCodes::~AIMCodes(void)
{
}

template<typename T, typename M>
const M AIMCodes::FindMapValue(const std::map<T,M>& theMap, const T& lookupValue, const M& defaultValue)
{
	typename std::map<T,M>::const_iterator iter = theMap.find(lookupValue);

	if (iter != theMap.end())
		return iter->second;

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for " << _stringify(T) <<  "(" << lookupValue << ") was not found." << std::endl;

	return defaultValue;
}

template<typename T>
const T& AIMCodes::FindMapKeyByCodeValue(const std::map<T,DSRCodedEntryValue>& theMap, const DSRCodedEntryValue& lookupValue, const T& defaultValue)
{
	for (typename std::map<T,DSRCodedEntryValue>::const_iterator iter = theMap.begin(); iter != theMap.end(); iter++)
	{
		if (iter->second.getCodeValue() == lookupValue.getCodeValue())
			return iter->first;
	}

	assert(false); // Code Value is not found!
	std::cout << "Error: Mapping for " << _stringify(T) <<  " code (" << lookupValue.getCodeValue() << ") was not found." << std::endl;

	return defaultValue;
}

const DSRCodedEntryValue AIMCodes::GetCalculationResultTypeValue(CalculationResult::CalculationResultType calculationResultType)
{
	// initialize map on the first use
	static CalcResultTypeMap calcResultTypes = AIMCodes::InitializeCalculationResultTypes();

	return AIMCodes::FindMapValue<CalculationResult::CalculationResultType, DSRCodedEntryValue>(calcResultTypes, calculationResultType, EmptyCodedEntryValue);
}

const DSRCodedEntryValue AIMCodes::GetOrganizationalRoleValue(const std::string& organizationalRoleName)
{
	static StringMap organizationalRoles = AIMCodes::InitializeOrganizationalRoles();

	return AIMCodes::GetMappedValue(organizationalRoles, "DCM", organizationalRoleName);
}

const DSRCodedEntryValue AIMCodes::GetPerformingRoleValue(const std::string& performingRoleName)
{
	static StringMap performingRoles = AIMCodes::InitializePerformingRoles();

	return AIMCodes::GetMappedValue(performingRoles, "DCM", performingRoleName);
}

const DSRCodedEntryValue AIMCodes::GetUcumCodeValue(const std::string& unitAbbreviation)
{
	static StringMap ucumUnits = AIMCodes::InitializeUcumUnits();

	return AIMCodes::GetMappedValue(ucumUnits, "UCUM", unitAbbreviation);
}

const DSRCodedEntryValue AIMCodes::GetCharacteristicQuantificationTypeValue(CharacteristicQuantification::QuantificationType charQuantificationType)
{
	static CharQuantificationTypeMap charQuantificationTypes = AIMCodes::InitializeCharQuantificationTypes();

	return AIMCodes::FindMapValue<CharacteristicQuantification::QuantificationType, DSRCodedEntryValue>(charQuantificationTypes, charQuantificationType, EmptyCodedEntryValue);
}

const DSRCodedEntryValue AIMCodes::GetComparisonOperatorTypeValue(ComparisonOperatorType comparisonOperatorType)
{
	const ComparisonOperatorTypeMap& comparisonOperatorTypes = AIMCodes::GetComparisonOperatorTypes();

	return AIMCodes::FindMapValue<ComparisonOperatorType, DSRCodedEntryValue>(comparisonOperatorTypes, comparisonOperatorType, EmptyCodedEntryValue);
}

const ComparisonOperatorType AIMCodes::GetComparisonOperatorType(const DSRCodedEntryValue& comparisonOperatorCode)
{
	const ComparisonOperatorTypeMap& comparisonOperatorTypes = AIMCodes::GetComparisonOperatorTypes();

	return AIMCodes::FindMapKeyByCodeValue(comparisonOperatorTypes, comparisonOperatorCode, InvalidComparisonOperatorType);
}

const DSRCodedEntryValue AIMCodes::GetBooleanCodeValue(bool boolValue)
{
	static BooleanTypeMap booleanTypes = AIMCodes::InitializeBooleanTypes();

	return booleanTypes[boolValue];
}

const DSRCodedEntryValue AIMCodes::GetScaleTypeValue(Scale::ScaleType scaleType)
{
	const ScaleTypeMap& scaleTypes = AIMCodes::GetScaleTypes();

	return AIMCodes::FindMapValue<Scale::ScaleType, DSRCodedEntryValue>(scaleTypes, scaleType, EmptyCodedEntryValue);
}

const Scale::ScaleType AIMCodes::GetScaleType(const DSRCodedEntryValue& scaleTypeCode)
{
	const ScaleTypeMap& scaleTypes = AIMCodes::GetScaleTypes();

	return AIMCodes::FindMapKeyByCodeValue(scaleTypes, scaleTypeCode, Scale::InvalidScaleType);
}

const DSRCodedEntryValue AIMCodes::GetEntityValue(const std::string& entityClassName)
{
	const String2CodedEntryValueMap& entityCodes = AIMCodes::GetAnnotationEnities();

	return AIMCodes::FindMapValue<std::string, DSRCodedEntryValue>(entityCodes, entityClassName, EmptyCodedEntryValue);
}

const std::string& AIMCodes::GetEntityClassName(const DSRCodedEntryValue& entityCode)
{
	const String2CodedEntryValueMap& entityCodes = AIMCodes::GetAnnotationEnities();

	return AIMCodes::FindMapKeyByCodeValue(entityCodes, entityCode, AIMCodes::_emptyStr);
}

const DSRCodedEntryValue AIMCodes::GetStatementPredicateValue(const std::string& statementPredicateClassName)
{
	const String2CodedEntryValueMap& statementPredicates = AIMCodes::GetStatementPredicates();

	return AIMCodes::FindMapValue<std::string, DSRCodedEntryValue>(statementPredicates, statementPredicateClassName, EmptyCodedEntryValue);
}

const std::string& AIMCodes::GetStatementPredicateClassName(const DSRCodedEntryValue& statementPredicateCode)
{
	const String2CodedEntryValueMap& statementPredicates = AIMCodes::GetStatementPredicates();

	return AIMCodes::FindMapKeyByCodeValue(statementPredicates, statementPredicateCode, AIMCodes::_emptyStr);
}

const DSRCodedEntryValue AIMCodes::GetMappedValue(const StringMap& lookupMap, const std::string& codingScheme, const std::string& lookupValue)
{
	StringMap::const_iterator iterValue = lookupMap.find(lookupValue);

	if (iterValue != lookupMap.end())
		return DSRCodedEntryValue(iterValue->second, codingScheme, iterValue->first);

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for coding scheme(" << codingScheme << ") lookup value(" << lookupValue << "} was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const DSRCodedEntryValue AIMCodes::GetMappedValue(const String2PairMap& lookupMap, const std::string& lookupValue)
{
	String2PairMap::const_iterator iterValue = lookupMap.find(lookupValue);

	if (iterValue != lookupMap.end())
		return DSRCodedEntryValue(iterValue->second.first, iterValue->second.second, iterValue->first);

	assert(false); // Mapping is not found!
	std::cout << "Error: Mapping for lookup value(" << lookupValue << "} was not found" << std::endl;

	return EmptyCodedEntryValue;
}

const DSRCodedEntryValue AIMCodes::CreateCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning, const std::string& codingSchemeDesignator, const std::string& codingSchemeVersion)
{
	if (codingSchemeVersion.length() > 0)
		return DSRCodedEntryValue(codeValue, codingSchemeDesignator, codingSchemeVersion, codeMeaning);
	return DSRCodedEntryValue(codeValue, codingSchemeDesignator, codeMeaning);
}

const DSRCodedEntryValue AIMCodes::CreateAimCodedEntryValue(const std::string& codeValue, const std::string& codeMeaning)
{
	return CreateCodedEntryValue(codeValue, codeMeaning, AIM_CODING_SCHEME_DESIGNATOR, AIM_CODING_SCHEME_VERSION);
}

DSRCodedEntryValue AIMCodes::CreateCodedEntryValueFromCd(const iso_21090::CD& cd){
	if (cd.GetCodingSchemeVersion().empty())
		return DSRCodedEntryValue(cd.GetCodeValue(), cd.GetCodingSchemeDesignator(), cd.GetCodeMeaning());
	else
		return DSRCodedEntryValue(cd.GetCodeValue(), cd.GetCodingSchemeDesignator(), cd.GetCodingSchemeVersion(), cd.GetCodeMeaning());
}

iso_21090::CD AIMCodes::CreateCdFromCodedEntryValue(const DSRCodedEntryValue& dsrCode){
	return iso_21090::CD(dsrCode.getCodeValue(), dsrCode.getCodeMeaning(), dsrCode.getCodingSchemeDesignator(), dsrCode.getCodingSchemeVersion());
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////  Codes  ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

const AIMCodes::CalcResultTypeMap AIMCodes::InitializeCalculationResultTypes()
{
	CalcResultTypeMap calculationResultTypesRels;

//	calculationResultTypesRels[Scalar]	= "crt001";
	calculationResultTypesRels[CalculationResult::Scalar]		= CreateAimCodedEntryValue("crt001", "Scalar");
	calculationResultTypesRels[CalculationResult::Vector]		= CreateAimCodedEntryValue("crt002", "Vector");
	calculationResultTypesRels[CalculationResult::Histogram]	= CreateAimCodedEntryValue("crt003", "Histogram");
	calculationResultTypesRels[CalculationResult::Matrix]		= CreateAimCodedEntryValue("crt004", "Matrix");
	calculationResultTypesRels[CalculationResult::Array]		= CreateAimCodedEntryValue("crt005", "Array");
	calculationResultTypesRels[CalculationResult::Binary]		= CreateAimCodedEntryValue("crt006", "Binary");

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
	ucumUnitsRels["m"]			= "meter";
	ucumUnitsRels["m2"]			= "m^2"; // meter square
	ucumUnitsRels["mm"]			= "mm";
	ucumUnitsRels["mm2"]		= "mm^2"; // mm square
	ucumUnitsRels["cm"]			= "cm"; // centimeter
	ucumUnitsRels["cm2"]		= "cm^2"; // centimeter square
	ucumUnitsRels["mm/{pixel}"]	= "mm per pixel";
	ucumUnitsRels["Hz"]			= "Hz";
	ucumUnitsRels["s"]			= "s"; // second
	ucumUnitsRels["ms"]			= "ms"; // millisecond
	ucumUnitsRels["min"]		= "minute";
	ucumUnitsRels["h"]			= "hour";
	ucumUnitsRels["d"]			= "day";
	ucumUnitsRels["wk"]			= "week";
	ucumUnitsRels["mo"]			= "month";
	ucumUnitsRels["a"]			= "Year";
	ucumUnitsRels["g"]			= "gram";
	ucumUnitsRels["mg"]			= "mg"; // milligram
	ucumUnitsRels["kg"]			= "kg"; // kilogram
	ucumUnitsRels["rad"]		= "radian";
	ucumUnitsRels["deg"]		= "deg"; // degree
	ucumUnitsRels["pixel"]		= "pixel";
	ucumUnitsRels["HU"]			= "hounsfield";
	ucumUnitsRels["%"]			= "Percent";  // percent
	ucumUnitsRels["1"]			= "ratio"; // non-dimensional unit
	ucumUnitsRels["Cel"]		= "C"; // degree centigrade
	ucumUnitsRels["l"]			= "l"; // litter
	ucumUnitsRels["ml"]			= "ml"; // milliliter


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

const AIMCodes::ComparisonOperatorTypeMap& AIMCodes::GetComparisonOperatorTypes()
{
	static ComparisonOperatorTypeMap comparisonOperatorTypes = AIMCodes::InitializeComparisonOperatorTypes();
	return comparisonOperatorTypes;
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
	BooleanTypeMap booleanTypes;

	booleanTypes[true]	= DSRCodedEntryValue("R-0038D", "SRT", "Yes");
	booleanTypes[false]	= DSRCodedEntryValue("R-00339", "SRT", "No");

	return booleanTypes;
}

const AIMCodes::ScaleTypeMap& AIMCodes::GetScaleTypes()
{
	static ScaleTypeMap scaleTypes = AIMCodes::InitializeScaleTypes();
	return scaleTypes;
}

const AIMCodes::ScaleTypeMap AIMCodes::InitializeScaleTypes()
{
	ScaleTypeMap scaleTypes;

	scaleTypes[Scale::Ordinal] = DSRCodedEntryValue("C47797", "NCI", "Ordinal Scale");
	scaleTypes[Scale::Nominal] = DSRCodedEntryValue("C47798", "NCI", "Nominal Scale");
	scaleTypes[Scale::Ratio] = DSRCodedEntryValue("C47800", "NCI", "Ratio Scale");

	return scaleTypes;
}

const AIMCodes::String2CodedEntryValueMap& AIMCodes::GetAnnotationEnities()
{
	static String2CodedEntryValueMap entityCodes = AIMCodes::InitializeAnnotationEnities();
	return entityCodes;
}

const AIMCodes::String2CodedEntryValueMap AIMCodes::InitializeAnnotationEnities()
{
	String2CodedEntryValueMap annotationEntities;

	annotationEntities[_stringify(AnnotationOfAnnotation)]				= CreateAimCodedEntryValue("AS001", "Annotation of Annotation");
	annotationEntities[_stringify(AnnotationEntity)]					= CreateAimCodedEntryValue("AS002", "Annotation Entity");
	annotationEntities[_stringify(AnnotationRoleEntity)]				= CreateAimCodedEntryValue("AS003", "Annotation Role Entity");
	annotationEntities[_stringify(CalculationEntity)]					= CreateAimCodedEntryValue("AS004", "Calculation Entity");
	annotationEntities[_stringify(DicomImageReferenceEntity)]			= CreateAimCodedEntryValue("AS005", "DICOM Image Reference Entity");
	annotationEntities[_stringify(DicomSegmentationEntity)]				= CreateAimCodedEntryValue("AS006", "DICOM Segmentation Entity");
	annotationEntities[_stringify(GeneralLesionObservationEntity)]		= CreateAimCodedEntryValue("AS007", "General Lesion Observation Entity");
	annotationEntities[_stringify(ImageAnnotation)]						= CreateAimCodedEntryValue("AS008", "Image Annotation");
	annotationEntities[_stringify(ImagingObservationEntity)]			= CreateAimCodedEntryValue("AS009", "Imaging Observation Entity");
	annotationEntities[_stringify(ImagingPhysicalEntity)]				= CreateAimCodedEntryValue("AS011", "Imaging Physical Entity");
	annotationEntities[_stringify(InferenceEntity)]						= CreateAimCodedEntryValue("AS013", "Inference Entity");
	annotationEntities[_stringify(TaskContextEntity)]					= CreateAimCodedEntryValue("AS014", "Task Context Entity");
	annotationEntities[_stringify(TextAnnotationEntity)]				= CreateAimCodedEntryValue("AS015", "Text Annotation Entity");
	annotationEntities[_stringify(TimePointLesionObservationEntity)]	= CreateAimCodedEntryValue("AS016", "Time Point Lesion Observation Entity");
	annotationEntities[_stringify(UriImageReferenceEntity)]				= CreateAimCodedEntryValue("AS017", "URI Image Reference Entity");
	annotationEntities[_stringify(TwoDimensionGeometricShapeEntity)]	= CreateAimCodedEntryValue("AS018", "2D Geometric Shape Entity");
	annotationEntities[_stringify(ThreeDimensionGeometricShapeEntity)]	= CreateAimCodedEntryValue("AS019", "3D Geometric Shape Entity");

	return annotationEntities;
}

const AIMCodes::String2CodedEntryValueMap& AIMCodes::GetStatementPredicates()
{
	static String2CodedEntryValueMap statementPredicates = AIMCodes::InitializeStatementPredicates();
	return statementPredicates;
}

const AIMCodes::String2CodedEntryValueMap AIMCodes::InitializeStatementPredicates()
{
	String2CodedEntryValueMap statementPredicates;

	statementPredicates[_stringify(ExcludesAnnotationStatementRelationship)]		= CreateAimCodedEntryValue("REL001", "Excludes");
	statementPredicates[_stringify(HasAnnotationStatementRelationship)]				= CreateAimCodedEntryValue("REL002", "Has");
	statementPredicates[_stringify(HasChildAnnotationStatementRelationship)]		= CreateAimCodedEntryValue("REL003", "Has Child");
	statementPredicates[_stringify(HasPerformedAnnotationStatementRelationship)]	= CreateAimCodedEntryValue("REL004", "Has Performed");
	statementPredicates[_stringify(HasPlannedAnnotationStatementRelationship)]		= CreateAimCodedEntryValue("REL005", "Has Planned");
	statementPredicates[_stringify(ReferencesAnnotationStatementRelationship)]		= CreateAimCodedEntryValue("REL006", "References");
	statementPredicates[_stringify(UsesAnnotationStatementRelationship)]			= CreateAimCodedEntryValue("REL007", "Uses");
	statementPredicates[_stringify(IsComparedWithAnnotationStatementRelationship)]	= CreateAimCodedEntryValue("REL008", "Is Compared With");
	statementPredicates[_stringify(IsComprisedOfAnnotationStatementRelationship)]	= CreateAimCodedEntryValue("REL009", "Is Comprised Of");
	statementPredicates[_stringify(IsFoundInAnnotationStatementRelationship)]		= CreateAimCodedEntryValue("REL010", "Is Found In");
	statementPredicates[_stringify(IsIdentifiedByAnnotationStatementRelationship)]	= CreateAimCodedEntryValue("REL011", "Is Identified By");

	return statementPredicates;
}
