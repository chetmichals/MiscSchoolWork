set echo on;
set SERVEROUTPUT on;
@createtables2;
SPOOL homework3.txt;
set SERVEROUTPUT on;
@hw3;
show errors;
@testHW3;
SPOOL off;