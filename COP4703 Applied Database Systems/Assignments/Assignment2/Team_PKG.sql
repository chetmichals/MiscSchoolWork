-- Chet Michals
create or replace PACKAGE TEAM_pkg AS -- Package Definition problem 1
	name_in_use EXCEPTION;
	team_not_found EXCEPTION;
	TYPE TeamRecord IS RECORD(Team_ID integer, Tname varchar(15), Rank integer, City varchar(20), Championships integer);
	CURSOR TeamCursor RETURN TeamRecord;
	FUNCTION add(TeamName varchar, TeamCity varchar) RETURN integer;
	FUNCTION remove(TeamID integer) RETURN integer;
	PROCEDURE displayinfo(TeamID integer);
	PROCEDURE displayinfo(Teamname varchar);
	FUNCTION getTeam(TeamID integer) RETURN TeamRecord;
	PROCEDURE displayTeams;
	FUNCTION updateCity(TeamID integer, NewCity varchar) RETURN integer;
	FUNCTION updateCity(TeamName varchar, NewCity varchar) RETURN integer;
	FUNCTION updateName(TeamID integer, NewName varchar) RETURN integer;
	FUNCTION updateName(TeamName varchar, NewName varchar) RETURN integer;
	FUNCTION updateChampionships(TeamID integer) RETURN integer;
	FUNCTION updateChampionships(TeamName varchar) RETURN integer;
END TEAM_pkg;
/