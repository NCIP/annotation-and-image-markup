/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.SplashScreen;
import java.awt.geom.Rectangle2D;

/**
 * @author Vitaliy Semeshko
 */
public class SplashScreenHelper {

	static SplashScreen mySplash;                   // instantiated by JVM we use it to get graphics
    static Graphics2D splashGraphics;               // graphics context for overlay of the splash image
    static Rectangle2D.Double splashProgressArea;   // area where we draw the progress bar
	
    /**
     * Prepare the global variables for the other splash functions
     */
    public static void splashInit(int delay) {
        // the splash screen object is created by the JVM, if it is displaying a splash image
        mySplash = SplashScreen.getSplashScreen();
        
        // if there are any problems displaying the splash image
        // the call to getSplashScreen will returned null
        if (mySplash != null) {
            // get the size of the image now being displayed
            Dimension ssDim = mySplash.getSize();
            int height = ssDim.height;
            int width = ssDim.width;

            // stake out some area for our status information
            splashProgressArea = new Rectangle2D.Double(0, height * .8, width, 6);

            // create the Graphics environment for drawing status info
            splashGraphics = mySplash.createGraphics();

            splashProgress(0);
        }
        
        try {
			Thread.sleep(delay);
		} catch (InterruptedException e) {
			// ignore
		}
    }
    
    /**
     * Display a (very) basic progress bar
     * @param pct how much of the progress bar to display 0-100
     */
    public static void splashProgress(int pct) {
        if (mySplash != null && mySplash.isVisible()) {
            
        	splashGraphics.setPaint(Color.lightGray);
            splashGraphics.fill(splashProgressArea);
            
            splashGraphics.setPaint(Color.lightGray);
            splashGraphics.draw(splashProgressArea);

            // Calculate the width corresponding to the correct percentage
            int x = (int) splashProgressArea.getMinX();
            int y = (int) splashProgressArea.getMinY();
            int wid = (int) splashProgressArea.getWidth();
            int hgt = (int) splashProgressArea.getHeight();

            int doneWidth = Math.round(pct * wid / 100.f);
            doneWidth = Math.max(0, Math.min(doneWidth, wid - 1));

            // fill the done part one pixel smaller than the outline
            splashGraphics.setPaint(new Color(255, 98, 3));
            splashGraphics.fillRect(x, y+1, doneWidth, hgt-1);

            // make sure it's displayed
            mySplash.update();
        }
    }
	
}
