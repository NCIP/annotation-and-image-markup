/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Scale;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class ScaleRenderer extends AbstractElementRenderer<Scale> {

	public ScaleRenderer() {
		super(TreeImageBundle.getInstance().getScaleIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Scale el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Scale: " + shortText(el.getDescription()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + ScaleRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;Scale</b><br><br>" + 
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"<b>Comment: </b> " + shortText(el.getComment()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return ScaleRenderer.this.getIcon();
			}
		};
	}

}
