/*
 * Name: Chet Michals
 * Date: 02/09/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 1-B, Factors
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;


public class factors 
{
	public static void main(String[] args) throws FileNotFoundException 
	{
		int  x, i, j=0, k=0; 
	    int[] z;//Declares the array
	    
	    Scanner sc = new Scanner(System.in);//Makes scanner object
	    
	    System.out.println("Enter a filename to read from: ");
	    String filename = sc.next();
	    Scanner userFileScanner = new Scanner(new File(filename));
	    PrintStream fileWriter = new PrintStream(new File("outputFact.txt"));
	    while (userFileScanner.hasNextLine())
	    {
		    x= userFileScanner.nextInt();
		    z = new int [2048];//Allocates memory for array, and makes new array each time
		    j = 0;
		    for (i = 2; i < x; i++) //Loop puts all non-trivial factors in an the array x
		    {
		        if (x%i == 0)//Checks if i is a factor of x
		        {
		               z[j] = i; //puts i into array at spot j
		               z[j+1] = (x/i);// puts x/i into array at spot j+2
		               j+=2; //Increments j by 2
		        }
		    }
		    System.out.printf("%d has these factors: ",x);
		    fileWriter.printf("%d has these factors: ",x);
		    for (i = 2; i < x; i++) //Loop goes though array 'Z' 'X-2' times to identify every unique entry (Very slow, but I am feeling lazy)
		    {
		        for (k = 0; k <= j; k++) //Loop goes though array Z to compare values inside of it to i, to insure each value is only printed once
		            {
		                 if(z[k]==i)
		                 {
		                	 System.out.printf("%d ",z[k]);
		                	 fileWriter.printf("%d ",z[k]);
		                     k = j+1; //Gets out of the loop 
		                 }
		            }
		    }
		    System.out.printf("\n");
		    fileWriter.println("\n");
	    }
	}
}
