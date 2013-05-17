/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.base;

import java.awt.BorderLayout;
import java.awt.Component;

import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane;

/**
 * @author Vitaliy Semeshko
 */
public class TwoCellSplitPaneView extends AbstractView {

	protected JPanel root = new JPanel(new BorderLayout());
	
	protected CollapsibleSplitPane splitPaneMain = new CollapsibleSplitPane();

	private JPanel holder = new JPanel(new BorderLayout());
	
	private int dividerSize = splitPaneMain.getDividerSize();
	
	private int lastDividerLocation;
	
	private boolean isSplitAreaHidden;

	public TwoCellSplitPaneView() {
		root.add(splitPaneMain, BorderLayout.CENTER);
		splitPaneMain.setRightComponent(holder);
	}
	
	public void setLeftComponent(Component c) {
		splitPaneMain.setLeftComponent(c);		
	}

	public void setRightComponent(Component c) {
		splitPaneMain.setRightComponent(c);
	}

	public void setTopComponent(Component c) {
		root.add(c, BorderLayout.NORTH);
	}
	
	public void setBottomComponent(Component c) {
		root.add(c, BorderLayout.SOUTH);
	}
	
	public void showRightComponent(final Component c) {
		showRightComponent(c, false);
	}
	
	public void showRightComponent(final Component c, final boolean forceShow) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				if (isSplitAreaHidden && splitPaneMain.isManuallyCollapsed()) {
					// show only divider and let user expand it (it was previously manually collapsed)
					splitPaneMain.setDividerSize(dividerSize);
					holder.removeAll();
					holder.add(c, BorderLayout.CENTER);
					holder.setVisible(true);
				} else if (forceShow || isSplitAreaHidden && !splitPaneMain.isManuallyCollapsed()) {
					splitPaneMain.setDividerSize(dividerSize);
					
					if (!isSplitAreaHidden && splitPaneMain.getDividerLocation() > 0 && !splitPaneMain.isCollapsed()) {
						lastDividerLocation = splitPaneMain.getDividerLocation();
					}
					
					if (forceShow && splitPaneMain.isManuallyCollapsed()) {
						splitPaneMain.setDividerLocation(splitPaneMain.getLastDividerLocation());
					} else if (lastDividerLocation > 0) {
						splitPaneMain.setDividerLocation(lastDividerLocation);
					} else {
						int preferredWidth = (int) c.getPreferredSize().getWidth();
						int dividerLocation = splitPaneMain.getWidth() - preferredWidth - dividerSize;
						splitPaneMain.setDividerLocation(dividerLocation > 0 ? dividerLocation : 0);
					}
					
					holder.removeAll();
					holder.add(c, BorderLayout.CENTER);
					holder.setVisible(true);
					isSplitAreaHidden = false;
					
					// request focus
					c.requestFocusInWindow();
				} else {
					holder.removeAll();
					holder.add(c, BorderLayout.CENTER);
					holder.updateUI();
				}
			}
		});
	}

	public void hideRightComponent() {
		splitPaneMain.setDividerSize(0);

		holder.setVisible(false);
		isSplitAreaHidden = true;
		
		if (splitPaneMain.getDividerLocation() > 0 && !splitPaneMain.isCollapsed()) {
			lastDividerLocation = splitPaneMain.getDividerLocation();
		}
	}
	
	public boolean isShowingRightComponent() {
		return holder.isVisible();
	}
	
	@Override
	public Component asComponent() {
		return root;
	}

}
