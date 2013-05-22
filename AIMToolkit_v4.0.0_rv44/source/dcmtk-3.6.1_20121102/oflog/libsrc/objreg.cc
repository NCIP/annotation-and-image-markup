/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/spi/objreg.h"

using namespace std;
using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::spi;


///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::spi::ObjectRegistryBase ctor and dtor
///////////////////////////////////////////////////////////////////////////////

ObjectRegistryBase::ObjectRegistryBase()
 : mutex(DCMTK_LOG4CPLUS_MUTEX_CREATE)
{
}


ObjectRegistryBase::~ObjectRegistryBase()
{
    DCMTK_LOG4CPLUS_MUTEX_FREE( mutex );
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::spi::ObjectRegistryBase public methods
///////////////////////////////////////////////////////////////////////////////

bool
ObjectRegistryBase::exists(const tstring& name) const
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        return data.find(name) != data.end();
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


OFList<tstring>
ObjectRegistryBase::getAllNames() const
{
    OFList<tstring> tmp;
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        for(ObjectMap::const_iterator it=data.begin(); it!=data.end(); ++it)
            tmp.push_back( (*it).first );
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
    return tmp;
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::spi::ObjectRegistryBase protected methods
///////////////////////////////////////////////////////////////////////////////

bool
ObjectRegistryBase::putVal(const tstring& name, void* object)
{
    ObjectMap::value_type value(name, object);
    OFPair<ObjectMap::iterator, bool> ret;

    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        ret = data.insert(value);
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;

    if (! ret.second)
        deleteObject( value.second );
    return ret.second;
}


void*
ObjectRegistryBase::getVal(const tstring& name) const
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        ObjectMap::const_iterator it (data.find (name));
        if (it != data.end ())
            return it->second;
        else
            return 0;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}




void
ObjectRegistryBase::clear()
{
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
    for(ObjectMap::iterator it=data.begin(); it!=data.end(); ++it) {
        deleteObject( (*it).second );
    }
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}
