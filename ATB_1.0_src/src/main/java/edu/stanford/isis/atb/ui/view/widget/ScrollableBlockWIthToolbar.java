/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.Color;
import java.awt.Component;

import javax.swing.JScrollPane;

/**
 * @author Vitaliy Semeshko
 */
public class ScrollableBlockWIthToolbar extends BlockWIthToolbar {
	
	private JScrollPane scrollPane = new JScrollPane();
	
	public ScrollableBlockWIthToolbar() {
		super.setMainComponent(scrollPane);
	}
	
	public void setMainComponent(Component c) {
		scrollPane.setViewportView(c);
	}
	
	public void setScrollableAreaBackground(Color color) {
		scrollPane.getViewport().setBackground(color);
	}
	
}
