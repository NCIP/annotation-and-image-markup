/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.impl;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.util.Collection;

import org.apache.commons.io.output.ByteArrayOutputStream;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import edu.stanford.isis.atb.dao.template.TemplateDao;
import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateContainerComplete;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Callback;
import edu.stanford.isis.atb.service.TemplateService;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */

@Service
public class TemplateServiceImpl implements TemplateService {

	@Autowired
	private TemplateDao dao;

	@Override
	public Collection<TemplateRef> getTemplates() {
		return dao.getTemplateRefs();
	}
	
	@Override
	public Collection<TemplateContainer> getContainers() {
		return dao.getContainers();
	}
	
	@Override
	public Template getTemplate(TemplateRef ref) {
		return dao.getTemplate(ref);
	}

	@Override
	public TemplateRef getTemplateRef(Identifier id) {
		return dao.getTemplateRef(id);
	}

	@Override
	public void saveContainer(TemplateContainer container) {
		dao.saveContainer(container);
	}
	
	@Override
	public void saveTemplate(Template template) {
		dao.saveTemplate(template);
	}

	@Override
	public void deleteContainer(TemplateContainer container) {
		dao.deleteContainer(container);		
	}

	@Override
	public void deleteTemplate(TemplateRef template) {
		dao.deleteTemplate(template);
	}

	@Override
	public void exportContainer(TemplateContainer container, File path, Callback<Void> callback) {
		try {
			dao.exportContainer(container, path);
			callback.onSuccess(null);
		} catch (ATBException e) {
			callback.onFailure(e);
		}
	}

	@Override
	public void importContainer(File path, Callback<TemplateContainer> callback) {
		try {
			// import if everything is fine
			callback.onSuccess(dao.importContainer(path));
		} catch (Exception e) {
			callback.onFailure(e);
		}
	}

	@Override
	public TemplateRef copyTemplate(TemplateRef ref) {
		// get complete template and change name
		Template template = dao.getTemplate(ref);
		template.setName(compileCopyOfName(ref.getName()));
		
		// export existing template to buffer
		ByteArrayOutputStream buffer = new ByteArrayOutputStream();
		dao.exportTemplate(template, buffer);
		
		// import from buffer
		return dao.importTemplate(new ByteArrayInputStream(buffer.toByteArray()));
	}
	
	@Override
	public TemplateContainer copyContainer(TemplateContainer container) {
		// get complete container and change name (also for templates)
		TemplateContainerComplete origin = dao.getCompleteContainer(container);
		origin.setName(compileCopyOfName(origin.getName()));
		
		for (Template template : origin.getTemplates()) {
			template.setName(compileCopyOfName(template.getName()));
		}
		
		// export existing template to buffer
		ByteArrayOutputStream buffer = new ByteArrayOutputStream();
		dao.exportContainer(origin, buffer);
				
		// import from buffer
		return dao.importContainer(new ByteArrayInputStream(buffer.toByteArray()));
	}

	private String compileCopyOfName(String name) {
		return Const.TXT_COPY_OF + " " + name;
	}
	
}
