/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DSRXMLC_H
#define DSRXMLC_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/oftypes.h"    /* for definition of OFBool */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDDEF
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmsr/dsdefine.h"

#ifdef WITH_LIBXML
#include <libxml/parser.h>
#endif


/*--------------------*
 *  type definitions  *
 *--------------------*/

#ifndef WITH_LIBXML
// define pointer type if 'libxml' absent
typedef void (*xmlNodePtr);
#endif


/*-----------------------*
 *  forward declaration  *
 *-----------------------*/

class DSRXMLDocument;


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for XML document cursors.
 *  This class encapsulates the access to the 'libxml' node pointer and,
 *  therefore, allows to replace the XML library with little effort (if
 *  required).
 */
class DCMTK_DCMSR_EXPORT DSRXMLCursor
{

    // allow DSRXMLDocument to access private member variable 'Node' directly
    friend class DSRXMLDocument;


  public:

    /** default constructor
     */
    DSRXMLCursor();

    /** copy constructor
     ** @param cursor cursor object to be copied
     */
    DSRXMLCursor(const DSRXMLCursor &cursor);

    /** destructor
     */
    virtual ~DSRXMLCursor();

    /** assignment operator
     ** @param  cursor  cursor object to be copied
     ** @return reference to this cursor object after 'cursor' has been copied
     */
    DSRXMLCursor &operator=(const DSRXMLCursor &cursor);

    /** check whether cursor is valid.
     *  Valid means that the cursor points to a valid XML node.
     ** @return OFTrue if valid, OFFalse otherwise
     */
    inline OFBool valid() const
    {
        return (Node != NULL);
    }

    /** set cursor to next XML node (same level).
     *  Blank (empty or whitespace only) nodes are ignored/skipped.
     ** @return reference to this cursor object (might be invalid)
     */
    DSRXMLCursor &gotoNext();

    /** set cursor to first XML child node (next lower level).
     *  Blank (empty or whitespace only) nodes are ignored/skipped.
     ** @return reference to this cursor object (might be invalid)
     */
    DSRXMLCursor &gotoChild();

    /** get cursor pointing to next XML node (same level).
     *  This cursor object is not modified.
     ** @return copy of the requested cursor object (might be invalid)
     */
    DSRXMLCursor getNext() const;

    /** get cursor pointing to first XML child node (next lower level).
     *  This cursor object is not modified.
     ** @return copy of the requested cursor object (might be invalid)
     */
    DSRXMLCursor getChild() const;


  private:

    /// pointer to the associated 'libxml' node
    xmlNodePtr Node;
};


#endif
