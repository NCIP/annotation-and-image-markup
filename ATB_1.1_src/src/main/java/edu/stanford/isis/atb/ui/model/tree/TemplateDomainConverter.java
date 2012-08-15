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

package edu.stanford.isis.atb.ui.model.tree;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CalculationType;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.ImagingObservation;
import edu.stanford.isis.atb.domain.template.ImagingObservationCharacteristic;
import edu.stanford.isis.atb.domain.template.Inference;
import edu.stanford.isis.atb.domain.template.Interval;
import edu.stanford.isis.atb.domain.template.NonQuantifiable;
import edu.stanford.isis.atb.domain.template.Numerical;
import edu.stanford.isis.atb.domain.template.OrdinalLevel;
import edu.stanford.isis.atb.domain.template.Quantile;
import edu.stanford.isis.atb.domain.template.QuestionType;
import edu.stanford.isis.atb.domain.template.Scale;
import edu.stanford.isis.atb.domain.template.Tag;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateComponent;
import edu.stanford.isis.atb.domain.template.ValidTerm;

/**
 * Provides methods to convert domain object that can be presented as tree nodes.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateDomainConverter {

	private static final TemplateDomainConverter instance = new TemplateDomainConverter();
	
	private TemplateDomainConverter() {}
	
	public static TemplateDomainConverter getInstance() {
		return instance;
	}
	
	/**
	 * Convert domain model to {@link TreeModel}.
	 * 
	 * @param t domain model to be converted.
	 * @return implementation of {@link TreeModel}
	 */
	public TreeModel template(Template t) {
		DefaultMutableTreeNode root = createNode(TemplateNodeType.TEMPLATE, t);
		
		for (TemplateComponent component : t.getComponents()) {
			root.add(templateComponent(component));
		}
		
		for (Tag tag : t.getTags()) {
			root.add(tag(tag));
		}
		
		return new DefaultTreeModel(root);
	}
	
	public DefaultMutableTreeNode tag(Tag value) {
		return createNode(TemplateNodeType.TAG, value);
	}
	
	public DefaultMutableTreeNode templateComponent(TemplateComponent value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.COMPONENT, value);
		
		QuestionType questionType = value.getQuestionType();
		if (questionType != null) {
			node.add(questionType(questionType));
		}
		
		Object content = value.getContent();
		if (content != null) {
			if (content instanceof AnatomicEntity) {
				node.add(anatomicEntity((AnatomicEntity) content));
			} else if (content instanceof ImagingObservation) {
				node.add(imagingObservation((ImagingObservation) content));
			} else if (content instanceof Inference) {
				node.add(inference((Inference) content));
			} else if (content instanceof GeometricShape) {
				node.add(geometricShape((GeometricShape) content));
			} else if (content instanceof Calculation) {
				node.add(calculation((Calculation) content));
			}
		}
		
		for (AllowedTerm at : value.getAllowedTerms()) {
			node.add(allowedTerm(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode questionType(QuestionType value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.QUESTION_TYPE, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode calculation(Calculation value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CALCULATION, value);
		
		for (CalculationType ct : value.getCalculationType()) {
			node.add(calculationType(ct));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode calculationType(CalculationType value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CALCULATION_TYPE, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		for (AlgorithmType at : value.getAlgorithmTypes()) {
			node.add(algorithmType(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode algorithmType(AlgorithmType value) {
		return createNode(TemplateNodeType.ALGORITHM_TYPE, value);
	}
	
	public DefaultMutableTreeNode anatomicEntity(AnatomicEntity value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ANATOMIC_ENTITY, value);
		
		for (AnatomicEntityCharacteristic aec : value.getCharacteristics()) {
			node.add(anatomicEntityCharacteristic(aec));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode imagingObservation(ImagingObservation value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.IMAGING_OBSERVATION, value);
		
		for (ImagingObservationCharacteristic ioc : value.getCharacteristics()) {
			node.add(imagingObservationCharacteristic(ioc));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode inference(Inference value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.INFERENCE, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode geometricShape(GeometricShape value) {
		return createNode(TemplateNodeType.GEOMETRIC_SHAPE, value);
	}
	
	public DefaultMutableTreeNode anatomicEntityCharacteristic(AnatomicEntityCharacteristic value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		for (AllowedTermWithQuantification at : value.getAllowedTerms()) {
			node.add(allowedTermWithQuantification(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode imagingObservationCharacteristic(ImagingObservationCharacteristic value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC, value);
		
		QuestionType qt = value.getQuestionType();
		if (qt != null) {
			node.add(questionType(qt));
		}
		
		for (AllowedTermWithQuantification at : value.getAllowedTerms()) {
			node.add(allowedTermWithQuantification(at));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode validTerm(ValidTerm value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.VALID_TERM, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode allowedTerm(AllowedTerm value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ALLOWED_TERM, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}

		for (NonQuantifiable nq : value.getNonQuantifiables()) {
			node.add(nonQuantifiable(nq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode allowedTermWithQuantification(AllowedTermWithQuantification value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION, value);
		
		for (ValidTerm vt : value.getValidTerms()) {
			node.add(validTerm(vt));
		}
		
		CharacteristicQuantification cq = value.getCharacteristicQuantification();
		if (cq != null) {
			node.add(characteristicQuantifications(cq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode nonQuantifiable(NonQuantifiable value) {
		return createNode(TemplateNodeType.NON_QUANTIFIABLE, value);
	}
	
	public DefaultMutableTreeNode characteristicQuantifications(CharacteristicQuantification value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.CHARACTERISTIC_QUANTIFICATION, value);
		
		Scale scale = value.getScale();
		if (scale != null) {
			node.add(scale(scale));
		}
		
		for (Numerical nm : value.getNumericals()) {
			node.add(numerical(nm));
		}
		
		for (Interval iv : value.getIntervals()) {
			node.add(interval(iv));
		}
		
		Quantile qt = value.getQuantile();
		if (qt != null) {
			node.add(quantile(qt));
		}
		
		for (NonQuantifiable nq : value.getNonQuantifiables()) {
			node.add(nonQuantifiable(nq));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode scale(Scale value) {
		DefaultMutableTreeNode node = createNode(TemplateNodeType.SCALE, value);
		
		for (OrdinalLevel ol : value.getOrdinalLevels()) {
			node.add(ordinalLevel(ol));
		}
		
		return node;
	}
	
	public DefaultMutableTreeNode ordinalLevel(OrdinalLevel value) {
		return createNode(TemplateNodeType.ORDINAL_LEVEL, value);
	}
	
	public DefaultMutableTreeNode numerical(Numerical value) {
		return createNode(TemplateNodeType.NUMERICAL, value);
	}
	
	public DefaultMutableTreeNode interval(Interval value) {
		return createNode(TemplateNodeType.INTERVAL, value);
	}
	
	public DefaultMutableTreeNode quantile(Quantile value) {
		return createNode(TemplateNodeType.QUANTILE, value);
	}
	
	private DefaultMutableTreeNode createNode(TemplateNodeType type, Object userObject) {
		return new DefaultMutableTreeNode(new TemplateNodeValue(type, userObject));
	}
	
}
