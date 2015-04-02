
public class NBA_Team extends Team{

	private String division;
	
	public NBA_Team(String teamName)
	{
		super(teamName);
		this.division = "Atlantic";
	}
	
	public NBA_Team(String teamName, String teamCity)
	{
		super(teamName, teamCity);
		this.division = "Atlantic";
	}
	
	public NBA_Team(String teamName, String teamCity, String division)
	{
		super(teamName, teamCity);
		this.division = division;
	}
	
	//Methods
	
	public void printTeamInfo()
	{
		super.printTeamInfo();
		System.out.println("Division: " + this.division);
	}
	
	public void changeDivision(String division)
	{
		this.division = division;
	}
	
	public String getDivision()
	{
		return division;
	}
	
	
}
