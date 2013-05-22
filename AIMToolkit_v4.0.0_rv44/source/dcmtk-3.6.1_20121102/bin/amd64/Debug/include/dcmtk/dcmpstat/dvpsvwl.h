/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DVPSVWL_H
#define DVPSVWL_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmpstat/dpdefine.h"
#include "dcmtk/dcmdata/dcitem.h"

class DVPSVOIWindow;


/** the list of VOI Windows contained in an image attached to a presentation state.
 *  This class manages the data structures comprising the VOI Windows
 *  of one image attached to a presentation state.
 */

class DCMTK_DCMPSTAT_EXPORT DVPSVOIWindow_PList
{
public:
  /// default constructor
  DVPSVOIWindow_PList();

  /// copy constructor
  DVPSVOIWindow_PList(const DVPSVOIWindow_PList& copy);

  /** clone method.
   *  @return a pointer to a new DVPSVOIWindow_PList object containing
   *  a deep copy of this object.
   */
  DVPSVOIWindow_PList *clone() { return new DVPSVOIWindow_PList(*this); }

  /// destructor
  virtual ~DVPSVOIWindow_PList();

  /** reads a list of VOI Windows from a DICOM dataset.
   *  The DICOM elements of the VOI Window are copied
   *  from the dataset to this object.
   *  If this method returns an error code, the object is in undefined state afterwards.
   *  @param dset the dataset from which the VOI Windows are to be read
   *  @return EC_Normal if successful, an error code otherwise.
   */
  OFCondition read(DcmItem &dset);

  /** reset the object to initial state.
   *  After this call, the object is in the same state as after
   *  creation with the default constructor.
   */
  void clear();

  /** get number of VOI Windows in this list.
   *  @return the number of VOI Windows.
   */
  size_t size() const { return list_.size(); }

  /** returns a pointer to the VOI Window with the given
   *  index or NULL if it does not exist.
   *  @param idx index, must be < size()
   *  @return pointer to VOI Window or NULL
   */
  DVPSVOIWindow *getVOIWindow(size_t idx);

private:

  /// private undefined assignment operator
  DVPSVOIWindow_PList& operator=(const DVPSVOIWindow_PList&);

  /** the list maintained by this object
   */
  OFList<DVPSVOIWindow *> list_;

};

#endif
