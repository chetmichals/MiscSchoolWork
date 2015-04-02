-- COP4703
-- Assignment 3
-- Script to test the triggers
--
-- 1\  Arena: ARENA_noDelete_trig
delete from arena where arena_id = 1;
commit;
--
--
--
--
-- 2\ Player: PLAYER_noDelete_trig
delete from player where player_id = 1;
commit;
--
--
--
--
-- 3\ Team: TEAM_noDelete_trig
delete from team where team_id = 1;
commit;
--
--
--
--
-- 4-a\ Arena:ARENA_BeforInsert_trig. inserting null id
insert into arena (arena_id, aname, city) values ( '', 'Test', 'Boca');
commit; 
--
--
--
--
-- 4-b\ Arena: ARENA_BeforInsert_trig. insert 0 id
insert into arena (arena_id, aname, city) values ( 0, 'Test2', 'Boca');
commit;
--
--
--
--
-- 5\ team: TEAM_noDuplicateName_trig
insert into TEAM (team_id, tname, rank, city, championships) values ( 7, 'Bulls', 0, 'Boca', 0);
commit;
--
--
--
--
-- 6\ Arena: ARENA_noDuplicateNameCity_trig
insert into arena (arena_id, aname, city) values ( 10, 'Test', 'Boca');
commit;
--
--
--
--
-- 7-a\ PLAYER: PLAYER_noNulls_trig. No null in PName
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 9, '', 'point guard', 2010, '', 'Kentucky');
commit;
--
--
--
--
-- 7-b\ PLAYER: PLAYER_noNulls_trig. PName not an empty string.
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 10, '  ', 'point guard', 2010, '', 'Kentucky');
commit;
--
--
--
--
-- 7-c\ PLAYER: : PLAYER_noNulls_trig. No null in draft_year
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 11, 'John Wall', 'point guard', '', '', 'Kentucky');
commit;
--
--
--
--
-- 7-d\ PLAYER: : PLAYER_noNulls_trig. draft_year is not zero.
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 12, 'John Wall', 'point guard', 0, '', 'Kentucky');
commit;
--
--
--
--
-- 7-e\ PLAYER: : PLAYER_noNulls_trig. No null in education
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 13, 'John Wall', 'point guard', 2010, '', '');
commit;
-- 
--
--
--
-- 7-f\ PLAYER: : PLAYER_noNulls_trig. education is not an empty string
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 14, 'John Wall', 'point guard', 2010, '', '  ');
commit;
--
--
--
--
-- 7-g\ PLAYER: : PLAYER_noNulls_trig. retire_year is null
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 15, 'John Wall', 'point guard', 2010, 2020, 'Kentucky');
commit;
--
--
--
--
-- 7\ PLAYER: : PLAYER_noNulls_trig.This insert is successful
insert into player (player_id, pname, position, draft_year, retire_year, education) values ( 16, 'John Wall', 'point guard', 2010, '', 'Kentucky');
commit;




