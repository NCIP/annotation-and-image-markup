/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.form.impl;

import static edu.stanford.isis.atb.ui.Const.TXT_FORM_NO_ATTRIBUTES;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JLabel;
import javax.swing.SwingConstants;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.form.EmptyFormView;

/**
 * @author Vitaliy Semeshko
 */
public class EmptyFormViewImpl extends AbstractEditFormView<Enum<?>> implements EmptyFormView {

	public EmptyFormViewImpl() {
		// hide buttons
		controlButtonsPanel.setVisible(false);
		
		formPanel.setLayout(new BorderLayout());
		JLabel text = new JLabel(TXT_FORM_NO_ATTRIBUTES);
		text.setHorizontalAlignment(SwingConstants.CENTER);
		text.setForeground(Color.gray);
		formPanel.add(text, BorderLayout.CENTER);
	}
	
	@Override
	public void setFieldValue(Enum<?> field, Object value) {}

	@Override
	public Object getFieldValue(Enum<?> field) {
		return null;
	}
	

}
