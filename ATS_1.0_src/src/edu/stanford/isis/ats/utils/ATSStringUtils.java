/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

package edu.stanford.isis.ats.utils;

import java.util.Collection;
import java.util.Iterator;

/**
 *
 * @author Vladimir Kleper
 *
 */
public class ATSStringUtils {

    private static final String UID_REGEX = "[0-2]((\\.0)|(\\.[1-9][0-9]*))*";

    public static int tryParseInt(String in, int defaultValue) {
        try {
            return Integer.parseInt(in);
        } catch(NumberFormatException ex) {
            return defaultValue;
        }
    }

    /**
     * Convert given string to titleCase.
     *  NOTE: Characters that are already upper case are ignored. To get proper Title Case, call String.toLower() first.
     *  Example: toTitleCase("stRIng onE") results in "StRIng OnE" output
     * @param input
     * @return given string
     */
    public static String toTitleCase(String input) {
        final StringBuilder titleCase = new StringBuilder();
        boolean nextTitleCase = true;

        for (char c : input.toCharArray()) {
            if (Character.isSpaceChar(c)) {
                nextTitleCase = true;
            } else if (nextTitleCase) {
                c = Character.toTitleCase(c);
                nextTitleCase = false;
            }
            titleCase.append(c);
        }

        return titleCase.toString();
    }

    /**
     * Test the given string if it is a valid DICOM UID
     * @param uidToValidate - UID to test
     * @return true is UID is a valid DICOM UID or false - if not
     */
    public static boolean isValidUid(String uidToValidate) {
        return uidToValidate != null && uidToValidate.length() <= 64 && uidToValidate.matches(UID_REGEX);
    }

    /**
     * Get file name out of the full path name
     * @param filePathName
     * @return file name of the file's path & name if found, or the original file path name
     */
    public static String fileNameFromPathName (String filePathName) {
        if (filePathName == null)
            return filePathName;

        final String[] separators = {"\\", "/"};
        for (String sep : separators) {
            int idx = filePathName.lastIndexOf(sep);
            if (idx >= 0)
                return filePathName.substring(idx + 1);
        }
        return filePathName;
    }

    /**
     * Join collection into a delimited string
     * @param in input collection
     * @param delimiter
     * @return string of collection items separated by the delimiter
     */
    public static String join(Collection<?> in, String delimiter) {
        final StringBuilder builder = new StringBuilder();
        final Iterator<?> iter = in.iterator();
        while (iter.hasNext()) {
            builder.append(iter.next());
            if (!iter.hasNext()) {
                break;
            }
            builder.append(delimiter);
        }
        return builder.toString();
    }
}
