-- this is a comment
--
/* this
   is
   a 
   comment
*/
DECLARE
   btest  BOOLEAN := FALSE;
   message  varchar2(20):= 'Hello, World!';
BEGIN
   if btest then
     dbms_output.put_line(message || 'Welcome to COP 4703' || '*****, '   || 'and have a since day!!');
   else
     dbms_output.put_line(message || 'Welcome...' || '*****, ');
   end if;

END;
/
