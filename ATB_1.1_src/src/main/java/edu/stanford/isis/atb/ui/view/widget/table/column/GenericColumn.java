/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table.column;

import javax.swing.JTable;
import javax.swing.table.TableColumn;

/**
 * @author Vitaliy Semeshko
 */
public abstract class GenericColumn<T, C> extends TableColumn {

	protected ColumnValue<T, C> columnValue;
	
	private boolean editable;
	
	public GenericColumn(ColumnValue<T, C> value, String caption, int width, boolean editable) {
		super(-1, width);
		this.columnValue = value;
		setHeaderValue(caption);
		this.editable = editable;
	}
	
	public C getValue(T source) {
		return columnValue.getValue(source);
	}
	
	public void setValue(T target, Object value) {
		columnValue.setValue(target, value);
	}

	public abstract Class<?> getColumnClass();

	/**
	 * Columns can access table after being added to it.
	 * 
	 * @param table table that accepts column
	 */
	public void registerTableListeners(JTable table) {}
	
	public boolean isEditable() {
		return editable;
	}
	
	/**
	 * Interface that provides ability for the column to get value.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface ColumnValue<T, C> {
		
		public C getValue(T source);
		
		public void setValue(T source, Object value);
		
	}
	
}
