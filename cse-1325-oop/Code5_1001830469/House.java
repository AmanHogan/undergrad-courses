/*
 * Aman Hogan-Bailey 1001830469
 */
package code5_1001830469;

import java.util.HashMap;

/**
 *
 * @author Aman
 */
public abstract class House
{
    private String houseName;
    public HashMap <String, Integer> CandyList = new HashMap<>();
    
    public House(String houseName, HashMap <String, Integer> CandyList)
    {
        this.houseName = houseName;
        this.CandyList = CandyList;
    }
    
    public abstract String ringDoorbell(TrickOrTreater thing);
  
}
