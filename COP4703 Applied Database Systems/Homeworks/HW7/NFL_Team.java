
public class NFL_Team extends Team{
	
	private String conference;
	
	//Constructors
	public NFL_Team(String teamName)
	{
		super(teamName);
		this.conference = "AFL";
	}
	
	public NFL_Team(String teamName, String teamCity)
	{
		super(teamName, teamCity);
		this.conference = "AFL";
	}
	
	public NFL_Team(String teamName, String teamCity, String conference)
	{
		super(teamName, teamCity);
		this.conference = conference;
	}
	
	//Methods
	public void changeConference(String conference)
	{
		this.conference = conference;
	}
	
	public String getConference()
	{
		return conference;
	}
}
