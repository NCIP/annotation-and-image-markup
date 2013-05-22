/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.resources.image;

import java.net.URL;

import javax.swing.Icon;
import javax.swing.ImageIcon;

/**
 * Default implementation.
 * 
 * @author Vitaliy Semeshko
 */
public class DefaultLazyIcon implements LazyIcon {

	private Icon icon;
	
	private URL location;

	public DefaultLazyIcon(URL location) {
		this.location = location;
	}
	
	@Override
	public Icon loadIcon() {
		if (icon == null) {
			icon = new ImageIcon(location);
		}
		
		return icon;
	}

	@Override
	public URL getLocation() {
		return location;
	}
	
}
