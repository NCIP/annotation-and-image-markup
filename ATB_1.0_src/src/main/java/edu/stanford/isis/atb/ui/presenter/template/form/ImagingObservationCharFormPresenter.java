/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.ANNOTATOR_CONFIDENCE;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.CARDINALITY;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.EXPL_TEXT;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.GROUP_LABEL;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.LABEL;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.SHOULD_DISPLAY;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.ImagingObservationCharacteristic;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.Cardinality;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.ComponentFormView.ComponentFormField;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField;

/**
 * @author Vitaliy Semeshko
 */
public class ImagingObservationCharFormPresenter extends AbstractFormPresenter<ImagingObservationCharacteristic, 
		ImagingObservationCharFormView> {

	public ImagingObservationCharFormPresenter(ImagingObservationCharFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(ImagingObservationCharacteristic value) {
		this.value = value;
		
		// initialize form fields
		view.setFieldValue(LABEL, StringUtils.trimToEmpty(value.getLabel()));
		view.setFieldValue(EXPL_TEXT, StringUtils.trimToEmpty(value.getExplanatoryText()));
		view.setFieldValue(CARDINALITY, new Cardinality(value.getMinCardinality(), value.getMaxCardinality()));
		view.setFieldValue(SHOULD_DISPLAY, value.isShouldDisplay());
		view.setFieldValue(ANNOTATOR_CONFIDENCE, value.isAnnotatorConfidence());
		
		String authors = StringUtils.trimToEmpty(value.getAuthors());
		if (StringUtils.isNotEmpty(authors)) {
			view.setFieldValue(AUTHORS, authors);
		} else if (!value.isInitialized()) {
			view.setFieldValue(AUTHORS, PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME));
		} else {
			view.setFieldValue(AUTHORS, Const.EMPTY);
		}
		
		view.setFieldValue(GROUP_LABEL, StringUtils.trimToEmpty(value.getGroupLabel()));
	}

	@Override
	protected boolean validate() {
		String label = view.getFieldValue(ImagingObservationCharFormField.LABEL).toString();
		if (isEmptyString(label, ComponentFormField.LABEL)) {
			return false;
		}

		String explText = view.getFieldValue(EXPL_TEXT).toString();
		Cardinality cardinality = (Cardinality) view.getFieldValue(CARDINALITY);
		Boolean shouldDisplay = (Boolean) view.getFieldValue(SHOULD_DISPLAY);
		Boolean confidence = (Boolean) view.getFieldValue(ANNOTATOR_CONFIDENCE);
		String authors = view.getFieldValue(AUTHORS).toString();
		String groupLabel = view.getFieldValue(GROUP_LABEL).toString();
		
		value.setLabel(label);
		value.setExplanatoryText(explText);
		value.setMinCardinality(cardinality.getMin());
		value.setMaxCardinality(cardinality.getMax());
		value.setShouldDisplay(shouldDisplay);
		value.setAnnotatorConfidence(confidence);
		value.setAuthors(authors);
		value.setGroupLabel(groupLabel);
		
		return true;
	}
	
}
