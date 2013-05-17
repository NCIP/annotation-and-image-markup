/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;

import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane;
import edu.stanford.isis.atb.ui.view.widget.splitpane.CollapsibleSplitPane.CollapseMode;
import edu.stanford.isis.atb.ui.view.widget.toolbar.RichToolBar;

/**
 * @author Vitaliy Semeshko
 */
public class BlockWIthToolbar extends JPanel {
	
	private JPanel header = new JPanel(new BorderLayout());
	
	private JLabel caption = new JLabel();
	
	private RichToolBar toolbar = new RichToolBar();
	
	private CollapsibleSplitPane splitPane = new CollapsibleSplitPane(JSplitPane.VERTICAL_SPLIT); 
	
	private JPanel mainArea = new JPanel(new BorderLayout());
	
	private JPanel bottomArea = new JPanel(new BorderLayout());
	
	private int dividerSize = splitPane.getDividerSize();

	private int lastDividerLocation;
	
	private boolean isSplitAreaHidden;
	
	public BlockWIthToolbar() {
		setLayout(new BorderLayout());
		add(splitPane, BorderLayout.CENTER);
		
		splitPane.setBorder(null);
		splitPane.setResizeWeight(1);
		splitPane.setDividerLocation(0);
		splitPane.setTopComponent(mainArea);
		splitPane.setBottomComponent(bottomArea);
		
		caption.setBorder(BorderFactory.createEmptyBorder(6, 6, 6, 6));
		header.add(caption, BorderLayout.WEST);
		
		add(header, BorderLayout.NORTH);
		add(toolbar, BorderLayout.SOUTH);
		
		toolbar.setFloatable(false);
		// hide until elements added
		toolbar.setVisible(false);
		
		hideBottomSplitArea();
	}
	
	public void setCaptionText(String text) {
		caption.setText(text);
	}
	
	public void addToolBarAction(CommandAction action) {
		toolbar.add(action);
		if (!toolbar.isVisible()) {
			toolbar.setVisible(true);
		}
	}
	
	public void addToolBarSeparator() {
		toolbar.addSeparator(new Dimension(24, 0));
	}

	public void clearToolBar() {
		toolbar.removeAll();
		toolbar.repaint();
	}
	
	public void setMainComponent(Component c) {
		mainArea.add(c, BorderLayout.CENTER);
	}
	
	public void setPreferredWidth(int width) {
		mainArea.setPreferredSize(new Dimension(width, 0));
	}
	
	public void setBottomSplitAreaComponent(Component c) {
		bottomArea.add(c, BorderLayout.CENTER);
	}
	
	public void hideBottomSplitArea() {
		if (!bottomArea.isVisible()) {
			return;
		}
		
		splitPane.setDividerSize(0);
		bottomArea.setVisible(false);
		isSplitAreaHidden = true;
		
		if (splitPane.getDividerLocation() > 0) {
			lastDividerLocation = splitPane.getDividerLocation();
		}
	}
	
	public void showBottomSplitArea() {
		showBottomSplitArea(bottomArea.getComponent(0));
	}
	
	public void showBottomSplitArea(final Component c) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				if (isSplitAreaHidden && splitPane.isManuallyCollapsed()) {
					// show only divider and let user expand it (it was previously manually collapsed)
					splitPane.setDividerSize(dividerSize);
					bottomArea.removeAll();
					bottomArea.add(c, BorderLayout.CENTER);
					bottomArea.setVisible(true);
				} else if (isSplitAreaHidden && !splitPane.isManuallyCollapsed()) {
					splitPane.setDividerSize(dividerSize);
					
					if (!isSplitAreaHidden && splitPane.getDividerLocation() > 0) {
						lastDividerLocation = splitPane.getDividerLocation();
					}
					
					Component currentContent = null;
					if (bottomArea.getComponentCount() > 0) {
						currentContent = bottomArea.getComponent(0);
					}
					
					// use last divider location
					if (lastDividerLocation > 0) {
						splitPane.setDividerLocation(lastDividerLocation);
					} else {
						// else set divider location based on preferred component height
						int preferredHeight = (int) c.getPreferredSize().getHeight();
						int dividerLocation = splitPane.getHeight() - preferredHeight - dividerSize;
						splitPane.setDividerLocation(dividerLocation > 0 ? dividerLocation : 0);
					}
					
					if (c != currentContent) {
						bottomArea.add(c, BorderLayout.CENTER);
					}
					bottomArea.setVisible(true);
					isSplitAreaHidden = false;
					
					// request focus
					c.requestFocusInWindow();
				} else {
					bottomArea.removeAll();
					bottomArea.add(c, BorderLayout.CENTER);
					bottomArea.updateUI();
				}
			}
		});
	}
	
	public void addHeaderRightComponent(Component c) {
		header.add(c, BorderLayout.EAST);
	}
	
	public void setSplitCollapsible(CollapseMode mode) {
		splitPane.setCollapsible(mode);
	}

}
