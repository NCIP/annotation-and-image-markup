/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class Term extends AbstractDatabaseEntity implements LexiconTermAttributes {

	private String codeMeaning = Const.DEF_CODE_MEANING;
	private String codeValue = Const.DEF_CODE_VALUE;
	private String description;
	private Integer parentId;
	private Date creationDate;
	private Date modificationDate;
	private int levelNumber;
	private String parentCodeValue;
	
	private Lexicon lexicon;
	
	private int childCount;
	
	private List<Term> terms;
	
	@Override
	public String getCodeMeaning() {
		return codeMeaning;
	}
	
	public void setCodeMeaning(String codeMeaning) {
		this.codeMeaning = codeMeaning;
	}

	@Override
	public String getCodeValue() {
		return codeValue;
	}
	
	public void setCodeValue(String codeValue) {
		this.codeValue = codeValue;
	}
	
	@Override
	public String getSchemaDesignator() {
		return lexicon != null ? lexicon.getSchemaDesignator() : Const.EMPTY;
	}

	@Override
	public String getSchemaVersion() {
		return lexicon != null ? lexicon.getSchemaVersion() : Const.EMPTY;
	}

	public String getDescription() {
		return description;
	}
	
	public void setDescription(String description) {
		this.description = description;
	}
	
	public Integer getParentId() {
		return parentId;
	}
	
	public void setParentId(Integer parentId) {
		this.parentId = parentId;
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

	public Lexicon getLexicon() {
		return lexicon;
	}

	public void setLexicon(Lexicon lexicon) {
		this.lexicon = lexicon;
	}
	
	public int getLevelNumber() {
		return levelNumber;
	}

	public void setLevelNumber(int levelNumber) {
		this.levelNumber = levelNumber;
	}

	public boolean isEmpty() {
		return childCount == 0;
	}

	public void setChildCount(int childCount) {
		this.childCount = childCount;
	}

	public String getParentCodeValue() {
		return parentCodeValue;
	}

	public void setParentCodeValue(String parentCodeValue) {
		this.parentCodeValue = parentCodeValue;
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
		term.setParentId(id);
		term.setLexicon(lexicon);
		this.terms.add(term);
	}

	
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result
				+ ((id == null) ? 0 : id.hashCode());
		result = prime * result + ((lexicon == null) ? 0 : lexicon.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!super.equals(obj))
			return false;
		if (getClass() != obj.getClass())
			return false;
		Term other = (Term) obj;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (lexicon == null) {
			if (other.lexicon != null)
				return false;
		} else if (!lexicon.equals(other.lexicon))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return codeMeaning;
	}
	
}
