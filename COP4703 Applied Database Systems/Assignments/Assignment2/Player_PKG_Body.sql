-- Chet Michals
-- Problem 2 Body

create or replace PACKAGE BODY PLAYER_pkg AS
    FUNCTION add(Pname varchar, Position varchar, draft_year integer, Education varchar) RETURN integer
    IS ID integer;
    playerID INT;
    BEGIN
      if (Pname IS NULL) OR (Position IS NULL) OR (Education IS NULL) THEN 
        raise invalid_value;      
      else
      select max(Player_ID) into playerID from PLAYER;
      ID := playerID + 1;
      insert into PLAYER(Player_ID, Pname, Position, draft_year, Education) values (ID, Pname, Position, draft_year, Education);
      return (ID);
      end if;
    END add;
    
    FUNCTION retire(PlayerID integer, retireYear integer) RETURN integer IS ID integer;
    BEGIN
      select count(*) into ID from PLAYER where PLAYER.Player_ID = PlayerID;
      if ID = 0 THEN
        raise player_not_found;
      ELSE 
      update PLAYER set retire_year = retireYear where player.Player_ID = PlayerID;
      return (PlayerID);
      end if;
    END retire;
    
    FUNCTION retire(PlayerName varchar, retireYear integer) RETURN integer 
    IS 
    ID integer;
    
    BEGIN
      select count(*) into ID from PLAYER where PLAYER.Pname = PlayerName;
      if ID = 0 THEN
        raise player_not_found;
      ELSE 
        select Player_ID into ID from PLAYER where PLAYER.Pname = PlayerName;
        ID := retire(ID,retireYear);
        return (ID);
      END IF;
     
      
      
    END retire;
    
    FUNCTION getPlayer(PlayerID integer) RETURN PlayerRecord 	IS theRecord PlayerRecord; aNumber integer;
    BEGIN
    select count(*) into aNumber from player where Player_ID = PlayerID;
    if aNumber = 0 then
    raise player_not_found;
    else
    select * into theRecord from player where Player_ID = PlayerID;
    return(theRecord);
    end if;
    END getPlayer;
END PLAYER_pkg;
/