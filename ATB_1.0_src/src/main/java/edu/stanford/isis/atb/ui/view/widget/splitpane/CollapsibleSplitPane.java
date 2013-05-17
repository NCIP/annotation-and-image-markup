/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.splitpane;

import java.awt.Component;
import java.awt.Cursor;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;
import javax.swing.plaf.basic.BasicSplitPaneDivider;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;

/**
 * @author Vitaliy Semeshko
 */
public class CollapsibleSplitPane extends JSplitPane {

	private static final Logger logger = LoggerFactory.getLogger(CollapsibleSplitPane.class);

	private static final MiscImageBundle images = MiscImageBundle.getInstance();

	private static final Icon leftDefaultIcon = images.getSplitPaneLeftDefaultIcon().loadIcon();
	private static final Icon leftHoverIcon = images.getSplitPaneLeftHoverIcon().loadIcon();
	private static final Icon rightDefaultIcon = images.getSplitPaneRightDefaultIcon().loadIcon();
	private static final Icon rightHoverIcon = images.getSplitPaneRightHoverIcon().loadIcon();
	
	private static final Icon topDefaultIcon = images.getSplitPaneTopDefaultIcon().loadIcon();
	private static final Icon topHoverIcon = images.getSplitPaneTopHoverIcon().loadIcon();
	private static final Icon bottomDefaultIcon = images.getSplitPaneBottomDefaultIcon().loadIcon();
	private static final Icon bottomHoverIcon = images.getSplitPaneBottomHoverIcon().loadIcon();

	private BasicSplitPaneDivider dividerContainer;

	private boolean initialized;

	private boolean manuallyCollapsed;
	
	private CollapseMode mode;

	public static enum CollapseMode {
		COLLAPSE_LEFT,
		COLLAPSE_RIGHT,
		COLLAPSE_TOP,
		COLLAPSE_BOTTOM;
	}
	
    public CollapsibleSplitPane() {}

    public CollapsibleSplitPane(int newOrientation) {
        super(newOrientation);
    }
	
	public void setCollapsible(CollapseMode mode) {
		if (initialized) {
			throw new ATBException("Collapsible split pane already initialized.");
		}

		this.mode = mode;
		
		for (Component component : getComponents()) {
			if (component instanceof BasicSplitPaneDivider) {
				dividerContainer = (BasicSplitPaneDivider) component;
				break;
			}
		}

		if (dividerContainer == null) {
			logger.warn("Can't initialize collapsible split pane. No BasicSplitPaneDivider found.");
			return;
		}

		setOneTouchExpandable(true);

		JButton left = (JButton) dividerContainer.getComponent(0);
		JButton right = (JButton) dividerContainer.getComponent(1);

		final CollapseButton button = new CollapseButton(left.getActionListeners(), right.getActionListeners());

		setOneTouchExpandable(false);

		dividerContainer.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 0));
		dividerContainer.setLayout(new GridBagLayout());

		dividerContainer.add(button);

		addPropertyChangeListener(JSplitPane.DIVIDER_LOCATION_PROPERTY, new PropertyChangeListener() {
			@Override
			public void propertyChange(PropertyChangeEvent pce) {
				button.update();
			}
		});
		
		initialized = true;
	}

	public boolean isManuallyCollapsed() {
		return manuallyCollapsed;
	}
	
	public boolean isCollapsed() {
		if (mode == null) {
			return false;
		}
		
		Insets insets = getInsets();
		int currentLoc = getUI().getDividerLocation(this);
		
		if (mode == CollapseMode.COLLAPSE_LEFT || mode == CollapseMode.COLLAPSE_TOP) {
			if (orientation == JSplitPane.HORIZONTAL_SPLIT) {
				if (currentLoc == insets.left) {
					return true;
				} else {
					return false;
				}
			} else {
				if (currentLoc == insets.top) {
					return true;
		        } else {
					return false;
		        }
			}
		} else {
			if (orientation == JSplitPane.HORIZONTAL_SPLIT) {
				if (currentLoc >= (getWidth() - insets.right - dividerContainer.getWidth())) {
					return true;
				} else {
					return false;
				}
			} else {
				if (currentLoc >= (getHeight() - insets.bottom - dividerContainer.getHeight())) {
					return true;
	            } else {
	            	return false;
	            }
			}
		}
	}
	
	/**
	 * @author Vitaliy Semeshko
	 */
	private class CollapseButton extends JButton {

		public CollapseButton(final ActionListener[] collapseLeftActionListeners, 
				final ActionListener[] collapseRightActionListeners) {
			setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			setBorder(BorderFactory.createEmptyBorder());
			setFocusable(false);
			setOpaque(false);
			setRolloverEnabled(true);
			setContentAreaFilled(false);

			switch (mode) {
			case COLLAPSE_LEFT:
				setIcon(leftDefaultIcon);
				setRolloverIcon(leftHoverIcon);
				break;
			case COLLAPSE_RIGHT:
				setIcon(rightDefaultIcon);
				setRolloverIcon(rightHoverIcon);
				break;
			case COLLAPSE_TOP:
				setIcon(topDefaultIcon);
				setRolloverIcon(topHoverIcon);
				break;
			case COLLAPSE_BOTTOM:
				setIcon(bottomDefaultIcon);
				setRolloverIcon(bottomHoverIcon);
				break;
			}
			
			addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					
					manuallyCollapsed = !isCollapsed();
					
					if (leftDirectionAllowed() || topDirectionAllowed()) {
						for (ActionListener listener : collapseLeftActionListeners) {
							listener.actionPerformed(e);
						}
					} else {
						for (ActionListener listener : collapseRightActionListeners) {
							listener.actionPerformed(e);
						}
					}
					update();
				}
			});	
		}

		public void update() {
			SwingUtilities.invokeLater(new Runnable() {
				@Override
				public void run() {
					switch (mode) {
					case COLLAPSE_LEFT:
					case COLLAPSE_RIGHT:
						if (leftDirectionAllowed()) {
							setIcon(leftDefaultIcon);
							setRolloverIcon(leftHoverIcon);
						} else {
							setIcon(rightDefaultIcon);
							setRolloverIcon(rightHoverIcon);
						}
						break;
					case COLLAPSE_TOP:
					case COLLAPSE_BOTTOM:
						if (topDirectionAllowed()) {
							setIcon(topDefaultIcon);
							setRolloverIcon(topHoverIcon);
						} else {
							setIcon(bottomDefaultIcon);
							setRolloverIcon(bottomHoverIcon);
						}
						break;
					}
				}
			});
		}

		private boolean leftDirectionAllowed() {
			boolean isCollapsed = isCollapsed(); 
			return ((!isCollapsed && mode == CollapseMode.COLLAPSE_LEFT) ||
					(isCollapsed && mode == CollapseMode.COLLAPSE_RIGHT));
		}
		
		private boolean topDirectionAllowed() {
			boolean isCollapsed = isCollapsed(); 
			return ((!isCollapsed && mode == CollapseMode.COLLAPSE_TOP) ||
					(isCollapsed && mode == CollapseMode.COLLAPSE_BOTTOM));
		}

	}

}
