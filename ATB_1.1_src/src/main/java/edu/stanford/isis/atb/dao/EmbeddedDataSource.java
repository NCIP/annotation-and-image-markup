/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao;

import java.net.URI;

import org.apache.commons.dbcp.BasicDataSource;
import org.springframework.beans.factory.InitializingBean;

import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class EmbeddedDataSource extends BasicDataSource implements InitializingBean {

	private String prefix;
	private String location;
	private String extension;
	
	public void setUrlPrefix(String prefix) {
		this.prefix = prefix;
	}
	
	public void setLocation(String location) {
		this.location = location;
	}

	public void setExtension(String extension) {
		this.extension = extension;
	}

	@Override
	public void afterPropertiesSet() throws Exception {
		URI uri = ResourceManager.getInstance().getResourceURI(location);
		setUrl(prefix + uri.getPath().replace(extension, Const.EMPTY));
	}
	
}
