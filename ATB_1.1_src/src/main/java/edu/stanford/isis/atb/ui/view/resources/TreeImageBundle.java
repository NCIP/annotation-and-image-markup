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
 * Image bundle for tree.
 * 
 * @author Vitaliy Semeshko
 */
public class TreeImageBundle {

	private static TreeImageBundle instance = new TreeImageBundle();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private TreeImageBundle() {}
	
	public static TreeImageBundle getInstance() {
		return instance;
	}
	
	private static final String ROOT_TREE_DIR = "etc/images/tree/";
	
	private static final String TEMPLATE = ROOT_TREE_DIR + "template.png";
	
	public LazyIcon getTemplateIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(TEMPLATE));
	}
	
	private static final String COMPONENT = ROOT_TREE_DIR + "component.png";  
	
	public LazyIcon getComponentIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(COMPONENT));
	}
	
	private static final String CALCULATION = ROOT_TREE_DIR + "calculation.png";
	
	public LazyIcon getCalculationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CALCULATION));
	}
	
	private static final String SHAPE = ROOT_TREE_DIR + "shape.png";
	
	public LazyIcon getShapeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SHAPE));
	}
	
	private static final String ANATOMIC_ENTITY = ROOT_TREE_DIR + "anatomic_entity.png";
	
	public LazyIcon getAnatomicEntityIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ANATOMIC_ENTITY));
	}
	
	private static final String ANATOMIC_ENTITY_CHAR = ROOT_TREE_DIR + "anatomic_entity_char.png";
	
	public LazyIcon getAnatomicEntityCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ANATOMIC_ENTITY_CHAR));
	}
	
	private static final String INFERENCE = ROOT_TREE_DIR + "inference.png";
	
	public LazyIcon getInferenceIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(INFERENCE));
	}
	
	private static final String IMAGING_OBSERVATION = ROOT_TREE_DIR + "imaging_observation.png";
	
	public LazyIcon getImagingObservationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMAGING_OBSERVATION));
	}
	
	private static final String IMAGING_OBSERVATION_CHAR = ROOT_TREE_DIR + "imaging_observation_char.png";
	
	public LazyIcon getImagingObservationCharIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(IMAGING_OBSERVATION_CHAR));
	}
	
	private static final String EMPTY = ROOT_TREE_DIR + "empty.png";
	
	public LazyIcon getEmptyIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(EMPTY));
	}
	
	private static final String QUESTION_TYPE = ROOT_TREE_DIR + "question_type.png";
	
	public LazyIcon getQuestionTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(QUESTION_TYPE));
	}
	
	private static final String ALLOWED_TERM = ROOT_TREE_DIR + "allowed_term.png";
	
	public LazyIcon getAllowedTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ALLOWED_TERM));
	}
	
	private static final String VALID_TERM = ROOT_TREE_DIR + "valid_term.png";
	
	public LazyIcon getValidTermIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(VALID_TERM));
	}
	
	private static final String TAG = ROOT_TREE_DIR + "tag.png";
	
	public LazyIcon getTagIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(TAG));
	}
	
	private static final String INTERVAL = ROOT_TREE_DIR + "interval.png";
	
	public LazyIcon getIntervalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(INTERVAL));
	}
	
	private static final String CALC_TYPE = ROOT_TREE_DIR + "calculation_type.png";
	
	public LazyIcon getCalcTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CALC_TYPE));
	}
	
	private static final String ALGORITHM_TYPE = ROOT_TREE_DIR + "algorithm_type.png";
	
	public LazyIcon getAlgorithmTypeIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ALGORITHM_TYPE));
	}
	
	private static final String NON_QUANTIFIABLE = ROOT_TREE_DIR + "non_quantifiable.png";
	
	public LazyIcon getNonQuantifiableIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(NON_QUANTIFIABLE));
	}
	
	private static final String CHAR_QUANT = ROOT_TREE_DIR + "characteristic_quantification.png";
	
	public LazyIcon getCharacteristicQuantificationIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(CHAR_QUANT));
	}
	
	private static final String SCALE = ROOT_TREE_DIR + "scale.png";
	
	public LazyIcon getScaleIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(SCALE));
	}
	
	private static final String ORDINAL_LEVEL = ROOT_TREE_DIR + "ordinal_level.png";
	
	public LazyIcon getOrdinalLevelIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(ORDINAL_LEVEL));
	}
	
	private static final String NUMERICAL = ROOT_TREE_DIR + "numerical.png";
	
	public LazyIcon getNumericalIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(NUMERICAL));
	}
	
	private static final String QUANTILE = ROOT_TREE_DIR + "quantile.png";
	
	public LazyIcon getQuantileIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(QUANTILE));
	}
	
	// Lexicons
	
	private static final String LEXICON = ROOT_TREE_DIR + "lexicon.png";
	
	public LazyIcon getLexiconIcon() {
		return new DefaultLazyIcon(resourceManager.getResourceURL(LEXICON));
	}
	
}
