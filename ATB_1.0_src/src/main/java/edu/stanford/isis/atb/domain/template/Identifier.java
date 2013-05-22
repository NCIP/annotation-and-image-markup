/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.math.BigInteger;
import java.util.UUID;

/**
 * Identifier for elements with uid attribute.
 * 
 * @author Vitaliy Semeshko
 */
public class Identifier {

	private String original;
	
	public Identifier(String identifier) {
		original = identifier;
	}

	public String getOriginal() {
		return original;
	}

	public String getComposite() {
		return original;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((original == null) ? 0 : original.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Identifier other = (Identifier) obj;
		if (original == null) {
			if (other.original != null)
				return false;
		} else if (!original.equals(other.original))
			return false;
		return true;
	}

	public String toString() {
		return getComposite();		
	}
	
	public static Identifier generate() {
		final UUID uuid = UUID.randomUUID();
		final String uuidString = uuid.toString().replace("-", ""); 
		String suffix = new BigInteger(uuidString, 16).toString(10); 
		return new Identifier("2.25." + suffix);
	}
	
}
