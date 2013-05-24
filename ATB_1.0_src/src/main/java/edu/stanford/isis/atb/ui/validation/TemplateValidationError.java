/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.validation;

import javax.swing.tree.DefaultMutableTreeNode;

import edu.stanford.isis.atb.system.validation.ValidationError;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateValidationError {

	private ValidationError validationError;
	
	private TemplateNodeType nodeType;

	private DefaultMutableTreeNode node;
	
	public TemplateValidationError(ValidationError validationError, TemplateNodeType nodeType, 
			DefaultMutableTreeNode node) {
		this.validationError = validationError;
		this.nodeType = nodeType;
		this.node = node;
	}
	
	public ValidationError getValidationError() {
		return validationError;
	}

	public TemplateNodeType getNodeType() {
		return nodeType;
	}
	
	public DefaultMutableTreeNode getNode() {
		return node;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((validationError == null) ? 0 : validationError.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		TemplateValidationError other = (TemplateValidationError) obj;
		if (validationError == null) {
			if (other.validationError != null)
				return false;
		} else if (!validationError.equals(other.validationError))
			return false;
		return true;
	}
	
}
