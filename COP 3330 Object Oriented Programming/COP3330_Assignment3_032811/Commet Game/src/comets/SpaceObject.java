/*
 * Name: Chet Michals
 * Date: 03/28/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 3, Comets
 */

package comets;

/**
 * SpaceObject is the super class for all the visable objects in the game
 * @author Chet Michals
 *
 */
public abstract class SpaceObject {
	
	/**
	 * 
	 */
	public static double playfieldHeight;
	public static double playfieldWidth;
	
	protected double xVelocity;
	protected double yVelocity;
	
	
	protected double xPossition;
	protected double yPossition;
	protected double radius;
	
	/**
	 * Defalut Consturctor used for all subclasses
	 * @param xPos X Possition
	 * @param yPos Y Possition
	 * @param xVel X Velocity
	 * @param yVel Y Velocity
	 * @param radius Radius of object
	 */
	public SpaceObject(double xPos,
            double yPos,
            double xVel,
            double yVel,
            double radius)
	{
	this.xPossition = xPos;
	this.yPossition = yPos;
	this.xVelocity = xVel;
	this.yVelocity = yVel;
	this.radius = radius;
	}
	
	/**
	 *  Gets Object Radius
	 * @return Returns the radius of the object
	 */
	public double getRadius()
	{
		return this.radius;
	}
	
	/**
	 * Gets the object's X Position
	 * @return Returns X Position
	 */
	public double getXPosition()
	{
		return this.xPossition;
	}
	
	
	/**
	 * Gets the object's Y Position
	 * @return Returns Y Position
	 */
	public double getYPosition()
	{
		return this.yPossition;
	}
	
	/**
	 * Updates object's possition
	 */
	public void move()
	{
		this.xPossition += this.xVelocity;
		this.yPossition += this.yVelocity;
		
		if (this.xPossition > playfieldWidth) 
			this.xPossition -= playfieldWidth;
		else if (this.xPossition < 0) 
			this.xPossition += playfieldWidth;
		
		if (this.yPossition > playfieldHeight) 
			this.yPossition -= playfieldHeight;
		else if (this.yPossition < 0) 
			this.yPossition += playfieldHeight;
	}
	
	/**
	 * Checks if two objects are overlapping
	 * @param rhs Object to be compared to
	 * @return True if Overlapping, false if not
	 */
	public boolean overlapping(SpaceObject rhs)
	{
		//"Two circles overlap if the sum of there radii is greater than the distance between their centers."
		//(cx1-cx2)2 + (cy1-cy2)2 < (r1+r2)2
		//http://www.euclideanspace.com/maths/geometry/elements/intersection/twod/index.htm
		double TempX;
		double TempY;
		double XYSqr;
		double LocalX1 = OffScreenNomralizerX(this.xPossition, this.radius);
		double LocalX2 = OffScreenNomralizerX(rhs.xPossition, rhs.radius);
		double LocalY1 = OffScreenNomralizerY(this.yPossition, this.radius);
		double LocalY2 = OffScreenNomralizerY(rhs.yPossition, rhs.radius);;
		
		TempX = Math.abs(LocalX1 - LocalX2);
		TempY = Math.abs(LocalY1 - LocalY2);
		
		XYSqr = Math.sqrt(Math.pow(TempX,2)+Math.pow(TempY,2));
		if (XYSqr < (this.radius+rhs.radius)) return true;
		else return false;
		
	}
	
	private double OffScreenNomralizerX(double xPos, double radius)
	{
		//if (xPos-radius < SpaceObject.playfieldWidth) {return xPos + SpaceObject.playfieldWidth;}
		return xPos;
	}
	
	private double OffScreenNomralizerY(double yPos, double radius)
	{
		//if (yPos-radius < SpaceObject.playfieldHeight) {return yPos + SpaceObject.playfieldHeight;}
		return yPos;
	}
}
