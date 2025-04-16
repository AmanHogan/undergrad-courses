// Aman Hogan-Bailey
// 1001830469
// Version 14.0.2 2020-07-14
// Ubuntu (20.04.1 LTS (Focal Fossa)) [CSE 1320 Virtual Machine]


package ajh0469_lab01;

import java.io.File;

public class Ajh0469_lab01
{    
    public static void main(String[] args)
    {
        //initializing sum and starting path
        int sum = 0;
        String initialPath = ".";
        
        //calling function that will calculate total filze size in directory and subdirectories
        sum = dirspace(initialPath);
        System.out.println(sum);
    }
    
    //Function finds the total file and directory size in current directory
    //returns size of entry
    public static int dirspace(String path)
    {
        //initializing sum
        int sum = 0;
    
        //initializing am array that will hold the info of found entries
        File[] entries = null;
        
        //calling function that will return an array of entries
        entries = getEntries(path);
        
        //iterate though the list and for each entry...
        for(File iterator: entries)
        {
            //if entry is a directiry, call the function recursively
            if(iterator.isDirectory())
            {
                sum = sum + dirspace(iterator.getAbsolutePath());
            }
            
            //if entry is a file, get size of file
            else
            {
                sum = sum + (int)iterator.length();
            }
        }
        return sum;
    }
    
    //function gets an array of entries
    //function returns a list of entries
    public static File[] getEntries(String path)
    {
        //creating a filehandle from the current path
        File parent = new File(path);
        
        //returning an array of entries in the current directory
        File[] L = parent.listFiles();
        return L;
    }
}