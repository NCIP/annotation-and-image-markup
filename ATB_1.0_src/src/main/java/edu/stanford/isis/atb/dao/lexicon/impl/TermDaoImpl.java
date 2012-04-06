/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
