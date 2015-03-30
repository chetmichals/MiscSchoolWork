/*
 * Name: Chet Michals
 * Date: 02/09/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 1-A, Manic Gamer
 */
import java.util.Scanner;


public class Billy {
	public static void main(String[] args) 
	{
		// Create a Scanner for user input.
		Scanner sc = new Scanner(System.in);//Scanner for user input
	    int allow = 0, cost = 0, weeks = 0, games = 0, money = 0, i = 0, z = 0;
	    // Ask for input and pass it to varables 
	    System.out.println("Please enter Billy's weekly allowance in dollars: ");
	    allow = sc.nextInt();
	    System.out.println("Please enter the cost of a video game in dollars: ");
	    cost = sc.nextInt();
	    System.out.println("Please enter the number of weeks to follow Billy's spending habits: ");
	    weeks = sc.nextInt();

	    for (i = 0; i < weeks; i++) //Loops though getting allowance each weak  
	    {
	        money += allow;
	        System.out.printf("After week %d", (i+1));
	        if ((money/cost)>0)//Check to see if there is enough money for a game
	        {
	        	System.out.printf(" Billy has $%d, enough to get a game! Billy now has ", money);
	              z = money/cost;
	              money-=(cost*z);
	              games+=z;
	              System.out.printf("%d games and $%d\n", games, money);
	        }
	        else
	        {
	        	System.out.printf(" Billy can't buy a game. He has $%d and %d games\n", money , games);
	        }
	    }
	    System.out.printf("\nAfter all %d weeks, Billy has $%d and %d games!\n",weeks,money,games);
	}
}
