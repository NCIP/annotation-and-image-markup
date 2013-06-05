/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import org.apache.commons.lang3.StringUtils;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="TagName", strict=false)
public class TagName extends CodedTerm {

	@Override
	public String toString() {
		return "TagName: " + StringUtils.trimToEmpty(getCodeMeaning());
	}
	
}
