/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_MEANING;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_VALUE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.DESCRIPTION;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.ID;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.PARENT_CODE_VALUE;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * @author Vitaliy Semeshko
 */
public class ExportTermRowMapper implements RowMapper<Term> {

	@Override
	public Term mapRow(ResultSet rs, int rowNum) throws SQLException {
		Term t = new Term();
		
		t.setId(rs.getInt(ID.field()));
		t.setCodeMeaning(rs.getString(CODE_MEANING.field()));
		t.setCodeValue(rs.getString(CODE_VALUE.field()));
		t.setDescription(rs.getString(DESCRIPTION.field()));
		t.setParentCodeValue(rs.getString(PARENT_CODE_VALUE.field()));
		
		return t;
	}
	
}
