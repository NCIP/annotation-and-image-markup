/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.InputMap;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.KeyStroke;

/**
 * @author Vitaliy Semeshko
 */
public class EscapeDialog extends JDialog {

	private static final String EXIT_KEY = "ESCAPE";
	
	public EscapeDialog() {
		KeyStroke stroke = KeyStroke.getKeyStroke(EXIT_KEY);
		InputMap inputMap = rootPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
		inputMap.put(stroke, EXIT_KEY);
		rootPane.getActionMap().put(EXIT_KEY, new AbstractAction() {
			public void actionPerformed(ActionEvent actionEvent) {
				setVisible(false);
			}
		});
	}

}
