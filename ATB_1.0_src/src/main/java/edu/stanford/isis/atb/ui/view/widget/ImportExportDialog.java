/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
