/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMImplementationSource.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATIONSOURCE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMIMPLEMENTATIONSOURCE_HPP

 /**
  * This interface permits a DOM implementer to supply one or more
  * implementations, based upon requested features and versions. Each implemented
  * <code>DOMImplementationSource</code> object is listed in the
  * binding-specific list of available sources so that its
  * <code>DOMImplementation</code> objects are made available.
  *
  * @since DOM Level 3
  */
#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMImplementation;
class DOMImplementationList;

class CDOM_EXPORT DOMImplementationSource
{
protected :
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{    
    DOMImplementationSource() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMImplementationSource(const DOMImplementationSource &);
    DOMImplementationSource & operator = (const DOMImplementationSource &);
    //@}


public:
    // -----------------------------------------------------------------------
    //  All constructors are hidden, just the destructor is available
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
    /**
     * Destructor
     *
     */
    virtual ~DOMImplementationSource() {};
    //@}

    // -----------------------------------------------------------------------
    //  Virtual DOMImplementationSource interface
    // -----------------------------------------------------------------------
    /** @name Functions introduced in DOM Level 3 */
    //@{
    /**
     * A method to request the first DOM implementation that supports the specified features.
     *
     * @param features A string that specifies which features are required.
     *   This is a space separated list in which each feature is specified
     *   by its name optionally followed by a space and a version number.
     *   This is something like: "XML 1.0 Traversal 2.0"
     * @return An implementation that has the desired features, or
     *   <code>null</code> if this source has none.
     * @since DOM Level 3
     */
    virtual DOMImplementation* getDOMImplementation(const XMLCh* features) const = 0;

    /**
     * A method to request a list of DOM implementations that support the specified features and versions,
     *
     * @param features A string that specifies which features are required.
     *   This is a space separated list in which each feature is specified
     *   by its name optionally followed by a space and a version number.
     *   This is something like: "XML 1.0 Traversal 2.0"
     * @return A list of DOM implementations that support the desired features
     * @since DOM Level 3
     */
    virtual DOMImplementationList* getDOMImplementationList(const XMLCh* features) const = 0;
    //@}

};

XERCES_CPP_NAMESPACE_END

#endif
