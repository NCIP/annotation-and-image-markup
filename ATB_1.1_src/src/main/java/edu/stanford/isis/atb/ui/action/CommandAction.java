/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.action;

import java.awt.event.ActionEvent;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.swing.AbstractAction;

import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.resources.image.LazyIcon;

/**
 * Action with configurable command.
 * 
 * @author Vitaliy Semeshko
 */
@SuppressWarnings("serial")
public class CommandAction extends AbstractAction {

	private Command command;
	
	private boolean nested;
	
	private List<CommandAction> subActions;

	public CommandAction(String text, LazyIcon icon) {
		this(text, icon, null);
	}
	
	public CommandAction(String text, LazyIcon icon, Command command) {
		super(text, icon == null ? null : icon.loadIcon());
		putValue(SHORT_DESCRIPTION, text);
		this.command = command;
	}
	
	public void setCommand(Command command) {
		// don't allow to change command
		if (this.command != null) {
			throw new RuntimeException("Command has already been assigned. Action: " + getValue(SHORT_DESCRIPTION));
		}
		this.command = command;
	}
	
	public Collection<CommandAction> getSubActions() {
		if (subActions == null) {
			return Collections.emptyList();
		}
		return subActions;
	}
	
	public void addSubAction(CommandAction action) {
		if (subActions == null) {
			subActions = new ArrayList<CommandAction>();
		}
		subActions.add(action);
		action.setNested(true);
	}
	
	public boolean hasSubActions() {
		return subActions != null && !subActions.isEmpty();
	}

	public boolean isNested() {
		return nested;
	}

	public void setNested(boolean nested) {
		this.nested = nested;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (command != null) {
			command.execute();
		}
	}

}
