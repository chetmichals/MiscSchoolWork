-- ARENA PACKAGE TEST
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
   
begin
   -- Call the functions in Arena_PKG properly
   AName := 'Best Arena';
   City := 'Miami';
   ArenaID := ARENA_PKG.add('Best Arena', 'Miami');
   DBMS_OUTPUT.PUT_LINE(ArenaID);
   i := ARENA_PKG.remove(7);
   DBMS_OUTPUT.PUT_LINE(i);
   i := ARENA_PKG.remove('Staples Center');
   DBMS_OUTPUT.PUT_LINE(i);
   AnArenaRecord := ARENA_PKG.getArenaByID(ArenaID);
   DBMS_OUTPUT.PUT_LINE(AnArenaRecord.ARENA_ID||' '||AnArenaRecord.Aname||' '||AnArenaRecord.City);
   AnArenaRecord := ARENA_PKG.getArenaByName('United Center');
   DBMS_OUTPUT.PUT_LINE(AnArenaRecord.ARENA_ID||' '||AnArenaRecord.Aname||' '||AnArenaRecord.City);
   AnArenaRecord := ARENA_PKG.getArenaByCity('Boston');
   DBMS_OUTPUT.PUT_LINE(AnArenaRecord.ARENA_ID||' '||AnArenaRecord.Aname||' '||AnArenaRecord.City);
   EXCEPTION 
	WHEN ARENA_PKG.invalid_value THEN
		raise_application_error(-20004, 'Invalid Value inputed');
   commit;
        
end;
/

 -- Call the functions in Arena_PKG improperly
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
 begin
ArenaID := ARENA_PKG.add('Best Arena', '');
EXCEPTION 
  WHEN ARENA_PKG.invalid_value THEN
	raise_application_error(-20004, 'Invalid Value inputed');
end;
/
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
begin
i := ARENA_PKG.remove(-1);
DBMS_OUTPUT.PUT_LINE(i);
i := ARENA_PKG.remove('No Arena');
DBMS_OUTPUT.PUT_LINE(i);
end;
/
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
begin
AnArenaRecord := ARENA_PKG.getArenaByID(-1);
EXCEPTION 
  WHEN ARENA_PKG.invalid_value THEN
	raise_application_error(-20004, 'Invalid Value inputed');
end;
/
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
begin
AnArenaRecord := ARENA_PKG.getArenaByName('UnitedCenter');
EXCEPTION 
  WHEN ARENA_PKG.invalid_value THEN
	raise_application_error(-20004, 'Invalid Value inputed');
end;
/
declare
   AName varchar(20) := 'Best Arena';
   City varchar(20) := 'Miami';
   ArenaID integer(20);
   AnArenaRecord ARENA_PKG.ArenaRecord;
   i integer;
begin
AnArenaRecord := ARENA_PKG.getArenaByCity('Baston');
EXCEPTION 
  WHEN ARENA_PKG.invalid_value THEN
	raise_application_error(-20004, 'Invalid Value inputed');
end;
/
commit;
