/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/ofstd/ofstack.h"
#include "dcmtk/ofstd/ofconsol.h"


int main()
{
    OFStack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);

    OFStack<int> nst(st);
    COUT << "Output of number of Elements in st: " << st.size() << OFendl;
    COUT << "Output and deletion of st: ";
    while(!st.empty())
    {
	COUT << st.top() << " ";
	st.pop();
    }
    COUT << OFendl;

    COUT << "Output of number of Elements in copy from st: " << nst.size() << OFendl;
    COUT << "Output and deletion of copy from st: ";
    while(!nst.empty())
    {
	COUT << nst.top() << " ";
	nst.pop();
    }
    COUT << OFendl;
}


/*
**
** CVS/RCS Log:
** $Log: tststack.cc,v $
** Revision 1.11  2010-10-14 13:15:16  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.10  2006/08/14 16:42:48  meichel
** Updated all code in module ofstd to correctly compile if the standard
**   namespace has not included into the global one with a "using" directive.
**
** Revision 1.9  2005/12/08 15:49:11  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.8  2004/01/16 10:37:23  joergr
** Removed acknowledgements with e-mail addresses from CVS log.
**
** Revision 1.7  2002/04/16 13:37:01  joergr
** Added configurable support for C++ ANSI standard includes (e.g. streams).
**
** Revision 1.6  2001/06/01 15:51:41  meichel
** Updated copyright header
**
** Revision 1.5  2000/03/08 16:36:08  meichel
** Updated copyright header.
**
** Revision 1.4  2000/03/03 14:02:53  meichel
** Implemented library support for redirecting error messages into memory
**   instead of printing them to stdout/stderr for GUI applications.
**
** Revision 1.3  1998/11/27 12:42:11  joergr
** Added copyright message to source files and changed CVS header.
**
**
**
*/
