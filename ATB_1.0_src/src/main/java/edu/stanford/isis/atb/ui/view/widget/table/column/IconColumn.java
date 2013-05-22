/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table.column;

import java.awt.Component;

import javax.swing.Icon;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

/**
 * @author Vitaliy Semeshko
 */
public class IconColumn<T> extends GenericColumn<T, Icon> {

	public IconColumn(IconColumnValue<T> value, String caption, int width) {
		super(value, caption, width, false);
		setCellRenderer(new CommandRenderer());
	}
	
	public Class<?> getColumnClass() {
		return Object.class;
	}

	/**
	 * @author Vitaliy Semeshko
	 */
	public static abstract class IconColumnValue<T> implements ColumnValue<T, Icon> {
		
		public abstract Icon getValue(T source);
		
		public void setValue(T target, Object value) {}
		
	}

	private class CommandRenderer extends DefaultTableCellRenderer {
		
		public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, 
				boolean hasFocus, int row, int column) {
			super.getTableCellRendererComponent(table, null, isSelected, false, row, column);

			setIcon((Icon) value);
			
			return this;
		}
		
	}

}
