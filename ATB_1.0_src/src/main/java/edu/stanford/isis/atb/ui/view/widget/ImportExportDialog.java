/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dialog.ModalityType;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.text.BadLocationException;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;

/**
 * Dialog for displaying operation status.
 * 
 * @author Vitaliy Semeshko
 */
public class ImportExportDialog {

	private JPanel root = new JPanel(new BorderLayout());
	
	private EscapeDialog dialog = new EscapeDialog();

	private MiscImageBundle miscImages = MiscImageBundle.getInstance();
	
	private ImportExportListener listener;

	private Mode mode;
	
	private boolean running;
	
	private JTextField filePathText = new JTextField();
	
	private JTextPane infoTextPane = new JTextPane();
	
	private String currentDirectory;
	
	private String defaultExtension;
	
	private String defaultExtensionText;
	
	private JButton submitButton = new JButton(Const.EMPTY, miscImages.getButtonSubmitIcon().loadIcon());
	private JButton cancelButton = new JButton(Const.BTN_CANCEL, miscImages.getButtonCancelIcon().loadIcon());

	public static enum Mode {
		IMPORT,
		EXPORT;
	}
	
	public ImportExportDialog() {
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		dialog.add(root);
		dialog.setSize(400, 240);
		
		initTopPane();
		initCentralPane();
		initBottomPane();
	}
	
	private void initTopPane() {
		JPanel top = new JPanel(new BorderLayout());
		top.setBorder(BorderFactory.createEmptyBorder(6, 6, 6, 6));
		root.add(top, BorderLayout.NORTH);
		
		JButton fileChoserButton = new JButton(Const.BTN_BROWSE);
		JPanel buttonPanel = new JPanel(new GridBagLayout());
		buttonPanel.add(Box.createRigidArea(new Dimension(6, 0)));
		buttonPanel.add(fileChoserButton);
		
		top.add(new JLabel(Const.LBL_FILE), BorderLayout.NORTH);
		top.add(filePathText, BorderLayout.CENTER);
		top.add(buttonPanel, BorderLayout.EAST);
		
		
		fileChoserButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				final JFileChooser c = new JFileChooser();
				if (StringUtils.isNotEmpty(defaultExtension) && StringUtils.isNotEmpty(defaultExtensionText)) {
					c.setFileFilter(new FileNameExtensionFilter(defaultExtensionText, defaultExtension));
					c.setAcceptAllFileFilterUsed(false);
				}
				
				if (StringUtils.isNotEmpty(currentDirectory)) {
					File dir = new File(currentDirectory);
					if (dir.isDirectory()) {
						c.setCurrentDirectory(dir);
					}
				}
				
				int rVal = c.showDialog(dialog, (mode == Mode.IMPORT) ? Const.TTL_IMPORT : Const.TTL_EXPORT); 
				if (rVal == JFileChooser.APPROVE_OPTION) {
					if (StringUtils.isNotEmpty(defaultExtension)) {
						if (!c.getSelectedFile().getPath().toLowerCase().endsWith("." + defaultExtension)) {
							c.setSelectedFile(new File(c.getSelectedFile().getPath() + "." + defaultExtension));
						}
					}
					filePathText.setText(c.getSelectedFile().getAbsolutePath());
					infoTextPane.setText(Const.EMPTY);
				}
			}
		});
	}
	
	private void initCentralPane() {
		JPanel central = new JPanel(new BorderLayout());
		central.setBorder(BorderFactory.createEmptyBorder(0, 6, 6, 6));
		root.add(central, BorderLayout.CENTER);
		
		JScrollPane scroll = new JScrollPane(infoTextPane);
		scroll.setAutoscrolls(true);
		
		central.add(new JLabel(Const.LBL_INFORMATION), BorderLayout.NORTH);
		central.add(scroll, BorderLayout.CENTER);
		
		infoTextPane.setEditable(false);
		infoTextPane.setContentType("text/html");
	}
	
	private void initBottomPane() {
		JPanel bottom = new JPanel(new FlowLayout());
		root.add(bottom, BorderLayout.SOUTH);;

		bottom.add(submitButton);
		bottom.add(cancelButton);
		
		submitButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (!running) {
					if (listener != null) {
						setRunning(true);
						listener.onStart(filePathText.getText());
					}
				}
			}
		});

		cancelButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (running) {
					if (listener != null) {
						listener.onCancel();
					}
					setRunning(false);
				} else {
					dialog.setVisible(false);
				}
			}
		});
	}
	
	public void setListener(ImportExportListener listener) {
		this.listener = listener;
	}
	
	public void showAsDialog(Mode mode) {
		setMode(mode);
		setRunning(false);
		filePathText.setText(Const.EMPTY);
		infoTextPane.setText(Const.EMPTY);
		
		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);
		
		dialog.setVisible(true);
	}
	
	public void setCurrentDirectory(String currentDirectory) {
		this.currentDirectory = currentDirectory;
	}
	
	public void setDefaultExtension(String defaultExtension) {
		this.defaultExtension = defaultExtension;
	}

	public void setDefaultExtensionText(String defaultExtensionText) {
		this.defaultExtensionText = defaultExtensionText;
	}

	private void writeInfo(String text, Color color) {
		StyledDocument doc = infoTextPane.getStyledDocument();
		text = text + "\n";
		try {
			SimpleAttributeSet style = new SimpleAttributeSet();
			if (color != null) {
				StyleConstants.setForeground(style, color);
			}
			
			doc.insertString(doc.getLength(), text, style);
			infoTextPane.setCaretPosition(doc.getLength());
		} catch (BadLocationException e) {
			// ignore
		}
	}
	
	public void notifyStatus(String status) {
		writeInfo(status, null);
	}
	
	public void notifyCancelled() {
		writeInfo(Const.MSG_OPERATION_INTERRUPTED, Color.red);
	}
	
	public void notifySuccess() {
		setRunning(false);
		writeInfo(Const.MSG_OPERATION_FINISHED, Color.green);
	}
	
	public void notifyFail() {
		setRunning(false);
		writeInfo(Const.MSG_OPERATION_FAILED, Color.red);
	}
	
	private void setRunning(boolean running) {
		this.running = running;
		submitButton.setEnabled(!running);
		
		if (running) {
			infoTextPane.setText(Const.EMPTY);
		} else {
			// stop indication
		}
	}
	
	private void setMode(Mode mode) {
		this.mode = mode;
		switch (mode) {
		case IMPORT:
			dialog.setTitle(Const.TTL_IMPORT);
			submitButton.setText(Const.BTN_IMPORT);
			break;
		case EXPORT:
			dialog.setTitle(Const.TTL_EXPORT);
			submitButton.setText(Const.BTN_EXPORT);
			break;
		}
	}
	
	public interface ImportExportListener {
		
		public void onStart(String filePath);
		
		public void onCancel();

	}
	
}
