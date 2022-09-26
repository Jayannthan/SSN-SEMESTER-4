DECLARE
TEMP NUMBER(3);
BEGIN
TEMP:=3;
DBMS_OUTPUT.PUT_LINE( 'VALUE OF TEMP IS = ' || TEMP );
END;

CREATE PROCEDURE TESTPROCEDURE
BEGIN
INSERT INTO Student VALUES (5, 'Joe');
END;

CREATE PROCEDURE SELECTALLCUSTOMERS
AS
SELECT * FROM CUSTOMERS
GO;

BEGIN
   DBMS_OUTPUT.put_line ('Hello World!');
END;


CREATE PROCEDURE TESTPROCEDURE1 (num IN int) IS
BEGIN
    INSERT INTO t VALUES (num);
END;

-- An user desired to buy the product with the specific price. Ask the user for a price,
-- find the food item(s) that is equal or closest to the desired price. Print the product
-- number, food type, flavor and price. Also print the number of items that is equal or
-- closest to the desired price.
DROP PROCEDURE SPEC_COST;
CREATE PROCEDURE SPEC_COST(num in int) IS
BEGIN
    DBMS_OUTPUT.PUT_LINE( 'ENTER VALUE FOR DPRICE = ' || num);
END;
/
execute SPEC_COST (num=>10);


FOR i in 1 .. 5 LOOP
INSERT INTO t values (10 + i);
END LOOP;

DECLARE 
begin
    FOR i in 1 .. 5 LOOP
    INSERT INTO t values (10 + i);
    END LOOP;
end;
/
