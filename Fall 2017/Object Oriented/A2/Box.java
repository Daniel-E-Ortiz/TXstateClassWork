/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 package Assignment2;

 /**
  * Contains elements: dimension and volume
  /**
  * Contains elements: int dimension and int volume
  * @author Justin Davis (j_d362)
  */
  public class Box extends Package {

    /**
     * Constructor to create the Box with parameters for each element.
     * Constructor to class Box with parameters for each element.
     * @param track
     * @param spec
     * @param mailingClass
     * @param dimension
     * @param volume
     */
    public Box(String track, String spec, String mailingClass, int dimension,
            int volume) {
      super(track, spec, mailingClass);
      this.dimension = dimension;
      this.volume = volume;
    }

    /**
     * toString returns a string of all the contents inside Box separated by
     *      spaces.
     * @return
     */
    @Override
    public String toString(){
        return(super.toString() + "," + Integer.toString(dimension) + ","
            + Integer.toString(volume));
    }

     private final int dimension;
     private final int volume;
  }
