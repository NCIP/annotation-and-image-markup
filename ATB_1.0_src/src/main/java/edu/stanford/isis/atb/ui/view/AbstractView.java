/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view;

import static edu.stanford.isis.atb.ui.Const.DLG_TITLE_CONFIRMATION;
import static edu.stanford.isis.atb.ui.Const.DLG_TITLE_ERROR;
import static edu.stanford.isis.atb.ui.Const.DLG_TITLE_INFORMATION;
import static edu.stanford.isis.atb.ui.Const.DLG_TITLE_VALIDATION_ERROR;

import java.awt.Component;

import javax.swing.JOptionPane;

import edu.stanford.isis.atb.ui.Application;

/**
 * Common base for custom views.
 * 
 * @author Vitaliy Semeshko
 */
public abstract class AbstractView implements View {
	
	private Component topParent = Application.accessApplication().asComponent();
	
	@Override
	public void showInformation(String text) {
		JOptionPane.showMessageDialog(topParent, text, DLG_TITLE_INFORMATION, JOptionPane.INFORMATION_MESSAGE);
	}
	
	@Override
	public void showError(String text) {
		JOptionPane.showMessageDialog(topParent, text, DLG_TITLE_ERROR, JOptionPane.ERROR_MESSAGE);
	}
	
	@Override
	public void showValidationError(String text) {
		JOptionPane.showMessageDialog(topParent, text, DLG_TITLE_VALIDATION_ERROR, JOptionPane.ERROR_MESSAGE);
	}
	
	@Override
	public boolean confirm(String text) {
		return JOptionPane.showConfirmDialog(topParent, text, DLG_TITLE_CONFIRMATION, JOptionPane.OK_CANCEL_OPTION) == 0;
	}
	
}
