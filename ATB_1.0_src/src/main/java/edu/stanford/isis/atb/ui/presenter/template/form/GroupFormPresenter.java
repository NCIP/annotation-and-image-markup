/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.Const.EMPTY;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.NAME;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.UID;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.VERSION;

import java.util.Date;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.GroupFormView;

/**
 * @author Vitaliy Semeshko
 */
public class GroupFormPresenter extends AbstractFormPresenter<TemplateContainer, GroupFormView> {

	public GroupFormPresenter(GroupFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(TemplateContainer value) {
		this.value = value;
		
		// initialize form fields
		Identifier uid = value.getUid();
		String uidStr;
		if (uid != null) {
			uidStr = StringUtils.trimToEmpty(uid.getOriginal());
		} else {
			uidStr = EMPTY;
		}
		view.setFieldValue(UID, uidStr);
		
		view.setFieldValue(NAME, StringUtils.trimToEmpty(value.getName()));
		view.setFieldValue(VERSION, StringUtils.trimToEmpty(value.getVersion()));
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		
		String authors = StringUtils.trimToEmpty(value.getAuthors());
		if (StringUtils.isNotEmpty(authors)) {
			view.setFieldValue(AUTHORS, authors);
		} else if (!value.isInitialized()) {
			view.setFieldValue(AUTHORS, PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME));
		} else {
			view.setFieldValue(AUTHORS, Const.EMPTY);
		}
		
		view.setFieldValue(CREATION_DATE, value.getCreationDate());
	}

	@Override
	protected boolean validate() {
		String name = view.getFieldValue(NAME).toString();
		if (isEmptyString(name, NAME)) {
			return false;
		}

		String version = view.getFieldValue(VERSION).toString();
		if (isEmptyString(version, VERSION)) {
			return false;
		}
		
		String description = view.getFieldValue(DESCRIPTION).toString();
		if (isEmptyString(description, DESCRIPTION)) {
			return false;
		}
		
		String authors = view.getFieldValue(AUTHORS).toString();
		if (isEmptyString(authors, AUTHORS)) {
			return false;
		}

		String uid = view.getFieldValue(UID).toString();
		if (isEmptyString(uid, UID)) {
			return false;
		}
		
		Date date = (Date) view.getFieldValue(CREATION_DATE);
		if (date == null) {
			notifyWrongFieldValue(CREATION_DATE);
			return false;
		}

		if (creation) {
			value.setCreationDate(date);
		}
		
		value.setName(name);
		value.setVersion(version);
		value.setDescription(description);
		value.setAuthors(authors);
		
		return true;
	}
	
}
