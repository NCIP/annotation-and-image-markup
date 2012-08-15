/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package edu.stanford.isis.atb.ui.view.lexicon.search.impl;

import static edu.stanford.isis.atb.ui.Const.HNT_REMOVE_TERM;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dialog.ModalityType;
import java.awt.FlowLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collection;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.view.base.TwoCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.lexicon.search.SearchView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.EscapeDialog;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * Default lexicon search view.
 * 
 * @author Vitaliy Semeshko
 */
public class SearchViewImpl extends TwoCellSplitPaneView implements SearchView {

	private static final int BATCH_MODE_WIDTH_EXTENSION = 280;
	
	private EscapeDialog dialog = new EscapeDialog();

	private JTabbedPane tabbedPane;
	
	private Command submitCommand;

	private ScrollableBlockWIthToolbar allowedTermsPane = new ScrollableBlockWIthToolbar();

	private GenericTable<LexiconTermAttributes> allowedTermsTable = new GenericTable<LexiconTermAttributes>();
	
	private CommandAction removeAllowedTermAction;
	
	private MiscImageBundle miscImages = MiscImageBundle.getInstance();

	private ToolBarImageBundle tbImages = ToolBarImageBundle.getInstance();
	
	public SearchViewImpl() {
		splitPaneMain.setResizeWeight(1);
		dialog.setTitle(Const.TTL_LEXICON_SEARCH);
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		dialog.add(asComponent());
		dialog.setSize(860, 640);
		
		initTabs();
		initBottomPane();
		initRightPane();
	}
	
	public void initTabs() {
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setFocusable(false);
		setLeftComponent(tabbedPane);
	}

	@Override
	public void setLocalSearchTab(Component tab) {
		tabbedPane.addTab(Const.TAB_LOCAL_LEXICON_SEARCH, tab);
	}

	@Override
	public void setRemoteSearchTab(Component tab) {
		tabbedPane.addTab(Const.TAB_BIOPORTAL_LEXICON_SEARCH, tab);
		tabbedPane.setEnabledAt(1, false);
	}

	private void initBottomPane() {
		JPanel bottom = new JPanel(new FlowLayout());

		JButton btnSubmit = new JButton(Const.BTN_OK, miscImages.getButtonSubmitIcon().loadIcon());
		JButton btnCancel = new JButton(Const.BTN_CANCEL, miscImages.getButtonCancelIcon().loadIcon());

		bottom.add(btnSubmit);
		bottom.add(btnCancel);
		
		setBottomComponent(bottom);
		
		btnSubmit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				submitCommand.execute();
				dialog.setVisible(false);
			}
		});

		btnCancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialog.setVisible(false);
			}
		});
	}

	private void initRightPane() {
		allowedTermsPane.setScrollableAreaBackground(Color.white);
		allowedTermsPane.setCaptionText(Const.LBL_ALLOWED_TERMS);
		allowedTermsPane.setPreferredWidth(BATCH_MODE_WIDTH_EXTENSION);
		hideRightComponent();
		
		allowedTermsPane.setMainComponent(allowedTermsTable);
		
		allowedTermsTable.addTextColumn(new TextColumnValue<LexiconTermAttributes>() {
			@Override
			public String getValue(LexiconTermAttributes source) {
				return source.getCodeValue();
			}
		}, Const.COLUMN_VALUE, 90, true, false);
		
		allowedTermsTable.addTextColumn(new TextColumnValue<LexiconTermAttributes>() {
			@Override
			public String getValue(LexiconTermAttributes source) {
				return source.getCodeMeaning();
			}
		}, Const.COLUMN_MEANING, 180, true, false);
		
		// add actions
		removeAllowedTermAction = new CommandAction(HNT_REMOVE_TERM, tbImages.getDeleteIcon());
		allowedTermsPane.addToolBarAction(removeAllowedTermAction);
		removeAllowedTermAction.setCommand(new Command() {
			@Override
			public void execute() {
				allowedTermsTable.removeSelectedValue();
			}
		});
	}
	
	@Override
	public void setSubmitCommand(Command command) {
		submitCommand = command;
	}

	@Override
	public void setAllowedTerms(Collection<LexiconTermAttributes> terms) {
		allowedTermsTable.setValues(terms);
	}

	@Override
	public void addAllowedTerm(LexiconTermAttributes term) {
		allowedTermsTable.addValue(term);
	}

	@Override
	public Collection<LexiconTermAttributes> getAllowedTerms() {
		return allowedTermsTable.getValues();
	}

	@Override
	public void showAsDialog(boolean showRightPane, Command afterShowing) {
		if (showRightPane) {
			if (!isShowingRightComponent()) {
				dialog.setSize(dialog.getWidth() + BATCH_MODE_WIDTH_EXTENSION, dialog.getHeight());
			}
			showRightComponent(allowedTermsPane);
		} else {
			if (isShowingRightComponent()) {
				dialog.setSize(dialog.getWidth() - BATCH_MODE_WIDTH_EXTENSION, dialog.getHeight());
			}
			hideRightComponent();
		}

		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);

		if (afterShowing != null) {
			afterShowing.execute();
		}
		
		dialog.setVisible(true);
	}

}
