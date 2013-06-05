/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.impl;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import edu.stanford.isis.atb.service.CallbackAdapter;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.system.exception.ATBException;

/**
 * @author Vitaliy Semeshko
 */

@Ignore //this test is used for debugging only 

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations={"classpath:conf/atb-application-context.xml"})
public class TemplateSearchServiceTest {

	@Autowired
	private TemplateSearchService templateSearchService;
	
	@Test
	public void testLogin() {
		templateSearchService.login("guest2", "guest2", new CallbackAdapter<Void>() {
			@Override
			public void onSuccess(Void result) {
				System.out.println("Sucess!");
			}
			
			@Override
			protected void onFailure(ATBException caught) {
				System.out.println("Fail!");
			};
		});
		
		
//		try {
//			Thread.sleep(5000);
//		} catch (InterruptedException e) {
//			e.printStackTrace();
//		}
	}
	
}
