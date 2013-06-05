/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.resources;

import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.view.resources.image.DefaultLazyIcon;
import edu.stanford.isis.atb.ui.view.resources.image.LazyIcon;

/**
 * Image bundle for toolbar.
 * 
 * @author Vitaliy Semeshko
 */
public class ToolBarImageBundle {

	private static ToolBarImageBundle instance = new ToolBarImageBundle();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private ToolBarImageBundle() {}
	
	public static ToolBarImageBundle getInstance() {
		return instance;
	}
	
	private static final String ROOT_TOOLBAR_DIR = "etc/images/toolbar/";
	
	// templates
	
	private static final String COPY_TEMPLATE = ROOT_TOOLBAR_DIR + "copy_template.png";
	
	public LazyIcon getCopyTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COPY_TEMPLATE));
	}
	
	private static final String SEARCH_TEMPLATES = ROOT_TOOLBAR_DIR + "search_templates.png";
	
	public LazyIcon getSearchTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_TEMPLATES));
	}
	
	private static final String CREATE_COMPONENT = ROOT_TOOLBAR_DIR + "create_component.png";
	
	public LazyIcon getCreateComponentIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_COMPONENT));
	}
	
	private static final String CREATE_CALCULATION = ROOT_TOOLBAR_DIR + "create_calculation.png";
	
	public LazyIcon getCreateCalculationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CALCULATION));
	}
	
	private static final String CREATE_SHAPE = ROOT_TOOLBAR_DIR + "create_shape.png";
	
	public LazyIcon getCreateShapeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_SHAPE));
	}
	
	private static final String CREATE_ANATOMIC_ENTITY = ROOT_TOOLBAR_DIR + "create_anatomic_entity.png";
	
	public LazyIcon getCreateAnatomicEntityIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ANATOMIC_ENTITY));
	}
	
	private static final String CREATE_INFERENCE = ROOT_TOOLBAR_DIR + "create_inference.png";
	
	public LazyIcon getCreateInferenceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_INFERENCE));
	}
	
	private static final String CREATE_IMAGE_OBSERVATION = ROOT_TOOLBAR_DIR + "create_image_observation.png";
	
	public LazyIcon getCreateImageObservationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_IMAGE_OBSERVATION));
	}
	
	private static final String CREATE_IMAGE_OBSERVATION_CHAR = ROOT_TOOLBAR_DIR + 
			"create_image_observation_characteristic.png";
	
	public LazyIcon getCreateImageObservationCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_IMAGE_OBSERVATION_CHAR));
	}
	
	private static final String CREATE_TAG = ROOT_TOOLBAR_DIR + "create_tag.png";
	
	public LazyIcon getCreateTagIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_TAG));
	}
	
	private static final String CREATE_QUESTION_TYPE = ROOT_TOOLBAR_DIR + "create_question_type.png";
	
	public LazyIcon getCreateQuestionTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_QUESTION_TYPE));
	}
	
	private static final String CREATE_ALLOWED_TERM = ROOT_TOOLBAR_DIR + "create_allowed_term.png";
	
	public LazyIcon getCreateAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ALLOWED_TERM));
	}
	
	private static final String CREATE_VALID_TERM = ROOT_TOOLBAR_DIR + "create_valid_term.png";
	
	public LazyIcon getCreateValidTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_VALID_TERM));
	}
	
	private static final String CREATE_CALC_TYPE = ROOT_TOOLBAR_DIR + "create_calculation_type.png";
	
	public LazyIcon getCreateCalcTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CALC_TYPE));
	}
	
	private static final String CREATE_ALGORITHM_TYPE = ROOT_TOOLBAR_DIR + "create_algorithm_type.png";
	
	public LazyIcon getCreateAlgorithmTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ALGORITHM_TYPE));
	}
	
	private static final String CREATE_ANATOMIC_ENTITY_CHAR = ROOT_TOOLBAR_DIR + 
			"create_anatomic_entity_characteristic.png";
	
	public LazyIcon getCreateAnatomicEntityCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ANATOMIC_ENTITY_CHAR));
	}
	
	private static final String CREATE_NON_QUANTIFIABLE = ROOT_TOOLBAR_DIR + "create_non_quantifiable.png";
	
	public LazyIcon getCreateNonQuantifiableIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_NON_QUANTIFIABLE));
	}
	
	private static final String CREATE_CHAR_QUANT = ROOT_TOOLBAR_DIR + "create_characteristic_quantification.png";
	
	public LazyIcon getCreateCharacteristicQuantificationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CHAR_QUANT));
	}
	
	private static final String CREATE_SCALE = ROOT_TOOLBAR_DIR + "create_scale.png";
	
	public LazyIcon getCreateScaleIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_SCALE));
	}
	
	private static final String CREATE_ORDINAL_LEVEL = ROOT_TOOLBAR_DIR + "create_ordinal_level.png";
	
	public LazyIcon getCreateOrdinalLevelIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ORDINAL_LEVEL));
	}
	
	private static final String CREATE_NUMERICAL = ROOT_TOOLBAR_DIR + "create_numerical.png";
	
	public LazyIcon getCreateNumericalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_NUMERICAL));
	}
	
	private static final String CREATE_INTERVAL = ROOT_TOOLBAR_DIR + "create_interval.png";
	
	public LazyIcon getCreateIntervalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_INTERVAL));
	}
	
	private static final String CREATE_QUANTILE = ROOT_TOOLBAR_DIR + "create_quantile.png";
	
	public LazyIcon getCreateQuantileIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_QUANTILE));
	}
	
	// groups
	
	private static final String COPY_GROUP = ROOT_TOOLBAR_DIR + "copy_group.png";
	
	public LazyIcon getCopyGroupIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COPY_GROUP));
	}
	
	private static final String LINK_TEMPLATES = ROOT_TOOLBAR_DIR + "link_templates.png";
	
	public LazyIcon getLinkTemplatesIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(LINK_TEMPLATES));
	}
	
	private static final String SEARCH_GROUPS = ROOT_TOOLBAR_DIR + "search_groups.png";
	
	public LazyIcon getSearchGroupsIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_GROUPS));
	}
	
	private static final String IMPORT_EXPORT = ROOT_TOOLBAR_DIR + "import_export.png";
	
	public LazyIcon getImportExportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMPORT_EXPORT));
	}
	
	private static final String IMPORT = ROOT_TOOLBAR_DIR + "import.png";
	
	public LazyIcon getImportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMPORT));
	}
	
	private static final String EXPORT = ROOT_TOOLBAR_DIR + "export.png";
	
	public LazyIcon getExportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EXPORT));
	}
	
	private static final String REMOTE_SERVICE = ROOT_TOOLBAR_DIR + "remote_service.png";
	
	public LazyIcon getRemoteServiceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(REMOTE_SERVICE));
	}
	
	private static final String PUBLISH = ROOT_TOOLBAR_DIR + "publish.png";
	
	public LazyIcon getPublishIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(PUBLISH));
	}

	// lexicons
	
	private static final String USE_ALLOWED_TERM = ROOT_TOOLBAR_DIR + "use_allowed_term.png";
	
	public LazyIcon getUseAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(USE_ALLOWED_TERM));
	}
	
	private static final String SEARCH_LEXICONS = ROOT_TOOLBAR_DIR + "search_lexicons.png";
	
	public LazyIcon getSearchLexiconsIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_LEXICONS));
	}
	
	// misc
	
	private static final String CREATE = ROOT_TOOLBAR_DIR + "create.png";
	
	public LazyIcon getCreateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE));
	}
	
	private static final String EDIT = ROOT_TOOLBAR_DIR + "edit.png";
	
	public LazyIcon getEditIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EDIT));
	}
	
	private static final String DELETE = ROOT_TOOLBAR_DIR + "delete.png";
	
	public LazyIcon getDeleteIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(DELETE));
	}
	
	private static final String MOVE_UP = ROOT_TOOLBAR_DIR + "move_up.png";
	
	public LazyIcon getMoveUpIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(MOVE_UP));
	}
	
	private static final String MOVE_DOWN = ROOT_TOOLBAR_DIR + "move_down.png";
	
	public LazyIcon getMoveDownIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(MOVE_DOWN));
	}
	
}
