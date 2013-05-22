/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.rules;

import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.ALLOWED_TERM;
import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION;
import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC;
import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.COMPONENT;
import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC;
import static edu.stanford.isis.atb.ui.model.tree.TemplateNodeType.VALID_TERM;

import java.util.EnumSet;
import java.util.Set;

import edu.stanford.isis.atb.domain.template.AbstractElement;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.ComponentCharacteristic;
import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.Inference;
import edu.stanford.isis.atb.domain.template.TemplateComponent;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeValue;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AllowedTermWithQuantAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AnatomicEntityCharAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.CharQuantificationAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ComponentAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ImagingObservationCharAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.InferenceAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.MoveUpDownAction;

/**
 * Template modification rules. 
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateModificationRules {
	
	private Set<TemplateNodeType> allowedForMovingUpDown = EnumSet.of(COMPONENT,
			ANATOMIC_ENTITY_CHARACTERISTIC, 
			IMAGING_OBSERVATION_CHARACTERISTIC,
			ALLOWED_TERM,
			ALLOWED_TERM_WITH_QUANTIFICATION,
			VALID_TERM);
	
	public void applyRulesToNode(TemplateNodeValue nodeValue, ActionSet actions) {
		// firstly enable all
		for (CommandAction action : actions.getAll()) {
			action.setEnabled(true);
		}
		
		// after apply rules to disable some actions
		switch (nodeValue.getNodeType()) {
		case COMPONENT:
			applyComponentRules((TemplateComponent) nodeValue.getValue(), actions);
			break;
		case CHARACTERISTIC_QUANTIFICATION:
			applyCharacteristicQuantificationRules((CharacteristicQuantification) nodeValue.getValue(), actions);
			break;
		case ANATOMIC_ENTITY_CHARACTERISTIC:
		case IMAGING_OBSERVATION_CHARACTERISTIC:
			applyComponentCharacteristicRules((ComponentCharacteristic) nodeValue.getValue(), actions);
			break;
		case INFERENCE:
			applyInferenceRules((Inference) nodeValue.getValue(), actions);
			break;
		case ALLOWED_TERM_WITH_QUANTIFICATION:
			applyAllowedTermWithQuantificationRules((AllowedTermWithQuantification) nodeValue.getValue(), actions);
			break;
		}
	}
	
	public boolean isMoveUpDownAllowed(TemplateNodeValue nodeValue) {
		AbstractElement el = nodeValue.getValue();
		return allowedForMovingUpDown.contains(nodeValue.getNodeType()) && el.getContext().isMovingAllowed();
	}
	
	public void applyRulesToMoveUpDownActions(TemplateNodeValue nodeValue, ActionSet actions) {
		// firstly enable all
		for (CommandAction action : actions.getAll()) {
			action.setEnabled(true);
		}
		
		AbstractElement el = nodeValue.getValue();
		
		if (!el.getContext().canMoveUp()) {
			disableAction(MoveUpDownAction.UP, actions);
		}
		
		if (!el.getContext().canMoveDown()) {
			disableAction(MoveUpDownAction.DOWN, actions);
		}
	}
	
	private void applyComponentRules(TemplateComponent target, ActionSet actions) {
		if (target.getQuestionType() != null) {
			disableAction(ComponentAction.CREATE_QST_TYPE, actions);
		}

		Object content = target.getContent(); 
		
		if (content != null) {
			disableAction(ComponentAction.CREATE_AN_ENTITY, actions);
			disableAction(ComponentAction.CREATE_IMG_OBS, actions);
			disableAction(ComponentAction.CREATE_INFERENCE, actions);
			disableAction(ComponentAction.CREATE_CALCULATION, actions);
			disableAction(ComponentAction.CREATE_GEOM_SHAPE, actions);
			
			if (content instanceof Calculation || content instanceof GeometricShape) {
				disableAction(ComponentAction.ADD_ALLOWED_TERMS, actions);
			}
		} else {
			if (!target.getAllowedTerms().isEmpty()) {
				disableAction(ComponentAction.CREATE_CALCULATION, actions);
				disableAction(ComponentAction.CREATE_GEOM_SHAPE, actions);	
			}
		}
		
	}
	
	private void applyCharacteristicQuantificationRules(CharacteristicQuantification target, ActionSet actions) {
		if (target.getScale() != null || target.getQuantile() != null) {
			disableAction(CharQuantificationAction.CREATE_INTERVAL, actions);
			disableAction(CharQuantificationAction.CREATE_NUMERICAL, actions);
			disableAction(CharQuantificationAction.CREATE_QUANTILE, actions);
			disableAction(CharQuantificationAction.CREATE_SCALE, actions);
		}
		
		if (!target.getNumericals().isEmpty()) {
			disableAction(CharQuantificationAction.CREATE_INTERVAL, actions);
			disableAction(CharQuantificationAction.CREATE_QUANTILE, actions);
			disableAction(CharQuantificationAction.CREATE_SCALE, actions);			
		}
		
		if (!target.getIntervals().isEmpty()) {
			disableAction(CharQuantificationAction.CREATE_NUMERICAL, actions);
			disableAction(CharQuantificationAction.CREATE_QUANTILE, actions);
			disableAction(CharQuantificationAction.CREATE_SCALE, actions);
		}
	}
	
	private void applyComponentCharacteristicRules(ComponentCharacteristic target, ActionSet actions) {
		if (target.getQuestionType() != null) {
			disableAction(AnatomicEntityCharAction.CREATE_QST_TYPE, actions);
			disableAction(ImagingObservationCharAction.CREATE_QST_TYPE, actions);
		}
	}
	
	private void applyInferenceRules(Inference target, ActionSet actions) {
		if (target.getQuestionType() != null) {
			disableAction(InferenceAction.CREATE_QST_TYPE, actions);
		}
	}
	
	private void applyAllowedTermWithQuantificationRules(AllowedTermWithQuantification target, ActionSet actions) {
		if (target.getCharacteristicQuantification() != null) {
			disableAction(AllowedTermWithQuantAction.CREATE_CHAR_QUANT, actions);
		}
	}
	
	private void disableAction(Object actionKey, ActionSet actions) {
		CommandAction action = actions.get(actionKey);
		if (action != null) {
			action.setEnabled(false);
		}
	}
	
}
