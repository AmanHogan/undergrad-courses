/*
 * Aman Hogan-Bailey 
   MAV ID: 1001830469
 */
package code3_1001830469;
import java.util.Scanner;

public class Code3_1001830469
{
 
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args)
    {   
        
        CokeMachine MyCokeMachine = new CokeMachine("CSE 1325 Coke Machine", 50, 500, 100);
        int menuChoice = CokeMenu(MyCokeMachine.getMachineName());        
        CokeMachine.ACTION action;
        
        //variables
        int payment = 0;
        
        while(menuChoice != 0)
        {
            switch(menuChoice)
            {
                case 1 :
                    
                    System.out.println("A coke costs " + displayMoney(MyCokeMachine.getCokePrice()));
                    System.out.print("\nInsert payment ");
                    
                    Scanner in = new Scanner(System.in);
                    payment = in.nextInt();
                    
                    //Coding requirement #2
                    action = MyCokeMachine.buyACoke(payment);
                    
                    //Case changes depening on return value of 'action'
                    switch(action)
                    {
                        case DISPENSECHANGE :
                            System.out.println("\nHere's your Coke and your change of " + displayMoney(MyCokeMachine.getChangeDispensed()) + "\n\n");
                            break;
                        case INSUFFICIENTCHANGE :
                            System.out.println("\n\nUnable to sell a Coke - call 1800WEDONTCARE to register a complaint...returning your payment.\n\n");
                            break;
                        case INSUFFICIENTFUNDS :
                            System.out.println("\n\nInsufficient payment...returning your payment\n\n");
                            break;
                        case EXACTPAYMENT :
                            System.out.println("\n\nThank you for your exact payment.\nHere's your coke.\n\n");
                            break;
                        case NOINVENTORY :
                            System.out.println("\n\nUnable to sell a Coke - call 1800WEDONTCARE to register a complaint...returning your payment.\n\n");
                            break;
                        default :
                            System.out.println("\n\nSomething unknonwn happened.\n\n");
                    }
                    break;
                    
                //Restocking Machine
                case 2 :
                    System.out.printf("How much product are you adding to the machine? ");
                    
                    int amountToAdd = 0;
                    Scanner inputInventory = new Scanner(System.in);
                    amountToAdd = inputInventory.nextInt();
                    
                    //If TRUE increment inventory
                    if(MyCokeMachine.incrementInventoryLevel(amountToAdd) == true)
                    {
                        System.out.printf("\nThe Coke Machine has been restocked.\n\nYour inventory level is %d\n\n", MyCokeMachine.getInventoryLevel());
                    }
                    
                    //If false, exceeded max capacity
                    else if(MyCokeMachine.incrementInventoryLevel(amountToAdd) == false)
                    {
                        System.out.printf("\nYou have exceeded your machine's max capacity - no inventory was added\n\nYour inventory level is %d\n\n", MyCokeMachine.getInventoryLevel());
                    }
                    
                    //In case unknown error
                    else
                    {
                        System.out.printf("Error: Exceeds Coke Machine capacity. Current Capacity: %d\n", MyCokeMachine.getInventoryLevel());
                    }
                    break;
                    
                //Adding change to Coke Machine
                case 3 :
                    System.out.printf("\nHow much change will be added to the machine ");
                    
                    int changeToAdd = 0;
                    Scanner inputChange = new Scanner(System.in);
                    changeToAdd = inputChange.nextInt();
                    
                    //If TRUE icrement change level 
                    if(MyCokeMachine.incrementChangeLevel(changeToAdd) == true)
                    {
                        System.out.printf("\nYour change level has been updated\n\n\nYour change level is %s with a max capacity of %s\n\n", displayMoney(MyCokeMachine.getChangeLevel()), displayMoney(MyCokeMachine.getMaxChangeCapacity()));
                    }
                    
                    //If FALSE, exceeded capacity
                    else if(MyCokeMachine.incrementChangeLevel(changeToAdd) == false)
                    {
                        System.out.printf("\n\nYou exceeded your mahine's max change capacity - no chnage added\n\nYour change level is %s with a max capacity of %s\n\n", displayMoney(MyCokeMachine.getChangeLevel()), displayMoney(MyCokeMachine.getMaxChangeCapacity()));
                    }
                    
                    //In case unknown error
                    else
                    {
                        System.out.printf("Error: Exceeds Coke Machine capacity. Current Change Level: %s\n", displayMoney(MyCokeMachine.getChangeLevel()));
                    }
                     
                    break;
                    
                //Prints details of Coke Machine
                case 4 :
                    System.out.println(MyCokeMachine);
                    break;
                default :
                    System.out.println("Something Unknwon happened");
            }
            menuChoice = CokeMenu(MyCokeMachine.getMachineName());  
        }
        
        //If user purchased at least 1 coke, print thank you
        if(MyCokeMachine.getNumberOfCokesSold() >= 1)
        {
            System.out.println("Bye - enjoy your Coke");
        }
        
        //If they did not buy some coke
        else
        {
            System.out.println("Are you sure you aren't really THIRSTY amd need a Coke?");
        }
    }
    
    public static int CokeMenu(String name)
    {
        //Scanner
        Scanner in = new Scanner(System.in);
        
        //Format
        System.out.println(name + "\n");
        System.out.println("0. Walk away");
        System.out.println("1. Buy a Coke");
        System.out.println("2. Restock Machine");
        System.out.println("3. Add change");
        System.out.println("4. Display Machine Info");
        System.out.printf("\nChoice? ");
        
        //User Input
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
        while((userInput > 4) || (userInput < 0))
        {
            System.out.println("Invalid menu option");
            System.out.println("\nPlease choose from the following options\n\n");
            System.out.println("0.\tWalk away");
            System.out.println("1.\tBuy a Coke");
            System.out.println("2.\tRestock Machine");
            System.out.println("3.\tAdd change");
            System.out.println("4.\tDisplay Machine Info");
            System.out.printf("\nChoice? ");
            
            userInput = Integer.valueOf(in.next());
        }
        return userInput;
    }
    
    public static String displayMoney(int MoneyValue)
    {
        String dollarAmount = String.valueOf(MoneyValue/100);
        String centAmount = String.valueOf(MoneyValue % 100);
        return "$" + dollarAmount + "." + (centAmount.length() == 1 ? "0" : "") + centAmount;
    }
}
