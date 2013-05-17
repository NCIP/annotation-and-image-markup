/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class AnatomicEntityCharacteristicRenderer extends AbstractElementRenderer<AnatomicEntityCharacteristic> {

	public AnatomicEntityCharacteristicRenderer() {
		super(TreeImageBundle.getInstance().getAnatomicEntityCharIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final AnatomicEntityCharacteristic el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Anatomic Entity Characteristic: " + trimToEmpty(el.getLabel()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + AnatomicEntityCharacteristicRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Anatomic Entity Characteristic" + "</b><br><br>" + 
						"<b>Label: </b> " + trimToEmpty(el.getLabel()) + "<br>" +
						"<b>Item Number: </b> " + trimToEmpty(String.valueOf(el.getItemNumber())) + "<br>" +
						"<b>Authors: </b> " + trimToEmpty(el.getAuthors()) + "<br>" +
						"<b>Explanatory Text: </b> " + shortText(el.getExplanatoryText()) + "<br>" +
						"<b>Min Cardinality: </b> " + trimToEmpty(String.valueOf(el.getMinCardinality())) + "<br>" +
						"<b>Max Cardinality: </b> " + getCardinalityText(el.getMaxCardinality()) + "<br>" +
						"<b>Should Display: </b> " + trimToEmpty(String.valueOf(el.isShouldDisplay())) + "<br>" +
						"<b>Annotator Confidence: </b> " + String.valueOf(el.isAnnotatorConfidence()) + "<br>" +
						"<b>Group Label: </b> " + trimToEmpty(el.getGroupLabel()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return AnatomicEntityCharacteristicRenderer.this.getIcon();
			}

			private String getCardinalityText(long value) {
				return value >= Long.MAX_VALUE ? Const.TXT_INFINITY : String.valueOf(value);
			}
			
		};
	}

}
