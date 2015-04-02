-- Chet Michals
create or replace PACKAGE ARENA_pkg AS -- Package Definition problem 3
	invalid_value EXCEPTION;
	TYPE ArenaRecord IS RECORD(ARENA_ID integer, Aname varchar(20), city varchar(20));
	FUNCTION add(Aname varchar, city varchar) RETURN INTEGER;
	FUNCTION remove(ArenaID integer) RETURN INTEGER;
  FUNCTION remove(ArenaName varchar) RETURN INTEGER;
	FUNCTION getArenaByID(ArenaID integer) RETURN ArenaRecord;
	FUNCTION getArenaByName(ArenaName varchar) RETURN ArenaRecord;
	FUNCTION getArenaByCity(ArenaCity varchar) RETURN ArenaRecord;
END ARENA_pkg;
/