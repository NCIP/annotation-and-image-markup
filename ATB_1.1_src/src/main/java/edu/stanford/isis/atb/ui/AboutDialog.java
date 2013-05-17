/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui;

import static edu.stanford.isis.atb.system.config.PropertyManager.HELP_URL;
import static edu.stanford.isis.atb.system.config.PropertyManager.VERSION;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Desktop;
import java.awt.Dialog.ModalityType;
import java.awt.Rectangle;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.URI;

import javax.swing.JPanel;
import javax.swing.JTextPane;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.ui.view.widget.EscapeDialog;

/**
 * About dialog.
 * 
 * @author Vitaliy Semeshko
 */
public class AboutDialog {

	private static final Logger logger = LoggerFactory.getLogger(AboutDialog.class);
	
	private static final String HELP_URL_TEXT = "<html><br><center><font color=\"blue\"><b>" +
			"Online Help" +
			"<b></font></center></html>";
	
	private static final String ABOUT_TEXT = "<html><br><center><b>AIM Template Builder</b><br>" +
			"<b>v.%s</b><br><br>" +
			"Developed by:<br>" +
			"Danny Korenblum<br>" +
			"Alan Snyder<br>" +
			"Vitaliy Semeshko<br>" +
			"Vladimir Kleper<br>" +
			"Pattanasak Mongkolwat.<br><br>" +
			"Northwestern University and Stanford University.<br><br>" +
			"<font size=-1>This software application was supported by the National Cancer Institute of the National Institutes of Health under award number 29XS153.</font><br>" +
			"</center></html>";
	
	private static EscapeDialog dialog;
	
	public static void showDialog() {
		if (dialog == null) {
			dialog = new EscapeDialog();
			dialog.setResizable(false);
			dialog.setSize(320, 440);
			dialog.setModalityType(ModalityType.APPLICATION_MODAL);
			
			JPanel panel = new JPanel(new BorderLayout());
			dialog.getContentPane().add(panel, BorderLayout.CENTER);
			
			JTextPane txtInfo = new JTextPane();
			txtInfo.setEditable(false);
			txtInfo.setContentType("text/html");
			
			String version = PropertyManager.getInstance().get(VERSION);
			
			txtInfo.setText(String.format(ABOUT_TEXT, version));
			
			panel.add(txtInfo, BorderLayout.NORTH);
			
			JTextPane txtLink = new JTextPane();
			txtLink.setEditable(false);
			txtLink.setContentType("text/html");
			txtLink.setText(HELP_URL_TEXT);
			txtLink.setForeground(Color.BLUE);
			txtLink.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			
			panel.add(txtLink, BorderLayout.CENTER);
			
			txtLink.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					try {
						Desktop.getDesktop().browse(new URI(PropertyManager.getInstance().get(HELP_URL)));
					} catch (Exception ex) {
						logger.warn("Can't open help page.", ex);
					}
				}
			});
		}
		
		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);
		
		dialog.setVisible(true);
	}
}
