/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ContentLeafNameTypeVector.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CONTENTLEAFNAMETYPEVECTOR_HPP)
#define XERCESC_INCLUDE_GUARD_CONTENTLEAFNAMETYPEVECTOR_HPP

#include <xercesc/validators/common/ContentSpecNode.hpp>
#include <xercesc/framework/MemoryManager.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLPARSER_EXPORT ContentLeafNameTypeVector : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Class specific types
    // -----------------------------------------------------------------------


    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ContentLeafNameTypeVector
    (
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    ContentLeafNameTypeVector
    (
        QName** const                     qName
      , ContentSpecNode::NodeTypes* const types
      , const XMLSize_t                   count
      , MemoryManager* const              manager = XMLPlatformUtils::fgMemoryManager
    );

    ~ContentLeafNameTypeVector();

    ContentLeafNameTypeVector(const ContentLeafNameTypeVector&);

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    QName* getLeafNameAt(const XMLSize_t pos) const;

    ContentSpecNode::NodeTypes getLeafTypeAt(const XMLSize_t pos) const;
    XMLSize_t getLeafCount() const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setValues
    (
        QName** const                      qName
      , ContentSpecNode::NodeTypes* const  types
      , const XMLSize_t                    count
    );

    // -----------------------------------------------------------------------
    //  Miscellaneous
    // -----------------------------------------------------------------------

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ContentLeafNameTypeVector& operator=(const ContentLeafNameTypeVector&);

    // -----------------------------------------------------------------------
    //  helper methods
    // -----------------------------------------------------------------------
    void cleanUp();
    void init(const XMLSize_t size);

    // -----------------------------------------------------------------------
    //  Private Data Members
    //
    // -----------------------------------------------------------------------
    MemoryManager*                fMemoryManager;
    QName**                       fLeafNames;
    ContentSpecNode::NodeTypes   *fLeafTypes;
    XMLSize_t                     fLeafCount;
};

inline void ContentLeafNameTypeVector::cleanUp()
{
	fMemoryManager->deallocate(fLeafNames); //delete [] fLeafNames;
	fMemoryManager->deallocate(fLeafTypes); //delete [] fLeafTypes;
}

inline void ContentLeafNameTypeVector::init(const XMLSize_t size)
{
    fLeafNames = (QName**) fMemoryManager->allocate(size * sizeof(QName*));//new QName*[size];
    fLeafTypes = (ContentSpecNode::NodeTypes *) fMemoryManager->allocate
    (
        size * sizeof(ContentSpecNode::NodeTypes)
    ); //new ContentSpecNode::NodeTypes [size];
    fLeafCount = size;
}

XERCES_CPP_NAMESPACE_END

#endif
