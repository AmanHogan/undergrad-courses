/*
 * Aman Hogan-Bailey 1001830469
 */
package code2_1001830469;

import java.util.Scanner;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;

/*
 * @author Aman
 */

public class Code2_1001830469
{
    enum ACTION
    {
        DISPENSECHANGE, INSUFFICIENTCHANGE, INSUFFICIENTFUNDS, EXACTPAYMENT 
    }

    public static void main(String[] args) throws FileNotFoundException
    {
        
        
        String Filename = args[0].substring(args[0].indexOf('=')+1);
        int PENCIL_PRICE = Integer.parseInt(args[1].substring(args[1].indexOf('=')+1));
        
        
        ArrayList <String> colors = new ArrayList<>();
        
        //intializing arrays
        int changeLevelArray[] = {0};
        int inventoryLevelArray[] ={0};
        int arrayOfLevels[] = {0, 0};
        
        //initializing variables
        int changeLevel = 0;
        int inventoryLevel = 0;
        
        try
        {
            ReadFile(arrayOfLevels,Filename,colors);
        }
        catch(Exception E)
        {
            System.out.println("File not found. Exiting....");
            System.exit(0);
        }
        
        
        changeLevel =  arrayOfLevels[0];
        inventoryLevel = arrayOfLevels[1];
        
        changeLevelArray[0] = changeLevel;
        inventoryLevelArray[0] = inventoryLevel;
        
        System.out.println("\nWelcome to my Pencil Machine ");
        
        int menuChoice = PencilMenu(); //Calling menu
        
        String colorOfPencils = "";        
        
        //initializing variables
        int pencilQuantity;
        int payment;
        int pencilChangeBack;
          
        //creating scanner object
        Scanner input = new Scanner(System.in);
        
        //while 0 is not entered, continue program
        while(menuChoice != 0)
        {
            //if menuchoice is ... then ...
            switch(menuChoice)
            {
                case 1 :
                    if(inventoryLevel == 0)
                    {
                       System.out.println("\nThis Pencil Dispenser is out of inventory");
                    }
                    else
                    {
                        
                        System.out.print("\nThe pencil costs " + displayMoney(PENCIL_PRICE));
                        System.out.print("\nHow many pencils would you like to purchase? ");
                       
                        pencilQuantity = input.nextInt();
                       
                        while((pencilQuantity < 1) || (pencilQuantity > inventoryLevel))
                        {
                            System.out.print("Cannot sell that quantity of pencils. Please reenter quantity: ");
                            pencilQuantity = input.nextInt();
                        }
                        
                        System.out.println("\nYour total is " + displayMoney(PENCIL_PRICE * pencilQuantity));
                        System.out.print("\nEnter your payment (in cents) ");
                   
                        payment = input.nextInt();
                        
                        String changeArr[] = {""};
                        ACTION menuDecision = buyPencils(PENCIL_PRICE, payment, pencilQuantity, arrayOfLevels, changeArr);
                        
                        switch(menuDecision)
                        {
                            case DISPENSECHANGE :
                                pencilChangeBack = payment - (PENCIL_PRICE * pencilQuantity);
                                colorOfPencils = RandomColor(colors);
                                System.out.println("Here's your " + colorOfPencils + " pencils and your change of " + changeArr[0]);
                           
                                changeLevelArray[0] = arrayOfLevels[0];
                                inventoryLevelArray[0] = arrayOfLevels[1];
                                changeLevel = arrayOfLevels[0];
                                inventoryLevel = arrayOfLevels[1];
                                break;
                            case EXACTPAYMENT :
                                pencilChangeBack = payment - (PENCIL_PRICE * pencilQuantity);
                                colorOfPencils = RandomColor(colors);
                                System.out.println("Here's your "  + colorOfPencils + " pencils and your change of " + changeArr[0]);
                                System.out.println("Thank you for exact payment");//rubric criteria
                           
                                changeLevelArray[0] = arrayOfLevels[0];
                                inventoryLevelArray[0] = arrayOfLevels[1];
                                changeLevel = arrayOfLevels[0];
                                inventoryLevel = arrayOfLevels[1];
                                break;
                            case INSUFFICIENTCHANGE :
                                System.out.println("The Pencil Dispenser does not have enoguh change and cannot accept your payment.");
                                break;
                            case INSUFFICIENTFUNDS :
                                System.out.println("You did not enter a sufficeint payment. No pencils for you. ");
                                break;
                            default : 
                                System.out.println("Something unknown happened");
                        } 
                    }
                    break;
                case 2 :
                    System.out.println("\nThe current inventory level is " + inventoryLevel);
                    break;
                case 3 :
                    System.out.println("\nThe current change level is " + displayMoney(changeLevel));
                    break;
                default :
                    System.out.println("error");
            }
            menuChoice = PencilMenu();
        }
        PrintWriter outFile = new PrintWriter(Filename);
        
        outFile.printf("%d %d\n", changeLevel, inventoryLevel);
        
        for(String Read : colors)
        {
            outFile.print(Read + " ");
            
        }
        outFile.close();
        
        
    }
    
    
    public static int PencilMenu()
    {
        //creating scanner object
        Scanner in = new Scanner(System.in);
        
        //formatting output
        System.out.println("\nPlease choose from the following options\n\n");
        System.out.println("0. No pencils for me today ");
        System.out.println("1. Purchase pencils ");
        System.out.println("2. Check inventory level ");
        System.out.println("3. Check change level ");
        System.out.print("\nChoice: ");
        
        //gettign user input
        int userInput = 0;
        
        try
        {
            userInput = in.nextInt();
        }
        catch (Exception e)
        {
            userInput = -1;
            in.nextLine();
        }
        
        //if menu choice is invalid, prompt for choice again
        while((userInput > 3) || (userInput < 0))
        {
            System.out.println("Invalid menu option");
            System.out.println("\nPlease choose from the following options\n\n");
            System.out.println("0. No pencils for me today ");
            System.out.println("1. Purchase pencils ");
            System.out.println("2. Check inventory level ");
            System.out.println("3. Check change level ");
            System.out.print("\nChoice:  ");
            userInput = Integer.valueOf(in.nextLine());
            
            
        }
        return userInput;
    }
    
    public static String displayMoney(int MoneyValue)
    {
        String dollarAmount = String.valueOf(MoneyValue/100);
        String centAmount = String.valueOf(MoneyValue % 100);
        return "$" + dollarAmount + "." + (centAmount.length() == 1 ? "0" : "") + centAmount;
    }
    
    public static ACTION buyPencils(int priceOfPencil, int enteredPayment, int pencilsPurchased, int[]arr, String changeBack[])
    {
        int totalPencilCost = priceOfPencil * pencilsPurchased; 
        int changeLvl = arr[0];
        int inventoryLvl = arr[1];
        int pencilChangeBack = enteredPayment - (priceOfPencil * pencilsPurchased);
        
        ACTION decision = ACTION.DISPENSECHANGE;
        
        if(totalPencilCost == enteredPayment)
        {
            decision = ACTION.EXACTPAYMENT;
            arr[0] = changeLvl + enteredPayment;
            arr[1] = inventoryLvl - pencilsPurchased;
            changeBack[0] = displayMoney(pencilChangeBack);

        }
        
        else if(enteredPayment < totalPencilCost)
        {
            decision = ACTION.INSUFFICIENTFUNDS;    
        }
        
        else if(changeLvl < (enteredPayment - totalPencilCost))
        {
            decision = ACTION.INSUFFICIENTCHANGE;
        }
        
        else if(changeLvl > (enteredPayment - totalPencilCost))
        {
            decision = ACTION.DISPENSECHANGE;
            arr[0] = changeLvl - (enteredPayment - totalPencilCost);
            arr[1] = inventoryLvl - pencilsPurchased;
            changeBack[0] = displayMoney(pencilChangeBack);

        }
        return decision;
    }
    
    public static void ReadFile(int arrayOfLevel[], String FileName, ArrayList <String> Colors) throws FileNotFoundException
    {
       //Creating File Handle and Scanners//
        File fileHandle = new File(FileName);
        Scanner inline = new Scanner(fileHandle);
        
        //Getting First Line//
        String firstLine = inline.nextLine();

        //Spliting//
        String tokensfirstLine[] = firstLine.split("[ ]");
        arrayOfLevel[0] = Integer.valueOf(tokensfirstLine[0]);
        arrayOfLevel[1] = Integer.valueOf(tokensfirstLine[1]);
        
        //Getting Second Line//
        String secondLine = inline.nextLine();
        
        //parsing and setting values//
        String changelvl = tokensfirstLine[0];
        int inventorylvl = Integer.parseInt(tokensfirstLine[1]);
        
        String Array[] = secondLine.split("[ ]");
        
        //Enhanced for loop//
        for(String Read : Array)
        {
            Colors.add(Read);     
        }
        inline.close();
    }
    
    public static String RandomColor(ArrayList <String> colorList)
    {
        int length = colorList.size();
        Random r = new Random();
        int chosenNumber = r.nextInt(length);
        String chosenColor = colorList.get(chosenNumber);
        return chosenColor;
    }
}
