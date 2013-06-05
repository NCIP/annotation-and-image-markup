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

#include "../AIMLib/external/CD.h"
#include "../AIMLib/external/II.h"
#include "../AIMLib/AimHeaders.h"

#include "../AIMLib/Operations/BaseModel.h"
#include "../AIMLib/Operations/DcmModel.h"
#include "../AIMLib/Operations/XmlModel.h"

#include <cstdlib>
#include <cassert>

#include <sstream>

#include "memdebug.h"

using namespace aim_lib;
using namespace iso_21090;

#define DICOM_DOC_NAME "outdoc.dcm"
#define DICOM_DOC_NAME2 "outdoc2.dcm"
#define XML_DOC_NAME "outdoc.xml"
#define XML_DOC_NAME2 "outdoc2.xml"

enum TestDocumentType{
	DT_DICOM,
	DT_XML,
	DT_ALL
};

static int test_create_annotation(AnnotationEntity::AnnotationType, TestDocumentType);
static int test_create_annotations(int annCount, AnnotationEntity::AnnotationType, TestDocumentType);
static void test_save_annotation(const AnnotationCollection*, TestDocumentType, const std::string& = "");
static AnnotationCollection* test_load_annotations(TestDocumentType, const std::string& = "");
static void test_create_load_save_annotation(AnnotationEntity::AnnotationType, TestDocumentType, TestDocumentType);
static void test_load_save_annotation(TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo, const std::string& = "", const std::string& = "");

static ImageAnnotation* create_image_annotation();
static ImageAnnotationCollection* create_image_annotation_collection(bool = true);
static AnnotationOfAnnotation* create_annotation_of_annotation();
static AnnotationOfAnnotationCollection* create_annotation_of_annotation_collection(bool = true);
static void populateAnnotationCollection(AnnotationCollection*);
static void populateAnnotationEntity(AnnotationEntity*);
static void populateGeometricShapeEntity(GeometricShapeEntity*, int);
static void populateAnnotationStatments(AnnotationEntity *, std::vector<AnnotationStatement*>&);

static int test_jni_protege_bridge();

#if !defined( __GNUC__ )
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char **argv)
#endif
{
	// 1. Test generating annotations
	//test_create_annotation(AnnotationEntity::AT_ImageAnnotation, DT_DICOM);
	//test_create_annotation(AnnotationEntity::AT_AnnotationOfAnnotation, DT_DICOM);

	//test_create_annotation(AnnotationEntity::AT_ImageAnnotation, DT_XML);
	//test_create_annotation(AnnotationEntity::AT_AnnotationOfAnnotation, DT_XML);

	//test_create_annotations(2, AnnotationEntity::AT_ImageAnnotation, DT_DICOM);
	//test_create_annotations(2, AnnotationEntity::AT_AnnotationOfAnnotation, DT_DICOM);

	//test_create_annotations(2, AnnotationEntity::AT_ImageAnnotation, DT_XML);
	//test_create_annotations(2, AnnotationEntity::AT_AnnotationOfAnnotation, DT_XML);

	// 2. Test generating/reading/saving annotations cycle
	test_create_load_save_annotation(AnnotationEntity::AT_ImageAnnotation, DT_XML, DT_XML);
	//test_create_load_save_annotation(AnnotationEntity::AT_AnnotationOfAnnotation, DT_XML, DT_XML);

	//test_create_load_save_annotation(AnnotationEntity::AT_ImageAnnotation, DT_DICOM, DT_XML);
	//test_create_load_save_annotation(AnnotationEntity::AT_AnnotationOfAnnotation, DT_DICOM, DT_XML);

	//test_create_load_save_annotation(AnnotationEntity::AT_ImageAnnotation, DT_XML, DT_DICOM);
	//test_create_load_save_annotation(AnnotationEntity::AT_AnnotationOfAnnotation, DT_XML, DT_DICOM);

	// 3. Test reading annotations from file
	//test_load_annotations(DT_XML);
	//test_load_annotations(DT_DICOM);

	//test_load_save_annotation(DT_DICOM, DT_XML);
	//test_load_save_annotation(DT_XML, DT_DICOM);
	//test_load_save_annotation(DT_XML, DT_XML);

	// Test reading specific individual annotation
	//test_load_annotations(DT_XML, XML_DOC_NAME);
	//test_load_annotations(DT_XML, "AIM_tcga_to_3.0_v2.xml");

	//test_load_save_annotation(DT_XML, DT_DICOM, "AIM_tcga_to_3.0_v2.xml", "AIM_tcga_to_3.0_v2.dcm");
	//test_load_save_annotation(DT_DICOM, DT_XML, "058_aim1_vk.dcm", "058_aim1_vk_out.xml");
}

static int test_create_annotation(AnnotationEntity::AnnotationType atAnnotationKind, TestDocumentType dtType)
{
	AnnotationCollection* pAnnotationColl = NULL;

	if (atAnnotationKind == AnnotationEntity::AT_ImageAnnotation)
		pAnnotationColl = create_image_annotation_collection();
	else if (atAnnotationKind == AnnotationEntity::AT_AnnotationOfAnnotation)
		pAnnotationColl = create_annotation_of_annotation_collection();
	else
	{
		assert(false);
		return -1;
	}

	test_save_annotation(pAnnotationColl, dtType);

	// Cleanup
	delete pAnnotationColl;
	pAnnotationColl = NULL;

	return 0;
}

// Test createing ->saving->loading->saving an annotation
static void test_create_load_save_annotation(AnnotationEntity::AnnotationType atAnnotationKind, TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo)
{
	AnnotationCollection* pAnnotationColl;

	if (test_create_annotation(atAnnotationKind, /*dtTypeFrom*/ DT_ALL) == 0)
	{
		pAnnotationColl = test_load_annotations(dtTypeFrom);
		if (pAnnotationColl)
		{
			test_save_annotation(pAnnotationColl, dtTypeTo, dtTypeTo == DT_DICOM ? DICOM_DOC_NAME2 : XML_DOC_NAME2);
		}

		delete pAnnotationColl;
		pAnnotationColl = NULL;
	}
}

// Test loading->saving an annotation
static void test_load_save_annotation(TestDocumentType dtTypeFrom, TestDocumentType dtTypeTo, const std::string& fileNameFrom/* = ""*/, const std::string& fileNameTo/* = ""*/)
{
	AnnotationCollection* pAnnotationColl;

	pAnnotationColl = test_load_annotations(dtTypeFrom, fileNameFrom);
	if (pAnnotationColl)
	{
		test_save_annotation(pAnnotationColl, dtTypeTo, fileNameTo.empty() ? (dtTypeTo == DT_DICOM ? DICOM_DOC_NAME2 : XML_DOC_NAME2) : fileNameTo);
	}

	delete pAnnotationColl;
	pAnnotationColl = NULL;
}

static int test_create_annotations(int annCount, AnnotationEntity::AnnotationType atAnnotationKind, TestDocumentType dtType)
{
	if (annCount < 1)
		return -1;

	AnnotationEntity* pAnnotation = NULL;
	AnnotationCollection* pAnnotationColl = NULL;

	switch(atAnnotationKind)
	{
	case AnnotationEntity::AT_ImageAnnotation:
		{
			ImageAnnotation* pImgAnnotation = create_image_annotation();
			assert(pImgAnnotation);
			ImageAnnotationCollection* pImgAnnColl = create_image_annotation_collection(false);
			assert(pImgAnnColl);
			pAnnotation = pImgAnnotation;
			pAnnotationColl = pImgAnnColl;
			ImageAnnotationVector imgAnnotations;
			for (int i=0; i < annCount; i++)
				imgAnnotations.push_back(*pImgAnnotation);
			pImgAnnColl->SetImageAnnotations(imgAnnotations);
		}
		break;
	case AnnotationEntity::AT_AnnotationOfAnnotation:
		{
			AnnotationOfAnnotation* pAnnOfAnnotation = create_annotation_of_annotation();
			assert(pAnnOfAnnotation);
			AnnotationOfAnnotationCollection* pAnnOfAnnColl = create_annotation_of_annotation_collection(false);
			assert(pAnnOfAnnotation);
			pAnnotation = pAnnOfAnnotation;
			pAnnotationColl = pAnnOfAnnColl;
			AnnotationOfAnnotationVector annOfAnnotations;
			for (int i=0; i < annCount; i++)
				annOfAnnotations.push_back(*pAnnOfAnnotation);
			pAnnOfAnnColl->SetAnnotationOfAnnotations(annOfAnnotations);
		}
		break;
	default:
		{
			assert(false);
			return -1;
		}
	}

	string outXml;
	ofstream myfile;

	if (dtType == DT_DICOM || dtType == DT_ALL)
	{
		DcmModel dcmModel;
		dcmModel.WriteAnnotationCollectionToFile(pAnnotationColl, DICOM_DOC_NAME);

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
				//xmlSize = xmlModel.WriteAnnotationCollectionToFile(pAnnotationColl, pXml, xmlSize);
				xmlSize = xmlModel.WriteAnnotationCollectionToXmlString(pAnnotationColl, pXml, xmlSize);
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
	delete pAnnotationColl;
	pAnnotationColl = NULL;

	return 0;
}

/*
 Reads annotations from file
*/
static AnnotationCollection* test_load_annotations(TestDocumentType dtType, const std::string& fileName)
{
	AnnotationCollection* pAnnotationColl;
	if (DT_DICOM == dtType)
	{
		DcmModel dcmModel;
		pAnnotationColl = dcmModel.ReadAnnotationCollectionFromFile(fileName.empty() ? DICOM_DOC_NAME : fileName);
	}
	else if (DT_XML == dtType)
	{
		XmlModel xmlModel;
		pAnnotationColl = xmlModel.ReadAnnotationCollectionFromFile(fileName.empty() ? XML_DOC_NAME : fileName);
	}

	//delete pAnnotationColl;
	//pAnnotationColl = NULL;

	return pAnnotationColl;
}

// Save Annotation
static void test_save_annotation(const AnnotationCollection* pAnnotationColl, TestDocumentType dtType, const std::string& outFileName)
{
	if (dtType == DT_DICOM || dtType == DT_ALL)
	{
		DcmModel dcmModel("1.999.9.9.9");
		dcmModel.WriteAnnotationCollectionToFile(pAnnotationColl, outFileName.empty() ? DICOM_DOC_NAME : outFileName);
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
				xmlSize = pXmlModel->WriteAnnotationCollectionToXmlString(pAnnotationColl, pXml, xmlSize);
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
	Creates test Image Annotation Collection object
	NOTE: After using the object, it needs to be deallocated.
*/

static ImageAnnotationCollection* create_image_annotation_collection(bool hasImageAnnotation /*= true*/)
{
	ImageAnnotationCollection* pImgAnnColl = new ImageAnnotationCollection();
	::populateAnnotationCollection(pImgAnnColl);

	// Person
	Person person;
	person.SetName("Test^Person");
	person.SetId("PID123");
	person.SetBirthDate(Date(1950, 1, 1));
	person.SetSex("O");
	person.SetEthnicGroup("Other");
	pImgAnnColl->SetPerson(&person);

	if (hasImageAnnotation)
	{
		ImageAnnotation* pImgAnn = create_image_annotation();
		if (pImgAnn)
		{
			ImageAnnotationVector imgAnnotations;
			imgAnnotations.push_back(*pImgAnn);
			pImgAnnColl->SetImageAnnotations(imgAnnotations);
			imgAnnotations.clear();
			delete pImgAnn;
			pImgAnn = NULL;
		}
	}

	return pImgAnnColl;
}

static AnnotationOfAnnotationCollection* create_annotation_of_annotation_collection(bool hasAnnotationOfAnnotation /*= true*/)
{
	AnnotationOfAnnotationCollection* pAnnOfAnnColl = new AnnotationOfAnnotationCollection();
	::populateAnnotationCollection(pAnnOfAnnColl);

	if (hasAnnotationOfAnnotation)
	{
		AnnotationOfAnnotation* pAnnOfAnn = create_annotation_of_annotation();
		if (pAnnOfAnn)
		{
			AnnotationOfAnnotationVector annOfAnnotations;
			annOfAnnotations.push_back(*pAnnOfAnn);
			pAnnOfAnnColl->SetAnnotationOfAnnotations(annOfAnnotations);
			annOfAnnotations.clear();
			delete pAnnOfAnn;
			pAnnOfAnn = NULL;
		}
	}

	return pAnnOfAnnColl;
}

static void populateAnnotationCollection(AnnotationCollection* pAnnColl)
{
	if (!pAnnColl)
		return;

	pAnnColl->SetUniqueIdentifier(II::generate());
	pAnnColl->SetDescription("Collection Description");
	pAnnColl->SetDateTime(DateTime::Now());

	// User
	User user;
	user.SetName("FName-Test^LName-User");
	user.SetLoginName("TUser");
	user.SetRoleInTrial("Recording");
	user.SetNumberWithinRoleOfClinicalTrial(11);
	pAnnColl->SetUser(&user);

	// Equipment
	Equipment equipment;
	equipment.SetManufacturerName("NWU");
	equipment.SetManufacturerModelName("AIM_4.0");
	equipment.SetSoftwareVersion("4.0alpha");
	equipment.SetDeviceSerialNumber("ser_num_123");
	pAnnColl->SetEquipment(&equipment);
}

static void populateAnnotationEntity(AnnotationEntity* pAnnEnt)
{
	if (!pAnnEnt)
		return;

	II uid;
	CD code;
	CDVector cdVector;
	string str;
	bool flag;
	double dValue;
	DateTime ct = DateTime::Now();
	int questionIndex = 0;

	// Set Annotation Entity data
	pAnnEnt->SetDateTime(ct);
//	string str = "AIM.4.0R0";
//	pAnnEnt->SetAimVersion(str);
	pAnnEnt->SetComment(str = "Annotation comments of arbitrary length");
	pAnnEnt->SetName(str = "My Annotation Name");
	uid = AimUidGenerator::GenerateNewUid("1.2.3.4.5.6");
	pAnnEnt->SetUniqueIdentifier(uid);
	uid = AimUidGenerator::GenerateNewUid("1.2.3");
	pAnnEnt->SetTemplateUid(&uid);
	cdVector.clear();
	cdVector.push_back(code = CD("RECIST-123", "Baseline_Non-target_Lesion", "VKL", "XXX"));
	pAnnEnt->SetTypeCode(cdVector);
	uid = II("1.444.555.666.777");
	pAnnEnt->SetPrecedentReferencedAnnotationUid(&uid);

	// TaskContextEntity
	TaskContextEntity taskContextEntity;
	//taskContextEntity.SetUniqueIdentifier(uid = II::generate());
	taskContextEntity.SetWorklistTaskUid(uid = II::generate());
	taskContextEntity.SetWorklistTaskName(str = "Task uno");
	taskContextEntity.SetWorklistTaskDescription(str = "Task uno descr");
	taskContextEntity.SetWorklistTaskCategory(code = CD("tsk1", "Task Category One", "VKL"));
	taskContextEntity.SetWorklistTaskLevel(code = CD("tsklvl1", "Task Level One", "VKL"));
	taskContextEntity.SetWorklistTaskType(code = CD("tsktype1", "Task Type One", "VKL"));
	taskContextEntity.SetWorklistTaskRepeatType(&(code = CD("tskrpttype1", "Task One Repeate Type", "VKL")));
	taskContextEntity.SetWorklistTaskVariabilityType(&(code = CD("tskvartype1", "Task One Variability Type", "VKL")));
	taskContextEntity.SetWorklistTaskVersion(str = "TaskOneVer");
	taskContextEntity.SetWorklistSubtaskUid(uid = II::generate());
	taskContextEntity.SetWorklistSubtaskName(str = "Subtask uno");
	taskContextEntity.SetWorklistSubtaskStartDateTime(ct);
	taskContextEntity.SetWorklistSubtaskClosedDateTime(ct);
	TaskContextEntityVector taskContexts;
	taskContexts.push_back(taskContextEntity);
	taskContextEntity.SetTaskContextEntityCollection(taskContexts);
	pAnnEnt->SetTaskContextEntityCollection(taskContexts);

	// AnnotationRoleEntity
	AnnotationRoleEntity annRoleEntity;
	cdVector.clear();
	cdVector.push_back(code = CD("roleQt1", "Role Question Type One", "VKL"));
	annRoleEntity.SetQuestionTypeCode(cdVector);
	annRoleEntity.SetRoleCode(code = CD("role1", "Role One", "VKL"));
	annRoleEntity.SetRoleSequenceNumber(17);
	AnnotationRoleEntityVector roles;
	roles.push_back(annRoleEntity);
	pAnnEnt->SetAnnotationRoleEntityCollection(roles);

	// InferenceEntity
	InferenceEntity inferenceEntity;
	cdVector.clear();
	cdVector.push_back(code = CD("inferenceType1", "Inference Type One", "VKL"));
	inferenceEntity.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("inferenceQt1", "Inference Question Type One", "VKL"));
	inferenceEntity.SetQuestionTypeCode(cdVector);
	inferenceEntity.SetImageEvidence(false);
	inferenceEntity.SetIsPresent(&(flag = false));
	inferenceEntity.SetAnnotatorConfidence(&(dValue = 0.33));
	inferenceEntity.SetDescription(str = "Inference Descr");
	inferenceEntity.SetLabel(str = "Inference Label");
	inferenceEntity.SetQuestionIndex(questionIndex++);
	InferenceEntityVector inferences;
	inferences.push_back(inferenceEntity);
	pAnnEnt->SetInferenceEntityCollection(inferences);

	// AuditTrail
	AuditTrail auditTrail;
	auditTrail.SetStatusCode(code = CD("auditstatus1", "Audit Status One", "VKL"));
	auditTrail.SetDateTime(ct);
	auditTrail.SetChangeReason(code = CD("reason1", "Change Reason One", "VKL"));
	auditTrail.SetWorklistSubtaskUid(&(uid = II::generate()));
	auditTrail.SetComment(str = "Audit Trail comment");
	AuditTrailVector auditTrails;
	auditTrails.push_back(auditTrail);
	pAnnEnt->SetAuditTrailCollection(auditTrails);

	// LesionObservation
	// GeneralLesionObservationEntity
	GeneralLesionObservationEntity genLesionObsEntity;
	genLesionObsEntity.SetLesionUniqueIdentifier(uid = II::generate());
	genLesionObsEntity.SetIsAdditionalObservation(&(flag = false));
	genLesionObsEntity.SetLesionType(code = CD("lesionType1", "Lesion Type One", "VKL"));
	genLesionObsEntity.SetTrackingIdentifier(str = "lesionOne");
	genLesionObsEntity.SetLaterality(&(code = CD("laterality1", "Laterality One", "VKL")));
	genLesionObsEntity.SetReconstructionInterval(&(code = CD("recoInterval1", "Reco Interval One", "VKL")));
	LesionObservationEntityPtrVector lesionObservations;
	lesionObservations.push_back(&genLesionObsEntity);
	// TimePointLesionObservationEntity
	TimePointLesionObservationEntity timepointLesionObsEntity;
	timepointLesionObsEntity.SetLesionUniqueIdentifier(uid = II::generate());
	timepointLesionObsEntity.SetIsAdditionalObservation(&(flag = false));
	timepointLesionObsEntity.SetCalibration(flag = false);
	timepointLesionObsEntity.SetCanEvaluateLesion(&(flag = true));
	timepointLesionObsEntity.SetCanMeasureLesion(&(flag = true));
	timepointLesionObsEntity.SetComment(str = "TimePoint Lesion Observation Comment");
	timepointLesionObsEntity.SetIsUnequivocalProgression(&(flag = false));
	timepointLesionObsEntity.SetPredecessorLesionTrackingUid(&(uid = II::generate()));
	timepointLesionObsEntity.SetQualitativeAssessment(&(code = CD("qualAssess1", "Qualitative Assessment One", "VKL")));
	timepointLesionObsEntity.SetReasonUnableToEvaluate(&(code = CD("unableToEval1", "Unable To Eval One", "VKL")));
	timepointLesionObsEntity.SetReasonUnableToMeasure(&(code = CD("unableToMeasure1", "Unable To Measure One", "VKL")));
	timepointLesionObsEntity.SetTherapeuticResponse(&(code = CD("theraResp1", "Thera Response One", "VKL")));
	lesionObservations.push_back(&timepointLesionObsEntity);
	pAnnEnt->SetLesionOservationEntityCollection(lesionObservations);
	lesionObservations.clear();
	
	// CharacteristicQuantifications
	CharacteristicQuantificationPtrVector characteristicQuantifications;
	// Quantile
	Quantile quantile;
	quantile.SetBins(4);
	quantile.SetSelectedBin(2);
	quantile.SetLabel(str = "Quantile 2");
	quantile.SetCharacteristicQuantificationIndex(1);
	quantile.SetMinValue(dValue = 5.25);
	quantile.SetMaxValue(dValue = 123.987);
	quantile.SetAnnotatorConfidence(&(dValue = .378));
	quantile.SetValueLabel(str = "Quantile Value Label");
	quantile.SetValueDescription(str = "Quantile Value Description");
	quantile.SetComment(str = "Quantile Comment");
	characteristicQuantifications.push_back(&quantile);
	// Numerical
	Numerical numerical;
	numerical.SetValue(dValue = 765.902);
	numerical.SetUcumString(str = "mm");
	numerical.SetLabel(str = "Numerical Char Quantification");
	numerical.SetAnnotatorConfidence(&(dValue = .456));
	numerical.SetOperator(NotEqual);
	numerical.SetCharacteristicQuantificationIndex(2);
	numerical.SetValueLabel(str = "Numerical Value Label");
	numerical.SetValueDescription(str = "Numerical Value Description");
	numerical.SetComment(str = "Numerical Comment");
	characteristicQuantifications.push_back(&numerical);
	// Scale
	Scale scale;
	scale.SetScaleType(Scale::Ordinal);
	scale.SetValue(str = "Scale Value"); // TODO - validate scale value data type
	scale.SetLabel(str = "Scale Char Quantification");
	scale.SetAnnotatorConfidence(&(dValue = .469));
	scale.SetCharacteristicQuantificationIndex(3);
	scale.SetValueLabel(str = "Scale Value Label");
	scale.SetValueDescription(str = "Scale Value Description");
	scale.SetComment(str = "Scale Comment");
	characteristicQuantifications.push_back(&scale);
	// NonQuantifiable
	NonQuantifiable nonQuantifiable;
	nonQuantifiable.SetTypeCode(code = CD("nonQunat1", "NonQuantifiable Type One", "VKL"));
	nonQuantifiable.SetLabel(str = "NonQuantifiable Char Quantification");
	nonQuantifiable.SetAnnotatorConfidence(&(dValue = .567));
	nonQuantifiable.SetCharacteristicQuantificationIndex(4);
	nonQuantifiable.SetValueLabel(str = "NonQuantifiable Char Value Label");
	nonQuantifiable.SetValueDescription(str = "NonQuantifiable Char Value Description");
	nonQuantifiable.SetComment(str = "NonQuantifiable Char Comment");
	characteristicQuantifications.push_back(&nonQuantifiable);
	//Interval
	Interval interval;
	interval.SetLabel(str = "Interval 2");
	interval.SetMinValue(dValue = 3.25);
	interval.SetMinOperator(GreaterThanEqual);
	interval.SetMaxValue(dValue = 129.987);
	interval.SetMaxOperator(LessThan);
	interval.SetUcumString(str = "cm2");
	interval.SetAnnotatorConfidence(&(dValue = .366));
	interval.SetCharacteristicQuantificationIndex(5);
	interval.SetValueLabel(str = "Interval Value Label");
	interval.SetValueDescription(str = "Interval Value Description");
	interval.SetComment(str = "Interval Comment");
	characteristicQuantifications.push_back(&interval);

	// ImagingObservationEntity
	ImagingObservationEntity imgObsEntity;
	cdVector.clear();
	cdVector.push_back(code = CD("imgObsEntType1", "Imaging Obs Entity Type One", "VKL"));
	imgObsEntity.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("imgObsEntQt1", "Imaging Obs Ent Question Type One", "VKL"));
	imgObsEntity.SetQuestionTypeCode(cdVector);
	imgObsEntity.SetAnnotatorConfidence(&(dValue = .37));
	imgObsEntity.SetLabel(str = "Imgaging Observation Entity Label One");
	imgObsEntity.SetComment(str = "Imaging Observation Entity Comment One");
	imgObsEntity.SetIsPresent(&(flag = true));
	imgObsEntity.SetQuestionIndex(questionIndex++);
	// ImagingObservationCharacteristic
	ImagingObservationCharacteristic imgObsChar;
	cdVector.clear();
	cdVector.push_back(code = CD("imgObsCharType1", "Imaging Obs Char Type One", "VKL"));
	imgObsChar.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("imgObsCharQt1", "Imaging Obs Char Question Type One", "VKL"));
	imgObsChar.SetQuestionTypeCode(cdVector);
	imgObsChar.SetAnnotatorConfidence(&(dValue = .38));
	imgObsChar.SetLabel(str = "Imgaging Observation Char Label One");
	imgObsChar.SetComment(str = "Imaging Observation Char Comment One");
	imgObsChar.SetQuestionIndex(questionIndex++);
	imgObsChar.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	//
	ImagingObservationCharacteristicVector imagingObservationChars;
	imagingObservationChars.push_back(imgObsChar);
	imgObsEntity.SetImagingObservationCharacteristicCollection(imagingObservationChars);
	ImagingObservationEntityVector imagingObservationEntities;
	imagingObservationEntities.push_back(imgObsEntity);
	pAnnEnt->SetImagingObservationEntityCollection(imagingObservationEntities);

	// ImagingPhysicalEntity
	ImagingPhysicalEntity imgPhysEntity;
	cdVector.clear();
	cdVector.push_back(code = CD("imgPhysEntType1", "Imaging Phys Entity Type One", "VKL"));
	imgPhysEntity.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("imgPhysEntQt1", "Imaging Phys Ent Question Type One", "VKL"));
	imgPhysEntity.SetQuestionTypeCode(cdVector);
	imgPhysEntity.SetAnnotatorConfidence(&(dValue = .27));
	imgPhysEntity.SetLabel(str = "Imgaging Phys Entity Label One");
	imgPhysEntity.SetIsPresent(&(flag = true));
	imgPhysEntity.SetQuestionIndex(questionIndex++);
	// ImagingPhysicalEntityCharacterisitc
	ImagingPhysicalEntityCharacteristic imgPhysEntChar;
	cdVector.clear();
	cdVector.push_back(code = CD("imgPhysEntCharType1", "Imaging Phys Ent Char Type One", "VKL"));
	imgPhysEntChar.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("imgPhysEntCharQt1", "Imaging Phys Ent Char Question Type One", "VKL"));
	imgPhysEntChar.SetQuestionTypeCode(cdVector);
	imgPhysEntChar.SetAnnotatorConfidence(&(dValue = .435));
	imgPhysEntChar.SetLabel(str = "Imgaging Physical Entity Char Label One");
	imgPhysEntChar.SetQuestionIndex(questionIndex++);
	imgPhysEntChar.SetCharacteristicQuantificationCollection(characteristicQuantifications);
	//
	ImagingPhysicalEntityCharacteristicVector imgPhysEntityChars;
	imgPhysEntityChars.push_back(imgPhysEntChar);
	imgPhysEntity.SetImagingPhysicalEntityCharacteristicCollection(imgPhysEntityChars);
	imgPhysEntity.SetImagingObservationCharacteristicCollection(imagingObservationChars);
	ImagingPhysicalEntityVector imagingPhysicalEntities;
	imagingPhysicalEntities.push_back(imgPhysEntity);
	pAnnEnt->SetImagingPhysicalEntityCollection(imagingPhysicalEntities);

	// Parameter
	Parameter param;
	param.SetName(str = "Param One");
	param.SetValue(str = "Value One");
	param.SetDataType(code = CD("ParamType1", "Param Data Type One", "VKL"));
	ParameterVector params;
	params.push_back(param);
	// Algorithm
	Algorithm algorithm;
	cdVector.clear();
	cdVector.push_back(code = CD("AlgoType1", "Algorithm Type One", "VKL"));
	algorithm.SetType(cdVector);
	algorithm.SetName(str = "Algorithm Name One");
	algorithm.SetUniqueIdentifier(&(uid = II::generate()));
	algorithm.SetVersion(str = "Algorithm Version One");
	algorithm.SetDescription(str = "Algorithm Description");
	algorithm.SetParameterCollection(params);
	// CalculationEntity
	CalculationEntity calcEntity;
	cdVector.clear();
	cdVector.push_back(code = CD("calcType1", "Calculation Type One", "VKL"));
	calcEntity.SetTypeCode(cdVector);
	cdVector.clear();
	cdVector.push_back(code = CD("calcQt1", "Calculation Question Type One", "VKL"));
	calcEntity.SetQuestionTypeCode(cdVector);
	calcEntity.SetDescription(str = "Calculation Descr. One");
	calcEntity.SetMathML(str = "<math><ml/></math>");
	calcEntity.SetQuestionIndex(questionIndex++);
	calcEntity.SetAlgorithm(&algorithm);
	// Dimension
	Dimension dimension;
	dimension.SetIndex(1);
	dimension.SetLabel(str = "Dimension One");
	dimension.SetSize(3);
	DimensionVector dimensions;
	dimensions.push_back(dimension);
	// CompactCalculationResult
	CompactCalculationResult compactCalcResult;
	compactCalcResult.SetType(CalculationResult::Array);
	compactCalcResult.SetUnitOfMeasure(str = "m");
	compactCalcResult.SetDataType(code = CD("calcDT1", "Calculation Data Type One", "VKL"));
	compactCalcResult.SetValue(str = "1.2,3.4,555");
	compactCalcResult.SetEncoding(&(code = CD("calcEnc1", "Calculation Encoding One", "VKL")));
	compactCalcResult.SetCompression(&(code = CD("calcComp1", "Calculation Compression One", "VKL")));
	compactCalcResult.SetDimensionCollection(dimensions);
	// Coordinate
	Coordinate coord;
	coord.SetDimensionIndex(1);
	coord.SetPosition(2);
	CoordinateVector coords;
	coords.push_back(coord);
	// CalculationData
	CalculationData calcData;
	calcData.SetValue(str = "2.1415926");
	calcData.SetCoordinateCollection(coords);
	CalculationDataVector calcDataColl;
	calcDataColl.push_back(calcData);
	// ExtendedCalculationResult
	ExtendedCalculationResult extCalcResult;
	extCalcResult.SetType(CalculationResult::Array);
	extCalcResult.SetUnitOfMeasure(str = "m");
	extCalcResult.SetDataType(code = CD("calcDT1", "Calculation Data Type One", "VKL"));
	extCalcResult.SetCalculationDataCollection(calcDataColl);
	extCalcResult.SetDimensionCollection(dimensions);
	//
	CalculationResultPtrVector calcResults;
	calcResults.push_back(&compactCalcResult);
	calcResults.push_back(&extCalcResult);
	calcEntity.SetCalculationResultCollection(calcResults);
	calcResults.clear();
	CalculationEntityVector calculationEntities;
	calculationEntities.push_back(calcEntity);
	pAnnEnt->SetCalculationEntityCollection(calculationEntities);
}

static void populateGeometricShapeEntity(GeometricShapeEntity* pGeoShapeEntity, int shapeIdx)
{
	if (!pGeoShapeEntity)
		return;

	std::string str;
	CD code;
	CDVector cdVector;
	cdVector.push_back(CD("geoShapeQt1", "GeoShape Question Type One", "VKL"));
	pGeoShapeEntity->SetQuestionTypeCode(cdVector);
	pGeoShapeEntity->SetShapeIdentifier(500 + shapeIdx);
	pGeoShapeEntity->SetLabel("GeoShape Label " + shapeIdx);
	pGeoShapeEntity->SetDescription(str = "GeoShape Descr " + shapeIdx);
	pGeoShapeEntity->SetIncludeFlag(true);
	pGeoShapeEntity->SetComment("GeoShape Comment " + shapeIdx);
	pGeoShapeEntity->SetLineColor(str = "GeoShapeLineColor" + shapeIdx);
	pGeoShapeEntity->SetLineOpacity(str = "GeoShapeLineOpacity" + shapeIdx);
	pGeoShapeEntity->SetLineStyle(str = "GeoShapeLineStyle" + shapeIdx);
	pGeoShapeEntity->SetLineThickness(str = "GeoShapeLineThickness" + shapeIdx);
	pGeoShapeEntity->SetQuestionIndex(100 + shapeIdx);
	pGeoShapeEntity->SetInterpolationMethod(&(code = CD("interMethod1", "Interpolation Method One", "VKL")));
}

/*
	Creates test Image Annotation object. 
	NOTE: After using the object, it needs to be deallocated.
*/
static ImageAnnotation* create_image_annotation()
{
	ImageAnnotation* pAnnotation = new ImageAnnotation();

	// Populate AnnotationEnity common data
	::populateAnnotationEntity(pAnnotation);

	// Populate Image Annotation-specific data
	double dValue;
	std::string str;
	CD code;
	II uid;

	// ImagePlane
	ImagePlane imgPlane;
	imgPlane.SetRowImageOrientationX(&(dValue = 1.0));
	imgPlane.SetRowImageOrientationY(&(dValue = 2.0));
	imgPlane.SetRowImageOrientationZ(&(dValue = 3.0));
	imgPlane.SetColumnImageOrientationX(&(dValue = 4.0));
	imgPlane.SetColumnImageOrientationY(&(dValue = 5.0));
	imgPlane.SetColumnImageOrientationZ(&(dValue = 6.0));
	imgPlane.SetVerticalPixelSpacing(&(dValue = 7.0));
	imgPlane.SetHorizontalPixelSpacing(&(dValue = 8.0));
	imgPlane.SetSliceThickness(&(dValue = 9.0));
	imgPlane.SetImagePositionX(&(dValue = 10.0));
	imgPlane.SetImagePositionY(&(dValue = 11.0));
	imgPlane.SetImagePositionZ(&(dValue = 12.0));
	// GeneralImage
	GeneralImage genImage;
	genImage.SetPatientOrientationColumn(str = "2.0");
	genImage.SetPatientOrientationRow(str = "4.0");
	// Image
	Image image;
	image.SetSopClassUid(uid = II(str = "1.2.3.8888888"));
	image.SetSopInstanceUid(uid = II(str = "1.2.333.6666666666666.9"));
	image.SetGeneralImage(&genImage);
	image.SetImagePlane(&imgPlane);
	ImageVector images;
	images.push_back(image);
	// ImageSeries
	ImageSeries imageSeries;
	imageSeries.SetInstanceUid(uid = II(str = "1.2.98765543"));
	imageSeries.SetModality(code = CD("OM", "Other Modality", "VKL"));
	imageSeries.SetImageCollection(images);
	// ReferencedDicomObject
	ReferencedDicomObject refDicomObj;
	refDicomObj.SetModality(code = CD("OM", "Other Modality", "VKL"));
	refDicomObj.SetSopInstanceUid(uid = II("1.2.8348347643"));
	ReferencedDicomObjectVector refDicomObjects;
	refDicomObjects.push_back(refDicomObj);
	// ImageStudy
	ImageStudy imageStudy;
	imageStudy.SetInstanceUid(uid = II("1.2.4567887654")); // Study Instance UID
	imageStudy.SetStartDate(Date::Today());
	imageStudy.SetStartTime(Time::Now());
	imageStudy.SetProcedureDescription(str = "Test Procedure");
	imageStudy.SetImageSeries(imageSeries);
	imageStudy.SetReferencedDicomObjectCollection(refDicomObjects);
	// DicomImageReferenceEntity
	DicomImageReferenceEntity dicomImageRefEntity;
	dicomImageRefEntity.SetImageStudy(imageStudy);
	// UriImageReferenceEntity
	UriImageReferenceEntity uriImageRefEntity;
	uriImageRefEntity.SetUri(str = "test::uri-schema");
	uriImageRefEntity.SetMimeType(str = "image/png");
	// ImageReferenceEntity
	ImageReferenceEntityPtrVector imageRefEntities;
	imageRefEntities.push_back(&dicomImageRefEntity);
	imageRefEntities.push_back(&uriImageRefEntity);
	pAnnotation->SetImageReferenceEntityCollection(imageRefEntities);

	// DicomSegmentationEntity
	DicomSegmentationEntity dicomSegEntity;
	dicomSegEntity.SetSopInstanceUid(uid = II(str = "1.2.840.10008.5.1.4.1.1.1.999999999.3")); // Segmentation's SOP Instance UID
	dicomSegEntity.SetSopClassUid(uid = II(str = "1.2.840.10008.5.1.4.1.1.66.4")); // Segmentation Storage SOP Class UID 
	dicomSegEntity.SetReferencedSopInstanceUid(uid = image.GetSopInstanceUid()); // Image SOP Instance UID
	dicomSegEntity.SetSegmentNumber(1);
	SegmentationEntityPtrVector segmentationEntities;
	segmentationEntities.push_back(&dicomSegEntity);
	pAnnotation->SetSegmentationEntityCollection(segmentationEntities);
	segmentationEntities.clear();

	// GeometricShapeEntity
	int shapeIdx = 0;
	// TwoDimensionSpatialCoordinate
	TwoDimensionSpatialCoordinateVector twoDcoords;
	TwoDimensionSpatialCoordinate coord2d;
	// TwoDimensionPoint
	TwoDimensionPoint point2D;
	::populateGeometricShapeEntity(&point2D, shapeIdx++);
	point2D.SetCenter(coord2d = TwoDimensionSpatialCoordinate(20.0, 40.0, 0));
	point2D.SetImageReferenceUid(&(uid = image.GetSopInstanceUid()));
	point2D.SetReferencedFrameNumber(1);
	// TwoDimensionCircle
	TwoDimensionCircle circle2D;
	::populateGeometricShapeEntity(&circle2D, shapeIdx++);
	circle2D.SetCenter(coord2d = TwoDimensionSpatialCoordinate(20.0, 40.0, 0));
	circle2D.SetRadiusPoint(coord2d = TwoDimensionSpatialCoordinate(10.0, 15.0, 1));
	circle2D.SetUri(str = uriImageRefEntity.GetUri());
	// TwoDimensionEllipse
	TwoDimensionEllipse ellipse2D;
	::populateGeometricShapeEntity(&ellipse2D, shapeIdx);
	ellipse2D.SetImageReferenceUid(&(uid = image.GetSopInstanceUid()));
	ellipse2D.SetReferencedFrameNumber(1);
	twoDcoords.clear();
	twoDcoords.push_back(coord2d = TwoDimensionSpatialCoordinate(20.0, 40.0, 0));
	twoDcoords.push_back(coord2d = TwoDimensionSpatialCoordinate(30.0, 50.0, 1));
	twoDcoords.push_back(coord2d = TwoDimensionSpatialCoordinate(45.0, 25.0, 2));
	twoDcoords.push_back(coord2d = TwoDimensionSpatialCoordinate(55.0, 35.0, 3));
	ellipse2D.SetEllipseCollection(twoDcoords);
	// TwoDimensionPolyline
	TwoDimensionPolyline polyline2D;
	::populateGeometricShapeEntity(&polyline2D, shapeIdx++);
	polyline2D.SetImageReferenceUid(&(uid = image.GetSopInstanceUid()));
	polyline2D.SetReferencedFrameNumber(1);
	polyline2D.SetTwoDimensionSpatialCoordinateCollection(twoDcoords);
	// TwoDimensionMultiPoint
	TwoDimensionMultiPoint multipoint2D;
	::populateGeometricShapeEntity(&multipoint2D, shapeIdx++);
	multipoint2D.SetImageReferenceUid(&(uid = image.GetSopInstanceUid()));
	multipoint2D.SetReferencedFrameNumber(1);
	multipoint2D.SetTwoDimensionSpatialCoordinateCollection(twoDcoords);

	// ThreeDimensionSpatialCoordinate
	ThreeDimensionSpatialCoordinateVector threeDcoords;
	ThreeDimensionSpatialCoordinate coord3d;
	// ThreeDimensionPoint
	ThreeDimensionPoint point3D;
	::populateGeometricShapeEntity(&point3D, shapeIdx++);
	point3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	point3D.SetFiducialUid(&(uid = II::generate()));
	point3D.SetCenter(coord3d = ThreeDimensionSpatialCoordinate(10.0, 10.0, 10.0, 0));
	// ThreeDimensionEllipse
	ThreeDimensionEllipse ellipse3D;
	::populateGeometricShapeEntity(&ellipse3D, shapeIdx++);
	ellipse3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	ellipse3D.SetFiducialUid(&(uid = II::generate()));
	threeDcoords.clear();
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(-10.0, -10.0, -10.0, 0));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(10.0, 10.0, 10.0, 1));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(-20.0, -20.0, -20.0, 2));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(20.0, 20.0, 20.0, 3));
	ellipse3D.SetEllipseCollection(threeDcoords);
	// ThreeDimensionEllipsoid
	ThreeDimensionEllipsoid ellipsoid3D;
	::populateGeometricShapeEntity(&ellipsoid3D, shapeIdx++);
	ellipsoid3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	ellipsoid3D.SetFiducialUid(&(uid = II::generate()));
	threeDcoords.clear();
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(-10.0, -10.0, -10.0, 0));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(10.0, 10.0, 10.0, 1));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(-20.0, -20.0, -20.0, 2));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(20.0, 20.0, 20.0, 3));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(-30.0, -30.0, -30.0, 4));
	threeDcoords.push_back(coord3d = ThreeDimensionSpatialCoordinate(30.0, 30.0, 30.0, 5));
	ellipsoid3D.SetEllipsoidCollection(threeDcoords);
	// ThreeDimensionPolygon
	ThreeDimensionPolygon polygon3D;
	::populateGeometricShapeEntity(&polygon3D, shapeIdx++);
	polygon3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	polygon3D.SetFiducialUid(&(uid = II::generate()));
	polygon3D.SetThreeDimensionSpatialCoordinateCollection(threeDcoords);
	// ThreeDimensionPolyline
	ThreeDimensionPolyline polyline3D;
	::populateGeometricShapeEntity(&polyline3D, shapeIdx++);
	polyline3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	polyline3D.SetFiducialUid(&(uid = II::generate()));
	polyline3D.SetThreeDimensionSpatialCoordinateCollection(threeDcoords);
	// ThreeDimensionMultiPoint
	ThreeDimensionMultiPoint multipoint3D;
	::populateGeometricShapeEntity(&multipoint3D, shapeIdx++);
	multipoint3D.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	multipoint3D.SetFiducialUid(&(uid = II::generate()));
	multipoint3D.SetThreeDimensionSpatialCoordinateCollection(threeDcoords);

	// TextAnnotationEntity
	TextAnnotationEntity textAnnEntity;
	textAnnEntity.SetText(str = "Test Annotation Text");
	textAnnEntity.SetFont(str = "TestFont");
	textAnnEntity.SetFontColor(str = "TestFontColor");
	textAnnEntity.SetFontEffect(str = "TestFontEffect");
	textAnnEntity.SetFontSize(str = "TestFontSize");
	textAnnEntity.SetFontStyle(str = "TestFontStyle");
	textAnnEntity.SetFontOpacity(str = "TestFontOpacity");
	textAnnEntity.SetTextJustify(str = "TestTextJustify");
	// TwoDimensionMultiPoint
	TwoDimensionMultiPoint multipoint2DtextAnn;
	::populateGeometricShapeEntity(&multipoint2DtextAnn, shapeIdx++);
	multipoint2DtextAnn.SetImageReferenceUid(&(uid = image.GetSopInstanceUid()));
	multipoint2DtextAnn.SetReferencedFrameNumber(1);
	if (twoDcoords.size() > 2)
		twoDcoords.resize(2);
	multipoint2DtextAnn.SetTwoDimensionSpatialCoordinateCollection(twoDcoords);
	// ThreeDimensionMultiPoint
	ThreeDimensionMultiPoint multipoint3DtextAnn;
	::populateGeometricShapeEntity(&multipoint3DtextAnn, shapeIdx++);
	multipoint3DtextAnn.SetFrameOfReferenceUid(&(uid = dicomSegEntity.GetSopInstanceUid()));
	multipoint3DtextAnn.SetFiducialUid(&(uid = II::generate()));
	if (threeDcoords.size() > 2)
		threeDcoords.resize(2);
	multipoint3DtextAnn.SetThreeDimensionSpatialCoordinateCollection(threeDcoords);
	textAnnEntity.SetGeometricShapeEntity(&multipoint2DtextAnn);

	// MarkupEntity
	MarkupEntityPtrVector markupEntities;
	markupEntities.push_back(&point2D);
	markupEntities.push_back(&circle2D);
	markupEntities.push_back(&ellipse2D);
	markupEntities.push_back(&polyline2D);
	markupEntities.push_back(&multipoint2D);
	// SCOORD3D tests (need DCMTK support)
	markupEntities.push_back(&point3D);
	markupEntities.push_back(&ellipse3D);
	markupEntities.push_back(&ellipsoid3D);
	markupEntities.push_back(&polygon3D);
	markupEntities.push_back(&polyline3D);
	markupEntities.push_back(&multipoint3D);
	markupEntities.push_back(&textAnnEntity);
	pAnnotation->SetMarkupEntityCollection(markupEntities);
	markupEntities.clear();


	//////////////////////////////////////////////////////////////////////////////
	// Image Annotation Statements
	//////////////////////////////////////////////////////////////////////////////
	ImageAnnotationStatementPtrVector imgAnnStatements;

	// Annotation Statements
	::populateAnnotationStatments(pAnnotation, imgAnnStatements);

	DicomImageReferenceEntityHasCalculationEntityStatement dcmImgRefEntHasCalcEntStmt(dicomImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(dcmImgRefEntHasCalcEntStmt.Clone());
	DicomImageReferenceEntityHasImagingObservationEntityStatement dcmImgRefEntHasImgObsEntStmt(dicomImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(dcmImgRefEntHasImgObsEntStmt.Clone());
	DicomImageReferenceEntityHasImagingPhysicalEntityStatement dcmImgRefEntHasImgPhysEntStmt(dicomImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(dcmImgRefEntHasImgPhysEntStmt.Clone());
	DicomSegmentationEntityHasImagingObservationEntityStatement dcmSegEntHasImgObsEntStmt(dicomSegEntity.GetUniqueIdentifier(), pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(dcmSegEntHasImgObsEntStmt.Clone());
	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<GeneralLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			GeneralLesionObservationEntityHasImagingPhysicalEntityStatement genLesionObsHasImgPhysEntStmt(pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
			imgAnnStatements.push_back(genLesionObsHasImgPhysEntStmt.Clone());
			break;
		}
	}
	ImageAnnotationHasCalculationEntityStatement imgAnnHasCalcStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasCalcStmt.Clone());
	ImageAnnotationHasChildImageAnnotationStatement imgAnnHasChildImgAnn(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetUniqueIdentifier()); // self-reference
	imgAnnStatements.push_back(imgAnnHasChildImgAnn.Clone());

	ImageAnnotationHasDicomImageReferenceEntityStatement imgAnnHasDcmImgRefEntStmt(pAnnotation->GetUniqueIdentifier(), dicomImageRefEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasDcmImgRefEntStmt.Clone());
	ImageAnnotationHasDicomSegmentationEntityStatement imgAnnHasDcmSegEntStmt(pAnnotation->GetUniqueIdentifier(), dicomSegEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasDcmSegEntStmt.Clone());
	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<GeneralLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			ImageAnnotationHasGeneralLesionObservationEntityStatement imgAnnHasGenLesionObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier());
			imgAnnStatements.push_back(imgAnnHasGenLesionObsEntStmt.Clone());
			break;
		}
	}
	ImageAnnotationHasImagingObservationEntityStatement imgAnnHasImgObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasImgObsEntStmt.Clone());
	ImageAnnotationHasImagingPhysicalEntityStatement imgAnnHasImgPhysEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasImgPhysEntStmt.Clone());
	ImageAnnotationHasInferenceEntityStatement imgAnnHasInfEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetInferenceEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasInfEntStmt.Clone());
	ImageAnnotationHasTextAnnotationEntityStatement imgAnnHasTextAnnEntStmt(pAnnotation->GetUniqueIdentifier(), textAnnEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasTextAnnEntStmt.Clone());
	ImageAnnotationHasThreeDimensionGeometricShapeEntityStatement imgAnnHasThreeDEntStmt(pAnnotation->GetUniqueIdentifier(), point3D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasThreeDEntStmt.Clone());
	ImageAnnotationHasTwoDimensionGeometricShapeEntityStatement imgAnnHasTwoDEntStmt(pAnnotation->GetUniqueIdentifier(), point2D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasTwoDEntStmt.Clone());
	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<TimePointLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			ImageAnnotationHasTimePointLesionObservationEntityStatement imgAnnHasTimePointLesionObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier());
			imgAnnStatements.push_back(imgAnnHasTimePointLesionObsEntStmt.Clone());
			break;
		}
	}
	ImageAnnotationHasUriImageReferenceEntityStatement imgAnnHasUriImgRefEntStmt(pAnnotation->GetUniqueIdentifier(), uriImageRefEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgAnnHasUriImgRefEntStmt.Clone());

	ImagingObservationEntityIsIdentifiedByThreeDimensionGeometricShapeEntityStatement imgObsEntIsIdByThreeDGeoShapeEntStmt(pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier(), ellipsoid3D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgObsEntIsIdByThreeDGeoShapeEntStmt.Clone());
	ImagingObservationEntityIsIdentifiedByTwoDimensionGeometricShapeEntityStatement imgObsEntIsIdByTwoDGeoShapeEntStmt(pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier(), circle2D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgObsEntIsIdByTwoDGeoShapeEntStmt.Clone());
	ImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement imgObsEntIsIdByTxtAnnEntStmt(pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier(), textAnnEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgObsEntIsIdByTxtAnnEntStmt.Clone());

	ImagingPhysicalEntityHasThreeDimensionGeometricShapeEntityStatement imgPhysEntHasThreeDGeoShapeEntStmt(pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier(), ellipsoid3D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgPhysEntHasThreeDGeoShapeEntStmt.Clone());
	ImagingPhysicalEntityHasTwoDimensionGeometricShapeEntityStatement imgPhysEntHasTwoDGeoShapeEntStmt(pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier(), circle2D.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgPhysEntHasTwoDGeoShapeEntStmt.Clone());
	ImagingPhysicalEntityHasTextAnnotationEntityStatement imgPhysEntHasTxtAnnEntStmt(pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier(), textAnnEntity.GetUniqueIdentifier());
	imgAnnStatements.push_back(imgPhysEntHasTxtAnnEntStmt.Clone());

	ThreeDimensionGeometricShapeEntityIsComprisedOfThreeDimensionGeometricShapeEntityStatement threeDGeoShapeEntIsComprisedOfThreeDShapeEntStmt(polyline3D.GetUniqueIdentifier(), polygon3D.GetUniqueIdentifier());
	imgAnnStatements.push_back(threeDGeoShapeEntIsComprisedOfThreeDShapeEntStmt.Clone());
	ThreeDimensionGeometricShapeEntityExcludesThreeDimensionGeometricShapeEntityStatement threeDGeoShapeEntExcludesThreeDShapeEntStmt(polygon3D.GetUniqueIdentifier(), ellipse3D.GetUniqueIdentifier());
	imgAnnStatements.push_back(threeDGeoShapeEntExcludesThreeDShapeEntStmt.Clone());

	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<TimePointLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			TimePointLesionObservationEntityHasImagingPhysicalEntityStatement timePtEntHasImgPhysEntStmt(pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
			imgAnnStatements.push_back(timePtEntHasImgPhysEntStmt.Clone());
			break;
		}
	}

	TwoDimensionGeometricShapeEntityIsComprisedOfTwoDimensionGeometricShapeEntityStatement twoDGeoShapeEntIsComprisedOfTwoDGeoShapeEnt(multipoint2D.GetUniqueIdentifier(), circle2D.GetUniqueIdentifier());
	imgAnnStatements.push_back(twoDGeoShapeEntIsComprisedOfTwoDGeoShapeEnt.Clone());
	TwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement twoDGeoShapeEntExcludesTwoDGeoShapeEntStmt(ellipse2D.GetUniqueIdentifier(), circle2D.GetUniqueIdentifier());
	imgAnnStatements.push_back(twoDGeoShapeEntExcludesTwoDGeoShapeEntStmt.Clone());

	UriImageReferenceEntityHasImagingObservationEntityStatement uriImgRefEntHasImgObsEntStmt(uriImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(uriImgRefEntHasImgObsEntStmt.Clone());
	UriImageReferenceEntityHasImagingPhysicalEntityStatement uriImgRefEntHasImgPhysEntStmt(uriImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(uriImgRefEntHasImgPhysEntStmt.Clone());
	UriImageReferenceEntityHasCalculationEntityStatement uriImgRefEntHasCalcEntStmt(uriImageRefEntity.GetUniqueIdentifier(), pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	imgAnnStatements.push_back(uriImgRefEntHasCalcEntStmt.Clone());

	pAnnotation->SetImageAnnotationStatementCollection(imgAnnStatements);
	// Deallocate all statements
	for (ImageAnnotationStatementPtrVector::iterator iter = imgAnnStatements.begin(); iter < imgAnnStatements.end(); iter++)
		delete *iter;
	imgAnnStatements.clear();

	return pAnnotation;
}


/*
	Creates test Annotation Of Annotation object. 
	NOTE: After using the object, it needs to be deallocated.
*/
static AnnotationOfAnnotation* create_annotation_of_annotation()
{
	AnnotationOfAnnotation* pAnnotation = new AnnotationOfAnnotation();

	// Populate AnnotationEnity common data
	::populateAnnotationEntity(pAnnotation);

	// Populate AnnotationOfAnnotation-specific data
	CD code;
	II uid;
	std::vector<std::string> strVector;

	// AdjudicationObservation
	AdjudicationObservation adjudicationObs;
	adjudicationObs.SetObservationUid(uid = II::generate());
	adjudicationObs.SetPersonObserversRoleInThisProcedure(&(code = CD("obsRole1", "Pers Obs Role One", "VKL")));
	strVector.clear();
	strVector.push_back(_T("Accepted Role Id One"));
	strVector.push_back(_T("Accepted Role Id Two"));
	adjudicationObs.SetIdentifierWithinAcceptedPersonObserversRole(strVector);
	strVector.clear();
	strVector.push_back(_T("Rejected Role Id One"));
	strVector.push_back(_T("Rejected Role Id Two"));
	adjudicationObs.SetIdentifierWithinRejectedPersonObserversRole(strVector);
	adjudicationObs.SetReasonForChoice(code = CD("reasonForChoice1", "Reason For Choice One", "VKL"));
	adjudicationObs.SetReasonForDiscordance(&(code = CD("reasonForDisc1", "Reason For Discordance One", "VKL")));
	adjudicationObs.SetComment("Adjudicator Comment One");
	adjudicationObs.SetImageQualityIssuesDiscordance(false);
	adjudicationObs.SetObservationScope(code = CD("obsScope1", "Obs Scope One", "VKL"));
	pAnnotation->SetAdjudicationObservation(&adjudicationObs);


	//////////////////////////////////////////////////////////////////////////////
	// Annotation Of Annotation Statements
	//////////////////////////////////////////////////////////////////////////////
	AnnotationOfAnnotationStatementPtrVector annOfAnnStatements;
	::populateAnnotationStatments(pAnnotation, annOfAnnStatements);

	AnnotationOfAnnotationHasAnnotationOfAnnotationStatement annOfAnnHasAnnOfAnnStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasAnnOfAnnStmt.Clone());
	AnnotationOfAnnotationHasAnnotationRoleEntityStatement annOfAnnHasAnnRoleEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetAnnotationRoleEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasAnnRoleEntStmt.Clone());
	AnnotationOfAnnotationHasCalculationEntityStatement annOfAnnHasCalcEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasCalcEntStmt.Clone());
	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<GeneralLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			AnnotationOfAnnotationHasGeneralLesionObservationEntityStatement annOfAnnHasGenLesionObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier());
			annOfAnnStatements.push_back(annOfAnnHasGenLesionObsEntStmt.Clone());
			break;
		}
	}
	AnnotationOfAnnotationHasImageAnnotationStatement annOfAnnHasImgAnnStatement(pAnnotation->GetUniqueIdentifier(), uid = II::generate());
	annOfAnnStatements.push_back(annOfAnnHasImgAnnStatement.Clone());
	AnnotationOfAnnotationHasImagingObservationEntityStatement annOfAnnHasImgObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasImgObsEntStmt.Clone());
	AnnotationOfAnnotationHasImagingPhysicalEntityStatement annOfAnnHasImgPhysEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasImgPhysEntStmt.Clone());
	AnnotationOfAnnotationHasInferenceEntityStatement annOfAnnHasInferenceEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetInferenceEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnHasInferenceEntStmt.Clone());
	for (LesionObservationEntityPtrVector::size_type i = 0; i < pAnnotation->GetLesionObservationEntityCollection().size(); i++)
	{
		if (pAnnotation->GetLesionObservationEntityCollection()[i] && dynamic_cast<TimePointLesionObservationEntity*>(pAnnotation->GetLesionObservationEntityCollection()[i]))
		{
			AnnotationOfAnnotationHasTimePointLesionObservationEntityStatement annOfAnnHasTimePointLesionObsEntStmt(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetLesionObservationEntityCollection()[i]->GetUniqueIdentifier());
			annOfAnnStatements.push_back(annOfAnnHasTimePointLesionObsEntStmt.Clone());
			break;
		}
	}
	AnnotationOfAnnotationIsComparedWithAnnotationOfAnnotationStatement annOfAnnIsComparedWithAnnOfAnn(pAnnotation->GetUniqueIdentifier(), pAnnotation->GetUniqueIdentifier());
	annOfAnnStatements.push_back(annOfAnnIsComparedWithAnnOfAnn.Clone());
	AnnotationOfAnnotationIsComparedWithImageAnnotationStatement annOfAnnIsComparedWithImgAnnStmt(pAnnotation->GetUniqueIdentifier(), uid = II::generate());
	annOfAnnStatements.push_back(annOfAnnIsComparedWithImgAnnStmt.Clone());
	CalculationEntityIsComparedWithCalculationEntityStatement calcEntIsComparedWithCalcEntStmt(pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier(), pAnnotation->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(calcEntIsComparedWithCalcEntStmt.Clone());

	ImageAnnotationHasAnnotationRoleEntityStatement imgAnnHasAnnRoleEntStmt(uid = II::generate(), pAnnotation->GetAnnotationRoleEntityCollection()[0].GetUniqueIdentifier());
	annOfAnnStatements.push_back(imgAnnHasAnnRoleEntStmt.Clone());
	ImageAnnotationIsComparedWithImageAnnotationStatement imgAnnIsComparedWithImgAnnStmt(uid = II::generate(), uid = II::generate());
	annOfAnnStatements.push_back(imgAnnIsComparedWithImgAnnStmt.Clone());
	ImageAnnotationIsComparedWithAnnotationOfAnnotationStatement imgAnnIsComparedWithAnnOfAnnStmt(uid = II::generate(), pAnnotation->GetUniqueIdentifier());
	annOfAnnStatements.push_back(imgAnnIsComparedWithAnnOfAnnStmt.Clone());


	pAnnotation->SetAnnotationOfAnnotationStatementCollection(annOfAnnStatements);
	// Deallocate all statements
	for (AnnotationOfAnnotationStatementPtrVector::iterator iter = annOfAnnStatements.begin(); iter < annOfAnnStatements.end(); iter++)
		delete *iter;
	annOfAnnStatements.clear();

	return pAnnotation;
}

static void populateAnnotationStatments(AnnotationEntity *pAnnEntity, std::vector<AnnotationStatement*>& annStatements)
{
	if (!pAnnEntity)
		return;

	// Annotation statements
	for (TaskContextEntityVector::const_iterator iter = pAnnEntity->GetTaskContextEntityCollection().begin(); iter < pAnnEntity->GetTaskContextEntityCollection().end(); iter++)
	{
		AnnotationEntityHasPerformedTaskContextEntityStatement annEntHasPerformedTaskContextEntStmt(pAnnEntity->GetUniqueIdentifier(), iter->GetUniqueIdentifier());
		annStatements.push_back(annEntHasPerformedTaskContextEntStmt.Clone());
		AnnotationEntityHasPlannedTaskContextEntityStatement annEntHasPlannedTaskContextEntStmt(pAnnEntity->GetUniqueIdentifier(), iter->GetUniqueIdentifier());
		annStatements.push_back(annEntHasPlannedTaskContextEntStmt.Clone());
	}
	CalculationEntityReferencesCalculationEntityStatement calcEntReferencesCalcEntStmt(pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(calcEntReferencesCalcEntStmt.Clone());
	CalculationEntityUsesCalculationEntityStatement calcEntUsesCalcEntStmt(pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(calcEntUsesCalcEntStmt.Clone());
	ImagingObservationEntityHasCalculationEntityStatement imgObsEntHasCalcEntStmt(pAnnEntity->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(imgObsEntHasCalcEntStmt.Clone());
	ImagingObservationEntityIsFoundInImagingPhysicalEntityStatement imgObsEntIsFoundInImgPhysEntStmt(pAnnEntity->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(imgObsEntIsFoundInImgPhysEntStmt.Clone());
	ImagingPhysicalEntityHasCalculationEntityStatement imgPhysEntHasCalcEntStmt(pAnnEntity->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetCalculationEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(imgPhysEntHasCalcEntStmt.Clone());
	ImagingPhysicalEntityHasImagingObservationEntityStatement imgPhysEntHasImgObsEntStmt(pAnnEntity->GetImagingPhysicalEntityCollection()[0].GetUniqueIdentifier(), pAnnEntity->GetImagingObservationEntityCollection()[0].GetUniqueIdentifier());
	annStatements.push_back(imgPhysEntHasImgObsEntStmt.Clone());
}
