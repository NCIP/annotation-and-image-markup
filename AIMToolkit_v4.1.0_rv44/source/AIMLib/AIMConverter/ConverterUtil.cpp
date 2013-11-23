/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
