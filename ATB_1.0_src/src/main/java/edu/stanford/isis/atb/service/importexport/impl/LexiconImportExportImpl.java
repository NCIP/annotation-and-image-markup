/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.importexport.impl;

import static au.com.bytecode.opencsv.CSVWriter.NO_QUOTE_CHARACTER;
import static edu.stanford.isis.atb.ui.Const.FMT_DATE_TIME_WITH_SECONDS;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.text.SimpleDateFormat;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.transaction.interceptor.TransactionInterceptor;

import au.com.bytecode.opencsv.CSVReader;
import au.com.bytecode.opencsv.CSVWriter;
import edu.stanford.isis.atb.dao.lexicon.LexiconDao;
import edu.stanford.isis.atb.dao.lexicon.TermDao;
import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.WatchingCallback;
import edu.stanford.isis.atb.service.importexport.LexiconImportExport;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */

@Service
public class LexiconImportExportImpl implements LexiconImportExport {
	
	private static final char CSV_SEPARATOR = '\t';
	private static final Charset UTF_8 = Charset.forName("UTF-8");
	private static int EXPORT_BATCH_SIZE = 500;
	private static int IMPORT_BATCH_SIZE = 500;
	
	private String[] header = {"Code Meaning", "Code Value", "Coding Scheme Designator", "Description", "Parent"};
	
	@Autowired
	private LexiconDao lexiconDao;
	
	@Autowired
	private TermDao termDao;
	
	@Transactional
	@Override
	public void importFromCsv(String name, InputStream in, WatchingCallback<Lexicon> callback) {
		Date date = new Date();
		name = name + " " + new SimpleDateFormat(FMT_DATE_TIME_WITH_SECONDS).format(date);
		
		Map<String, Term> terms = new HashMap<String, Term>();
		
		Lexicon lexicon = new Lexicon();
		lexicon.setName(name);
		lexicon.setReadOnly(false);
		lexicon.setCreationDate(date);
		
		CSVReader reader = new CSVReader(new InputStreamReader(in), CSV_SEPARATOR);
		
		int line = -1;
		
		try {
			String [] nextLine;
			while ((nextLine = reader.readNext()) != null) {
				// skip heading line
				if (line == -1) {
					line++;
					continue;
				}
				
				line++;

				if (nextLine.length < 4) {
					throw new ATBException("File is not correct.");
				}
				
				Term term = new Term();
				term.setInitialized(false);
				term.setLexicon(lexicon);
				term.setCodeMeaning(nextLine[0]);
				term.setCodeValue(nextLine[1]);
				term.setDescription(nextLine[3]);
				term.setCreationDate(date);
				
				String schemaDesignator = nextLine[2];
				if (nextLine.length == 5) {
					term.setParentCodeValue(nextLine[4]);
				}
				
				// insert lexicon
				if (lexicon.getId() == null) {
					lexicon.setSchemaDesignator(schemaDesignator);
					lexiconDao.insert(lexicon);
				}
				
				termDao.insert(term);
				
				// add to terms map
				terms.put(term.getCodeValue(), term);
				
				if ((line % IMPORT_BATCH_SIZE) == 0) {
					callback.notifyStatus(String.format(Const.MSG_IMPORTED_TERMS, line));
				}
				
				// if manually interrupted
				if (callback.isCancelled()) {
					// rollback transaction
					TransactionInterceptor.currentTransactionStatus().setRollbackOnly();
					callback.notifyCancelled();
					return;
				}
			}
		} catch (Exception e) {
			throw new ATBException("Failed processing line: " + (line + 1), e);
		}
		
		// handle relations
		if (line > 0) {
			for (Term term : terms.values()) {
				if (StringUtils.isEmpty(term.getParentCodeValue())) {
					continue;
				}
				
				Term parent = terms.get(term.getParentCodeValue());

				if (parent != null) {
					Integer parentId = parent.getId();
					if (parentId != null) {
						term.setParentId(parentId);
						termDao.update(term);
					}
				}
				
				// if manually interrupted
				if (callback.isCancelled()) {
					// rollback transaction
					TransactionInterceptor.currentTransactionStatus().setRollbackOnly();
					callback.notifyCancelled();
					return;
				}
			}
		}
		
		if ((line % IMPORT_BATCH_SIZE) != 0) {
			callback.notifyStatus(String.format(Const.MSG_IMPORTED_TERMS, line));
		}
		
		callback.onSuccess(lexicon);
	}

	@Override
	public void exportToCsv(Lexicon lexicon, OutputStream out, WatchingCallback<Void> callback) {
		CSVWriter writer = new CSVWriter(new OutputStreamWriter(out, UTF_8), CSV_SEPARATOR, NO_QUOTE_CHARACTER);
		
		try {
			// write header
			writer.writeNext(header);
			
			int exportedTerms = 0;
			for (int i = 0; i < Integer.MAX_VALUE; i++) {
				Collection<Term> terms = termDao.getForExport(lexicon.getTermTable(), i * EXPORT_BATCH_SIZE, EXPORT_BATCH_SIZE);
				
				for (Term term : terms) {
					exportTerm(writer, term, lexicon.getSchemaDesignator());
					exportedTerms++;
				}
				
				callback.notifyStatus(String.format(Const.MSG_EXPORTED_TERMS, exportedTerms));
				
				// if manually interrupted or nothing left in table, break the loop
				if (callback.isCancelled()) {
					callback.notifyCancelled();
					break;
				} else if (CollectionUtils.isEmpty(terms) || terms.size() < EXPORT_BATCH_SIZE) {
					callback.onSuccess(null);
					break;
				}
			}
		} catch (Exception e) {
			throw new ATBException(e);
		} finally {
			closeWriterQuietly(writer);
		}
	}
	
	private void exportTerm(CSVWriter writer, Term term, String schemaDesignator) throws IOException {
		String[] data = new String[] {term.getCodeMeaning(), term.getCodeValue(), 
				schemaDesignator, term.getDescription(), term.getParentCodeValue()};
		writer.writeNext(data);
		writer.flush();
	}
	
	private void closeWriterQuietly(CSVWriter writer) {
		try {
			if (writer != null) {
				writer.flush();
				writer.close();
			}
		} catch (IOException e) {
			// ignore
		}
	}
	
}
