/*
 * Name: Chet Michals
 * Date: 03/28/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 3, Comets
 */

package comets;
/**
 * Class for laser shot by ship
 * @author Chet Michals
 *
 */
public class Shot extends SpaceObject{

	protected int age = 0;
	
	private Shot(double xPos, double yPos, double xVel, double yVel,
			double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}
	/**
	 * Constructor for a shot, has radius of 3
	 * @param xPos X Possition
	 * @param yPos Y Possition
	 * @param xVel X Velocity
	 * @param yVel Y Velocity
	 */
	public Shot(double xPos, double yPos, double xVel, double yVel) 
	{
		this(xPos,yPos,xVel,yVel,3);
	}
	
	/**
	 * Gets age of bullet
	 * @return Age of bullet
	 */
	public int getAge()
	{
		return age;
	}
	
	/**
	 * Overloads move function to also increment age each time it is called
	 */
	public void move()
	{
		age++;
		super.move();
	}
}
