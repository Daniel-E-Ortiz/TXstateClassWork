/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment1;
import java.util.ArrayList;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.File;
import java.util.Scanner;
/**
 * @author Daniel Ortiz (deo15)
 * @version 9/18/2017
 */
public class ShippingStore {
    
    ShippingStore(String f) throws Exception{
        this.file = f;
    }
    /**
     * Opens File to read and include into Package List database.
     * @param file String for the name of the file, ex: "packages.txt".
     * @throws Exception 
     */
    public void openFile(String file) throws Exception{
        File dataFile = new File(file);
        if (!dataFile.exists())
        {
            System.out.println("File: " + file + " does not exist. "
                    + "Creating one now!\n");
            PrintWriter pw = new PrintWriter(file);
            pw.close();
            return;
        }
        Scanner orderSc = new Scanner(new FileReader(file));
        String line;
        while (orderSc.hasNextLine()){
            line = orderSc.nextLine();
            String []words = line.split(" ");
            //Package(String Tracking#, String Type, String Spec, 
            //      String Mailingclass, Float Weight, Int Volume);
            float weight = Float.parseFloat(words[4]);
            int volume = Integer.parseInt(words[5]);
            list.add(new Package(words[0],words[1],words[2],words[3],weight,
                    volume));
        }
        orderSc.close();
    }
    /**
     * Prints all Packages with formatting inside list.
     */
    public void showAll(){
        if(list.isEmpty()){
            System.out.println("\nPACKAGE RECORDS ARE EMPTY!\n");
            System.out.println("Would you like to add a new one? (y/n)");
            Scanner in = new Scanner(System.in);
            String answer = in.nextLine();
            if(answer.equalsIgnoreCase("Y")){
                add();
            }
            return;
        }
        printHeader();
        for(Package p:list){
            String line = p.getPackage();
            String []words = line.split(" ");
            float weight = Float.parseFloat(words[4]);
            int volume = Integer.parseInt(words[5]);
            formatMe(words[0],words[1],words[2],words[3],weight,volume);
        }
        System.out.println(DASHLINE);
    }
    /**
     *  Adds a new package object into the list and verifies input.
     */
    public void add(){
        /* 
        * defualt values are necessary because compiler thinks there may be 
        *   possibility they may not
        *   be initialized.
        */
        String track = "err", type = "err", spec = "err", Class = "err",
        weight = "0.00", volume = "000";
        float weightCorrected;
        int volumeCorrected;
        int result;
        Scanner in = new Scanner(System.in);
        int k;
        do{
            k=0;
            System.out.println("Type in order, your new Package with spaces.");
            System.out.println("Tracking#, Type, Secification, Class, Weight,"
                    + " Volume");
            System.out.println("Example: 632VR Letter n/a First 1.55 6");
            String line = in.nextLine();
            String []words = line.split(" ");
            for (String s:words){k++;}
            if(k==6){
                track = words[0];
                type = words[1];
                spec = words[2];
                Class = words[3];
                weight = words[4];
                volume = words[5];    
            }
            else{System.out.println("You must have exactly 6 elements for your"
                    + "Package! Please re-enter your package correctly.");
            }
        }while(k!=6);
        do{    
            result = verify(track,type,spec,Class,weight,volume);
            switch (result){
                case 0: // no errors
                    System.out.println("\nSuccessful!\n");
                    break;
                case 1: // tracking number incorrect
                    track = in.nextLine();
                    break;
                case 2: // type incorrect
                    type = in.nextLine();
                    break;
                case 3: // spec incorrect
                    spec = in.nextLine();
                    break;
                case 4: // Class incorrect
                    Class = in.nextLine();
                    break;
                case 5: // weight incorrect
                    weight = in.nextLine();
                    break;
                case 6: // volume incorrect
                    volume = in.nextLine();
                    break;
            }
        }while(result != 0);
        weightCorrected = Float.parseFloat(weight);
        volumeCorrected = Integer.parseInt(volume);
        list.add(new Package (track,type,spec,Class,weightCorrected,
                volumeCorrected));
    }
    
    /**
     * Searches and deletes a package with a specified tracking number.
     * Prints "REMOVE SUCCESSFUL." or "ERROR: TRACKING NUMBER NOT FOUND.".
     */
    public void delete(){
        String track;
        System.out.println("Type in the Tracking# you want removed.");
        Scanner in = new Scanner(System.in);
        track = in.nextLine();
        boolean removeSuccess = false;
        int index = 0;
        while (index < list.size())
        {
            if(list.get(index).getTrack().equalsIgnoreCase(track)){
                  list.remove(index);
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
        
        for(Package p:list){
            if(p.getTrack().equalsIgnoreCase(track)){
                found = true;
                String line = p.getPackage();
                String []words = line.split(" ");
                float weight = Float.parseFloat(words[4]);
                int volume = Integer.parseInt(words[5]);
                printHeader();
                formatMe(words[0],words[1],words[2],words[3],weight,volume);
                break;
            }
        }
        System.out.println(DASHLINE);
        if(!found){
            System.out.println("TRACKING NUMBER NOT FOUND!");
        }
    }
    /**
     *  Displays the packages within a weight range.
     *  Asks user input for lowest and highest weights.
     */
    public void showWeight(){
        float low,high;
        Scanner in = new Scanner(System.in);
        System.out.println("Please input your the lowest weight.");
        low = in.nextFloat();
        System.out.println("Please input your the highest weight.");
        high = in.nextFloat();
        printHeader();
        for(Package p:list){
            if(p.getWeight() >= low && p.getWeight() <= high){
                String line = p.getPackage();
                String []words = line.split(" ");
                float weight = Float.parseFloat(words[4]);
                int volume = Integer.parseInt(words[5]);
                formatMe(words[0],words[1],words[2],words[3],weight,volume);
            }
        }
        System.out.println(DASHLINE);
       
    }
    /**
     * Writes to File.
     * @param file File being written to.
     * @throws Exception 
     */
    public void quit(String file) throws Exception{
        PrintWriter pw = new PrintWriter(file);
        for(Package p:list){
            pw.println(p.getPackage());
        }
        pw.close();
        System.out.println("Saving To file " + file + "... GoodBye!\n");
    }
    /**
     * Verifies all input values before being added to list. 
     * @param track Tracking Number. ex: ABC12
     * @param type Type of Package. ex: Letter
     * @param spec Specification of the Package. ex: Fragile
     * @param Class ex: First
     * @param weight in ounces written as a float value.
     * @param volume (L x W x H) integer value.
     * @return ERROR_CODE(0-6) 0:No errors, 1:track error, 2:type error, 3:spec 
     * error, 4:Class error, 5:weight error, 6:volume error.
     */
    private int verify(String track,String type,String spec,String Class, 
            String weight,String volume){
        // NO 2 PACKAGES CAN HAVE SAME TRACKING NUMBER.
        for(Package p:list){
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
            System.out.println("Must be 5 characters in length.");
            System.out.println("Example: ABC12 or 12ABC or AB12C.");
            System.out.println(DASHLINE);
            return 1;
        }
        // string "type" verification, returns 2 if bad.
        if (!type.matches("^(Postcard|Letter|Envelope|Packet|Box|Crate|Drum|"
                + "Roll|Tube)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Type: " + type);
            System.out.println("Please input correct Type!");
            System.out.println("Must be one the following:");
            System.out.println("Postcard, Letter, Envelope, Packet, Box, Crate,"
                    + " Drum, Roll, Tube");
            System.out.println(DASHLINE);
            return 2;
        }
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
            return 3;
        }
        // string "Classification" validation, returns 4 if bad.
        // must be one of the following...
        // First-Class, Priority, Retail, Ground, or Metro.
        if (!Class.matches("^(First-Class|Priority|Retail|Ground|Metro)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Class: " + Class);
            System.out.println("Please input correct Class!");
            System.out.println("Must be one of the following:");
            System.out.println("First-Class, Priority, Retail, Ground, Metro");
            System.out.println(DASHLINE);
            return 4;
        }
        // float "Weight" validation, returns 5 if bad.
        // must be a digit input separated by a decimal or Integer.
        if (!weight.matches("^(\\d+)(\\.?)(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Weight: " + weight);
            System.out.println("Please input correct Weight in ounces!");
            System.out.println("Must be a digit with or without a decimal point"
                    + ".");
            System.out.println("Example: 1, 1.0, 2.00.");
            System.out.println(DASHLINE);
            return 5;
        }
        // Integer Volume validation, returns 6 if bad.
        // must be an integer.
        if (!volume.matches("^(\\d+)$")){
            System.out.println(DASHLINE);
            System.out.println("ERROR: Incorrect Volume: " + volume);
            System.out.println("Please input correct Volume!");
            System.out.println("Must be a digit.");
            System.out.println("Example: 1, 2, 30, 45.");
            System.out.println(DASHLINE);
            return 6;
        }
        // If no problems return 0 to indicate correct Package!
        return 0;
    }
    /**
     * Verifies the tracking number only.
     * @param track Tracking Number to be checked.
     * @return (0 or 1) 0:Good tracking number, 1:Bad tracking number 
     */
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
    private void printHeader(){
        System.out.println(DASHLINE);
        System.out.format("| %1$10s |%2$9s |%3$14s |%4$12s |%5$7s |%6$7s |\n", 
                "TRACKING #","TYPE","SPECIFICATION","CLASS","WEIGHT","VOLUME");
        System.out.println(DASHLINE);
    }
    private void formatMe(String tr, String ty, String spec, String cl, float w,
            int v){
        System.out.format("|%1$11s |%2$9s |%3$14s |%4$12s |%5$7.2f |%6$7d |\n",
                tr,ty,spec,cl,w,v);
    }
    /**
     * Getter method to return the String "file" to be used in other methods.
     * @return file name. ex: "packages.txt"
     */
    public String getFile(){return file;}
    private ArrayList<Package> list = new ArrayList<>();
    private final String DASHLINE = "------------------------------------------"
            + "------------------------------";
    private String file;
    
    
}
    

