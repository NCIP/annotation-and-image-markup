/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table.column;

import java.awt.Color;
import java.awt.Component;
import java.awt.Cursor;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.Icon;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

import edu.stanford.isis.atb.service.Command;

/**
 * @author Vitaliy Semeshko
 */
public class CommandColumn<T> extends GenericColumn<T, String> {

	public CommandColumn(CommandColumnValue<T> value, String caption, int width) {
		super(value, caption, width, false);
		setCellRenderer(new CommandRenderer());
	}

	public void registerTableListeners(JTable table) {
		table.addMouseListener((MouseListener) getCellRenderer());
        table.addMouseMotionListener((MouseMotionListener) getCellRenderer());
	}
	
	public Class<?> getColumnClass() {
		return Command.class;
	}

	/**
	 * @author Vitaliy Semeshko
	 */
	public static abstract class CommandColumnValue<T> implements ColumnValue<T, String> {

		public abstract String getValue(T source);

		public abstract Command getCommand();
		
		public abstract Icon getIcon();
		
		public void setValue(T target, Object value) {}

	}

	private class CommandRenderer extends DefaultTableCellRenderer implements MouseListener, MouseMotionListener {
		private int row = -1, col = -1;
		private Icon icon;
		private Cursor originalCursor;
		
		public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, 
				boolean hasFocus, int row, int column) {
			super.getTableCellRendererComponent(table, value, isSelected, false, row, column);
			
			if (!table.isEditing() && this.row == row && this.col == column) {
				setForeground(Color.red);
			} else if(hasFocus) {
				setForeground(Color.red);
			}else{
				setForeground(Color.blue);
			}

			if (icon == null) {
				icon = ((CommandColumnValue<?>) columnValue).getIcon();
			}

			if (getIcon() == null) {
				setIcon(icon);
			}
			
			return this;
		}
		
		public void mouseMoved(MouseEvent e) {
			JTable table = (JTable)e.getSource();
			Point pt = e.getPoint();
			row = table.rowAtPoint(pt);
			col = table.columnAtPoint(pt);
			
			if (table.getColumnClass(col).equals(Command.class)) {
				// remember original cursor
				if (originalCursor == null) {
					originalCursor = table.getCursor();
				}
				table.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			} else {
				if (originalCursor != null) {
					table.setCursor(originalCursor);
				}
			}
			
			if (row < 0 || col < 0) {
				row = col = -1;
			}
			
			table.repaint();
		}
		
		public void mouseExited(MouseEvent e)  {
			JTable table = (JTable) e.getSource();
			table.setCursor(originalCursor);
			row = col = -1;
			table.repaint();
		}
		
		public void mouseClicked(MouseEvent e) {
			JTable table = (JTable) e.getSource();
			Point pt = e.getPoint();
			int col = table.columnAtPoint(pt);
			
			if (table.getColumnClass(col).equals(Command.class)) {
				((CommandColumnValue<?>) columnValue).getCommand().execute();
			}
		}
		
		public void mouseDragged(MouseEvent e) {}
		
		public void mouseEntered(MouseEvent e) {}
		
		public void mousePressed(MouseEvent e) {}
		
		public void mouseReleased(MouseEvent e) {}
		
	}

}
