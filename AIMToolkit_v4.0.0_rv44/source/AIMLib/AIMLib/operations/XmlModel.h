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

#if !defined(_AIMLib_XmlModel_Class)
#define _AIMLib_XmlModel_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API XmlModel : public BaseModel
	{
	public:
		XmlModel(void);
		~XmlModel(void);

		// Write to XML file
		void WriteAnnotationCollectionToFile(const AnnotationCollection* pAnnotationCollection, const std::string& fileName);

		// Write xml to char buffer
		std::string::size_type WriteAnnotationCollectionToXmlString(const AnnotationCollection* pAnnotationCollection, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize);

		// Read from XML file
		AnnotationCollection* ReadAnnotationCollectionFromFile(const std::string& fileName);
		AnnotationCollection* ReadAnnotationCollectionFromXmlString(const std::string& xmlIn);

	protected:
		std::string _xmlFileName;
	};
}

#endif // _AIMLib_XmlModel_Class