
public class Driver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		NBA_Team bulls = new NBA_Team("Bulls");
		NBA_Team OTK = new NBA_Team("OTK","Oklahoma","Northwest");
		
		NFL_Team bears = new NFL_Team("Bears");
		NFL_Team falcons = new NFL_Team("Falcons","Atlanta");
		
		bulls.changeDivision("NorthSouth West");
		bears.incrementChampionships();
		bears.changeTeamCity("Forest");
		falcons.changeTeamName("Bluejays");
		
		bulls.printTeamInfo();
		OTK.printTeamInfo();
		bears.printTeamInfo();
		falcons.printTeamInfo();
		
	}

}
