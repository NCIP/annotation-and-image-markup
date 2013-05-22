/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.template;

import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Collection;

import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateContainerComplete;
import edu.stanford.isis.atb.domain.template.TemplateRef;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateDao {

	/**
	 * Load data and keep it in the storage.
	 */
	public void initialize();
	
	/**
	 * Get all available template containers.
	 * 
	 * @return {@link Iterable} of {@link TemplateContainer}
	 */
	public Collection<TemplateContainer> getContainers();

	/**
	 * Get complete template container.
	 * 
	 * @return {@link TemplateContainerComplete}
	 */
	public TemplateContainerComplete getCompleteContainer(TemplateContainer container);
	
	/**
	 * Get all available templates.
	 * 
	 * @return {@link Iterable} of {@link TemplateRef}
	 */
	public Collection<TemplateRef> getTemplateRefs();

	/**
	 * Get complete template by reference.
	 * 
	 * @param ref reference
	 * @return initialized {@link Template}
	 */
	public Template getTemplate(TemplateRef ref);
	
	/**
	 * Get template reference.
	 * 
	 * @param id object identifier
	 * @return {@link TemplateRef}
	 */
	public TemplateRef getTemplateRef(Identifier id);

	/**
	 * Save container.
	 * 
	 * @param container container to be saved
	 */
	public void saveContainer(TemplateContainer container);

	/**
	 * Save template.
	 * 
	 * @param template template to be saved
	 */
	public TemplateRef saveTemplate(Template template);

	/**
	 * Delete container.
	 * 
	 * @param container container to be deleted
	 */
	public void deleteContainer(TemplateContainer container);
	
	/**
	 * Delete template.
	 * 
	 * @param template template to be deleted
	 */
	public void deleteTemplate(TemplateRef template);

	/**
	 * Export container to specified file.
	 * 
	 * @param container container to export
	 * @param path export path
	 */
	public void exportContainer(TemplateContainer container, File path);
	
	/**
	 * Export container to stream.
	 * 
	 * @param container container to export
	 * @param out output stream
	 */
	public void validateAndExportContainer(TemplateContainer container, OutputStream out);
	
	/**
	 * Export complete container to stream.
	 * 
	 * @param container container to export
	 * @param out output stream
	 */
	public void exportContainer(TemplateContainerComplete container, OutputStream out);

	/**
	 * Export template to stream.
	 * 
	 * @param template complete template
	 * @param out output stream
	 */
	public void exportTemplate(Template template, OutputStream out);
	
	/**
	 * Import container from specified path
	 * 
	 * @param path
	 * @return
	 */
	public TemplateContainer importContainer(File path);
	
	/**
	 * Import container from stream
	 * 
	 * @param input
	 * @return imported container
	 */
	public TemplateContainer importContainer(InputStream input);
	
	/**
	 * Import template from stream
	 * 
	 * @param input
	 * @return reference to imported template
	 */
	public TemplateRef importTemplate(InputStream input);
	
}
