-- 4: Proc POWER3(x): this proc will take the value x and return X^3 in the same variable
create or REPLACE PROCEDURE POWER3(x in out Integer) AS
BEGIN
x := x * x * x;
END;
/

DECLARE
 x Integer;
BEGIN
x := 5;
POWER3(x);
 DBMS_OUTPUT.put_line(x);
END;
/