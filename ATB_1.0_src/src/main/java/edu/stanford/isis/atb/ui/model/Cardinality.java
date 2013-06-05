/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model;

/**
 * @author Vitaliy Semeshko
 */
public class Cardinality {

	private long min;
	
	private long max;

	public Cardinality(long min, long max) {
		this.min = min;
		this.max = max;
	}
	
	public long getMin() {
		return min;
	}

	public long getMax() {
		return max;
	}
	
}
