/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.Collections;
import java.util.List;

import edu.stanford.isis.atb.system.exception.ATBException;

/**
 * @author Vitaliy Semeshko
 */
public class Context {

	private AbstractElement target;
	
	private List<?> holder;
	
	public Context(AbstractElement participant) {
		this.target = participant;
	}
	
	public void setHolder(List<?> holder) {
		this.holder = holder;
	}
	
	public boolean isMovingAllowed() {
		return holder != null && holder.size() > 1;
	}
	
	public boolean canMoveUp() {
		return isMovingAllowed() && holder.indexOf(target) > 0;
	}
	
	public boolean canMoveDown() {
		return isMovingAllowed() && holder.indexOf(target) < (holder.size() - 1);
	}
	
	public void moveUp() {
		if (canMoveUp()) {
			int currentIndex = holder.indexOf(target);
			Collections.swap(holder, currentIndex, currentIndex - 1);
		} else {
			throw new ATBException("Move up is not allowed");
		}
	}
	
	public void moveDown() {
		if (canMoveDown()) {
			int currentIndex = holder.indexOf(target);
			Collections.swap(holder, currentIndex, currentIndex + 1);
		} else {
			throw new ATBException("Move down is not allowed");
		}
	}
	
}
