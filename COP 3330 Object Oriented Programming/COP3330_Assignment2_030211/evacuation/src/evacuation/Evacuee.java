

package evacuation;
/** The Evacuee class contains the indivudual elements of each evacuee on the ship	 
 * @author Chet Michals
 */
public class Evacuee implements Comparable<Evacuee>
{

	//Private elements of the class
	private String firstName;	
	private String lastName;
	private Boolean isMale;
	private int age;
	private int income;
	
	/** Defalut constrctor for an Evacuee
	 * @param fname String with Evacuees first name
	 * @param lname String Evacuees last name
	 * @param male Bool indicating gender, true if male, false if female
	 * @param age Int with age
	 * @param income int with income ammount
	 * 
	 */
	public Evacuee(java.lang.String fname,
            java.lang.String lname,
            boolean male,
            int age,
            int income)
	{
		//Sets the passed into varables to the internal varables
		this.firstName = fname;
		this.lastName = lname;
		this.isMale = male;
		this.age = age;
		this.income = income;
	}
	
	/** Compares two Evacuees to each other for which has a higher priotriy
	 * @param e	The evacuee to compare to.		
	 * @return 	Returns an int, less then zero if the invoking evacuee has a higher pritory
	 * 			Greater then zero if the passed in evacuee has higher priotry, zero if they have the same priotry. 
	 */
	public int compareTo(Evacuee e)
	{
		if (this.age < 18 || e.age < 18) //If the ages are less then 18
		{
			if (this.age - e.age != 0) // If the ages aren't equal, just return A.age - B.age
			{
				return (this.age - e.age); 
			}
			else //Compare the names, if they are the same, just return 0
			{
				if (this.lastName.compareTo(e.lastName) != 0) return this.lastName.compareTo(e.lastName);
				if (this.firstName.compareTo(e.firstName) != 0) return this.firstName.compareTo(e.firstName);
				return 0;
			}
		}
		if (this.isMale != e.isMale) return this.isMale.compareTo(e.isMale); //Gender Check
		if (this.income != e.income) return (e.income - this.income); // Income Check
		if (this.lastName.compareTo(e.lastName) != 0) return this.lastName.compareTo(e.lastName); //Last name check
		if (this.firstName.compareTo(e.firstName) != 0) return this.firstName.compareTo(e.firstName); //First name check
		return 0; //All vales that are compared are the same
	}
	/** Outputs the information stored in the Evacuee in a human readable format
	 * 
	 */
	public java.lang.String toString()
	{
		StringBuilder output = new StringBuilder(); //Allows you to append things to the string builder to just output one long string
		
		output.append(this.firstName + " " + this.lastName + " (");
		if ( this.isMale == true ) output.append("Male, age ");
		else output.append("Female, age ");
		output.append(this.age + ", income $" + this.income + ")" );
		
		return output.toString();
	}
	
	
	public static void main(String[] args)
	{
		//Simple test to make sure class worked
		int number;
		Evacuee personA = new Evacuee("bob", "jake", true, 17, 9);
		Evacuee personB = new Evacuee("bomb", "jake", true, 16, 199);
		
		System.out.println(personA);
		System.out.println(personB);
		number = personA.compareTo(personB);
		System.out.println(number);
	}
	
}


