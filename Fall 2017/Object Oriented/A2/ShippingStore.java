/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;
import java.util.ArrayList;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.Calendar;
import java.io.*;
import java.util.Date;
import java.util.concurrent.ThreadLocalRandom;
import java.util.regex.Pattern;
/**
 * @author Daniel Ortiz (deo15)
 * @author Justin Davis (j_d362)
 * @version 10/04/2017
 */
public class ShippingStore{
    public void openFile(){
        try{
            FileInputStream fis = new FileInputStream("DataBase.ser");
            ObjectInputStream ois = new ObjectInputStream(fis);
            pList = (ArrayList<Package>)ois.readObject();
            uList = (ArrayList<User>)ois.readObject();
            tList = (ArrayList<Transaction>)ois.readObject();
        }
        catch(FileNotFoundException e){
            System.out.println("ERROR: " + e.getMessage());
        }
        catch(IOException e){
            System.out.println("ERROR: " + e.getMessage());
        }
        catch(ClassNotFoundException e)
        {
            System.out.println("ERROR: " + e.getMessage());
        }
        
    }
    public void quit(){
        try{
            FileOutputStream fos = new FileOutputStream("DataBase.ser");
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(pList);
            oos.writeObject(uList);
            oos.writeObject(tList);
        }
        catch(FileNotFoundException e){
            System.out.println("ERROR: " + e.getMessage());
        }
        catch(IOException e){
            System.out.println("ERROR: " + e.getMessage());   
        }
    }
    /**
     * Prints all Packages with formatting inside list.
     */
    public void showAllPackages(){
        if(pList.isEmpty()){
            System.out.println("\nPACKAGE RECORDS ARE EMPTY!\n");
            System.out.println("Would you like to add a new one? (y/n)");
            Scanner in = new Scanner(System.in);
            String answer = in.nextLine();
            if(answer.equalsIgnoreCase("Y"))
                addPackage();
            return;
        }
        printHeaderPackage();
        for(Package p:pList){
            if(p instanceof Box)
                formatBox(p.toString().split(","));
            else if(p instanceof Crate)
                formatCrate(p.toString().split(","));
            else if(p instanceof Drum)
                formatDrum(p.toString().split(","));
            else
                formatEnvelope(p.toString().split(","));
        }
        System.out.println(DASHLINE);
    }

    /**
     *  Adds a new package object into the list and verifies input.
     */
    public void addPackage(){

        /*
        * defualt values are necessary because compiler thinks there may be
        *   possibility they may not be initialized.
        */
        String track = "err", spec = "err", mailingClass = "err", type = "err";

        Scanner in = new Scanner(System.in);
        int k;
        do{
            k = 0;
            System.out.println("Enter (in-order), new Package information with spaces.");
            System.out.println("Only enter the following information:");
            System.out.println("Tracking#, Specification, Mailing Class, Type");
            System.out.println("Example: 632VR Fragile First Box");

            String line = in.nextLine();
            String []words = line.split(",");
            for(String s:words){k++;}     
                if(k == 4){
                    track = words[0];
                    spec = words[1];
                    mailingClass = words[2];
                    type = words[3];
                }
                else{System.out.println("You must have exactly 4 elements to begin"
                        + "adding a new Package. Please re-enter package information.");
                }
        }while(k!=4);

        /* Verifies basic package info */
        int result;
        do{
            result = verify(track, spec, mailingClass, type);
            switch (result){
                case 0: // no errors
                    System.out.println("\nSuccessful!\n");
                    break;
                case 1: // tracking number incorrect
                    track = in.nextLine();
                    break;
                case 2: // spec incorrect
                    spec = in.nextLine();
                    break;
                case 3: // mailingClass incorrect
                    mailingClass = in.nextLine();
                    break;
                case 4: // type incorrect
                    type = in.nextLine();
                    break;
            }
        } while(result != 0);
    }

    /**
     * Searches and deletes a package with a specified tracking number.
     * Prints "REMOVE SUCCESSFUL." or "ERROR: TRACKING NUMBER NOT FOUND."
     */
    public void delete(){
        String track;
        System.out.println("Type in the Tracking# you want removed.");
        Scanner in = new Scanner(System.in);
        track = in.nextLine();
        boolean removeSuccess = false;
        int index = 0;
        while (index < pList.size())
        {
            if(pList.get(index).getTrack().equalsIgnoreCase(track)){
                  pList.remove(index);
                  System.out.println("REMOVE SUCCESSFUL.");
                  removeSuccess = true;
                  break;
            }
            index++;
        }
          if (removeSuccess == false)
              System.out.println("ERROR: TRACKING NUMBER NOT FOUND.");
    }

    /**
     *  Asks user for Tracking Number input to find a package within the list.
     */
    public void search(){
        boolean found = false;
        String track;
        Scanner in = new Scanner(System.in);
        System.out.println("Please input the Tracking Number you are looking"
                + " for.");
        track = in.nextLine();
        int result;
        do{
            result = verifyTrack(track);
            if (result == 1)
                track = in.nextLine();
        }while(result != 0);

        for(Package p:pList){
            if(p.getTrack().equalsIgnoreCase(track)){
                found = true;
                printHeaderPackage();
                if(p instanceof Box)
                    formatBox(p.toString().split(","));
                else if(p instanceof Crate)
                    formatCrate(p.toString().split(","));
                else if(p instanceof Drum)
                    formatDrum(p.toString().split(","));
                else
                    formatEnvelope(p.toString().split(","));
                break;
            }
        }
        System.out.println(DASHLINE);
        if(!found){
            System.out.println("TRACKING NUMBER NOT FOUND!");
        }
    }

    /**
     *
     */
    public void updateUser(){
        Scanner sc = new Scanner(System.in);
        System.out.println("What is the User ID?");
        int ID = sc.nextInt();
        String first, last, input, phoneNumber, addr;
        int choice, SSN, directDeposit;
        int index = 0;
        double salary;
        boolean checkID = false;
        while (index < uList.size()){
            if(uList.get(index).getID() == ID){
                checkID = true;
                if(uList.get(index) instanceof Employee)
                {
                    do{
                        printEmployeeUpdateMenu();
                        choice = sc.nextInt();
                        switch(choice){
                            case 1: // update First and Last Name
                                System.out.println("Original: " + uList.get(index).getFirst());
                                System.out.println("First Name?");
                                sc.nextLine();
                                first = sc.nextLine();
                                while(!verifyFirstLast(first)){
                                    System.out.println("ERROR: First Name"
                                            + " cannot contain any numbers or"
                                            + " special characters! Please"
                                            + " re-input your First Name.");
                                    first = sc.nextLine();
                                }
                                System.out.println("Original: " + uList.get(index).getLast());
                                System.out.println("Last Name?");
                                last = sc.nextLine();
                                while(!verifyFirstLast(last)){
                                    System.out.println("ERROR: Last Name"
                                            + " cannot contain any numbers or"
                                            + " special characters! Please"
                                            + " re-input your First Name.");
                                    last = sc.nextLine();
                                }
                                uList.get(index).setName(first, last);
                                System.out.println("UPDATE SUCCESSFUL!");
                                break;
                            case 2: // update SSN
                                System.out.println("Original: " 
                                       + ((Employee)uList.get(index)).getSSN());
                                System.out.println("Type in the SSN of "
                                        + "Employee.");
                                sc.nextLine();
                                input = sc.nextLine();
                                while(!verifySSN(input)){
                                    System.out.println("ERROR: SSN: " + input
                                            + " not 9 numbers long. Please"
                                            + " re-enter the SSN.");
                                    input = sc.nextLine();
                                }
                                SSN = Integer.parseInt(input);
                                ((Employee) uList.get(index)).setSSN(SSN);
                                break;
                            case 3: // update Monthly Salary
                                // TRY
                                System.out.println("Original: " 
                                       + ((Employee)uList.get(index)).getSal());
                                System.out.println("Type in the new Monthly"
                                        + "Salary for Employee.");
                                input = sc.nextLine();
                                // catch exception (double parse shit)
                                // salary = Double.parseDouble(input);
                                // { while loop
                                while(!verifySalary(input)){
                                    System.out.println("ERROR: The Monthly"
                                            + " Salary you entered must be a"
                                            + " decimal. Please re-enter the"
                                            + " monthly salary.");
                                    input = sc.nextLine();
                                }
                                // }
                                salary = Double.parseDouble(input);
                                ((Employee) uList.get(index)).setMonSal(salary);
                                System.out.println("UPDATE SUCCESSFUL!");
                                break;
                            case 4: // update Direct Deposit
                                // TRY
                                System.out.println("Original: " 
                                    + ((Employee)uList.get(index)).getAccNum());
                                System.out.println("Type in the new Direct"
                                        + " Deposit Account Number for"
                                        + " Employee.");
                                input = sc.nextLine();
                                // catch exception (integer parse shit)
                                // directDeposit = Integer.parseInteger(input);
                                // { while loop
                                while(!verifyDDAN(input)){
                                    System.out.println("ERROR: The Direct"
                                            + " Deposit Account you entered"
                                            + " must be 10-12 digits long."
                                            + " Please re-enter the Direct"
                                            + " Deposit Account Number.");
                                    input = sc.nextLine();
                                }
                                // }
                                directDeposit = Integer.parseInt(input);
                                ((Employee) uList.get(index)).
                                        setDDAN(directDeposit);
                                System.out.println("UPDATE SUCCESSFUL!");
                                break;
                            case 5: // quit updates
                                System.out.println("Leaving Employee Edit"
                                        + " Menu!");
                                break;
                            default: // not a number between [1-5]
                                break;
                        }
                    }while(choice != 5);
                }
                else{ // User is Customer
                    do{
                        printCustomerUpdateMenu();
                        choice = sc.nextInt();
                        switch(choice){
                            case 1: // update First and Last Name
                                sc.nextLine();
                                System.out.println("Original: " 
                                     + ((Customer)uList.get(index)).getFirst());
                                System.out.println("First Name?");
                                first = sc.nextLine();
                                while(!verifyFirstLast(first)){
                                    System.out.println("ERROR: First Name"
                                            + " cannot contain any numbers or"
                                            + " special characters! Please"
                                            + " re-input your First Name.");
                                    first = sc.nextLine();
                                }
                                System.out.println("Original: " 
                                     + ((Customer)uList.get(index)).getLast());
                                System.out.println("Last Name?");
                                last = sc.nextLine();
                                while(!verifyFirstLast(last)){
                                    System.out.println("ERROR: Last Name"
                                            + " cannot contain any numbers or"
                                            + " special characters! Please"
                                            + " re-input your First Name.");
                                    last = sc.nextLine();
                                }
                                uList.get(index).setName(first, last);
                                System.out.println("UPDATE SUCCESSFUL!");
                                break;
                            case 2: // update phone number
                                sc.nextLine();
                                System.out.println("Original: " 
                                     + ((Customer)uList.get(index)).getPhone());
                                System.out.println("What is the new Phone"
                                        + " Number of the Customer?");
                                System.out.println("Example: 123-456-7890");
                                phoneNumber = sc.nextLine();
                                while(!verifyPhoneNum(phoneNumber)){
                                    System.out.println("ERROR: Must be written"
                                            + " as 123-456-7890");
                                    phoneNumber = sc.nextLine();
                                }
                                ((Customer) uList.get(index)).
                                        setPhoneNum(phoneNumber);
                                break;
                            case 3: // update address
                                sc.nextLine();
                                System.out.println("Original: " 
                                      + ((Customer)uList.get(index)).getAddr());
                                System.out.println("What is the new Address"
                                        + " for the Customer?");
                                System.out.println("Example: 123 fake street");
                                addr = sc.nextLine();
                                ((Customer) uList.get(index)).setAddr(addr);
                                break;
                            case 4: // quit updates
                                System.out.println("Leaving Customer Update"
                                        + " Menu!");
                                break;
                            default: // not a number between [1-4]
                                System.out.println("Please Input a number"
                                        + " between [1-4]");
                                break;
                        }
                    }while(choice != 4);
                }
                return;
            }
            else
                index++;
        }
        if(!checkID){
            System.out.println("ERROR: ID does not exist.");
        }
    }

    /**
     *
     */
    public void showAllUsers(){
        if(uList.isEmpty()){
            System.out.println("\nUSER RECORDS ARE EMPTY!\n");
            System.out.println("Would you like to add a new one? (y/n)");
            Scanner in = new Scanner(System.in);
            String answer = in.nextLine();
            if(answer.equalsIgnoreCase("Y")){
               addNewUser();
            }
            return;
        }
        printHeaderUser();
        for(User u:uList){
            if(u instanceof Employee)
                formatEmp(((Employee)u).toString().split(","));
            else
                formatCust(((Customer)u).toString().split(","));
        }
        System.out.println(DASHLINE_USER);
    }

    /**
     * Writes to File.
     * @param file File being written to.
     * @throws Exception
     */
    public void quit(String file) throws Exception{
        PrintWriter pw = new PrintWriter(file);
        /*for(Package p:list){
            pw.println(p.toString());
        }
        */
        System.out.println("Saving To file " + file + "... GoodBye!\n");
    }
    
    /**
     * Verifies all input parameters are correct, then verifies type-specifics
     * @param track Tracking Number. ex: ABC12
     * @param spec Specification of the Package. ex: Fragile
     * @param mailingClass ex: First
     * @param type Type of Package. ex: Box
     * @return ERROR_CODE(0-6) 0:No errors, 1:track error, 2:spec error,
     *                         3:mailingClass error, 4:type error,
     */
    private int verify(String track, String spec, String mailingClass, String type){
            /*String weight,String volume)*/
        // NO 2 PACKAGES CAN HAVE SAME TRACKING NUMBER.
        for(Package p:pList){
            if(track.equalsIgnoreCase(p.getTrack())){
                System.out.println(DASHLINE);
                System.out.println("ERROR: Tracking # already exists: "
                        + track);
                System.out.println("Please input another Tracking #!");
                System.out.println("Must be 5 characters in length.");
                System.out.println("Example: ABC12 or 12ABC or AB12C.");
                System.out.println(DASHLINE);
                return 1;
            }
        }

        // string "track" verification, returns 1 if bad.
        // must be exactly 5 characters long.
        if (!track.matches("^(\\w{5})$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Tracking #: " + track);
            System.out.println("Please input correct Tracking #!");
            System.out.println("Must be 5 alphanumeric characters in length.");
            System.out.println("Example: ABC12 or 12ABC or AB12C.");
            System.out.println(DASHLINE);
            return 1;
        }
        else{System.out.println("Tracking Number accepted!");}

        // string "spec" validation, returns 3 if bad.
        // must be 1 of the following:
        //      Fragile, Books, Catalogs, Do-not-Bend, N/A
        if (!spec.matches("^(Fragile|Books|Catalogs|Do-not-Bend|N/A|n/a)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Specification: " + spec);
            System.out.println("Please input correct Specification!");
            System.out.println("Must be one of the following:");
            System.out.println("Fragile, Books, Catalogs, Do-not-Bend, N/A");
            System.out.println(DASHLINE);
            return 2;
        }
        else{System.out.println("Specification accepted!");}

        // string "Classification" validation, returns 3 if bad.
        // must be one of the following...
        // First-Class, Priority, Retail, Ground, or Metro.
        if (!mailingClass.matches("^(First-Class|Priority|Retail|Ground|Metro)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Class: " + mailingClass);
            System.out.println("Please input correct Class!");
            System.out.println("Must be one of the following:");
            System.out.println("First-Class, Priority, Retail, Ground, Metro");
            System.out.println(DASHLINE);
            return 3;
        }

        // string "type" verification, returns 4 if bad.
        // must be one of the following...
        // Envelope, Box, Crate, or Drum.
        if (!(type.matches("^(Envelope|Box|Crate|Drum)$"))){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Type: " + type);
            System.out.println("Please input correct Type!");
            System.out.println("Must be one the following:");
            System.out.println("Envelope, Box, Crate, Drum");
            System.out.println("Hint: Case Sensitive!");
            System.out.println(DASHLINE);
            return 4;
        }
        else{
            // "type" of package is valid
            // now we must verify "type-specific" package information
            System.out.println("'Type' of package is valid...");
            System.out.println("Now we must enter Type-specific details...");

            switch (type) {
                case "Box":
                    verifyBox(track, spec, mailingClass);
                    break;
                case "Crate":
                    verifyCrate(track, spec, mailingClass);
                    break;
                case "Drum":
                    verifyDrum(track, spec, mailingClass);
                    break;
                case "Envelope":
                    verifyEnvelope(track, spec, mailingClass);
                    break;
                default:
            }
        }
        return 0;
    }
    /**
     * Verifies Box-specific info (largest dimension and volume).
     * Once verified, the Box is added to pList.
     * @param track
     * @param spec
     * @param mailingClass
     */
    private void verifyBox(String track, String spec, String mailingClass){

        int dimension, volume;
        String input;

        System.out.println("Enter the Box's largest dimension.");
        Scanner sc = new Scanner(System.in);
        input = sc.nextLine();
        // int "Dimension" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit WITHOUT a decimal point.");
            System.out.println(DASHLINE);
        }
        dimension = Integer.parseInt(input);
        System.out.println("DIMENSION ACCEPTED!");

        System.out.println("Enter the Box's volume (inches cubed).");
        sc = new Scanner(System.in);
        input = sc.nextLine();
        // int "volume" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit WITHOUT a decimal point.");
            System.out.println(DASHLINE);
        }
        volume = Integer.parseInt(input);
        System.out.println("VOLUME ACCEPTED!");

        pList.add(new Box(track, spec, mailingClass, dimension, volume));
        System.out.println("~~BOX ACCEPTED!~~");
    }

    /**
     * Verifies Crate-specific info (largest dimension and volume).
     * Once verified, the Crate is added to pList.
     * @param track
     * @param spec
     * @param mailingClass
     */
    private void verifyCrate(String track, String spec, String mailingClass){

        float maxLoad;
        String content = "err";
        String input;

        System.out.println("Enter the Crate's maximum load weight.");
        System.out.println("Values entered can be whole nubmers or"
                + " decimal point.");
        Scanner sc = new Scanner(System.in);
        input = sc.nextLine();
        // float "Max Load" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)(\\.?)(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit with or without a decimal point.");
            System.out.println("Example: 1, 1.0, 2.00.");
            System.out.println(DASHLINE);
        }
        maxLoad = Float.parseFloat(input);
        System.out.println("MAXLOAD ACCEPTED!");

        System.out.println("Enter the Crate's content.");
        System.out.println("Must be within 8 characters in length.");
        System.out.println("Example: Staples, Pencils, P_Clips, etc...");
        input = sc.nextLine();
        // string "Content" validation.
        while(input.length() > 8){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Content name too long: " + input);
            System.out.println("Must be within 8 characters long.");
            System.out.println("Example: Staples, Pencils, P_Clips, etc...");
            System.out.println(DASHLINE);
        }
        System.out.println("CONTENT ACCEPTED!");

        pList.add(new Crate(track, spec, mailingClass, maxLoad, content));
        System.out.println("~~CRATE ACCEPTED!~~");
    }

    private void verifyDrum(String track, String spec, String mailingClass){

        String material;
        float diameter;
        String input;

        System.out.println("Enter the Drum's material. Choices are: Plastic or Fiber");
        Scanner sc = new Scanner(System.in);
        material = sc.nextLine();
        // string "material" validation.
        // must be 1 of the following:
        // Plastic or Fiber
        while(!material.matches("^(Plastic|Fiber|)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Material: " + material);
            System.out.println("Please input correct Meterial..");
            System.out.println("Must be one of the following:");
            System.out.println("Plastic or Fiber");
            System.out.println(DASHLINE);
        }
        System.out.println("Meterial accepted..");

        System.out.println("Enter the Drum's diameter.");
        input = sc.nextLine();
        // float "Diamter" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)(\\.?)(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit with or without a decimal point.");
            System.out.println("Example: 1, 1.0, 2.00.");
            System.out.println(DASHLINE);
        }
        diameter = Float.parseFloat(input);

        System.out.println("Diameter accepted..");
        pList.add(new Drum(track, spec, mailingClass, material, diameter));
        System.out.println("Drum accepted!");
    }

    private void verifyEnvelope(String track, String spec, String mailingClass){

        int height, width;
        String input;

        System.out.println("Enter the Enveleope's largest height.");
        Scanner sc = new Scanner(System.in);
        input = sc.nextLine();
        // int "height" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit WITHOUT a decimal point.");
            System.out.println(DASHLINE);
        }
        height = Integer.parseInt(input);
        System.out.println("Height accepted..");

        System.out.println("Enter the Envelope's width.");
        sc = new Scanner(System.in);
        input = sc.nextLine();
        // int "Width" validation.
        // must be a digit input separated by a decimal or Integer.
        while(!input.matches("^(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Diameter: " + input);
            System.out.println("Please input correct Weight in inches!");
            System.out.println("Must be a digit WITHOUT a decimal point.");
            System.out.println(DASHLINE);
        }
        width = Integer.parseInt(input);
        System.out.println("Width accepted..");
        pList.add(new Envelope(track, spec, mailingClass, height, width));
        System.out.println("Envelope accepted!");
    }
    public void addNewUser(){
        Scanner sc = new Scanner(System.in);
        String first, last, phoneNumber, address;
        String input;
        int eOrC, userID, SSN = 000000000, directDeposit = 0000000000;
        double salary = 0.0;
        int min = 0, max = 1000;
        userID = ThreadLocalRandom.current().nextInt(min, max);
        System.out.println("What is the User's First Name?");
        first = sc.nextLine();
        while(!verifyFirstLast(first)){
            System.out.println("ERROR: First Name cannot contain any"
                    + " numbers or special characters! Please re-input"
                    + " your First Name.");
            first = sc.nextLine();
        }
        System.out.println("What is the User's Last Name?");
        last = sc.nextLine();
        while(!verifyFirstLast(last)){
            System.out.println("ERROR: Last Name cannot contain any"
                    + " numbers or special characters! Please re-input"
                    + " your Last Name.");
            last = sc.nextLine();
        }
        System.out.println("Is this new User an (1)Employee or"
                + " (2)Customer?");
        System.out.println("Press \'1\' for Employee or \'2\' for"
                + " Customer.");
        eOrC = sc.nextInt();
        while(!Pattern.matches("\\d{1}",Integer.toString(eOrC))){
            System.out.println("You must input a single digit number. "
                    + "Either a \'1\' or \'2\'.");
            eOrC = sc.nextInt();
        }
        switch(eOrC){
            case 1: // Employee
                System.out.println("What is the SSN for Employee: "
                        + first + " " + last + "?");
                System.out.println("Do not include spaces or "
                        + "dashes!");
                System.out.println("Must be 9 numbers long.");
                System.out.println("Example: 123456789");
                SSN = sc.nextInt();
                while(!verifySSN(Integer.toString(SSN))){
                    System.out.println("ERROR: SSN: " + SSN + " not 9 numbers"
                            + " long.");
                    SSN = sc.nextInt();
                }
                System.out.println("What is the Salary for Employee: "
                        + first + " " + last + "?");
                System.out.println("Example: 40000.00");
                salary = sc.nextDouble();
                while(!verifySalary(Double.toString(salary))){
                    System.out.println("ERROR: Salary: " + salary + " not"
                            + " written as a decimal.");
                    salary = sc.nextDouble();
                }
                System.out.println("What is the Direct Deposit"
                        + " Account Number for " + first + " "
                        + last + "?");
                System.out.println("Must be between 10-12 digits in"
                        + " length.");
                System.out.println("Example: 1234567890");
                directDeposit = sc.nextInt();
                while(!verifyDDAN(Integer.toString(directDeposit))){
                    System.out.println("ERROR: Must be between 10-12 digits"
                            + " in length.");
                    directDeposit = sc.nextInt();
                }
                System.out.println("----First: " + first);
                System.out.println("----Last: " + last);
                System.out.println("----SSN: " + SSN);
                System.out.println("----Salary: " + salary);
                System.out.println("----Direct Deposit Account Number: "
                        + directDeposit);
                uList.add(new Employee(userID,first,last,SSN,salary,
                        directDeposit));
                System.out.println("\t ADD SUCCESSFUL!");
                break;
            case 2: // Customer
                System.out.println("\tWhat is the Phone Number for"
                        + " Customer: " + first + " " + last + "?");
                System.out.println("\tExample: 123-456-7890");
                phoneNumber = sc.nextLine();
                while(!verifyPhoneNum(phoneNumber)){
                    System.out.println("\tERROR: Must be written"
                            + " as 123-456-7890");
                    phoneNumber = sc.nextLine();
                }
                System.out.println("\tWhat is the Address for"
                        + " Customer: " + first + " " + last + "?");
                System.out.println("\tExample: 123 fake street");
                address = sc.nextLine();
                System.out.println("----First: " + first);
                System.out.println("----Last: " + last);
                System.out.println("----Phone Number: " + phoneNumber);
                System.out.println("----Address: " + address);
                uList.add(new Customer(userID,first,last,phoneNumber,address));
                System.out.println("\t ADD SUCCESSFUL!");
                break;
            default:
                System.out.println("\tERROR: Your choice " + eOrC + " is"
                        + " not 1 or 2!");
                break;
        }
    }
    /**
    *
    */
    public void completeShip(){
        /*
        • Customer id: int
        • Package Tracking Number: String
        • Shipping date: Date
        • Delivery date: Date
        • Cost of shipping: float
        • Employee id (who completed the sale): int
        */
        int custID, empID, choice;
        boolean isCust, isEmp, isTrack;
        int index = 0;
        String track, input,mailClass;
        Calendar shDate;
        Calendar deDate;
        float shipCost;
        Scanner sc = new Scanner(System.in);
        if(uList.isEmpty()){
            System.out.println("ERROR: NO USERS IN DATABASE!");
            return;
        }
        System.out.println("What is the customerID?");
        custID = sc.nextInt();
        System.out.println("custID: " + custID);
        System.out.println("What is the Employee ID?");
        empID = sc.nextInt();
        isCust = false;
        isEmp = false;
        for(User u:uList){
            if(custID == u.getID()){isCust = true;}
            if(empID == u.getID()){isEmp = true;}
        }
        if(!isCust || !isEmp){
            if(!isCust)
                System.out.println("ERROR: Customer ID Does not exist!");
            if(!isEmp)
                System.out.println("ERROR: Employee ID does not exist!");
            System.out.println("Exiting to menu.\n");
            return;
        }
        if(!isEmp){
            System.out.println("ERROR: Employee ID does not exist!");
            return;
        }
        System.out.println("What is the Package Tracking Number?");
        do{
            isTrack = false;
            track = sc.nextLine();
            while(verifyTrack(track) == 1){
                track = sc.nextLine();
            }
            for(Package p:pList){
                if(p.getTrack().equalsIgnoreCase(track)){
                    isTrack = true;
                    index = pList.indexOf(p);
                    break;
                }
            }
        }while(!isTrack);

        shDate = Calendar.getInstance();
        deDate = Calendar.getInstance();
        mailClass = pList.get(index).getMailClass();
        // First-Class Priority Retail Ground Metro
        if(mailClass.equalsIgnoreCase("First-Class")){
            deDate.add(Calendar.DAY_OF_MONTH, FIRST_CLASS);
            shipCost = FIRST_COST;
        }
        else if(mailClass.equalsIgnoreCase("Priority")){
            deDate.add(Calendar.DAY_OF_MONTH, PRIORITY);
            shipCost = PRIORITY_COST;
        }
        else if(mailClass.equalsIgnoreCase("Retail")){
            deDate.add(Calendar.DAY_OF_MONTH, RETAIL);
            shipCost = RETAIL_COST;
        }
        else if(mailClass.equalsIgnoreCase("Ground")){
            deDate.add(Calendar.DAY_OF_MONTH, GROUND);
            shipCost = GROUND_COST;
        }
        else /*metro*/ {
            deDate.add(Calendar.DAY_OF_MONTH, METRO);
            shipCost = METRO_COST;
        }
        System.out.println("\nShipping Transaction SUCCESSFUL!"
                + "\n Press \'9\' to see list of completed transactions.\n");
        Date deliver = deDate.getTime();
        Date ship = shDate.getTime();
        tList.add(new Transaction(custID,track,ship,deliver,shipCost,empID));
        pList.remove(index);
    }
    /**
     * 
     */
    public void showShipTrans(){
       if(tList.isEmpty()){
           System.out.println("ERROR: NO SHIPPING TRANSACTIONS!");
           return;
       }
       printHeaderTrans();
       for(Transaction t:tList){
           formatTrans(t.toString().split(","));
       }
       System.out.println(DASHLINE_TRANS);
    }
    private boolean verifyFirstLast(String input){
        return Pattern.matches("[a-zA-Z]+", input);
    }
    private boolean verifySSN(String input){
        return Pattern.matches("\\d{9}", input);
    }
    private boolean verifySalary(String input){
        return Pattern.matches("^(\\d+)(\\.?)(\\d+)$", input);
    }
    private boolean verifyDDAN(String input){
        return Pattern.matches("\\d{10,12}", input);
    }
    private boolean verifyPhoneNum(String input){
        return Pattern.matches("^(\\d{3}-?\\d{3}-?\\d{4})$", input);
    }
    private int verifyTrack(String track){
        // string "track" verification, returns 1 if bad.
        if (!track.matches("^(\\w{5})$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Tracking #: " + track);
            System.out.println("Please input correct Tracking #!");
            System.out.println("Must be 5 characters in length.");
            System.out.println("Example: ABC12 or 12ABC or AB12C.");
            System.out.println(DASHLINE);
            return 1;
        }
        else return 0;
    }
    private void printHeaderPackage(){
        System.out.println(DASHLINE);
        System.out.format("|%1$9s | %2$10s |%3$14s |%4$14s |%5$11s %6$10s |\n",
                "Type","Tracking Number","Specification","Mailing Class","Extra","Info");
        System.out.println(DASHLINE);
    }
    private void printHeaderUser(){
        System.out.println(DASHLINE_USER);
        System.out.format("|%1$8s | %2$5s |%3$15s |%4$15s |%5$10s |%6$15s |%7$30s |"
                + "%8$15s |%9$20s |\n",
                "Employee","ID","FirstName","LastName","SSN","Monthly Salary",
                "Direct Deposit Account Number","PhoneNumber","Address");
        System.out.println(DASHLINE_USER);
    }
    private void printHeaderTrans(){
        System.out.println(DASHLINE_TRANS);
        System.out.format("|%1$11s | %2$15s |%3$10s |%4$14s |%5$17s |%6$12s |\n",
                "CustomerID","Tracking Number","Ship Date","Delivery Date",
                "Cost of Shipping","Employee ID");
        System.out.println(DASHLINE_TRANS);
    }
    private void formatTrans(String words[]){
        float shipCost = Float.parseFloat(words[4]);        
        // [0] Customer ID(int) + [1] TrackingNum(s) + [2] ShippingDate(s) + 
        // [3] DeliveryDate(s)  + [4] CostOfShip(f)  + [5] EmployeeID(int)
        
        System.out.format("|%1$11s |%2$16s |%3$15s |%4$15s |%5$17.2f |%6$12s |\n", 
                words[0],words[1],words[2],words[3],shipCost,words[5]);
    } 
    private void formatEmp(String words[]){
        double monSal = Double.parseDouble(words[4]);
        // [0]ID(int) + [1]FIRST(s) + [2]LAST(s) + [3]SSN(int) +
        // [4]MonthlySal(double) + [5]DirectDeposit(int)
        System.out.format("|%1$8b | %2$5s |%3$15s |%4$15s |%5$10s |%6$15.2f |%7$30s |"
                + "%8$15s |%9$20s |\n",
                true,words[0],words[1],words[2],words[3],monSal,words[5],"N/A","N/A");
    }
    private void formatCust(String words[]){
        System.out.format("|%1$8b | %2$5s |%3$15s |%4$15s |%5$10s |%6$15s |%7$30s |"
                + "%8$15s |%9$20s |\n",
                false,words[0],words[1],words[2],"N/A","N/A","N/A",words[3],words[4]);
    }
    private void formatBox(String words[]){
        
        int dimension = Integer.parseInt(words[3]);
        int volume = Integer.parseInt(words[4]);
        System.out.print(STARS);
        System.out.format("%1$11s |%2$9s |\n","Dimension","Volume");
        /*                                                               dimension & volume
        /*             words[0]          words[1]        words[2]        words[3,4]
        /*|     Type | Tracking Number | Specification | Mailing Class | extrainfo |*/
        System.out.format("|%1$9s |%2$16s |%3$14s |%4$14s |%5$11d |%6$9d |\n",
                "Box",words[0],words[1],words[2],dimension,volume);
        }
    private void formatDrum(String words[]){
        float diameter = Float.parseFloat(words[4]);
        System.out.print(STARS);
        System.out.format("%1$11s |%2$9s |\n","Material","Diameter");
        /*                                                               mats & diameter
        /*             words[0]          words[1]        words[2]        words[3,4]
        /*|     Type | Tracking Number | Specification | Mailing Class | extrainfo |*/
        System.out.format("|%1$9s |%2$16s |%3$14s |%4$14s |%5$11s |%6$9.2f |\n",
                "Drum",words[0],words[1],words[2],words[3],diameter);
    }
    private void formatEnvelope(String words[]){
        int height = Integer.parseInt(words[4]);
        int width = Integer.parseInt(words[5]);
        System.out.print(STARS);
        System.out.format("%1$11s |%2$9s |\n","Height","Width");
        /*                                                               height & width
        /*             words[0]          words[1]        words[2]        words[3,4]
        /*|     Type | Tracking Number | Specification | Mailing Class | extrainfo |*/
        System.out.format("|%1$9s |%2$16s |%3$14s |%4$14s |%5$11d |%6$9d |\n",
                "Envelope",words[0],words[1],words[2],height,width);
    }
    private void formatCrate(String words[]){
        float maxWeight = Float.parseFloat(words[3]);
        System.out.print(STARS);
        System.out.format("%1$11s |%2$9s |\n","Max Weight","Content");
        /*                                                               maxWeight & content
        /*             words[0]          words[1]        words[2]        words[3,4]
        /*|     Type | Tracking Number | Specification | Mailing Class | extrainfo |*/
        System.out.format("|%1$9s |%2$16s |%3$14s |%4$14s |%5$11.2f |%6$9s |\n",
                "Crate",words[0],words[1],words[2],maxWeight,words[4]);
    }
    
    private ArrayList<Package> pList = new ArrayList<>();
    private ArrayList<User> uList = new ArrayList<>();
    private ArrayList<Transaction> tList = new ArrayList<>();
    private final String DASHLINE = "------------------------------------------"
            + "--------------------------------------------";
    private final String DASHLINE_USER = "-------------------------------------"
            + "----------------------------------------------------------------"
            + "----------------------------------------------------";
    private final String DASHLINE_TRANS = "------------------------------------"
            + "---------------------------------------------------------";
    private final String STARS = "| ******** | *************** | ************* |"
                + " ************* |";
    private final String FILE = "DataBase.ser";
    private void printEmployeeUpdateMenu(){
        System.out.println("-----\t1. Update First and Last name.");
        System.out.println("-----\t2. Update SSN.");
        System.out.println("-----\t3. Update Monthly Salery.");
        System.out.println("-----\t4. Update Direct Deposit Account Number.");
        System.out.println("-----\t5. Return to Menu.");
    }
    private void printCustomerUpdateMenu(){
        System.out.println("-----\t1. Update First and Last name.");
        System.out.println("-----\t2. Update Phone Number.");
        System.out.println("-----\t3. Update Address.");
        System.out.println("-----\t4. Return to Menu.");
    }
    /*
    * Estimated Delivery time.
    */
    private final int FIRST_CLASS = 2;
    private final int PRIORITY = 1;
    private final int RETAIL = 3;
    private final int GROUND = 4;
    private final int METRO = 7;

    private final float FIRST_COST = 40/FIRST_CLASS;
    private final float PRIORITY_COST = 40/PRIORITY;
    private final float RETAIL_COST = 40/RETAIL;
    private final float GROUND_COST = 40/GROUND;
    private final float METRO_COST = 40/METRO;
}