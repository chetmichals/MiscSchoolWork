DECLARE
   val number(2) := 10;
BEGIN
   -- while loop execution 
   WHILE val < 20 LOOP
      dbms_output.put_line ('value is: ' || val);
      val := val + 1;
      IF val = 15 THEN
         val := val + 1;
         CONTINUE; -- skip the loop using the CONTINUE statement
      END IF;
   END LOOP;
END;
/