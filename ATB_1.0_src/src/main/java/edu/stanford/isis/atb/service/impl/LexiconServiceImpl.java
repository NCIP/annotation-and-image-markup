/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.impl;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.io.FilenameUtils;
import org.apache.commons.io.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import edu.stanford.isis.atb.dao.lexicon.LexiconDao;
import edu.stanford.isis.atb.dao.lexicon.TermDao;
import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.LexiconService;
import edu.stanford.isis.atb.service.WatchingCallback;
import edu.stanford.isis.atb.service.importexport.LexiconImportExport;

/**
 * @author Vitaliy Semeshko
 */

@Service
public class LexiconServiceImpl extends AbstractService implements LexiconService {

	private static final String WHOLE_WORD_PATTERN_TEMPLATE = ".*\\b%s\\b.*";
	
	@Autowired
	private LexiconDao lexiconDao;
	
	@Autowired
	private TermDao termDao;

	@Autowired
	private LexiconImportExport lexiconExporter;
	
	@Override
	public Collection<Lexicon> getLexicons() {
		Collection<Lexicon> lexicons = lexiconDao.getAll();
		// enrich with term count
		for (Lexicon lexicon : lexicons) {
			lexicon.setTermCount(termDao.getTermCount(lexicon.getTermTable()));
		}
		return lexicons;
	}

	@Override
	public void saveOrUpdateLexicon(Lexicon lexicon) {
		if (lexicon.getId() == null) {
			lexiconDao.insert(lexicon);
		} else {
			lexiconDao.update(lexicon);
		}
	}

	@Transactional
	@Override
	public void deleteLexicon(Lexicon lexicon) {
		lexiconDao.delete(lexicon.getId());
		termDao.dropTermTable(lexicon.getTermTable());
	}

	@Override
	public void getTerms(Lexicon lexicon) {
		Collection<Term> terms = termDao.getAllTop(lexicon.getTermTable());
		
		for (Term term : terms) {
			term.setLevelNumber(2);
		}
		
		lexicon.clearTerms();
		lexicon.addTerms(terms);
	}

	@Override
	public Collection<Term> findTerms(String searchText, Lexicon lexicon, boolean exactMatch) {
		Collection<Term> result = termDao.find(searchText, lexicon.getTermTable()); 
		if (exactMatch) {
			Pattern p = Pattern.compile(String.format(WHOLE_WORD_PATTERN_TEMPLATE, searchText));
			List<Term> filtered = new ArrayList<Term>();
			for (Term term : result) {
				Matcher m = p.matcher(term.getCodeMeaning());
				if (m.matches()) {
					filtered.add(term);
				}
			}
			return filtered;
		} else {
			return result;
		}
	}

	@Override
	public Collection<Term> getChildTerms(Term parent) {
		Collection<Term> terms = termDao.getChildren(parent);
		
		int levelNumber = parent.getLevelNumber() + 1;
		for (Term term : terms) {
			term.setLevelNumber(levelNumber);
		}
		
		return terms;
	}

	@Override
	public void saveOrUpdateTerm(Term term) {
		if (term.getId() == null) {
			termDao.insert(term);
		} else {
			termDao.update(term);
		}
	}
	
	@Override
	public void deleteTerm(Term term) {
		termDao.delete(term);
	}

	@Override
	public Term getPathToTheRoot(Term term) {
		return linkToParent(term);
	}
	
	@Override
	public void importFromCsv(final File path, final WatchingCallback<Lexicon> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				InputStream in = null;
				try {
					String name = FilenameUtils.removeExtension(path.getName());
					lexiconExporter.importFromCsv(name, in = new FileInputStream(path), callback);
				} catch (Exception e) {
					callback.onFailure(e);
				} finally {
					IOUtils.closeQuietly(in);
				}
			}
		});
	}

	@Override
	public void exportToCsv(final Lexicon lexicon, final File path, final WatchingCallback<Void> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				OutputStream out = null;
				try {
					lexiconExporter.exportToCsv(lexicon, out = new FileOutputStream(path), callback);
				} catch (Exception e) {
					callback.onFailure(e);
				} finally {
					IOUtils.closeQuietly(out);
				}
			}
		});
	}

	private Term linkToParent(Term term) {
		Term parent = termDao.getParent(term);
		if (parent != null) {
			parent.setLexicon(term.getLexicon());
			parent.addTerm(term);
			term = linkToParent(parent);
		}
		
		return term; 
	}
	
}
