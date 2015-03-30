/*
 * Name: Chet Michals
 * Date: 03/28/11
 * Class: Object-Oriented Programming, COP 3330
 * Section: 1, aka "the only one"
 * Assignment: 3, Comets
 */

package comets;
/**
 * Class for the Space Ship
 * @author Chet Michals
 *
 */
public class Ship extends SpaceObject{

	protected double angle = 0;
	
	private Ship(double xPos, double yPos, double xVel, double yVel,
			double radius) {
		super(xPos, yPos, xVel, yVel, radius);
	}

	/**
	 * Constructor for ship, radius is 10
	 * @param xPos X Possition of ship
	 * @param yPos Y Possition of ship
	 * @param xVel X Velocity of ship
	 * @param yVel Y Velocity of ship
	 */
	public Ship(double xPos, double yPos, double xVel, double yVel) 
	{
		this(xPos,yPos,xVel,yVel,10);
	}
	
	public Ship(int xPos, int yPos, int xVel, int yVel) 
	{
		this((double)xPos,(double)yPos,(double)xVel,(double)yVel,10);
	}
	
	/**
	 * Increases speed, based off angle
	 */
	public void accelerate()
	{
		this.yVelocity += .1*Math.cos(this.angle);
		this.xVelocity += .1*Math.sin(this.angle);
		CapSpeed();		
	}
	
	private void CapSpeed()
	{
		double temp;
		temp = Math.sqrt(xVelocity+yVelocity);
		if (temp > 10) 
		{			
			
			this.yVelocity = 10/temp*Math.cos(this.angle);
			this.xVelocity = 10/temp*Math.sin(this.angle);
		}
	}
	
	/**
	 * Get angle of ship in radians
	 * @return Angle of ship
	 */
	public double getAngle()
	{
		return angle;
	}
	
	/**
	 * Roatate ship slightly to left
	 */
	public void rotateLeft()
	{
		angle+=.1;
	}
	
	/**
	 * Roate Ship slightly to right
	 */
	public void rotateRight()
	{
		angle-=.1;
	}
	
	/**
	 * Makes a new laser shot at 3 pixels faster then ship was moving
	 * @return a new laser shot
	 */
	public Shot fire()
	{
		double ShotSpeed;
		ShotSpeed = 3+Math.sqrt(xVelocity+yVelocity);
		double tempY = this.yVelocity + ShotSpeed*Math.cos(this.angle);
		double tempX = this.xVelocity + ShotSpeed*Math.sin(this.angle);
		

		
		Shot FIRE = new Shot(xPossition, yPossition, tempX, tempY);
		return FIRE;
	}
	
}
