-- Chet Michals
-- Problem 3 Body

create or replace PACKAGE BODY ARENA_pkg AS
	FUNCTION add(Aname varchar, city varchar) RETURN INTEGER
  IS ID integer;
    arenaID INT;
    BEGIN
      if (Aname IS NULL) OR (city IS NULL) THEN 
        raise invalid_value;      
      else
      select max(ARENA_ID) into arenaID from ARENA;
      ID := arenaID + 1;
      insert into ARENA(ARENA_ID, ANAME, CITY) values (ID, Aname, city);
      return (ID);
      end if;
    END add;
    
	FUNCTION remove(ArenaID integer) RETURN INTEGER
  IS i integer;
  BEGIN
  delete from TEAM_PLAYER_ARENA where ARENA_ID = ArenaID;
  i := SQL%ROWCOUNT;
  delete from ARENA where ARENA_ID = ArenaID;
  i := i + SQL%ROWCOUNT;
  if i = 0 THEN
  return (i);
  else 
  return (ArenaID);
  END IF;
  END remove;
  
  FUNCTION remove(ArenaName varchar) RETURN INTEGER
  IS i integer;
  ArenaID integer;
  BEGIN
  select ARENA_ID into ArenaID from ARENA where ANAME = ArenaName;
  delete from TEAM_PLAYER_ARENA where ARENA_ID = ArenaID;
  i := SQL%ROWCOUNT;
  delete from ARENA where ARENA_ID = ArenaID;
  i := i + SQL%ROWCOUNT;
  if i = 0 THEN
  return (i);
  else 
  return (ArenaID);
  END IF;
  EXCEPTION
    when NO_DATA_FOUND then
    return (0);
  END remove;
  
	FUNCTION getArenaByID(ArenaID integer) RETURN ArenaRecord
  IS theRecord ArenaRecord;
  i integer;
  BEGIN
  select count(*) into i from ARENA where ARENA_ID = ArenaID;
  if i = 0 then
  raise invalid_value; 
  else
  select * into theRecord from ARENA where ARENA_ID = ArenaID;
  return (theRecord);
  end if;
  END getArenaByID;
  
	FUNCTION getArenaByName(ArenaName varchar) RETURN ArenaRecord
  IS theRecord ArenaRecord;
  i integer;
  BEGIN
  select count(*) into i from ARENA where ArenaName = AName;
  if i = 0 then
  raise invalid_value; 
  else
  select * into theRecord from ARENA where ArenaName = AName;
  return (theRecord);
  end if;
  return (theRecord);
  END getArenaByName;
  
	FUNCTION getArenaByCity(ArenaCity varchar) RETURN ArenaRecord
  IS theRecord ArenaRecord;
  i integer;
  BEGIN
  select count(*) into i from ARENA where ArenaCity = city;
  if i = 0 then
  raise invalid_value; 
  else
  select * into theRecord from ARENA where ArenaCity = city;
  return (theRecord);
  end if;

  return (theRecord);
  END getArenaByCity;
END ARENA_pkg;
/