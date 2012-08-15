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

package edu.stanford.isis.atb.ui;

import static edu.stanford.isis.atb.system.config.PropertyManager.CA_GRID_USER_NAME;
import static edu.stanford.isis.atb.system.config.PropertyManager.VERSION;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Cursor;
import java.awt.Insets;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;

import org.springframework.beans.factory.annotation.Autowired;

import edu.stanford.isis.atb.service.LexiconService;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.service.TemplateService;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.action.EventBusImpl;
import edu.stanford.isis.atb.ui.presenter.group.GroupPresenter;
import edu.stanford.isis.atb.ui.presenter.group.GroupSearchPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.LexiconEditorPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.LexiconPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.LocalSearchPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter;
import edu.stanford.isis.atb.ui.presenter.template.TemplateEditorPresenter;
import edu.stanford.isis.atb.ui.presenter.template.TemplatePresenter;
import edu.stanford.isis.atb.ui.presenter.template.TemplateSearchPresenter;
import edu.stanford.isis.atb.ui.view.group.impl.GroupSearchViewImpl;
import edu.stanford.isis.atb.ui.view.group.impl.GroupViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.impl.LexiconEditorViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.impl.LexiconViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.search.impl.LocalSearchViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.search.impl.SearchViewImpl;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.template.impl.TemplateEditorViewImpl;
import edu.stanford.isis.atb.ui.view.template.impl.TemplateSearchViewImpl;
import edu.stanford.isis.atb.ui.view.template.impl.TemplateViewImpl;

/**
 * Top level UI container.
 * 
 * @author Vitaliy Semeshko
 */

@org.springframework.stereotype.Component
public class Application implements AccessApplication {
	
	private static AccessApplication instance;
	
	private JFrame frame;
	
	private JTabbedPane tabbedPane;

	private boolean started;
	
	private PropertyManager properties = PropertyManager.getInstance();
	
	@Autowired
	private TemplateService templateService;
	
	@Autowired
	private LexiconService lexiconService;
	
	@Autowired
	private TemplateSearchService templateSearchService;
	
	@Autowired
	private EventBusImpl eventBus;
	
	public Application() {
		instance = this;
	}

	public void start() {
		if (started) {
			throw new ATBException("Application has been already started.");
		}
		
		init();
		
		if (!frame.isVisible()) {
			frame.setVisible(true);
		}
		
		started = true;
	}
	
	/**
	 * Initialize the contents of the frame.
	 */
	private void init() {
		initLookAndFeel();
		
		frame = new JFrame(Const.TTL_APPLICATION + " " + PropertyManager.getInstance().get(VERSION));
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		initHeader();
		
		JPanel main = new JPanel();
		frame.getContentPane().add(main, BorderLayout.CENTER);
		main.setLayout(new BorderLayout(0, 0));
		
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setFocusable(false);
		main.add(tabbedPane);
		
		// lexicon search
		SearchPresenter lexSearchPresenter = createLexiconSearchPresenter();
		
		initGroups();
		initTemplates(lexSearchPresenter);
		initLexicons(lexSearchPresenter);
		
		setMaximized();
	}

	public void initHeader() {
		JPanel header = new JPanel();
		header.setLayout(new BorderLayout());
		frame.getContentPane().add(header, BorderLayout.NORTH);
		
		JLabel logo = new JLabel(MiscImageBundle.getInstance().getApplicationLogo().loadIcon());
		header.add(logo, BorderLayout.WEST);
		
		JPanel headerInfo = new JPanel();
		headerInfo.setLayout(new BorderLayout());
		header.add(headerInfo, BorderLayout.CENTER);
		headerInfo.setBackground(Color.white);
		
		JLabel headerLabel = new JLabel(String.format(Const.LBL_CURRENT_USER, properties.get(CA_GRID_USER_NAME)));
		headerInfo.add(headerLabel, BorderLayout.WEST);
		
		JLabel info = new JLabel(MiscImageBundle.getInstance().getInfoIcon().loadIcon());
		info.setBorder(new EmptyBorder(new Insets(0, 0, 0, 10)));
		info.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		
		info.addMouseListener(new MouseAdapter() { 
			public void mouseClicked(MouseEvent e) {
				AboutDialog.showDialog();
			}
		});
		
		headerInfo.add(info, BorderLayout.EAST);
	}
	
	/**
	 * Initialize groups tab.
	 */
	private void initGroups() {
		// group search presenter
		GroupSearchPresenter searchPresenter = new GroupSearchPresenter(new GroupSearchViewImpl(), eventBus);
		searchPresenter.setSearchService(templateSearchService);
		searchPresenter.bindView();
		
		GroupViewImpl view = new GroupViewImpl();
		tabbedPane.addTab(Const.TAB_TEMPLATE_GROUPS, view.asComponent());
		GroupPresenter groupPresenter = new GroupPresenter(view, eventBus, templateService);
		groupPresenter.setSearchService(templateSearchService);
		groupPresenter.setSearchPresenter(searchPresenter);
		groupPresenter.bindView();
		
		eventBus.registerGroupPresenter(groupPresenter);
	}
	
	/**
	 * Initialize templates tab.
	 */
	private void initTemplates(SearchPresenter lexSearchPresenter) {
		TemplateEditorViewImpl editorView = new TemplateEditorViewImpl();
		TemplateViewImpl view = new TemplateViewImpl(editorView.asComponent());
		editorView.setEditFormManager(view);
		
		// template edit presenter
		TemplateEditorPresenter editorPresenter = new TemplateEditorPresenter(editorView);
		editorPresenter.bindView();
		editorPresenter.setLexiconSearchPresenter(lexSearchPresenter);
		
		// template search presenter
		TemplateSearchPresenter searchPresenter = new TemplateSearchPresenter(new TemplateSearchViewImpl(), eventBus);
		searchPresenter.setSearchService(templateSearchService);
		searchPresenter.bindView();
		
		tabbedPane.addTab(Const.TAB_TEMPLATES, view.asComponent());
		TemplatePresenter templatePresenter = new TemplatePresenter(view, eventBus);
		templatePresenter.setTemplateService(templateService);
		templatePresenter.setEditorPresenter(editorPresenter);
		templatePresenter.setSearchPresenter(searchPresenter);
		templatePresenter.bindView();
		
		eventBus.registerTemplatePresenter(templatePresenter);
	}
	
	/**
	 * Initialize lexicons tab.
	 */
	private void initLexicons(SearchPresenter lexSearchPresenter) {
		LexiconEditorViewImpl editorView = new LexiconEditorViewImpl();
		LexiconViewImpl view = new LexiconViewImpl(editorView.asComponent());
		editorView.setEditFormManager(view);

		LexiconEditorPresenter editorPresenter = new LexiconEditorPresenter(editorView);
		editorPresenter.setLexiconService(lexiconService);
		editorPresenter.bindView();
		
		tabbedPane.addTab(Const.TAB_LEXICONS, view.asComponent());
		LexiconPresenter lexiconPresenter = new LexiconPresenter(view, eventBus);
		lexiconPresenter.setLexiconService(lexiconService);
		lexiconPresenter.setEditorPresenter(editorPresenter);
		lexiconPresenter.setLexiconSearchPresenter(lexSearchPresenter);
		lexiconPresenter.bindView();
	}
	
	private SearchPresenter createLexiconSearchPresenter() {
		LocalSearchPresenter localSearchPresenter = new LocalSearchPresenter(new LocalSearchViewImpl());
		localSearchPresenter.setLexiconService(lexiconService);
		localSearchPresenter.bindView();
		
		SearchPresenter lexSearchPresenter = new SearchPresenter(new SearchViewImpl());
		lexSearchPresenter.setLocalSearchPresenter(localSearchPresenter);
		lexSearchPresenter.bindView();
		
		return lexSearchPresenter;
	}
	
	/**
	 * Initialize Look and Feel.
	 */
	private void initLookAndFeel() {
		UIManager.put ("ToolTip.background", Color.white);
		
		try {
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		} catch (Exception e) {
			throw new ATBException(e);
		}
	}
	
	private void setMaximized() {
		// Important: maximized mode works only after frame being packed 
		frame.pack();
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
	}

	@Override
	public Component asComponent() {
		return frame;
	}
	
	public static AccessApplication accessApplication() {
		return instance;
	}
	
}
