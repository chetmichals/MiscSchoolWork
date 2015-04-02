-- Chet Michals
create or replace PACKAGE PLAYER_pkg AS -- Package Definition problem 2
	invalid_value EXCEPTION;
	player_not_found EXCEPTION;
	TYPE PlayerRecord IS RECORD(Player_ID integer, Pname varchar(30), Position varchar(20), draft_year integer, retire_year integer, Education varchar(30));
	FUNCTION add(Pname varchar, Position varchar, draft_year integer, Education varchar) RETURN integer;
  FUNCTION retire(PlayerID integer, retireYear integer) RETURN integer;
	FUNCTION retire(PlayerName varchar, retireYear integer) RETURN integer;
	FUNCTION getPlayer(PlayerID integer) RETURN PlayerRecord;
END PLAYER_pkg;
/