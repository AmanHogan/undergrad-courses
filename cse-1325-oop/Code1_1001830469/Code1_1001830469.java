/*
    Aman Hogan-Bailey
    MAV ID: 1001830469
 */
package codingassignment1;

import java.util.Scanner;

public class CodingAssignment1
{
    enum ACTION
    {
        DISPENSECHANGE, INSUFFICIENTCHANGE, INSUFFICIENTFUNDS, EXACTPAYMENT 
    }
  
    public static void main(String[] args)
    {
        System.out.println("\nWelcome to my Pencil Machine ");
        
        final int PENCIL_PRICE = 60; //Constant price for pencil
        int menuChoice = PencilMenu(); //Calling menu
        
        //intializing arrays
        int changeLevelArray[] = {500};
        int inventoryLevelArray[] ={100};
        int arrayOfLevels[] = {0, 0};
        
        //initializing variables
        int changeLevel = changeLevelArray[0];
        int inventoryLevel = inventoryLevelArray[0];
        
        //setting array of levels to start amount
        arrayOfLevels[0] = changeLevel;
        arrayOfLevels[1] = inventoryLevel;
        
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
                        
                        ACTION menuDecision = buyPencils(PENCIL_PRICE, payment, pencilQuantity, arrayOfLevels);
                        
                        switch(menuDecision)
                        {
                            case DISPENSECHANGE :
                                pencilChangeBack = payment - (PENCIL_PRICE * pencilQuantity);
                                System.out.println("Here's your pencils and your change of " + displayMoney(pencilChangeBack));
                           
                                changeLevelArray[0] = arrayOfLevels[0];
                                inventoryLevelArray[0] = arrayOfLevels[1];
                                changeLevel = arrayOfLevels[0];
                                inventoryLevel = arrayOfLevels[1];
                                break;
                            case EXACTPAYMENT :
                                pencilChangeBack = payment - (PENCIL_PRICE * pencilQuantity);
                                System.out.println("Here's your pencils and your change of " + displayMoney(pencilChangeBack));
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
        int userInput = in.nextInt();
        
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
            
            userInput = in.nextInt();
        }
        return userInput;
    }
    
    public static String displayMoney(int MoneyValue)
    {
        String dollarAmount = String.valueOf(MoneyValue/100);
        String centAmount = String.valueOf(MoneyValue % 100);
        return "$" + dollarAmount + "." + (centAmount.length() == 1 ? "0" : "") + centAmount;
    }
    
    public static ACTION buyPencils(int priceOfPencil, int enteredPayment, int pencilsPurchased, int[]arr)
    {
        int totalPencilCost = priceOfPencil * pencilsPurchased; 
        int changeLvl = arr[0];
        int inventoryLvl = arr[1];
        
        ACTION decision = ACTION.DISPENSECHANGE;
        
        if(totalPencilCost == enteredPayment)
        {
            decision = ACTION.EXACTPAYMENT;
            arr[0] = changeLvl + enteredPayment;
            arr[1] = inventoryLvl - pencilsPurchased;
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
        }
        return decision;
    }
}
