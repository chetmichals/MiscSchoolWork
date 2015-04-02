
public class Circle implements Shape {

	public double radius;
	@Override
	public double getArea() {
		return PI * Math.pow(radius, 2);
	}

	@Override
	public double getCircumference() {
		return PI * 2 * radius;
	}
	
	public void setSide(double input)
	{
		radius = input;
	}

}
