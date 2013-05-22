/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcfilter.h"


class DcmAttributeFilter::SingleValueFilter : public FilterInterface
{
public:
    SingleValueFilter( const OFString& value )
    : m_Value( value )
    {

    }

    virtual OFBool apply( const OFString& value )
    {
        return m_Value == value;
    }

private:
    const OFString m_Value;
};

DcmAttributeFilter::DcmAttributeFilter()
: m_Tag(), m_pFilter( NULL )
{

}

DcmAttributeFilter::DcmAttributeFilter( const DcmTagKey& tag, const OFString& value )
: m_Tag( tag ), m_pFilter( new SingleValueFilter( value ) )
{

}

DcmAttributeFilter::DcmAttributeFilter( const DcmTagKey& tag, const char* const value )
: m_Tag( tag ), m_pFilter( new SingleValueFilter( value ) )
{

}

DcmAttributeFilter::~DcmAttributeFilter()
{
    delete m_pFilter;
}

OFBool DcmAttributeFilter::apply( DcmItem& item ) const
{
    if( m_pFilter )
    {
        OFString value;
        return item.findAndGetOFStringArray( m_Tag, value ).good()
            && m_pFilter->apply( value );
    }
    else return true;
}

OFBool DcmAttributeFilter::operator()( DcmItem& item ) const
{
    return apply( item );
}

OFBool DcmAttributeFilter::apply( DcmFileFormat& dcmfile ) const
{
    DcmDataset* const dataset = dcmfile.getDataset();
    return dataset && apply( *dataset );
}

OFBool DcmAttributeFilter::operator()( DcmFileFormat& dcmfile ) const
{
    return apply( dcmfile );
}
