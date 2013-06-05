/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.validation;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeModel;

import edu.stanford.isis.atb.system.validation.TemplateValidator;
import edu.stanford.isis.atb.system.validation.ValidationError;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeValue;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateTreeValidator {

	private static final TemplateTreeValidator instance = new TemplateTreeValidator(); 

	private TemplateValidator validator = TemplateValidator.getInstance();

	private TemplateTreeValidator() {}

	public static TemplateTreeValidator getInstance() {
		return instance;
	}

	public Set<TemplateValidationError> validateTemplateTree(TreeModel model) {
		Set<TemplateValidationError> validationErrors = new HashSet<TemplateValidationError>();

		List<DefaultMutableTreeNode> nodes = traverse(model);
		
		for (DefaultMutableTreeNode node : nodes) {
			TemplateNodeValue value = (TemplateNodeValue) node.getUserObject();
			Set<ValidationError> violations = validator.validate(value.getValue());
			for (ValidationError violation : violations) {
				validationErrors.add(new TemplateValidationError(violation, value.getNodeType(), node));
			}
		}

		return validationErrors;
	}

	public List<DefaultMutableTreeNode> traverse(TreeModel model) {
		List<DefaultMutableTreeNode> nodes = new ArrayList<DefaultMutableTreeNode>();
		
		if (model != null) {
			Object root = model.getRoot();
			nodes.add((DefaultMutableTreeNode) root);
			walk(model, root, nodes);    
		}
		
		return nodes;
	}

	protected void walk(TreeModel model, Object o, List<DefaultMutableTreeNode> nodes){
		for (int i = 0; i < model.getChildCount(o); i++) {
			Object child = model.getChild(o, i);
			if (model.isLeaf(child))
				nodes.add((DefaultMutableTreeNode) child);
			else {
				nodes.add((DefaultMutableTreeNode) child);
				walk(model, child, nodes); 
			}
		}
	} 

}
