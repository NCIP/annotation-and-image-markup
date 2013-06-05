/*L
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/


#include "ConverterUtil.h"

using namespace std;


ConverterUtil::ConverterUtil(void)
{
}

ConverterUtil::~ConverterUtil(void)
{
}

int ConverterUtil::nocase_cmp(const string & s1, const string& s2)
{
	string::const_iterator it1=s1.begin();
	string::const_iterator it2=s2.begin();

	//has the end of at least one of the strings been reached?
	while ( (it1!=s1.end()) && (it2!=s2.end()) )
	{
		if(::toupper(*it1) != ::toupper(*it2)) //letters differ?
			// return -1 to indicate 'smaller than', 1 otherwise
			return (::toupper(*it1) < ::toupper(*it2)) ? -1 : 1;
		//proceed to the next character in each string
		++it1;
		++it2;
	}
	size_t size1=s1.size(), size2=s2.size();// cache lengths
	//return -1,0 or 1 according to strings' lengths
	if (size1==size2)
		return 0;
	return (size1<size2) ? -1 : 1;
}
