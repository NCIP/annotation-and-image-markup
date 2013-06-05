/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

import static edu.stanford.isis.atb.domain.template.DomainConst.DEFAULT_NAMESPACE;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.Namespace;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */
@Root(name="result", strict=false)
@Namespace(reference=DEFAULT_NAMESPACE)
public abstract class AbstractSingleResult {

	@Attribute
	protected String uid; 
	
	@Element(required=false)
	protected String name;
	
	@Element(required=false)
	protected String author;
	
	@Element(required=false)
	protected String desc;
	
	@Element(required=false)
	protected String disease;
	
	@Element(required=false)
	protected String bodyPart;
	
	@Element(required=false)
	protected String modality;

	public String getUid() {
		return uid;
	}

	public void setUid(String uid) {
		this.uid = uid;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAuthor() {
		return author;
	}

	public void setAuthor(String author) {
		this.author = author;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public String getDisease() {
		return disease;
	}

	public void setDisease(String disease) {
		this.disease = disease;
	}

	public String getBodyPart() {
		return bodyPart;
	}

	public void setBodyPart(String bodyPart) {
		this.bodyPart = bodyPart;
	}

	public String getModality() {
		return modality;
	}

	public void setModality(String modality) {
		this.modality = modality;
	}
	
}
