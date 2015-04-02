-- try this program as is, then change variable name sum to sum & retry, 
-- explain what happened.
DECLARE
  firstValue  integer := 5;
  secondValue integer := 15;
  sum integer;
  ratio real;
BEGIN
  sum := firstValue + secondValue ;

  dbms_output.put_line('The sum is: '|| sum);

  ratio := firstValue/secondValue;

  dbms_output.put_line('Ratio is: ' || ratio);
END;
/