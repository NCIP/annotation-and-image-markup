/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
