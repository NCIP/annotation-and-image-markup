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

package edu.stanford.isis.atb.ui.view.resources;

import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.view.resources.image.DefaultLazyIcon;
import edu.stanford.isis.atb.ui.view.resources.image.LazyIcon;

/**
 * Image bundle for toolbar.
 * 
 * @author Vitaliy Semeshko
 */
public class ToolBarImageBundle {

	private static ToolBarImageBundle instance = new ToolBarImageBundle();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private ToolBarImageBundle() {}
	
	public static ToolBarImageBundle getInstance() {
		return instance;
	}
	
	private static final String ROOT_TOOLBAR_DIR = "etc/images/toolbar/";
	
	// templates
	
	private static final String COPY_TEMPLATE = ROOT_TOOLBAR_DIR + "copy_template.png";
	
	public LazyIcon getCopyTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COPY_TEMPLATE));
	}
	
	private static final String SEARCH_TEMPLATES = ROOT_TOOLBAR_DIR + "search_templates.png";
	
	public LazyIcon getSearchTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_TEMPLATES));
	}
	
	private static final String CREATE_COMPONENT = ROOT_TOOLBAR_DIR + "create_component.png";
	
	public LazyIcon getCreateComponentIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_COMPONENT));
	}
	
	private static final String CREATE_CALCULATION = ROOT_TOOLBAR_DIR + "create_calculation.png";
	
	public LazyIcon getCreateCalculationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CALCULATION));
	}
	
	private static final String CREATE_SHAPE = ROOT_TOOLBAR_DIR + "create_shape.png";
	
	public LazyIcon getCreateShapeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_SHAPE));
	}
	
	private static final String CREATE_ANATOMIC_ENTITY = ROOT_TOOLBAR_DIR + "create_anatomic_entity.png";
	
	public LazyIcon getCreateAnatomicEntityIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ANATOMIC_ENTITY));
	}
	
	private static final String CREATE_INFERENCE = ROOT_TOOLBAR_DIR + "create_inference.png";
	
	public LazyIcon getCreateInferenceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_INFERENCE));
	}
	
	private static final String CREATE_IMAGE_OBSERVATION = ROOT_TOOLBAR_DIR + "create_image_observation.png";
	
	public LazyIcon getCreateImageObservationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_IMAGE_OBSERVATION));
	}
	
	private static final String CREATE_IMAGE_OBSERVATION_CHAR = ROOT_TOOLBAR_DIR + 
			"create_image_observation_characteristic.png";
	
	public LazyIcon getCreateImageObservationCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_IMAGE_OBSERVATION_CHAR));
	}
	
	private static final String CREATE_TAG = ROOT_TOOLBAR_DIR + "create_tag.png";
	
	public LazyIcon getCreateTagIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_TAG));
	}
	
	private static final String CREATE_QUESTION_TYPE = ROOT_TOOLBAR_DIR + "create_question_type.png";
	
	public LazyIcon getCreateQuestionTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_QUESTION_TYPE));
	}
	
	private static final String CREATE_ALLOWED_TERM = ROOT_TOOLBAR_DIR + "create_allowed_term.png";
	
	public LazyIcon getCreateAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ALLOWED_TERM));
	}
	
	private static final String CREATE_VALID_TERM = ROOT_TOOLBAR_DIR + "create_valid_term.png";
	
	public LazyIcon getCreateValidTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_VALID_TERM));
	}
	
	private static final String CREATE_CALC_TYPE = ROOT_TOOLBAR_DIR + "create_calculation_type.png";
	
	public LazyIcon getCreateCalcTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CALC_TYPE));
	}
	
	private static final String CREATE_ALGORITHM_TYPE = ROOT_TOOLBAR_DIR + "create_algorithm_type.png";
	
	public LazyIcon getCreateAlgorithmTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ALGORITHM_TYPE));
	}
	
	private static final String CREATE_ANATOMIC_ENTITY_CHAR = ROOT_TOOLBAR_DIR + 
			"create_anatomic_entity_characteristic.png";
	
	public LazyIcon getCreateAnatomicEntityCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ANATOMIC_ENTITY_CHAR));
	}
	
	private static final String CREATE_NON_QUANTIFIABLE = ROOT_TOOLBAR_DIR + "create_non_quantifiable.png";
	
	public LazyIcon getCreateNonQuantifiableIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_NON_QUANTIFIABLE));
	}
	
	private static final String CREATE_CHAR_QUANT = ROOT_TOOLBAR_DIR + "create_characteristic_quantification.png";
	
	public LazyIcon getCreateCharacteristicQuantificationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_CHAR_QUANT));
	}
	
	private static final String CREATE_SCALE = ROOT_TOOLBAR_DIR + "create_scale.png";
	
	public LazyIcon getCreateScaleIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_SCALE));
	}
	
	private static final String CREATE_ORDINAL_LEVEL = ROOT_TOOLBAR_DIR + "create_ordinal_level.png";
	
	public LazyIcon getCreateOrdinalLevelIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_ORDINAL_LEVEL));
	}
	
	private static final String CREATE_NUMERICAL = ROOT_TOOLBAR_DIR + "create_numerical.png";
	
	public LazyIcon getCreateNumericalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_NUMERICAL));
	}
	
	private static final String CREATE_INTERVAL = ROOT_TOOLBAR_DIR + "create_interval.png";
	
	public LazyIcon getCreateIntervalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_INTERVAL));
	}
	
	private static final String CREATE_QUANTILE = ROOT_TOOLBAR_DIR + "create_quantile.png";
	
	public LazyIcon getCreateQuantileIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE_QUANTILE));
	}
	
	// groups
	
	private static final String COPY_GROUP = ROOT_TOOLBAR_DIR + "copy_group.png";
	
	public LazyIcon getCopyGroupIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COPY_GROUP));
	}
	
	private static final String LINK_TEMPLATES = ROOT_TOOLBAR_DIR + "link_templates.png";
	
	public LazyIcon getLinkTemplatesIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(LINK_TEMPLATES));
	}
	
	private static final String SEARCH_GROUPS = ROOT_TOOLBAR_DIR + "search_groups.png";
	
	public LazyIcon getSearchGroupsIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_GROUPS));
	}
	
	private static final String IMPORT_EXPORT = ROOT_TOOLBAR_DIR + "import_export.png";
	
	public LazyIcon getImportExportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMPORT_EXPORT));
	}
	
	private static final String IMPORT = ROOT_TOOLBAR_DIR + "import.png";
	
	public LazyIcon getImportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMPORT));
	}
	
	private static final String EXPORT = ROOT_TOOLBAR_DIR + "export.png";
	
	public LazyIcon getExportIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EXPORT));
	}
	
	private static final String REMOTE_SERVICE = ROOT_TOOLBAR_DIR + "remote_service.png";
	
	public LazyIcon getRemoteServiceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(REMOTE_SERVICE));
	}
	
	private static final String PUBLISH = ROOT_TOOLBAR_DIR + "publish.png";
	
	public LazyIcon getPublishIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(PUBLISH));
	}

	// lexicons
	
	private static final String USE_ALLOWED_TERM = ROOT_TOOLBAR_DIR + "use_allowed_term.png";
	
	public LazyIcon getUseAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(USE_ALLOWED_TERM));
	}
	
	private static final String SEARCH_LEXICONS = ROOT_TOOLBAR_DIR + "search_lexicons.png";
	
	public LazyIcon getSearchLexiconsIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SEARCH_LEXICONS));
	}
	
	// misc
	
	private static final String CREATE = ROOT_TOOLBAR_DIR + "create.png";
	
	public LazyIcon getCreateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CREATE));
	}
	
	private static final String EDIT = ROOT_TOOLBAR_DIR + "edit.png";
	
	public LazyIcon getEditIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EDIT));
	}
	
	private static final String DELETE = ROOT_TOOLBAR_DIR + "delete.png";
	
	public LazyIcon getDeleteIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(DELETE));
	}
	
	private static final String MOVE_UP = ROOT_TOOLBAR_DIR + "move_up.png";
	
	public LazyIcon getMoveUpIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(MOVE_UP));
	}
	
	private static final String MOVE_DOWN = ROOT_TOOLBAR_DIR + "move_down.png";
	
	public LazyIcon getMoveDownIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(MOVE_DOWN));
	}
	
}
