/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class CalculationRenderer extends AbstractElementRenderer<Calculation> {

	public CalculationRenderer() {
		super(TreeImageBundle.getInstance().getCalculationIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Calculation el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return el.toString();
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + CalculationRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Calculation" + "</b><br><br>" + 
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return CalculationRenderer.this.getIcon();
			}
		};
	}

}
