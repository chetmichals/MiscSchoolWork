
public class Square implements Shape {

	public double side;
	
	@Override
	public double getArea() {
		return Math.pow(side, 2);
	}

	@Override
	public double getCircumference() {
		return 4 * side; 
	}
	
	@Override
	public void setSide(double input)
	{
		side = input;
	}
}
