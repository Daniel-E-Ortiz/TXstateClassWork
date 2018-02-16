/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assignment2;
// probably dont need this?
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
        // Needs changing from file read to serialization reading.
        ShippingStore ss = new ShippingStore();
        Scanner sc = new Scanner(System.in);
        ss.openFile();
        String option;
        int choice;
        do{
            System.out.println("1. Show all existing package records in the"
                    + "database (sorted by tracking number).");
            System.out.println("2. Add new package record to the database.");
            System.out.println("3. Delete package record from a database.");
            System.out.println("4. Search for a package "
                    + "(given its tracking number).");
            System.out.println("5. Show a list of Users in the database.");
            System.out.println("6. Add new user to the database.");
            System.out.println("7. Update user info (given their id).");
            System.out.println("8. Complete a shipping transaction.");
            System.out.println("9. Show completed shipping transactions.");
            System.out.println("10. Exit program.");
            option = sc.nextLine();
            // input verification
            while(option.matches("^(\\D+\\d*)$")){
                System.out.println("Please input a number.");
                option = sc.nextLine();
            }
            choice = Integer.parseInt(option);
            switch(choice){
                case 1:
                    ss.showAllPackages();
                    break;
                case 2:
                    ss.addPackage();
                    break;
                case 3:
                    ss.delete();
                    break;
                case 4:
                    ss.search();
                    break;
                case 5:
                    ss.showAllUsers();
                    break;
                case 6:
                    ss.addNewUser();
                    break;
                case 7:
                    ss.updateUser();
                    break;
                case 8:
                    ss.completeShip();
                    break;
                case 9:
                    ss.showShipTrans();
                    break;
                case 10:
                    ss.quit();
                    break;
                default:
                    System.out.println("Incorrect choice: please type an input"
                            + " between 1-10");
            }
        }while (choice != 10);
    }
}
