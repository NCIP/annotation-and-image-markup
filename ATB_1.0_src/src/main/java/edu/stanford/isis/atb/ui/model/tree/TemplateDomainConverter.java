/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model.tree;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CalculationType;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.ImagingObservation;
import edu.stanford.isis.atb.domain.template.ImagingObservationCharacteristic;
import edu.stanford.isis.atb.domain.template.Inference;
import edu.stanford.isis.atb.domain.template.Interval;
import edu.stanford.isis.atb.domain.template.NonQuantifiable;
import edu.stanford.isis.atb.domain.template.Numerical;
import edu.stanford.isis.atb.domain.template.OrdinalLevel;
import edu.stanford.isis.atb.domain.template.Quantile;
import edu.stanford.isis.atb.domain.template.QuestionType;
import edu.stanford.isis.atb.domain.template.Scale;
import edu.stanford.isis.atb.domain.template.Tag;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateComponent;
import edu.stanford.isis.atb.domain.template.ValidTerm;

/**
 * Provides methods to convert domain object that can be presented as tree nodes.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateDomainConverter {

	private static final TemplateDomainConverter instance = new TemplateDomainConverter();
	
	private TemplateDomainConverter() {}
	
	public static TemplateDomainConverter getInstance() {
		return instance;
	}
	
	/**
	 * Convert domain model to {@link TreeModel}.
	 * 
	 * @param t domain model to be converted.
	 * @return implementation of {@link TreeModel}
	 */
	public TreeModel template(Template t) {
		DefaultMutableTreeNode root = createNode(TemplateNodeType.TEMPLATE, t);
		
		for (TemplateComponent component : t.getComponents()) {
			root.add(templateComponent(component));
		}
		
		for (Tag tag : t.getTags()) {
			root.add(tag(tag));
		}
		
		return new DefaultTreeModel(root);
	}
	
	public DefaultMutableTreeNode tag(Tag value) {
		return createNode(TemplateNodeType.TAG, value);
	}
	
	public DefaultMutableTreeNode templateComponent(TemplateComponent value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.COMPONENT, value);
		
		QuestionType questionType = value.getQuestionType();
		if (questionType != null) {
			node.add(questionType(questionType));
		}
		
		Object content = value.getContent();
		if (content != null) {
			if (content instanceof AnatomicEntity) {
				node.add(anatomicEntity((AnatomicEntity) content));
			} else if (content instanceof ImagingObservation) {
				node.add(imagingObservation((ImagingObservation) content));
			} else if (content instanceof Inference) {
				node.add(inference((Inference) content));
			} else if (content instanceof GeometricShape) {
				node.add(geometricShape((GeometricShape) content));
			} else if (content instanceof Calculation) {
				node.add(calculation((Calculation) content));
			}
		}
		
		for (AllowedTerm at : value.getAllowedTerms()) {
			node.add(allowedTerm(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode questionType(QuestionType value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.QUESTION_TYPE, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode calculation(Calculation value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CALCULATION, value);
		
		for (CalculationType ct : value.getCalculationType()) {
			node.add(calculationType(ct));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode calculationType(CalculationType value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CALCULATION_TYPE, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		for (AlgorithmType at : value.getAlgorithmTypes()) {
			node.add(algorithmType(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode algorithmType(AlgorithmType value) {
		return createNode(TemplateNodeType.ALGORITHM_TYPE, value);
	}
	
	public DefaultMutableTreeNode anatomicEntity(AnatomicEntity value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ANATOMIC_ENTITY, value);
		
		for (AnatomicEntityCharacteristic aec : value.getCharacteristics()) {
			node.add(anatomicEntityCharacteristic(aec));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode imagingObservation(ImagingObservation value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.IMAGING_OBSERVATION, value);
		
		for (ImagingObservationCharacteristic ioc : value.getCharacteristics()) {
			node.add(imagingObservationCharacteristic(ioc));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode inference(Inference value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.INFERENCE, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode geometricShape(GeometricShape value) {
		return createNode(TemplateNodeType.GEOMETRIC_SHAPE, value);
	}
	
	public DefaultMutableTreeNode anatomicEntityCharacteristic(AnatomicEntityCharacteristic value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		for (AllowedTermWithQuantification at : value.getAllowedTerms()) {
			node.add(allowedTermWithQuantification(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode imagingObservationCharacteristic(ImagingObservationCharacteristic value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		for (AllowedTermWithQuantification at : value.getAllowedTerms()) {
			node.add(allowedTermWithQuantification(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode validTerm(ValidTerm value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.VALID_TERM, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode allowedTerm(AllowedTerm value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ALLOWED_TERM, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}

		for (NonQuantifiable nq : value.getNonQuantifiables()) {
			node.add(nonQuantifiable(nq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode allowedTermWithQuantification(AllowedTermWithQuantification value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		CharacteristicQuantification cq = value.getCharacteristicQuantification();
		if (cq != null) {
			node.add(characteristicQuantifications(cq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode nonQuantifiable(NonQuantifiable value) {
		return createNode(TemplateNodeType.NON_QUANTIFIABLE, value);
	}
	
	public DefaultMutableTreeNode characteristicQuantifications(CharacteristicQuantification value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CHARACTERISTIC_QUANTIFICATION, value);
		
		Scale scale = value.getScale();
		if (scale != null) {
			node.add(scale(scale));
		}
		
		for (Numerical nm : value.getNumericals()) {
			node.add(numerical(nm));
		}
		
		for (Interval iv : value.getIntervals()) {
			node.add(interval(iv));
		}
		
		Quantile qt = value.getQuantile();
		if (qt != null) {
			node.add(quantile(qt));
		}
		
		for (NonQuantifiable nq : value.getNonQuantifiables()) {
			node.add(nonQuantifiable(nq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode scale(Scale value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.SCALE, value);
		
		for (OrdinalLevel ol : value.getOrdinalLevels()) {
			node.add(ordinalLevel(ol));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode ordinalLevel(OrdinalLevel value) {
		return createNode(TemplateNodeType.ORDINAL_LEVEL, value);
	}
	
	public DefaultMutableTreeNode numerical(Numerical value) {
		return createNode(TemplateNodeType.NUMERICAL, value);
	}
	
	public DefaultMutableTreeNode interval(Interval value) {
		return createNode(TemplateNodeType.INTERVAL, value);
	}
	
	public DefaultMutableTreeNode quantile(Quantile value) {
		return createNode(TemplateNodeType.QUANTILE, value);
	}
	
	private DefaultMutableTreeNode createNode(TemplateNodeType type, Object userObject) {
		return new DefaultMutableTreeNode(new TemplateNodeValue(type, userObject));
	}
	
}
