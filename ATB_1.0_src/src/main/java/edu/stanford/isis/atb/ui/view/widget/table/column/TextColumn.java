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
public class TextColumn<T> extends GenericColumn<T, String> {

	public TextColumn(ColumnValue<T, String> value, String caption, int width, boolean editable) {
		super(value, caption, width, editable);
	}

	public Class<?> getColumnClass() {
		return Object.class;
	}
	
	/**
	 * @author Vitaliy Semeshko
	 */
	public static abstract class TextColumnValue<T> implements ColumnValue<T, String> {
		
		public abstract String getValue(T source);
		
		public void setValue(T target, Object value) {}
		
	}
	
}
