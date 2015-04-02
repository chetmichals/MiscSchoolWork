CREATE OR REPLACE PACKAGE TEAM_pkg AS -- Package Definition problem 1
	name_in_use EXCEPTION;
	team_not_found EXCEPTION;
	TYPE TeamRecord IS RECORD(Team_ID integer, Tname varchar(15), Rank integer, City varchar(20), Championships integer);
	CURSOR TeamCursor RETURN TeamRecord;
	FUNCTION add(Tname varchar, City varchar) RETURN integer;
	FUNCTION remove(Team_ID integer) RETURN integer;
	PROCEDURE displayinfo(Team_ID integer);
	PROCEDURE displayinfo(Tname varchar);
	FUNCTION getTeam(Team_ID integer) RETURN TeamRecord;
	PROCEDURE displayTeams;
	FUNCTION updateCity(Team_ID integer, NewCity varchar) RETURN integer;
	FUNCTION updateCity(Tname varchar, NewCity varchar) RETURN integer;
	FUNCTION updateName(Team_ID integer, NewName varchar) RETURN integer;
	FUNCTION updateName(Tname varchar, NewName varchar) RETURN integer;
	FUNCTION updateChampionships(Team_ID integer) RETURN integer;
	FUNCTION updateChampionships(Tname varchar) RETURN integer;
END TEAM_pkg;

CREATE OR REPLACE PACKAGE PLAYER_pkg AS -- Package Definition problem 2
	invalid_value EXCEPTION;
	player_not_found EXCEPTION;
	TYPE PlayerRecord IS RECORD(Player_ID integer, Pname varchar(30), Position varchar(20), draft_year integer, retire_year integer, Education varchar(30));
	FUNCTION add(Pname varchar, Position varchar, draft_year integer, Education varchar) RETURN integer;
	FUNCTION retire(Player_ID integer, retire_year integer) RETURN integer;
	FUNCTION retire(Pname varchar, retire_year integer) RETURN integer;
	FUNCTION getPlayer(Player_ID integer) RETURN PlayerRecord;
END PLAYER_pkg;

CREATE OR REPLACE PACKAGE ARENA_pkg AS -- Package Definition problem 3
	invalid_value EXCEPTION;
	TYPE ArenaRecord IS RECORD(ARENA_ID integer, Aname varchar(20), city varchar(20));
	FUNCTION add(Aname varchar, city varchar) RETURN INTEGER;
	FUNCTION remove(ARENA_ID integer) RETURN INTEGER;
	FUNCTION getArenaByID(ARENA_ID integer) RETURN ArenaRecord;
	FUNCTION getArenaByName(Aname varchar) RETURN ArenaRecord;
	FUNCTION getArenaByCity(city varchar) RETURN ArenaRecord;
END ARENA_pkg;