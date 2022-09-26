-- Consider the following relations for the Bakery database:
-- CUSTOMERS (cid, fname, lname)
-- PRODUCTS (pid, flavor, food, price)
-- RECEIPTS (rno, rdate, cid)
-- ITEM_LIST (rno, ordinal, item)

SET SERVEROUTPUT ON;

-- Write a PL/SQL block to handle the following exceptions:
-- 1. For the given receipt number, if there are no rows then display as “No order with the
-- given receipt <number>”. If the receipt contains more than one item, display as
-- “The given receipt <number> contains more than one item”. If the receipt contains
-- single item, display as “The given receipt <number> contains exactly one item”. Use
-- predefined exception handling.

DECLARE
	RNO_INPUT ITEM_LIST.RNO%TYPE;
	CURSOR ITEM_LIST_CURSOR IS SELECT * FROM ITEM_LIST WHERE RNO=RNO_INPUT;
	ITEM_LIST_ROW ITEM_LIST_CURSOR%ROWTYPE;
	
BEGIN
	RNO_INPUT:='&RECEIPT_NO_INPUT';
	OPEN ITEM_LIST_CURSOR;
	FETCH ITEM_LIST_CURSOR INTO ITEM_LIST_ROW;
	CLOSE ITEM_LIST_CURSOR;
	SELECT * INTO ITEM_LIST_ROW FROM ITEM_LIST WHERE RNO=RNO_INPUT;
	DBMS_OUTPUT.PUT_LINE('THE GIVEN RECEIPT '||RNO_INPUT||' CONTAINS EXACTLY ONE ITEM');
EXCEPTION
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('NO ORDER WITH THE GIVEN RECEIPT '||RNO_INPUT);
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('THE GIVEN RECEIPT '||RNO_INPUT||' CONTAINS MORE THAN ONE ITEM');
END;
/

-- 2. While inserting the receipt details, raise an exception when the receipt date is greater
-- than the current date.

CREATE OR REPLACE TRIGGER CHECKINSDATE
BEFORE INSERT ON RECEIPTS FOR EACH ROW

DECLARE
	THROWEXCEPTION EXCEPTION;
	TODAYDATE DATE;
BEGIN
	SELECT SYSDATE INTO TODAYDATE FROM DUAL;
	IF(:NEW.RDATE>TODAYDATE) THEN
		RAISE THROWEXCEPTION; 
	END IF;

EXCEPTION
	WHEN THROWEXCEPTION THEN
		RAISE_APPLICATION_ERROR(-20009,'RECEIPT DATE GREATER THAN TODAYDATE');
END;
/