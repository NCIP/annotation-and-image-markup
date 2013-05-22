/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.Valid;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Inference", strict=false)
public class Inference extends AbstractRemovableElement {

	@Attribute
	private boolean annotatorConfidence;
	
	@Valid
	@Element(name="QuestionType", required=false)
	private QuestionType questionType;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (questionType != null) {
			questionType.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					questionType = null;
				}
			});
		}
	}

	public boolean isAnnotatorConfidence() {
		return annotatorConfidence;
	}

	public void setAnnotatorConfidence(boolean annotatorConfidence) {
		this.annotatorConfidence = annotatorConfidence;
	}

	public QuestionType getQuestionType() {
		return questionType;
	}

	public void setQuestionType(QuestionType questionType) {
		this.questionType = questionType;
		questionType.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				Inference.this.questionType = null;
			}
		});
	}
	
	@Override
	public String toString() {
		return "Inference";
	}
	
}
