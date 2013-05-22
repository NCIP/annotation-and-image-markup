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

import edu.stanford.isis.atb.domain.template.QuestionType;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class QuestionTypeRenderer extends AbstractElementRenderer<QuestionType> {

	public QuestionTypeRenderer() {
		super(TreeImageBundle.getInstance().getQuestionTypeIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final QuestionType el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html>Question: " + trimToEmpty(el.getCodeMeaning()) + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + QuestionTypeRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + "Question" + "</b><br><br>" + 
						"<b>Code Meaning: </b> " + trimToEmpty(el.getCodeMeaning()) + "<br>" +
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Schema Designator: </b> " + trimToEmpty(el.getSchemaDesignator()) + "<br>" +
						"<b>Schema Version: </b> " + trimToEmpty(el.getSchemaVersion()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return QuestionTypeRenderer.this.getIcon();
			}
		};
	}

}
