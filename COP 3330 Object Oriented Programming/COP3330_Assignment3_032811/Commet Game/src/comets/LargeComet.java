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
 * Class for Large Comet
 * @author Chet Michals
 *
 */
public class LargeComet extends Comet{

	
	private LargeComet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}

	/**
	 * Constructor for large comet, have radius of 40
	 */
	public LargeComet(double xPos, double yPos, double xVel, double yVel)
	{
		this(xPos,yPos,xVel,yVel,40);
	}
	@Override
	
	/**
	 * Function to return a vector of 2 Medium Comets
	 * @return A vector of 2 Medium comets with a random velocity
	 */
	public Vector<Comet> explode() {
		Vector<Comet> vc=new Vector<Comet>();
		for (int i = 0; i < 2; i++)
		vc.add(new MediumComet(this.xPossition,this.yPossition,(Math.random()-.5)*10,(Math.random()-.5)*10));
		return vc;
	}

}
