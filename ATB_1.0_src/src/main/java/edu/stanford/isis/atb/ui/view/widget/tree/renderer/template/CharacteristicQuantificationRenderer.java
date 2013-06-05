/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class CharacteristicQuantificationRenderer extends AbstractElementRenderer<CharacteristicQuantification> {

	public CharacteristicQuantificationRenderer() {
		super(TreeImageBundle.getInstance().getCharacteristicQuantificationIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final CharacteristicQuantification el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Characteristic Quantification: " + trimToEmpty(el.getName()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + CharacteristicQuantificationRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Characteristic Quantification" + "</b><br><br>" + 
						"<b>Name: </b> " + trimToEmpty(el.getName()) + "<br>" +
						"<b>Annotator Confidence: </b> " + String.valueOf(el.isAnnotatorConfidence()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return CharacteristicQuantificationRenderer.this.getIcon();
			}
		};
	}

}
