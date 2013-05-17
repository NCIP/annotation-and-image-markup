/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.util;

import java.awt.Color;
import java.awt.GridBagLayout;

import javax.swing.BorderFactory;
import javax.swing.border.Border;

/**
 * @author Vitaliy Semeshko
 */
public class UIUtil {

	/**
	 * Random color border generator.
	 * 
	 * @return
	 */
	public static Border randomLineBorder() {
		return BorderFactory.createLineBorder(
				new Color((int) (Math.random() * 255.0), 
						(int) (Math.random() * 255.0), 
						(int) (Math.random() * 255.0)), 2);
	}

	/**
	 * Create form layout with two columns and configurable rows number.
	 * 
	 * @param rows number of rows
	 * @return configured {@link GridBagLayout}
	 */
	public static GridBagLayout createFormLayout(int rows) {
		GridBagLayout gbl = new GridBagLayout();
		gbl.columnWidths = new int[3];
		gbl.rowHeights = new int[rows + 1];
		gbl.columnWeights = new double[] {0.0, 1.0, Double.MIN_VALUE};
		gbl.rowWeights = new double[rows + 1];
		gbl.rowWeights[gbl.rowWeights.length - 1] = Double.MIN_VALUE;
		return gbl;
	}
	
}
