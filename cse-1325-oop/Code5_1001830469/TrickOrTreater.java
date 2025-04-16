/*
 * Aman Hogan-Bailey 1001830469
 */
package code5_1001830469;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class TrickOrTreater implements Runnable
{
    public static int ImDone;
 
    private String name;
    private String path = ".";
    private ArrayList<House>ListOfHouses = new ArrayList<>();
    private HashMap<String, Integer>Bucket = new HashMap<>();
 
    /* constructor accepts a name and an ArrayList of Houses */
    TrickOrTreater(String name, ArrayList <House> ListOfHouses)
    {
        this.name = name;
        this.ListOfHouses = ListOfHouses;
    
    }
    
    /* instance method getName() that returns the name */
    public String getName()
    {
        return name;
    }
    
    /* instance method getPath() that return the path */
    public String getPath()
    {
        return path;
    }
    
    /* void instance method addToPath that accepts a string that it concatenates */
    /* onto instance variable path */ 
    public void addToPath(String concat)
    {
        path = path + concat;
    
    }
    
    /* private void instance method Walk that accepts a speed */
        /* for loop 10 times */
        /* concatenate . onto path */ 
        /* sleep for speed number of milliseconds */
    private void Walk(int speed)
    {
        for(int i = 0; i < 10; i++)
        {
            path = path + ".";
            try
            {
                Thread.sleep(speed);
            }
            catch (InterruptedException e)
            {
                Thread.currentThread().interrupt();    
            }
        }
    }
 
    public String printBucket()
    {
        String Candy = "";
        String BucketContents = "";
        int CandyCount = 0;
        
        BucketContents = String.format("%-10s - ", name);
        
        /* use an enhanced for loop to loop over Bucket – Week12 – Slides 72-76 */
        for(Map.Entry mapElement : Bucket.entrySet())
        {

            /* set Candy equal to the iterator’s key */
            Candy = (String)mapElement.getKey();
            
            /* set CandyCount equal to the iterator’s value */
            CandyCount = (int)mapElement.getValue();
            
            BucketContents += String.format("%15s %d ", Candy, CandyCount);
        }
        
        BucketContents += "\n";
        return BucketContents;
    }

    @Override
    public void run()
    {
        int speed = 0;
        int count = 0;
        
        String Candy = "";
        Random r = new Random();
        
        for(House it : ListOfHouses)
        {
            int Answer = r.nextInt(1500) + 1;
            
            speed = Answer;
            
            Walk(speed);
            
            Candy = it.ringDoorbell(this);
            
            if (Bucket.containsKey(Candy))
            {
                count = Bucket.get(Candy);
                Bucket.put(Candy, ++count);
            }
            else
            {
                Bucket.put(Candy, 1);
            }
        }
       
        synchronized(this)
        {
            ImDone = ImDone + 1;
        } 
    }
}
 
