DECLARE
   type playersarray IS VARRAY(5) OF VARCHAR2(30);
   type scores IS VARRAY(5) OF INTEGER;
   names playersarray;
   points scores;
   total integer;
BEGIN
   names := playersarray ('Wade', 'Curry', 'Alan', 'Lin', 'Bass');
   points:= scores (25, 43, 12, 23, 9);
   total := names.count;
   dbms_output.put_line('Total ='|| total || ' players');
   FOR i in 1 .. total LOOP
      dbms_output.put_line('Player: ' || names(i) || '
      Scored: ' || points(i));
   END LOOP;
END;
/