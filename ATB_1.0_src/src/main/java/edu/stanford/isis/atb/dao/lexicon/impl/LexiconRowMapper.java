/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.AUTHORS;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.CREATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.DESCRIPTION;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.ID;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.MODIFICATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.NAME;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.READ_ONLY;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.SCHEMA_DESIGNATOR;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.SCHEMA_VERSION;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.LexiconField.TERM_TABLE;

import java.sql.ResultSet;
import java.sql.SQLException;

import org.springframework.jdbc.core.RowMapper;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconRowMapper implements RowMapper<Lexicon> {

	@Override
	public Lexicon mapRow(ResultSet rs, int rowNum) throws SQLException {
		Lexicon lex = new Lexicon();
		
		lex.setId(rs.getInt(ID.field()));
		lex.setName(rs.getString(NAME.field()));
		lex.setSchemaDesignator(rs.getString(SCHEMA_DESIGNATOR.field()));
		lex.setSchemaVersion(rs.getString(SCHEMA_VERSION.field()));
		lex.setDescription(rs.getString(DESCRIPTION.field()));
		lex.setAuthors(rs.getString(AUTHORS.field()));
		lex.setReadOnly(rs.getBoolean(READ_ONLY.field()));
		lex.setCreationDate(rs.getTimestamp(CREATION_DATE.field()));
		lex.setModificationDate(rs.getTimestamp(MODIFICATION_DATE.field()));
		lex.setTermTable(rs.getString(TERM_TABLE.field()));
		
		return lex;
	}

}
