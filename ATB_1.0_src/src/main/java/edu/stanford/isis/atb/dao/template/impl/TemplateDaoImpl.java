/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.template.impl;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import org.apache.commons.io.IOUtils;
import org.apache.commons.io.output.ByteArrayOutputStream;
import org.apache.commons.lang3.ArrayUtils;
import org.simpleframework.xml.Serializer;
import org.simpleframework.xml.core.Persister;
import org.simpleframework.xml.stream.Format;
import org.springframework.stereotype.Repository;

import edu.stanford.isis.atb.dao.template.TemplateDao;
import edu.stanford.isis.atb.dao.template.util.ReadWriteMatcher;
import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.Persistent;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateContainerComplete;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.system.validation.TemplateContainerValidator;

/**
 * Keeps information about available templates and containers.
 * 
 * @author Vitaliy Semeshko
 */

@Repository
public class TemplateDaoImpl implements TemplateDao {

	private static final String DEFAULT_XML_DECLARATION = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

	private static final String FILE_EXT = ".xml";

	private static final String CONTAINERS_STORAGE = "data/groups";
	private static final String TEMPLATES_STORAGE = "data/templates";

	private Serializer reader = new Persister(new ReadWriteMatcher());
	
	private Serializer writer = new Persister(new ReadWriteMatcher(), new Format(DEFAULT_XML_DECLARATION));
	
	private ResourceManager resourceManager = ResourceManager.getInstance();

	private Map<Identifier, TemplateContainer> containers = new HashMap<Identifier, TemplateContainer>();

	private Map<Identifier, TemplateRef> templates = new HashMap<Identifier, TemplateRef>();

	private TemplateDaoImpl() {}

	/**
	 * Load data and keep it in the storage.
	 */
	@Override
	public void initialize() {
		// load templates
		for (File file : resourceManager.getFilesFromResourceFolder(TEMPLATES_STORAGE)) {
			TemplateRef template;
			try {
				template = reader.read(TemplateRef.class, file);
			} catch (Exception e) {
				throw new ATBException("Can't load template from file: " + file, e);
			}

			// all templates should be unique
			if (templates.containsKey(template.getUid())) {
				throw new ATBException("Not unique template found: " + template);
			}

			template.setFileName(file.getAbsolutePath());
			templates.put(template.getUid(), template);
		}

		// load containers
		for (File file : resourceManager.getFilesFromResourceFolder(CONTAINERS_STORAGE)) {
			TemplateContainer container;
			try {
				container = reader.read(TemplateContainer.class, file);
			} catch (Exception e) {
				throw new ATBException("Can't load template container from file: " + file, e);
			}	

			// all containers should be unique
			if (containers.containsKey(container.getUid())) {
				throw new ATBException("Not unique container found: " + container);
			}

			// check consistency, find all templates referenced by this container
			List<TemplateRef> dependencies = new ArrayList<TemplateRef>();
			for (TemplateRef ref : container.getTemplates()) {
				if (templates.containsKey(ref.getUid())) {
					dependencies.add(templates.get(ref.getUid()));
				} else {
					throw new ATBException("Can't find template: " + ref + 
							" referenced by the container: " + container);
				}
			}
			// replace references with dependencies
			container.clearTemplates();
			container.addTemplates(dependencies);

			container.setFileName(file.getAbsolutePath());
			containers.put(container.getUid(), container);
		}
	}

	/**
	 * Get all available template containers.
	 * 
	 * @return {@link Iterable} of {@link TemplateContainer}
	 */
	@Override
	public Collection<TemplateContainer> getContainers() {
		return containers.values();
	}

	/**
	 * Get complete template container.
	 * 
	 * @return {@link TemplateContainerComplete}
	 */
	public TemplateContainerComplete getCompleteContainer(TemplateContainer container) {
		// load real templates
		List<Template> templates = new ArrayList<Template>();
		for (TemplateRef ref : container.getTemplates()) {
			templates.add(getTemplate(ref));
		}
		
		// copy properties
		TemplateContainerComplete complete = new TemplateContainerComplete();
		complete.setName(container.getName());
		complete.setVersion(container.getVersion());
		complete.setDescription(container.getDescription());
		complete.setUid(container.getUid());
		complete.setAuthors(container.getAuthors());
		complete.setCreationDate(container.getCreationDate());
		
		// enrich with complete template data
		complete.addTemplates(templates);
		
		return complete;
	}
	
	/**
	 * Get all available templates.
	 * 
	 * @return {@link Iterable} of {@link TemplateRef}
	 */
	@Override
	public Collection<TemplateRef> getTemplateRefs() {
		return templates.values();
	} 

	/**
	 * Get complete template by reference.
	 * 
	 * @param ref reference
	 * @return initialized {@link Template}
	 */
	@Override
	public Template getTemplate(TemplateRef ref) {
		File source = new File(ref.getFileName());
		try {
			Template template = reader.read(Template.class, source);
			template.setFileName(ref.getFileName());
			return template;
		} catch (Exception e) {
			throw new ATBException("Can't load template from file", e);
		}
	}
	
	/**
	 * Get template reference.
	 * 
	 * @param id object identifier
	 * @return {@link TemplateRef}
	 */
	@Override
	public TemplateRef getTemplateRef(Identifier id) {
		return templates.get(id);
	}

	/**
	 * Save container.
	 * 
	 * @param container container to be saved
	 */
	@Override
	public void saveContainer(TemplateContainer container) {
		boolean isNew = !containers.containsKey(container.getUid()); 

		// if new container, assign file name
		if (isNew) {
			container.setFileName(generateUniqueFileName(CONTAINERS_STORAGE));
		}

		save(container);

		// after successful saving add to storage
		if (isNew) {
			containers.put(container.getUid(), container);
		}
	}

	/**
	 * Save template.
	 * 
	 * @param template template to be saved
	 */
	@Override
	public TemplateRef saveTemplate(Template template) {
		boolean isNew = !templates.containsKey(template.getUid()); 

		// if new template, assign file name
		if (isNew) {
			template.setFileName(generateUniqueFileName(TEMPLATES_STORAGE));
		}

		save(template);

		// after successful saving add/update storage
		TemplateRef ref = new TemplateRef();
		if (isNew) {
			ref = new TemplateRef();
			ref.setUid(template.getUid());
			ref.setFileName(template.getFileName());
		} else {
			ref = templates.get(template.getUid());
		}
		
		ref.setName(template.getName());
		ref.setVersion(template.getVersion());
		ref.setDescription(template.getDescription());
		ref.setCodeValue(template.getCodeValue());
		ref.setCodeMeaning(template.getCodeMeaning());
		ref.setCodingSchemeDesignator(template.getCodingSchemeDesignator());
		ref.setAuthors(template.getAuthors());
		ref.setCreationDate(template.getCreationDate());

		templates.put(template.getUid(), ref);
		
		return ref;
	}

	/**
	 * Delete container.
	 * 
	 * @param container container to be deleted
	 */
	@Override
	public void deleteContainer(TemplateContainer container) {
		new File(container.getFileName()).delete();
		containers.remove(container.getUid());
	}
	
	/**
	 * Delete template.
	 * 
	 * @param template template to be deleted
	 */
	@Override
	public void deleteTemplate(TemplateRef template) {
		// unlink from containers
		for (TemplateContainer container : containers.values()) {
			if (container.containsTemplate(template)) {
				container.removeTemplate(template);
				saveContainer(container);
			}
		}
		
		new File(template.getFileName()).delete();
		templates.remove(template.getUid());
	}

	/**
	 * Export container to specified file.
	 * 
	 * @param container container to export
	 * @param path export path
	 */
	@Override
	public void exportContainer(TemplateContainer container, File path) {
		FileOutputStream out = null;
		try {
			validateAndExportContainer(container, out = new FileOutputStream(path));
		} catch (FileNotFoundException e) {
			throw new ATBException("Error during container export.", e);
		} finally {
			IOUtils.closeQuietly(out);
		}
	}
	
	/**
	 * Export container to stream.
	 * 
	 * @param container container to export
	 * @param out output stream
	 */
	@Override
	public void validateAndExportContainer(TemplateContainer container, OutputStream out) {
		// write to byte buffer
		ByteArrayOutputStream bout = new ByteArrayOutputStream();
		export(getCompleteContainer(container), bout);
				
		// validate
		try {
			TemplateContainerValidator.validate(new ByteArrayInputStream(bout.toByteArray()));
		} catch (Exception e) {
			throw new ATBException(e);
		}

		// write to output
		try {
			out.write(bout.toByteArray());
		} catch (Exception e) {
			throw new ATBException(e);
		}
	}
	
	/**
	 * Export complete container to stream.
	 * 
	 * @param container container to export
	 * @param out output stream
	 */
	@Override
	public void exportContainer(TemplateContainerComplete container, OutputStream out) {
		export(container, out);
	}

	/**
	 * Export template to stream.
	 * 
	 * @param template complete template
	 * @param out output stream
	 */
	@Override
	public void exportTemplate(Template template, OutputStream out) {
		export(template, out);
	}

	/**
	 * Import container from specified path
	 * 
	 * @param path
	 * @return
	 */
	@Override
	public TemplateContainer importContainer(File path) {
		try {
			return importContainer(new FileInputStream(path));
		} catch (FileNotFoundException e) {
			throw new ATBException("Can't load template container from file: " + path, e);
		}
	}
	
	/**
	 * Import container from stream
	 * 
	 * @param input
	 * @return imported container
	 */
	@Override
	public TemplateContainer importContainer(InputStream input) {
		
		byte[] buffer = null;
		try {
			buffer = IOUtils.toByteArray(input);
		} catch (IOException e) {
			throw new ATBException(e);
		} finally {
			IOUtils.closeQuietly(input);
		}
		
		if (buffer == null || ArrayUtils.isEmpty(buffer)) {
			throw new ATBException("Can't import template container. Empty input.");
		}
		
		ByteArrayInputStream bufferedInputStream = new ByteArrayInputStream(buffer);
		
		// validate input
		try {
			TemplateContainerValidator.validate(bufferedInputStream);
			if (bufferedInputStream.markSupported()) {
				bufferedInputStream.reset();
			}
		} catch (Exception e) {
			throw new ATBException(e);
		}
		
		TemplateContainerComplete container;
		try {
			container = reader.read(TemplateContainerComplete.class, bufferedInputStream);
		} catch (Exception e) {
			throw new ATBException("Can't import template container.", e);
		}
		
		// generate new UID (all containers should be unique)
		if (containers.containsKey(container.getUid())) {
			container.setUid(Identifier.generate());
		}
		
		TemplateContainer toImport = new TemplateContainer();
		toImport.setName(container.getName());
		toImport.setVersion(container.getVersion());
		toImport.setDescription(container.getDescription());
		toImport.setUid(container.getUid());
		toImport.setAuthors(container.getAuthors());
		toImport.setCreationDate(container.getCreationDate());
		
		for (Template template : container.getTemplates()) {
			// generate new UID (all templates should be unique)
			if (templates.containsKey(template.getUid())) {
				template.setUid(Identifier.generate());
			}
			saveTemplate(template);
			toImport.addTemplate(templates.get(template.getUid()));
		}		
		
		saveContainer(toImport);
		
		return toImport;
	}
	
	/**
	 * Import template from stream
	 * 
	 * @param input
	 * @return reference to imported template
	 */
	@Override
	public TemplateRef importTemplate(InputStream input) {
		Template template;
		try {
			template = reader.read(Template.class, input);
		} catch (Exception e) {
			throw new ATBException("Can't import template.", e);
		} finally {
			IOUtils.closeQuietly(input);
		}
		
		// generate new UID (all templates should be unique)
		if (templates.containsKey(template.getUid())) {
			template.setUid(Identifier.generate());
		}
		
		return saveTemplate(template);
	}

	/**
	 * Save persistent object.
	 * 
	 * @param object object to be saved
	 */
	private void save(Persistent object) {
		File result = new File(object.getFileName());
		try {
			writer.write(object, result);
		} catch (Exception e) {
			throw new ATBException("Can't save data to file", e);
		}
	}

	/**
	 * Export persistent object.
	 * 
	 * @param object object to be exported
	 */
	private void export(Persistent object, OutputStream out) {
		try {
			writer.write(object, out);
		} catch (Exception e) {
			throw new ATBException("Can't export data to file", e);
		}
	}

	private String generateUniqueFileName(String resourcesFolder) {
		return resourceManager.getAbsoluteResourcePath(resourcesFolder) + File.separator + 
				UUID.randomUUID().toString() + FILE_EXT;
	}

}
