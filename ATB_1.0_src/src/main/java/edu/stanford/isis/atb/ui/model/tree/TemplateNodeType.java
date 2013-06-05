/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model.tree;

/**
 * Enumeration of template node types that are used in the tree.
 * 
 * @author Vitaliy Semeshko
 */
public enum TemplateNodeType {

	TEMPLATE("Template"),
	COMPONENT("Component"),
	QUESTION_TYPE("Question"),
	CALCULATION("Calculation"),
	CALCULATION_TYPE("Calculation Type"),
	ALGORITHM_TYPE("Algorithm Type"),
	GEOMETRIC_SHAPE("Geometric Shape"),
	ANATOMIC_ENTITY("Anatomic Entity"),
	ANATOMIC_ENTITY_CHARACTERISTIC("Anatomic Entity Characteristic"),
	CHARACTERISTIC_QUANTIFICATION("Characteristic Quantification"),
	IMAGING_OBSERVATION("Imaging Observation"),
	IMAGING_OBSERVATION_CHARACTERISTIC("Imaging Observation Characteristic"),
	INFERENCE("Inference"),
	VALID_TERM("Valid Term"),
	ALLOWED_TERM("Allowed Term"),
	ALLOWED_TERM_WITH_QUANTIFICATION("Allowed Term With Quantification"),
	NON_QUANTIFIABLE("Non-Quantifiable"),
	SCALE("Scale"),
	ORDINAL_LEVEL("Ordinal Level"),
	NUMERICAL("Numerical"),
	INTERVAL("Interval"),
	QUANTILE("Quantile"),
	TAG("Tag");

	private String fullName;
	
	private TemplateNodeType(String fullName) {
		this.fullName = fullName;
	}

	public String getFullName() {
		return fullName;
	}
	
}
