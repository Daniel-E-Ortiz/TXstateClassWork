/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment1;
/**
 * Contains elements like Tracking#, Type, Specification, Mailing Class,
 *  Weight, and volume.
 * @author Daniel Ortiz (deo15)
 * 
 */
public class Package {
    /**
     * Constructor to create the package with parameters for each element.
     * @param track Tracking Number for package
     * @param type Type of package
     * @param mailingClass Mailing Class for package
     * @param weight in ounces for package
     * @param volume Volume (L x W x H)
     * @param spec Specification. 
     */
    public Package(String track, String type, String spec, String mailingClass, 
            float weight, int volume){
        this.trackingNumber = track;
        this.type = type;
        this.specification = spec;
        this.mailingClass = mailingClass;
        this.weight = weight;
        this.volume = volume;
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
    public String getPackage(){
        return (trackingNumber + " " + type + " " + specification+ " " + 
                    mailingClass + " " + weight + " " + volume);
    }
    /**
     * Getter for the weight.
     * @return float number greater than or equal to 0.
     */
    public float getWeight(){return weight;}
    
    private final String trackingNumber;
    private final String type;
    private final String specification;
    private final String mailingClass;
    private final float weight;
    private final int volume;
}
