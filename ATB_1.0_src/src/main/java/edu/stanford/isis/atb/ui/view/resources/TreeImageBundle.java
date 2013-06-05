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
 * Image bundle for tree.
 * 
 * @author Vitaliy Semeshko
 */
public class TreeImageBundle {

	private static TreeImageBundle instance = new TreeImageBundle();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private TreeImageBundle() {}
	
	public static TreeImageBundle getInstance() {
		return instance;
	}
	
	private static final String ROOT_TREE_DIR = "etc/images/tree/";
	
	private static final String TEMPLATE = ROOT_TREE_DIR + "template.png";
	
	public LazyIcon getTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(TEMPLATE));
	}
	
	private static final String COMPONENT = ROOT_TREE_DIR + "component.png";  
	
	public LazyIcon getComponentIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COMPONENT));
	}
	
	private static final String CALCULATION = ROOT_TREE_DIR + "calculation.png";
	
	public LazyIcon getCalculationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CALCULATION));
	}
	
	private static final String SHAPE = ROOT_TREE_DIR + "shape.png";
	
	public LazyIcon getShapeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SHAPE));
	}
	
	private static final String ANATOMIC_ENTITY = ROOT_TREE_DIR + "anatomic_entity.png";
	
	public LazyIcon getAnatomicEntityIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ANATOMIC_ENTITY));
	}
	
	private static final String ANATOMIC_ENTITY_CHAR = ROOT_TREE_DIR + "anatomic_entity_char.png";
	
	public LazyIcon getAnatomicEntityCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ANATOMIC_ENTITY_CHAR));
	}
	
	private static final String INFERENCE = ROOT_TREE_DIR + "inference.png";
	
	public LazyIcon getInferenceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(INFERENCE));
	}
	
	private static final String IMAGING_OBSERVATION = ROOT_TREE_DIR + "imaging_observation.png";
	
	public LazyIcon getImagingObservationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMAGING_OBSERVATION));
	}
	
	private static final String IMAGING_OBSERVATION_CHAR = ROOT_TREE_DIR + "imaging_observation_char.png";
	
	public LazyIcon getImagingObservationCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMAGING_OBSERVATION_CHAR));
	}
	
	private static final String EMPTY = ROOT_TREE_DIR + "empty.png";
	
	public LazyIcon getEmptyIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EMPTY));
	}
	
	private static final String QUESTION_TYPE = ROOT_TREE_DIR + "question_type.png";
	
	public LazyIcon getQuestionTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(QUESTION_TYPE));
	}
	
	private static final String ALLOWED_TERM = ROOT_TREE_DIR + "allowed_term.png";
	
	public LazyIcon getAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ALLOWED_TERM));
	}
	
	private static final String VALID_TERM = ROOT_TREE_DIR + "valid_term.png";
	
	public LazyIcon getValidTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(VALID_TERM));
	}
	
	private static final String TAG = ROOT_TREE_DIR + "tag.png";
	
	public LazyIcon getTagIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(TAG));
	}
	
	private static final String INTERVAL = ROOT_TREE_DIR + "interval.png";
	
	public LazyIcon getIntervalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(INTERVAL));
	}
	
	private static final String CALC_TYPE = ROOT_TREE_DIR + "calculation_type.png";
	
	public LazyIcon getCalcTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CALC_TYPE));
	}
	
	private static final String ALGORITHM_TYPE = ROOT_TREE_DIR + "algorithm_type.png";
	
	public LazyIcon getAlgorithmTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ALGORITHM_TYPE));
	}
	
	private static final String NON_QUANTIFIABLE = ROOT_TREE_DIR + "non_quantifiable.png";
	
	public LazyIcon getNonQuantifiableIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(NON_QUANTIFIABLE));
	}
	
	private static final String CHAR_QUANT = ROOT_TREE_DIR + "characteristic_quantification.png";
	
	public LazyIcon getCharacteristicQuantificationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CHAR_QUANT));
	}
	
	private static final String SCALE = ROOT_TREE_DIR + "scale.png";
	
	public LazyIcon getScaleIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SCALE));
	}
	
	private static final String ORDINAL_LEVEL = ROOT_TREE_DIR + "ordinal_level.png";
	
	public LazyIcon getOrdinalLevelIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ORDINAL_LEVEL));
	}
	
	private static final String NUMERICAL = ROOT_TREE_DIR + "numerical.png";
	
	public LazyIcon getNumericalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(NUMERICAL));
	}
	
	private static final String QUANTILE = ROOT_TREE_DIR + "quantile.png";
	
	public LazyIcon getQuantileIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(QUANTILE));
	}
	
	// Lexicons
	
	private static final String LEXICON = ROOT_TREE_DIR + "lexicon.png";
	
	public LazyIcon getLexiconIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(LEXICON));
	}
	
}
