/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static java.lang.String.valueOf;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.OrdinalLevel;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class OrdinalLevelRenderer extends AbstractElementRenderer<OrdinalLevel> {

	public OrdinalLevelRenderer() {
		super(TreeImageBundle.getInstance().getOrdinalLevelIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final OrdinalLevel el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Ordinal Level: " + valueOf(el.getIntegerValue()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + OrdinalLevelRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;Ordinal Level</b><br><br>" + 
						"<b>Value: </b> " + valueOf(el.getIntegerValue()) + "<br>" +
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return OrdinalLevelRenderer.this.getIcon();
			}
		};
	}

}
