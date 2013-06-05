/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
