/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer;

import javax.swing.Icon;

/**
 * Information used by renderer.
 * 
 * @author Vitaliy Semeshko
 */
public interface RenderInfo {

	public String getText();
	
	public String getToolTipText();
	
	public Icon getIcon();
	
}
