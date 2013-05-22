/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "StdAfx.h"
#include "../Altova/Altova.h"
#include "../Altova/SchemaTypes.h"
#include "XmlException.h"

namespace altova {


CXmlException::CXmlException(int nCode, const tstring& sMessage)
	: CAltovaException(nCode, sMessage)
{
}


} // namespace altova
