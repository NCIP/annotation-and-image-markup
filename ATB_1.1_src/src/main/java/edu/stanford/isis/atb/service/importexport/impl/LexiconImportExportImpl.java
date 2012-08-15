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
