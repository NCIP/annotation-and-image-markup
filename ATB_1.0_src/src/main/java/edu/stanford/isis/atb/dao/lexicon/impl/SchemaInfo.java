/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

/**
 * @author Vitaliy Semeshko
 */
public class SchemaInfo {

	public static final String LEXICON_TABLE_NAME = "LEXICON";
	
	public static enum LexiconField {
		ID,
		NAME,
		SCHEMA_DESIGNATOR,
		SCHEMA_VERSION,
		DESCRIPTION,
		AUTHORS,
		READ_ONLY,
		CREATION_DATE,
		MODIFICATION_DATE,
		TERM_TABLE;
		
		public String field() {
			return toString();
		}
	}
	
	public static enum TermField {
		ID,
		CODE_MEANING,
		CODE_VALUE,
		DESCRIPTION,
		PARENT_ID,
		CREATION_DATE,
		MODIFICATION_DATE,
		CHILD_COUNT,
		PARENT_CODE_VALUE;

		public String field() {
			return toString();
		}
	}
	
	public static enum PARAMS {
		LIMIT_FROM,
		LIMIT_SIZE;
		
		public String param() {
			return toString();
		}
	}
	
}
