/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.template;

import static edu.stanford.isis.atb.ui.Const.TXT_NAME;
import static edu.stanford.isis.atb.ui.Const.TXT_VALUE;
import static org.apache.commons.lang3.StringUtils.isEmpty;
import static org.apache.commons.lang3.StringUtils.trimToEmpty;

import javax.swing.Icon;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.domain.template.Tag;
import edu.stanford.isis.atb.domain.template.TagName;
import edu.stanford.isis.atb.domain.template.TagValue;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.TreeImageBundle;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.AbstractElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * @author Vitaliy Semeshko
 */
public class TagRenderer extends AbstractElementRenderer<Tag> {

	public TagRenderer() {
		super(TreeImageBundle.getInstance().getTagIcon());
	}

	@Override
	public RenderInfo collectRenderInfo(final Tag el) {

		return new RenderInfo() {
			
			@Override
			public String getText() {
				String name = getTagName();
				String value = getTagValue();
				return (isEmpty(name) ? TXT_NAME : name) + " / " + (isEmpty(value) ? TXT_VALUE : value);
			}
			
			@Override
			public String getToolTipText() {
				return "<html>" + 
						"<img src=\"" + TreeImageBundle.getInstance().getTagIcon().getLocation() + "\"></img>" + 
						"<b>&nbsp;" + trimToEmpty(getTagName()) + "</b><br><br>" + 
						"<b>Value: </b> " + trimToEmpty(getTagValue()) + "<br>" +
						"</html>";
			}
			
			@Override
			public Icon getIcon() {
				return TagRenderer.this.getIcon();
			}
			
			private String getTagName() {
				TagName tagName = el.getTagName();
				return tagName != null ? tagName.getCodeMeaning() : Const.EMPTY; 
			}
			
			private String getTagValue() {
				// value
				TagValue tagValue = el.getTagValue();
				if (tagValue != null) {
					CodedTerm tagCodedValue = tagValue.getCodedValue();
					return tagCodedValue == null ? tagValue.getStringValue() : tagCodedValue.getCodeMeaning();
				}
				return Const.EMPTY;
			}
			
		};
	}

}
