/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



#include "StdAfx.h"
#include "Altova.h"
#include "AltovaException.h"

namespace altova {


CAltovaException::CAltovaException(int nCode, const tstring& sMessage, bool bUserExc)
	: m_nCode(nCode), m_sMessage(sMessage), m_bUserExc(bUserExc)
{
}


int CAltovaException::GetCode()
{
	return m_nCode;
}


const tstring& CAltovaException::GetInfo() const
{
	return m_sMessage;
}

bool CAltovaException::IsUserException() const
{
	return m_bUserExc;
}

} // namespace altova
