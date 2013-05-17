/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView.GeometricShapeFormField.SHAPE_TYPE;
import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.GeometricShapeType;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView;

/**
 * @author Vitaliy Semeshko
 */
public class GeometricShapeFormPresenter extends AbstractFormPresenter<GeometricShape, GeometricShapeFormView> {

	public GeometricShapeFormPresenter(GeometricShapeFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(GeometricShape value) {
		this.value = value;
		view.setFieldValue(SHAPE_TYPE, value.getValue());
	}

	@Override
	protected boolean validate() {
		Object shapeType = view.getFieldValue(SHAPE_TYPE);
		if (shapeType != null && shapeType instanceof GeometricShapeType) {
			value.setValue((GeometricShapeType) shapeType);
		} else {
			value.setValue(null);
		}
		
		return true;
	}
	
}
