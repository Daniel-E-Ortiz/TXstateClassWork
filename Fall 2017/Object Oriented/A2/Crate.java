/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 package Assignment2;

  /**
  * Contains elements: float weight and String content
  * @author Justin Davis (j_d362)
  */
  public class Crate extends Package {

    /**
     * Constructor to class Crate with parameters for each element.
     * @param track
     * @param spec
     * @param mailingClass
     * @param maxWeight
     * @param content
     */
    public Crate(String track, String spec, String mailingClass, float maxWeight,
            String content) {
        super(track, spec, mailingClass);
        this.maxWeight = maxWeight;
        this.content = content;
    }
    
    /**
     * toString returns a string of all the contents inside Crate separated by
     *      spaces.
     * @return
     */
    @Override
    public String toString() {
        return(super.toString() + "," + Float.toString(maxWeight) + ","
            + content);
    }

    private final float maxWeight;
    private final String content;
  }
