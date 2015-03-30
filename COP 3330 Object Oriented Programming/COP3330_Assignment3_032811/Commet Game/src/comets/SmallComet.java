/*
 * Name: Chet Michals
 * Date: 03/28/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 3, Comets
 */

package comets;

import java.util.Vector;
/**
 * Class for Small Comet
 * @author Chet Michals
 *
 */
public class SmallComet extends Comet{

	private SmallComet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}

	/**
	 * Constructor for Small comet, have radius of 20
	 */
	public SmallComet(double xPos, double yPos, double xVel, double yVel)
	{
		this(xPos,yPos,xVel,yVel,20);
	}
	
	@Override
	/**
	 * Function to return an empty vector of comets
	 * @return An emtpy comet vector
	 */
	public Vector<Comet> explode() {
		Vector<Comet> vc=new Vector<Comet>();
		return vc;
	}

}
