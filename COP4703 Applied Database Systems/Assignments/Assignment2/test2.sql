-- PLAYER PACKAGE TEST
declare
   AName varchar(20) := 'Smithy';
   Posistion varchar(20) := 'Yes';
   DraftYear integer(20) := 2015;
   Education varchar(20) := 'Some';
   APlayerRecord PLAYER_pkg.PlayerRecord;
   i integer;
begin
	i := PLAYER_pkg.add(AName, Posistion, DraftYear, Education);
	DBMS_OUTPUT.PUT_LINE(i);
	i := PLAYER_pkg.retire(1,2015);
	DBMS_OUTPUT.PUT_LINE(i);
	i := PLAYER_pkg.retire('Gary Neal',2015);
	DBMS_OUTPUT.PUT_LINE(i);
	APlayerRecord := PLAYER_pkg.getPlayer(2);
	DBMS_OUTPUT.PUT_LINE(APlayerRecord.Player_ID||'| '||APlayerRecord.Pname||'| '||APlayerRecord.Position||'| '||APlayerRecord.draft_year||'| '||APlayerRecord.retire_year||'| '||APlayerRecord.Education);
	EXCEPTION 
		WHEN PLAYER_pkg.player_not_found THEN
			raise_application_error(-20003, 'Player Not Found');
		WHEN PLAYER_pkg.invalid_value THEN
			raise_application_error(-20004, 'Invalid Value inputed');
		
end;
/

-- Testing fail cases to Player Package
declare
   AName varchar(20) := 'Smithy';
   Posistion varchar(20) := 'Yes';
   DraftYear integer(20) := 2015;
   Education varchar(20) := 'Some';
   APlayerRecord PLAYER_pkg.PlayerRecord;
   i integer;
begin
	i := PLAYER_pkg.add('', Posistion, DraftYear, Education);
	DBMS_OUTPUT.PUT_LINE(i);
	EXCEPTION 
		WHEN PLAYER_pkg.player_not_found THEN
			raise_application_error(-20003, 'Player Not Found');
		WHEN PLAYER_pkg.invalid_value THEN
			raise_application_error(-20004, 'Invalid Value inputed');
end;
/

declare
   AName varchar(20) := 'Smithy';
   Posistion varchar(20) := 'Yes';
   DraftYear integer(20) := 2015;
   Education varchar(20) := 'Some';
   APlayerRecord PLAYER_pkg.PlayerRecord;
   i integer;
begin
	i := PLAYER_pkg.retire(-1,2015);
	DBMS_OUTPUT.PUT_LINE(i);
	EXCEPTION 
		WHEN PLAYER_pkg.player_not_found THEN
			raise_application_error(-20003, 'Player Not Found');
		WHEN PLAYER_pkg.invalid_value THEN
			raise_application_error(-20004, 'Invalid Value inputed');
end;
/

declare
   AName varchar(20) := 'Smithy';
   Posistion varchar(20) := 'Yes';
   DraftYear integer(20) := 2015;
   Education varchar(20) := 'Some';
   APlayerRecord PLAYER_pkg.PlayerRecord;
   i integer;
begin
	i := PLAYER_pkg.retire('No one',2015);
	DBMS_OUTPUT.PUT_LINE(i);
	EXCEPTION 
		WHEN PLAYER_pkg.player_not_found THEN
			raise_application_error(-20003, 'Player Not Found');
		WHEN PLAYER_pkg.invalid_value THEN
			raise_application_error(-20004, 'Invalid Value inputed');
end;
/
declare
   AName varchar(20) := 'Smithy';
   Posistion varchar(20) := 'Yes';
   DraftYear integer(20) := 2015;
   Education varchar(20) := 'Some';
   APlayerRecord PLAYER_pkg.PlayerRecord;
   i integer;
begin
APlayerRecord := PLAYER_pkg.getPlayer(-1);
	DBMS_OUTPUT.PUT_LINE(APlayerRecord.Player_ID||'| '||APlayerRecord.Pname||'| '||APlayerRecord.Position||'| '||APlayerRecord.draft_year||'| '||APlayerRecord.retire_year||'| '||APlayerRecord.Education);
EXCEPTION 
		WHEN PLAYER_pkg.player_not_found THEN
			raise_application_error(-20003, 'Player Not Found');
		WHEN PLAYER_pkg.invalid_value THEN
			raise_application_error(-20004, 'Invalid Value inputed');
end;
/
commit;