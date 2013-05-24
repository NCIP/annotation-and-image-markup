/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "StdAfx.h"
#include "AIMOntology-typeinfo.h"
#include "../Altova/xs-types.h"

namespace AIMOntology
{

const altova::Binder binder = { namespaces, types, members, facets };

// Array of all namespaces with pointers to types:
const altova::NamespaceInfo namespaces[] =
{
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("aim"), _altova_tif_aim, _altova_til_aim },
	{ &binder, _T("http://www.w3.org/2001/XMLSchema"), _T("xs"), _altova_tif_xs, _altova_til_xs },
	{ 0 },
};

// Array of all types with pointers to members:
const altova::TypeInfo types[] =
{
	{ &binder, _altova_ni_aim, _T("AnatomicEntityXML"), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CAnatomicEntityXML, _altova_mil_aim_altova_CAnatomicEntityXML,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T("AnnotationDescriptionXML"), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CAnnotationDescriptionXML, _altova_mil_aim_altova_CAnnotationDescriptionXML,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T("ImagingObservationCharacteristicXML"), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CImagingObservationCharacteristicXML, _altova_mil_aim_altova_CImagingObservationCharacteristicXML,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T("ImagingObservationXML"), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CImagingObservationXML, _altova_mil_aim_altova_CImagingObservationXML,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T("AIMOntology"), ~0, _altova_mif_aim_altova_CAIMOntology, _altova_mil_aim_altova_CAIMOntology,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CrelatedAnatomicEntityXMLType, _altova_mil_aim_altova_CrelatedAnatomicEntityXMLType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CanatomicEntityCollectionXMLType, _altova_mil_aim_altova_CanatomicEntityCollectionXMLType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CimagingObservationCollectionXMLType, _altova_mil_aim_altova_CimagingObservationCollectionXMLType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CrelatedImagingObservationCharacteristicXMLType, _altova_mil_aim_altova_CrelatedImagingObservationCharacteristicXMLType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CrelatedImagingObservationXMLType, _altova_mil_aim_altova_CrelatedImagingObservationXMLType,  ~0 , altova::Whitespace_Unknown },
	{ &binder, _altova_ni_aim, _T(""), _altova_ti_xs_altova_CanyType, _altova_mif_aim_altova_CimagingObservationCharacteristicCollectionXMLType, _altova_mil_aim_altova_CimagingObservationCharacteristicCollectionXMLType,  ~0 , altova::Whitespace_Unknown },

	{ &binder, _altova_ni_xs, _T("ENTITIES"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CENTITIES, _altova_mil_xs_altova_CENTITIES,  0 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("ENTITY"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CENTITY, _altova_mil_xs_altova_CENTITY,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("ID"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CID, _altova_mil_xs_altova_CID,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("IDREF"), _altova_ti_xs_altova_CNCName, _altova_mif_xs_altova_CIDREF, _altova_mil_xs_altova_CIDREF,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("IDREFS"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CIDREFS, _altova_mil_xs_altova_CIDREFS,  3 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NCName"), _altova_ti_xs_altova_CName, _altova_mif_xs_altova_CNCName, _altova_mil_xs_altova_CNCName,  6 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NMTOKEN"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_CNMTOKEN, _altova_mil_xs_altova_CNMTOKEN,  8 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NMTOKENS"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CNMTOKENS, _altova_mil_xs_altova_CNMTOKENS,  10 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("NOTATION"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CNOTATION, _altova_mil_xs_altova_CNOTATION,  15 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("Name"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_CName, _altova_mil_xs_altova_CName,  17 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("QName"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CQName, _altova_mil_xs_altova_CQName,  19 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anySimpleType"), ~0, _altova_mif_xs_altova_CanySimpleType, _altova_mil_xs_altova_CanySimpleType,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anyType"), ~0, _altova_mif_xs_altova_CanyType, _altova_mil_xs_altova_CanyType,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("anyURI"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CanyURI, _altova_mil_xs_altova_CanyURI,  21 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("base64Binary"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cbase64Binary, _altova_mil_xs_altova_Cbase64Binary,  23 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("boolean"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cboolean, _altova_mil_xs_altova_Cboolean,  25 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("byte"), _altova_ti_xs_altova_Cshort, _altova_mif_xs_altova_Cbyte, _altova_mil_xs_altova_Cbyte,  27 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("date"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdate, _altova_mil_xs_altova_Cdate,  30 , altova::Whitespace_Collapse, &altova::DateFormatter },
	{ &binder, _altova_ni_xs, _T("dateTime"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CdateTime, _altova_mil_xs_altova_CdateTime,  32 , altova::Whitespace_Collapse, &altova::DateTimeFormatter },
	{ &binder, _altova_ni_xs, _T("decimal"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdecimal, _altova_mil_xs_altova_Cdecimal,  34 , altova::Whitespace_Collapse, &altova::DecimalFormatter },
	{ &binder, _altova_ni_xs, _T("double"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cdouble, _altova_mil_xs_altova_Cdouble,  36 , altova::Whitespace_Collapse, &altova::DoubleFormatter },
	{ &binder, _altova_ni_xs, _T("duration"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cduration, _altova_mil_xs_altova_Cduration,  38 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("float"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cfloat, _altova_mil_xs_altova_Cfloat,  40 , altova::Whitespace_Collapse, &altova::DoubleFormatter },
	{ &binder, _altova_ni_xs, _T("gDay"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgDay, _altova_mil_xs_altova_CgDay,  42 , altova::Whitespace_Collapse, &altova::GDayFormatter },
	{ &binder, _altova_ni_xs, _T("gMonth"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgMonth, _altova_mil_xs_altova_CgMonth,  44 , altova::Whitespace_Collapse, &altova::GMonthFormatter },
	{ &binder, _altova_ni_xs, _T("gMonthDay"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgMonthDay, _altova_mil_xs_altova_CgMonthDay,  46 , altova::Whitespace_Collapse, &altova::GMonthDayFormatter },
	{ &binder, _altova_ni_xs, _T("gYear"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgYear, _altova_mil_xs_altova_CgYear,  48 , altova::Whitespace_Collapse, &altova::GYearFormatter },
	{ &binder, _altova_ni_xs, _T("gYearMonth"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_CgYearMonth, _altova_mil_xs_altova_CgYearMonth,  50 , altova::Whitespace_Collapse, &altova::GYearMonthFormatter },
	{ &binder, _altova_ni_xs, _T("hexBinary"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_ChexBinary, _altova_mil_xs_altova_ChexBinary,  52 , altova::Whitespace_Collapse, &altova::HexBinaryFormatter },
	{ &binder, _altova_ni_xs, _T("int"), _altova_ti_xs_altova_Clong, _altova_mif_xs_altova_Cint, _altova_mil_xs_altova_Cint,  54 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("integer"), _altova_ti_xs_altova_Cdecimal, _altova_mif_xs_altova_Cinteger, _altova_mil_xs_altova_Cinteger,  57 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("language"), _altova_ti_xs_altova_Ctoken, _altova_mif_xs_altova_Clanguage, _altova_mil_xs_altova_Clanguage,  60 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("long"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_Clong, _altova_mil_xs_altova_Clong,  62 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("negativeInteger"), _altova_ti_xs_altova_CnonPositiveInteger, _altova_mif_xs_altova_CnegativeInteger, _altova_mil_xs_altova_CnegativeInteger,  65 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("nonNegativeInteger"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_CnonNegativeInteger, _altova_mil_xs_altova_CnonNegativeInteger,  67 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("nonPositiveInteger"), _altova_ti_xs_altova_Cinteger, _altova_mif_xs_altova_CnonPositiveInteger, _altova_mil_xs_altova_CnonPositiveInteger,  69 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("normalizedString"), _altova_ti_xs_altova_Cstring, _altova_mif_xs_altova_CnormalizedString, _altova_mil_xs_altova_CnormalizedString,  71 , altova::Whitespace_Replace, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("positiveInteger"), _altova_ti_xs_altova_CnonNegativeInteger, _altova_mif_xs_altova_CpositiveInteger, _altova_mil_xs_altova_CpositiveInteger,  73 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("short"), _altova_ti_xs_altova_Cint, _altova_mif_xs_altova_Cshort, _altova_mil_xs_altova_Cshort,  75 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("string"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Cstring, _altova_mil_xs_altova_Cstring,  78 , altova::Whitespace_Preserve, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("time"), _altova_ti_xs_altova_CanySimpleType, _altova_mif_xs_altova_Ctime, _altova_mil_xs_altova_Ctime,  80 , altova::Whitespace_Collapse, &altova::TimeFormatter },
	{ &binder, _altova_ni_xs, _T("token"), _altova_ti_xs_altova_CnormalizedString, _altova_mif_xs_altova_Ctoken, _altova_mil_xs_altova_Ctoken,  82 , altova::Whitespace_Collapse, &altova::AnySimpleTypeFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedByte"), _altova_ti_xs_altova_CunsignedShort, _altova_mif_xs_altova_CunsignedByte, _altova_mil_xs_altova_CunsignedByte,  84 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedInt"), _altova_ti_xs_altova_CunsignedLong, _altova_mif_xs_altova_CunsignedInt, _altova_mil_xs_altova_CunsignedInt,  86 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedLong"), _altova_ti_xs_altova_CnonNegativeInteger, _altova_mif_xs_altova_CunsignedLong, _altova_mil_xs_altova_CunsignedLong,  88 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T("unsignedShort"), _altova_ti_xs_altova_CunsignedInt, _altova_mif_xs_altova_CunsignedShort, _altova_mil_xs_altova_CunsignedShort,  90 , altova::Whitespace_Unknown, &altova::IntegerFormatter },
	{ &binder, _altova_ni_xs, _T(""), ~0, _altova_mif_xs_altova_CstringType, _altova_mil_xs_altova_CstringType,  ~0 , altova::Whitespace_Unknown, &altova::AnySimpleTypeFormatter },

{ 0 },
};

const altova::MemberInfo members[] =
{
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeMeaning"), _altova_ti_aim_altova_CAnatomicEntityXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codingSchemeDesignator"), _altova_ti_aim_altova_CAnatomicEntityXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeValue"), _altova_ti_aim_altova_CAnatomicEntityXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relationship"), _altova_ti_aim_altova_CAnatomicEntityXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relatedAnatomicEntityXML"), _altova_ti_aim_altova_CAnatomicEntityXML, _altova_ti_aim_altova_CrelatedAnatomicEntityXMLType, MemberFlags_None, 0, 1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("anatomicEntityCollectionXML"), _altova_ti_aim_altova_CAnnotationDescriptionXML, _altova_ti_aim_altova_CanatomicEntityCollectionXMLType, MemberFlags_None, 0, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("imagingObservationCollectionXML"), _altova_ti_aim_altova_CAnnotationDescriptionXML, _altova_ti_aim_altova_CimagingObservationCollectionXMLType, MemberFlags_None, 0, 1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeMeaning"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codingSchemeDesignator"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeValue"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("comment"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 0, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relationship"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relatedImagingObservationCharacteristicXML"), _altova_ti_aim_altova_CImagingObservationCharacteristicXML, _altova_ti_aim_altova_CrelatedImagingObservationCharacteristicXMLType, MemberFlags_None, 0, 1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeMeaning"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codingSchemeDesignator"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("codeValue"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("comment"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 0, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relationship"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_xs_altova_CstringType, MemberFlags_None, 1, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("relatedImagingObservationXML"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_aim_altova_CrelatedImagingObservationXMLType, MemberFlags_None, 0, 1 },
	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("imagingObservationCharacteristicCollectionXML"), _altova_ti_aim_altova_CImagingObservationXML, _altova_ti_aim_altova_CimagingObservationCharacteristicCollectionXMLType, MemberFlags_None, 0, 1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("AnnotationDescriptionXML"), _altova_ti_aim_altova_CAIMOntology, _altova_ti_aim_altova_CAnnotationDescriptionXML, MemberFlags_None, 0, 1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("AnatomicEntityXML"), _altova_ti_aim_altova_CrelatedAnatomicEntityXMLType, _altova_ti_aim_altova_CAnatomicEntityXML, MemberFlags_None, 0, -1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("AnatomicEntityXML"), _altova_ti_aim_altova_CanatomicEntityCollectionXMLType, _altova_ti_aim_altova_CAnatomicEntityXML, MemberFlags_None, 0, -1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("ImagingObservationXML"), _altova_ti_aim_altova_CimagingObservationCollectionXMLType, _altova_ti_aim_altova_CImagingObservationXML, MemberFlags_None, 0, -1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("ImagingObservationCharacteristicXML"), _altova_ti_aim_altova_CrelatedImagingObservationCharacteristicXMLType, _altova_ti_aim_altova_CImagingObservationCharacteristicXML, MemberFlags_None, 0, -1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("ImagingObservationXML"), _altova_ti_aim_altova_CrelatedImagingObservationXMLType, _altova_ti_aim_altova_CImagingObservationXML, MemberFlags_None, 0, -1 },

	{ &binder, _T("http://www.radiology.northwestern.edu/aim/1/ontology/1"), _T("ImagingObservationCharacteristicXML"), _altova_ti_aim_altova_CimagingObservationCharacteristicCollectionXMLType, _altova_ti_aim_altova_CImagingObservationCharacteristicXML, MemberFlags_None, 0, -1 },

	{ &binder, _T(""), _T(""), _altova_ti_xs_altova_CanyType, _altova_ti_xs_altova_CanySimpleType, MemberFlags_IsAttribute, 0, -1 },

	{ &binder, _T(""), _T(""), _altova_ti_xs_altova_CstringType, _altova_ti_xs_altova_Cstring, MemberFlags_IsAttribute, 1, 1 },

{ 0 },
};

const altova::FacetInfo facets[] =
{
	// ENTITIES
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 },
	{ 0, 0, 0, 0 },
	// IDREFS
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 },
	{ 0, 0, 0, 0 },
	// NCName
	{ 0, _T("pattern"), _T("[\\i-[:]][\\c-[:]]*"), 0 },
	{ 0, 0, 0, 0 },
	// NMTOKEN
	{ 0, _T("pattern"), _T("\\c+"), 0 },
	{ 0, 0, 0, 0 },
	// NMTOKENS
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, _T("minLength"), _T("1"), 1 },
	{ 0, _T("pattern"), _T("\\c+"), 0 },
	{ 0, _T("pattern"), _T("\\c+"), 0 },
	{ 0, 0, 0, 0 },
	// NOTATION
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// Name
	{ 0, _T("pattern"), _T("\\i\\c*"), 0 },
	{ 0, 0, 0, 0 },
	// QName
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// anyURI
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// base64Binary
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// boolean
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// byte
	{ 0, _T("minInclusive"), _T("-128"), 0 },
	{ 0, _T("maxInclusive"), _T("127"), 0 },
	{ 0, 0, 0, 0 },
	// date
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// dateTime
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// decimal
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// double
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// duration
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// float
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gDay
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gMonth
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gMonthDay
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gYear
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// gYearMonth
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// hexBinary
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// int
	{ 0, _T("minInclusive"), _T("-2147483648"), 0 },
	{ 0, _T("maxInclusive"), _T("2147483647"), 0 },
	{ 0, 0, 0, 0 },
	// integer
	{ 0, _T("fractionDigits"), _T("0"), 0 },
	{ 0, _T("pattern"), _T("[\\-+]?[0-9]+"), 0 },
	{ 0, 0, 0, 0 },
	// language
	{ 0, _T("pattern"), _T("[a-zA-Z]{1,8}(-[a-zA-Z0-9]{1,8})*"), 0 },
	{ 0, 0, 0, 0 },
	// long
	{ 0, _T("minInclusive"), _T("-9223372036854775808"), 0 },
	{ 0, _T("maxInclusive"), _T("9223372036854775807"), 0 },
	{ 0, 0, 0, 0 },
	// negativeInteger
	{ 0, _T("maxInclusive"), _T("-1"), 0 },
	{ 0, 0, 0, 0 },
	// nonNegativeInteger
	{ 0, _T("minInclusive"), _T("0"), 0 },
	{ 0, 0, 0, 0 },
	// nonPositiveInteger
	{ 0, _T("maxInclusive"), _T("0"), 0 },
	{ 0, 0, 0, 0 },
	// normalizedString
	{ 0, _T("whitespace"), _T("replace"), 0 },
	{ 0, 0, 0, 0 },
	// positiveInteger
	{ 0, _T("minInclusive"), _T("1"), 0 },
	{ 0, 0, 0, 0 },
	// short
	{ 0, _T("minInclusive"), _T("-32768"), 0 },
	{ 0, _T("maxInclusive"), _T("32767"), 0 },
	{ 0, 0, 0, 0 },
	// string
	{ 0, _T("whitespace"), _T("preserve"), 0 },
	{ 0, 0, 0, 0 },
	// time
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// token
	{ 0, _T("whitespace"), _T("collapse"), 0 },
	{ 0, 0, 0, 0 },
	// unsignedByte
	{ 0, _T("maxInclusive"), _T("255"), 0 },
	{ 0, 0, 0, 0 },
	// unsignedInt
	{ 0, _T("maxInclusive"), _T("4294967295"), 0 },
	{ 0, 0, 0, 0 },
	// unsignedLong
	{ 0, _T("maxInclusive"), _T("18446744073709551615"), 0 },
	{ 0, 0, 0, 0 },
	// unsignedShort
	{ 0, _T("maxInclusive"), _T("65535"), 0 },
	{ 0, 0, 0, 0 },
{ 0 },
};

}  // namespace AIMOntology
