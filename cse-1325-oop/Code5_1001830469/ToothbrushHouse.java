/*
 * Aman Hogan-Bailey 1001830469
 */
package code5_1001830469;

import java.util.HashMap;

/**
 *
 * @author Aman
 */
public class ToothbrushHouse extends House
{
    
    public ToothbrushHouse(String houseName, HashMap<String, Integer> CandyList)
    {
        super(houseName, CandyList);
    }

    public synchronized String ringDoorbell(TrickOrTreater TOT)
    {
        String Toothbrush = "";
        TOT.addToPath("-");
        
        try
        {
            Thread.sleep(3000);
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }
        
        return "Toothbrush";
    }
}
