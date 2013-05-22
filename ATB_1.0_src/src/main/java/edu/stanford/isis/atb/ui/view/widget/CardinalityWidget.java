/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.BorderFactory;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerListModel;
import javax.swing.SpinnerNumberModel;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.Cardinality;
import edu.stanford.isis.atb.ui.util.UIUtil;

/**
 * @author Vitaliy Semeshko
 */
public class CardinalityWidget extends JPanel {

	private static final int SPINNER_WIDTH = 50;
	
	private JSpinner spnMin = new JSpinner();
	
	private JSpinner spnMax = new JSpinner();
	
	private JCheckBox unlimitedCheckBox = new JCheckBox(Const.LBL_UNLIMITED);
	
	public CardinalityWidget() {
		setLayout(UIUtil.createFormLayout(2));
		setBorder(BorderFactory.createTitledBorder(Const.EMPTY));
		
		spnMin.setModel(new SpinnerNumberModel(0, 0, Long.MAX_VALUE, 1));
		spnMax.setModel(new SpinnerNumberModel(0, 0, Long.MAX_VALUE, 1));
		
		spnMin.setPreferredSize(new Dimension(SPINNER_WIDTH, (int) spnMin.getPreferredSize().getHeight()));
		spnMax.setPreferredSize(new Dimension(SPINNER_WIDTH, (int) spnMax.getPreferredSize().getHeight()));
		
		GridBagConstraints gbcLabelTemplateName = new GridBagConstraints();
		gbcLabelTemplateName.anchor = GridBagConstraints.WEST;
		gbcLabelTemplateName.gridx = 0;
		gbcLabelTemplateName.gridy = 0;
		JPanel minHolder = new JPanel();
		minHolder.add(spnMin);
		minHolder.add(new JLabel("min  to "));
		add(minHolder, gbcLabelTemplateName);
		
		GridBagConstraints gbcTextTemplateName = new GridBagConstraints();
		gbcTextTemplateName.anchor = GridBagConstraints.WEST;
		gbcTextTemplateName.gridx = 1;
		gbcTextTemplateName.gridy = 0;
		JPanel maxHolder = new JPanel();
		maxHolder.add(spnMax);
		maxHolder.add(new JLabel("max"));
		add(maxHolder, gbcTextTemplateName);
		
		GridBagConstraints gbcUnlimitedCheckbox = new GridBagConstraints();
		gbcUnlimitedCheckbox.anchor = GridBagConstraints.WEST;
		gbcUnlimitedCheckbox.gridx = 1;
		gbcUnlimitedCheckbox.gridy = 1;
		add(unlimitedCheckBox, gbcUnlimitedCheckbox);
		
		unlimitedCheckBox.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent e) {
				setState(e.getStateChange() == ItemEvent.SELECTED);
			}
		});
	}
	
	public Cardinality getCardinality() {
		Number min = (Number) spnMin.getValue(); 
		Number max = unlimitedCheckBox.isSelected() ? Long.MAX_VALUE : (Number) spnMax.getValue(); 
		return new Cardinality(min.longValue(), max.longValue());
	}
	
	public void setCardinality(Cardinality cardinality) {
		spnMin.setValue(cardinality.getMin());
		boolean isUnlimited = cardinality.getMax() >= Long.MAX_VALUE;
		unlimitedCheckBox.setSelected(isUnlimited);
		setState(isUnlimited, cardinality.getMax());
	}

	private void setState(boolean isUnlimited) {
		setState(isUnlimited, ((Number) spnMin.getValue()).longValue());
	}
	
	private void setState(boolean isUnlimited, long value) {
		spnMax.setEnabled(!isUnlimited);
		if (isUnlimited) {
			setMaxCardinalityInfinity();
		} else {
			setMaxCardinalityValue(value);
		}
	}
	
	private void setMaxCardinalityInfinity() {
		spnMax.setModel(new SpinnerListModel(new String[] {Const.TXT_INFINITY}));
	}
	
	private void setMaxCardinalityValue(long value) {
		spnMax.setModel(new SpinnerNumberModel(value, 0, Long.MAX_VALUE, 1));
	}
	
}
