/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.base;

import java.awt.Component;

import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane;
import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane.CollapseMode;

/**
 * @author Vitaliy Semeshko
 */
public class ThreeCellSplitPaneView extends TwoCellSplitPaneView {

	private CollapsibleSplitPane splitPaneNested = new CollapsibleSplitPane();

	public ThreeCellSplitPaneView() {
		splitPaneMain.setCollapsible(CollapseMode.COLLAPSE_RIGHT);
		splitPaneNested.setCollapsible(CollapseMode.COLLAPSE_LEFT);
		
		splitPaneMain.setLeftComponent(splitPaneNested);
		splitPaneMain.setResizeWeight(1);
		splitPaneNested.setBorder(null);
	}
	
	public void setLeftComponent(Component c) {
		splitPaneNested.setLeftComponent(c);
	}

	public void setMainComponent(Component c) {
		splitPaneNested.setRightComponent(c);
	}

}
