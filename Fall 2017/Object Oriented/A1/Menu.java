/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment1;
import java.util.Scanner;

 /**
 * @author Daniel Ortiz (deo15)
 * @version 9/18/2017
 */
public class Menu {

    /** 
     * main controls the menu for the program.
     * @param args the command line arguments
     * @throws java.lang.Exception
     */
    public static void main(String[] args) throws Exception{
        ShippingStore ss = new ShippingStore("packages.txt");
        ss.openFile(ss.getFile());
        Scanner sc = new Scanner(System.in);
        String option;
        int choice;
        do{
            System.out.println("1. Show all existing package records in the "
                    + "database (in any order).");
            System.out.println("2. Add new package record to the database.");
            System.out.println("3. Delete package record from a database.");
            System.out.println("4. Search for a package "
                    + "(given its tracking number).");
            System.out.println("5. Show a list of packages within a given "
                    + "weight range.");
            System.out.println("6. Exit program.");
            option = sc.nextLine();
            while(option.matches("^(\\D+\\d*)$")){
                System.out.println("Please input a number.");
                option = sc.nextLine();
            }
            choice = Integer.parseInt(option);
            switch(choice){
                case 1:
                    ss.showAll();
                    break;
                case 2:
                    ss.add();
                    break;
                case 3:
                    ss.delete();
                    break;
                case 4:
                    ss.search();
                    break;
                case 5:
                    ss.showWeight();
                    break;
                case 6:
                    ss.quit(ss.getFile());
                    break;
                default:    
                    System.out.println("Incorrect choice: please type an input"
                            + " between 1-6");
            }
        }while (choice != 6);
    }
}
