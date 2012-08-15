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

import static edu.stanford.isis.atb.ui.Const.FRM_LBL_PASSWORD;
import static edu.stanford.isis.atb.ui.Const.TPL_FORM_LABEL_MANDATORY;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dialog.ModalityType;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;

import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.util.UIUtil;

/**
 * @author Vitaliy Semeshko
 */
public class LoginDialog {

	private EscapeDialog dialog;

	private LoginListener loginListener;

	private JTextField userNameText = new JTextField();

	private JPasswordField passwordText = new JPasswordField();

	private JLabel authFailed = new JLabel(Const.TXT_AUTHENTICATION_FAILED);
	
	public void setLoginListener(LoginListener loginListener) {
		this.loginListener = loginListener;
	}

	public void showDialog(String defaultUserName) {
		if (dialog == null) {
			dialog = new EscapeDialog();
			dialog.setResizable(false);
			dialog.setSize(320, 180);
			dialog.setModalityType(ModalityType.APPLICATION_MODAL);

			JPanel panel = new JPanel(new BorderLayout());
			dialog.getContentPane().add(panel, BorderLayout.CENTER);

			panel.setLayout(UIUtil.createFormLayout(3));
			panel.setBorder(new EmptyBorder(new Insets(10, 5, 10, 5)));

			// fields

			GridBagConstraints gbcLabelUsername = new GridBagConstraints();
			gbcLabelUsername.insets = new Insets(10, 10, 10, 8);
			gbcLabelUsername.anchor = GridBagConstraints.EAST;
			gbcLabelUsername.gridx = 0;
			gbcLabelUsername.gridy = 0;
			panel.add(new JLabel(String.format(TPL_FORM_LABEL_MANDATORY, Const.FRM_LBL_USERNAME)), gbcLabelUsername);

			GridBagConstraints gbcTextUsername = new GridBagConstraints();
			gbcTextUsername.insets = new Insets(10, 0, 10, 10);
			gbcTextUsername.fill = GridBagConstraints.HORIZONTAL;
			gbcTextUsername.gridx = 1;
			gbcTextUsername.gridy = 0;
			panel.add(userNameText, gbcTextUsername);
			userNameText.setColumns(8);

			GridBagConstraints gbcLabelPassword = new GridBagConstraints();
			gbcLabelPassword.anchor = GridBagConstraints.EAST;
			gbcLabelPassword.insets = new Insets(0, 10, 8, 8);
			gbcLabelPassword.gridx = 0;
			gbcLabelPassword.gridy = 1;
			panel.add(new JLabel(String.format(TPL_FORM_LABEL_MANDATORY, FRM_LBL_PASSWORD)), gbcLabelPassword);

			GridBagConstraints gbcTextPassword = new GridBagConstraints();
			gbcTextPassword.insets = new Insets(0, 0, 8, 10);
			gbcTextPassword.fill = GridBagConstraints.HORIZONTAL;
			gbcTextPassword.gridx = 1;
			gbcTextPassword.gridy = 1;
			panel.add(passwordText, gbcTextPassword);
			passwordText.setColumns(8);
			
			GridBagConstraints gbclabelAuthFailed = new GridBagConstraints();
			gbclabelAuthFailed.insets = new Insets(0, 0, 0, 10);
			gbclabelAuthFailed.fill = GridBagConstraints.HORIZONTAL;
			gbclabelAuthFailed.gridx = 1;
			gbclabelAuthFailed.gridy = 2;
			panel.add(authFailed, gbclabelAuthFailed);
			authFailed.setForeground(Color.red);
			authFailed.setVisible(false);

			// buttons

			JPanel bottom = new JPanel(new BorderLayout());
			dialog.getContentPane().add(bottom, BorderLayout.SOUTH);

			JPanel buttons = new JPanel();
			buttons.setBorder(new EmptyBorder(new Insets(0, 0, 10, 10)));
			bottom.add(buttons, BorderLayout.EAST);

			JButton login = new JButton(Const.BTN_LOGIN);
			JButton cancel = new JButton(Const.BTN_CANCEL);
			buttons.add(login);
			buttons.add(cancel);

			login.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					if (loginListener != null) {
						loginListener.onLogin(userNameText.getText(), new String(passwordText.getPassword()));
					}
				}
			});

			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					dialog.setVisible(false);
				}
			});
		}

		userNameText.setText(defaultUserName);
		passwordText.setText(Const.EMPTY);

		SwingUtilities.invokeLater(new Runnable() {  
			@Override
			public void run() {  
				passwordText.requestFocusInWindow();
			}
		});

		if (!dialog.isVisible()) {
			Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
			int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
			int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
			dialog.setLocation(x, y);

			dialog.setVisible(true);
		}
	}

	public void hideDialog() {
		dialog.setVisible(false);
	}
	
	public void authenticationFailed() {
		authFailed.setVisible(true);
	}
	
	public interface LoginListener {

		public void onLogin(String userName, String password);

	}

}
