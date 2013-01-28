/*
 * Copyright (c) 2008-2013, Northwestern University
 * All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 *   Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *  
 *   Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *  
 *   Neither the name of the Northwestern University nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
