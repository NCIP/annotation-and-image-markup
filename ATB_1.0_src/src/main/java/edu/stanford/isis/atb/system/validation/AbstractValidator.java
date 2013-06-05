/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.validation;

import java.lang.annotation.Annotation;
import java.lang.annotation.ElementType;
import java.lang.reflect.Field;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import javax.validation.Configuration;
import javax.validation.ConstraintViolation;
import javax.validation.MessageInterpolator;
import javax.validation.Path;
import javax.validation.Path.Node;
import javax.validation.TraversableResolver;
import javax.validation.Validation;
import javax.validation.Validator;
import javax.validation.ValidatorFactory;

import org.apache.commons.collections.CollectionUtils;
import org.hibernate.validator.messageinterpolation.ResourceBundleMessageInterpolator;
import org.hibernate.validator.resourceloading.PlatformResourceBundleLocator;

import edu.stanford.isis.atb.system.util.ReflectionUtils;

/**
 * @author Vitaliy Semeshko
 */
public class AbstractValidator {

	private static final String VALIDATION_MESSAGES = "etc.validation.ValidationMessages";
	
	private final MessageInterpolator messageInterpolator = new ResourceBundleMessageInterpolator(
			new PlatformResourceBundleLocator(VALIDATION_MESSAGES));
	
	private Validator validator;
	
	private Validator graphValidator;

	public AbstractValidator() {
		Configuration<?> configuration = Validation.byDefaultProvider().configure();
		ValidatorFactory validationFactory = configuration.traversableResolver(new TraversableResolver() {

			@Override
			public boolean isReachable(Object traversableObject, Node traversableProperty, Class<?> rootBeanType,
					Path pathToTraversableObject, ElementType elementType) {
				// allow access properties
				return true;
			}

			@Override
			public boolean isCascadable(Object traversableObject, Node traversableProperty, Class<?> rootBeanType,
					Path pathToTraversableObject, ElementType elementType) {
				// prohibit graph validation unless marked with {@link ForceGraphValidation}
				
				Field field = ReflectionUtils.findField(traversableObject.getClass(), traversableProperty.getName());
				
				if (field != null) {
					Annotation[] annotations = field.getDeclaredAnnotations();
					for (Annotation annotation : annotations) {
						if (annotation.annotationType().equals(ForceGraphValidation.class)) {
							return true;
						}
					}
				}
				
				return false;
			}
			
		}).messageInterpolator(messageInterpolator).buildValidatorFactory();

		validator = validationFactory.getValidator();
		
		Configuration<?> graphConfiguration = Validation.byDefaultProvider().configure();
		ValidatorFactory graphValidationfactory = graphConfiguration
				.messageInterpolator(messageInterpolator).buildValidatorFactory();
		graphValidator = graphValidationfactory.getValidator();
	}
	
	public Set<ValidationError> validate(Object element) {
		return validate(validator, element);
	}
	
	public Set<ValidationError> validateGraph(Object element) {
		return validate(graphValidator, element);
	}
	
	private Set<ValidationError> validate(Validator validator, Object element) {
		Set<ConstraintViolation<Object>> violations = validator.validate(element);
		if (CollectionUtils.isNotEmpty(violations)) {
			Set<ValidationError> errors = new HashSet<ValidationError>();
			for (ConstraintViolation<Object> violation : violations) {
				errors.add(new ValidationError(violation.getMessage()));
			}
			return errors;
		} else {
			return Collections.emptySet();
		}
	}
	
}
