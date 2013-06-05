/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageStudy
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageStudy



namespace AIMXML
{

class CImageStudy : public TypeBase
{
public:
	AIMXML_EXPORT CImageStudy(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageStudy(CImageStudy const& init);
	void operator=(CImageStudy const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageStudy); }
	MemberElement<iso::CII, _altova_mi_altova_CImageStudy_altova_instanceUid> instanceUid;
	struct instanceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CImageStudy_altova_startDate> startDate;
	struct startDate { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CImageStudy_altova_startTime> startTime;
	struct startTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CImageStudy_altova_procedureDescription> procedureDescription;
	struct procedureDescription { typedef Iterator<iso::CST> iterator; };
	MemberElement<CImageSeries, _altova_mi_altova_CImageStudy_altova_imageSeries> imageSeries;
	struct imageSeries { typedef Iterator<CImageSeries> iterator; };
	MemberElement<CreferencedDicomObjectCollectionType, _altova_mi_altova_CImageStudy_altova_referencedDicomObjectCollection> referencedDicomObjectCollection;
	struct referencedDicomObjectCollection { typedef Iterator<CreferencedDicomObjectCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageStudy
