/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.form;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.presenter.AbstractPresenter;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;

/**
 * Base presenter for edit forms.
 * 
 * @param T value being edited
 * 
 * @author Vitaliy Semeshko
 */
public abstract class AbstractFormPresenter<T, V extends EditFormView<? extends Enum<?>>> extends AbstractPresenter<V> 
		implements FormPresenter<V> {

	protected T value;

	protected boolean creation;
	
	private FormCloseListener formCloseListener;
	
	private FormSubmitListener<T> formSubmitListener;
	
	public AbstractFormPresenter(V view) {
		super(view);
		bindView();
	}
	
	@Override
	public void bindView() {
		view.setFormCloseActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				formCloseListener.onFormClose();
			}
		});
		
		view.setFormSubmitActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (validate()) {
					formSubmitListener.onFormSubmit(value, creation);
				}
			}
		});
	}
	
	@Override
	public Component prepareForm(boolean isCreation) {
		this.creation = isCreation;
		view.initFieldsState(isCreation);
		return view.asComponent();
	}
	
	protected abstract boolean validate();
	
	public abstract void setValue(T value);
	
	public void setFormCloseListener(FormCloseListener formCloseListener) {
		this.formCloseListener = formCloseListener;
	}

	public void setFormSubmitListener(FormSubmitListener<T> formSubmitListener) {
		this.formSubmitListener = formSubmitListener;
	}
	
	protected boolean isEmptyString(String value, LabeledFormField formField) {
		if (StringUtils.isBlank(value)) {
			notifyWrongFieldValue(formField);
			return true;
		}
		return false;
	}
	
	protected boolean isEmpty(Object value, LabeledFormField formField) {
		if (value == null) {
			notifyWrongFieldValue(formField);
			return true;
		}
		return false;
	}
	
	protected void notifyWrongFieldValue(LabeledFormField formField) {
		view.notifyValidationError(formField, String.format(Const.MSG_WRONG_FIELD_VALUE, formField.getLabel()));
	}
	
	public interface FormCloseListener {
		
		public void onFormClose();
		
	}
	
	public interface FormSubmitListener<T> {
		
		public void onFormSubmit(T value, boolean isCreation);
		
	}

}
