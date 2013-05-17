/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb;

import static edu.stanford.isis.atb.SplashScreenHelper.splashInit;
import static edu.stanford.isis.atb.SplashScreenHelper.splashProgress;

import java.awt.EventQueue;
import java.io.File;
import java.lang.Thread.UncaughtExceptionHandler;
import java.util.Properties;

import javax.swing.JOptionPane;

import org.apache.commons.lang3.StringUtils;
import org.apache.log4j.PropertyConfigurator;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import edu.stanford.isis.atb.dao.template.TemplateDao;
import edu.stanford.isis.atb.service.ExceptionTranslator;
import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;

/**
 * Entry point
 * 
 * @author alansnyder
 */
public class Main {

	private static final String[] springConfiguration = {"classpath:conf/atb-application-context.xml"};
	
	private static final String LOG_PROPERTIES = "conf/log4j.properties";
	private static final String LOG_FILE_FOLDER = "log";
	private static final String LOG_FILE = "atb.log";
	private static final String APPENDER_FILE = "log4j.appender.file.File";
	
	public static void main(String[] args) {
		
		splashInit(500);
		
		splashProgress(10);
		
		// initialize log4j
		Properties property = new Properties();
		try {
			property.load(ResourceManager.getInstance().getResourceAsStream(LOG_PROPERTIES));
		} catch (Exception e) {
			throw new RuntimeException("Could not load log4j.properties file", e);
		}
		
		splashProgress(20);
		
		String path = ResourceManager.getInstance().getAbsoluteResourcePath(LOG_FILE_FOLDER) + File.separator + LOG_FILE;
		property.setProperty(APPENDER_FILE, path);
		PropertyConfigurator.configure(property);

		final Logger logger = LoggerFactory.getLogger(Main.class);
		
		splashProgress(30);
		
		// common exception handler
		Thread.setDefaultUncaughtExceptionHandler(new UncaughtExceptionHandler() {
			@Override
			public void uncaughtException(Thread t, Throwable e) {
				logger.error("Uncaught exception handled", e);
				
				Throwable translatedException = ExceptionTranslator.getInstance().translate(e);
				
				String msg = Const.MSG_ERROR;
				String errMsg = translatedException.getMessage();
				if (StringUtils.isNotEmpty(errMsg)) {
					msg = msg + "\n\n" + errMsg;
				}
				JOptionPane.showMessageDialog(null, msg, Const.DLG_TITLE_ERROR, JOptionPane.ERROR_MESSAGE);
			}
		});
		
		splashProgress(40);
		
		// initialize spring application context
		ApplicationContext ctx = new ClassPathXmlApplicationContext(springConfiguration);
		
		splashProgress(60);
		
		// initialize data
		TemplateDao templateDao = ctx.getBean(TemplateDao.class);
		templateDao.initialize();
		
		splashProgress(90);
		
		final Application app = ctx.getBean(Application.class);
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				app.start();
			}
		});
		
		splashProgress(100);
	}
	
}
