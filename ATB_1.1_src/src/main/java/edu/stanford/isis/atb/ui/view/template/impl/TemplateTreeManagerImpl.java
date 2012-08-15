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

package edu.stanford.isis.atb.ui.view.template.impl;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CalculationType;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.CodedTerm;
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
import edu.stanford.isis.atb.ui.model.tree.TemplateDomainConverter;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeValue;
import edu.stanford.isis.atb.ui.view.template.TemplateTreeManager;
import edu.stanford.isis.atb.ui.view.widget.tree.TemplateTree;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateTreeManagerImpl implements TemplateTreeManager {

	private TemplateTree tree;
	
	private TemplateDomainConverter converter = TemplateDomainConverter.getInstance();
	
	public TemplateTreeManagerImpl(TemplateTree tree) {
		this.tree = tree;
	}

	@Override
	public void clear() {
		tree.setModel(null);
	}

	@Override
	public void setTemplate(Template template) {
		tree.setModel(converter.template(template));
		selectRootNode();
	}

	@Override
	public void addComponent(TemplateComponent component) {
		DefaultMutableTreeNode newNode = converter.templateComponent(component);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.COMPONENT);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addQuestionType(QuestionType questionType) {
		DefaultMutableTreeNode newNode = converter.questionType(questionType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addNonQuantifiable(NonQuantifiable nonQuantifiable) {
		DefaultMutableTreeNode newNode = converter.nonQuantifiable(nonQuantifiable);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addAllowedTerm(AllowedTerm allowedTerm) {
		DefaultMutableTreeNode newNode = converter.allowedTerm(allowedTerm);
		DefaultMutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}
	
	@Override
	public void addAllowedTermWithQuantification(AllowedTermWithQuantification allowedTerm) {
		DefaultMutableTreeNode newNode = converter.allowedTermWithQuantification(allowedTerm);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}
	
	@Override
	public void addValidTerm(ValidTerm validTerm) {
		DefaultMutableTreeNode newNode = converter.validTerm(validTerm);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.VALID_TERM);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		
		// refresh currently selected node (edit conditions could change)
		tree.fireCurrentNodeSelected();
	}

	@Override
	public void addCalculationType(CalculationType calculationType) {
		DefaultMutableTreeNode newNode = converter.calculationType(calculationType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAlgorithmType(AlgorithmType algorithmType) {
		DefaultMutableTreeNode newNode = converter.algorithmType(algorithmType);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addCharacteristicQuantification(CharacteristicQuantification characteristicQuantification) {
		DefaultMutableTreeNode newNode = converter.characteristicQuantifications(characteristicQuantification);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addScale(Scale scale) {
		DefaultMutableTreeNode newNode = converter.scale(scale);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addNumerical(Numerical numerical) {
		DefaultMutableTreeNode newNode = converter.numerical(numerical);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.NUMERICAL);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addInterval(Interval interval) {
		DefaultMutableTreeNode newNode = converter.interval(interval);
		MutableTreeNode node = getSelectedNode();
		
		int index;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.INTERVAL);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addQuantile(Quantile quantile) {
		DefaultMutableTreeNode newNode = converter.quantile(quantile);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAnatomicEntity(AnatomicEntity anatomicEntity) {
		DefaultMutableTreeNode newNode = converter.anatomicEntity(anatomicEntity);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addAnatomicEntityChar(AnatomicEntityCharacteristic characteristic) {
		DefaultMutableTreeNode newNode = converter.anatomicEntityCharacteristic(characteristic);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addImagingObservation(ImagingObservation imagingObservation) {
		DefaultMutableTreeNode newNode = converter.imagingObservation(imagingObservation);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addImagingObservationChar(ImagingObservationCharacteristic characteristic) {
		DefaultMutableTreeNode newNode = converter.imagingObservationCharacteristic(characteristic);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addGeometricShape(GeometricShape geometricShape) {
		DefaultMutableTreeNode newNode = converter.geometricShape(geometricShape);
		MutableTreeNode node = getSelectedNode();
		int childCount = node.getChildCount();
		insertNode(newNode, node, childCount > 0 ? 1 : 0);
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addCalculation(Calculation calculation) {
		DefaultMutableTreeNode newNode = converter.calculation(calculation);
		MutableTreeNode node = getSelectedNode();
		int childCount = node.getChildCount();
		insertNode(newNode, node, childCount > 0 ? 1 : 0);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addInference(Inference inference) {
		DefaultMutableTreeNode newNode = converter.inference(inference);
		MutableTreeNode node = getSelectedNode();
		
		int index = 0;
		if (node.getChildCount() == 0) {
			index = 0;
		} else {
			int i = getLastIndexOfType(node, TemplateNodeType.QUESTION_TYPE);
			index = i == -1 ? 0 : i;
		}
		
		insertNode(newNode, node, index);
		scrollToNodeAndSelect(newNode);
	}

	@Override
	public void addTag(Tag tag) {
		DefaultMutableTreeNode newNode = converter.tag(tag);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void addOrdinalLevel(OrdinalLevel ordinalLevel) {
		DefaultMutableTreeNode newNode = converter.ordinalLevel(ordinalLevel);
		MutableTreeNode node = getSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(newNode);
	}
	
	@Override
	public void removeSelectedNode() {
		DefaultMutableTreeNode node = getSelectedNode(); 
		DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) node.getParent(); 
		
		if (parentNode != null) {
			removeNode(node);
			// select parent node
			tree.setSelectionPath(new TreePath(parentNode.getPath()));
		}
	}
	
	@Override
	public void removeChildNodeTermWithUserObject(CodedTerm term) {
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		DefaultMutableTreeNode currentNode = getSelectedNode();
		
		for (int i = 0; i < model.getChildCount(currentNode); i++) {
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) model.getChild(currentNode, i);
			Object value = ((TemplateNodeValue) node.getUserObject()).getValue();
			if (term.equals(value)) {
				removeNode(node);
			}
		}
	}

	@Override
	public void refreshSelectedNode() {
		((DefaultTreeModel) tree.getModel()).nodeChanged(getSelectedNode());
	}
	
	@Override
	public void selectRootNode() {
		tree.setSelectionRow(0);
	}
	
	@Override
	public void moveSelectedNodeUp() {
		moveNodeUpDown(getSelectedNode(), true);
	}

	@Override
	public void moveSelectedNodeDown() {
		moveNodeUpDown(getSelectedNode(), false);
	}
	
	@Override
	public TreeModel getTreeModel() {
		return tree.getModel();
	}

	@Override
	public void scrollToNodeAndSelect(DefaultMutableTreeNode node) {
		TreePath path = new TreePath(node.getPath());
		tree.scrollPathToVisible(path);
		tree.setSelectionPath(path);
	}
	
	private void moveNodeUpDown(DefaultMutableTreeNode node, boolean isUp) {
		DefaultMutableTreeNode parent = (DefaultMutableTreeNode) node.getParent();
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		int totalCount = model.getChildCount(parent);
		int currentIndex = model.getIndexOfChild(parent, node);
		
		// avoid indexes boundary violation
		if ((isUp && currentIndex == 0) || (!isUp && currentIndex == (totalCount - 1))) {
			return;
		}
		
		removeNode(node);
		model.insertNodeInto(node, parent, isUp ? currentIndex - 1 : currentIndex + 1);
		scrollToNodeAndSelect(node);
	}
	
	private int getLastIndexOfType(TreeNode node, TemplateNodeType type) {
		boolean found = false;
		int i;
		for (i = 0; i < node.getChildCount(); i++) {
			DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(i);
			TemplateNodeValue value = (TemplateNodeValue) child.getUserObject();
			if (value.getNodeType() == type) {
				found = true;
			} else if (found) {
				break;
			}
		}
		
		if (found) {
			return i;
		} else {
			return -1;
		}
		
	}
	
	private DefaultMutableTreeNode getSelectedNode() {
		return (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
	}
	
	private void removeNode(MutableTreeNode node) {
		((DefaultTreeModel) tree.getModel()).removeNodeFromParent(node);
	}
	
	private void insertNode(MutableTreeNode newNode, MutableTreeNode node, int index) {
		((DefaultTreeModel) tree.getModel()).insertNodeInto(newNode, node, index);
	}

}
