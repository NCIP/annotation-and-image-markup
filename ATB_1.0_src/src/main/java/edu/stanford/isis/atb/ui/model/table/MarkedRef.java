/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model.table;

/**
 * Wrapper with boolean marker.
 * 
 * @author Vitaliy Semeshko
 */
public class MarkedRef<V> {

	private V value;
	
	private boolean marked;
	
	public MarkedRef(V value, boolean marked) {
		this.value = value;
		this.marked = marked;
	}
	
	public V getValue() {
		return value;
	}
	
	public void setMarked(boolean marked) {
		this.marked = marked;
	}

	public boolean isMarked() {
		return marked;
	}
	
}
