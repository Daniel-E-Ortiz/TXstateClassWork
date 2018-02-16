/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;

/**
 * Class Employee extends Class User with added variables like SSN,
 *      monthly salary, and direct deposit account number.
 * @author Daniel Ortiz(deo15)
 */
public class Employee extends User {
    /**
     * Constructor for Employee taking 6 parameters.
     * @param id
     * @param first
     * @param last
     * @param SSN
     * @param monthly
     * @param directDeposit
     */
    public Employee(int id, String first, String last, int SSN, double monthly,
            int directDeposit){
        super(id,first,last,true);
        this.SSN = SSN;
        this.monthlySalary = monthly;
        this.directDepositAccNumber = directDeposit;
    }
    /**
     * toString returns a string of all the contents inside Employee including
     *      the contents inside User by calling User's toString().
     * ID + First + Last + SSN + MonthlySal + DirectDeposit 
     * @return
     */
    @Override
    public String toString(){
        return(super.toString() + "," + Integer.toString(SSN) +
                "," + Double.toString(monthlySalary) +
                "," + Integer.toString(directDepositAccNumber));
    }
    public void setSSN(int s){
        this.SSN = s;
    }
    public void setMonSal(double m){
        this.monthlySalary = m;
    }
    public void setDDAN(int d){
        this.directDepositAccNumber = d;
    }
    public int getSSN(){return SSN;}
    public double getSal(){return monthlySalary;}
    public int getAccNum(){return directDepositAccNumber;}
    
    private int SSN;
    private double monthlySalary;
    private int directDepositAccNumber;
}
