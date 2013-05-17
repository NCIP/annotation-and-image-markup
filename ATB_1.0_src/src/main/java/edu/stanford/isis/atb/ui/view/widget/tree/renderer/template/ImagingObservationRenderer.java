/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.ImagingObservation;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class ImagingObservationRenderer extends AbstractElementRenderer<ImagingObservation> {

	public ImagingObservationRenderer() {
		super(TreeImageBundle.getInstance().getImagingObservationIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final ImagingObservation el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Imaging Observation</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + ImagingObservationRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Imaging Observation" + "</b><br><br>" + 
						"<b>Annotator Confidence: </b> " + String.valueOf(el.isAnnotatorConfidence()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return ImagingObservationRenderer.this.getIcon();
			}
		};
	}

}
