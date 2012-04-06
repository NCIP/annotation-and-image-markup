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


/**
 * Keeps all text (labels, messages) from UI.
 * Will be useful for possible future internationalization.
 * 
 * @author Vitaliy Semeshko
 */
public class Const {
	
	// texts
	
	public static final String TTL_APPLICATION = "Aim Template Builder";
	public static final String TTL_LEXICON_SEARCH = "Lexicon Search";
	public static final String TTL_IMPORT = "Import";
	public static final String TTL_EXPORT = "Export";
	
	public static final String TAB_TEMPLATE_GROUPS = "Template Groups";
	public static final String TAB_TEMPLATES = "Templates";
	public static final String TAB_LEXICONS = "Lexicons";
	public static final String TAB_HELP = "About/Help";
	public static final String TAB_LOCAL_LEXICON_SEARCH = "Local";
	public static final String TAB_BIOPORTAL_LEXICON_SEARCH = "Bioportal";
	
	public static final String LBL_GROUPS = "Groups";
	public static final String LBL_TEMPLATES = "Templates";
	public static final String LBL_LEXICONS = "Lexicons";
	public static final String LBL_LEXICON_TERMS = "Lexicon Terms";
	public static final String LBL_TEMPLATE_COMPONENTS = "Template Components";
	public static final String LBL_GROUP_MEMBERS = "Group Members";
	public static final String LBL_GROUP_MEMBERSHIPS = "Group Memberships";
	public static final String LBL_LEXICON_TERM = "Lexicon Term";
	public static final String LBL_ALLOWED_TERMS = "Allowed Terms";
	public static final String LBL_CURRENT_USER = "User: %s";
	public static final String LBL_UNLIMITED = "Unlimited";
	public static final String LBL_FILE = "File";
	public static final String LBL_INFORMATION = "Information";
	public static final String LBL_SELECTED_TERMS = "Selected %s terms...";
	
	public static final String BTN_SUBMIT = "Save";
	public static final String BTN_CANCEL = "Cancel";
	public static final String BTN_SELECT_TERM = "Select Term";
	public static final String BTN_OK = "OK";
	public static final String BTN_SEARCH = "Search";
	public static final String BTN_RESET = "Reset";
	public static final String BTN_LOGIN = "Login";
	public static final String BTN_WHOLE_WORD = "Whole word";
	public static final String BTN_IMPORT = "Import";
	public static final String BTN_EXPORT = "Export";
	public static final String BTN_BROWSE = "Browse...";
	
	public static final String HNT_INCLUDE_TEMPLATES = "Include Selected Templates";
	public static final String HNT_CREATE_TEMPLATE = "Create Template";
	public static final String HNT_DELETE_TEMPLATE = "Delete Template";
	public static final String HNT_COPY_TEMPLATE = "Copy Template";
	public static final String HNT_SEARCH_TEMPLATES = "Search Templates";
	public static final String HNT_CREATE_GROUP = "Add Template Container";
	public static final String HNT_DELETE_GROUP = "Delete Template Container";
	public static final String HNT_COPY_GROUP = "Copy Template Container";
	public static final String HNT_EDIT_GROUP = "Edit Template Container";
	public static final String HNT_IMPORT_EXPORT_GROUP = "Import/Export Template Container";
	public static final String HNT_IMPORT = "Import";
	public static final String HNT_EXPORT = "Export";
	public static final String HNT_IMPORT_EXPORT_LEXICON = "Import/Export Lexicon";
	public static final String HNT_SEARCH_PUBLISH_GROUP = "Search/Publish Template Container";
	public static final String HNT_SEARCH_GROUPS = "Search";
	public static final String HNT_PUBLISH_GROUP = "Publish";
	public static final String HNT_CREATE_LEXICON = "Create Lexicon";
	public static final String HNT_DELETE_LEXICON = "Delete Lexicon";
	public static final String HNT_SEARCH_TERMINOLOGY = "Search Terminology";
	public static final String HNT_ADD_TERM = "Create Lexicon Entry";
	public static final String HNT_DELETE_TERM = "Delete Lexicon Entry";
	public static final String HNT_REMOVE_TERM = "Remove Lexicon Term From The List";
	public static final String HNT_SELECT_DIRECT_CHILDREN = "Select direct children";
	public static final String HNT_SELECT_ALL_NESTED_TERMS = "Select all nested terms";
	
	public static final String HNT_EXPAND_TREE = "Expand Tree";
	public static final String HNT_COLLAPSE_TREE = "Collapse Tree";
	
	public static final String HNT_CREATE_COMPONENT = "Create Template Component";
	public static final String HNT_EDIT_COMPONENT = "Edit Template Component";
	public static final String HNT_EDIT_QST_TYPE = "Edit Question";
	public static final String HNT_DELETE_QST_TYPE = "Delete Question";
	public static final String HNT_EDIT_GEOM_SHAPE = "Edit Geometric Shape";
	public static final String HNT_DELETE_GEOM_SHAPE = "Delete Geometric Shape";
	public static final String HNT_EDIT_CALCULATION = "Edit Calculation";
	public static final String HNT_DELETE_ALLOWED_TERM = "Delete Allowed Term";
	public static final String HNT_DELETE_VALID_TERM = "Delete Valid Term";
	public static final String HNT_EDIT_ALLOWED_TERM = "Edit Allowed Term";
	public static final String HNT_DELETE_INFERENCE = "Delete Inference";
	public static final String HNT_EDIT_INFERENCE = "Edit Inference";
	public static final String HNT_CREATE_NON_QUANT = "Create Non Quantifiable";
	public static final String HNT_DELETE_NON_QUANT = "Delete Non Quantifiable";
	public static final String HNT_DELETE_AN_ENTITY = "Delete Anatomic Entity";
	public static final String HNT_CREATE_IMG_OBS_CHAR = "Create Imaging Observation Characteristic";
	public static final String HNT_DELETE_IMG_OBS = "Delete Imaging Observation";
	public static final String HNT_DELETE_IMG_OBS_CHAR = "Delete Imaging Observation Characteristic";
	public static final String HNT_EDIT_AN_ENTITY = "Edit Anatomic Entity";
	public static final String HNT_CREATE_AN_ENTITY_CHAR = "Create Anatomic Entity Characteristic";
	public static final String HNT_DELETE_AN_ENTITY_CHAR = "Delete Anatomic Entity Characteristic";
	public static final String HNT_CREATE_CHAR_QUANT = "Create Characteristic Quantification";
	public static final String HNT_DELETE_CHAR_QUANT = "Delete Characteristic Quantification";
	public static final String HNT_CREATE_CALC_TYPE = "Create Calculation Type";
	public static final String HNT_EDIT_CALC_TYPE = "Edit Calculation Type";
	public static final String HNT_DELETE_CALC_TYPE = "Delete Calculation Type";
	public static final String HNT_CREATE_ALGORITHM_TYPE = "Create Algorithm Type";
	public static final String HNT_EDIT_ALGORITHM_TYPE = "Edit Algorithm Type";
	public static final String HNT_DELETE_ALGORITHM_TYPE = "Delete Algorithm Type";
	public static final String HNT_DELETE_CALCULATION = "Delete Calculation";
	public static final String HNT_DELETE_COMPONENT = "Delete Template Component";
	public static final String HNT_CREATE_TAG = "Create Tag";
	public static final String HNT_DELETE_TAG = "Delete Tag";
	public static final String HNT_EDIT_TAG_NAME = "Edit Tag Name";
	public static final String HNT_CREATE_QST_TYPE = "Create Question";
	public static final String HNT_CREATE_AN_ENTITY = "Create Anatomic Entity";
	public static final String HNT_CREATE_IMG_OBS = "Create Imaging Observation";
	public static final String HNT_CREATE_INFERENCE = "Create Inference";
	public static final String HNT_CREATE_CALCULATION = "Create Calculation";
	public static final String HNT_CREATE_GEOM_SHAPE = "Create Geometric Shape";
	public static final String HNT_ADD_ALLOWED_TERMS = "Add Allowed Terms";
	public static final String HNT_ADD_VALID_TERMS = "Add Valid Terms";
	public static final String HNT_CREATE_SCALE = "Create Scale";
	public static final String HNT_DELETE_SCALE = "Delete Scale";
	public static final String HNT_CREATE_NUMERICAL = "Create Numerical";
	public static final String HNT_CREATE_INTERVAL = "Create Interval";
	public static final String HNT_CREATE_QUANTILE = "Create Quantile";
	public static final String HNT_CREATE_ORDINAL_LEVEL = "Create Ordinal Level";
	public static final String HNT_DELETE_ORDINAL_LEVEL = "Delete Ordinal Level";
	public static final String HNT_DELETE_NUMERICAL = "Delete Numerical";
	public static final String HNT_DELETE_INTERVAL = "Delete Interval";
	public static final String HNT_DELETE_QUANTILE = "Delete Quantile";
	public static final String HNT_MOVE_UP = "Move Up";
	public static final String HNT_MOVE_DOWN = "Move Down";
	
	public static final String FRM_LBL_UID = "UID";
	public static final String FRM_LBL_NAME = "Name";
	public static final String FRM_LBL_VERSION = "Version";
	public static final String FRM_LBL_DESCRIPTION = "Description";
	public static final String FRM_LBL_AUTHORS = "Authors";
	public static final String FRM_LBL_DATE = "Date";
	public static final String FRM_LBL_BODY_PART = "Body Part";
	public static final String FRM_LBL_DISEASE = "Disease";
	public static final String FRM_LBL_MODALITY = "Modality";
	public static final String FRM_LBL_LABEL = "Label";
	public static final String FRM_LBL_CARDINALITY = "Cardinality";
	public static final String FRM_LBL_ITEM_NUMBER = "Item Number";
	public static final String FRM_LBL_SHOULD_DISPLAY = "Should Display";
	public static final String FRM_LBL_EXPLANATORY_TEXT = "Explanatory Text";
	public static final String FRM_LBL_GROUP_LABEL = "Group Label";
	public static final String FRM_LBL_GROUP = "Group";
	public static final String FRM_LBL_ANNOTATOR_CONFIDENCE = "Annotator Confidence";
	public static final String FRM_LBL_SHAPE_TYPE = "Shape Type";
	public static final String FRM_LBL_UNIQUE_IDENTIFIER = "Unique Identifier";
	public static final String FRM_LBL_ALGORITHM_NAME = "Algorithm Name";
	public static final String FRM_LBL_ALGORITHM_VERSION = "Algorithm Version";
	public static final String FRM_LBL_MATH_ML = "Math ML";
	public static final String FRM_LBL_TAG_NAME = "Tag Name";
	public static final String FRM_LBL_TAG_VALUE = "Tag Value";
	public static final String FRM_LBL_VALUE = "Value";
	public static final String FRM_LBL_STRING_VALUE = "String Value";
	public static final String FRM_LBL_USE_STRING_VALUE = "Use String Value";
	public static final String FRM_LBL_USE_LEXICON_TERM = "Use Lexicon Term";
	public static final String FRM_LBL_SCHEMA_DESIGNATOR = "Schema Designator";
	public static final String FRM_LBL_SCHEMA_VERSION = "Schema Version";
	public static final String FRM_LBL_IS_READ_ONLY = "Is Read-only";
	public static final String FRM_LBL_CREATION_DATE = "Created";
	public static final String FRM_LBL_MODIFICATION_DATE = "Modified";
	public static final String FRM_LBL_CODE_MEANING = "Code Meaning";
	public static final String FRM_LBL_CODE_VALUE = "Code Value";
	public static final String FRM_LBL_COMMENT = "Comment";
	public static final String FRM_LBL_OPERATOR = "Operator";
	public static final String FRM_LBL_UCUM_STRING = "UCUM String";
	public static final String FRM_LBL_MIN_VALUE = "Min Value";
	public static final String FRM_LBL_MAX_VALUE = "Max Value";
	public static final String FRM_LBL_MIN_OPERATOR = "Min Operator";
	public static final String FRM_LBL_MAX_OPERATOR = "Max Operator";
	public static final String FRM_LBL_BINS = "Bins";
	public static final String FRM_LBL_TEMPLATE_NAME = "Template Name";
	public static final String FRM_LBL_TEMPLATE_CODE_DESC = "Template Code Desc";
	public static final String FRM_LBL_TEMPLATE_DESCRIPTION = "Template Description";
	public static final String FRM_LBL_TEMPLATE_AUTHOR = "Template Author";
	public static final String FRM_LBL_USERNAME = "Username";
	public static final String FRM_LBL_PASSWORD = "Password";
	public static final String FRM_LBL_CONTAINER_NAME = "Container Name";
	public static final String FRM_LBL_CONTAINER_DESCRIPTION = "Container Description";
	public static final String FRM_LBL_CONTAINER_AUTHOR = "Container Author";
	public static final String FRM_LBL_LEXICON_TERM = "Lexicon Term";
	public static final String FRM_LBL_PRECEDING_ANNOTATION = "Preceding Annotation";
	
	public static final String TXT_NAME = "Name";
	public static final String TXT_VALUE = "Value";
	public static final String TXT_FORM_NO_ATTRIBUTES = "No attributes to edit";
	public static final String TXT_AUTHENTICATION_FAILED = "Authentication Failed";
	public static final String TXT_COPY_OF = "Copy Of";
	public static final String TXT_INFINITY = "\u221E";
	
	public static final String COLUMN_NAME = "Name";
	public static final String COLUMN_DATE = "Date";
	public static final String COLUMN_VERSION = "Version";
	public static final String COLUMN_CODE_MEANING = "Code Meaning";
	public static final String COLUMN_AUTH = "Auth";
	public static final String COLUMN_AUTHORS = "Authors";
	public static final String COLUMN_DESCRIPTION = "Description";
	public static final String COLUMN_LEXICON = "Lexicon";
	public static final String COLUMN_VALUE = "Value";
	public static final String COLUMN_MEANING = "Meaning";
	public static final String COLUMN_DISEASE = "Disease";
	public static final String COLUMN_BODY_PART = "Body Part";
	public static final String COLUMN_MODALITY = "Modality";
	public static final String COLUMN_UID = "UID";
	public static final String COLUMN_TERM_COUNT = "Term Count";
	public static final String COLUMN_ELEMENT = "Element";
	
	public static final String MSG_CANT_CONNECT_TO_DB = "Can't connect to database.\nIf there is another application running, please close it and try again.";
	public static final String MSG_NO_CONTAINER_SELECTED = "No template container selected";
	public static final String MSG_NO_TEMPLATE_SELECTED = "No template selected";
	public static final String MSG_NO_LEXICON_SELECTED = "No lexicon selected";
	public static final String MSG_LEXICON_IS_EMPTY = "Lexicon is empty";
	public static final String MSG_LEXICON_IS_NOT_ALLOWED_FOR_EXPORT = "Lexicon is not allowed for the export";
	public static final String MSG_LEXICON_IS_READONLY = "This Lexicon is Read-Only.";
	public static final String MSG_WRONG_FIELD_VALUE = "Incorrect value in field \"%s\"";
	public static final String MSG_CONTAINER_EXPORTED = "Template Container \"%s\" successfully exported";
	public static final String MSG_CONTAINER_EXPORT_FAILED = "Template Container \"%s\" export failed.";
	public static final String MSG_CONTAINER_IMPORTED = "Template Container \"%s\" successfully imported";
	public static final String MSG_TEMPLATE_IMPORTED = "Template \"%s\" successfully imported";
	public static final String MSG_CONTAINER_IMPORT_FAILED = "Template Container import failed.";
	public static final String MSG_EMPTY_SEARCH_TEXT = "No search text specified";
	public static final String MSG_SHORT_SEARCH_TEXT = "Search text is too short";
	public static final String MSG_NO_LEXICON_SELECTED_FOR_SEARCH = "No Lexicon selected";
	public static final String MSG_LEXICON_EXPORT_FAILED = "Lexicon \"%s\" export failed.";
	public static final String MSG_LEXICON_IMPORT_FAILED = "Lexicon import failed.";
	public static final String MSG_LEXICON_EXPORTED = "Lexicon \"%s\" successfully exported";
	public static final String MSG_LEXICON_IMPORTED = "Lexicon \"%s\" successfully imported";
	public static final String MSG_TERM_ALREADY_SELECTED = "Term '%s' has been already selected.";
	public static final String MSG_CONTAINER_PUBLISHED = "Template Container \"%s\" successfully published.";
	public static final String MSG_CONTAINER_IS_EMPTY = "Template Container is empty";
	public static final String MSG_CONTAINER_IS_INCORRECT = "Template Container is not correct.\nPlease fix warnings previously";
	public static final String MSG_TEMPLATE_COPIED = "Template Copy created: '%s'";
	public static final String MSG_CONTAINER_COPIED = "Template Container copy created: '%s'";
	public static final String MSG_INVALID_TEMPLATE = "Invalid AIM Template";
	public static final String MSG_ERROR = "Error happened...";
	public static final String MSG_OPERATION_INTERRUPTED = "Operation interrupted...";
	public static final String MSG_OPERATION_FINISHED = "Operation finished";
	public static final String MSG_OPERATION_FAILED = "Operation failed";
	public static final String MSG_EXPORTED_TERMS = "Exported %d Term(s)";
	public static final String MSG_IMPORTED_TERMS = "Imported %d Term(s)";
	public static final String MSG_INCORRECT_FILE_LOCATION = "File location is incorrect: '%s'";
	
	public static final String DLG_TITLE_INFORMATION = "Information";
	public static final String DLG_TITLE_ERROR = "Error";
	public static final String DLG_TITLE_CONFIRMATION = "Confirmation";
	public static final String DLG_TITLE_VALIDATION_ERROR = "Validation Error";
	
	public static final String QST_DELETE_GROUP = "Are you sure you want to delete this Template Container?";
	public static final String QST_DELETE_TEMPLATE = "Are you sure you want to delete this Template?";
	public static final String QST_DELETE_LEXICON = "Are you sure you want to delete this Lexicon?";
	
	public static final String EMPTY = "";
	
	// formats
	
	public static final String FMT_DATE_DISPLAY = "yyyy-MM-dd";
	public static final String FMT_TIME_DATE_DISPLAY = "hh:mm yyyy-MM-dd";
	public static final String FMT_DATE_TIME_WITH_SECONDS = "yyyy-MM-dd hh:mm:ss";
	
	// templates
	
	public static final String TPL_FORM_LABEL = "%s  :";
	public static final String TPL_FORM_LABEL_MANDATORY = "<html>%s<font color=red>*</font> :</html>";
	
	// defaults
	
	public static final String DEF_CODE_MEANING = "New Lexicon Entry";
	public static final String DEF_CODE_VALUE = "";
	
	// extensions
	
	public static final String EXT_XML = "xml";
	public static final String EXT_XML_TEXT = "XML-files (*.xml)";
	public static final String EXT_CSV = "csv";
	public static final String EXT_CSV_TEXT = "CSV-files (*.csv)";
	
	// resource separator (platform-independent)
	
	public static final String R_SEP = "/";

}
