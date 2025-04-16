/*
 * Aman Hogan-Bailey 1001830469
 */
package code5_1001830469;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

/**
 *
 * @author Aman
 */
public class CandyHouse extends House
{
    public CandyHouse(String houseName, HashMap<String, Integer> CandyList)
    {
        super(houseName, CandyList);
    }
    
    public synchronized String ringDoorbell(TrickOrTreater TOT)
    {
        String Candy = "";
        TOT.addToPath("+");
        
        try
        {
            Thread.sleep(3000);
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }
        
        Random randomNum = new Random();
        int Answer = randomNum.nextInt(CandyList.size()) + 1;
        
        for (Map.Entry mapElement : CandyList.entrySet())
        {
            if((int)mapElement.getValue() == Answer)
            {
                Candy = (String)mapElement.getKey();
            }
        }
        return Candy;
    }
}
