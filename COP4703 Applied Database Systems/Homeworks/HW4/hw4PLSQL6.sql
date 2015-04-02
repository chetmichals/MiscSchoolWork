-- 6: Proc printHi(first, last): this proc takes two strings, first name & last name, and prints: “Hi <first last> to the
-- console. E.g. calling printHi(‘Blake’, ‘Griffin’) , results in: Hi Blake Griffin being printed out.
create or REPLACE PROCEDURE printHi(first in VarChar2, last in VarChar2) AS
BEGIN
DBMS_OUTPUT.put_line('Hi '||first||' '||last);
END;
/

DECLARE
 x varchar2(200);
 y varchar2(200);
 BEGIN
x := 'Chet';
y := 'Michals';
printHi(x,y);
end;
/