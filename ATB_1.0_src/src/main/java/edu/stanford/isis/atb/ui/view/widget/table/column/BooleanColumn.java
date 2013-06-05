/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table.column;



/**
 * @author Vitaliy Semeshko
 */
public class BooleanColumn<T> extends GenericColumn<T, Boolean> {

	public BooleanColumn(ColumnValue<T, Boolean> value, String caption, int width, boolean editable) {
		super(value, caption, width, editable);
	}

	public Class<?> getColumnClass() {
		return Boolean.class;
	}
	
	/**
	 * @author Vitaliy Semeshko
	 */
	public static abstract class BooleanColumnValue<T> implements ColumnValue<T, Boolean> {
		
		public abstract Boolean getValue(T source);
		
		public void setValue(T target, Object value) {}
		
	}
	
}
