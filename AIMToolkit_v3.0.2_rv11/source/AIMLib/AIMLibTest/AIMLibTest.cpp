/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

//#include <string>
#include <ctime>

#include "../AIMLib/AIMCommon.h"

#include "../AIMLib/model/AimHeaders.h"

#include "../AIMLib/Operations/BaseModel.h"
#include "../AIMLib/Operations/DcmModel.h"
#include "../AIMLib/Operations/XmlModel.h"

//#include "xmlStream.h"

//#include "../JniProtegeBridge/JniProtegeBridge.h"

#include <cstdlib>
#include <cassert>

#include <sstream>

#include "memdebug.h"

using namespace aim_lib;

#define DICOM_DOC_NAME "outdoc.dcm"
#define DICOM_DOC_NAME2 "outdoc2.dcm"
#define XML_DOC_NAME "outdoc.xml"
#define XML_DOC_NAME2 "outdoc2.xml"

enum TestDocumentType{
	DT_DICOM,
	DT_XML,
	DT_ALL
};

static int test_create_annotation(Annotation::AnnotationKind, TestDocumentType);
static int test_create_annotations(int annCount, Annotation::AnnotationKind, TestDocumentType);
static void test_save_annotation(Annotation*, TestDocumentType, const std::string& = "");
static AnnotationPtrVector test_load_annotations(TestDocumentType, const std::string& = "");
static void test_create_load_save_annotation(Annotation::AnnotationKind, TestDocumentType, TestDocumentType);
static void test_load_save_annotation(TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo, const std::string& = "", const std::string& = "");

static ImageAnnotation* create_image_annotation();
static AnnotationOfAnnotation* create_annotation_of_annotation();

static int test_jni_protege_bridge();

#if !defined( __GNUC__ )
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char **argv)
#endif
{
	// 1. Test generating annotations
	//test_create_annotation(Annotation::AK_ImageAnnotation, DT_DICOM);
	//test_create_annotation(Annotation::AK_AnnotationOfAnnotation, DT_DICOM);

	test_create_annotation(Annotation::AK_ImageAnnotation, DT_XML);
	//test_create_annotation(Annotation::AK_AnnotationOfAnnotation, DT_XML);

	//test_create_annotations(2, Annotation::AK_ImageAnnotation, DT_DICOM);
	//test_create_annotations(2, Annotation::AK_AnnotationOfAnnotation, DT_DICOM);

	//test_create_annotations(2, Annotation::AK_ImageAnnotation, DT_XML);
	//test_create_annotations(2, Annotation::AK_AnnotationOfAnnotation, DT_XML);

	// 2. Test generating/reading/saving annotations cycle
	//test_create_load_save_annotation(Annotation::AK_ImageAnnotation, DT_XML, DT_XML);
	//test_create_load_save_annotation(Annotation::AK_AnnotationOfAnnotation, DT_XML, DT_XML);

	//test_create_load_save_annotation(Annotation::AK_ImageAnnotation, DT_DICOM, DT_XML);
	//test_create_load_save_annotation(Annotation::AK_AnnotationOfAnnotation, DT_DICOM, DT_XML);

	// 3. Test reading annotations from file
	//test_load_annotations(DT_XML);
	//test_load_annotations(DT_DICOM);

	//test_load_save_annotation(DT_DICOM, DT_XML);
	//test_load_save_annotation(DT_XML, DT_DICOM);

	// Test reading specific individual annotation
	//test_load_annotations(DT_XML, XML_DOC_NAME);
	//test_load_annotations(DT_XML, "AIM_tcga_to_3.0_v2.xml");

	//test_load_save_annotation(DT_XML, DT_DICOM, "AIM_tcga_to_3.0_v2.xml", "AIM_tcga_to_3.0_v2.dcm");
	//test_load_save_annotation(DT_DICOM, DT_XML, "058_aim1_vk.dcm", "058_aim1_vk_out.xml");

	// 4. Test JNI Protege Bridge
	//test_jni_protege_bridge();
}

static int test_create_annotation(Annotation::AnnotationKind atAnnotationKind, TestDocumentType dtType)
{
	Annotation* pAnnotation = NULL;

	if (atAnnotationKind == Annotation::AK_ImageAnnotation)
		pAnnotation = create_image_annotation();
	else if (atAnnotationKind == Annotation::AK_AnnotationOfAnnotation)
		pAnnotation = create_annotation_of_annotation();
	else
	{
		assert(false);
		return -1;
	}

	test_save_annotation(pAnnotation, dtType);

	// Cleanup
	delete pAnnotation;
	pAnnotation = NULL;

	return 0;
}

// Test createing ->saving->loading->saving an annotation
static void test_create_load_save_annotation(Annotation::AnnotationKind atAnnotationKind, TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo)
{
	AnnotationPtrVector annotations;

	if (test_create_annotation(atAnnotationKind, /*dtTypeFrom*/ DT_ALL) == 0)
	{
		annotations = test_load_annotations(dtTypeFrom);
		if (annotations.size() == 1 && annotations[0] != NULL)
		{
			test_save_annotation(annotations[0], dtTypeTo, dtTypeTo == DT_DICOM ? DICOM_DOC_NAME2 : XML_DOC_NAME2);
		}

		for (AnnotationPtrVector::iterator iter = annotations.begin(); iter < annotations.end(); iter++)
		{
			delete *iter;
			*iter = NULL;
		}
		annotations.clear();
	}
}

// Test loading->saving an annotation
static void test_load_save_annotation(TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo, const std::string& fileNameFrom/* = ""*/, const std::string& fileNameTo/* = ""*/)
{
	AnnotationPtrVector annotations;

	annotations = test_load_annotations(dtTypeFrom, fileNameFrom);
	if (annotations.size() == 1 && annotations[0] != NULL)
	{
		test_save_annotation(annotations[0], dtTypeTo, fileNameTo.empty() ? (dtTypeTo == DT_DICOM ? DICOM_DOC_NAME2 : XML_DOC_NAME2) : fileNameTo);
	}

	for (AnnotationPtrVector::iterator iter = annotations.begin(); iter < annotations.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	annotations.clear();
}

static int test_create_annotations(int annCount, Annotation::AnnotationKind atAnnotationKind, TestDocumentType dtType)
{
	if (annCount < 1)
		return -1;

	Annotation* pAnnotation = NULL;

	if (atAnnotationKind == Annotation::AK_ImageAnnotation)
		pAnnotation = create_image_annotation();
	else if (atAnnotationKind == Annotation::AK_AnnotationOfAnnotation)
		pAnnotation = create_annotation_of_annotation();
	else
	{
		assert(false);
		return -1;
	}

	string outXml;
	ofstream myfile;
	AnnotationPtrVector annotations;
	for (int i=0; i < annCount; i++)
	{
		annotations.push_back(pAnnotation);
	}

	if (dtType == DT_DICOM || dtType == DT_ALL)
	{
		DcmModel dcmModel;
		dcmModel.WriteAnnotationsToFile(annotations, DICOM_DOC_NAME);

		// Run Notepad
	//	system("notepad dcmtk_outdoc.xml");

	}
	if (dtType == DT_XML || dtType == DT_ALL)
	{
		XmlModel xmlModel;
		outXml = "";
		std::string::size_type xmlSize = 10240; // 10K - initial buffer size
		do
		{
			std::string::traits_type::char_type* pXml = NULL;
			try
			{
				pXml = new std::string::traits_type::char_type[xmlSize];
				xmlSize = xmlModel.WriteAnnotationsToXmlString(annotations, pXml, xmlSize);
				outXml = pXml;
				delete pXml;
				pXml = NULL;
			}
			catch(exception ex)
			{
				if (pXml != NULL)
				{
					delete pXml;
					pXml = NULL;
				}
			}
		}
		while(xmlSize != outXml.length());

		myfile.open(XML_DOC_NAME, ios::out | ios::trunc);
		myfile << outXml << endl;
		myfile.close();

	}

	// Cleanup
	delete pAnnotation;
	pAnnotation = NULL;

	return 0;
}

/*
 Reads annotations from file
*/
static AnnotationPtrVector test_load_annotations(TestDocumentType dtType, const std::string& fileName)
{
	//Annotation* pAnnotation = NULL;
	//Annotation::AnnotationKind readAnnotationKind = Annotation::AK_Unknown;

	AnnotationPtrVector annotations;
	if (DT_DICOM == dtType)
	{
		DcmModel dcmModel;
		//dcmModel.ReadAnnotationFromFile(&pAnnotation, DICOM_DOC_NAME);
		int annCnt = dcmModel.ReadAnnotationsFromFile(fileName.empty() ? DICOM_DOC_NAME : fileName);

		for(int i=0; i < annCnt; i++)
		{
			Annotation* pAnnotation = dcmModel.GetNextAnnotation(&pAnnotation);

			bool isImageAnn = dynamic_cast<ImageAnnotation*>(pAnnotation) != NULL;
			bool isAnnotationOfAnn = dynamic_cast<AnnotationOfAnnotation*>(pAnnotation) != NULL;

			annotations.push_back(pAnnotation);
		}
	}
	else if (DT_XML == dtType)
	{
		XmlModel xmlModel;
		// Read from file
		//readAnnotationKind = xmlModel.ReadFromXmlFile(&pAnnotation, XML_DOC_NAME);
		int annCnt = xmlModel.ReadAnnotationsFromFile(fileName.empty() ? XML_DOC_NAME : fileName);

		for(int i=0; i < annCnt; i++)
		{
			Annotation* pAnnotation;
			pAnnotation = xmlModel.GetNextAnnotation(&pAnnotation);
			annotations.push_back(pAnnotation);
		}

		//for (AnnotationPtrVector::iterator iter = annotations.begin(); iter < annotations.end(); iter++)
		//{
		//	pAnnotation = *iter;

		//	delete pAnnotation;
		//
		//}

		// Read from string
//		readAnnotationKind = xmlModel.ReadFromXmlString(&pAnnotation, "....");


		//bool isImageAnn = dynamic_cast<ImageAnnotation*>(pAnnotation) != NULL;
		//bool isAnnotationOfAnn = dynamic_cast<AnnotationOfAnnotation*>(pAnnotation) != NULL;
	}

	//delete pAnnotation;
	//pAnnotation = NULL;

	return annotations;
}

// Save Annotation
static void test_save_annotation(Annotation* pAnnotation, TestDocumentType dtType, const std::string& outFileName)
{
	if (dtType == DT_DICOM || dtType == DT_ALL)
	{
		DcmModel dcmModel("999.9.9.9");
		dcmModel.WriteAnnotationToFile(*pAnnotation, outFileName.empty() ? DICOM_DOC_NAME : outFileName);
	}
	if (dtType == DT_XML || dtType == DT_ALL)
	{
		XmlModel* pXmlModel = new XmlModel();
		string outXml;
		std::string::size_type xmlSize = 5120; // 5K - initial buffer size
		do
		{
			std::string::traits_type::char_type* pXml = NULL;
			try
			{
				pXml = new std::string::traits_type::char_type[xmlSize];
				xmlSize = pXmlModel->WriteAnnotationToXmlString(pAnnotation, pXml, xmlSize);
				outXml = pXml;
				delete[] pXml;
				pXml = NULL;
			}
			catch(exception ex)
			{
				if (pXml != NULL)
				{
					delete[] pXml;
					pXml = NULL;
				}
			}
		}
		while(xmlSize != outXml.length());

		ofstream myfile;
		//xmlStream myfile;
		myfile.open(outFileName.empty() ? XML_DOC_NAME : outFileName.c_str(), ios::out | ios::trunc);
		myfile << outXml << endl;
		myfile.close();

		delete pXmlModel;
		pXmlModel = NULL;
	}

}

/*
	Creates test Image Annotation object.
	NOTE: After using the object, it needs to be deallocated.
*/
static ImageAnnotation* create_image_annotation()
{
	ImageAnnotation* pAnnotation = new ImageAnnotation();

	// Set Annotation data
	DateTime ct = DateTime::Now();
	pAnnotation->SetDateTime(ct);
//	string str = "AIM.1.0R3";
//	pAnnotation->SetAimVersion(str);
	string str = "Annotation comments of arbitrary length";
	pAnnotation->SetComment(str);
	str = "My Annotation Name";
	pAnnotation->SetName(str);
	str = AimUidGenerator::GenerateNewUID("1.2.3.4.5.6");
	pAnnotation->SetUniqueidentifier(str);
	pAnnotation->SetCodeValue("RECIST-123");
	pAnnotation->SetCodeMeaning("Baseline_Non-target_Lesion");
	pAnnotation->SetCodingSchemeDesignator("VKL");
	pAnnotation->SetCodingSchemeVersion("XXX");
	pAnnotation->SetPrecedentReferencedAnnotationUID("1.444.555.666.777");

	// AnatomicEntity
	AnatomicEntityVector anatomicEntityCollection;
	AnatomicEntityCharacteristicVector anatomicEntityCharCollection;
	AnatomicEntity anatomicEntity;
	AnatomicEntityCharacteristic anatomicEntityChar;
	anatomicEntity.SetCodeValue("AnatomicEntity-1");
	anatomicEntity.SetCodeMeaning("AnatomicEntity One");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX");
	double confidence = 2.1;
	anatomicEntity.SetAnnotatorConfidence(&confidence);
	anatomicEntity.SetLabel("Anatomic Entity 1 Label");
	anatomicEntityChar.SetCodeValue("AnatEntityChar-1");
	anatomicEntityChar.SetCodeMeaning("AnatomicEntityChar One");
	anatomicEntityChar.SetCodingSchemeDesignator("CDE");
	anatomicEntityChar.SetCodingSchemeVersion("XXX");
	confidence = 3.1;
	anatomicEntityChar.SetAnnotatorConfidence(&confidence);
	anatomicEntityChar.SetLabel("Anatomic Entity Char 1 Label");
	anatomicEntityCharCollection.push_back(anatomicEntityChar);
	anatomicEntityChar = AnatomicEntityCharacteristic();
	anatomicEntityChar.SetCodeValue("AnatEntityChar-2");
	anatomicEntityChar.SetCodeMeaning("AnatomicEntityChar Two");
	anatomicEntityChar.SetCodingSchemeDesignator("CDE");
	anatomicEntityChar.SetCodingSchemeVersion("XXX");
	confidence = 3.2;
	anatomicEntityChar.SetAnnotatorConfidence(&confidence);
	anatomicEntityChar.SetLabel("Anatomic Entity Char 2 Label");
	CharacteristicQuantificationPtrVector characteristicQuantifications;
	Numerical numerical;
	numerical.SetName("Numerical 1");
	numerical.SetAnnotatorConfidence(&confidence);
	numerical.SetValue(77.7);
	numerical.SetUcumString("cm");
	numerical.SetOperator(LessThan);
	characteristicQuantifications.push_back(&numerical);
	Quantile quantile;
	quantile.SetName("Quantile 1");
	quantile.SetAnnotatorConfidence(&confidence);
	quantile.SetBin(3);
	characteristicQuantifications.push_back(&quantile);
	NonQuantifiable nonQuantifiable;
	nonQuantifiable.SetName("NonQuantifiable 1");
	nonQuantifiable.SetAnnotatorConfidence(&confidence);
	nonQuantifiable.SetCodeValue("NonQCodeValue");
	nonQuantifiable.SetCodeMeaning("NonQCodeMeaning");
	nonQuantifiable.SetCodingSchemeDesignator("NonQDesignator");
	nonQuantifiable.SetCodingSchemeVersion("NonQVersion");
	characteristicQuantifications.push_back(&nonQuantifiable);
	Scale scale;
	scale.SetName("Scale 1");
	scale.SetAnnotatorConfidence(&confidence);
	scale.SetValue("Scale Value");
	scale.SetComment("Scale Comment");
	scale.SetDescription("Scale Description");
	characteristicQuantifications.push_back(&scale);
	Interval interval;
	interval.SetName("Interval 1");
	interval.SetAnnotatorConfidence(&confidence);
	interval.SetMaxValue(22.2);
	interval.SetMaxOperator(LessThan);
	interval.SetMinValue(11.1);
	interval.SetMinOperator(GreaterThan);
	interval.SetUcumString("mm");
	characteristicQuantifications.push_back(&interval);
	anatomicEntityChar.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	anatomicEntityCharCollection.push_back(anatomicEntityChar);
	anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityCharCollection);
	anatomicEntityCollection.push_back(anatomicEntity);
	anatomicEntity = AnatomicEntity();
	anatomicEntity.SetCodeValue("AnatomicEntity-2");
	anatomicEntity.SetCodeMeaning("AnatomicEntity Two");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX-2");
	confidence = 2.2;
	anatomicEntity.SetAnnotatorConfidence(&confidence);
	anatomicEntity.SetIsPresent(false);
	anatomicEntity.SetLabel("Anatomic Entity 2 Label");
	anatomicEntityCollection.push_back(anatomicEntity);
	anatomicEntity.SetCodeValue("AnatomicEntity-3");
	anatomicEntity.SetCodeMeaning("AnatomicEntity Three");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX-3");
	anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityCharCollection);
	anatomicEntityCollection.push_back(anatomicEntity);
	pAnnotation->SetAnatomicEntityCollection(anatomicEntityCollection);
	anatomicEntityCharCollection.clear();
	anatomicEntityCollection.clear();

	// Geometric Shapes
	GeoShapePtrVector shapes;
	SpatialCoordPtrVector spatialCoordCollection;
	Circle* pCircle;
	Point* pPoint;
	MultiPoint* pMultiPoint;
	aim_lib::Ellipse* pEllipse;
	aim_lib::Polyline* pPolyline;
	//
	TwoDimensionSpatialCoordinate spatialCoord1(11.0, 111.0, "1.2.840.10008.5.1.4.1.1.1.999999999.2", 0, 5);
	TwoDimensionSpatialCoordinate spatialCoord2(22.0, 222.0, "1.2.840.10008.5.1.4.1.1.1.999999999.2", 1, 5);
	TwoDimensionSpatialCoordinate spatialCoord3(22.0, 222.0, "1.2.840.10008.5.1.4.1.1.1.999999999.2", 2, 5);
	TwoDimensionSpatialCoordinate spatialCoord4(22.0, 222.0, "1.2.840.10008.5.1.4.1.1.1.999999999.2", 3, 5);
	// Circle
	pCircle = new Circle();
	pCircle->SetCenter(spatialCoord1);
	pCircle->SetRadiusPoint(spatialCoord2);
	pCircle->SetIncludeFlag(true);
	pCircle->SetShapeIdentifier(4);
	// Point
	pPoint = new Point();
	pPoint->SetCenter(spatialCoord1);
	pPoint->SetIncludeFlag(true);
	pPoint->SetShapeIdentifier(6);
	// Ellipse
	pEllipse = new aim_lib::Ellipse();
	spatialCoordCollection.push_back(&spatialCoord1);
	spatialCoordCollection.push_back(&spatialCoord2);
	spatialCoordCollection.push_back(&spatialCoord3);
	spatialCoordCollection.push_back(&spatialCoord4);
	pEllipse->SetIncludeFlag(true);
	pEllipse->SetSpatialCoordinateCollection(spatialCoordCollection);
	pEllipse->SetShapeIdentifier(7);
	spatialCoordCollection.clear();
	// MultiPoint
	pMultiPoint = new MultiPoint();
	spatialCoordCollection.push_back(&spatialCoord1);
	spatialCoordCollection.push_back(&spatialCoord2);
	pMultiPoint->SetIncludeFlag(true);
	pMultiPoint->SetSpatialCoordinateCollection(spatialCoordCollection);
	pMultiPoint->SetShapeIdentifier(8);
	spatialCoordCollection.clear();
	// Polyline
	pPolyline = new aim_lib::Polyline();
	spatialCoordCollection.push_back(&spatialCoord1);
	spatialCoordCollection.push_back(&spatialCoord2);
	spatialCoordCollection.push_back(&spatialCoord3);
	pPolyline->SetIncludeFlag(true);
	pPolyline->SetSpatialCoordinateCollection(spatialCoordCollection);
	pPolyline->SetShapeIdentifier(10);
	spatialCoordCollection.clear();
	//
	shapes.reserve(5);
	shapes.push_back(pCircle);
	shapes.push_back(pPoint);
	shapes.push_back(pMultiPoint);
	shapes.push_back(pEllipse);
	shapes.push_back(pPolyline);
	pAnnotation->SetGeometricShapeCollection(shapes);
	for (GeoShapePtrVector::size_type i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
		shapes[i] = NULL;
	}
	shapes.clear();

	GeoShapePtrVector shapes2;
	shapes2 = pAnnotation->GetGeometricShapeCollection();
	shapes2.clear();

	// Imaging Observation / Imaging Observation Characteristic
	ImagingObservationVector imagingObservationCollection;
	ImagingObservationCharacteristicVector imagingObservationCharacteristicCollection;
	ImagingObservation imagingObservation;
	ImagingObservationCharacteristic imagingObservationCharacteristic;
	imagingObservation.SetCodeValue("ImgObs-1");
	imagingObservation.SetCodeMeaning("ImagingObservation One");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetCodingSchemeVersion("Ver0");
	imagingObservation.SetComment("Imaging Observation Comment 1");
	confidence = 4.0;
	imagingObservation.SetAnnotatorConfidence(&confidence);
	imagingObservation.SetIsPresent(true);
	imagingObservation.SetLabel("Imaging Observation 1 Label");
	imagingObservationCollection.push_back(imagingObservation);  // add 1st - no Imaging Observation Characteristic
	imagingObservation.SetCodeValue("ImgObs-2");
	imagingObservation.SetCodeMeaning("ImagingObservation Two");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("Imaging Observation Comment 2");
	imagingObservation.SetIsPresent(false);
	imagingObservation.SetLabel("Imaging Observation 2 Label");
	imagingObservationCharacteristic.SetCodeValue("ImgObsChar-1");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic One");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetCodingSchemeVersion("Ver1");
	imagingObservationCharacteristic.SetComment("Imaging Observation Characteristic Comment 1");
	confidence = 0.4;
	imagingObservationCharacteristic.SetAnnotatorConfidence(&confidence);
	imagingObservationCharacteristic.SetLabel("Imaging Observation Char 1 Label");
	imagingObservationCharacteristic.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	imagingObservationCollection.push_back(imagingObservation);  // add 2nd - one Imaging Observation Characteristic
	imagingObservation.SetCodeValue("ImgObs-3");
	imagingObservation.SetCodeMeaning("ImagingObservation Three");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("");
	imagingObservation.SetIsPresent(false);
	imagingObservation.SetLabel("Imaging Observation 3 Label");
	imagingObservationCharacteristic.SetCodeValue("ImgObsChar-2");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic Two");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetComment("");
	imagingObservationCharacteristic.SetLabel("Imaging Observation Char 2 Label");
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	imagingObservationCollection.push_back(imagingObservation);  // add 3rd - two Imaging Observation Characteristics
	pAnnotation->SetImagingObservationCollection(imagingObservationCollection);
	imagingObservationCollection.clear();

	// User
	User user;
	user.SetName("ImageAnnoation User");
	user.SetLoginName("iuser");
	user.SetRoleInTrial("Recording");
	user.SetNumberWithinRoleOfClinicalTrial(3);
	pAnnotation->SetUser(&user);

	// Equipment
	Equipment equipment;
	equipment.SetManufacturerName("NWU");
	equipment.SetManufacturerModelName("AIM_3.0");
	equipment.SetSoftwareVersion("3.0b");
	pAnnotation->SetEquipment(&equipment);

	// Patient
	Person patient;
	patient.SetId("Pat#1");
	patient.SetName("Patient One");
	Date birthDate(1950, 2, 2); // 1950-01-01
	patient.SetBirthDate(birthDate);
	patient.SetSex("M");
	patient.SetEthnicGroup("EthnicGr1");
	pAnnotation->SetPatient(patient);

	// AimStatus
	AimStatus aimStatus;
	aimStatus.SetCodeValue("AIM Status Code Value");
	aimStatus.SetCodeMeaning("AIM Status Code Meaning");
	aimStatus.SetCodingSchemeDesignator("AIM TEST");
	aimStatus.SetCodingSchemeVersion("Ver X3");
	aimStatus.SetAnnotationVersion(1.0);
	aimStatus.SetAuthorizedBy("Big B");

	// Calculations
	CoordinateVector coordColl;
	Coordinate coordinate;
	CalculationDataVector dataColl;
	CalculationData data;
	DimensionVector dimColl;
	Dimension dim;
	// Calculation Results
	CalcResultVector calcResults;
	CalculationResult calcResult;
	//##### Result #1
	calcResult.SetUnitOfMeasure("cm");
	calcResult.SetType(Scalar);
	calcResult.SetNumberOfDimensions(1);
	// Dim #1
	dim.SetIndex(0);
	dim.SetLabel("Dimension 0");
	dim.SetSize(1);
	dimColl.push_back(dim);
	calcResult.SetDimensionCollection(dimColl);
	// Data #1
	data.SetValue(1.0);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(0);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	calcResult.SetCalculationDataCollection(dataColl);
	calcResults.push_back(calcResult);
	// Cleanup
	dimColl.clear();
	coordColl.clear();
	dataColl.clear();
	data = CalculationData();
	calcResult = CalculationResult();
	//##### Result #2
	calcResult.SetUnitOfMeasure("mm");
	calcResult.SetType(Array);
	calcResult.SetNumberOfDimensions(2);
	// Dim #1
	dim.SetIndex(0);
	dim.SetLabel("Dimension 0");
	dim.SetSize(3);
	dimColl.push_back(dim);
	// Dim #2
	dim.SetIndex(1);
	dim.SetLabel("Dimension 1");
	dim.SetSize(7);
	dimColl.push_back(dim);
	calcResult.SetDimensionCollection(dimColl);
	// Data #1
	data.SetValue(11.0);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(2);
	coordColl.push_back(coordinate);
	coordinate.SetDimensionIndex(1);
	coordinate.SetPosition(4);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	// Data #2
	data.SetValue(22.22f);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(2);
	coordColl.push_back(coordinate);
	coordinate.SetDimensionIndex(1);
	coordinate.SetPosition(6);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	//
	calcResult.SetCalculationDataCollection(dataColl);
	calcResults.push_back(calcResult);
	// Cleanup
	dimColl.clear();
	coordColl.clear();
	dataColl.clear();
	data = CalculationData();
	calcResult = CalculationResult();
	// Referenced Calculation
	ReferencedCalcVector refCalcs;
	ReferencedCalculation refCalc;
	refCalc.SetUniqueIdentifier(AimUidGenerator::GenerateNewUID("11.111.1"));
	refCalcs.push_back(refCalc);
	refCalc.SetUniqueIdentifier(AimUidGenerator::GenerateNewUID("22.222.2"));
	refCalcs.push_back(refCalc);
	// Referenced Geo Shape
	ReferencedGeometricShapeVector refGeoShapeCollection;
	ReferencedGeometricShape refGeoShape;
	refGeoShape.SetReferencedShapeIdentifier(1);
	refGeoShapeCollection.push_back(refGeoShape);
	refGeoShape.SetReferencedShapeIdentifier(2);
	refGeoShapeCollection.push_back(refGeoShape);
	// Calculation
	CalculationVector calculations;
	Calculation calc;
	calc.SetUID(AimUidGenerator::GenerateNewUID("33.333"));
	calc.SetCodeValue("Value::Length");
	calc.SetCodeMeaning("length");
	calc.SetCodingSchemeDesignator("CALC_SCHEME");
	calc.SetDescription("Description of the Calculation One - Length");
	calc.SetMathML("MathML for the Calc One");
	calc.SetCalculationResultCollection(calcResults);
	calc.SetReferencedCalculationCollection(refCalcs);
	calculations.push_back(calc);
	calc.SetUID(AimUidGenerator::GenerateNewUID("44.444"));
	calc.SetDescription("Description of the Calculation Two - Mean");
	calc.SetMathML("MathML for the Calc Two");
	calc.SetAlgorithmName("Algorithm Name 1");
	calc.SetAlgorithmVersion("Algorithm Version 1");
	calc.SetCalculationResultCollection(calcResults);
	calc.SetReferencedCalculationCollection(refCalcs);
	calc.SetReferencedGeometricShapeCollection(refGeoShapeCollection);
	calculations.push_back(calc);
	pAnnotation->SetCalculationCollection(calculations);
	// Cleanup
	calcResults.clear();
	refCalcs.clear();
	refGeoShapeCollection.clear();
	calculations.clear();

	// Inference
	Inference inference;
	InferenceVector inferenceCollection;
	inference.SetCodeMeaning("Inference 1");
	inference.SetCodeValue("Inference 1");
	inference.SetCodingSchemeDesignator("VKL");
	inference.SetCodingSchemeVersion("Ver 1");
	confidence = 5.7;
	inference.SetAnnotatorConfidence(&confidence);
	inference.SetImageEvidence(true);
	inferenceCollection.push_back(inference);
	inference.SetCodeMeaning("Inference 2");
	inference.SetCodeValue("Inference 2");
	inference.SetCodingSchemeDesignator("Inference 2");
	inference.SetCodingSchemeVersion("Inference 2");
	confidence = 5.77;
	inference.SetAnnotatorConfidence(&confidence);
	inference.SetImageEvidence(true);
	inferenceCollection.push_back(inference);
	pAnnotation->SetInferenceCollection(inferenceCollection);

	// Image Reference
	ImageReferencePtrVector imageReferences;
	DICOMImageReference* pDicomImageRef;
	Image image;
	ImageSeries series;
	ImageStudy study;
	ImageVector images;
	PresentationState presentationState;
	PresentationStateVector presentationStates;
	// Img Ref #1
	pDicomImageRef = new DICOMImageReference();
	image.SetSopClassUID("1.2.840.10008.5.1.4.1.1.999999999.1");
	image.SetSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.1");
	images.push_back(image);
	series.SetInstanceUID("555.555.555.1");
	series.SetImageCollection(images);
	study.SetStartDate(Date::Today());
	study.SetStartTime(Time::Now());
	study.SetInstanceUID("666.6.6.66.6.6.1");
	study.SetSeries(series);
	pDicomImageRef->SetStudy(study);
	presentationState.SetSopInstanceUID("777.333.444.55555");
	presentationStates.push_back(presentationState);
	pDicomImageRef->SetPresentationStateCollection(presentationStates);
	imageReferences.push_back(pDicomImageRef);
	pDicomImageRef = new DICOMImageReference();
	// Img Ref #2
	images.clear();
	image.SetSopClassUID("1.2.840.10008.5.1.4.1.1.999999999.2");
	image.SetSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.2");
	images.push_back(image);
	series.SetInstanceUID("555.5.555.5555.2");
	series.SetImageCollection(images);
	study.SetStartDate(Date::Today());
	study.SetStartTime(Time::Now());
	study.SetInstanceUID("666.6.6.66.6.6.1");
	study.SetSeries(series);
	pDicomImageRef->SetStudy(study);
	imageReferences.push_back(pDicomImageRef);
	// Img Ref #3
	WebImageReference* pWebImageRef;
	pWebImageRef = new WebImageReference();
	pWebImageRef->SetURI("uri:Web-UIR-1");
	imageReferences.push_back(pWebImageRef);
	// Img Ref #4
	pWebImageRef = new WebImageReference();
	pWebImageRef->SetURI("uri:Web-UIR-2");
	imageReferences.push_back(pWebImageRef);
	pAnnotation->SetImageReferenceCollection(imageReferences);
	for(ImageReferencePtrVector::size_type i = 0; i < imageReferences.size(); i++)
	{
		delete imageReferences[i];
		imageReferences[i] = NULL;
	}
	imageReferences.clear();

	// Segmentation 1
	SegmentationVector segmentationCollection;
	Segmentation segmentation;
	segmentation.SetSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.3"); // Segmentation's SOP Instance UID
	segmentation.SetSopClassUID("1.2.840.10008.5.1.4.1.1.66.4"); // Segmentation Storage SOP Class UID
	segmentation.SetReferencedSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.1"); // Image SOP Instance UID
	segmentation.SetSegmentNumber(1);
	imagingObservation = ImagingObservation();
	imagingObservationCharacteristic = ImagingObservationCharacteristic();
	imagingObservationCharacteristicCollection = ImagingObservationCharacteristicVector();
	imagingObservation.SetCodeValue("ImgObsForSeg-1");
	imagingObservation.SetCodeMeaning("ImagingObservation code meaning 'Segmentation 1'");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("Segmentation's Imaging Observation Segmentations comment 1");
	imagingObservation.SetLabel("Segmentation's Imaging Observation Segmentations label 1");
	imagingObservationCharacteristic.SetCodeValue("ImgObsCharSeg-1");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic code meaning Segmentation 1");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetComment("Segmentation's Imaging Observation Characteristic comment Segmentation 1");
	imagingObservationCharacteristic.SetLabel("Segmentation's Imaging Observation Characteristic Label Segmentation 1");
	confidence = 5.1;
	imagingObservationCharacteristic.SetAnnotatorConfidence(&confidence);
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	segmentation.SetImagingObservation(&imagingObservation);
	segmentationCollection.push_back(segmentation);
	// Segmentation 2
	segmentation = Segmentation();
	segmentation.SetSopInstanceUID("1.2.840.10008.5.1.4.1.1.999999999.3"); // Segmentation's SOP Instance UID
	segmentation.SetSopClassUID("1.2.840.10008.5.1.4.1.1.66.4"); // Segmentation Storage SOP Class UID
	segmentation.SetReferencedSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.2"); // Image SOP Instance UID
	segmentation.SetSegmentNumber(2);
	imagingObservation = ImagingObservation();
	imagingObservationCharacteristic = ImagingObservationCharacteristic();
	imagingObservationCharacteristicCollection = ImagingObservationCharacteristicVector();
	imagingObservation.SetCodeValue("ImgObsForSeg-2");
	imagingObservation.SetCodeMeaning("ImagingObservation code meaning 'Segmentation 2'");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("Segmentation's Imaging Observation Segmentation's comment 2");
	imagingObservation.SetLabel("Segmentation's Imaging Observation Segmentation's label 2");
	imagingObservationCharacteristic.SetCodeValue("ImgObsCharSeg-2");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic code meaning PMap 2");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetComment("Segmention's Imaging Observation Characteristic comment PMap 2");
	imagingObservationCharacteristic.SetLabel("Segmention's Imaging Observation Characteristic label PMap 2");
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	segmentation.SetImagingObservation(&imagingObservation);
	segmentationCollection.push_back(segmentation);
	// Segmentation 3
	segmentation = Segmentation();
	segmentation.SetSopInstanceUID("1.2.3.4.5.6.7.8.9"); //
	segmentation.SetSopClassUID("1.2.840.10008.5.1.4.1.1.66.4"); // Segmentation Storage SOP Class UID
	segmentation.SetReferencedSopInstanceUID("1.2.840.10008.5.1.4.1.1.1.999999999.1"); // Referenced image SOP Instance UID
	segmentation.SetSegmentNumber(3);
	imagingObservation = ImagingObservation();
	imagingObservationCharacteristic = ImagingObservationCharacteristic();
	imagingObservationCharacteristicCollection = ImagingObservationCharacteristicVector();
	imagingObservation.SetCodeValue("ImgObsForSeg-3");
	imagingObservation.SetCodeMeaning("ImagingObservation code meaning 'Segmentation 3'");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("Segmentation's Imaging Observation Segmentation comment 3");
	imagingObservation.SetLabel("Segmentation's Imaging Observation Segmentation label 3");
	imagingObservationCharacteristic.SetCodeValue("ImgObsCharSeg-3");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic code meaning Segmentation 2");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetComment("Segmentation's Imaging Observation Characteristic comment Segmentation 2");
	imagingObservationCharacteristic.SetLabel("Segmentation's Imaging Observation Characteristic label Segmentation 2");
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	segmentation.SetImagingObservation(&imagingObservation);
	segmentationCollection.push_back(segmentation);
	pAnnotation->SetSegmentationCollection(segmentationCollection);
	segmentationCollection.clear();

	TextAnnotationVector textAnnotations;
	TextAnnotation textAnnotation;
	SpatialCoordPtrVector spatialCoords;
	TwoDimensionSpatialCoordinate spatialCoord;
	MultiPoint multiPoint;
	// Text Markup 1
	textAnnotation.SetText("Markup Text 1");
	textAnnotation.SetTextJustify("Markup Text Justify 1");
	textAnnotation.SetFont("Markup Text Font 1");
	textAnnotation.SetFontColor("Markup Text Color 1");
	textAnnotation.SetFontEffect("Markup Text Effect 1");
	textAnnotation.SetFontOpacity("Markup Text opacity 1");
	textAnnotation.SetFontSize("Markup Text Size 1");
	textAnnotation.SetFontStyle("Markup Text Style 1");
	// Connector Start Point
	spatialCoord.SetCoordinateIndex(0);
	spatialCoord.SetX(10.0);
	spatialCoord.SetY(3.0);
	spatialCoord.SetImageReferenceUID("1.2.840.10008.5.1.4.1.1.1.999999999.2");
	spatialCoord.SetReferencedFrameNumber(7);
	spatialCoords.push_back(spatialCoord.Clone());
	// Connector Finish Point
	spatialCoord.SetCoordinateIndex(1);
	spatialCoord.SetX(20.0);
	spatialCoord.SetY(13.0);
	spatialCoord.SetImageReferenceUID("1.2.840.10008.5.1.4.1.1.1.999999999.2");
	spatialCoord.SetReferencedFrameNumber(7);
	spatialCoords.push_back(spatialCoord.Clone());
	// Connector
	//multiPoint.SetIncludeFlag(true); - ignored by Text Annotation
	multiPoint.SetShapeIdentifier(13);
	multiPoint.SetSpatialCoordinateCollection(spatialCoords);
	for(SpatialCoordPtrVector::size_type i = 0; i < spatialCoords.size(); i++)
	{
		delete spatialCoords[i];
		spatialCoords[i] = NULL;
	}
	spatialCoords.clear();
	textAnnotation.SetConnectorPoints(&multiPoint);
	textAnnotations.push_back(textAnnotation);
	// Text Markup 1
	multiPoint = MultiPoint();
	//multiPoint.SetIncludeFlag(false); - ignored by Text Annotation
	multiPoint.SetShapeIdentifier(2);
	multiPoint.SetSpatialCoordinateCollection(spatialCoords);
	textAnnotation = TextAnnotation();
	textAnnotation.SetConnectorPoints(&multiPoint);
	textAnnotation.SetText("Markup Text 2");
	textAnnotation.SetTextJustify("Markup Text Justify 2");
	textAnnotation.SetFont("Markup Text Font 2");
	textAnnotation.SetFontColor("Markup Text Color 2");
	textAnnotation.SetFontEffect("Markup Text Effect 2");
	textAnnotation.SetFontOpacity("Markup Text opacity 2");
	textAnnotation.SetFontSize("Markup Text Size 2");
	textAnnotation.SetFontStyle("Markup Text Style 2");
	textAnnotations.push_back(textAnnotation);
	pAnnotation->SetTextAnnotationCollection(textAnnotations);

	return pAnnotation;
}


/*
	Creates test Annotation Of Annotation object.
	NOTE: After using the object, it needs to be deallocated.
*/
static AnnotationOfAnnotation* create_annotation_of_annotation()
{
	AnnotationOfAnnotation* pAnnotation = new AnnotationOfAnnotation();

	// Set Annotation data
	time_t ct;
	time(&ct);
	pAnnotation->SetDateTime(ct);
//	string str = "AIM.1.0R3";
//	pAnnotation->SetAimVersion(str);
	string str = "Annotation comments of arbitrary length";
	pAnnotation->SetComment(str);
	str = "My Annotation Name";
	pAnnotation->SetName(str);
	str = AimUidGenerator::GenerateNewUID("1.2.3.4.5.6");
	pAnnotation->SetUniqueidentifier(str);
	pAnnotation->SetCodeValue("RECIST-123");
	pAnnotation->SetCodeMeaning("Baseline_Non-target_Lesion");
	pAnnotation->SetCodingSchemeDesignator("VKL");
	pAnnotation->SetCodingSchemeVersion("XXX");
	pAnnotation->SetPrecedentReferencedAnnotationUID("1.444.555.666.777");

	// AnatomicEntity
	AnatomicEntityVector anatomicEntityCollection;
	AnatomicEntityCharacteristicVector anatomicEntityCharCollection;
	AnatomicEntity anatomicEntity;
	AnatomicEntityCharacteristic anatomicEntityChar;
	anatomicEntity.SetCodeValue("AnatomicEntity-1");
	anatomicEntity.SetCodeMeaning("AnatomicEntity One");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX");
	double confidence = 2.1;
	anatomicEntity.SetAnnotatorConfidence(&confidence);
	anatomicEntity.SetLabel("Anatomic Entity 1 Label");
	anatomicEntityChar.SetCodeValue("AnatEntityChar-1");
	anatomicEntityChar.SetCodeMeaning("AnatomicEntityChar One");
	anatomicEntityChar.SetCodingSchemeDesignator("CDE");
	anatomicEntityChar.SetCodingSchemeVersion("XXX");
	confidence = 3.1;
	anatomicEntityChar.SetAnnotatorConfidence(&confidence);
	anatomicEntityChar.SetLabel("Anatomic Entity Char 1 Label");
	anatomicEntityCharCollection.push_back(anatomicEntityChar);
	anatomicEntityChar = AnatomicEntityCharacteristic();
	anatomicEntityChar.SetCodeValue("AnatEntityChar-2");
	anatomicEntityChar.SetCodeMeaning("AnatomicEntityChar Two");
	anatomicEntityChar.SetCodingSchemeDesignator("CDE");
	anatomicEntityChar.SetCodingSchemeVersion("XXX");
	confidence = 3.2;
	anatomicEntityChar.SetAnnotatorConfidence(&confidence);
	anatomicEntityChar.SetLabel("Anatomic Entity Char 2 Label");
	CharacteristicQuantificationPtrVector characteristicQuantifications;
	Numerical numerical;
	numerical.SetName("Numerical 1");
	numerical.SetAnnotatorConfidence(&confidence);
	numerical.SetValue(77.7);
	numerical.SetUcumString("cm");
	numerical.SetOperator(LessThan);
	characteristicQuantifications.push_back(&numerical);
	Quantile quantile;
	quantile.SetName("Quantile 1");
	quantile.SetAnnotatorConfidence(&confidence);
	quantile.SetBin(3);
	characteristicQuantifications.push_back(&quantile);
	NonQuantifiable nonQuantifiable;
	nonQuantifiable.SetName("NonQuantifiable 1");
	nonQuantifiable.SetAnnotatorConfidence(&confidence);
	nonQuantifiable.SetCodeValue("NonQCodeValue");
	nonQuantifiable.SetCodeMeaning("NonQCodeMeaning");
	nonQuantifiable.SetCodingSchemeDesignator("NonQDesignator");
	nonQuantifiable.SetCodingSchemeVersion("NonQVersion");
	characteristicQuantifications.push_back(&nonQuantifiable);
	Scale scale;
	scale.SetName("Scale 1");
	scale.SetAnnotatorConfidence(&confidence);
	scale.SetValue("Scale Value");
	scale.SetComment("Scale Comment");
	scale.SetDescription("Scale Description");
	characteristicQuantifications.push_back(&scale);
	Interval interval;
	interval.SetName("Interval 1");
	interval.SetAnnotatorConfidence(&confidence);
	interval.SetMaxValue(22.2);
	interval.SetMaxOperator(LessThan);
	interval.SetMinValue(11.1);
	interval.SetMinOperator(GreaterThan);
	interval.SetUcumString("mm");
	characteristicQuantifications.push_back(&interval);
	anatomicEntityChar.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	anatomicEntityCharCollection.push_back(anatomicEntityChar);
	anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityCharCollection);
	anatomicEntityCollection.push_back(anatomicEntity);
	anatomicEntity = AnatomicEntity();
	anatomicEntity.SetCodeValue("AnatomicEntity-2");
	anatomicEntity.SetCodeMeaning("AnatomicEntity Two");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX-2");
	confidence = 2.2;
	anatomicEntity.SetAnnotatorConfidence(&confidence);
	anatomicEntity.SetIsPresent(false);
	anatomicEntity.SetLabel("Anatomic Entity 2 Label");
	anatomicEntityCollection.push_back(anatomicEntity);
	anatomicEntity.SetCodeValue("AnatomicEntity-3");
	anatomicEntity.SetCodeMeaning("AnatomicEntity Three");
	anatomicEntity.SetCodingSchemeDesignator("CDE");
	anatomicEntity.SetCodingSchemeVersion("XXX-3");
	anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityCharCollection);
	anatomicEntityCollection.push_back(anatomicEntity);
	pAnnotation->SetAnatomicEntityCollection(anatomicEntityCollection);
	anatomicEntityCharCollection.clear();
	anatomicEntityCollection.clear();

	// Imaging Observation / Imaging Observation Characteristic
	ImagingObservationVector imagingObservationCollection;
	ImagingObservationCharacteristicVector imagingObservationCharacteristicCollection;
	ImagingObservation imagingObservation;
	ImagingObservationCharacteristic imagingObservationCharacteristic;
	imagingObservation.SetCodeValue("ImgObs-1");
	imagingObservation.SetCodeMeaning("ImagingObservation One");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetCodingSchemeVersion("Ver0");
	imagingObservation.SetComment("Imaging Observation Comment 1");
	confidence = 4.0;
	imagingObservation.SetAnnotatorConfidence(&confidence);
	imagingObservation.SetIsPresent(true);
	imagingObservation.SetLabel("Imaging Observation 1 Label");
	imagingObservationCollection.push_back(imagingObservation);  // add 1st - no Imaging Observation Characteristic
	imagingObservation.SetCodeValue("ImgObs-2");
	imagingObservation.SetCodeMeaning("ImagingObservation Two");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("Imaging Observation Comment 2");
	imagingObservation.SetIsPresent(false);
	imagingObservation.SetLabel("Imaging Observation 2 Label");
	imagingObservationCharacteristic.SetCodeValue("ImgObsChar-1");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic One");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetCodingSchemeVersion("Ver1");
	imagingObservationCharacteristic.SetComment("Imaging Observation Characteristic Comment 1");
	confidence = 0.4;
	imagingObservationCharacteristic.SetAnnotatorConfidence(&confidence);
	imagingObservationCharacteristic.SetLabel("Imaging Observation Char 1 Label");
	imagingObservationCharacteristic.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	imagingObservationCollection.push_back(imagingObservation);  // add 2nd - one Imaging Observation Characteristic
	imagingObservation.SetCodeValue("ImgObs-3");
	imagingObservation.SetCodeMeaning("ImagingObservation Three");
	imagingObservation.SetCodingSchemeDesignator("CDE");
	imagingObservation.SetComment("");
	imagingObservation.SetIsPresent(false);
	imagingObservation.SetLabel("Imaging Observation 3 Label");
	imagingObservationCharacteristic.SetCodeValue("ImgObsChar-2");
	imagingObservationCharacteristic.SetCodeMeaning("ImagingObservationCharacteristic Two");
	imagingObservationCharacteristic.SetCodingSchemeDesignator("CDE");
	imagingObservationCharacteristic.SetComment("");
	imagingObservationCharacteristic.SetLabel("Imaging Observation Char 2 Label");
	imagingObservationCharacteristicCollection.push_back(imagingObservationCharacteristic);
	imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationCharacteristicCollection);
	imagingObservationCollection.push_back(imagingObservation);  // add 3rd - two Imaging Observation Characteristics
	pAnnotation->SetImagingObservationCollection(imagingObservationCollection);
	imagingObservationCollection.clear();

	// User
	User user;
	user.SetName("AnnOfAnnoation User");
	user.SetLoginName("auser");
	user.SetRoleInTrial("Verifying");
	user.SetNumberWithinRoleOfClinicalTrial(3);
	pAnnotation->SetUser(&user);

	// Equipment
	Equipment equipment;
	equipment.SetManufacturerName("NWU");
	equipment.SetManufacturerModelName("AIM_3.0");
	equipment.SetSoftwareVersion("3.0b");
	pAnnotation->SetEquipment(&equipment);

	// AimStatus
	AimStatus aimStatus;
	aimStatus.SetCodeValue("AIM Status Code Value");
	aimStatus.SetCodeMeaning("AIM Status Code Meaning");
	aimStatus.SetCodingSchemeDesignator("AIM TEST");
	aimStatus.SetCodingSchemeVersion("Ver X3");
	aimStatus.SetAnnotationVersion(1.0);
	aimStatus.SetAuthorizedBy("Big B");

	// Calculations
	CoordinateVector coordColl;
	Coordinate coordinate;
	CalculationDataVector dataColl;
	CalculationData data;
	DimensionVector dimColl;
	Dimension dim;
	// Calculation Results
	CalcResultVector calcResults;
	CalculationResult calcResult;
	//##### Result #1
	calcResult.SetUnitOfMeasure("cm");
	calcResult.SetType(Scalar);
	calcResult.SetNumberOfDimensions(1);
	// Dim #1
	dim.SetIndex(0);
	dim.SetLabel("Dimension 0");
	dim.SetSize(1);
	dimColl.push_back(dim);
	calcResult.SetDimensionCollection(dimColl);
	// Data #1
	data.SetValue(1.0);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(0);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	calcResult.SetCalculationDataCollection(dataColl);
	calcResults.push_back(calcResult);
	// Cleanup
	dimColl.clear();
	coordColl.clear();
	dataColl.clear();
	data = CalculationData();
	calcResult = CalculationResult();
	//##### Result #2
	calcResult.SetUnitOfMeasure("mm");
	calcResult.SetType(Array);
	calcResult.SetNumberOfDimensions(2);
	// Dim #1
	dim.SetIndex(0);
	dim.SetLabel("Dimension 0");
	dim.SetSize(3);
	dimColl.push_back(dim);
	// Dim #2
	dim.SetIndex(1);
	dim.SetLabel("Dimension 1");
	dim.SetSize(7);
	dimColl.push_back(dim);
	calcResult.SetDimensionCollection(dimColl);
	// Data #1
	data.SetValue(11.0);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(2);
	coordColl.push_back(coordinate);
	coordinate.SetDimensionIndex(1);
	coordinate.SetPosition(4);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	// Data #2
	data.SetValue(22.22f);
	coordinate.SetDimensionIndex(0);
	coordinate.SetPosition(2);
	coordColl.push_back(coordinate);
	coordinate.SetDimensionIndex(1);
	coordinate.SetPosition(6);
	coordColl.push_back(coordinate);
	data.SetCoordinateCollection(coordColl);
	dataColl.push_back(data);
	//
	calcResult.SetCalculationDataCollection(dataColl);
	calcResults.push_back(calcResult);
	// Cleanup
	dimColl.clear();
	coordColl.clear();
	dataColl.clear();
	data = CalculationData();
	calcResult = CalculationResult();
	// Referenced Calculation
	ReferencedCalcVector refCalcs;
	ReferencedCalculation refCalc;
	refCalc.SetUniqueIdentifier(AimUidGenerator::GenerateNewUID("11.111.1"));
	refCalcs.push_back(refCalc);
	refCalc.SetUniqueIdentifier(AimUidGenerator::GenerateNewUID("22.222.2"));
	refCalcs.push_back(refCalc);
	// Referenced Geo Shape
	ReferencedGeometricShapeVector refGeoShapeCollection;
	ReferencedGeometricShape refGeoShape;
	refGeoShape.SetReferencedShapeIdentifier(1);
	refGeoShapeCollection.push_back(refGeoShape);
	refGeoShape.SetReferencedShapeIdentifier(2);
	refGeoShapeCollection.push_back(refGeoShape);
	// Calculation
	CalculationVector calculations;
	Calculation calc;
	calc.SetUID(AimUidGenerator::GenerateNewUID("33.333"));
	calc.SetCodeValue("Value::Length");
	calc.SetCodeMeaning("length");
	calc.SetCodingSchemeDesignator("CALC_SCHEME");
	calc.SetDescription("Description of the Calculation One - Length");
	calc.SetMathML("MathML for the Calc One");
	calc.SetCalculationResultCollection(calcResults);
	calc.SetReferencedCalculationCollection(refCalcs);
	calculations.push_back(calc);
	calc.SetUID(AimUidGenerator::GenerateNewUID("44.444"));
	calc.SetDescription("Description of the Calculation Two - Mean");
	calc.SetMathML("MathML for the Calc Two");
	calc.SetAlgorithmName("Algorithm Name 1");
	calc.SetAlgorithmVersion("Algorithm Version 1");
	calc.SetCalculationResultCollection(calcResults);
	calc.SetReferencedCalculationCollection(refCalcs);
	calc.SetReferencedGeometricShapeCollection(refGeoShapeCollection);
	calculations.push_back(calc);
	pAnnotation->SetCalculationCollection(calculations);
	// Cleanup
	calcResults.clear();
	refCalcs.clear();
	refGeoShapeCollection.clear();
	calculations.clear();

	// Inference
	Inference inference;
	InferenceVector inferenceCollection;
	inference.SetCodeMeaning("Inference 1");
	inference.SetCodeValue("Inference 1");
	inference.SetCodingSchemeDesignator("VKL");
	inference.SetCodingSchemeVersion("Ver 1");
	confidence = 5.7;
	inference.SetAnnotatorConfidence(&confidence);
	inference.SetImageEvidence(true);
	inferenceCollection.push_back(inference);
	inference.SetCodeMeaning("Inference 2");
	inference.SetCodeValue("Inference 2");
	inference.SetCodingSchemeDesignator("Inference 2");
	inference.SetCodingSchemeVersion("Inference 2");
	confidence = 5.77;
	inference.SetAnnotatorConfidence(&confidence);
	inference.SetImageEvidence(true);
	inferenceCollection.push_back(inference);
	pAnnotation->SetInferenceCollection(inferenceCollection);

	// Referenced Annotations
	ReferencedAnnotationVector referencedAnnotations;
	ReferencedAnnotation referencedAnnotation;
	AnnotationRole annotationRole;
	annotationRole.SetCodeValue("Role-1");
	annotationRole.SetCodeMeaning("Annoation Role 1");
	annotationRole.SetCodingSchemeDesignator("VKL");
	annotationRole.SetCodingSchemeVersion("Ver1");
	annotationRole.SetRoleSequenceNumber(33);
	referencedAnnotation.SetReferencedAnnotationUID(AimUidGenerator::GenerateNewUID("55555"));
	referencedAnnotation.SetAnnotationRole(&annotationRole);
	referencedAnnotations.push_back(referencedAnnotation);
	referencedAnnotation = ReferencedAnnotation();
	referencedAnnotation.SetReferencedAnnotationUID(AimUidGenerator::GenerateNewUID("66666"));
	referencedAnnotations.push_back(referencedAnnotation);
	pAnnotation->SetReferencedAnnotationCollection(referencedAnnotations);

	return pAnnotation;
}

//int test_jni_protege_bridge()
//{
//	try
//	{
//		aim_protege_jni::CJniProtegeBridge protegeBridge("C:/Projects/aim/AIMOntology/v1.1");
//
//		int annTypeId = 0;
//		//for(int annTypeId=0; annTypeId < 14; annTypeId++) // check all posible annotation types
//		{
//			//std::string retval = protegeBridge.getOntologyValues(annTypeId);
//			std::string retval = protegeBridge.getOntologyValues("RID3");
//
//			ofstream myfile;
//			std::stringstream fileName;
//			fileName << "AIMOntology" << annTypeId << ".xml";
//			myfile.open(const_cast<char*>(fileName.str().c_str()), ios::out | ios::trunc);
//			myfile << retval << endl;
//			myfile.close();
//		}
//
//		std::string retval = protegeBridge.getValidationResult("NU", "NU", "NU");  // test failure
//		cout << "Validation Result (" << "NU, NU, NU):" << endl << retval << endl;
//		retval = protegeBridge.getValidationResult("j.0:RID226", "fornix of calyx", "RADLEX"); // test existing element
//		cout << "Validation Result (" << "j.0:RID226, fornix of calyx, RADLEX):" << endl << retval << endl;
//
//
//		// cout << retval << endl;
//	}
//	catch(std::exception& ex)
//	{
//		cout << ex.what() << endl;
//	}
//	catch(...)
//	{
//		cout << "Other exception is cought" << endl;
//	}
//
//	return 0;
//}
