/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

package edu.stanford.isis.ats.resources;

import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;

/**
 * @author Vladimir Kleper
 */
public class ResourceManager {

    private static ResourceManager instance = new ResourceManager();

    private ResourceManager() {}

    public static ResourceManager getInstance() {
        return instance;
    }

    /**
     * Check if resource exists.
     *
     * @param name - name of the resource
     * @return <code>true/false</code>
     */
    public boolean isExists(String name) {
        URL url = this.getResourceURL(name);
        return url == null ? false : true;
    }

    public InputStream getResourceAsStream(String name) {
        return this.getClass().getClassLoader().getResourceAsStream(this.getFixedUpName(name));
    }

    public URL getResourceURL(String name) {
        return this.getClass().getClassLoader().getResource(this.getFixedUpName(name));
    }

    public URI getResourceURI(String name) throws URISyntaxException {
        URL location = getResourceURL(name);
        return new URI(location.getPath());
    }

    /**
     * Add current package name if none is supplied
     * @param name
     * @return fixed up package name
     */
    private String getFixedUpName(String name) {
        if (name != null && !name.contains("/"))
            return this.getClass().getPackage().getName().replace(".", "/") + "/" + name;

        return name;
    }
}
