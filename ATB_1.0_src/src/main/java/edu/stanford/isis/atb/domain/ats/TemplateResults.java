/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

import java.util.Collections;
import java.util.List;

import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="results", strict=false)
public class TemplateResults {

	@ElementList(name="result", inline=true, required=false)
	private List<TemplateSingleResult> templates;

	public List<TemplateSingleResult> getTemplates() {
		if (templates == null) {
			return Collections.emptyList();
		}
		return templates;
	}
	
}
