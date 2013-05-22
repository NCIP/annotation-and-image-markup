/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLFileMgr.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLFILEMGR_HPP)
#define XERCESC_INCLUDE_GUARD_XMLFILEMGR_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

typedef void* FileHandle;
#define XERCES_Invalid_File_Handle 0

//	Abstract class for files. This is be used to allow multiple file handling implementations.
class XMLFileMgr : public XMemory
{
    public:
        XMLFileMgr() {}
        virtual ~XMLFileMgr() {}

		// File access
        virtual FileHandle	fileOpen(const XMLCh* path, bool toWrite, MemoryManager* const manager) = 0;
        virtual FileHandle	fileOpen(const char* path, bool toWrite, MemoryManager* const manager) = 0;
        virtual FileHandle	openStdIn(MemoryManager* const manager) = 0;
        
        virtual void		fileClose(FileHandle f, MemoryManager* const manager) = 0;
        virtual void		fileReset(FileHandle f, MemoryManager* const manager) = 0;

        virtual XMLFilePos	curPos(FileHandle f, MemoryManager* const manager) = 0;
        virtual XMLFilePos	fileSize(FileHandle f, MemoryManager* const manager) = 0;

        virtual XMLSize_t	fileRead(FileHandle f, XMLSize_t byteCount, XMLByte* buffer, MemoryManager* const manager) = 0;
        virtual void		fileWrite(FileHandle f, XMLSize_t byteCount, const XMLByte* buffer, MemoryManager* const manager) = 0;
        
        // Ancillary path handling routines
        virtual XMLCh*		getFullPath(const XMLCh* const srcPath, MemoryManager* const manager) = 0;
        virtual XMLCh*		getCurrentDirectory(MemoryManager* const manager) = 0;
        virtual bool		isRelative(const XMLCh* const toCheck, MemoryManager* const manager) = 0;
};

XERCES_CPP_NAMESPACE_END

#endif

