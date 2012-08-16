package edu.stanford.isis.ats.resources;

import java.math.BigInteger;
import java.util.UUID;

/**
 * 
 * author Vladimir Kleper
 *
 */
public class Uid {

    public static String generate() {
        final UUID uuid = UUID.randomUUID();
        final String uuidString = uuid.toString().replace("-", ""); 
        final String suffix = new BigInteger(uuidString, 16).toString(10); 
        return "2.25." + suffix;
    }
}
