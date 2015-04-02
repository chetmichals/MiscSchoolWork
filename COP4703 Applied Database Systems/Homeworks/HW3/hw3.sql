-- Problem 1
create  or replace  trigger ARENA_noDelete_trig
  before delete
  on ARENA
begin
  dbms_output.put('ARENA_noDelete_trig has fired');
  raise_application_error(-20008, 'Delete operations are not allowed on this table');
end;
/
-- Problem 2
create  or replace  trigger PLAYER_noDelete_trig
  before delete
  on PLAYER
begin
  dbms_output.put('PLAYER_noDelete_trig has fired');
  raise_application_error(-20009, 'Delete operations are not allowed on this table');
end;
/
-- Problem 3
create  or replace  trigger TEAM_noDelete_trig
  before delete
  on TEAM
begin
  dbms_output.put('TEAM_noDelete_trig has fired');
  raise_application_error(-20010, 'Delete operations are not allowed on this table');
end;
/
-- Problem 4
create  or replace  trigger ARENA_BeforInsert_trig
  before INSERT on ARENA
  FOR EACH ROW
begin
  dbms_output.put('ARENA_BeforInsert_trig has fired');
	If (:new.ARENA_ID = 0 OR :new.ARENA_ID IS NULL) Then
		select max(ARENA_ID)+1 into :new.ARENA_ID from ARENA;
	end if;
end;
/
-- Problem 5
create  or replace  trigger TEAM_noDuplicateName_trig
  before INSERT on TEAM
  FOR EACH ROW
DECLARE
	teamCount int;
begin
	dbms_output.put('TEAM_noDuplicateName_trig has fired');
	select count(*) into teamCount from TEAM where TNAME = :new.TNAME;
	if (teamCount != 0) THEN
		raise_application_error(-20011, ' Team name already in use, name: '||:new.TNAME);
	END IF;
end;
/
-- Problem 6
create  or replace  trigger ARENA_noDuplicateNameCity_trig
  before INSERT on ARENA
  FOR EACH ROW
DECLARE
	arenaCount int;
begin
	dbms_output.put('ARENA_noDuplicateNameCity_trig has fired');
	select count(*) into arenaCount from ARENA where CITY = :new.CITY;
	if (arenaCount != 0) THEN
		raise_application_error(-20012, 'Arena name already in use, name: '||:new.CITY);
	END IF;
end;
/
-- Problem 7
create  or replace  trigger PLAYER_noNulls_trig
  before INSERT on PLAYER
  FOR EACH ROW
DECLARE
	errorCount int;
begin
	dbms_output.put('PLAYER_noNulls_trig has fired');
	errorCount := 0;
	If (:new.PNAME = '' OR :new.PNAME IS NULL) Then
		errorCount := errorCount + 1;
		dbms_output.put('Error: Player Name is Null');
	END IF;
	If (:new.EDUCATION = '' OR :new.EDUCATION IS NULL) Then
		errorCount := errorCount + 1;
		dbms_output.put('Error: Education Name is Null');
	END IF;
	If (:new.DRAFT_YEAR = 0 OR :new.DRAFT_YEAR IS NULL) Then
		errorCount := errorCount + 1;
		dbms_output.put('Error: Draft Year is not valid');
	END IF;
	If (:new.retire_year IS NOT NULL) Then
		errorCount := errorCount + 1;
		dbms_output.put('Error: Do not set retire year');
	END IF;
	if (errorCount != 0) THEN
		raise_application_error(-20013, 'PLAYER table. Insert operation failed');
	END IF;
end;
/