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

package edu.stanford.isis.atb.ui.view.base;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import javax.swing.text.JTextComponent;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.widget.CardinalityWidget;

/**
 * Base for edit forms.
 * 
 * @author Vitaliy Semeshko
 */
public abstract class AbstractEditFormView<E extends Enum<?>> extends AbstractView implements EditFormView<E> {

	private static final int DEFAULT_FORM_WIDTH = 380;
	private static final int TEXT_CONTROLS_COLS = 10;
	
	protected JPanel formPanel = new JPanel();
	
	protected JPanel controlButtonsPanel = new JPanel(new FlowLayout());
	
	private JButton submitButton;
	
	private JButton cancelButton;

	private JPanel root = new JPanel(new BorderLayout());

	private JScrollPane scrollPane = new JScrollPane();

	private Map<LabeledFormField, FormField> fields = new LinkedHashMap<LabeledFormField, FormField>();

	private MiscImageBundle miscImageBundle = MiscImageBundle.getInstance();

	private boolean readOnly;
	
	public AbstractEditFormView() {
		scrollPane.setViewportView(formPanel);
		root.add(scrollPane, BorderLayout.CENTER);

		// form buttons
		submitButton = new JButton(Const.BTN_SUBMIT, miscImageBundle.getButtonSubmitIcon().loadIcon());
		cancelButton = new JButton(Const.BTN_CANCEL, miscImageBundle.getButtonCancelIcon().loadIcon());

		controlButtonsPanel.add(submitButton);
		//controlButtons.add(cancelButton);
		root.add(controlButtonsPanel, BorderLayout.SOUTH);
	}

	protected void setPreferredSize(int widht, int height) {
		root.setPreferredSize(new Dimension(widht, height));
	}

	/**
	 * Builds form from added fields.
	 */
	public void buildForm() {
		// layout can be properly configured when all rows added
		GridBagLayout layout = new GridBagLayout();
		layout.columnWidths = new int[3];
		layout.rowHeights = new int[fields.size() + 1];
		layout.columnWeights = new double[] {0.0, 1.0, Double.MIN_VALUE};
		layout.rowWeights = new double[fields.size() + 1];
		layout.rowWeights[layout.rowWeights.length - 1] = Double.MIN_VALUE;

		formPanel.setLayout(layout);
		formPanel.setBorder(new EmptyBorder(12, 6, 12, 6));

		Iterator<LabeledFormField> it = fields.keySet().iterator();
		int rowIndex = 0;
		while (it.hasNext()) {
			FormField field = fields.get(it.next());

			if (!field.isBlock()) {
				String labelText;
				if (StringUtils.isNotEmpty(field.getLabel())) {
					if (field.getMode().isMandatory()) {
						labelText = String.format(Const.TPL_FORM_LABEL_MANDATORY, field.getLabel());
					} else {
						labelText = String.format(Const.TPL_FORM_LABEL, field.getLabel());
					}
				} else {
					labelText = Const.EMPTY;
				}

				JLabel label = new JLabel(labelText);

				GridBagConstraints labelConstraints = new GridBagConstraints();
				labelConstraints.insets = new Insets(0, 0, 5, 8);
				labelConstraints.anchor = getLabelAnchor(field.getComponent());
				labelConstraints.gridx = 0;
				labelConstraints.gridy = rowIndex;
				formPanel.add(label, labelConstraints);
			}

			GridBagConstraints componentConstraints = new GridBagConstraints();

			// block spans two columns
			if (field.isBlock()) {
				componentConstraints.insets = new Insets(0, 0, 12, 0);
				componentConstraints.gridx = 0;
				componentConstraints.gridwidth = 2;
			} else {
				componentConstraints.insets = new Insets(0, 0, 5, 0);
				componentConstraints.gridx = 1;
			}

			componentConstraints.gridy = rowIndex;
			if (field.isExtendable()) {
				componentConstraints.fill = GridBagConstraints.HORIZONTAL;
			}
			componentConstraints.anchor = GridBagConstraints.WEST;

			// wrap text area into scroll pane
			if (field.getComponent() instanceof JTextArea) {
				formPanel.add(new JScrollPane(field.getComponent()), componentConstraints);
			} else {
				formPanel.add(field.getComponent(), componentConstraints);
			}

			rowIndex++;
		}
		
		root.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				// focus first control on the form
				for (final FormField field : fields.values()) {
					SwingUtilities.invokeLater(new Runnable() {
						@Override
						public void run() {
							field.getComponent().requestFocusInWindow();
						}
					});
					return;
				}
			}
		});
	}

	@Override
	public void initFieldsState(boolean isCreation) {
		for (FormField field : fields.values()) {
			if (!field.isBlock()) {
				Mode mode = field.getMode();
				boolean enabled = isCreation ? mode.isCreationEnabled() : mode.isModificationEnabled();
				enabled = enabled && !readOnly;
				
				JComponent c = field.getComponent();
				if (c instanceof JTextComponent) {
					((JTextComponent) c).setEditable(enabled);
				} else {
					c.setEnabled(enabled);
				}
			}
		}
		
		Dimension current = root.getPreferredSize();
		if (current.getWidth() < DEFAULT_FORM_WIDTH) {
			root.setPreferredSize(new Dimension(DEFAULT_FORM_WIDTH, (int) current.getHeight()));
		}
	}

	private int getLabelAnchor(JComponent c) {
		if ((c instanceof JTextArea) || (c instanceof CardinalityWidget)) {
			return GridBagConstraints.NORTHEAST;
		} else {
			return GridBagConstraints.EAST;
		}
	}

	public void addBlock(LabeledFormField fieldKey, JComponent component) {
		fields.put(fieldKey, new FormField(component));
	}

	public void addRow(LabeledFormField fieldKey, JComponent component, Mode mode) {
		fields.put(fieldKey, new FormField(fieldKey.getLabel(), component, mode));
	}

	@Override
	public void setFormSubmitActionListener(ActionListener l) {
		submitButton.addActionListener(l);
	}

	@Override
	public void setFormCloseActionListener(ActionListener l) {
		cancelButton.addActionListener(l);
	}

	public void notifyValidationError(LabeledFormField formField, String msg) {
		JComponent c = getFieldComponent(formField);
		if (c.isEnabled()) {
			c.requestFocus();
		}
		showValidationError(msg);
	}

	public JComponent getFieldComponent(LabeledFormField fieldKey) {
		if (!fields.containsKey(fieldKey)) {
			throw new IllegalArgumentException("No field found: " + fieldKey.getLabel());
		}
		return fields.get(fieldKey).getComponent();
	}

	protected JTextArea textArea(final int rows) {
		return new JTextArea() {{ 
				setRows(rows);
				setColumns(TEXT_CONTROLS_COLS);
				setLineWrap(true);
			}

			@Override
			public void setText(String t) {
				super.setText(t);
				setCaretPosition(0);
			}
		};
	}

	/**
	 * Create custom instance of {@link JTextField} used in all forms.
	 * 
	 * @return custom instance of {@link JTextField}
	 */
	protected JTextField textField() {
		return new JTextField() {{ 
				setColumns(TEXT_CONTROLS_COLS); 
			}

			@Override
			public void setText(String t) {
				super.setText(t);
				setCaretPosition(0);
			}
		};
	}

	protected CardinalityWidget cardinality() {
		return new CardinalityWidget();
	}

	protected JComboBox comboBox(Object[] values, boolean addEmptyOption) {
		if (addEmptyOption) {
			Object[] valuesWithEmptyOption = new Object[values.length + 1];
			valuesWithEmptyOption[0] = Const.EMPTY;
			for (int i = 1; i < valuesWithEmptyOption.length; i++) {
				valuesWithEmptyOption[i] = values[i-1];
			}
			return new JComboBox(valuesWithEmptyOption);
		} else {
			return new JComboBox(values);
		}
	}

	@Override
	public void setReadOnly(boolean readOnly) {
		this.readOnly = readOnly;
		
		//disable buttons
		submitButton.setEnabled(!readOnly);
		cancelButton.setEnabled(!readOnly);
	}

	@Override
	public Component asComponent() {
		return root;
	}

	private class FormField {

		private String label;
		private JComponent component;
		private Mode mode;
		private boolean block;

		public FormField(String label, JComponent component, Mode mode) {
			this.label = label;
			this.mode = mode;
			this.component = component;
		}

		public FormField(JComponent component) {
			this.component = component;
			this.block = true;
		}

		public String getLabel() {
			return label;
		}

		public JComponent getComponent() {
			return component;
		}

		public Mode getMode() {
			return mode;
		}

		public boolean isExtendable() {
			return block || (component instanceof JTextComponent) 
					|| (component instanceof JComboBox) 
					|| (component instanceof JSpinner)
					|| (component instanceof CardinalityWidget);
		}

		public boolean isBlock() {
			return block;
		}

	}

	/**
	 * All possible modes used for form fields.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public enum Mode {
		M_EN_EN   (true , true , true ),
		M_EN_DIS  (true , true , false),
		M_DIS_EN  (true , false, true ),
		M_DIS_DIS (true , false, false),
		NM_EN_EN  (false, true , true ),
		NM_EN_DIS (false, true , false),
		NM_DIS_EN (false, false, true ),
		NM_DIS_DIS(false, false, false);

		private boolean mandatory;
		private boolean creationEnabled;
		private boolean modificationEnabled;

		private Mode(boolean mandatory, boolean creationEnabled, boolean modificationEnabled) {
			this.mandatory = mandatory;
			this.creationEnabled = creationEnabled;
			this.modificationEnabled = modificationEnabled;
		}

		public boolean isMandatory() {
			return mandatory;
		}

		public boolean isCreationEnabled() {
			return creationEnabled;
		}

		public boolean isModificationEnabled() {
			return modificationEnabled;
		}
	}
}
