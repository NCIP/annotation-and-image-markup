/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.impl;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CalculationType;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.CodedTerm;
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
import edu.stanford.isis.atb.ui.model.tree.TemplateDomainConverter;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeValue;
import edu.stanford.isis.atb.ui.view.template.TemplateTreeManager;
import edu.stanford.isis.atb.ui.view.widget.tree.TemplateTree;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateTreeManagerImpl implements TemplateTreeManager {

	private TemplateTree tree;
	
	private TemplateDomainConverter converter = TemplateDomainConverter.getInstance();
	
	public TemplateTreeManagerImpl(TemplateTree tree) {
		this.tree = tree;
	}

	@Override
	public void clear() {
		tree.setModel(null);
	}

	@Override
	public void setTemplate(Template template) {
		tree.setModel(converter.template(template));
		selectRootNode();
	}

	@Override
	public void addComponent(TemplateComponent component) {
		DefaultMutableTreeNode newNode = converter.templateComponent(component);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.COMPONENT);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addQuestionType(QuestionType questionType) {
		DefaultMutableTreeNode newNode = converter.questionType(questionType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addNonQuantifiable(NonQuantifiable nonQuantifiable) {
		DefaultMutableTreeNode newNode = converter.nonQuantifiable(nonQuantifiable);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addAllowedTerm(AllowedTerm allowedTerm) {
		DefaultMutableTreeNode newNode = converter.allowedTerm(allowedTerm);
		DefaultMutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}
	
	@Override
	public void addAllowedTermWithQuantification(AllowedTermWithQuantification allowedTerm) {
		DefaultMutableTreeNode newNode = converter.allowedTermWithQuantification(allowedTerm);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}
	
	@Override
	public void addValidTerm(ValidTerm validTerm) {
		DefaultMutableTreeNode newNode = converter.validTerm(validTerm);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.VALID_TERM);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}

	@Override
	public void addCalculationType(CalculationType calculationType) {
		DefaultMutableTreeNode newNode = converter.calculationType(calculationType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAlgorithmType(AlgorithmType algorithmType) {
		DefaultMutableTreeNode newNode = converter.algorithmType(algorithmType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addCharacteristicQuantification(CharacteristicQuantification characteristicQuantification) {
		DefaultMutableTreeNode newNode = converter.characteristicQuantifications(characteristicQuantification);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addScale(Scale scale) {
		DefaultMutableTreeNode newNode = converter.scale(scale);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addNumerical(Numerical numerical) {
		DefaultMutableTreeNode newNode = converter.numerical(numerical);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.NUMERICAL);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addInterval(Interval interval) {
		DefaultMutableTreeNode newNode = converter.interval(interval);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.INTERVAL);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addQuantile(Quantile quantile) {
		DefaultMutableTreeNode newNode = converter.quantile(quantile);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAnatomicEntity(AnatomicEntity anatomicEntity) {
		DefaultMutableTreeNode newNode = converter.anatomicEntity(anatomicEntity);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAnatomicEntityChar(AnatomicEntityCharacteristic characteristic) {
		DefaultMutableTreeNode newNode = converter.anatomicEntityCharacteristic(characteristic);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addImagingObservation(ImagingObservation imagingObservation) {
		DefaultMutableTreeNode newNode = converter.imagingObservation(imagingObservation);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addImagingObservationChar(ImagingObservationCharacteristic characteristic) {
		DefaultMutableTreeNode newNode = converter.imagingObservationCharacteristic(characteristic);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addGeometricShape(GeometricShape geometricShape) {
		DefaultMutableTreeNode newNode = converter.geometricShape(geometricShape);
		MutableTreeNode node = getSelectedNode();
		int childCount = node.getChildCount();
		insertNode(newNode, node, childCount > 0 ? 1 : 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addCalculation(Calculation calculation) {
		DefaultMutableTreeNode newNode = converter.calculation(calculation);
		MutableTreeNode node = getSelectedNode();
		int childCount = node.getChildCount();
		insertNode(newNode, node, childCount > 0 ? 1 : 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addInference(Inference inference) {
		DefaultMutableTreeNode newNode = converter.inference(inference);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addTag(Tag tag) {
		DefaultMutableTreeNode newNode = converter.tag(tag);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addOrdinalLevel(OrdinalLevel ordinalLevel) {
		DefaultMutableTreeNode newNode = converter.ordinalLevel(ordinalLevel);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void removeSelectedNode() {
		DefaultMutableTreeNode node = getSelectedNode(); 
		DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) node.getParent(); 
		
		if (parentNode != null) {
			removeNode(node);
			// select parent node
			tree.setSelectionPath(new TreePath(parentNode.getPath()));
		}
	}
	
	@Override
	public void removeChildNodeTermWithUserObject(CodedTerm term) {
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		DefaultMutableTreeNode currentNode = getSelectedNode();
		
		for (int i = 0; i < model.getChildCount(currentNode); i++) {
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) model.getChild(currentNode, i);
			Object value = ((TemplateNodeValue) node.getUserObject()).getValue();
			if (term.equals(value)) {
				removeNode(node);
			}
		}
	}

	@Override
	public void refreshSelectedNode() {
		((DefaultTreeModel) tree.getModel()).nodeChanged(getSelectedNode());
	}
	
	@Override
	public void selectRootNode() {
		tree.setSelectionRow(0);
	}
	
	@Override
	public void moveSelectedNodeUp() {
		moveNodeUpDown(getSelectedNode(), true);
	}

	@Override
	public void moveSelectedNodeDown() {
		moveNodeUpDown(getSelectedNode(), false);
	}
	
	@Override
	public TreeModel getTreeModel() {
		return tree.getModel();
	}

	@Override
	public void scrollToNodeAndSelect(DefaultMutableTreeNode node) {
		TreePath path = new TreePath(node.getPath());
		tree.scrollPathToVisible(path);
		tree.setSelectionPath(path);
	}
	
	private void moveNodeUpDown(DefaultMutableTreeNode node, boolean isUp) {
		DefaultMutableTreeNode parent = (DefaultMutableTreeNode) node.getParent();
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		int totalCount = model.getChildCount(parent);
		int currentIndex = model.getIndexOfChild(parent, node);
		
		// avoid indexes boundary violation
		if ((isUp && currentIndex == 0) || (!isUp && currentIndex == (totalCount - 1))) {
			return;
		}
		
		removeNode(node);
		model.insertNodeInto(node, parent, isUp ? currentIndex - 1 : currentIndex + 1);
		scrollToNodeAndSelect(node);
	}
	
	private int getLastIndexOfType(TreeNode node, TemplateNodeType type) {
		boolean found = false;
		int i;
		for (i = 0; i < node.getChildCount(); i++) {
			DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(i);
			TemplateNodeValue value = (TemplateNodeValue) child.getUserObject();
			if (value.getNodeType() == type) {
				found = true;
			} else if (found) {
				break;
			}
		}
		
		if (found) {
			return i;
		} else {
			return -1;
		}
		
	}
	
	private DefaultMutableTreeNode getSelectedNode() {
		return (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
	}
	
	private void removeNode(MutableTreeNode node) {
		((DefaultTreeModel) tree.getModel()).removeNodeFromParent(node);
	}
	
	private void insertNode(MutableTreeNode newNode, MutableTreeNode node, int index) {
		((DefaultTreeModel) tree.getModel()).insertNodeInto(newNode, node, index);
	}

}
