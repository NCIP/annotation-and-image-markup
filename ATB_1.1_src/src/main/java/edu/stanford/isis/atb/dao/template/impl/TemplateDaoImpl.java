/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
import edu.stanford.isis.atb.domain.template.Tag;
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
		
		for (Tag tag : container.getTags())
			complete.addTag(tag);
		
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
		
		for(Tag tag : container.getTags())
			toImport.addTag(tag);
		
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