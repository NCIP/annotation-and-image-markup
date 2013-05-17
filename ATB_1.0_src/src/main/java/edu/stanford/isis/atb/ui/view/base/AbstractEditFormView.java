/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
