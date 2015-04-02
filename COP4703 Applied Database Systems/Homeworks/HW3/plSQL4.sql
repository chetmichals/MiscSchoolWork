DECLARE
   val number(2) := 10;
BEGIN
   WHILE val  < 20 LOOP
      dbms_output.put_line('value is: ' || val );
      val  := val  + 1;
   END LOOP;
END;
/