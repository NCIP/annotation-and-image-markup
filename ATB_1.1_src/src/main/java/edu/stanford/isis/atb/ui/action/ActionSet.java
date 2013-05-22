/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.action;

import java.util.HashMap;
import java.util.LinkedHashMap;

/**
 * @author Vitaliy Semeshko
 */
public class ActionSet {

	private static final CommandAction separatorPlacehorder = new CommandAction(null, null);
	
	private HashMap<Object, CommandAction> actions = new LinkedHashMap<Object, CommandAction>();
	
	public CommandAction get(Object key) {
		return actions.get(key);
	}
	
	public void add(Object key, CommandAction action) {
		actions.put(key, action);
	}
	
	public void addSeparator() {
		actions.put(null, separatorPlacehorder);
	}
	
	public boolean isSeparator(CommandAction action) {
		return separatorPlacehorder == action;
	}
	
	public Iterable<CommandAction> getAll() {
		return actions.values();
	}
	
}
