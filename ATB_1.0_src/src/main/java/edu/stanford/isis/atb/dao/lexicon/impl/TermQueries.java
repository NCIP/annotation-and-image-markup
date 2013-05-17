/*
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
public enum TermQueries {

	CREATE_TABLE("CREATE TABLE {table} (" +
			"ID INT AUTO_INCREMENT PRIMARY KEY," +
			"CODE_MEANING VARCHAR(255) NOT NULL," +
			"CODE_VALUE VARCHAR(100) NOT NULL," +
			"DESCRIPTION TEXT," +
			"PARENT_ID INT," +
			"CREATION_DATE TIMESTAMP NOT NULL," +
			"MODIFICATION_DATE TIMESTAMP); " +
			"CREATE INDEX IDX_CODE_MEANING_DESC_{table} ON {table} (CODE_MEANING DESC);" +
			"CREATE INDEX IDX_PARENT_ID_DESC_{table} ON {table} (PARENT_ID ASC NULLS FIRST);"),
			
	SELECT_BY_LEXICON(
			"SELECT t.*, " +
				"(SELECT COUNT(*) from {table} p WHERE p.PARENT_ID = t.ID) CHILD_COUNT " +
			"FROM {table} t " +
			"WHERE t.PARENT_ID IS NULL " +
			"ORDER BY ID"),
	
	SELECT_ALL_BY_RANGE(
			"SELECT t.*, tp.CODE_VALUE PARENT_CODE_VALUE " +
			"FROM {table} t " +
			"LEFT JOIN {table} tp on tp.ID = t.PARENT_ID " +
			"LIMIT :LIMIT_FROM, :LIMIT_SIZE"),
	
	COUNT(
			"SELECT COUNT(*) from {table}"),
	
	FIND(
			"SELECT t.*, " +
				"(SELECT COUNT(*) from {table} p WHERE p.PARENT_ID = t.ID) CHILD_COUNT " +
			"FROM {table} t " +
			"WHERE UPPER(t.CODE_MEANING) LIKE UPPER(:CODE_MEANING) " +
			"ORDER BY ID"),
	
	SELECT_BY_PARENT(
			"SELECT t.*, " +
				"(SELECT COUNT(*) from {table} p WHERE p.PARENT_ID = t.ID) CHILD_COUNT " +
			"FROM {table} t " +
			"WHERE t.PARENT_ID = :ID " +
			"ORDER BY ID"),
	
	SELECT_PARENT(
			"SELECT t.*, " +
				"(SELECT COUNT(*) from {table} p WHERE p.PARENT_ID = t.ID) CHILD_COUNT " +
			"FROM {table} t " +
			"WHERE t.ID = :PARENT_ID"),
	
	INSERT("INSERT INTO {table} (" +
			"CODE_MEANING," +
			"CODE_VALUE," +
			"DESCRIPTION," +
			"PARENT_ID," +
			"CREATION_DATE) " +
			"VALUES (" +
			":CODE_MEANING, " +
			":CODE_VALUE, " +
			":DESCRIPTION, " +
			":PARENT_ID, " +
			":CREATION_DATE);"),
			
	UPDATE("UPDATE {table} SET " +
			"CODE_MEANING = :CODE_MEANING," +
			"CODE_VALUE = :CODE_VALUE," +
			"DESCRIPTION = :DESCRIPTION," +
			"PARENT_ID = :PARENT_ID," +
			"MODIFICATION_DATE = :MODIFICATION_DATE " +
			"WHERE ID = :ID;"),
			
	DELETE("DELETE FROM {table} WHERE ID = ?"),
	
	DROP_TABLE("DROP TABLE {table}");
	
	private String text;
	
	private TermQueries(String text) {
		this.text = text;
	}
	
	public String prepare(String tableName) {
		return text.replaceAll("\\{table\\}", tableName);
	}
	
}
