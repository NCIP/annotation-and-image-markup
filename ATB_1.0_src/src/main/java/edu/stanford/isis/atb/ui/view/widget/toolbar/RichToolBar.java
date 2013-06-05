/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.toolbar;

import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JToolBar;
import javax.swing.border.EmptyBorder;

import edu.stanford.isis.atb.ui.action.CommandAction;

/**
 * Custom tool bar that handles complex cases:
 * - actions with sub-actions
 * 
 * @author Vitaliy Semeshko
 */
public class RichToolBar extends JToolBar {

	public void add(CommandAction a) {
		// if there are sub actions add menu
		if (a.hasSubActions()) {
			MenuToggleButton b = new MenuToggleButton(a);
			b.setInsets(getDefaultButtonInsets());
			// make transparent
			b.setOpaque(false);
			add(b);
		} else {
			// typical action
			JButton b = super.add(a);
			// set border 
			b.setBorder(new EmptyBorder(getDefaultButtonInsets()));
			// non-focusable
			b.setFocusable(false);
			// make transparent
			b.setOpaque(false);
		}
	}
	
	private Insets getDefaultButtonInsets() {
		return new Insets(4, 4, 4, 4);
	}
	
}
