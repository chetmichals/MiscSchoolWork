-- 1: Proc AddNum: this proc will add two numbers X & Y, and return the result in a third variable Z
create or REPLACE PROCEDURE AddNum(x IN number, y IN number, z OUT number) AS
BEGIN
z:= x + y;
end;
/

DECLARE
 x number;
 y number;
 z number;
BEGIN
x := 5;
y := 15;
AddNum(x,y,z);
 DBMS_OUTPUT.put_line(z);
END;
/