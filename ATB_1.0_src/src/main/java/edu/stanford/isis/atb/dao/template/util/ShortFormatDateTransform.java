/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.template.util;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.simpleframework.xml.transform.Transform;

/**
 * @author Vitaliy Semeshko
 */
public class ShortFormatDateTransform implements Transform<Date> {

	private DateFormat format = new SimpleDateFormat("yyyy-MM-dd");

	public synchronized Date read(String text) throws Exception {      
		return format.parse(text);
	}

	public synchronized String write(Date date) throws Exception {
		return format.format(date);     
	}

}
