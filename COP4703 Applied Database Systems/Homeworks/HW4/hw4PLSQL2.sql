-- 2: Proc MultiplyNum: this proc will multiply two numbers X & Y, and return the result in a third variable Z
create or REPLACE PROCEDURE MultiplyNum(x IN number, y IN number, z OUT number) AS
BEGIN
z:= x * y;
end;
/

DECLARE
 x number;
 y number;
 z number;
BEGIN
x := 5;
y := 6;
MultiplyNum(x,y,z);
 DBMS_OUTPUT.put_line(z);
END;
/