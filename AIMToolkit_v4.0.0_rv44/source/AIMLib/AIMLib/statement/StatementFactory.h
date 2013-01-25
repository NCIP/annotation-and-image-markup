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

#pragma once
#ifndef _AIMLib_StatementFactory_Class_
#define _AIMLib_StatementFactory_Class_

#include <map>
#include <string>

namespace aim_lib
{
	class AIMLIB_API StatementFactory
	{
	public:
		~StatementFactory(void) {};

		static AnnotationStatement* Create(const std::string& stmtClassName);
		static AnnotationStatement* Create(const std::string& stmtSubjectClassName, const std::string& stmtObjectClassName, const std::string& stmtRelationshipClassName);

	protected:
		typedef std::map<std::string, AnnotationStatement::InstanceCreator> StmtFactoryMap;
		typedef std::map<std::string, std::string> StmtAliasMap;

		static bool InitializeFactory();

		static bool IsInitialized();
		// Maps statement class name to class initializer
		static StmtFactoryMap& GetStatementFactoryMap();
		// Maps class Subject+Relationship+Object names to class name for each statement class
		static StmtAliasMap& GetStatementAliasMap();

	private:
		StatementFactory(void){};
	};
}
#endif // _AIMLib_StatementFactory_Class_
