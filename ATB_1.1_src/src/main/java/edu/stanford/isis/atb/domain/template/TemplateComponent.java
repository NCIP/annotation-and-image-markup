/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import static org.apache.commons.collections.CollectionUtils.isEmpty;
import static org.apache.commons.collections.CollectionUtils.isNotEmpty;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.validation.Valid;
import javax.validation.constraints.AssertTrue;
import javax.validation.constraints.NotNull;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.ElementUnion;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Component", strict=false)
public class TemplateComponent extends AbstractNumberedElement {

	@Valid
	@Element(name="QuestionType", required=false)
	private QuestionType questionType;
	
	@Valid
	@NotNull(message = "{templateComponent.content.notNull}")
	@ElementUnion({
		@Element(name="AnatomicEntity", type=AnatomicEntity.class, required=false),
		@Element(name="ImagingObservation", type=ImagingObservation.class, required=false),
		@Element(name="Inference", type=Inference.class, required=false),
		@Element(name="GeometricShape", type=GeometricShape.class, required=false),
		@Element(name="Calculation", type=Calculation.class, required=false)})
	private RemovableElement content;
	
	@NotEmpty(message = "{templateComponent.label.notEmpty}")
	@Attribute(required=false)
	private String label;
	
	@Attribute(required=false)
	private int itemNumber;
	
	@Attribute(required=false)
	private String authors;
	
	@Attribute(required=false)
	private String explanatoryText;
	
	@Attribute(required=false)
	private long minCardinality = 1; // PM: set a default value
	
	@Attribute(required=false)
	private long maxCardinality = 1; // PM: set a default value

	@Attribute(required=false)
	private boolean shouldDisplay = true; // PM: set a default value

	@Attribute(required=false)
	private String groupLabel;
	
	@Valid
	@ElementList(name="AllowedTerm", inline=true, required=false)
	private List<AllowedTerm> allowedTerms;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (content != null) {
			content.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					content = null;
				}
			});
		}
		
		if (questionType != null) {
			questionType.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					questionType = null;
				}
			});
		}
		
		if (allowedTerms != null) {
			for (AllowedTerm allowedTerm : allowedTerms) {
				allowedTerm.initRemoveCommand(allowedTerms);
				allowedTerm.initContext(allowedTerms);
			}
		}
	}
	
	@AssertTrue(message = "{templateComponent.allowedTerms.notEmpty}")
	public boolean isAllowedTermsValidNotEmpty() {
		// allowed terms should not be empty
		if ((content instanceof AnatomicEntity) || (content instanceof ImagingObservation) || (content instanceof Inference)) {
			return isNotEmpty(allowedTerms);
		}
		return true;
	}
	
	@AssertTrue(message = "{templateComponent.allowedTerms.empty}")
	public boolean isAllowedTermsValidEmpty() {
		// allowed terms should be empty
		if ((content instanceof Calculation) || (content instanceof GeometricShape)) {
			return isEmpty(allowedTerms);
		}
		return true;
	}
	
	@AssertTrue(message = "{cardinality.invalid}")
	public boolean isCardinalityValid() {
		return minCardinality <= maxCardinality;
	}
	
	public RemovableElement getContent() {
		return content;
	}
	
	public void setContent(RemovableElement content) {
		this.content = content;
		content.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				TemplateComponent.this.content = null;
			}
		});
	}

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

	public QuestionType getQuestionType() {
		return questionType;
	}

	public void setQuestionType(QuestionType questionType) {
		this.questionType = questionType;
		questionType.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				TemplateComponent.this.questionType = null;
			}
		});
	}
	
	public Collection<AllowedTerm> getAllowedTerms() {
		if (allowedTerms == null) {
			return Collections.emptyList();
		}
		return allowedTerms;
	}

	public void addAllowedTerm(AllowedTerm allowedTerm) {
		if (allowedTerms == null) {
			allowedTerms = new ArrayList<AllowedTerm>();
		}
		allowedTerms.add(allowedTerm);
		allowedTerm.initRemoveCommand(allowedTerms);
		allowedTerm.initContext(allowedTerms);
	}
	
	public void clearAllowedTerms() {
		this.allowedTerms = null;
	}

	@Override
	public String toString() {
		return itemNumber + " - " + label;
	}
	
}
