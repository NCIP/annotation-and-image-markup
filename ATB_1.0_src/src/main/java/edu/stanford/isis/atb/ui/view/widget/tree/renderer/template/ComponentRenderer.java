/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.TemplateComponent;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class ComponentRenderer extends AbstractElementRenderer<TemplateComponent> {

	public ComponentRenderer() {
		super(TreeImageBundle.getInstance().getComponentIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final TemplateComponent el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				String maxCardinality = getCardinalityText(el.getMaxCardinality());
				return "<html>" + trimToEmpty(el.getLabel()) + " " + 
    					"<font color=#AAAAAA><i>(min:" + el.getMinCardinality() + " max:" + maxCardinality + 
    					" " + shortText(el.getExplanatoryText()) + ")</i></font>" + 
    					"</html>";
			}
			
			@Override
			public String getToolTipText() {
				String maxCardinality = getCardinalityText(el.getMaxCardinality());
				return "<html>" + 
						"<img src=\"" + ComponentRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + trimToEmpty(el.getLabel()) + "</b><br><br>" + 
						"<b>Item Number: </b> " + el.getItemNumber() + "<br>" +
						"<b>Authors: </b> " + trimToEmpty(el.getAuthors()) + "<br>" +
						"<b>Group Label: </b> " + trimToEmpty(el.getGroupLabel()) + "<br>" +
						"<b>Min Cardinality: </b> " + el.getMinCardinality() + "<br>" +
						"<b>Max Cardinality: </b> " + maxCardinality + "<br>" +
						"<b>Should Display: </b> " + el.isShouldDisplay() + "<br>" +
						"<b>Explanatory Text: </b> " + shortText(el.getExplanatoryText()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return ComponentRenderer.this.getIcon();
			}
			
			private String getCardinalityText(long value) {
				return value >= Long.MAX_VALUE ? Const.TXT_INFINITY : String.valueOf(value);
			}
		};
	}

}
