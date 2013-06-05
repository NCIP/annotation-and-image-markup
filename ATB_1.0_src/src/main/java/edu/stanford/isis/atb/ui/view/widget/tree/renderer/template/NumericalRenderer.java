/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static java.lang.String.valueOf;
import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.Numerical;
import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class NumericalRenderer extends AbstractElementRenderer<Numerical> {

	public NumericalRenderer() {
		super(TreeImageBundle.getInstance().getNumericalIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Numerical el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Numerical: " + valueOf(el.getValue()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + NumericalRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;Numerical</b><br><br>" + 
						"<b>Value: </b> " + valueOf(el.getValue()) + "<br>" +
						"<b>Operator: </b> " + getOperatorText(el.getOperator()) + "<br>" +
						"<b>UCUM String: </b> " + trimToEmpty(el.getUcumString()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return NumericalRenderer.this.getIcon();
			}
			
			private String getOperatorText(Operator operator) {
				return operator == null ? Const.EMPTY : operator.toString();
			}
			
		};
	}

}
