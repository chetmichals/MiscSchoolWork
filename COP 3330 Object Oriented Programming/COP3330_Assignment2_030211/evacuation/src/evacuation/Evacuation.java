package evacuation;

import java.util.Scanner;
import evacuation.EvacueeQueue;
/** The Evacuataion class is the main class of the program, driving the evcauation process
 * @author Chet Michals
 */
public class Evacuation {
	/** Prints the basic menu which list the selectable options
	 * 
	 */
	public static void PrintMenu()
	{
		System.out.println("1) Add an evacuee to the waiting list");
		System.out.println("2) Release a lifeboat");
		System.out.println("0) Exit");
	}
	
	public static void main(String[] args)
	{
		int choice = -1;
		int boatSize;
		EvacueeQueue list = new EvacueeQueue();
		
		
		Scanner input = new Scanner(System.in);
		while (choice != 0)
		{
			PrintMenu();
			choice = input.nextInt();
			if (choice != 0 && choice != 1 && choice != 2) {System.out.println("Invalid choice"); continue;} //continue restarts while loop
			if (choice == 1) list.add(GetPerson()); //Get a person's info and pass it to the list
			if (choice == 2) 
			{
				System.out.println("How many people can fit on the lifeboat?");
				boatSize = input.nextInt();
				ReleaseBoat(boatSize, list);
			}
		}
		FairWell(list);
	}

/** Prints the closing statemetns, such as who is left on the ship
 * 
 * @param list An EvacueeQueue object containing the rest of the passangers on the ship 
 */
	private static void FairWell(EvacueeQueue list) 
	{
		Evacuee tempMan;
		tempMan = list.getNextEvacuee();
		System.out.println("Thank you for acctually using the evacuation assistant. Hope your accounted for the crew!");
		if (tempMan != null) System.out.println("Hope the following people are strong swimmers!");
		else System.out.println("Hey, everyone fit! No costly settlements for us boys!");
		while (tempMan != null)
		{
			System.out.println(tempMan);
			tempMan = list.getNextEvacuee();
		}	
	}

/** Pops off a number of people from the passed in list and places them in a boat
 * 
 * @param k The number of people who can fit on the boat 
 * @param list The list containing who is in line to get on a boat
 */
	public static void ReleaseBoat(int k, EvacueeQueue list) 
	{
		Evacuee tempMan;
		System.out.println("Let these people on to the boat:");
		for (int i = 0; i < k; i++)
		{
			tempMan = list.getNextEvacuee();
			if (tempMan == null){System.out.println("There are " + (k-i) + " empty seats left."); i=k; break;}
			System.out.println(tempMan);
		}
	}

/** Gets the information for an Evcuee and creates and Evcuee object with that information
 * 
 * @return An Evcuee to be put onto the EvcueeQueue
 */
	public static Evacuee GetPerson() 
	{
		String firstName;	
		String lastName;
		int tempMale;
		int age;
		int income;
		Boolean isMale = false;
		
		Scanner input = new Scanner(System.in);
		
		System.out.println("What is the evacuee’s last name?");
		lastName = input.next();
		
		System.out.println("What is the evacuee’s first name?");
		firstName = input.next();
		
		System.out.println("What is the evacuee’s gender? 1) Male, 2) Female.");
		tempMale = input.nextInt();
		
		System.out.println("What is the evacuee’s age?");
		age = input.nextInt();
		
		System.out.println("What is the evacuee’s income in USD?");
		income = input.nextInt();
		
		if (tempMale == 1) isMale = true;
		Evacuee currentPerson = new Evacuee(firstName, lastName, isMale, age, income);
		System.out.println(currentPerson);
		
		return currentPerson;
	}
}
