
public class Ratio {
	float getRatio(float X, float Y) throws DivideByZeroException 
	{
		Divider divider = new Divider();
		return divider.divide(X, Y);
	}
}
