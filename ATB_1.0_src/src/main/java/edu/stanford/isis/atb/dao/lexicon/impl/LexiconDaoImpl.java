/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

import static edu.stanford.isis.atb.dao.lexicon.impl.LexiconQueries.INSERT;
import static edu.stanford.isis.atb.dao.lexicon.impl.LexiconQueries.SELECT_ALL;
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

import java.util.Collection;
import java.util.Date;
import java.util.UUID;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

import edu.stanford.isis.atb.dao.lexicon.LexiconDao;
import edu.stanford.isis.atb.domain.lexicon.Lexicon;

/**
 * @author Vitaliy Semeshko
 */

@Repository
public class LexiconDaoImpl implements LexiconDao {

	private NamedParameterJdbcTemplate jdbc;

	@Override
	public Collection<Lexicon> getAll() {
		return jdbc.getJdbcOperations().query(SELECT_ALL.prepare(), new LexiconRowMapper());
	}

	@Override
	public void insert(Lexicon lexicon) {
		// create table for terms
		String termTableName = "T" + UUID.randomUUID().toString().replaceAll("-", "_").toUpperCase();
		jdbc.getJdbcOperations().execute(TermQueries.CREATE_TABLE.prepare(termTableName));

		// insert lexicon
		lexicon.setTermTable(termTableName);
		Date creationDate = lexicon.getCreationDate();
		lexicon.setCreationDate(creationDate == null ? new Date() : creationDate);
		KeyHolder keyHolder = new GeneratedKeyHolder();
		jdbc.update(INSERT.prepare(), asParameters(lexicon), keyHolder);
		lexicon.setId(keyHolder.getKey().intValue());
	}

	@Override
	public void update(Lexicon lexicon) {
		lexicon.setModificationDate(new Date());
		jdbc.update(LexiconQueries.UPDATE.prepare(), asParameters(lexicon));
	}

	@Override
	public void delete(Integer id) {
		jdbc.getJdbcOperations().update(LexiconQueries.DELETE.prepare(), id);
	}

	private SqlParameterSource asParameters(Lexicon lexicon) {
		MapSqlParameterSource map = new MapSqlParameterSource();

		map.addValue(ID.field(), lexicon.getId());
		map.addValue(NAME.field(), lexicon.getName());
		map.addValue(SCHEMA_DESIGNATOR.field(), lexicon.getSchemaDesignator());
		map.addValue(SCHEMA_VERSION.field(), lexicon.getSchemaVersion());
		map.addValue(DESCRIPTION.field(), lexicon.getDescription());
		map.addValue(AUTHORS.field(), lexicon.getAuthors());
		map.addValue(READ_ONLY.field(), lexicon.isReadOnly());
		map.addValue(CREATION_DATE.field(), lexicon.getCreationDate());
		map.addValue(MODIFICATION_DATE.field(), lexicon.getModificationDate());
		map.addValue(TERM_TABLE.field(), lexicon.getTermTable());

		return map;
	}

	@Autowired
	public void setDataSource(DataSource dataSource) {
		jdbc = new NamedParameterJdbcTemplate(dataSource);
	}

}
