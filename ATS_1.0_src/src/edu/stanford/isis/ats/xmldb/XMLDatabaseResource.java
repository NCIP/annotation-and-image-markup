/*
 * Copyright Notice. Copyright 2011 - 2012 Northwestern University and Stanford
 * University ("caBIG® Participant"). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the "caBIG® Software").
 *
 * This caBIG® Software License (the "License") is between the National Cancer
 * Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. "Control" for purposes of this definition means (i)
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
 * 1. Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * 2. Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: "This product includes software
 * developed by Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University."
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * 3. You may not use the names "Northwestern University", "Stanford University",
 * "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
 * "caBIG®" to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * 4. For sake of clarity, and not by way of limitation, You are not prohibited by
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
 * 
 * 5. For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
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
package edu.stanford.isis.ats.xmldb;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;

import org.restlet.data.Form;
import org.restlet.data.Status;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;
import org.restlet.resource.ServerResource;

import com.sleepycat.db.DatabaseException;
import com.sleepycat.db.Environment;
import com.sleepycat.db.EnvironmentConfig;
import com.sleepycat.dbxml.XmlContainer;
import com.sleepycat.dbxml.XmlDocument;
import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlManager;
import com.sleepycat.dbxml.XmlManagerConfig;
import com.sleepycat.dbxml.XmlQueryContext;
import com.sleepycat.dbxml.XmlResults;
import com.sleepycat.dbxml.XmlValue;

import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.xmldb.data.QueryResultAdapter;


/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 * @see edu.cornell.sc.aimannotations.server.xmldbresource.XMLDatabaseResource
 */
public class XMLDatabaseResource extends ServerResource{
   protected Map<String, String> dbVars;
   protected Environment env;
   protected static final ATSLogger log = ATSLogger.getLogger();

   /**
    * Constructs a new XMLDatabaseResource, including setting up the
    * environment.
    */
   public XMLDatabaseResource() {

      dbVars = DatabaseConfig.getInstance().getDbVars();

      initXmlDbEnvironment();
   }

   protected void initXmlDbEnvironment()
   {
      File envHome = new File(dbVars.get("dbpath"));
      try {
         log.debug("New Environment envHome="+envHome);
         env = new Environment(envHome, null);
         //env = new Environment(envHome,createEnvironmentConfig());
         printEnvironmentConfig();

      } catch(FileNotFoundException e) {
         log.error("envHome not found. envHome="+envHome, e);

         EnvironmentConfig envConfig = createEnvironmentConfig();//new EnvironmentConfig();
         try {
            log.debug("New Environment envConfig");
            env = new Environment(envHome, envConfig);
         } catch(Exception e_create) {
             log.error("XDR70: "+e_create.getMessage(), e_create);
             log.info("No dB Environment - exiting.");
            System.exit(1);
         }

      } catch(DatabaseException e) {
         log.error("XDR75: "+e.getMessage(), e);
         log.info("Exiting. (db exception)");
         System.exit(1);
      } catch(UnsatisfiedLinkError ule) {
          log.error("XDR77: "+ule.getMessage(), ule);
          String javaLibPath = System.getProperty("java.library.path");
          log.debug("Check java.library.path. \n "+javaLibPath);
          log.info("Continue running ...");
      } catch(NoClassDefFoundError ncdfe) {
          log.error("XDR85: "+ncdfe.getMessage(), ncdfe);
          log.info("Continue running ...");
      }
   }


    /**
     * Create the EnvironmentConfig for this application.
     * @return
     */
    private EnvironmentConfig createEnvironmentConfig(){
        EnvironmentConfig envConf = new EnvironmentConfig();

        envConf.setAllowCreate(true);
        envConf.setInitializeCache(true);
        envConf.setInitializeLocking(true);
        envConf.setInitializeLogging(true);
        envConf.setTransactional(true);
        envConf.setCacheSize(200 * 1024 * 1024);
        envConf.setMaxLockers(4000);
        envConf.setMaxLocks(4000);
        envConf.setMaxLockObjects(4000);

        return envConf;
    }

    private void printEnvironmentConfig(){
        EnvironmentConfig ec;
        try {
            ec = env.getConfig();
            StringBuilder sb = new StringBuilder();
            sb.append("cache-size      : ").append(ec.getCacheSize()).append("\n");
            sb.append("cache-count     : ").append(ec.getCacheCount()).append("\n");
            sb.append("max-mutex       : ").append(ec.getMaxMutexes()).append("\n");
            sb.append("max-locks       : ").append(ec.getMaxLocks()).append("\n");
            sb.append("max-lockers     : ").append(ec.getMaxLockers()).append("\n");
            sb.append("max-lock-objects: ").append(ec.getMaxLockObjects()).append("\n");
            sb.append("lock-partitions : ").append(ec.getLockPartitions()).append("\n");
            sb.append("max-open-file   : ").append(ec.getMaxOpenFiles()).append("\n");

            log.debug("EnvironmentConfig: \n"+sb.toString());
        } catch (DatabaseException ex) {
            log.error("XDR-74: Out-Of-Memory DatabaseException: ", ex);
            System.exit(2);
            return;
        }
    }

   /**
    * This method must be called by all subclasses during the cleanup phase
    * after the XmlManager and XmlContainer have been closed in order to make
    * sure the environment can be used by other resources.
    * @throws DatabaseException
    */
   protected void cleanup()
        throws DatabaseException
   {
       if(env!=null){
           log.debug("Closing Environment");
           env.close();
           env=null;
       }else{
           log.info("cleanup() - com.sleepycat.db.Environment was already null.");
       }
   }

   /**
    * Puts an error string into an XML format.
    * @param message
    * @return
    */
   protected String genErrorXML(String message) {

       log.info("(XDR-145) Error: "+message);

      return "<?xml version=\"1.0\"?><error>\n <message>" +
      message.replaceAll("&", "&amp;").replaceAll("<", "&lt;").replaceAll(">", "&gt;") +
      "</message>\n</error>";
   }

   /**
    * Processes GET requests for information about the XML database:
    * listCollections(): list collections in database
    * listDocuments(c): list documents in collection c
    * @return
    */
   @Get
   public Representation getDatabaseInfo() {
      Form queryForm = this.getReference().getQueryAsForm();
      String getFunction = queryForm.getFirstValue("fun");

      log.info("fun="+getFunction);

      String[] funParams = parseParams(queryForm.getFirstValue("params"));
      if (getFunction == null) {
         setStatus(Status.CLIENT_ERROR_BAD_REQUEST, "No function requested");
         return new StringRepresentation(genErrorXML("No function requested."));
      }

      Representation returnRep;
      XmlManager dbManager = null;
      try {
         dbManager = new XmlManager(env, XmlManagerConfig.DEFAULT);

         //List collections
         if (getFunction.equals("listCollections")) {
            String returnString;
            File dbDir = new File(dbVars.get("dbpath"));
            String[] dbDirContents = dbDir.list();
            List<String> validContainers = new ArrayList<String>();
            for (String s : dbDirContents) {
               if (dbManager.existsContainer(s) != 0)
                  validContainers.add(s);
            }
            returnString = toXmlResultList(validContainers);
            returnRep = new StringRepresentation(returnString);
         }
         else if(getFunction.equals("listDocuments")) {
            if(funParams == null || funParams.length < 1) {
               setStatus(Status.CLIENT_ERROR_BAD_REQUEST, "No parameters passed for function");
               returnRep = new StringRepresentation(genErrorXML("No parameters passed for function."));
            }
            else {
               XmlContainer container = null;
               XmlResults results = null;
               try {
                  if(dbManager.existsContainer(funParams[0]) == 0) {
                     setStatus(Status.CLIENT_ERROR_BAD_REQUEST, "Collection " + funParams[0] + " does not exist");
                     returnRep = new StringRepresentation(genErrorXML("Collection " + funParams[0] + " does not exist."));
                  }
                  else {
                     container = dbManager.openContainer(funParams[0]);
                     results = container.getAllDocuments(null);
                     XmlDocument doc = dbManager.createDocument();
                     List<String> docNames = new ArrayList<String>();
                     while(results.next(doc)) {
                        docNames.add(doc.getName());
                     }
                     returnRep = new StringRepresentation(toXmlResultList(docNames));
                  }
               } catch(XmlException e) {
                  setStatus(Status.SERVER_ERROR_INTERNAL, "Error - internal database (XDR-224)");
                  returnRep = new StringRepresentation(genErrorXML("Error - internal database (XDR-224)."));
               } finally {
                  MetaDataUtil.deleteXmlResults(results);
                  MetaDataUtil.closeXmlContainer(container);
               }
            }
         }
         else {
            setStatus(Status.CLIENT_ERROR_BAD_REQUEST, "Unknown function requested");
            returnRep = new StringRepresentation(genErrorXML("Unknown function requested."));
         }
      } catch (DatabaseException e) {
         log.error("XDR-243: DatabaseException",e);
         setStatus(Status.SERVER_ERROR_INTERNAL, "Error - internal database (XDR-244)");
         returnRep = new StringRepresentation(genErrorXML("Error - internal database (XDR-244): " + e.getMessage()));
      } finally {
          MetaDataUtil.closeXmlManager(dbManager);
      }
      return returnRep;
   }

   /**
    * Returns a String containing XML representing a return value or list of
    * return values.
    * @param results
    * @return A String representation of the XML collection
    */
   protected String toXmlResultList(Collection<String> results) {
      String r = "";
      if(results.size() > 1)
         r += "<list>\n";
      for(String s : results)
         r += "<item>" + s + "</item>\n";
      if(results.size() > 1)
         r += "</list>";
      return r;
   }

   protected String toXmlTemplateDownload(Collection<String> results){

       for(String s: results){
           return s;
       }
       return "";
   }


   private String[] parseParams(String params) {
      if(params == null)
         return null;
      return params.split(",");
   }

    /**
     * Execute the given query and return results as a string. 
     * Most likely, the query will dictate the format of the output string
     *  
     * @param collection - db collection to use in query
     * @param namespace - namespace of the documents that are being queried
     * @param queryString - the actual XQuery to execute
     * @return returns string representation of the query results.
     */
    public List<String> processQuery(String collection, String namespace, String queryString) {
        return this.processQuery(collection, namespace, queryString, new QueryResultAdapter<String>() {
            @Override
            public String adaptResult(XmlValue value) {
                try {
                    return value.asString();
                } catch (XmlException ex) {
                    log.error("(XDR-390): Failed to convert query result to string. The value will be skipped.", ex);
                }
                return null;
            }
        });
    }

    /**
     * Execute given query and return result in the requested format
     *  
     * @param collection - name of the database collection to query
     * @param namespace - results namespace
     * @param queryString - actual query to execute
     * @param resultAdapter - converter, that makes results to be of a desired type
     * @return Returns a list of results of the desired type
     */
    public <T> List<T> processQuery(String collection, String namespace, String queryString, QueryResultAdapter<T> resultAdapter) {
        XmlManager dbManager = null;
        XmlContainer dbContainer = null;
        XmlResults queryResults = null;
        List<T> resultList = new ArrayList<T>();

        try {
            verifyEnv(env);
            dbManager = new XmlManager(env, XmlManagerConfig.DEFAULT);

            if (dbManager.existsContainer(collection) == 0)
                return resultList;

            dbContainer = dbManager.openContainer(collection);

            // Set the context and collection for this query
            XmlQueryContext dbQueryContext = dbManager.createQueryContext(XmlQueryContext.LiveValues, XmlQueryContext.Eager);
            if (namespace != null && !namespace.isEmpty())
                dbQueryContext.setNamespace("", namespace);

            // VK: Set metadata namespace
            dbQueryContext.setNamespace(MetaDataUtil.METADATA_URI_PREFIX, MetaDataUtil.METADATA_URI);
            
            queryResults = dbManager.query(queryString, dbQueryContext);

            log.debug("Found " + queryResults.size() + " queryResults");

            while (queryResults.hasNext()) {
                final T result = resultAdapter.adaptResult(queryResults.next());
                if (result != null)
                    resultList.add(result);
            }
        } catch (DatabaseException e) {
            log.error("XDR-410: DatabaseException for XQuery:" + queryString, e);
            setStatus(Status.SERVER_ERROR_INTERNAL, "XQuery evaluation error: " + e.getMessage());
            resultList = null;
        } catch (Exception e) {
            log.error("XDR-414: Exception", e);
            setStatus(Status.SERVER_ERROR_INTERNAL, "Internal error: " + e.getMessage());
            resultList = null;
        } finally {
            try {
                MetaDataUtil.deleteXmlResults(queryResults);
                MetaDataUtil.closeXmlContainer(dbContainer);
                MetaDataUtil.closeXmlManager(dbManager);
                cleanup();
            } catch (DatabaseException e) {
                log.error("XDR-422: DatabaseException", e);
            }
        }

        return resultList;
    }
    
    /**
     * ToDo: return this name to "getCollection"
     * @param queryForm
     * @return
     */
    public static String getCollection(Form queryForm){
        String collection = queryForm.getFirstValue("collection");
        if(collection==null || collection.isEmpty()){
            //collection = dbVars.get("defaultcontainer");
            collection = DatabaseConfig.getInstance().getDbVars().get("defaultcontainer");
        }

        if(collection==null){
            collection="ats_test.dbxml";
        }
        log.info("Setting collection to: '"+collection+"'");

        return collection;
    }


    /**
     * 
     * @param queryForm
     * @return
     */
    public static String getNamespace(Form queryForm){
        String namespace = queryForm.getFirstValue("namespace");
        if(namespace==null){
            namespace="gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate";
            log.debug("adding namespace");
        }
        return namespace;
   }

    /**
     * This method is for debugging why the Environment isn't always set.
     * @param env
     */
    private void verifyEnv(Environment env){
        try{
            if(env==null){
                log.debug("env==null. calling initXmlDbEnv...()");
                initXmlDbEnvironment();
            }else{
                log.debug("env version: "+Environment.getVersionString());
                log.debug("   env home: "+env.getHome().getAbsolutePath());
                //ToDo: might want to print stats here.

                EnvironmentConfig ec = env.getConfig();
                log.debug("EnvConfig lock partitions: "+ec.getLockPartitions());
                //ToDo: might want to print stats here.
            }

        }catch(Exception e){
            log.error("verifyEnv", e);
        }

    }

    /**
     * Check User-Agent for ATB value. 
     * @return true if request contains ATB; otherwise false.
     */
    protected boolean isRequestByAtb(){
        final String userAgent = getClientInfo().getAgent();
        return userAgent.toLowerCase().indexOf("atb") > 0;
    }
}
