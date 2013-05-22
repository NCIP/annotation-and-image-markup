/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCASCCFF_H
#define DCASCCFF_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofcond.h"   /* for class OFCondition */
#include "dcmtk/dcmnet/dndefine.h"

class DcmAssociationConfiguration;
class OFConfigFile;

/** helper class that encapsulated methods for filling 
 *  a DcmAssociationConfiguration object from a config file
 */
class DCMTK_DCMNET_EXPORT DcmAssociationConfigurationFile
{
public:

  /** reads the given configuration file and feeds the information
   *  contained therein into the association configuration object.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition initialize(
    DcmAssociationConfiguration& cfg,
    const char *filename);

private:

  /** parses the transfer syntax lists in the config file.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition parseTransferSyntaxes(
    DcmAssociationConfiguration& cfg,
    OFConfigFile& config);

  /** parses the presentation context lists in the config file.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition parsePresentationContexts(
    DcmAssociationConfiguration& cfg,
    OFConfigFile& config);

  /** parses the role selection lists in the config file.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition parseRoleSelectionItems(
    DcmAssociationConfiguration& cfg,
    OFConfigFile& config);

  /** parses the extended negotiation lists in the config file.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition parseExtendedNegotiationItems(
    DcmAssociationConfiguration& cfg,
    OFConfigFile& config);

  /** parses the association configuration profile lists in the config file.
   *  @param cfg association configuration object to initialize
   *  @param filename name of config file
   *  @return EC_Normal if successful, an error code otherwise
   */
  static OFCondition parseProfiles(
    DcmAssociationConfiguration& cfg,
    OFConfigFile& config);

};

#endif
