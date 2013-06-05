/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.impl;

import org.springframework.core.task.SimpleAsyncTaskExecutor;

import edu.stanford.isis.atb.service.Command;

/**
 * @author Vitaliy Semeshko
 */
public abstract class AbstractService {

	private final SimpleAsyncTaskExecutor executor = new SimpleAsyncTaskExecutor();
	
	protected void executeAsynchronously(final Command command) {
		executor.execute(new Runnable() {
			@Override
			public void run() {
				command.execute();
			}
		});		
	}
	
}
