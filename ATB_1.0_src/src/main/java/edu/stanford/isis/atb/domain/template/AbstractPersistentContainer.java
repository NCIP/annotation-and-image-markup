/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import java.util.Date;

import javax.validation.constraints.NotNull;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */
@Root(strict=false)
public class AbstractPersistentContainer extends AbstractElement implements Persistent {

	private String fileName;
	
	@NotNull(message = "{templateContainer.uid.notEmpty}")
	@Attribute 
	private Identifier uid;
	
	@NotEmpty(message = "templateContainer.name.notEmpty")
	@Attribute
	private String name;
	
	@Attribute(required=false)
	private String authors;
	
	@NotEmpty(message = "{templateContainer.version.notEmpty}")
	@Attribute
	private String version;
	
	@Attribute(required=false)
	private Date creationDate;
	
	@NotEmpty(message = "Description may not be null")
	@Attribute
	private String description;
	
	public AbstractPersistentContainer() {
		creationDate = new Date();
	}
	
	@Override
	public Identifier getUid() {
		return uid;
	}
	
	public void setUid(Identifier uid) {
		this.uid = uid;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getVersion() {
		return version;
	}

	public void setVersion(String version) {
		this.version = version;
	}

	public String getAuthors() {
		return authors;
	}

	public void setAuthors(String authors) {
		this.authors = authors;
	}

	public Date getCreationDate() {
		return creationDate;
	}

	public void setCreationDate(Date creationDate) {
		this.creationDate = creationDate;
	}
	
	public String getFileName() {
		return fileName;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((uid == null) ? 0 : uid.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		AbstractPersistentContainer other = (AbstractPersistentContainer) obj;
		if (uid == null) {
			if (other.uid != null)
				return false;
		} else if (!uid.equals(other.uid))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return name + " uid: [" + uid + "] " + "file: [" + trimToEmpty(fileName) + "]";
	}
	
}
