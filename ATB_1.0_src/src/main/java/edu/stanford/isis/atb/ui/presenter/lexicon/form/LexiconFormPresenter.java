/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.form;

import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.MODIFICATION_DATE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.NAME;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.READ_ONLY;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.SCHEMA_DESIGNATOR;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.SCHEMA_VERSION;
import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconFormPresenter extends AbstractFormPresenter<Lexicon, LexiconFormView> {

	public LexiconFormPresenter(LexiconFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Lexicon value) {
		this.value = value;
		
		// initialize form fields
		view.setFieldValue(NAME, trimToEmpty(value.getName()));
		view.setFieldValue(SCHEMA_DESIGNATOR, StringUtils.trimToEmpty(value.getSchemaDesignator()));
		view.setFieldValue(SCHEMA_VERSION, StringUtils.trimToEmpty(value.getSchemaVersion()));
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		
		String authors = StringUtils.trimToEmpty(value.getAuthors());
		if (StringUtils.isNotEmpty(authors)) {
			view.setFieldValue(AUTHORS, authors);
		} else if (!value.isInitialized()) {
			view.setFieldValue(AUTHORS, PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME));
		} else {
			view.setFieldValue(AUTHORS, Const.EMPTY);
		}
		
		view.setFieldValue(READ_ONLY, value.isReadOnly());
		view.setFieldValue(CREATION_DATE, value.getCreationDate());
		view.setFieldValue(MODIFICATION_DATE, value.getModificationDate());
		
		view.setReadOnly(value.isReadOnly());
	}

	@Override
	protected boolean validate() {
		String name = view.getFieldValue(NAME).toString();
		if (isEmptyString(name, NAME)) {
			return false;
		}
		
		String schemaDesignator = view.getFieldValue(SCHEMA_DESIGNATOR).toString();
		if (isEmptyString(schemaDesignator, SCHEMA_DESIGNATOR)) {
			return false;
		}
		
		String schemaVersion = view.getFieldValue(SCHEMA_VERSION).toString();
		String description = view.getFieldValue(DESCRIPTION).toString();
		String authors = view.getFieldValue(AUTHORS).toString();

		value.setName(name);
		value.setSchemaDesignator(schemaDesignator);
		value.setSchemaVersion(schemaVersion);
		value.setDescription(description);
		value.setAuthors(authors);
		
		return true;
	}
	
}
