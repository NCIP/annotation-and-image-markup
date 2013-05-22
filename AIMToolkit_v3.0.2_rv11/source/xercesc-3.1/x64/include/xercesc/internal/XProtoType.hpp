/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XProtoType.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XPROTOTYPE_HPP)
#define XERCESC_INCLUDE_GUARD_XPROTOTYPE_HPP

#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XSerializeEngine;
class XSerializable;

class XMLUTIL_EXPORT XProtoType
{
public:

           void       store(XSerializeEngine& serEng) const;

    static void        load(XSerializeEngine&          serEng
                          , XMLByte*          const    name
                          , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
                          );

    // -------------------------------------------------------------------------------
    //  data
    //
    //  fClassName: 
    //            name of the XSerializable derivatives
    //
    //  fCreateObject:
    //            pointer to the factory method (createObject()) 
    //            of the XSerializable derivatives
    //
    // -------------------------------------------------------------------------------

    XMLByte*          fClassName;

    XSerializable*    (*fCreateObject)(MemoryManager*);

};

#define DECL_XPROTOTYPE(class_name) \
static  XProtoType        class##class_name;                   \
static  XSerializable*    createObject(MemoryManager* manager);

/***
 * For non-abstract class
 ***/
#define IMPL_XPROTOTYPE_TOCREATE(class_name) \
IMPL_XPROTOTYPE_INSTANCE(class_name) \
XSerializable* class_name::createObject(MemoryManager* manager) \
{return new (manager) class_name(manager);}

/***
* For abstract class
 ***/
#define IMPL_XPROTOTYPE_NOCREATE(class_name) \
IMPL_XPROTOTYPE_INSTANCE(class_name) \
XSerializable* class_name::createObject(MemoryManager*) \
{return 0;}


/***
 * Helper Macro 
 ***/
#define XPROTOTYPE_CLASS(class_name) ((XProtoType*)(&class_name::class##class_name))

#define IMPL_XPROTOTYPE_INSTANCE(class_name) \
XProtoType class_name::class##class_name = \
{(XMLByte*) #class_name, class_name::createObject };

XERCES_CPP_NAMESPACE_END

#endif
