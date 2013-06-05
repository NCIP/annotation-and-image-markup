/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

/**
 * @author Vitaliy Semeshko
 */
public enum LexiconQueries {

	SELECT_ALL("SELECT * FROM LEXICON ORDER BY NAME"),
	
	INSERT("INSERT INTO LEXICON (" +
			"NAME," +
			"SCHEMA_DESIGNATOR," +
			"SCHEMA_VERSION," +
			"DESCRIPTION," +
			"AUTHORS," +
			"READ_ONLY," +
			"CREATION_DATE," +
			"TERM_TABLE) " +
			"VALUES (" +
			":NAME, " +
			":SCHEMA_DESIGNATOR, " +
			":SCHEMA_VERSION, " +
			":DESCRIPTION, :AUTHORS, " +
			"'FALSE', " +
			":CREATION_DATE, " +
			":TERM_TABLE);"),
	
	UPDATE("UPDATE LEXICON SET " +
			"NAME = :NAME," +
			"SCHEMA_DESIGNATOR = :SCHEMA_DESIGNATOR," +
			"SCHEMA_VERSION = :SCHEMA_VERSION," +
			"DESCRIPTION = :DESCRIPTION," +
			"AUTHORS = :AUTHORS," +
			"MODIFICATION_DATE = :MODIFICATION_DATE " +
			"WHERE ID = :ID;"),
			
	DELETE("DELETE FROM LEXICON WHERE ID = ?");
	
	private String text;
	
	private LexiconQueries(String text) {
		this.text = text;
	}
	
	public String prepare() {
		return text;
	}
	
}
