/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;
import java.text.DateFormat;
import java.util.Date;
import java.text.SimpleDateFormat;

/**
 *
 * @author Daniel Ortiz (deo15)
 */
public class Transaction {
    public Transaction(int cID, String trNum, Date sh, Date de, 
            float shCost, int eID){
    this.custID = cID;
    this.trackNum = trNum;
    this.shipped = sh;
    this.delivered = de;
    this.shipCost = shCost;
    this.empID = eID;
}
    @Override
    public String toString(){
        return(Integer.toString(custID) + "," + trackNum + "," + getShipped() 
                + "," + getDelivered() + "," + Float.toString(shipCost) + "," 
                + Integer.toString(empID)) ;
    }
    public int getCustID(){return custID;}
    public String getTrackNum(){return trackNum;}
    public String getShipped(){
        DateFormat df = new SimpleDateFormat("MM/dd/yyyy");
        return (df.format(shipped));      
    }
    public String getDelivered(){
        DateFormat df = new SimpleDateFormat("MM/dd/yyyy");
        return (df.format(delivered));
    }
    public float getShipCost(){return shipCost;}
    public int getEmpID(){return empID;}
    
    private final int custID; // customer ID
    private final String trackNum; // Tracking Number of Package
    private final Date shipped; // Date in which it was shipped
    private final Date delivered; // Date in which it was delivered
    private final float shipCost; // cost of shipping
    private final int empID; // employee who completed the sale.
}
