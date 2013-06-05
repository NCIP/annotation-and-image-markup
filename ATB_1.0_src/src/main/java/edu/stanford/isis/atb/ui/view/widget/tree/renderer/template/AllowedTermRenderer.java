/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class AllowedTermRenderer extends AbstractElementRenderer<AllowedTerm> {

	public AllowedTermRenderer() {
		super(TreeImageBundle.getInstance().getAllowedTermIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final AllowedTerm el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Allowed Term: " + trimToEmpty(el.getCodeMeaning()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + AllowedTermRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Allowed Term" + "</b><br><br>" + 
						"<b>Code Meaning: </b> " + trimToEmpty(el.getCodeMeaning()) + "<br>" +
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Schema Designator: </b> " + trimToEmpty(el.getSchemaDesignator()) + "<br>" +
						"<b>Schema Version: </b> " + trimToEmpty(el.getSchemaVersion()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return AllowedTermRenderer.this.getIcon();
			}
		};
	}

}
