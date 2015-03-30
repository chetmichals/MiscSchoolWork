/*
 * Name: Chet Michals
 * Date: 03/28/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 3, Comets
 */


package comets;
/**
 * Comet is the super class for all the comets in the game
 * @author Chet Michals
 *
 */
public abstract class Comet extends SpaceObject {

/**
 * Defalut Constructor of Comet
 * @param xPos X Position of object
 * @param yPos Y Position of object
 * @param xVel X Velocity of object
 * @param yVel Y Velocity of object
 * @param radius Radius of object
 */
	public Comet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}
	/**
	 * Function to return a vector of new comets, used by child classes
	 * @return A vector of comets
	 */
	public abstract java.util.Vector<Comet> explode();
}
