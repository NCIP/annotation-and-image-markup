/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import java.awt.Component;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;

import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.model.tree.NodeValue;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.ElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * Custom tree node renderer.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateTreeNodeRenderer extends DefaultTreeCellRenderer {

	@SuppressWarnings("rawtypes")
	private Map<TemplateNodeType, ElementRenderer> renderers = new HashMap<TemplateNodeType, ElementRenderer>();
	
	public TemplateTreeNodeRenderer() {
		renderers.put(TemplateNodeType.TEMPLATE, new TemplateRenderer());
		renderers.put(TemplateNodeType.COMPONENT, new ComponentRenderer());
		renderers.put(TemplateNodeType.QUESTION_TYPE, new QuestionTypeRenderer());
		renderers.put(TemplateNodeType.ANATOMIC_ENTITY, new AnatomicEntityRenderer());
		renderers.put(TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC, new AnatomicEntityCharacteristicRenderer());
		renderers.put(TemplateNodeType.IMAGING_OBSERVATION, new ImagingObservationRenderer());
		renderers.put(TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC, new ImagingObservationCharacteristicRenderer());
		renderers.put(TemplateNodeType.VALID_TERM, new ValidTermRenderer());
		renderers.put(TemplateNodeType.ALLOWED_TERM, new AllowedTermRenderer());
		renderers.put(TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION, new AllowedTermWithQuantificationRenderer());
		renderers.put(TemplateNodeType.CHARACTERISTIC_QUANTIFICATION, new CharacteristicQuantificationRenderer());
		renderers.put(TemplateNodeType.NON_QUANTIFIABLE, new NonQuantifiableRenderer());
		renderers.put(TemplateNodeType.INTERVAL, new IntervalRenderer());
		renderers.put(TemplateNodeType.NUMERICAL, new NumericalRenderer());
		renderers.put(TemplateNodeType.ORDINAL_LEVEL, new OrdinalLevelRenderer());
		renderers.put(TemplateNodeType.QUANTILE, new QuantileRenderer());
		renderers.put(TemplateNodeType.SCALE, new ScaleRenderer());
		renderers.put(TemplateNodeType.INFERENCE, new InferenceRenderer());
		renderers.put(TemplateNodeType.GEOMETRIC_SHAPE, new GeometricShapeRenderer());
		renderers.put(TemplateNodeType.CALCULATION, new CalculationRenderer());
		renderers.put(TemplateNodeType.CALCULATION_TYPE, new CalculationTypeRenderer());
		renderers.put(TemplateNodeType.ALGORITHM_TYPE, new AlgorithmTypeRenderer());
		renderers.put(TemplateNodeType.TAG, new TagRenderer());
	}
	
	public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded,
			boolean leaf, int row, boolean hasFocus) {
		// basic operations
		super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
		
		// render node according to the type
		renderNode(((DefaultMutableTreeNode) value).getUserObject());

		return this;
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	private void renderNode(Object value) {
		NodeValue nodeValue = ((NodeValue) value);

		ElementRenderer renderer = renderers.get(nodeValue.getNodeType());
		
		if (renderer == null) {
			throw new RuntimeException("No renderer found for node type: " + nodeValue.getNodeType());
		}
		
		RenderInfo info = renderer.collectRenderInfo(nodeValue.getValue());
		
		setText(info.getText());
		setToolTipText(info.getToolTipText());
		setIcon(info.getIcon());
	}

}
