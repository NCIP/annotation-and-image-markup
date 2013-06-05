/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.Collection;

/**
 * @author Vitaliy Semeshko
 */
public abstract class AbstractRemovableElement extends AbstractElement implements RemovableElement {

	private RemoveCommand removeCommand;
	
	@Override
	public void setRemoveCommand(RemoveCommand command) {
		this.removeCommand = command;
	}

	@Override
	public void remove() {
		if (removeCommand != null) {
			removeCommand.execute();
		}
	}

	public void initRemoveCommand(final Collection<?> collection) {
		// init remove command
		removeCommand = new RemoveCommand() {
			@Override
			public void execute() {
				collection.remove(AbstractRemovableElement.this);
			}
		};
	}
	
}
