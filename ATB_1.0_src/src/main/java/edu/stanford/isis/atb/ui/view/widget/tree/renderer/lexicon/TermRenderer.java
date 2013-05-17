/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.lexicon;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class TermRenderer extends AbstractElementRenderer<Term> {

	public TermRenderer() {
		super(TreeImageBundle.getInstance().getAllowedTermIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Term el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html><font color=#AAAAAA>(" + el.getLevelNumber() + ")</font> " + el.getCodeMeaning() + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + TermRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + el.getCodeMeaning() + "</b><br><br>" + 
						"<b>Code Value: </b> " + trimToEmpty(el.getCodeValue()) + "<br>" +
						"<b>Level Number: </b> " + String.valueOf(el.getLevelNumber()) + "<br>" +
						"<b>Creation Date: </b> " + formatDate(el.getCreationDate()) + "<br>" +
						"<b>Modification Date: </b> " + formatDate(el.getModificationDate()) + "<br>" +
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return TermRenderer.this.getIcon();
			}
		};
	}

}
