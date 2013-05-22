/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui;

import static edu.stanford.isis.atb.system.config.PropertyManager.CA_GRID_USER_NAME;

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
		
		frame = new JFrame(Const.TTL_APPLICATION);
		
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
