/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.impl;

import static edu.stanford.isis.atb.ui.Const.HNT_ADD_ALLOWED_TERMS;
import static edu.stanford.isis.atb.ui.Const.HNT_ADD_VALID_TERMS;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_ALGORITHM_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_AN_ENTITY;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_AN_ENTITY_CHAR;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_CALCULATION;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_CALC_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_CHAR_QUANT;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_COMPONENT;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_GEOM_SHAPE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_IMG_OBS;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_IMG_OBS_CHAR;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_INFERENCE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_INTERVAL;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_NON_QUANT;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_NUMERICAL;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_ORDINAL_LEVEL;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_QST_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_QUANTILE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_SCALE;
import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_TAG;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_ALGORITHM_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_ALLOWED_TERM;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_AN_ENTITY;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_AN_ENTITY_CHAR;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_CALCULATION;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_CALC_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_CHAR_QUANT;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_COMPONENT;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_GEOM_SHAPE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_IMG_OBS;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_IMG_OBS_CHAR;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_INTERVAL;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_NUMERICAL;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_ORDINAL_LEVEL;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_QST_TYPE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_QUANTILE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_SCALE;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_TAG;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_VALID_TERM;
import static edu.stanford.isis.atb.ui.Const.HNT_MOVE_DOWN;
import static edu.stanford.isis.atb.ui.Const.HNT_MOVE_UP;
import static edu.stanford.isis.atb.ui.Const.LBL_TEMPLATE_COMPONENTS;

import java.awt.Color;
import java.awt.Component;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Insets;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.Icon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.EmptyBorder;
import javax.swing.tree.DefaultMutableTreeNode;

import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeValue;
import edu.stanford.isis.atb.ui.validation.TemplateValidationError;
import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.CanShowEditForm;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView;
import edu.stanford.isis.atb.ui.view.template.TemplateTreeManager;
import edu.stanford.isis.atb.ui.view.template.rules.TemplateModificationRules;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane.CollapseMode;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn.IconColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;
import edu.stanford.isis.atb.ui.view.widget.tree.AbstractTree.NodeSelectionListener;
import edu.stanford.isis.atb.ui.view.widget.tree.TemplateTree;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateEditorViewImpl extends AbstractView implements TemplateEditorView {

	private static final int WARNINGS_PANE_HEIGHT = 100;
	
	private CanShowEditForm editFormManager;
	
	private ScrollableBlockWIthToolbar root = new ScrollableBlockWIthToolbar();

	private TemplateTree tree = new TemplateTree();

	private GenericTable<TemplateValidationError> warningsTable = new GenericTable<TemplateValidationError>();
	
	private TemplateTreeManager treeManager = new TemplateTreeManagerImpl(tree);
	
	private ToolBarImageBundle images = ToolBarImageBundle.getInstance();
	
	private MiscImageBundle miscImages = MiscImageBundle.getInstance();

	private TemplateModificationRules modificationRules = new TemplateModificationRules();
	
	private Map<TemplateNodeType, Command> formShowCommands = new HashMap<TemplateNodeType, Command>();
	
	private List<ActionSet> actions = new ArrayList<ActionSet>();
	private ActionSet templateActions = new ActionSet();
	private ActionSet componentActions = new ActionSet();
	private ActionSet qstTypeActions = new ActionSet();
	private ActionSet geomShapeActions = new ActionSet();
	private ActionSet calculationActions = new ActionSet();
	private ActionSet calcTypeActions = new ActionSet();
	private ActionSet algorithmTypeActions = new ActionSet();
	private ActionSet tagActions = new ActionSet();
	private ActionSet termActions = new ActionSet();
	private ActionSet termWithQuantActions = new ActionSet();
	private ActionSet validTermActions = new ActionSet();
	private ActionSet anatomicEntityActions = new ActionSet();
	private ActionSet anatomicEntityCharActions = new ActionSet();
	private ActionSet inferenceActions = new ActionSet();
	private ActionSet nonQuantActions = new ActionSet();
	private ActionSet imgObsActions = new ActionSet();
	private ActionSet imgObsCharActions = new ActionSet();
	private ActionSet charQuantificationActions = new ActionSet();
	private ActionSet scaleActions = new ActionSet();
	private ActionSet ordinalLevelActions = new ActionSet();
	private ActionSet numericalActions = new ActionSet();
	private ActionSet quantileActions = new ActionSet();
	private ActionSet intervalActions = new ActionSet();
	
	private Map<TemplateNodeType, ActionSet> nodeActions = new HashMap<TemplateNodeType, ActionSet>();
	
	private ActionSet moveUpDownActions = new ActionSet();
	
	public TemplateEditorViewImpl() {
		root.setSplitCollapsible(CollapseMode.COLLAPSE_BOTTOM);
		root.setCaptionText(LBL_TEMPLATE_COMPONENTS);
		root.setMainComponent(tree);

		initTree();
		initWarnings();
		initNodeActions();
		
		actions.add(templateActions);
		actions.add(componentActions);
		actions.add(qstTypeActions);
		actions.add(geomShapeActions);
		actions.add(tagActions);
		actions.add(calculationActions);
		actions.add(calcTypeActions);
		actions.add(algorithmTypeActions);
		actions.add(termActions);
		actions.add(termWithQuantActions);
		actions.add(validTermActions);
		actions.add(anatomicEntityActions);
		actions.add(anatomicEntityCharActions);
		actions.add(inferenceActions);
		actions.add(nonQuantActions);
		actions.add(imgObsActions);
		actions.add(imgObsCharActions);
		actions.add(charQuantificationActions);
		actions.add(scaleActions);
		actions.add(ordinalLevelActions);
		actions.add(numericalActions);
		actions.add(quantileActions);
		actions.add(intervalActions);
		
		initExpandCollapseActions();
		initMoveUpDownActions();
		initTemplateActions();
		initComponentActions();
		initQuestionTypeActions();
		initGeomShapeActions();
		initCalculationActions();
		initTagActions();
		initAllowedTermActions();
		initValidTermActions();
		initAnatomicEntityActions();
		initAnatomicEntityCharActions();
		initInferenceActions();
		initNonQuantifiableActions();
		initImgObsActions();
		initImgObsCharActions();
		initCharQuantificationActions();
		initScaleActions();
		initNumericalActions();
		initInervalActions();
		initQuantileActions();
	}

	public void setEditFormManager(CanShowEditForm editFormManager) {
		this.editFormManager = editFormManager;
	}
	
	private void initTree() {
		tree.enableContextMenu();
		
		tree.addNodeSelectionListener(new NodeSelectionListener<TemplateNodeValue>() {
			@Override
			public void onNodeSelected(TemplateNodeValue nodeValue) {
				ActionSet actions = nodeActions.get(nodeValue.getNodeType());
				
				// show/hide form
				Command showFormCommand = formShowCommands.get(nodeValue.getNodeType());
				if (showFormCommand != null) {
					showFormCommand.execute();
				} else {
					// hide edit form if no form to show
					hideEditForm();
				}
				
				tree.getContextMenu().removeAll();
				root.clearToolBar();
				
				if (actions != null) {
					// apply rules according to the node state
					modificationRules.applyRulesToNode(nodeValue, actions);
					
					// add actions to the toolbar and context menu
					for (CommandAction action : actions.getAll()) {
						if (actions.isSeparator(action)) {
							root.addToolBarSeparator();
							tree.getContextMenu().addSeparator();
						} else {
							root.addToolBarAction(action);
							tree.getContextMenu().add(action);
						}
					}
					
					// add custom actions
					if (modificationRules.isMoveUpDownAllowed(nodeValue)) {
						modificationRules.applyRulesToMoveUpDownActions(nodeValue, moveUpDownActions);
						root.addToolBarSeparator();
						root.addToolBarAction(moveUpDownActions.get(MoveUpDownAction.UP));
						root.addToolBarAction(moveUpDownActions.get(MoveUpDownAction.DOWN));
						tree.getContextMenu().addSeparator();
						tree.getContextMenu().add(moveUpDownActions.get(MoveUpDownAction.UP));
						tree.getContextMenu().add(moveUpDownActions.get(MoveUpDownAction.DOWN));
					}
				}
			}
		});
	}
	
	private void initWarnings() {
		JScrollPane scroll = new JScrollPane(warningsTable);
		scroll.getViewport().setBackground(Color.white);
		scroll.setPreferredSize(new Dimension((int) scroll.getPreferredSize().getWidth(), WARNINGS_PANE_HEIGHT));
		root.setBottomSplitAreaComponent(scroll);
		
		IconColumn<TemplateValidationError> iconColumn = new IconColumn<TemplateValidationError>(
				new IconColumnValue<TemplateValidationError>() {
			private Icon warningIcon = miscImages.getValidationWarningIcon().loadIcon();
			
			@Override
			public Icon getValue(TemplateValidationError source) {
				return warningIcon;
			}
		}, Const.EMPTY, 20);
		warningsTable.addGenericColumn(iconColumn, false);
		
		warningsTable.addTextColumn(new TextColumnValue<TemplateValidationError>() {
			@Override
			public String getValue(TemplateValidationError source) {
				return source.getValidationError().getMessage();
			}
		}, Const.COLUMN_DESCRIPTION, 500, false);
		
		warningsTable.addTextColumn(new TextColumnValue<TemplateValidationError>() {
			@Override
			public String getValue(TemplateValidationError source) {
				return source.getNodeType().getFullName();
			}
		}, Const.COLUMN_ELEMENT, 240, false);
	}
	
	private void initNodeActions() {
		nodeActions.put(TemplateNodeType.TEMPLATE, templateActions);
		nodeActions.put(TemplateNodeType.COMPONENT, componentActions);
		nodeActions.put(TemplateNodeType.QUESTION_TYPE, qstTypeActions);
		nodeActions.put(TemplateNodeType.GEOMETRIC_SHAPE, geomShapeActions);
		nodeActions.put(TemplateNodeType.CALCULATION, calculationActions);
		nodeActions.put(TemplateNodeType.CALCULATION_TYPE, calcTypeActions);
		nodeActions.put(TemplateNodeType.ALGORITHM_TYPE, algorithmTypeActions);
		nodeActions.put(TemplateNodeType.TAG, tagActions);
		nodeActions.put(TemplateNodeType.ALLOWED_TERM, termActions);
		nodeActions.put(TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION, termWithQuantActions);
		nodeActions.put(TemplateNodeType.VALID_TERM, validTermActions);
		nodeActions.put(TemplateNodeType.ANATOMIC_ENTITY, anatomicEntityActions);
		nodeActions.put(TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC, anatomicEntityCharActions);
		nodeActions.put(TemplateNodeType.INFERENCE, inferenceActions);
		nodeActions.put(TemplateNodeType.NON_QUANTIFIABLE, nonQuantActions);
		nodeActions.put(TemplateNodeType.IMAGING_OBSERVATION, imgObsActions);
		nodeActions.put(TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC, imgObsCharActions);
		nodeActions.put(TemplateNodeType.CHARACTERISTIC_QUANTIFICATION, charQuantificationActions);
		nodeActions.put(TemplateNodeType.SCALE, scaleActions);
		nodeActions.put(TemplateNodeType.ORDINAL_LEVEL, ordinalLevelActions);
		nodeActions.put(TemplateNodeType.NUMERICAL, numericalActions);
		nodeActions.put(TemplateNodeType.QUANTILE, quantileActions);
		nodeActions.put(TemplateNodeType.INTERVAL, intervalActions);
	}
	
	private void initExpandCollapseActions() {
		JPanel holder = new JPanel(new FlowLayout());
		holder.setBorder(new EmptyBorder(new Insets(0, 0, 0, 6)));
		
		JLabel expand = new JLabel(miscImages.getExpandIcon().loadIcon());
		expand.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		
		expand.addMouseListener(new MouseAdapter() { 
			public void mouseClicked(MouseEvent e) {
				for (int i = 0; i < tree.getRowCount(); i++) {
					tree.expandRow(i);
				}
			}
		});
		
		JLabel collapse = new JLabel(miscImages.getCollapseIcon().loadIcon());
		collapse.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		
		collapse.addMouseListener(new MouseAdapter() { 
			public void mouseClicked(MouseEvent e) {
				for (int i = tree.getRowCount() - 1; i > 0 ; i--) {
					tree.collapseRow(i);
				}
			}
		});
		
		holder.add(expand);
		holder.add(collapse);
		
		root.addHeaderRightComponent(holder);
	}
	
	private void initMoveUpDownActions() {
		CommandAction moveUp = new CommandAction(HNT_MOVE_UP, images.getMoveUpIcon());
		moveUpDownActions.add(MoveUpDownAction.UP, moveUp);
		
		CommandAction moveDown = new CommandAction(HNT_MOVE_DOWN, images.getMoveDownIcon());
		moveUpDownActions.add(MoveUpDownAction.DOWN, moveDown);
	}
	
	private void initTemplateActions() {
		CommandAction createComponent = new CommandAction(HNT_CREATE_COMPONENT, images.getCreateComponentIcon());
		templateActions.add(TemplateAction.CREATE_COMPONENT, createComponent);
		
		CommandAction createTag = new CommandAction(HNT_CREATE_TAG, images.getCreateTagIcon());
		templateActions.add(TemplateAction.CREATE_TAG, createTag);
	}
	
	private void initComponentActions() {
		CommandAction createQstType = new CommandAction(HNT_CREATE_QST_TYPE, images.getCreateQuestionTypeIcon());
		componentActions.add(ComponentAction.CREATE_QST_TYPE, createQstType);
		
		CommandAction createAnEntity = new CommandAction(HNT_CREATE_AN_ENTITY, images.getCreateAnatomicEntityIcon());
		componentActions.add(ComponentAction.CREATE_AN_ENTITY, createAnEntity);
		
		CommandAction createImgObs = new CommandAction(HNT_CREATE_IMG_OBS, images.getCreateImageObservationIcon());
		componentActions.add(ComponentAction.CREATE_IMG_OBS, createImgObs);
		
		CommandAction createInference = new CommandAction(HNT_CREATE_INFERENCE, images.getCreateInferenceIcon());
		componentActions.add(ComponentAction.CREATE_INFERENCE, createInference);
		
		CommandAction createCalculation = new CommandAction(HNT_CREATE_CALCULATION, images.getCreateCalculationIcon());
		componentActions.add(ComponentAction.CREATE_CALCULATION, createCalculation);
		
		CommandAction createGeomShape = new CommandAction(HNT_CREATE_GEOM_SHAPE, images.getCreateShapeIcon());
		componentActions.add(ComponentAction.CREATE_GEOM_SHAPE, createGeomShape);
		
		CommandAction addAllowedTerms = new CommandAction(HNT_ADD_ALLOWED_TERMS, images.getCreateAllowedTermIcon());
		componentActions.add(ComponentAction.ADD_ALLOWED_TERMS, addAllowedTerms);
		
		CommandAction deleteComponent = new CommandAction(HNT_DELETE_COMPONENT, images.getDeleteIcon());
		componentActions.addSeparator();
		componentActions.add(ComponentAction.DELETE, deleteComponent);
	}

	private void initQuestionTypeActions() {
		CommandAction addValidTerms = new CommandAction(HNT_ADD_VALID_TERMS, images.getCreateValidTermIcon());
		qstTypeActions.add(QuestionTypeAction.ADD_VALID_TERMS, addValidTerms);
		
		CommandAction delete = new CommandAction(HNT_DELETE_QST_TYPE, images.getDeleteIcon());
		qstTypeActions.addSeparator();
		qstTypeActions.add(QuestionTypeAction.DELETE, delete);
	}
	
	private void initGeomShapeActions() {
		CommandAction delete = new CommandAction(HNT_DELETE_GEOM_SHAPE, images.getDeleteIcon());
		geomShapeActions.add(GeometricShapeAction.DELETE, delete);
	}
	
	private void initCalculationActions() {
		// calculation
		CommandAction createCalcType = new CommandAction(HNT_CREATE_CALC_TYPE, images.getCreateCalcTypeIcon());
		calculationActions.add(СalculationAction.CREATE_CALC_TYPE, createCalcType);
		
		CommandAction deleteCalculation = new CommandAction(HNT_DELETE_CALCULATION, images.getDeleteIcon());
		calculationActions.addSeparator();
		calculationActions.add(СalculationAction.DELETE, deleteCalculation);
		
		// calc type
		CommandAction addValidTerms = new CommandAction(Const.HNT_ADD_VALID_TERMS, images.getCreateValidTermIcon());
		calcTypeActions.add(CalculationTypeAction.ADD_VALID_TERMS, addValidTerms);
		
		CommandAction createAlgorithmType = new CommandAction(HNT_CREATE_ALGORITHM_TYPE, 
				images.getCreateAlgorithmTypeIcon());
		calcTypeActions.add(CalculationTypeAction.CREATE_ALGORITHM_TYPE, createAlgorithmType);
		
		CommandAction deleteCalcType = new CommandAction(HNT_DELETE_CALC_TYPE, images.getDeleteIcon());
		calcTypeActions.addSeparator();
		calcTypeActions.add(CalculationTypeAction.DELETE, deleteCalcType);
		
		// algorithm type
		CommandAction deleteAlgorithmType = new CommandAction(HNT_DELETE_ALGORITHM_TYPE, images.getDeleteIcon());
		algorithmTypeActions.add(AlgorithmTypeAction.DELETE, deleteAlgorithmType);
	}
	
	private void initAnatomicEntityActions() {
		CommandAction createChar = new CommandAction(HNT_CREATE_AN_ENTITY_CHAR, images.getCreateAnatomicEntityCharIcon());
		anatomicEntityActions.add(AnatomicEntityAction.CREATE_AN_ENTITY_CHAR, createChar);
		
		CommandAction delete = new CommandAction(HNT_DELETE_AN_ENTITY, images.getDeleteIcon());
		anatomicEntityActions.addSeparator();
		anatomicEntityActions.add(AnatomicEntityAction.DELETE, delete);
	}
	
	private void initAnatomicEntityCharActions() {
		CommandAction createQstType = new CommandAction(HNT_CREATE_QST_TYPE, images.getCreateQuestionTypeIcon());
		anatomicEntityCharActions.add(AnatomicEntityCharAction.CREATE_QST_TYPE, createQstType);
		
		CommandAction addAllowedTerms = new CommandAction(HNT_ADD_ALLOWED_TERMS, images.getCreateAllowedTermIcon());
		anatomicEntityCharActions.add(AnatomicEntityCharAction.ADD_ALLOWED_TERMS, addAllowedTerms);
		
		CommandAction delete = new CommandAction(HNT_DELETE_AN_ENTITY_CHAR, images.getDeleteIcon());
		anatomicEntityCharActions.addSeparator();
		anatomicEntityCharActions.add(AnatomicEntityCharAction.DELETE, delete);
	}
	
	private void initImgObsActions() {
		CommandAction createChar = new CommandAction(HNT_CREATE_IMG_OBS_CHAR, images.getCreateImageObservationCharIcon());
		imgObsActions.add(ImagingObservationAction.CREATE_IMG_OBS_CHAR, createChar);
		
		CommandAction delete = new CommandAction(HNT_DELETE_IMG_OBS, images.getDeleteIcon());
		imgObsActions.addSeparator();
		imgObsActions.add(ImagingObservationAction.DELETE, delete);
	}
	
	private void initImgObsCharActions() {
		CommandAction createQstType = new CommandAction(HNT_CREATE_QST_TYPE, images.getCreateQuestionTypeIcon());
		imgObsCharActions.add(ImagingObservationCharAction.CREATE_QST_TYPE, createQstType);
		
		CommandAction addAllowedTerms = new CommandAction(HNT_ADD_ALLOWED_TERMS, images.getCreateAllowedTermIcon());
		imgObsCharActions.add(ImagingObservationCharAction.ADD_ALLOWED_TERMS, addAllowedTerms);
		
		CommandAction delete = new CommandAction(HNT_DELETE_IMG_OBS_CHAR, images.getDeleteIcon());
		imgObsCharActions.addSeparator();
		imgObsCharActions.add(ImagingObservationCharAction.DELETE, delete);
	}
	
	private void initAllowedTermActions() {
		// simple allowed term
		CommandAction addValidTerms = new CommandAction(HNT_ADD_VALID_TERMS, images.getCreateValidTermIcon());
		termActions.add(AllowedTermAction.ADD_VALID_TERMS, addValidTerms);
		
//		CommandAction createNonQuantifiable = new CommandAction(HNT_CREATE_NON_QUANT, 
//				images.getCreateNonQuantifiableIcon());
//		termActions.add(AllowedTermAction.CREATE_NON_QUANT, createNonQuantifiable);
		
		CommandAction deleteTerm = new CommandAction(HNT_DELETE_ALLOWED_TERM, images.getDeleteIcon());
		termActions.addSeparator();
		termActions.add(AllowedTermAction.DELETE, deleteTerm);
		
		// allowed term with quantification
		CommandAction addValidTermsToTermWithQuant = new CommandAction(HNT_ADD_VALID_TERMS, 
				images.getCreateValidTermIcon());
		termWithQuantActions.add(AllowedTermWithQuantAction.ADD_VALID_TERMS, addValidTermsToTermWithQuant);
		
		CommandAction createCharQuant = new CommandAction(HNT_CREATE_CHAR_QUANT, 
				images.getCreateCharacteristicQuantificationIcon());
		termWithQuantActions.add(AllowedTermWithQuantAction.CREATE_CHAR_QUANT, createCharQuant);
		
		CommandAction deleteTermWithQuant = new CommandAction(HNT_DELETE_ALLOWED_TERM, images.getDeleteIcon());
		termWithQuantActions.addSeparator();
		termWithQuantActions.add(AllowedTermWithQuantAction.DELETE, deleteTermWithQuant);
	}
	
	private void initValidTermActions() {
		CommandAction addValidTerms = new CommandAction(HNT_ADD_VALID_TERMS, images.getCreateValidTermIcon());
		validTermActions.add(ValidTermAction.ADD_VALID_TERMS, addValidTerms);
		
		CommandAction deleteTerm = new CommandAction(HNT_DELETE_VALID_TERM, images.getDeleteIcon());
		validTermActions.addSeparator();
		validTermActions.add(ValidTermAction.DELETE, deleteTerm);
	}
	
	private void initCharQuantificationActions() {
		CommandAction createNonQuant = new CommandAction(HNT_CREATE_NON_QUANT, images.getCreateNonQuantifiableIcon());
		charQuantificationActions.add(CharQuantificationAction.CREATE_NON_QUANT, createNonQuant);
		
		CommandAction createScale = new CommandAction(HNT_CREATE_SCALE, images.getCreateScaleIcon());
		charQuantificationActions.add(CharQuantificationAction.CREATE_SCALE, createScale);
		
		CommandAction createNumerical = new CommandAction(HNT_CREATE_NUMERICAL, images.getCreateNumericalIcon());
		charQuantificationActions.add(CharQuantificationAction.CREATE_NUMERICAL, createNumerical);
		
		CommandAction createQuantile = new CommandAction(HNT_CREATE_QUANTILE, images.getCreateQuantileIcon());
		charQuantificationActions.add(CharQuantificationAction.CREATE_QUANTILE, createQuantile);
		
		CommandAction createInterval = new CommandAction(HNT_CREATE_INTERVAL, images.getCreateIntervalIcon());
		charQuantificationActions.add(CharQuantificationAction.CREATE_INTERVAL, createInterval);
		
		CommandAction delete = new CommandAction(HNT_DELETE_CHAR_QUANT, images.getDeleteIcon());
		charQuantificationActions.addSeparator();
		charQuantificationActions.add(CharQuantificationAction.DELETE, delete);
	}
	
	private void initScaleActions() {
		CommandAction createOrdLevel = new CommandAction(HNT_CREATE_ORDINAL_LEVEL, images.getCreateOrdinalLevelIcon());
		scaleActions.add(ScaleAction.CREATE_ORD_LEVEL, createOrdLevel);
		
		CommandAction deleteScale = new CommandAction(HNT_DELETE_SCALE, images.getDeleteIcon());
		scaleActions.addSeparator();
		scaleActions.add(ScaleAction.DELETE, deleteScale);
		
		// ordinal level
		CommandAction deleteOrdLevel = new CommandAction(HNT_DELETE_ORDINAL_LEVEL, images.getDeleteIcon());
		ordinalLevelActions.add(OrdinalLevelAction.DELETE, deleteOrdLevel);
	}
	
	private void initNumericalActions() {
		CommandAction delete = new CommandAction(HNT_DELETE_NUMERICAL, images.getDeleteIcon());
		numericalActions.add(NumericalAction.DELETE, delete);
	}
	
	private void initInervalActions() {
		CommandAction delete = new CommandAction(HNT_DELETE_INTERVAL, images.getDeleteIcon());
		intervalActions.add(IntervalAction.DELETE, delete);
	}
	
	private void initQuantileActions() {
		CommandAction delete = new CommandAction(HNT_DELETE_QUANTILE, images.getDeleteIcon());
		quantileActions.add(QuantileAction.DELETE, delete);
	}
	
	private void initNonQuantifiableActions() {
		CommandAction delete = new CommandAction(Const.HNT_DELETE_NON_QUANT, images.getDeleteIcon());
		nonQuantActions.add(NonQuantifiableAction.DELETE, delete);
	}
	
	private void initInferenceActions() {
		CommandAction createQuestType = new CommandAction(HNT_CREATE_QST_TYPE, images.getCreateQuestionTypeIcon());
		inferenceActions.add(InferenceAction.CREATE_QST_TYPE, createQuestType);
		
		CommandAction deleteInference = new CommandAction(Const.HNT_DELETE_INFERENCE, images.getDeleteIcon());
		inferenceActions.addSeparator();
		inferenceActions.add(InferenceAction.DELETE, deleteInference);
	}
	
	private void initTagActions() {
		// tag
		CommandAction deleteTag = new CommandAction(HNT_DELETE_TAG, images.getDeleteIcon());
		tagActions.add(TagAction.DELETE, deleteTag);
	}
	
	@Override
	public Component asComponent() {
		return root;
	}

	@Override
	public void setActiveTemplate(Template template) {
		treeManager.setTemplate(template);
	}

	@Override
	public void setWarnings(Collection<TemplateValidationError> warnings) {
		warningsTable.setValues(warnings);
	}

	@Override
	public void clearWarnings() {
		warningsTable.clear();
	}

	@SuppressWarnings("unchecked")
	@Override
	public <T> T getSelectedNodeValue() {
		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
		TemplateNodeValue nodeValue = ((TemplateNodeValue) node.getUserObject());
		return (T) nodeValue.getValue();
	}
	
	@Override
	public void setCommand(Object actionKey, Command command) {
		for (ActionSet actionSet : actions) {
			CommandAction action = actionSet.get(actionKey);
			if (action != null) {
				action.setCommand(command);
				break;
			}
		}
	}
	
	@Override
	public void setCommand(MoveUpDownAction actionKey, Command command) {
		CommandAction action = moveUpDownActions.get(actionKey);
		if (action != null) {
			action.setCommand(command);
		}
	}
	
	@Override
	public void setShowFormCommand(TemplateNodeType nodeType, Command command) {
		formShowCommands.put(nodeType, command);
	}
	
	// view

	@Override
	public void hideEditForm() {
		editFormManager.hideEditForm();
	}

	@Override
	public void showEditForm(Component c, boolean forceShow) {
		editFormManager.showEditForm(c, forceShow);
	}
	
	@Override
	public void showEditForm(Component c) {
		editFormManager.showEditForm(c, false);
	}
	
	@Override
	public void showWarnings() {
		root.showBottomSplitArea();
	}

	@Override
	public void hideWarnings() {
		root.hideBottomSplitArea();
	}

	@Override
	public void clear() {
		treeManager.clear();
		root.clearToolBar();
		tree.getContextMenu().removeAll();		
	}

	@Override
	public void selectRootNode() {
		treeManager.selectRootNode();
	}

	@Override
	public TemplateTreeManager getTreeManager() {
		return treeManager;
	}

	// set listeners
	
	@Override
	public void addWarningSelectionListeners(final TemplateWarningSelectionListener ... listeners) {
		warningsTable.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				TemplateValidationError warning = warningsTable.getSelectedValue();
				if (warning != null) {
					for (TemplateWarningSelectionListener listener : listeners) {
						// only if template was selected
						// (this event also can be fired when we reload data into the table and selection is lost)
						listener.onWarningSelected(warning);
					}
				}
			}
		});
	}
	
}
