/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;

import java.io.Serializable;

/**
 * Contains elements: Tracking#, Specification, and Mailing Class
 * @author Daniel Ortiz (deo15)
 * @author Justin Davis (j_d362)
 */
abstract class Package implements Serializable {
    /**
     * Constructor to create the package with parameters for each element.
     * @param track Tracking Number for package
     * @param spec Specification.
     * @param mailingClass Mailing Class for package
     */
    public Package(String track, String spec, String mailingClass){
        this.trackingNumber = track;
        this.specification = spec;
        this.mailingClass = mailingClass;
    }

    /**
     * Getter for the tracking number.
     * @return String of tracking number.
     */
    public String getTrack(){return this.trackingNumber;}
    /**
     * Getter for the contents of package in correct order separated by spaces.
     * Example: "AAAAA Letter N/A First 1.0 1"
     * @return String of package contents
     */
    @Override
    public String toString(){
        return (trackingNumber + "," + specification + "," + mailingClass);
    }
    public String getMailClass(){
        return mailingClass;
    }
    private final String trackingNumber;
    private final String specification;
    private final String mailingClass;
}
