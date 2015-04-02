
public class Divider {
public float divide(float Num, float Den) throws DivideByZeroException
{
	if (Den == 0)
	{
		throw new DivideByZeroException();
	}

	return Num/Den;
}
}
