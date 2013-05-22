/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: StdInInputSource.hpp 527149 2007-04-10 14:56:39Z amassari $
 */


#if !defined(XERCESC_INCLUDE_GUARD_STDININPUTSOURCE_HPP)
#define XERCESC_INCLUDE_GUARD_STDININPUTSOURCE_HPP

#include <xercesc/sax/InputSource.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class BinInputStream;


/**
 *  This class is a derivative of the standard InputSource class. It provides
 *  for the parser access to data via the standard input. This input source
 *  is not commonly used, but can be useful when implementing such things
 *  as pipe based tools which exchange XML data.
 *
 *  As with all InputSource derivatives. The primary objective of an input
 *  source is to create an input stream via which the parser can spool in
 *  data from the referenced source.
 */
class XMLPARSER_EXPORT StdInInputSource : public InputSource
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructor */
    //@{

    /**
      * Since the standard input is a canned source, the constructor is very
      * simple. It just uses local platform services to open up the standard
      * input source as file, a new handleof which it gives to each new stream
      * it creates.
      */
    StdInInputSource(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    //@}

    /** @name Destructor */
    //@{
    ~StdInInputSource();
    //@}


    // -----------------------------------------------------------------------
    //  Virtual input source interface
    // -----------------------------------------------------------------------


    /** @name Virtual methods */
    //@{

    /**
     * This method will return a binary input stream derivative that will
     * parse from the standard input of the local host.
     *
     * @return A dynamically allocated binary input stream derivative that
     *         can parse from the standardinput.
     */
    BinInputStream* makeStream() const;

    //@}

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    StdInInputSource(const StdInInputSource&);
    StdInInputSource& operator=(const StdInInputSource&);

};

inline StdInInputSource::StdInInputSource(MemoryManager* const manager) :

    InputSource("stdin", manager)
{
}

inline StdInInputSource::~StdInInputSource()
{
}

XERCES_CPP_NAMESPACE_END

#endif
