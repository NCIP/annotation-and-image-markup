/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.resources;

import java.io.File;
import java.io.IOException;

import org.springframework.core.io.ByteArrayResource;

/**
 * Byte array resource with link to file.
 * <br/>
 * <b>Note:</b> this class is created only for ATS publish purposes.
 * It only overrides methods that are important for uploading.
 * 
 * @author Vitaliy Semeshko
 */
public class FileBackedByteArrayResource extends ByteArrayResource {

	private File file;
	
	public FileBackedByteArrayResource(byte[] byteArray, File file) {
		super(byteArray);
		this.file = file;
	}

	@Override
	public File getFile() throws IOException {
		return file;
	}
	
	@Override
	public String getFilename() throws IllegalStateException {
		return file.getName();
	}
	
}
