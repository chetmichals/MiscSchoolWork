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
 * Class for Medium Comet
 * @author Chet Michals
 *
 */
public class MediumComet extends Comet{

	private MediumComet(double xPos, double yPos, double xVel, double yVel, double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}

	/**
	 * Constructor for Medium comet, have radius of 30
	 */
	public MediumComet(double xPos, double yPos, double xVel, double yVel)
	{
		this(xPos,yPos,xVel,yVel,30);
	}
	
	@Override
	/**
	 * Function to return a vector of 3 Small Comets
	 * @return A vector of 3 Small comets with a random velocity
	 */
	public Vector<Comet> explode() {
		Vector<Comet> vc=new Vector<Comet>();
		vc.add(new SmallComet(this.xPossition,this.yPossition,(Math.random()-.5)*10,(Math.random()-.5)*10));
		vc.add(new SmallComet(this.xPossition,this.yPossition,(Math.random()-.5)*10,(Math.random()-.5)*10));
		vc.add(new SmallComet(this.xPossition,this.yPossition,(Math.random()-.5)*10,(Math.random()-.5)*10));
		return vc;
	}

}
