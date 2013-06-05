/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

/**
 * @author Vitaliy Semeshko
 */
public abstract class WatchingCallbackAdapter<T> extends CallbackAdapter<T> implements WatchingCallback<T> {

	private boolean cancelled;
	
	@Override
	public void notifyStatus(String status) {}
	
	@Override
	public void notifyCancelled() {}
	
	public void setCancelled(boolean cancelled) {
		this.cancelled = cancelled;
	}

	@Override
	public boolean isCancelled() {
		return cancelled;
	}
	
}
