/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: WindowsFileMgr.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_WINDOWSFILEMGR_HPP)
#define XERCESC_INCLUDE_GUARD_WINDOWSFILEMGR_HPP

#include <xercesc/util/XMLFileMgr.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//	Concrete implementation of XMLFileMgr, implementing
//	file access on Windows systems.
class WindowsFileMgr : public XMLFileMgr
{
    public:
        WindowsFileMgr();
        virtual ~WindowsFileMgr();

		// File access
        virtual FileHandle	fileOpen(const XMLCh* path, bool toWrite, MemoryManager* const manager);
        virtual FileHandle	fileOpen(const char* path, bool toWrite, MemoryManager* const manager);
        virtual FileHandle	openStdIn(MemoryManager* const manager);
        
        virtual void		fileClose(FileHandle f, MemoryManager* const manager);
        virtual void		fileReset(FileHandle f, MemoryManager* const manager);

        virtual XMLFilePos	curPos(FileHandle f, MemoryManager* const manager);
        virtual XMLFilePos	fileSize(FileHandle f, MemoryManager* const manager);

        virtual XMLSize_t   fileRead(FileHandle f, XMLSize_t byteCount, XMLByte* buffer, MemoryManager* const manager);
        virtual void		fileWrite(FileHandle f, XMLSize_t byteCount, const XMLByte* buffer, MemoryManager* const manager);
        
        // Ancillary path handling routines
        virtual XMLCh*		getFullPath(const XMLCh* const srcPath, MemoryManager* const manager);
        virtual XMLCh*		getCurrentDirectory(MemoryManager* const manager);
        virtual bool		isRelative(const XMLCh* const toCheck, MemoryManager* const manager);

    private:
        bool _onNT;
};

XERCES_CPP_NAMESPACE_END

#endif

