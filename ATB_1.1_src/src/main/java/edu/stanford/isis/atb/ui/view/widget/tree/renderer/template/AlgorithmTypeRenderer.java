/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class AlgorithmTypeRenderer extends AbstractElementRenderer<AlgorithmType> {

	public AlgorithmTypeRenderer() {
		super(TreeImageBundle.getInstance().getAlgorithmTypeIcon());
	}
	
	@Override
	public RenderInfo collectRenderInfo(final AlgorithmType el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Algorithm Type: " + trimToEmpty(el.getAlgorithmName()) + " " + 
    					"<font color=#AAAAAA><i>(" + trimToEmpty(el.getDescription()) + ")</i></font>" + 
    					"</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + TreeImageBundle.getInstance().getAlgorithmTypeIcon().getLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Algorithm Type" + "</b><br><br>" + 
						"<b>Algorithm Name: </b> " + trimToEmpty(el.getAlgorithmName()) + "<br>" +
						"<b>Algorithm Version: </b> " + trimToEmpty(el.getAlgorithmVersion()) + "<br>" +
						"<b>Math ML: </b> " + trimToEmpty(el.getMathML()) + "<br>" +
						"<b>Unique Identifier: </b> " + trimToEmpty(el.getUniqueIdentifier()) + "<br>" +
						"<b>Code Meaning: </b> " + trimToEmpty(el.getCodeMeaning()) + "<br>" +
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Coding Scheme Designator: </b> " + trimToEmpty(el.getSchemaDesignator()) + "<br>" +
						"<b>Coding Scheme Version: </b> " + trimToEmpty(el.getSchemaVersion()) + "<br>" +
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return AlgorithmTypeRenderer.this.getIcon();
			}
		};
	}

}
