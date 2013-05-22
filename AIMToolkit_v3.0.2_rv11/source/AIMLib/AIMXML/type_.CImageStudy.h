/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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

	MemberAttribute<__int64,_altova_mi_altova_CImageStudy_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CImageStudy_altova_instanceUID, 0, 0> instanceUID;	// instanceUID Cstring

	MemberAttribute<altova::DateTime,_altova_mi_altova_CImageStudy_altova_startDate, 0, 0> startDate;	// startDate CdateTime

	MemberAttribute<string_type,_altova_mi_altova_CImageStudy_altova_startTime, 0, 0> startTime;	// startTime Cstring
	MemberElement<CimageSeriesType, _altova_mi_altova_CImageStudy_altova_imageSeries> imageSeries;
	struct imageSeries { typedef Iterator<CimageSeriesType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageStudy
