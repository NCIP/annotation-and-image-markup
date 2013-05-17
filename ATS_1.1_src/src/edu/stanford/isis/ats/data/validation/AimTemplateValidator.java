/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.ats.data.validation;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;

import javax.xml.XMLConstants;
import javax.xml.namespace.NamespaceContext;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Attr;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import edu.stanford.isis.ats.resources.Constants;
import edu.stanford.isis.ats.resources.ResourceManager;
import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.ATSStringUtils;

/**
 * AIM Template Validation class
 * 
 * @author Vladimir Kleper
 */
public class AimTemplateValidator {
    private static ATSLogger log = ATSLogger.getLogger();
    
    /**
     * Validates given template against its XSD and returns the template's UID
     * 
     * @param filePathName - template to validate
     * @return template UID
     * @throws TemplateValidationException if the given AIM template file does not pass validation
     */
    public static String validateTemplateAndGetUid(File file) throws TemplateValidationException {
        String uid = null;
        String xsdName = null;
        FileInputStream fileInputStream = null;
        // Get template's UID value and XSD file name
        try {
            final XPath xpath = XPathFactory.newInstance().newXPath();
            final String expression = "/aim:TemplateContainer/@*";
            fileInputStream = new FileInputStream(file);
            final InputSource inputSource = new InputSource(fileInputStream);
            
            xpath.setNamespaceContext(new NamespaceContext() {
                @SuppressWarnings("rawtypes")
                @Override
                public Iterator getPrefixes(String namespaceURI) {
                    return null;
                }
                @Override
                public String getPrefix(String namespaceURI) {
                    return XMLConstants.DEFAULT_NS_PREFIX;
                }
                @Override
                public String getNamespaceURI(String prefix) {
                    if ("aim".equals(prefix))
                        return Constants.AIM_NAMESPACE;
                    return XMLConstants.NULL_NS_URI;
                }
            });
            
            NodeList attributes = (NodeList)xpath.evaluate(expression, inputSource, XPathConstants.NODESET);
            for (int i=0; i < attributes.getLength() && (uid == null || xsdName == null); i++) {
                Attr attr = (Attr)attributes.item(i);
                if ("uid".equals(attr.getLocalName()))
                    uid = attr.getValue().trim();
                else if ("schemaLocation".equals(attr.getLocalName())) {
                    String schemaLocation = attr.getValue().trim();
                    int idx = schemaLocation.indexOf(" ");
                    if (idx >= 0) {
                        String maybeXsdName = schemaLocation.substring(idx).trim();
                        if (maybeXsdName.length() > 0)
                            xsdName = maybeXsdName;
                    }
                }
            }
        } catch (FileNotFoundException e) {
            log.error("(ATV-96): Cannot load file for attribute parsing: " + file.getPath(), e);
            throw new TemplateValidationException("Error reading file", "Cannot read file for attribute parsing: " + file.getName());
        } catch (XPathExpressionException e) {
            log.error("(ATV-99): Failed to find required attributes in the uploaded template. Template may not be valid." , e);
            throw new TemplateValidationException("Template data is missing", "Cannot read required attributes: " + file.getName());
        } finally {
            if (fileInputStream != null) {
                try {
                    fileInputStream.close();
                } catch (IOException e) {
                    log.error("(ATV-106): Failed to close file", e);
                } finally {
                    fileInputStream = null;                  
                }
            }
        }
        
        if (xsdName == null)
            throw new TemplateValidationException("Failed to validate the template", "Could not get schema file name from the document: " + file.getName());
        
        // Load one of the known XSDs
        final InputStream schemaFile = ResourceManager.getInstance().getResourceAsStream(xsdName);
        if (schemaFile == null)
            throw new TemplateValidationException("Failed to validate the template", "Could not load schema file: " + xsdName + " for template " + file.getName());

        try {
            // Validate doc against its schema
            fileInputStream = new FileInputStream(file.getPath());
            Source xmlFile = new StreamSource(fileInputStream);
            Source xsdFile = new StreamSource(schemaFile);
            SchemaFactory schemaFactory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = schemaFactory.newSchema(xsdFile);
            Validator validator = schema.newValidator();
            validator.validate(xmlFile);
            
            // Validate UID
            if (!ATSStringUtils.isValidUid(uid)) {
                log.error("Template has an invalid UID {" + uid + "}: " + file.getName(), null);
                throw new TemplateValidationException("Failed to validate template UID", "Template UID {" + uid + "} has invalid format. Template: " + file.getName());
            }
        } catch (FileNotFoundException e) {
            log.error("(ATV-137): Cannot load file for validation: " + file.getPath(), e);
            throw new TemplateValidationException("Error reading file", "Cannot read file for validation: " + file.getName());
        } catch (SAXException e) {
            log.error("(ATV-140): Uploaded template file validation error: " + file.getPath(), e);
            throw new TemplateValidationException("Error validating uploaded file: " + file.getName(), e.getMessage(), e);
        } catch (IOException e) {
            log.error("(ATV-143): Uploaded template file validation error: " + file.getPath(), e);
            throw new TemplateValidationException("IO Error validating uploaded file: " + file.getName(), e);
        } finally {
            if (fileInputStream != null) {
                try {
                    fileInputStream.close();
                } catch (IOException e) {
                    log.error("(ATV-150): Failed to close file", e);
                } finally {
                    fileInputStream = null;                  
                }
            }
        }
        
        return uid;
    }
}
