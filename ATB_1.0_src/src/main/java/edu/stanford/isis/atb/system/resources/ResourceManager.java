/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.resources;

import java.io.File;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;

import edu.stanford.isis.atb.system.exception.ATBException;

/**
 * Resource manager.
 * 
 * @author Vitaliy Semeshko
 */
public class ResourceManager {

	private static ResourceManager instance = new ResourceManager();
	
	private ResourceManager() {}
	
	public static ResourceManager getInstance() {
		return instance;
	}
	
	/**
	 * Check if resource exists.
	 * 
	 * @param name name of the resource
	 * @return <code>true/false</code>
	 */
	public boolean isExists(String name) {
		URL url = getClass().getClassLoader().getResource(name); 
		return url == null ? false : true;
	}
	
	public InputStream getResourceAsStream(String name) {
		InputStream is = this.getClass().getClassLoader().getResourceAsStream(name); 
		
		if (is == null) {
			throw new ATBException("Cant' load resource: " + name);
		}
		return is;
	}
	
	public URL getResourceURL(String name) {
		URL location = this.getClass().getClassLoader().getResource(name);
		
		if (location == null) {
			throw new ATBException("Cant' load resource: " + name);
		}
		
		return location;
	}
	
	public URI getResourceURI(String name) {
		URL location = getResourceURL(name);
		try {
			return new URI(location.getPath());
		} catch (URISyntaxException e) {
			throw new ATBException("Cant' load resource (URI can't be created): " + name, e);
		} 
	}
	
	public Iterable<File> getFilesFromResourceFolder(String resourcesFolder) {
		try {
			Enumeration<URL> resources = getClass().getClassLoader().getResources(resourcesFolder);
			
			while (resources.hasMoreElements()) {
				// need URI here since path may contain spaces
				URI uri = new URI(resources.nextElement().getPath());
				File targetFolder = new File(uri.getPath());
				return new ArrayList<File>(Arrays.asList(targetFolder.listFiles()));
			}
			
			return Collections.emptyList();
		} catch (Exception e) {
			throw new ATBException("Can't load files from folder: " + resourcesFolder, e);
		}
	}
	
	public String getAbsoluteResourcePath(String resource) {
		URI uri = null;
		try {
			Enumeration<URL> resources = getClass().getClassLoader().getResources(resource);
			
			while (resources.hasMoreElements()) {
				// need URI here since path may contain spaces
				uri = new URI(resources.nextElement().getPath());
				return uri.getPath();
			}
		} catch (Exception e) {
			throw new ATBException("Can't find resource: " + resource, e);
		}
		
		throw new ATBException("No resource found: " + resource);
	}

}
