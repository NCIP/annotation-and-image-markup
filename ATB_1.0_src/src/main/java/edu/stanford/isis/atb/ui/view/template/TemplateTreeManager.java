/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeModel;

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

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateTreeManager {

	public void clear();
	
	public void setTemplate(Template template);
	
	public void addComponent(TemplateComponent component);
	
	public void addQuestionType(QuestionType questionType);
	
	public void addAnatomicEntity(AnatomicEntity anatomicEntity);
	
	public void addAnatomicEntityChar(AnatomicEntityCharacteristic characteristic);
	
	public void addImagingObservation(ImagingObservation imagingObservation);
	
	public void addImagingObservationChar(ImagingObservationCharacteristic characteristic);
	
	public void addGeometricShape(GeometricShape geometricShape);
	
	public void addCalculation(Calculation calculation);
	
	public void addNonQuantifiable(NonQuantifiable nonQuantifiable);
	
	public void addAllowedTerm(AllowedTerm allowedTerm);
	
	public void addAllowedTermWithQuantification(AllowedTermWithQuantification allowedTerm);
	
	public void addValidTerm(ValidTerm validTerm);
	
	public void addCalculationType(CalculationType calculationType);
	
	public void addAlgorithmType(AlgorithmType algorithmType);
	
	public void addCharacteristicQuantification(CharacteristicQuantification characteristicQuantification);
	
	public void addScale(Scale scale);
	
	public void addNumerical(Numerical numerical);

	public void addInterval(Interval interval);
	
	public void addQuantile(Quantile quantile);
	
	public void addInference(Inference inference);
	
	public void addTag(Tag tag);
	
	public void addOrdinalLevel(OrdinalLevel ordinalLevel);
	
	public void removeSelectedNode();
	
	public void removeChildNodeTermWithUserObject(CodedTerm term);
	
	public void refreshSelectedNode();
	
	public void selectRootNode();
	
	public void moveSelectedNodeUp();
	
	public void moveSelectedNodeDown();
	
	public TreeModel getTreeModel();
	
	public void scrollToNodeAndSelect(DefaultMutableTreeNode node);
	
}
