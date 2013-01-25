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
