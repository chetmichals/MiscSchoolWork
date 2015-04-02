public class ClassExamples 
{
	public static void main(String[] args)
	{
			//Slide 22, increments
			int count = 0;
			System.out.println("count= " + count);
			System.out.println("count++= " + (count++));
			System.out.println("count= " + count);
			System.out.println("++count= " + (++count));
			System.out.println("count= " + count);
			
			//Slide 27, Logical Evaluations
			int small = 1;
			int big = 1000;
			if (small > big)
			{
				System.out.println("small > big");
			}
			else if (small == big)
			{
				System.out.println("small = big");
			}
			else
			{
				System.out.println("small < big");
			}
			
			//Slide 28, While loops
			
			int y = 10;
			
			while( y < 20)
			{
				System.out.print("value of y : " + y);
				y++;
				System.out.print("\n");
			}
			
			y = 10;
			
			do
			{
				System.out.print("value of y : " + y);
				y++;
				System.out.print("\n");
			}
			while (y < 20);
			
			//Slide 29, for loops
			for(int x = 10; x < 20; x = x+1)
			{
				System.out.print("value of x : " + x);
				System.out.print("\n");
			}
			
			int [] numbers = {10, 20, 30, 40, 50};
	
			for (int x : numbers )
			{
				System.out.print(x);
				System.out.print(", ");
			}
			
			String [] names = {"Jim", "Bob", "Tom", "Li"};
			for (String name : names )
			{
				System.out.print(name);
				System.out.print(", ");
			}
			
			//Slide 30, break and continue
			for (int x : numbers )
			{
				if( x == 30)
				{
					break;
				}
				System.out.print(x);
				System.out.print("\n");
			}
			
			for (int x : numbers )
			{
				if ( x == 30)
				{
					continue;
				}
				System.out.print(x);
				System.out.print("\n");
			}
			
			return;
	}
}