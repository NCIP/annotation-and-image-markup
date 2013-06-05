/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer;

import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.Icon;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.image.LazyIcon;

/**
 * @author Vitaliy Semeshko
 */
public abstract class AbstractElementRenderer<E> implements ElementRenderer<E> {

	private static final int TEXT_MAX_LENGTH = 65; 
	
	private Icon icon;
	
	private URL iconLocation;
	
	private DateFormat df = new SimpleDateFormat(Const.FMT_DATE_DISPLAY);
	
	public AbstractElementRenderer(LazyIcon icon) {
		this.icon = icon.loadIcon();
		this.iconLocation = icon.getLocation();
	}

	protected Icon getIcon() {
		return icon;
	}

	protected URL getIconLocation() {
		return iconLocation;
	}
	
	protected String formatDate(Date date) {
		return date == null ? Const.EMPTY : df.format(date);
	}
	
	protected String shortText(String text) {
		return shorten(text, TEXT_MAX_LENGTH);
	}
	
	protected String shorten(String longText, int length) {
		if (StringUtils.isEmpty(longText)) {
			return Const.EMPTY;
		} else if (longText.length() > length) {
			return longText.substring(0, length) + "...";
		} else {
			return longText;
		}
	}
	
}
