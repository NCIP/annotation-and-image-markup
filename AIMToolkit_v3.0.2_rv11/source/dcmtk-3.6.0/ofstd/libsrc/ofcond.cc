/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofcond.h"


/* ---------- global condition constants ---------- */

const OFConditionConst ECC_Normal(          0, 0, OF_ok,      "Normal");
const OFConditionConst ECC_IllegalParameter(0, 1, OF_error,   "Illegal parameter");
const OFConditionConst ECC_MemoryExhausted( 0, 2, OF_failure, "Virtual Memory exhausted");

// NOTE: 
// error codes 1024..2047 are reserved for inter-process communication 
// errors defined elsewhere in module ofstd

const OFCondition EC_Normal(ECC_Normal);
const OFCondition EC_IllegalParameter(ECC_IllegalParameter);
const OFCondition EC_MemoryExhausted(ECC_MemoryExhausted);

/* ---------- class OFConditionConst ---------- */


const OFConditionBase *OFConditionConst::clone() const
{
  return this; // since we're not deletable, we just return a copy to ourselves
}

unsigned long OFConditionConst::codeAndModule() const
{
  return theCodeAndModule;
}

OFStatus OFConditionConst::status() const
{
  return theStatus;
}

const char *OFConditionConst::text() const
{
  return theText;
}

OFBool OFConditionConst::deletable() const
{
  return OFFalse;
}


/* ---------- class OFConditionString ---------- */


const OFConditionBase *OFConditionString::clone() const
{
  return new OFConditionString(*this);
}

unsigned long OFConditionString::codeAndModule() const
{
  return theCodeAndModule;
}

OFStatus OFConditionString::status() const
{
  return theStatus;
}

const char *OFConditionString::text() const
{
  return theText.c_str();
}

OFBool OFConditionString::deletable() const
{
  return OFTrue;
}


/*
 *
 * CVS/RCS Log:
 * $Log: ofcond.cc,v $
 * Revision 1.5  2010-10-14 13:14:53  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2005/12/08 15:48:51  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.3  2002/07/10 11:52:54  meichel
 * Added comment about reserved range of error codes
 *
 * Revision 1.2  2001/09/25 17:07:27  meichel
 * Disabled implicit conversion to bool, added default constructor
 *   to class OFCondition.
 *
 * Revision 1.1  2001/08/23 16:08:41  meichel
 * Initial release of class OFCondition, a generic approach for condition codes
 *
 *
 *
 */
