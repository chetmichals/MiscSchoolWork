/*
 * Name: Chet Michals
 * Date: 02/09/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 1-C, Anagrams
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.StringTokenizer;


public class anagrams 
{
	public static void main(String[] args) throws FileNotFoundException 
	{
	    String word1, word2;
	    int x, i, k, MatchFound = 0;
	    int count = 0;
	    Scanner sc = new Scanner(System.in);//Makes scanner object
	    
	    //When changing to java, switch with file handlers and one more loop
	    
	    System.out.println("Enter a filename to read from: ");
	    String filename = sc.next();
	    Scanner userFileScanner = new Scanner(new File(filename));
	    PrintStream fileWriter = new PrintStream(new File("outputAna.txt"));

//		Code for Manual entry of words
//	    System.out.println("Please type in word 1: ");
//	    word1 = sc.nextLine();
//	    System.out.println("Please type in word 2: ");
//	    word2 = sc.nextLine();
	    
	    while (userFileScanner.hasNextLine())
	    {
	    	count++; 
	    	MatchFound = 0;
	    	StringTokenizer st = new StringTokenizer(userFileScanner.nextLine()); //Tokenizes text file. Note, does not like new lines starting the file
	    	word1 = st.nextElement().toString(); //Places first token into word 1
	    	word2 = st.nextElement().toString(); //Places second token into word 2
		    if (word1.length() != word2.length() ) fileWriter.println("Case " +count + ": Not Anagrams :("); //Simple Anagram check, if they aren't the same length they can't be anagrams
		    else 
		    {
		         x = word1.length() ;
		         for (i = 0; i < x; i++) //Goes though the two words letter by letter to compare 
		         {
		             for (k = 0; k < x; k++)//Cycles though the letters of word two to compare a single letter in word one to all the letters in word two
		             {
		                 if (word1.charAt(i) == word2.charAt(k))
		                 {
		                	word2 =  word2.replaceFirst(Character.toString(word2.charAt(k)),Character.toString('~'));//Changes already "Found" letters with Tilde (No one uses those), god damn was this a pain to translate from C++,  "word2[k] = '~';" is so much cleaner
		                    k = x; //Gets out of k loop, which causes i loop to increment
		                    MatchFound = 1;//Sets match found to 1. 
		                 }
		                 else 
		                 {
		                	 MatchFound = 0;//Sets match found to 0.               	 
		                 }
		             }
		             if (MatchFound == 0) //Fixes bug where if the last letter matched, would give a false positive
		             {
		            	 fileWriter.println("Case " +count + ": Not Anagrams :(");
		            	 break;
		             }
		         }
		    }
		    if (MatchFound == 1) fileWriter.println("Case " +count + ": Anagrams!");
		}
	}
}
