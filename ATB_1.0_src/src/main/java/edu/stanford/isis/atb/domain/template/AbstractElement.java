/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.List;

import edu.stanford.isis.atb.domain.Initializable;

/**
 * @author Vitaliy Semeshko
 */
public abstract class AbstractElement implements Initializable {

	private boolean initialized = true;
	
	private Context context = new Context(this);
	
	@Override
	public boolean isInitialized() {
		return initialized;
	}

	@Override
	public void setInitialized(boolean initialized) {
		this.initialized = initialized;
	}

	public Context getContext() {
		return context;
	}

	public void initContext(final List<?> collection) {
		context.setHolder(collection);
	}
	
}
