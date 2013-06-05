/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.importexport;

import java.io.InputStream;
import java.io.OutputStream;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.service.WatchingCallback;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconImportExport {

	public void importFromCsv(String name, InputStream in, WatchingCallback<Lexicon> callback);
	
	public void exportToCsv(Lexicon lexicon, OutputStream out, WatchingCallback<Void> callback);
	
}
