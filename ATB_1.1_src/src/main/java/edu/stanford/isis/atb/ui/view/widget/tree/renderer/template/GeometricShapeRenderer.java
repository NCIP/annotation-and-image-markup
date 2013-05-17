/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.GeometricShapeType;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class GeometricShapeRenderer extends AbstractElementRenderer<GeometricShape> {

	public GeometricShapeRenderer() {
		super(TreeImageBundle.getInstance().getShapeIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final GeometricShape el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Geometric Shape: " + getValueText(el.getValue()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + GeometricShapeRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Geometric Shape" + "</b><br><br>" + 
						"<b>Value: </b> " + getValueText(el.getValue()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return GeometricShapeRenderer.this.getIcon();
			}
			
			private String getValueText(GeometricShapeType value) {
				return value == null ? Const.EMPTY : value.toString();
			}
			
		};
	}

}
