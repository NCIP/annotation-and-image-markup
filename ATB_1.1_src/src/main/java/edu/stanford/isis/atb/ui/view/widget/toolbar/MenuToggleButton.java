/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.toolbar;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;

import javax.swing.Action;
import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JPopupMenu;
import javax.swing.JToggleButton;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;

import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.action.CommandAction;

/**
 * @author Vitaliy Semeshko
 */
public class MenuToggleButton extends JToggleButton {

	private static final Icon arrowIcon = new MenuArrowIcon();

	public MenuToggleButton(CommandAction action) {
		final JPopupMenu menu = new JPopupMenu();
		
		for (CommandAction subAction : action.getSubActions()) {
			menu.add(subAction);
		}

		// show/hide in order to initialize dimensions
		menu.show(null, 2500, 2500);
		menu.setVisible(false);

		menu.addPopupMenuListener(new PopupMenuListener() {

			@Override 
			public void popupMenuCanceled(PopupMenuEvent e) {}

			@Override 
			public void popupMenuWillBecomeVisible(PopupMenuEvent e) {}

			@Override 
			public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				setSelected(false);
			}
		});

		action.setCommand(new Command() {
			@Override
			public void execute() {
				if (menu != null) {
					menu.show(MenuToggleButton.this, 0, - menu.getHeight());
				}
			}
		});

		setAction(action);
		setFocusable(false);

		if (action  != null && (action.getValue(Action.SMALL_ICON) != null || 
				action.getValue(Action.LARGE_ICON_KEY) != null)) {
			setHideActionText(true);
		}

		setHorizontalTextPosition(JButton.CENTER);
		setVerticalTextPosition(JButton.BOTTOM);
	}

	public void setInsets(Insets insets) {
		setBorder(BorderFactory.createEmptyBorder(insets.top, insets.left, insets.bottom, 
				insets.right + arrowIcon.getIconWidth()));
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Dimension dim = getSize();
		Insets ins = getInsets();
		int x = dim.width - ins.right;
		int y = ins.top + (dim.height - ins.top - ins.bottom -arrowIcon.getIconHeight()) / 2;
		arrowIcon.paintIcon(this, g, x, y);
	}

	private static class MenuArrowIcon implements Icon {

		@Override 
		public void paintIcon(Component c, Graphics g, int x, int y) {
			Graphics2D g2 = (Graphics2D) g;
			g2.setPaint(Color.DARK_GRAY);
			g2.translate(x, y);
			g2.drawLine(2, 5, 6, 5);
			g2.drawLine(3, 4, 5, 4);
			g2.drawLine(4, 3, 4, 3);
			g2.translate(-x, -y);
		}

		@Override public int getIconWidth() {
			return 9;
		}

		@Override public int getIconHeight() {
			return 9;
		}
	}

}
