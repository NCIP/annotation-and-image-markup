/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.ScaleFormView.ScaleFormField.COMMENT;
import static edu.stanford.isis.atb.ui.view.template.form.ScaleFormView.ScaleFormField.DESCRIPTION;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.Scale;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.ScaleFormView;

/**
 * @author Vitaliy Semeshko
 */
public class ScaleFormPresenter extends AbstractFormPresenter<Scale, ScaleFormView> {

	public ScaleFormPresenter(ScaleFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Scale value) {
		this.value = value;
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		view.setFieldValue(COMMENT, StringUtils.trimToEmpty(value.getComment()));
	}

	@Override
	protected boolean validate() {
		String description = view.getFieldValue(DESCRIPTION).toString();
		String comment = view.getFieldValue(COMMENT).toString();
		
		value.setDescription(description);
		value.setComment(comment);
		
		return true;
	}
	
}
