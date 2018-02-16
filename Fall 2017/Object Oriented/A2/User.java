/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;
import java.io.Serializable;
/**
 *
 * @author Daniel Ortiz(deo15)
 */
abstract class User implements Serializable{
    /**
     * Constructor to class User with parameters for each element.
     * @param id
     * @param first
     * @param last
     */
    public User(int id, String first, String last, boolean isEmp){
        this.identificationNumber = id;
        this.firstName = first;
        this.lastName = last;
        this.isEmployee = isEmp;
    }
    /**
     * toString returns a string of all the contents inside User separated by
     *      spaces.
     * @return
     */
    @Override
    public String toString(){
        return(Integer.toString(identificationNumber) + "," + firstName + "," +
                lastName);
    }
    /**
     * setName is a modifier for first and last name.
     */
    public void setName(String first, String last){
        this.firstName = first;
        this.lastName = last;
    }
    /**
     * 
     * @return
     */
    public boolean getWorkerStatus(){return isEmployee;}
    public int getID(){return identificationNumber;}
    public String getFirst(){return firstName;}
    public String getLast(){return lastName;}
    private String firstName;
    private String lastName;
    private final int identificationNumber;
    private final boolean isEmployee;    
}
