/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CHILD_COUNT;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_MEANING;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_VALUE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CREATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.DESCRIPTION;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.ID;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.MODIFICATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.PARENT_ID;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * @author Vitaliy Semeshko
 */
public class TermRowMapper implements RowMapper<Term> {

	@Override
	public Term mapRow(ResultSet rs, int rowNum) throws SQLException {
		Term t = new Term();
		
		t.setId(rs.getInt(ID.field()));
		t.setCodeMeaning(rs.getString(CODE_MEANING.field()));
		t.setCodeValue(rs.getString(CODE_VALUE.field()));
		t.setDescription(rs.getString(DESCRIPTION.field()));
		t.setParentId(rs.getInt(PARENT_ID.field()));
		if (rs.wasNull()) {
			t.setParentId(null);
	    }
		t.setCreationDate(rs.getTimestamp(CREATION_DATE.field()));
		t.setModificationDate(rs.getTimestamp(MODIFICATION_DATE.field()));
		t.setChildCount(rs.getInt(CHILD_COUNT.field()));
		
		return t;
	}
	
}
