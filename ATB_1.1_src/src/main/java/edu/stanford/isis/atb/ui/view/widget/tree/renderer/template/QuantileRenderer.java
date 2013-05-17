/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static java.lang.String.valueOf;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Quantile;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class QuantileRenderer extends AbstractElementRenderer<Quantile> {

	public QuantileRenderer() {
		super(TreeImageBundle.getInstance().getQuantileIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Quantile el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Quantile: " + valueOf(el.getBins()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + QuantileRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;Quantile Level</b><br><br>" + 
						"<b>Bins: </b> " + valueOf(el.getBins()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return QuantileRenderer.this.getIcon();
			}
		};
	}

}
