/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon.impl;

import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_MEANING;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CODE_VALUE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.CREATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.DESCRIPTION;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.ID;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.MODIFICATION_DATE;
import static edu.stanford.isis.atb.dao.lexicon.impl.SchemaInfo.TermField.PARENT_ID;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.DELETE;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.FIND;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.INSERT;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.SELECT_BY_LEXICON;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.SELECT_PARENT;
import static edu.stanford.isis.atb.dao.lexicon.impl.TermQueries.UPDATE;

import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

import edu.stanford.isis.atb.dao.lexicon.TermDao;
import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * @author Vitaliy Semeshko
 */

@Repository
public class TermDaoImpl implements TermDao {

	private NamedParameterJdbcTemplate jdbc;

	private TermRowMapper rowMapper = new TermRowMapper();
	
	@Override
	public Collection<Term> getAllTop(String termTable) {
		return jdbc.getJdbcOperations().query(SELECT_BY_LEXICON.prepare(termTable), rowMapper);
	}

	@Override
	public Collection<Term> getForExport(String termTable, int limitFrom, int limitSize) {
		Map<String, Object> params = new HashMap<String, Object>();
		params.put(SchemaInfo.PARAMS.LIMIT_FROM.param(), limitFrom);
		params.put(SchemaInfo.PARAMS.LIMIT_SIZE.param(), limitSize);
		return jdbc.query(TermQueries.SELECT_ALL_BY_RANGE.prepare(termTable), params, new ExportTermRowMapper());
	}

	@Override
	public int getTermCount(String termTable) {
		return jdbc.getJdbcOperations().queryForInt(TermQueries.COUNT.prepare(termTable));
	}

	@Override
	public Collection<Term> find(String searchText, String termTable) {
		Map<String, Object> params = new HashMap<String, Object>();
		params.put(CODE_MEANING.field(), "%" + searchText + "%");
		return jdbc.query(FIND.prepare(termTable), params, rowMapper);
	}

	@Override
	public Collection<Term> getChildren(Term parent) {
		String termTable = parent.getLexicon().getTermTable();
		return jdbc.query(TermQueries.SELECT_BY_PARENT.prepare(termTable), asParameters(parent), rowMapper);
	}

	@Override
	public void insert(Term term) {
		term.setCreationDate(new Date());
		KeyHolder keyHolder = new GeneratedKeyHolder();
		jdbc.update(INSERT.prepare(term.getLexicon().getTermTable()), asParameters(term), keyHolder);
		term.setId(keyHolder.getKey().intValue());
	}

	@Override
	public void update(Term term) {
		// set modification date only for initialized terms
		// avoid setting modification date after first editing (which is actually creating)
		if (term.isInitialized()) {
			term.setModificationDate(new Date());
		}
		jdbc.update(UPDATE.prepare(term.getLexicon().getTermTable()), asParameters(term));
	}
	
	@Override
	public void delete(Term term) {
		// delete children first
		Collection<Term> children = getChildren(term);
		
		for (Term child : children) {
			child.setLexicon(term.getLexicon());
			delete(child);
		}
		
		jdbc.getJdbcOperations().update(DELETE.prepare(term.getLexicon().getTermTable()), term.getId());
	}
	
	@Override
	public void dropTermTable(String termTable) {
		jdbc.getJdbcOperations().execute(TermQueries.DROP_TABLE.prepare(termTable));
	}

	@Override
	public Term getParent(Term term) {
		List<Term> terms = jdbc.query(SELECT_PARENT.prepare(term.getLexicon().getTermTable()), 
				asParameters(term), rowMapper);
		return terms.isEmpty() ? null : terms.get(0);
	}

	private SqlParameterSource asParameters(Term term) {
		MapSqlParameterSource map = new MapSqlParameterSource();

		map.addValue(ID.field(), term.getId());
		map.addValue(CODE_MEANING.field(), term.getCodeMeaning());
		map.addValue(CODE_VALUE.field(), term.getCodeValue());
		map.addValue(DESCRIPTION.field(), term.getDescription());
		map.addValue(PARENT_ID.field(), term.getParentId());
		map.addValue(CREATION_DATE.field(), term.getCreationDate());
		map.addValue(MODIFICATION_DATE.field(), term.getModificationDate());

		return map;
	}

	@Autowired
	public void setDataSource(DataSource dataSource) {
		jdbc = new NamedParameterJdbcTemplate(dataSource);
	}

}
