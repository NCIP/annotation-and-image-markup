/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget;

import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.Vector;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JPanel;
import javax.swing.JTextField;

import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class SuggestionBox extends JPanel {
	
	private final JTextField textField;
	
	private final JComboBox comboBox = new JComboBox();
	
	private final Vector<String> options = new Vector<String>();
	
	private boolean hide;
	
	private boolean sorted;

	public SuggestionBox(boolean sorted) {
		super(new BorderLayout());
		comboBox.setEditable(true);
		this.sorted = sorted;
		
		textField = (JTextField) comboBox.getEditor().getEditorComponent();
		textField.addKeyListener(new KeyAdapter() {
			@Override
			public void keyTyped(KeyEvent e) {
				EventQueue.invokeLater(new Runnable() {
					public void run() {
						String text = textField.getText();
						if (text.isEmpty()) {
							comboBox.hidePopup();
							setModel(new DefaultComboBoxModel(options), Const.EMPTY);
						} else {
							Vector<String> sorted = new Vector<String>(options);
							
							if (SuggestionBox.this.sorted) {
								Collections.sort(sorted);
							}
							
							DefaultComboBoxModel m = getSuggestedModel(sorted, text);
							if (m.getSize() == 0 || hide) {
								comboBox.hidePopup();
								hide = false;
							} else {
								setModel(m, text);
								comboBox.showPopup();
							}
						}
					}
				});
			}
			
			@Override
			public void keyPressed(KeyEvent e) {
				String text = textField.getText();
				int code = e.getKeyCode();
				
				if (code == KeyEvent.VK_ENTER) {
					if (!options.contains(text)) {
						options.addElement(text);
						setModel(getSuggestedModel(options, text), text);
					}
					hide = true; 
				} else if (code==KeyEvent.VK_ESCAPE) {
					hide = true; 
				} else if (code==KeyEvent.VK_RIGHT) {
					for(int i=0;i<options.size();i++) {
						String str = options.elementAt(i);
						if (str.startsWith(text)) {
							comboBox.setSelectedIndex(-1);
							textField.setText(str);
							return;
						}
					}
				}
			}
		});

		JPanel p = new JPanel(new BorderLayout());
		p.add(comboBox, BorderLayout.NORTH);
		add(p);
	}
	
	public String getText() {
		return textField.getText();
	}
	
	public void setOptions(Set<String> options) {
		this.options.clear();
		this.options.addAll(options);
		if (sorted) {
			Collections.sort(this.options);
		}
		comboBox.setModel(new DefaultComboBoxModel(this.options));
		
	}

	public void clear() {
		comboBox.setSelectedIndex(-1);
		textField.setText(Const.EMPTY);
	}
	
	@Override
	public boolean requestFocusInWindow() {
		return comboBox.requestFocusInWindow();
	}
	
	private void setModel(DefaultComboBoxModel model, String str) {
		comboBox.setModel(model);
		comboBox.setSelectedIndex(-1);
		textField.setText(str);
	}

	private static DefaultComboBoxModel getSuggestedModel(List<String> list, String text) {
		DefaultComboBoxModel m = new DefaultComboBoxModel();
		for(String s : list) {
			if (s.startsWith(text)) {
				m.addElement(s);
			}
		}
		return m;
	}
	
	public synchronized void addKeyListener(KeyListener l) {
		// add listeners to inner component
		textField.addKeyListener(l);
	}
	
}
