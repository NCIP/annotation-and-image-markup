/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.table;

import javax.swing.DefaultListSelectionModel;

/**
 * @author Vitaliy Semeshko
 */
public class GenericTableSelectionModel extends DefaultListSelectionModel {

	private boolean eventsEnabled = true;
	
	public boolean isEventsEnabled() {
		return eventsEnabled;
	}

	public void setEventsEnabled(boolean eventsEnabled) {
		this.eventsEnabled = eventsEnabled;
	}

	protected void fireValueChanged(int firstIndex, int lastIndex, boolean isAdjusting) {
		if (eventsEnabled) {
			super.fireValueChanged(firstIndex, lastIndex, isAdjusting);
		}
	}
	
}
