/*
 * Aman Hogan-Bailey 
   MAVID: 1001830469
 */
package code3_1001830469;

/**
 *
 * @author Aman
 */
public class CokeMachine
{
    public enum ACTION
    {
        DISPENSECHANGE, INSUFFICIENTCHANGE, INSUFFICIENTFUNDS, EXACTPAYMENT, NOINVENTORY 
    }
    
    private String machineName;
    private int changeLevel;
    private int maxChangeCapacity = 5000; 
    private int inventoryLevel;
    private int maxInventoryCapacity = 100;
    private int CokePrice;
    private int changeDispensed;
    private static int numberOfCokesSold = 0;
    
    public CokeMachine(String name, int cost, int change, int inventory)
    {
        machineName = name;
        CokePrice = cost;
        changeLevel = change;
        inventoryLevel = inventory;
    }
    
    public String getMachineName()
    {
        return machineName;
    }
    
    public int getChangeLevel()
    {
        return changeLevel;
    }
    
    public int getMaxChangeCapacity()
    {
        return maxChangeCapacity;
    }
    
    public int getInventoryLevel()
    {
        return inventoryLevel;
    }
    
    public int getMaxInventoryCapacity()
    {
        return maxInventoryCapacity;
    }
    
    public int getCokePrice()
    {
        return CokePrice;
    }
    
    public int getChangeDispensed()
    {
        return changeDispensed;
    }
    
    
    public int getNumberOfCokesSold()
    {
        return numberOfCokesSold;
    
    }
    
    public boolean incrementInventoryLevel(int amountToAdd)
    {
        if(maxInventoryCapacity >= inventoryLevel + amountToAdd)
        {
            inventoryLevel = inventoryLevel + amountToAdd;
            return true;
        }
        
        else
        {
            
            return false;
            
        }

    }
    
    public boolean incrementChangeLevel(int amountToAdd)
    {
        if(maxChangeCapacity >= changeLevel + amountToAdd)
        {
            changeLevel = changeLevel + amountToAdd;
            return true;
        }
        
        else
        {
            return false;
        
        }
    
    }
    
    public ACTION buyACoke(int payment)
    {
        //Initialize
        ACTION action = ACTION.NOINVENTORY;
        
        //Action to take
        if(payment == CokePrice)
        {
            action = ACTION.EXACTPAYMENT;
            changeLevel = changeLevel + CokePrice;
            inventoryLevel = inventoryLevel - 1;
            numberOfCokesSold = numberOfCokesSold + 1;
            
        }
        
        else if(payment < CokePrice)
        {
            action = ACTION.INSUFFICIENTFUNDS;    
        }
        
        else if(payment > changeLevel)
        {
            action = ACTION.INSUFFICIENTCHANGE;
        }
        
        else if(payment > CokePrice)
        {
            action = ACTION.DISPENSECHANGE;
            changeDispensed = (payment - CokePrice);
            changeLevel = changeLevel + CokePrice;
            inventoryLevel = inventoryLevel - 1;
            numberOfCokesSold = numberOfCokesSold + 1;
        }
        
        else if(payment > inventoryLevel)
        {
            action = ACTION.NOINVENTORY;
        }
        
        return action;
    }
    
    public String toString()
    {
        return String.format("%n%-25s%s%n%-25s%s%n%-25s%s%n%-25s%s%n%-25s%s%n%-25s%s%n%-25s%s%n%-25s%s%n%n","Machine Name", machineName, "Current Inventory Level", inventoryLevel, "Current Change Lvel",changeLevel, "Last Change Dispensed", changeDispensed, "Inventory Capacity", maxInventoryCapacity, "Change Capacity", maxChangeCapacity, "Coke Price", CokePrice, "Cokes Sold",numberOfCokesSold);
    }
    
}
