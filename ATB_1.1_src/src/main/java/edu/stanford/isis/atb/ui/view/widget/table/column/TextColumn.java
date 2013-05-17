/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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
