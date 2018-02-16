/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;

/**
 *
 * @author Daniel Ortiz(deo15)
 */
public class Customer extends User {

    /**
     * Constructor for Customer Class including parameter for super constructor.
     * @param id
     * @param first
     * @param last
     * @param phone
     * @param addr
     * @param isEmp
     */
    public Customer(int id, String first, String last, String phone,
            String addr){
        super(id,first,last,false);
        this.phoneNumber = phone;
        this.address = addr;
    }

    @Override
    public String toString(){
        return (super.toString() + "," + phoneNumber + "," + address);
    }

    public void setPhoneNum(String phoneNum){
        this.phoneNumber = phoneNum;
    }

    public void setAddr(String addr){
        this.address = addr;
    }
    public String getPhone(){return phoneNumber;}
    public String getAddr(){return address;}
    
    private String phoneNumber;
    private String address;
}
