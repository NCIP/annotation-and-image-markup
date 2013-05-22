/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: HexBin.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_HEXBIN_HPP)
#define XERCESC_INCLUDE_GUARD_HEXBIN_HPP

#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT HexBin
{
public :
    //@{

    /**
     * return the length of hexData in terms of HexBinary.
     *
     * @param hexData A string containing the HexBinary
     *
     * return: -1 if it contains any invalid HexBinary
     *         the length of the HexNumber otherwise.
     */

    static int  getDataLength(const XMLCh* const hexData);

     /**
     * check an array of data against the Hex table.
     *
     * @param hexData A string containing the HexBinary
     *
     * return: false if it contains any invalid HexBinary
     *         true otherwise.
     */

    static bool isArrayByteHex(const XMLCh* const hexData);

     /**
     * get canonical representation
     *
     * Caller is responsible for the proper deallocation
     * of the string returned.
     *
     * @param hexData A string containing the HexBinary
     * @param manager The MemoryManager to use to allocate the string
     *
     * return: the canonical representation of the HexBinary
     *         if it is a valid HexBinary,
     *         0 otherwise
     */

    static XMLCh* getCanonicalRepresentation
                  (
                      const XMLCh*          const hexData
                    ,       MemoryManager*  const manager = XMLPlatformUtils::fgMemoryManager
                  );

   /**
     * Decodes HexBinary data into XMLByte
     *
     * NOTE: The returned buffer is dynamically allocated and is the
     * responsibility of the caller to delete it when not longer needed.
     * Use the memory manager to release the returned buffer.
     *
     * @param hexData HexBinary data in XMLCh stream.
     * @param manager client provided memory manager
     * @return Decoded binary data in XMLByte stream,
     *      or NULL if input data can not be decoded.
     */
    static XMLByte* decodeToXMLByte(
                         const XMLCh*          const    hexData
                       ,       MemoryManager*  const    manager = XMLPlatformUtils::fgMemoryManager
                        );


    //@}

private :

    // -----------------------------------------------------------------------
    //  Helper methods
    // -----------------------------------------------------------------------

    static bool isHex(const XMLCh& octet);

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    HexBin();
    HexBin(const HexBin&);
    HexBin& operator=(const HexBin&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  isInitialized
    //
    //     set once hexNumberTable is initialized.
    //
    //  hexNumberTable
    //
    //     arrany holding valid hexNumber character.
    //
    // -----------------------------------------------------------------------
    static const XMLByte    hexNumberTable[];
};

XERCES_CPP_NAMESPACE_END

#endif
