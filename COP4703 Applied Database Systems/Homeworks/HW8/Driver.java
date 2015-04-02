import java.util.ArrayList;


public class Driver {

	public static void main(String[] args) {
		//Test Shape Interface
		Shape shapeA = new Circle();
		Shape shapeB = new Square();
		
		shapeA.setSide(10);
		shapeB.setSide(10);
		
		System.out.println("Shape A Area " + shapeA.getArea());
		System.out.println("Shape B Area " + shapeB.getArea());
		System.out.println("Shape A Circumferencee " + shapeA.getCircumference());
		System.out.println("Shape B Circumferencee " + shapeB.getCircumference());
		
		//Test DivideByZero Exception
		Divider divider = new Divider();
		
		try
		{
			System.out.println(divider.divide(15, 3));
			System.out.println(divider.divide(15, 0));
			
			
		}
		catch(DivideByZeroException de)
		{
			System.out.println(de.getMessage());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		Ratio ratio = new Ratio();
		try 
		{
			ratio.getRatio(0, 0);
		} 
		catch (DivideByZeroException e) 
		{
			System.out.println(e.getMessage());
		}
		
		try 
		{
			System.out.println(ratio.getRatio(1, 4));
			System.out.println(ratio.getRatio(0, 0));
		} 
		catch (DivideByZeroException e) 
		{
			System.out.println(e.getMessage());
		}
		
		ArrayList<String> arrayList = new ArrayList<String>();
		
		arrayList.add("C");
		arrayList.add("A");
		arrayList.add("E");
		arrayList.add("B");
		arrayList.add("D");
		arrayList.add("F");
		
		java.util.Iterator<String> itr = arrayList.iterator();
		while(itr.hasNext())
		{
			String element = itr.next();
			System.out.print(element + " ");			
		}
		System.out.println();
		
		Vehicle normalRaceCar = new RaceCar();
		Vehicle superRaceCar = new SuperRaceCar();
		
		System.out.println("Normal Race Card Speed: " + normalRaceCar.getTopSpeed());
		System.out.println("Super Race Card Speed: " + superRaceCar.getTopSpeed());
		
	}

}
