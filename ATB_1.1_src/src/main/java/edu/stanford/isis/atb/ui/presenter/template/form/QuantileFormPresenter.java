/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import edu.stanford.isis.atb.domain.template.Quantile;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.QuantileFormView;
import edu.stanford.isis.atb.ui.view.template.form.QuantileFormView.QuantileFormField;

/**
 * @author Vitaliy Semeshko
 */
public class QuantileFormPresenter extends AbstractFormPresenter<Quantile, QuantileFormView> {

	public QuantileFormPresenter(QuantileFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Quantile value) {
		this.value = value;
		view.setFieldValue(QuantileFormField.BINS, value.getBins());
	}

	@Override
	protected boolean validate() {
		Integer bins = (Integer) view.getFieldValue(QuantileFormField.BINS);
		if (isEmpty(bins, QuantileFormField.BINS)) return false;
				
		value.setBins(bins);
		
		return true;
	}
	
}
