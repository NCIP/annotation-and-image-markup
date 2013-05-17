/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.validation;

import java.io.IOException;
import java.io.InputStream;

import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.xml.sax.SAXException;

import edu.stanford.isis.atb.system.resources.ResourceManager;

/**
 * Validates template container against XML Schema.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateContainerValidator {

	private static final String SCHEMA_LOCATION = "etc/validation/AIMTemplateSchema.xsd";

	private static Schema schema;

	/**
	 * Validate input stream against schema.
	 * 
	 * @param input
	 * @throws SAXException
	 * @throws IOException
	 */
	public static void validate(InputStream input) throws SAXException, IOException {
		// lookup a factory for the W3C XML Schema language
		SchemaFactory factory = SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");

		// compile the schema
		if (schema == null) {
			Source source = new StreamSource(ResourceManager.getInstance().getResourceAsStream(SCHEMA_LOCATION));
			schema = factory.newSchema(source);
		}

		// get a validator from the schema
		Validator validator = schema.newValidator();

		// parse the document you want to check
		Source source = new StreamSource(input);

		// check the document
		validator.validate(source);
	}

}
