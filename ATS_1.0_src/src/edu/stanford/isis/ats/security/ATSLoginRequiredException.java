/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.security;

/**
 * Throw this exception when a login is required. It should force the
 * application to display the login page.
 * @author alansnyder
 */
public class ATSLoginRequiredException extends Exception {

}
