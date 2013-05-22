/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static java.lang.String.valueOf;
import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Interval;
import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class IntervalRenderer extends AbstractElementRenderer<Interval> {

	public IntervalRenderer() {
		super(TreeImageBundle.getInstance().getIntervalIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Interval el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Interval: min: " + String.valueOf(el.getMinValue()) + 
						" max: " + String.valueOf(el.getMaxValue()) +
    					"</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + IntervalRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;Interval</b><br><br>" + 
						"<b>Min Value: </b> " + valueOf(el.getMinValue()) + "<br>" +
						"<b>Max Value: </b> " + valueOf(el.getMaxValue()) + "<br>" +
						"<b>Min Operator: </b> " + getOperatorText(el.getMinOperator()) + "<br>" +
						"<b>Max Operator: </b> " + getOperatorText(el.getMaxOperator()) + "<br>" +
						"<b>UCUM String: </b> " + trimToEmpty(el.getUcumString()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return IntervalRenderer.this.getIcon();
			}
			
			private String getOperatorText(Operator operator) {
				return operator == null ? Const.EMPTY : operator.toString();
			}
			
		};
	}

}
