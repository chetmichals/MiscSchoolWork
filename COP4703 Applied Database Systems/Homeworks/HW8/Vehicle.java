
public abstract class Vehicle {	
	
	String fuelType = "Gas";
	int numberOfWheels = 4; 
	
	public String getFuleType()
	{
		return fuelType;
	}
	
	public int getNumberOfWheels()
	{
		return numberOfWheels;
	}
	
	public abstract int getTopSpeed();
}
