/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.lexicon;

import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconRenderer extends AbstractElementRenderer<Lexicon> {

	public LexiconRenderer() {
		super(TreeImageBundle.getInstance().getLexiconIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Lexicon el) {
		
		return new RenderInfo() {
			
			@Override
			public String getText() {
				return "<html><font color=#AAAAAA>(1)</font> " + el.getName() + "</html>";
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + LexiconRenderer.this.getIconLocation() + "\"></img>" + 
						"<b>&nbsp;" + el.getName() + "</b><br><br>" + 
						"<b>Schema Designator: </b> " + trimToEmpty(el.getSchemaDesignator()) + "<br>" +
						"<b>Schema Version: </b> " + trimToEmpty(el.getSchemaVersion()) + "<br>" +
						"<b>Authors: </b> " + trimToEmpty(el.getAuthors()) + "<br>" +
						"<b>Read-Only: </b> " + String.valueOf(el.isReadOnly()) + "<br>" +
						"<b>Term Count: </b> " + String.valueOf(el.getTermCount()) + "<br>" +
						"<b>Creation Date: </b> " + formatDate(el.getCreationDate()) + "<br>" +
						"<b>Modification Date: </b> " + formatDate(el.getModificationDate()) + "<br>" +
						"<b>Description: </b> " + shortText(el.getDescription()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return LexiconRenderer.this.getIcon();
			}
		};
	}

}
