/*
 * Copyright (c) 2008-2013, Northwestern University
 * All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 *   Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *  
 *   Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *  
 *   Neither the name of the Northwestern University nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
