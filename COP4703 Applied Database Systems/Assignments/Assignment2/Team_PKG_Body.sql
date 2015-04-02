create or replace PACKAGE BODY TEAM_pkg AS

CURSOR TeamCursor RETURN TeamRecord is
select TEAM_ID , TNAME , RANK , CITY , CHAMPIONSHIPS  from TEAM order by TEAM_ID ASC;

FUNCTION add(TeamName varchar, TeamCity varchar) RETURN integer 
IS i integer;
BEGIN
select count(*) into i from team where TNAME = TeamName;
if i = 1 then
 raise name_in_use; 
else
i := TEAM_seq.NEXTVAL;
insert into team (Team_ID, TName, City, Championships) values (i, TeamName, TeamCity, 0);
RETURN (i);
end if;
END add;

	FUNCTION remove(TeamID integer) RETURN integer IS i integer;
BEGIN
delete from TEAM_PLAYER_ARENA where Team_ID = TeamID;
i := SQL%ROWCOUNT;
delete from TEAM where Team_ID = TeamID;
  i := i + SQL%ROWCOUNT;
  if i = 0 THEN
  return (i);
  else 
  return (TeamID);
  END IF;
END remove;

	PROCEDURE displayinfo(TeamID integer) is i INTEGER; aRecord TeamRecord;
  BEGIN
  select count(*) into i from team where Team_ID = TeamID;
  if i = 0 then
 raise team_not_found; 
else
select TEAM_ID , TNAME , RANK , CITY ,CHAMPIONSHIPS into aRecord from team where Team_ID = TeamID;
DBMS_OUTPUT.PUT_LINE('Team ID: ' ||aRecord.TEAM_ID|| '| Team Name: '|| aRecord.TNAME || '| Rank: '|| aRecord.RANK ||' | City: '||aRecord.CITY||'| Championships: '||aRecord.CHAMPIONSHIPS);
end if;
  END displayinfo;
  
  
	PROCEDURE displayinfo(TeamName varchar) is i INTEGER; aRecord TeamRecord;
  BEGIN
  select count(*) into i from team where Tname = TeamName;
  if i = 0 then
 raise team_not_found; 
else
select TEAM_ID , TNAME , RANK , CITY ,CHAMPIONSHIPS into aRecord from team where Tname = TeamName;
DBMS_OUTPUT.PUT_LINE('Team ID: ' ||aRecord.TEAM_ID|| '| Team Name: '|| aRecord.TNAME || '| Rank: '|| aRecord.RANK ||' | City: '||aRecord.CITY||'| Championships: '||aRecord.CHAMPIONSHIPS);
end if;
  END displayinfo;
  
  
	FUNCTION getTeam(TeamID integer) RETURN TeamRecord IS aRecord TeamRecord;
 i integer;
BEGIN
select count(*) into i from team where Team_ID = TeamID;
if i = 0 then
 raise team_not_found; 
else
select TEAM_ID , TNAME , RANK , CITY , CHAMPIONSHIPS  into aRecord from team where Team_ID = TeamID;
RETURN (aRecord);
end if;
END getTeam;

	PROCEDURE displayTeams is i INTEGER; aRecord TeamRecord;
  BEGIN
   OPEN TeamCursor; 
   LOOP
    FETCH TeamCursor INTO aRecord;
    EXIT WHEN TeamCursor%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Team ID: ' ||aRecord.TEAM_ID|| '| Team Name: '|| aRecord.TNAME || '| Rank: '|| aRecord.RANK ||' | City: '||aRecord.CITY||'| Championships: '||aRecord.CHAMPIONSHIPS);
    END LOOP;
   CLOSE TeamCursor;
  END displayTeams;
  
  
	FUNCTION updateCity(TeamID integer, NewCity varchar) RETURN integer IS
i integer;
BEGIN
select count(*) into i from team where Team_ID = TeamID;
if i = 0 then
 raise team_not_found; 
else
update team set city = NewCity where Team_ID = TeamID;
i := SQL%ROWCOUNT;
RETURN (i);
end if;
END updateCity;

	FUNCTION updateCity(TeamName varchar, NewCity varchar) RETURN integer IS i integer;
BEGIN
select count(*) into i from team where TName = TeamName;
if i = 0 then
 raise team_not_found; 
else
update team set city = NewCity where TName = TeamName;
i := SQL%ROWCOUNT;
RETURN (i);
end if;
END updateCity;

	FUNCTION updateName(TeamID integer, NewName varchar) RETURN integer IS i integer;
BEGIN
select count(*) into i from team where Team_ID = TeamID;
if i = 0 then
 raise team_not_found; 
else
update team set TName = NewName where Team_ID = TeamID;
i := SQL%ROWCOUNT;
RETURN (i);
end if;
END updateName;

	FUNCTION updateName(TeamName varchar, NewName varchar) RETURN integer IS i integer;
BEGIN
select count(*) into i from team where TName = TeamName;
if i = 0 then
 raise team_not_found; 
else
update team set TName = NewName where TName = TeamName;
i := SQL%ROWCOUNT;
RETURN (i);
end if;
END updateName;

	FUNCTION updateChampionships(TeamID integer) RETURN integer IS i integer;
BEGIN
select count(*) into i from team where Team_ID = TeamID;
if i = 0 then
 raise team_not_found; 
else
update team set Championships = Championships + 1 where Team_ID = TeamID;
select Championships into i from team where Team_ID = TeamID;
RETURN (i);
end if;
END updateChampionships;

	FUNCTION updateChampionships(TeamName varchar) RETURN integer IS i integer;
BEGIN
select count(*) into i from team where TName = TeamName;
if i = 0 then
 raise team_not_found; 
else
update team set Championships = Championships + 1 where TName = TeamName;
select Championships into i from team where TName = TeamName;
RETURN (i);
end if;
END updateChampionships;
END TEAM_pkg;
/