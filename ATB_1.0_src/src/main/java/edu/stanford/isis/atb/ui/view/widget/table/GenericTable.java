/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
