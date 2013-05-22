/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.resources;

import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.view.resources.image.DefaultLazyIcon;
import edu.stanford.isis.atb.ui.view.resources.image.LazyIcon;

/**
 * Image bundle all other images (non-classified).
 * 
 * @author Vitaliy Semeshko
 */
public class MiscImageBundle {

	private static MiscImageBundle instance = new MiscImageBundle();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private MiscImageBundle() {}
	
	public static MiscImageBundle getInstance() {
		return instance;
	}
	
	private static final String ROOT_MISC_DIR = "etc/images/misc/";
	
	private static final String ROOT_SPLIT_PANE = ROOT_MISC_DIR + "splitpane/";
	
	private static final String LOGO = ROOT_MISC_DIR + "logo.png";  
	
	public LazyIcon getApplicationLogo() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(LOGO));
	}
	
	private static final String BUTTON_SUBMIT = ROOT_MISC_DIR + "button_submit.png";
	
	public LazyIcon getButtonSubmitIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(BUTTON_SUBMIT));
	}
	
	private static final String BUTTON_CANCEL = ROOT_MISC_DIR + "button_cancel.png";
	
	public LazyIcon getButtonCancelIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(BUTTON_CANCEL));
	}
	
	private static final String BUTTON_RESET = ROOT_MISC_DIR + "button_reset.png";
	
	public LazyIcon getButtonResetIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(BUTTON_RESET));
	}
	
	private static final String INFO = ROOT_MISC_DIR + "info.png";
	
	public LazyIcon getInfoIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(INFO));
	}
	
	private static final String COLLAPSE = ROOT_MISC_DIR + "collapse.png";
	
	public LazyIcon getCollapseIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COLLAPSE));
	}
	
	private static final String EXPAND = ROOT_MISC_DIR + "expand.png";
	
	public LazyIcon getExpandIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EXPAND));
	}
	
	private static final String DOWNLOAD = ROOT_MISC_DIR + "download.png";
	
	public LazyIcon getDownloadIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(DOWNLOAD));
	}
	
	private static final String VALIDATION_WARNING = ROOT_MISC_DIR + "validation_warning.png";
	
	public LazyIcon getValidationWarningIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(VALIDATION_WARNING));
	}
	
	private static final String SPLIT_PANE_LEFT_DEFAULT = ROOT_SPLIT_PANE + "left_default.png";
	
	public LazyIcon getSplitPaneLeftDefaultIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_LEFT_DEFAULT));
	}
	
	private static final String SPLIT_PANE_RIGHT_DEFAULT = ROOT_SPLIT_PANE + "right_default.png";
	
	public LazyIcon getSplitPaneRightDefaultIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_RIGHT_DEFAULT));
	}
	
	private static final String SPLIT_PANE_TOP_DEFAULT = ROOT_SPLIT_PANE + "top_default.png";
	
	public LazyIcon getSplitPaneTopDefaultIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_TOP_DEFAULT));
	}
	
	private static final String SPLIT_PANE_BOTTOM_DEFAULT = ROOT_SPLIT_PANE + "bottom_default.png";
	
	public LazyIcon getSplitPaneBottomDefaultIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_BOTTOM_DEFAULT));
	}
	
	private static final String SPLIT_PANE_LEFT_HOVER = ROOT_SPLIT_PANE + "left_hover.png";
	
	public LazyIcon getSplitPaneLeftHoverIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_LEFT_HOVER));
	}
	
	private static final String SPLIT_PANE_RIGHT_HOVER = ROOT_SPLIT_PANE + "right_hover.png";
	
	public LazyIcon getSplitPaneRightHoverIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_RIGHT_HOVER));
	}
	
	private static final String SPLIT_PANE_TOP_HOVER = ROOT_SPLIT_PANE + "top_hover.png";
	
	public LazyIcon getSplitPaneTopHoverIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_TOP_HOVER));
	}
	
	private static final String SPLIT_PANE_BOTTOM_HOVER = ROOT_SPLIT_PANE + "bottom_hover.png";
	
	public LazyIcon getSplitPaneBottomHoverIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SPLIT_PANE_BOTTOM_HOVER));
	}
	
}
