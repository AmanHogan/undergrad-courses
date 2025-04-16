/*
 * Aman Hogan-Bailey 1001830469
 */
package code5_1001830469;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Code5_1001830469
{
    public static void main(String[] args)
    {
        String Candytxt = "";
        String Housetxt = "";
        String TOTtxt = "";
        
        if(args.length != 3)
        {
            System.out.println("Missing command line paramaters - - ");
            System.exit(0);
        }
        
        else
        {
            Candytxt = args[0].substring(args[0].indexOf('=')+1);
            Housetxt = args[1].substring(args[1].indexOf('=')+1);
            TOTtxt = args[2].substring(args[2].indexOf('=')+1);
        }
        
        HashMap <String, Integer> candyMap = new HashMap<>();
        CreateCandyList(Candytxt, candyMap);
        
        ArrayList <House> Houses = new ArrayList<>();
        String HousesString = CreateHouses(Housetxt, Houses, candyMap);
      
        ArrayList <TrickOrTreater> TOT = new ArrayList<>();
        CreateTOTs(TOTtxt, TOT, Houses);
        
        ExecutorService executorService = Executors.newCachedThreadPool();

        for(TrickOrTreater it : TOT) 
        {
            executorService.execute(it); // where it is iterator over the ArrayList
        }
        
        TextAreaFrame TAF = new TextAreaFrame();
        TAF.setVisible(true);
        String ScreenOutput = "";
        while (TrickOrTreater.ImDone != TOT.size())
        {
            ScreenOutput = String.format("%s", HousesString);
            for(TrickOrTreater it : TOT)
            {
                ScreenOutput += String.format("%s%s\n", it.getPath(), it.getName());
            }
            TAF.textArea.setText(ScreenOutput);
        }
        
        executorService.shutdown();
        String BucketContents = "Candy!!\n\n";
        
        for(TrickOrTreater it : TOT) 
        {
            BucketContents = BucketContents + it.printBucket(); // where it is iterator over the ArrayList
        }
        TAF.textArea.setText(BucketContents);
    }
    
    public static void CreateCandyList(String Candytxt, HashMap <String, Integer> candyMap)
    {
        /* Set up File and Scanner and declare String array */
        File fileHandle = new File(Candytxt);
        Scanner FileReader = null;
        String FileLine[];
        
        /* Open file and catch exception if needed. Exit if file does not open */
        try
        {
            FileReader = new Scanner(fileHandle);
        }
        
        catch(FileNotFoundException e)
        {
            System.out.printf("%s file name does not exist...exiting", Candytxt);
            System.exit(0);
        }
        
        /* while reading the file*/
        while(FileReader.hasNextLine())
        {
            /* use split() to put file line into String array */
            FileLine = FileReader.nextLine().split("[|]");
            String candyName = FileLine[0];
            int candyValue = Integer.valueOf(FileLine[1]);
            
            /* Use map method put() to add (candyname, candynumber) to HashMap */
            candyMap.put(candyName, candyValue);
        }
        /* close the file */
        FileReader.close();
    }
    
    public static String CreateHouses (String Housetxt, ArrayList <House> Houses, HashMap <String, Integer> CandyList)
    {
        /* Create a string named HouseHeading and set it equal to " " */
        String HouseHeading = "           ";
        String FileLine = "";
        
        /* Set up File and Scanner */
        File fileHandle = new File(Housetxt);
        Scanner FileReader = null;
        
        try
        {
            FileReader = new Scanner(fileHandle);
        }
        
        catch(FileNotFoundException e)
        {
            System.out.printf("%s file name does not exist...exiting", Housetxt);
            System.exit(0);
        }
        
        Random r = new Random();
        
        /* while reading the file */
        while(FileReader.hasNextLine())
        {
            FileLine = FileReader.nextLine();
            HouseHeading = HouseHeading + FileLine;
            for (int i = 0; i < 11-FileLine.length(); i++)
            {
                HouseHeading += " ";
            }
        
            int Answer = r.nextInt(3);
            
            if (Answer == 0)
            {
                CandyHouse candyHouse = new CandyHouse(FileLine, CandyList);
                Houses.add(candyHouse);
            }
            
            else
            {
                ToothbrushHouse toothbrushbouse = new ToothbrushHouse(FileLine, CandyList);
                Houses.add(toothbrushbouse);
            }
     
        }
        FileReader.close();
        HouseHeading = HouseHeading + "\n\n";
        return HouseHeading;
    }
    
    public static void CreateTOTs(String TOTtxt, ArrayList <TrickOrTreater> TOT, ArrayList <House> Houses)
    {
        File fileHandle = new File(TOTtxt);
        Scanner FileReader = null;
        String FileLine = "";
        
        try
        {
            FileReader = new Scanner(fileHandle);
        }
        
        catch(FileNotFoundException e)
        {
            System.out.printf("%s file name does not exist...exiting", TOTtxt);
            System.exit(0);
        }
        
        while(FileReader.hasNextLine())
        {
            FileLine = FileReader.nextLine();
            TrickOrTreater newTOT = new TrickOrTreater(FileLine, Houses);
            TOT.add(newTOT);
        }
        FileReader.close();
    }
}
