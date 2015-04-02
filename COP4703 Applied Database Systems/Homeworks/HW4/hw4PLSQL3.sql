-- 3: Porc POWERR(n,r, R): this proc will raise the first number n, to the power r & return the result in the variable R.
create or REPLACE PROCEDURE POWERR(n IN Integer, r IN Integer, O OUT Integer) AS
loopCounter Integer; 
BEGIN
  loopCounter := 0;
	IF r < 0 THEN
		raise_application_error(-20101, 'Can not calculate negative exponents');
	END IF;
	if r = 0 THEN
		O := 0;
		return;
	END IF;
	O := n;
	loop
		exit when loopCounter = r;
		O := n * O;
		loopCounter := loopCounter + 1;
	end loop;
end;
/

DECLARE
 x Integer;
 y Integer;
 z Integer;
BEGIN
x := 5;
y := 6;
POWERR(x,y,z);
 DBMS_OUTPUT.put_line(z);
END;
/