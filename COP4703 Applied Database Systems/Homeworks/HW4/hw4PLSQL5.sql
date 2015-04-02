-- 5: Proc DOUBLE(y): this proc will take the value y and return 2y in the same variable

create or REPLACE PROCEDURE DOUBLE(y in out Integer) AS
BEGIN
y := y * 2;
END;
/

DECLARE
 y Integer;
BEGIN
y := 5;
DOUBLE(y);
 DBMS_OUTPUT.put_line(y);
END;
/