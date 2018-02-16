/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 package Assignment2;

  /**
  * Contains elements: String material and float diameter
  * @author Justin Davis (j_d362)
  */
  public class Drum extends Package {

    /**
     * Constructor to class Drum with parameters for each element.
     * @param track
     * @param spec
     * @param mailingClass
     * @param material
     * @param diameter
     */
    public Drum (String track, String spec, String mailingClass, String material,
            float diameter) {
      super(track, spec, mailingClass);
      this.material = material;
      this.diameter = diameter;
    }

    /**
     * toString returns a string of all the contents inside Drum separated by
     *      spaces.
     * @return
     */
    @Override
    public String toString() {
      return(super.toString() + "," + material + "," + Float.toString(diameter));
    }
    
    private final String material;
    private final float diameter;
  }
