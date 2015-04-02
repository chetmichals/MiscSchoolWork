-- Testing Team Package
declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.add(AName,City);
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.remove(1);
DBMS_OUTPUT.PUT_LINE(i);
ATeamRecord := TEAM_pkg.getTeam(2);
DBMS_OUTPUT.PUT_LINE('Team ID: ' ||ATeamRecord.TEAM_ID|| '| Team Name: '|| ATeamRecord.TNAME || '| Rank: '|| ATeamRecord.RANK ||' | City: '||ATeamRecord.CITY||'| Championships: '||ATeamRecord.CHAMPIONSHIPS);
i:= TEAM_pkg.updateCity(3,'Nowhere');
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.updateCity('Spurs','Dreamland');
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.updateName(5,'Gloves');
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.updateName('Gloves','Spurs');
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.updateChampionships(5);
DBMS_OUTPUT.PUT_LINE(i);
i:= TEAM_pkg.updateChampionships('Spurs');
DBMS_OUTPUT.PUT_LINE(i);
TEAM_pkg.displayinfo(2);
TEAM_pkg.displayinfo('Spurs');
TEAM_pkg.displayTeams;
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

-- Testing fail cases of team Package

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.add('Socks',City);
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.remove(-1);
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
ATeamRecord := TEAM_pkg.getTeam(-2);
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateCity(-3,'Nowhere');
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateCity('spuds','Dreamland');
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateName(-5,'Gloves');
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateName('Gives','Spurs');
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateChampionships(-5);
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

declare
   TeamID integer(20);
   AName varchar(20) := 'Socks';
   City varchar(20) := 'Maybe';
   ATeamRecord TEAM_pkg.TeamRecord;
   i integer;
begin
i:= TEAM_pkg.updateChampionships('spins');
EXCEPTION 
      WHEN TEAM_pkg.team_not_found THEN
        raise_application_error(-20002, 'Team Not Found');

      WHEN TEAM_pkg.name_in_use THEN
        raise_application_error(-20001, 'Name in Use');
end;
/

commit;
