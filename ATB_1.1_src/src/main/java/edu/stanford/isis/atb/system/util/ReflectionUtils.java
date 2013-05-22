/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.util;

import java.lang.reflect.Field;

/**
 * @author Vitaliy Semeshko
 */
public class ReflectionUtils {

	public static Field findField(Class<?> clazz, String fieldName) {
		while (clazz != null) {
			Field[] fields = clazz.getDeclaredFields();
			for (Field field : fields) {
				if (field.getName().equals(fieldName)) {
					return field;
				}
			}
			clazz = clazz.getSuperclass();
		}
		return null;
	}

}
