/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableColumnModel;

import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.view.widget.table.column.BooleanColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.BooleanColumn.BooleanColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.GenericColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * @author Vitaliy Semeshko
 */
public class GenericTable<T> extends JTable {

	//private static final Color evenColor = new Color(250, 250, 255);

	private int defaultSortColumnIndex = -1;

	public GenericTable() {
		super(null, new DefaultTableColumnModel(), new GenericTableSelectionModel());
		setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		// set empty model
		setModel(new GenericTableModel());
		
		// disable auto resize (allow horizontal scrolling)
		setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		//		setAutoResizeMode(JTable.AUTO_RESIZE_LAST_COLUMN);

		// enable sorting by default
		setAutoCreateRowSorter(true);
	}

//	@Override 
//	public Component prepareRenderer(TableCellRenderer tcr, int row, int column) {
//		Component c = super.prepareRenderer(tcr, row, column);
//		c.setForeground(getForeground());
//		c.setBackground((row %2 == 0) ? evenColor : getBackground());
//		return c;
//	}

	public void setValues(Collection<T> values) {
		setModel(new GenericTableModel(values));
		// toggle default sort column
		if (defaultSortColumnIndex != -1) {
			getRowSorter().toggleSortOrder(defaultSortColumnIndex);
		}
	}

	public Collection<T> getValues() {
		return getModel().getValues();
	}

	public T getSelectedValue() {
		int selectedRow = getSelectedRow();
		if (selectedRow != -1) {
			return getModel().getValueAt(convertRowIndexToModel(selectedRow));
		}
		return null;
	}

	public void addValue(T value) {
		getModel().addValue(value);
		refresh();
	}

	public void removeSelectedValue() {
		int selectedRow = getSelectedRow();
		if (selectedRow != -1) {
			getModel().removeValue(convertRowIndexToModel(selectedRow));
			refresh();
		}
	}

	public void clear() {
		List<T> emptyList = Collections.emptyList();
		setModel(new GenericTableModel(emptyList));
	}

	@Override
	public void clearSelection() {
		super.clearSelection();
		setFocusable(false);
		setFocusable(true);
	}

	/**
	 * Convenient way to refresh table on demand.
	 */
	public void refresh() {
		int selectedRow = getSelectedRow();
		getModel().fireTableDataChanged();
		selectRow(selectedRow);
	}

	public void selectRow(int row) {
		if (row >= 0 && row < getModel().getRowCount()) {
			boolean eventsEnabled = getSelectionModel().isEventsEnabled();
			getSelectionModel().setEventsEnabled(false);
			try {
				setRowSelectionInterval(row, row);
			} finally {
				getSelectionModel().setEventsEnabled(eventsEnabled);
			}
		}
	}
	
	public void addGenericColumn(GenericColumn<T, ?> column, boolean isDefaultSort) {
		int columnCount = columnModel.getColumnCount();
		column.setModelIndex(columnCount);
		columnModel.addColumn(column);

		// initialize default column sorting (if wasn't previously)
		if (isDefaultSort && defaultSortColumnIndex == -1) {
			defaultSortColumnIndex = columnCount;
		}

		column.registerTableListeners(this);
	}

	public void addTextColumn(TextColumnValue<T> value, String caption, int width, 
			boolean isDefaultSort, boolean editable) {
		TextColumn<T> column = new TextColumn<T>(value, caption, width, editable);
		addGenericColumn(column, isDefaultSort);
	}

	public void addTextColumn(TextColumnValue<T> value, String caption, int width, boolean editable) {
		this.addTextColumn(value, caption, width, false, editable);
	}

	public void addBooleanColumn(BooleanColumnValue<T> value, String caption, int width, 
			boolean isDefaultSort, boolean editable) {
		BooleanColumn<T> column = new BooleanColumn<T>(value, caption, width, editable);
		addGenericColumn(column, isDefaultSort);
	}

	public void addBooleanColumn(BooleanColumnValue<T> value, String caption, int width, boolean editable) {
		this.addBooleanColumn(value, caption, width, false, editable);
	}

	@SuppressWarnings("unchecked")
	public GenericTableModel getModel() {
		return (GenericTableModel) super.getModel();
	}

	public GenericTableSelectionModel getSelectionModel() {
		return (GenericTableSelectionModel) super.getSelectionModel();
	}
	
	private class GenericTableModel extends AbstractTableModel {

		private List<T> values = new ArrayList<T>();

		public GenericTableModel() {}
		
		public GenericTableModel(Iterable<T> values) {
			for (T value : values) {
				this.values.add(value);
			}
		}

		@Override
		public int getRowCount() {
			return values == null ? 0 : values.size();
		}

		@Override
		public int getColumnCount() {
			return columnModel.getColumnCount();
		}

		@Override
		public Object getValueAt(int rowIndex, int columnIndex) {
			@SuppressWarnings("unchecked")
			GenericColumn<T, ?> column = (GenericColumn<T, ?>) columnModel.getColumn(columnIndex);
			if (rowIndex >= 0 && rowIndex < values.size()) {
				return column.getValue(values.get(rowIndex));
			} 
			return null;
		}

		public T getValueAt(int rowIndex) {
			if (rowIndex >= values.size()) {
				throw new ATBException("Accessing non-existing row. Index: " + rowIndex + " size: " + values.size());
			}
			return values.get(rowIndex);
		}

		public Class<?> getColumnClass(int columnIndex) {
			@SuppressWarnings("unchecked")
			GenericColumn<T, ?> column = (GenericColumn<T, ?>) columnModel.getColumn(columnIndex);
			return column.getColumnClass();
		}

		public boolean isCellEditable(int row, int col) {
			@SuppressWarnings("unchecked")
			GenericColumn<T, ?> column = (GenericColumn<T, ?>) columnModel.getColumn(col);
			return column.isEditable();
		}

		public void setValueAt(Object value, int row, int col) {
			@SuppressWarnings("unchecked")
			GenericColumn<T, ?> column = (GenericColumn<T, ?>) columnModel.getColumn(col);
			column.setValue(values.get(row), value);
		}

		public void addValue(T value) {
			values.add(value);
		}

		public void removeValue(int rowIndex) {
			if (rowIndex >= values.size()) {
				throw new ATBException("Accessing non-existing row. Index: " + rowIndex + " size: " + values.size());
			}
			values.remove(rowIndex);
		}

		public List<T> getValues() {
			return values;
		}

	}

}
