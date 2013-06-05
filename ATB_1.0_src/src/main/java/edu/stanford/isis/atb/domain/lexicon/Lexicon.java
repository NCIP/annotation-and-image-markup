/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.lexicon;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.List;

/**
 * @author Vitaliy Semeshko
 */
public class Lexicon extends AbstractDatabaseEntity {

	private String name;
	private String schemaDesignator;
	private String schemaVersion;
	private String description;
	private String authors;
	private boolean readOnly;
	private Date creationDate;
	private Date modificationDate;
	private String termTable;
	private int termCount;
	
	private List<Term> terms;
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getSchemaDesignator() {
		return schemaDesignator;
	}

	public void setSchemaDesignator(String schemaDesignator) {
		this.schemaDesignator = schemaDesignator;
	}

	public String getSchemaVersion() {
		return schemaVersion;
	}

	public void setSchemaVersion(String schemaVersion) {
		this.schemaVersion = schemaVersion;
	}

	public String getDescription() {
		return description;
	}
	
	public void setDescription(String description) {
		this.description = description;
	}
	
	public String getAuthors() {
		return authors;
	}
	
	public void setAuthors(String authors) {
		this.authors = authors;
	}
	
	public boolean isReadOnly() {
		return readOnly;
	}
	
	public void setReadOnly(boolean readOnly) {
		this.readOnly = readOnly;
	}
	
	public Date getCreationDate() {
		return creationDate;
	}
	
	public void setCreationDate(Date creationDate) {
		this.creationDate = creationDate;
	}
	
	public Date getModificationDate() {
		return modificationDate;
	}

	public void setModificationDate(Date modificationDate) {
		this.modificationDate = modificationDate;
	}

	public String getTermTable() {
		return termTable;
	}
	
	public void setTermTable(String termTable) {
		this.termTable = termTable;
	}
	
	public int getTermCount() {
		return termCount;
	}

	public void setTermCount(int termCount) {
		this.termCount = termCount;
	}

	public Collection<Term> getTerms() {
		if (terms == null) {
			return Collections.emptyList();
		}
		return terms; 
	}
	
	public void addTerms(Collection<Term> terms) {
		for (Term term : terms) {
			addTerm(term);
		}
	}
	
	public void addTerm(Term term) {
		if (this.terms == null) {
			this.terms = new ArrayList<Term>();
		}
		term.setLexicon(this);
		terms.add(term);
	}
	
	public void clearTerms() {
		if (terms != null) {
			terms.clear();
		}
	}

	@Override
	public String toString() {
		return name;
	}
	
}
