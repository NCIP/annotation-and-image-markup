/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model.tree;

/**
 * User object holder with additional type information.
 * 
 * @author Vitaliy Semeshko
 */
public abstract class NodeValue<E extends Enum<?>> {

	private E nodeType;
	
	private Object value;
	
	public NodeValue(E nodeType, Object value) {
		this.nodeType = nodeType;
		this.value = value;
	}

	public E getNodeType() {
		return nodeType;
	}

	@SuppressWarnings("unchecked")
	public <T> T getValue() {
		return (T) value;
	}
	
	public String toString() {
		return value.toString();
	}
	
}
