/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.ats.xmldb;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.restlet.data.Form;

import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.ATSStringUtils;

/**
 * Creates a XQuery String for a particular search.
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class ATSQueryBuilder {

    private static ATSLogger log = ATSLogger.getLogger();

    private final String xQuerySearch;

    public static class Builder {

        private static final String PARAM_TAG_NAME = "tgn";
        private static final String PARAM_TAG_VALUE = "tgv";
        private static final String PARAM_USER_NAME = "userName"; // fake param for the query's where clause
        private static final String PARAM_RESULT_START_INDEX = "index"; // 0-based index of the results to return
        private static final String PARAM_RESULT_COUNT_PER_PAGE = "limit"; // number of results to return
        private static int defaultResultStartIndex = 0;
        private static int defaultResultCountPerPage = 200;
        
        private boolean isContainer;

        private static final Map<String,String> tWhereMap = createTemplateWhereClauses();
        private static final Map<String,String> cWhereMap = createContainerWhereClauses();

        private Form queryForm;
        private String userName;

        boolean isXml = false;


        /**
         * Constructor
         * @param isContainer
         */
        public Builder(boolean isContainer) {
            this.isContainer = isContainer;
        }

        /**
         * Builder
         * @return
         */
        public ATSQueryBuilder build() {
            return new ATSQueryBuilder(this);
        }

        public Builder formData(Form queryForm) {
            this.queryForm = queryForm;
            return this;
        }

        public Builder userName(String userName) {
            this.userName = userName;
            return this;
        }
        
        public Builder setXmlReturnType(boolean useXml) {
            isXml = useXml;
            return this;
        }

        public String createString() {

            if (queryForm == null) {
                throw new IllegalStateException("no queryForm");
            }

            final StringBuilder sb = new StringBuilder();
            final String collection = XMLDatabaseResource.getCollection(queryForm);
//            String namespace = XMLDatabaseResource.getNamespace(queryForm);
            // zero-based index of the first found item to display
            int startIndex = Math.abs(ATSStringUtils.tryParseInt(queryForm.getFirstValue(PARAM_RESULT_START_INDEX, Integer.toString(defaultResultStartIndex)), defaultResultStartIndex));
            int limit = Math.abs(ATSStringUtils.tryParseInt(queryForm.getFirstValue(PARAM_RESULT_COUNT_PER_PAGE, Integer.toString(defaultResultCountPerPage)), defaultResultCountPerPage));

            // Add user name to the query
            if (userName != null) {
                queryForm.set(PARAM_USER_NAME, userName);
            }
            sb.append(getXQueryTagFunction());

            sb.append("(");
            if (isContainer) {
                sb.append("for $Tp in collection(\"").append(collection).append("\")/aim:TemplateContainer \n");
                sb.append(getCommonXPathContainQueryV2(false));
                sb.append(createWhereClause(getWhereClauses(cWhereMap)));
                if (isXml) {
                    sb.append(getXmlXPathReturn(false));
                } else {
                    sb.append(getCommonXPathReturn(false));
                }

            } else {
                sb.append("for $Tp in collection(\"").append(collection).append("\")/aim:TemplateContainer/aim:Template \n");
                sb.append(getCommonXPathContainQueryV2(true));
                sb.append(createWhereClause(getWhereClauses(tWhereMap)));
                if (isXml) {
                    sb.append(getXmlXPathReturn(true));
                } else {
                    sb.append(getCommonXPathReturn(true));
                }

            }
            sb.append("\n)");
            sb.append("[position() = ").append(startIndex + 1).append(" to ").append(startIndex + limit).append("]");
            sb.append("\n");

            return sb.toString();
        }

        /**
         * Find all the where clauses and replace them.
         * 
         * @param map
         * @return
         */
        private Set<String> getWhereClauses(Map<String, String> map) {
            Set<String> retVal = new HashSet<String>();
            Set<String> keySet = map.keySet();

            for (String curr : keySet) {
                final String searchString = queryForm.getFirstValue(curr);
                if (searchString != null) {
                    String whereClause = map.get(curr);
                    retVal.add(whereClause.replaceAll("%searchString%", searchString));
                }
            }

            return retVal;
        }

        /**
         * Creates the where clause part of the XQuery string.
         * @param whereClauseSet 
         */
        private static String createWhereClause(Set<String> whereClauseSet) {
            if (whereClauseSet == null)
                return "";

            final StringBuilder sb = new StringBuilder();
            log.debug("number of where clauses: " + whereClauseSet.size());
            for (String curr : whereClauseSet) {
                if (sb.length() > 0) {
                    sb.append(" and ");
                } else {
                    sb.append("where ");
                }
                sb.append(curr);
            }
            sb.append("\n");

            return sb.toString();
        }

        private static Map<String, String> createTemplateWhereClauses() {
            final Map<String, String> retVal = new HashMap<String, String>();

            retVal.put("tn", "fn:contains(lower-case($tmpName),lower-case(\"%searchString%\"))");
            retVal.put("td", "fn:contains(lower-case($tempDesc),lower-case(\"%searchString%\"))");
            retVal.put("ta", "fn:contains(lower-case($tempAuthors),lower-case(\"%searchString%\"))");
            retVal.put("d", "fn:contains(lower-case(string($disease)),lower-case(\"%searchString%\"))");
            retVal.put("bp", "fn:contains(lower-case(string($bodyPart)),lower-case(\"%searchString%\"))");
            retVal.put("m", "fn:contains(lower-case($modality),lower-case(\"%searchString%\"))");
            retVal.put(PARAM_TAG_NAME, "fn:contains(lower-case($tagNames),lower-case(\"%searchString%\"))");
            retVal.put(PARAM_TAG_VALUE, "fn:contains(lower-case($tagValues),lower-case(\"%searchString%\"))");
            retVal.put(PARAM_USER_NAME, "($userName eq \"%searchString%\" or (lower-case($permission) eq 'public') or (string-length($allowedUser) > 0))");

            return retVal;
        }

        private static Map<String, String> createContainerWhereClauses() {
            final Map<String, String> retVal = new HashMap<String, String>();

            retVal.put("cn", "fn:contains(lower-case($tmpName),lower-case(\"%searchString%\"))");
            retVal.put("cd", "fn:contains(lower-case($tempDesc),lower-case(\"%searchString%\"))");
            retVal.put("ca", "fn:contains(lower-case($tempAuthors),lower-case(\"%searchString%\"))");
            retVal.put("d", "fn:contains(lower-case($disease),lower-case(\"%searchString%\"))");
            retVal.put("bp", "fn:contains(lower-case($bodyPart),lower-case(\"%searchString%\"))");
            retVal.put("m", "");
            retVal.put(PARAM_TAG_NAME, "fn:contains(lower-case($tagNames),lower-case(\"%searchString%\"))");
            retVal.put(PARAM_TAG_VALUE, "fn:contains(lower-case($tagValues),lower-case(\"%searchString%\"))");
            retVal.put(PARAM_USER_NAME, "($userName eq \"%searchString%\" or (lower-case($permission) eq 'public') or (string-length($allowedUser) > 0))");

            retVal.put("metadata-owner", "fn:contains(lower-case($metaDataOwner),lower-case(\"%searchString%\"))");
            retVal.put("metadata-publish", "fn:contains(lower-case($metaDataPermission),lower-case(\"%searchString%\"))");

            return retVal;
        }

        private String getCommonXPathContainQueryV2(boolean includeModality) {
            final StringBuilder sb = new StringBuilder();
            sb.append("let $tmpName := $Tp/@name \n");
            sb.append("let $tempAuthors := $Tp/@authors \n");
            sb.append("let $tempDesc := $Tp/@description \n");
            if(includeModality){
                sb.append("let $modality := $Tp/@modality \n");
            }
            sb.append("let $uid := $Tp/@uid \n");
            sb.append("let $allTags := $Tp/aim:Tags \n");

            sb.append("let $bodyPart := aim:getMatchingTagValues(aim:getMatchingTagNodes($allTags, 'Body Part', false()), '', true()) (: Comma-separated list of all body parts :) \n");
            sb.append("let $disease := aim:getMatchingTagValues(aim:getMatchingTagNodes($allTags, 'Disease', false()), '', true()) (: Comma-separated list of all deseases :) \n");

            // Arbitrary Tag Query
            sb.append("let $tagName := '").append(queryForm.getFirstValue(PARAM_TAG_NAME, "")).append("' \n"); 
            sb.append("let $tagValue := '").append(queryForm.getFirstValue(PARAM_TAG_VALUE, "")).append("' \n");
            sb.append("let $tags := aim:getMatchingTagNodes($allTags, $tagName, true()) \n");
            sb.append("let $tagValues := aim:getMatchingTagValues(if (string-length($tagName) > 0) then $tags else $allTags/aim:Tag, $tagValue, true()) \n");
            sb.append("let $tagNames := aim:getTagNamesAsString($tags) \n");

            // User permission
            sb.append("let $userName := aim:getTemplateMetadata($Tp, '").append(MetaDataUtil.OWNER).append("') \n");
            sb.append("let $permission := aim:getTemplateMetadata($Tp, '").append(MetaDataUtil.PERMISSION).append("') \n");
            sb.append("let $allowedUsers := aim:getTemplateMetadata($Tp, '").append(MetaDataUtil.ALLOWED_USER).append("') \n");
            sb.append("let $allowedUser := (for $nm in tokenize($allowedUsers, ',') where lower-case($nm) eq lower-case('").append(this.userName == null ? "" : this.userName).append("') return $nm) \n");
            
            return sb.toString();
        }

        /**
         * Create the code that concatenates XQuery codes.
         *
         * The function that is created will look for
         *
         * @return
         */
        private static String getXQueryTagFunction(){
            return "xquery version \"1.0\"; \n" +
                    "declare namespace aim = \"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate\"; \n" +
                    "\n" +
                    "(: Returns a list of tag nodes that matches the given tag name :) \n" +
                    "declare function aim:getMatchingTagNodes($tagContainer as element()?, $tagName as xs:string, $partial as xs:boolean) as element(aim:Tag)* \n" +
                    "{ \n" +
                    "   for $currentTag in (if ($partial) then $tagContainer/aim:Tag[aim:TagName/fn:contains(lower-case(@codeMeaning),lower-case($tagName))] else $tagContainer/aim:Tag[aim:TagName/lower-case(@codeMeaning)=lower-case($tagName)]) \n" +
                    "   return $currentTag \n" +
                    "}; \n" +
                    "(: Returns comma-separated list of matching tag values from the given sequence of tags :) \n" +
                    "declare function aim:getMatchingTagValues($tags as element(aim:Tag)*, $tagValue as xs:string, $partial as xs:boolean) as xs:string \n" +
                    "{ \n" +
                    "   string-join ( \n" +
                    "       (for $eachTag in $tags \n" +
                    "           let $curTagValue := if (exists($eachTag/aim:TagValue/aim:StringValue)) \n" +
                    "               then ($eachTag/aim:TagValue/aim:StringValue) \n" +
                    "               else($eachTag/aim:TagValue/aim:CodedValue/@codeMeaning) \n" +
                    "        where if ($partial) then contains(lower-case($curTagValue), lower-case($tagValue)) else lower-case($curTagValue)=lower-case($tagValue) \n" +
                    "       return $curTagValue \n" +
                    "       ), ',') \n" +
                    "}; \n" +
                    "(: Returns all tag names concatenated into a single string separated by a comma :) \n" +
                    "declare function aim:getTagNamesAsString($tags as element(aim:Tag)*) as xs:string \n" +
                    "{ \n" +
                    "   aim:getTagNamesAsString($tags, ',') \n" +
                    "}; \n" +
                    "(: Returns all tag names concatenated into a single string separated by the given delimiter:) \n" +
                    "declare function aim:getTagNamesAsString($tags as element(aim:Tag)*, $delim as xs:string) as xs:string \n" +
                    "{ \n" +
                    "   string-join( \n" +
                    "       (for $eachTag in $tags \n" +
                    "           return $eachTag/aim:TagName/@codeMeaning \n" +
                    "       ), $delim) \n" +
                    "}; \n" +
                    "(: Returns the given template container metadata string or an empty string :) \n" +
                    "declare function aim:getTemplateMetadata($containerOrTemplate as element(), $metaName as xs:string) as xs:string \n" +
                    "{ \n" +
                    "   let $realMetaName := string-join(('" + MetaDataUtil.METADATA_URI_PREFIX + ":',$metaName), '') \n" +
                    "   return \n" +
                    "     typeswitch($containerOrTemplate) \n" +
                    "     case element(aim:TemplateContainer) return string(dbxml:metadata($realMetaName, $containerOrTemplate)) \n" +
                    "     case element(aim:Template) return string(dbxml:metadata($realMetaName, $containerOrTemplate/..)) \n" +
                    "     default return '' \n" +
                    "}; \n";
        }

        private static String getCommonXPathReturn(boolean includeModality) {
            StringBuilder sb = new StringBuilder();
            sb.append("return ");
            sb.append("<tr>");
            sb.append(" <td>{string($tmpName)}</td>");
            sb.append(" <td>{string($tempAuthors)}</td>");
            sb.append(" <td>{string($tempDesc)}</td>");
            sb.append(" <td>{string($disease)}</td>");
            sb.append(" <td>{string($bodyPart)}</td>");
            if (includeModality) {
                sb.append(" <td>{string($modality)}</td>");
            }
            //VK: Adding this requires UI change
//            sb.append("<td>{aim:getTagNamesAsString($allTags/aim:Tag, ', ')}</td>"); // note the space after the comma
            sb.append(" <td><a href='/templates/download?uid={string($uid)}&amp;mode=save'>download</a></td>");
            sb.append("</tr>");

            return sb.toString();
        }

        /**
         * @param includeModality
         * @return
         */
        private static String getXmlXPathReturn(boolean includeModality) {
            StringBuilder sb = new StringBuilder();
            sb.append("return ");
            sb.append("<result uid='{string($uid)}'>");
            sb.append("<name>{string($tmpName)}</name>");
            sb.append("<author>{string($tempAuthors)}</author>");
            sb.append("<desc>{string($tempDesc)}</desc>");
            sb.append("<disease>{string($disease)}</disease>");
            sb.append("<bodyPart>{string($bodyPart)}</bodyPart>");
            if (includeModality) {
                sb.append(" <modality>{string($modality)}</modality>");
            }
            sb.append("<tags>{aim:getTagNamesAsString($allTags/aim:Tag, ', ')}</tags>");
            sb.append("</result>");

            return sb.toString();
        }
    }

    private ATSQueryBuilder(Builder builder) {
        xQuerySearch = builder.createString();
    }

    public String getXQuery() {
        return xQuerySearch;
    }
}
