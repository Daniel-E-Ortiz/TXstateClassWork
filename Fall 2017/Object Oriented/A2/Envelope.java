/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 package Assignment2;

 /**
  * Contains elements: int height and int width
  * @author Justin Davis (j_d362)
  */
  public class Envelope extends Package {

    /**
     * Constructor to class Envelope with parameters for each element.
     * @param track
     * @param spec
     * @param mailingClass
     * @param height
     * @param width
     */
    public Envelope(String track, String spec, String mailingClass, int height,
            int width){
        super(track, spec, mailingClass);
        this.height = height;
        this.width = width;

    }
    
    @Override
    public String toString(){
        return (super.toString() + "," + Integer.toString(height) + "," 
                + Integer.toString(width));
    }

    private final int height;
    private final int width;
  }
