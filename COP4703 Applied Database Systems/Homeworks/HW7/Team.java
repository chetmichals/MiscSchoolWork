
public abstract class Team {
	
	private String teamName;
	private String teamCity;
	private int championships = 0;
	
	//Public Constructors  
	public Team(String teamName)
	{
		this.teamName = teamName;
		this.teamCity = "Unknown";
	}
	
	public Team(String teamName, String teamCity)
	{
		this.teamName = teamName;
		this.teamCity = teamCity;		
	}
	
	//Object Methods 
	public void printTeamInfo()
	{
		System.out.println("Team Name: " + this.teamName +" | Team City: " 
				+ this.teamCity + " | Championships: " + this.championships );		
	}
	
	//Variable getters and setters
	public void changeTeamName(String teamName)
	{	
		this.teamName = teamName;
	}
	
	public void changeTeamCity(String teamCity)
	{	
		this.teamCity = teamCity;
	}
	
	public String getTeamName()
	{	
		return this.teamName;
	}
	public String getTeamCity()
	{	
		return this.teamCity;
	}
	
	public void incrementChampionships()
	{
		this.championships++;
	}
	
	public int getChampionships()
	{
		return this.championships;
	}	
}
