/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateRenderer extends AbstractElementRenderer<Template> {

	public TemplateRenderer() {
		super(TreeImageBundle.getInstance().getTemplateIcon());
	}
	
	@Override
	public RenderInfo collectRenderInfo(final Template el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>" + el.getName() + " " + 
                			"<font color=#AAAAAA><i>(ver." + el.getVersion() + " " + el.getDescription() + ")</i></font>" + 
                		"</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + TemplateRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + el.getName() + "</b><br><br>" + 
						"<b>UID: </b> " + el.getUid().getOriginal() + "<br>" +
						"<b>Version: </b> " + trimToEmpty(el.getVersion()) + "<br>" +
						"<b>Authors: </b> " + trimToEmpty(el.getAuthors()) + "<br>" +
						"<b>Creation Date: </b> " + formatDate(el.getCreationDate()) + "<br>" +
						"<b>Code Meaning: </b> " + trimToEmpty(el.getCodeMeaning()) + "<br>" +
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Schema Designator: </b> " + trimToEmpty(el.getCodingSchemeDesignator()) + "<br>" +
						"<b>Schema Version: </b> " + trimToEmpty(el.getCodingSchemeVersion()) + "<br>" +
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return TemplateRenderer.this.getIcon();
			}
		};
	}

}
