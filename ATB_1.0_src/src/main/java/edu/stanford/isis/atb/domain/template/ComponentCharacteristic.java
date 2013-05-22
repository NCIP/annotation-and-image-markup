/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.validation.Valid;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(strict=false)
public abstract class ComponentCharacteristic extends AbstractRemovableElement {

	@NotEmpty(message = "{componentCharacteristic.label.notEmpty}")
	@Attribute(required=false)
	private String label;
	
	@Attribute(required=false)
	private int itemNumber;
	
	@Attribute(required=false)
	private String authors;
	
	@Attribute(required=false)
	private String explanatoryText;
	
	@Attribute(required=false)
	private long minCardinality;
	
	@Attribute(required=false)
	private long maxCardinality;
	
	@Attribute(required=false)
	private boolean shouldDisplay;

	@Attribute(required=false)
	private String groupLabel;

	@Valid
	@NotEmpty(message = "{componentCharacteristic.allowedTerms.notEmpty}")
	@ElementList(name="AllowedTerm", inline=true, required=false)
	private List<AllowedTermWithQuantification> allowedTerms;
	
	@Valid
	@Element(name="QuestionType", required=false)
	private QuestionType questionType;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (allowedTerms != null) {
			for (AllowedTermWithQuantification allowedTerm : allowedTerms) {
				allowedTerm.initRemoveCommand(allowedTerms);
				allowedTerm.initContext(allowedTerms);
			}
		}
		
		if (questionType != null) {
			questionType.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					questionType = null;
				}
			});
		}
		
		afterDescendantPropertiesSet();
	}
	
	protected void afterDescendantPropertiesSet() {}
	
	public String getLabel() {
		return label;
	}

	public void setLabel(String label) {
		this.label = label;
	}

	public int getItemNumber() {
		return itemNumber;
	}

	public void setItemNumber(int itemNumber) {
		this.itemNumber = itemNumber;
	}

	public String getAuthors() {
		return authors;
	}

	public void setAuthors(String authors) {
		this.authors = authors;
	}

	public String getExplanatoryText() {
		return explanatoryText;
	}

	public void setExplanatoryText(String explanatoryText) {
		this.explanatoryText = explanatoryText;
	}

	public long getMinCardinality() {
		return minCardinality;
	}

	public void setMinCardinality(long minCardinality) {
		this.minCardinality = minCardinality;
	}

	public long getMaxCardinality() {
		return maxCardinality;
	}

	public void setMaxCardinality(long maxCardinality) {
		this.maxCardinality = maxCardinality;
	}

	public boolean isShouldDisplay() {
		return shouldDisplay;
	}

	public void setShouldDisplay(boolean shouldDisplay) {
		this.shouldDisplay = shouldDisplay;
	}

	public String getGroupLabel() {
		return groupLabel;
	}

	public void setGroupLabel(String groupLabel) {
		this.groupLabel = groupLabel;
	}
	
	public Collection<AllowedTermWithQuantification> getAllowedTerms() {
		if (allowedTerms == null) {
			return Collections.emptyList();
		}
		return allowedTerms;
	}

	public void addAllowedTerm(AllowedTermWithQuantification allowedTerm) {
		if (allowedTerms == null) {
			allowedTerms = new ArrayList<AllowedTermWithQuantification>();
		}
		allowedTerms.add(allowedTerm);
		allowedTerm.initRemoveCommand(allowedTerms);
		allowedTerm.initContext(allowedTerms);
	}
	
	public QuestionType getQuestionType() {
		return questionType;
	}

	public void setQuestionType(QuestionType questionType) {
		this.questionType = questionType;
		if (questionType != null) {
			questionType.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					ComponentCharacteristic.this.questionType = null;
				}
			});
		}
	}
	
}
