/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.NonQuantifiable;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class NonQuantifiableRenderer extends AbstractElementRenderer<NonQuantifiable> {

	public NonQuantifiableRenderer() {
		super(TreeImageBundle.getInstance().getNonQuantifiableIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final NonQuantifiable el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Non-Quantifiable: " + trimToEmpty(el.getCodeMeaning()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + NonQuantifiableRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Non-Quantifiable" + "</b><br><br>" + 
						"<b>Code Meaning: </b> " + trimToEmpty(el.getCodeMeaning()) + "<br>" +
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Schema Designator: </b> " + trimToEmpty(el.getSchemaDesignator()) + "<br>" +
						"<b>Schema Version: </b> " + trimToEmpty(el.getSchemaVersion()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return NonQuantifiableRenderer.this.getIcon();
			}
		};
	}

}
