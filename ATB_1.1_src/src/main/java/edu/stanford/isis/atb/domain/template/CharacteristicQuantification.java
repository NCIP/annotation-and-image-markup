/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.validation.Valid;

import org.apache.commons.lang3.StringUtils;
import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="CharacteristicQuantification", strict=false)
public class CharacteristicQuantification extends AbstractRemovableElement {

	@NotEmpty(message = "{characteristicQuantification.name.notEmpty}")
	@Attribute(required=false)
	private String name;
	
	@Attribute(required=false)
	private boolean annotatorConfidence;

	@Valid
	@Element(name="Scale", required=false)
	private Scale scale;
	
	@Valid
	@Element(name="Quantile", required=false)
	private Quantile quantile;
	
	@Valid
	@ElementList(name="Numerical", inline=true, required=false)
	private List<Numerical> numericals;
	
	@Valid
	@ElementList(name="Interval", inline=true, required=false)
	private List<Interval> intervals;
	
	@Valid
	@ElementList(name="NonQuantifiable", inline=true, required=false)
	private List<NonQuantifiable> nonQuantifiables;
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public boolean isAnnotatorConfidence() {
		return annotatorConfidence;
	}

	public void setAnnotatorConfidence(boolean annotatorConfidence) {
		this.annotatorConfidence = annotatorConfidence;
	}
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (scale != null) {
			scale.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					CharacteristicQuantification.this.scale = null;
				}
			});
		}
		
		if (quantile != null) {
			quantile.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					CharacteristicQuantification.this.quantile = null;
				}
			});
		}
		
		if (nonQuantifiables != null) {
			for (NonQuantifiable nonQuantifiable : nonQuantifiables) {
				nonQuantifiable.initRemoveCommand(nonQuantifiables);
			}
		}
		
		if (numericals != null) {
			for (Numerical numerical : numericals) {
				numerical.initRemoveCommand(numericals);
			}
		}
		
		if (intervals != null) {
			for (Interval interval : intervals) {
				interval.initRemoveCommand(intervals);
			}
		}
	}
	
	public Scale getScale() {
		return scale;
	}

	public void setScale(Scale scale) {
		this.scale = scale;
		scale.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				CharacteristicQuantification.this.scale = null;
			}
		});
	}

	public Quantile getQuantile() {
		return quantile;
	}

	public void setQuantile(Quantile quantile) {
		this.quantile = quantile;
		quantile.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				CharacteristicQuantification.this.quantile = null;
			}
		});
	}

	public Collection<Numerical> getNumericals() {
		if (numericals == null) {
			return Collections.emptyList();
		}
		return numericals;
	}
	
	public void addNumerical(Numerical numerical) {
		if (numericals == null) {
			numericals = new ArrayList<Numerical>();
		}
		numericals.add(numerical);
		numerical.initRemoveCommand(numericals);
	}
	
	public Collection<Interval> getIntervals() {
		if (intervals == null) {
			return Collections.emptyList();
		}
		return intervals;
	}
	
	public void addInterval(Interval interval) {
		if (intervals == null) {
			intervals = new ArrayList<Interval>();
		}
		intervals.add(interval);
		interval.initRemoveCommand(intervals);
	}
	
	public Collection<NonQuantifiable> getNonQuantifiables() {
		if (nonQuantifiables == null) {
			return Collections.emptyList();
		}
		return nonQuantifiables;
	}

	public void addNonQuantifiable(NonQuantifiable nonQuantifiable) {
		if (nonQuantifiables == null) {
			nonQuantifiables = new ArrayList<NonQuantifiable>();
		}
		nonQuantifiables.add(nonQuantifiable);
		nonQuantifiable.initRemoveCommand(nonQuantifiables);
	}
	
	@Override
	public String toString() {
		return "Characteristic Quantification: " + StringUtils.trimToEmpty(name);
	}
	
}
