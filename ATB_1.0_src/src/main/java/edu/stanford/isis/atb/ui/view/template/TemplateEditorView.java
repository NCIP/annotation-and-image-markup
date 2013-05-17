/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template;

import java.awt.Component;
import java.util.Collection;

import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.validation.TemplateValidationError;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateEditorView extends View {

	// data
	
	public void setActiveTemplate(Template template);
	
	public <T> T getSelectedNodeValue();
	
	public void setWarnings(Collection<TemplateValidationError> warnings);
	
	public void clearWarnings();
	
	// commands
	
	public void setCommand(Object actionKey, Command command);
	
	public void setCommand(MoveUpDownAction actionKey, Command command);
	
	public void setShowFormCommand(TemplateNodeType nodeType, Command command);
	
	// view
	
	public void hideEditForm();
	
	public void showEditForm(Component c, boolean forceShow);
	
	public void showEditForm(Component c);
	
	public void showWarnings();
	
	public void hideWarnings();
	
	public void clear();
	
	public void selectRootNode();
	
	public TemplateTreeManager getTreeManager();
	
	// set listeners
	
	public void addWarningSelectionListeners(TemplateWarningSelectionListener ... listeners);
	
	/**
	 * Listeners of template warnings selections should implement this interface.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface TemplateWarningSelectionListener {
		
		public void onWarningSelected(TemplateValidationError warning);
		
	}
	
	public enum TemplateAction {
		CREATE_COMPONENT,
		CREATE_TAG;
	}
	
	public enum ComponentAction {
		DELETE,
		CREATE_AN_ENTITY,
		CREATE_IMG_OBS,
		CREATE_INFERENCE,
		CREATE_CALCULATION,
		CREATE_GEOM_SHAPE,
		CREATE_QST_TYPE,
		ADD_ALLOWED_TERMS;
	}

	public enum QuestionTypeAction {
		DELETE,
		ADD_VALID_TERMS;
	}
	
	public enum GeometricShapeAction {
		DELETE;
	}	
		
	public enum СalculationAction {
		DELETE,
		CREATE_CALC_TYPE;
	}
		
	public enum CalculationTypeAction {
		DELETE,
		ADD_VALID_TERMS,
		CREATE_ALGORITHM_TYPE;
	}
		
	public enum AlgorithmTypeAction {
		DELETE;
	}
		
	public enum AllowedTermAction {
		DELETE,
		ADD_VALID_TERMS,
		CREATE_NON_QUANT;
	}
		
	public enum AnatomicEntityAction {
		DELETE,
		CREATE_AN_ENTITY_CHAR;
	}
	
	public enum AnatomicEntityCharAction {
		DELETE,
		ADD_ALLOWED_TERMS,
		CREATE_QST_TYPE;
	}
	
	public enum ImagingObservationAction {
		DELETE,
		CREATE_IMG_OBS_CHAR;
	}
	
	public enum ImagingObservationCharAction {
		DELETE,
		ADD_ALLOWED_TERMS,
		CREATE_QST_TYPE;
	}
		
	public enum AllowedTermWithQuantAction {
		DELETE,
		ADD_VALID_TERMS,
		CREATE_CHAR_QUANT;
	}
		
	public enum TagAction {
		DELETE;
	}
	
	public enum NonQuantifiableAction {
		DELETE;
	}
	
	public enum NumericalAction {
		DELETE;
	}
	
	public enum IntervalAction {
		DELETE;
	}
	
	public enum QuantileAction {
		DELETE;
	}
	
	public enum OrdinalLevelAction {
		DELETE;
	}
	
	public enum CharQuantificationAction {
		DELETE,
		CREATE_SCALE,
		CREATE_NUMERICAL,
		CREATE_INTERVAL,
		CREATE_QUANTILE,
		CREATE_NON_QUANT;
	}

	public enum InferenceAction {
		DELETE,
		CREATE_QST_TYPE;
	}
	
	public enum ScaleAction {
		DELETE,
		CREATE_ORD_LEVEL;
	}

	public enum ValidTermAction {
		DELETE,
		ADD_VALID_TERMS;
	}
	
	// misc
	
	public enum MoveUpDownAction {
		UP,
		DOWN;
	}
	
}
