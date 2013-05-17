/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

import java.io.File;
import java.util.Collection;

import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;

/**
 * Template service provides operations on templates and containers.
 * 
 * @author Vitaliy Semeshko
 */
public interface TemplateService {

	// read
	
	public Collection<TemplateRef> getTemplates();
	
	public Collection<TemplateContainer> getContainers();
	
	public Template getTemplate(TemplateRef ref);
	
	public TemplateRef getTemplateRef(Identifier id);
	
	// write
	
	public void saveContainer(TemplateContainer container);
	
	public void saveTemplate(Template template);
	
	// remove
	
	public void deleteContainer(TemplateContainer container);
	
	public void deleteTemplate(TemplateRef template);
	
	// import/export
	
	public void exportContainer(TemplateContainer container, File path, Callback<Void> callback);
	
	public void importContainer(File path, Callback<TemplateContainer> callback);
	
	// copy
	
	public TemplateRef copyTemplate(TemplateRef ref);
	
	public TemplateContainer copyContainer(TemplateContainer container);
	
}
