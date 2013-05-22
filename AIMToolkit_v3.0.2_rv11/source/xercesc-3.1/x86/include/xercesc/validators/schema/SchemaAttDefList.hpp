/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: SchemaAttDefList.hpp 673679 2008-07-03 13:50:10Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_SCHEMAATTDEFLIST_HPP)
#define XERCESC_INCLUDE_GUARD_SCHEMAATTDEFLIST_HPP

#include <xercesc/util/RefHash2KeysTableOf.hpp>
#include <xercesc/validators/schema/SchemaElementDecl.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a derivative of the framework abstract class which defines the
//  interface to a list of attribute defs that belong to a particular
//  element. The scanner needs to be able to get a list of the attributes
//  that an element supports, for use during the validation process and for
//  fixed/default attribute processing.
//
//  For us, we just wrap the RefHash2KeysTableOf collection that the SchemaElementDecl
//  class uses to store the attributes that belong to it.
//
//  This class does not adopt the hash table, it just references it. The
//  hash table is owned by the element decl it is a member of.
//
class VALIDATORS_EXPORT SchemaAttDefList : public XMLAttDefList
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    SchemaAttDefList
    (
         RefHash2KeysTableOf<SchemaAttDef>* const    listToUse,
         MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    ~SchemaAttDefList();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual interface
    // -----------------------------------------------------------------------

    virtual bool isEmpty() const;
    virtual XMLAttDef* findAttDef
    (
        const   unsigned int       uriID
        , const XMLCh* const        attName
    );
    virtual const XMLAttDef* findAttDef
    (
        const   unsigned int       uriID
        , const XMLCh* const        attName
    )   const;
    virtual XMLAttDef* findAttDef
    (
        const   XMLCh* const        attURI
        , const XMLCh* const        attName
    );
    virtual const XMLAttDef* findAttDef
    (
        const   XMLCh* const        attURI
        , const XMLCh* const        attName
    )   const;

    XMLAttDef* findAttDefLocalPart
    (
        const   unsigned int        uriID
        , const XMLCh* const        attLocalPart
    );

    const XMLAttDef* findAttDefLocalPart
    (
        const   unsigned int        uriID
        , const XMLCh* const        attLocalPart
    )   const;

    /**
     * return total number of attributes in this list
     */
    virtual XMLSize_t getAttDefCount() const ;

    /**
     * return attribute at the index-th position in the list.
     */
    virtual XMLAttDef &getAttDef(XMLSize_t index) ;

    /**
     * return attribute at the index-th position in the list.
     */
    virtual const XMLAttDef &getAttDef(XMLSize_t index) const ;

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(SchemaAttDefList)

	SchemaAttDefList(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    SchemaAttDefList(const SchemaAttDefList&);
    SchemaAttDefList& operator=(const SchemaAttDefList&);

    void addAttDef(SchemaAttDef *toAdd);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fEnum
    //      This is an enumerator for the list that we use to do the enumerator
    //      type methods of this class.
    //
    //  fList
    //      The list of SchemaAttDef objects that represent the attributes that
    //      a particular element supports.
    //  fArray
    //      vector of pointers to the DTDAttDef objects contained in this list
    //  fSize
    //      size of fArray
    //  fCount
    //      number of DTDAttDef objects currently stored in this list
    // -----------------------------------------------------------------------
    RefHash2KeysTableOfEnumerator<SchemaAttDef>*    fEnum;
    RefHash2KeysTableOf<SchemaAttDef>*              fList;
    SchemaAttDef**                                  fArray;
    XMLSize_t                                       fSize;
    XMLSize_t                                       fCount;

    friend class ComplexTypeInfo;
};

inline void SchemaAttDefList::addAttDef(SchemaAttDef *toAdd)
{
    if(fCount == fSize)
    {
        // need to grow fArray
        fSize <<= 1;
        SchemaAttDef** newArray = (SchemaAttDef **)((getMemoryManager())->allocate( sizeof(SchemaAttDef*) * fSize ));
        memcpy(newArray, fArray, fCount * sizeof(SchemaAttDef *));
        (getMemoryManager())->deallocate(fArray);
        fArray = newArray;
    }
    fArray[fCount++] = toAdd;
}

inline XMLAttDef* SchemaAttDefList::findAttDefLocalPart(const   unsigned int       uriID
                                                      , const XMLCh* const        attLocalPart)
{
    return fList->get((void*)attLocalPart, uriID);
}

inline const XMLAttDef* SchemaAttDefList::findAttDefLocalPart(const   unsigned int       uriID
                                                            , const XMLCh* const        attLocalPart)   const
{
    return fList->get((void*)attLocalPart, uriID);
}

XERCES_CPP_NAMESPACE_END

#endif
