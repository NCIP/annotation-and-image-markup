/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: EndOfEntityException.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_ENDOFENTITYEXCEPTION_HPP)
#define XERCESC_INCLUDE_GUARD_ENDOFENTITYEXCEPTION_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLEntityDecl;

//
//  This class is only used internally. Its thrown by the ReaderMgr class,
//  when an entity ends, and is caught in the scanner. This tells the scanner
//  that an entity has ended, and allows it to do the right thing according
//  to what was going on when the entity ended.
//
//  Since its internal, it does not bother implementing XMLException.
//
class XMLPARSER_EXPORT EndOfEntityException
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    EndOfEntityException(       XMLEntityDecl*  entityThatEnded
                        , const XMLSize_t       readerNum) :

        fEntity(entityThatEnded)
        , fReaderNum(readerNum)
    {
    }

    EndOfEntityException(const EndOfEntityException& toCopy) :

        fEntity(toCopy.fEntity)
        , fReaderNum(toCopy.fReaderNum)
    {
    }

    ~EndOfEntityException()
    {
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLEntityDecl& getEntity();
    const XMLEntityDecl& getEntity() const;
    XMLSize_t getReaderNum() const;


private :
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    EndOfEntityException& operator = (const  EndOfEntityException&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fEntity
    //      This is a reference to the entity that ended, causing this
    //      exception.
    //
    //  fReaderNum
    //      The unique reader number of the reader that was handling this
    //      entity. This is used to know whether a particular entity has
    //      ended.
    // -----------------------------------------------------------------------
    XMLEntityDecl*  fEntity;
    XMLSize_t       fReaderNum;
};


// ---------------------------------------------------------------------------
//  EndOfEntityException: Getter methods
// ---------------------------------------------------------------------------
inline XMLEntityDecl& EndOfEntityException::getEntity()
{
    return *fEntity;
}

inline const XMLEntityDecl& EndOfEntityException::getEntity() const
{
    return *fEntity;
}

inline XMLSize_t EndOfEntityException::getReaderNum() const
{
    return fReaderNum;
}

XERCES_CPP_NAMESPACE_END

#endif
