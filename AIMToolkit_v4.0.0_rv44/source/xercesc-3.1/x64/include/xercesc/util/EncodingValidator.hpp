/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: EncodingValidator.hpp 635560 2008-03-10 14:10:09Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_ENCODINGVALIDATOR_HPP)
#define XERCESC_INCLUDE_GUARD_ENCODINGVALIDATOR_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/ValueHashTableOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * A singleton class that checks whether an encoding name is a valid IANA
  * encoding
  */

class XMLUTIL_EXPORT EncodingValidator {

public:
    // -----------------------------------------------------------------------
    //  Validation methods
    // -----------------------------------------------------------------------
    bool isValidEncoding(const XMLCh* const encName);

    // -----------------------------------------------------------------------
    //  Instance methods
    // -----------------------------------------------------------------------
    static EncodingValidator* instance();

private:
    // -----------------------------------------------------------------------
    //  Constructor and destructors
    // -----------------------------------------------------------------------
    EncodingValidator();
    ~EncodingValidator();

    // -----------------------------------------------------------------------
    //  Private Helpers methods
    // -----------------------------------------------------------------------
    /*
     *  Initializes the registry with a set of valid IANA encoding names
     */
     void initializeRegistry();

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fEncodingRegistry
    //      Contains a set of IANA encoding names
	//
    //  fInstance
    //      An EncodingValidator singleton instance
    // -----------------------------------------------------------------------
    ValueHashTableOf<bool>*   fEncodingRegistry;
    static EncodingValidator* fInstance;
    friend class XMLInitializer;
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  *	End file EncodingValidator.hpp
  */
