-- Consider the following relations for the Bakery database:
-- CUSTOMERS (cid, fname, lname)
-- PRODUCTS (pid, flavor, food, price)
-- RECEIPTS (rno, rdate, cid)
-- ITEM_LIST (rno, ordinal, item)

SET SERVEROUTPUT ON;

-- Write a PL/SQL stored procedure for the following:

-- 1. For the given receipt number, calculate the Discount as follows:
-- For total amount > $10 and total amount < $25: Discount=5%
-- For total amount > $25 and total amount < $50: Discount=10%
-- For total amount > $50: Discount=20%
-- Calculate the amount (after the discount) and update the same in Receipts table.

CREATE OR REPLACE PROCEDURE PRINTRECEIPT
(ORDER_NUMBER IN ITEM_LIST.RNO%TYPE)
IS
	CFNAME CUSTOMERS.FNAME%TYPE;
	CLNAME CUSTOMERS.LNAME%TYPE;
	RECDATE RECEIPTS.RDATE%TYPE;
	-- TOTAL_ITEM NUMBER:=0;
	TOTAL_PRICE NUMBER:=0;
	DISCOUNT NUMBER:=0;
	CURSOR DETAILS IS SELECT FOOD,FLAVOR,PRICE,COUNT(*) AS QUANTITY FROM ITEM_LIST,PRODUCTS WHERE RNO=ORDER_NUMBER AND PID=ITEM GROUP BY FOOD,FLAVOR,PRICE;
	DETAILROW DETAILS%ROWTYPE;
BEGIN
	SELECT FNAME,LNAME,RDATE INTO CFNAME,CLNAME,RECDATE FROM CUSTOMERS JOIN RECEIPTS USING(CID) WHERE RNO=ORDER_NUMBER;
	DBMS_OUTPUT.PUT_LINE('RECEIPT NUMBER: '||ORDER_NUMBER);
	DBMS_OUTPUT.PUT_LINE('CUSTOMER NAME: '||CFNAME||' '||CLNAME);
	DBMS_OUTPUT.PUT_LINE('RECEIPT DATE: '||RECDATE);
	OPEN DETAILS;
	DBMS_OUTPUT.PUT_LINE('FOOD			FLAVOR			 QUANTITY');
	LOOP
		FETCH DETAILS INTO DETAILROW;
		IF DETAILS%NOTFOUND THEN
			EXIT;
		ELSE
			DBMS_OUTPUT.PUT_LINE(DETAILROW.FOOD||'			 '||DETAILROW.FLAVOR||'			 '||DETAILROW.QUANTITY);
			-- TOTAL_ITEM:=TOTAL_ITEM+DETAILROW.QUANTITY;
			TOTAL_PRICE:=TOTAL_PRICE+DETAILROW.QUANTITY*DETAILROW.PRICE;
		END IF;
	END LOOP;
	DBMS_OUTPUT.PUT_LINE('TOTAL AMOUNT :$ '||TOTAL_PRICE);
	IF TOTAL_PRICE<=10 THEN
		DBMS_OUTPUT.PUT_LINE('NO DISCOUNT');
	END IF;
	IF TOTAL_PRICE>10 AND TOTAL_PRICE<25 THEN
		DISCOUNT:=0.05*TOTAL_PRICE;
		DBMS_OUTPUT.PUT_LINE('DISCOUNT (5%) :$ '||DISCOUNT);
	END IF;
	IF TOTAL_PRICE<50 THEN
		DISCOUNT:=0.1*TOTAL_PRICE;
		DBMS_OUTPUT.PUT_LINE('DISCOUNT (10%) :$ '||DISCOUNT);
	END IF;
	IF TOTAL_PRICE>=50 THEN
		DISCOUNT:=0.2*TOTAL_PRICE;
		DBMS_OUTPUT.PUT_LINE('DISCOUNT (20%) :$ '||DISCOUNT);
	END IF;
	CLOSE DETAILS;
	TOTAL_PRICE:=TOTAL_PRICE-DISCOUNT;
	DBMS_OUTPUT.PUT_LINE('AMOUNT TO BE PAID $ '||TOTAL_PRICE);
	EXCEPTION
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('INVALID ORDER NUMBER!');
END;
/

CALL PRINTRECEIPT(13355);


-- 2. Ask the user for the budget and his/her preferred food type. You recommend the best
-- item(s) within the planned budget for the given food type. The best item is
-- determined by the maximum ordered product among many customers for the given
-- food type.


CREATE OR REPLACE PROCEDURE BUDGETFOOD
(BUDGET IN NUMBER,FOODTYPE IN PRODUCTS.FOOD%TYPE)
IS
	CURSOR ITEMLIST_CURSOR IS SELECT PID,FOOD,FLAVOR,PRICE FROM PRODUCTS WHERE FOOD=FOODTYPE AND PRICE<BUDGET;
	PRODUCTROW ITEMLIST_CURSOR%ROWTYPE;
	CNT NUMBER:=0;
	FLAG NUMBER:=0;
	PIID ITEM_LIST.ITEM%TYPE;
	FLAVOR PRODUCTS.FLAVOR%TYPE;
	PRODUCTPRICE PRODUCTS.PRICE%TYPE;
	ITEMSINBAG NUMBER;

BEGIN
	DBMS_OUTPUT.PUT_LINE('BUDGET:'||BUDGET||'	'||'FOOD:'||FOODTYPE);
	DBMS_OUTPUT.PUT_LINE('');
	DBMS_OUTPUT.PUT_LINE('ITEM ID	FOOD	FLAVOR	PRICE');
	OPEN ITEMLIST_CURSOR;
	LOOP
		FETCH ITEMLIST_CURSOR INTO PRODUCTROW;
		IF ITEMLIST_CURSOR%NOTFOUND THEN
			EXIT;
		END IF;
		SELECT COUNT(*) INTO FLAG FROM ITEM_LIST WHERE ITEM=PRODUCTROW.PID;
		IF FLAG>CNT THEN
			CNT:=FLAG;
			PIID:=PRODUCTROW.PID;

		END IF;
		DBMS_OUTPUT.PUT_LINE(PRODUCTROW.PID||'	'||PRODUCTROW.FOOD||'	'||PRODUCTROW.FLAVOR||'	'||PRODUCTROW.PRICE);
	END LOOP;
	CLOSE ITEMLIST_CURSOR;
	SELECT FLAVOR INTO FLAVOR FROM PRODUCTS WHERE PID=PIID;
	SELECT PRICE INTO productprice FROM PRODUCTS WHERE PID=PIID;
	DBMS_OUTPUT.PUT_LINE('');
	DBMS_OUTPUT.PUT_LINE('THE ITEM WITH ID '||PIID||' AND '||FLAVOR||' IS THE BEST CHOICE FOR YOU');
	ITEMSINBAG:=BUDGET/productprice;
	DBMS_OUTPUT.PUT_LINE('YOU CAN BUY A MAXIMUM OF '||ITEMSINBAG||' ITEM OF THIS PRODUCT');
	DBMS_OUTPUT.PUT_LINE('');

END;
/

call BUDGETFOOD(10,'Meringue');


-- 3. Take a receipt number and item as arguments, and insert this information into the
-- Item list. However, if there is already a receipt with that receipt number, then keep
-- adding 1 to the maximum ordinal number. Else before inserting into the Item list
-- with ordinal as 1, ask the user to give the customer name who placed the order and
-- insert this information into the Receipts.


--PROCEDURE TO INSERT INTO ITEM_LIST
CREATE OR REPLACE PROCEDURE INSITEM
(RECEIPTNO_TO_INS IN RECEIPTS.RNO%TYPE, ORDINAL_TO_INS IN ITEM_LIST.ORDINAL%TYPE, PRODID_TO_INS IN PRODUCTS.PID%TYPE) IS

BEGIN
	INSERT INTO ITEM_LIST VALUES(RECEIPTNO_TO_INS,ORDINAL_TO_INS,PRODID_TO_INS);
END;
/

--PROCEDURE TO INSERT INTO RECEIPTS
CREATE OR REPLACE PROCEDURE INSERT_INTO_RECEIPT
(RECEIPTNO_TO_INS IN RECEIPTS.RNO%TYPE, DATE_TO_INS IN RECEIPTS.RDATE%TYPE,CUSTID_TO_INS IN RECEIPTS.CID%TYPE) IS
BEGIN 
	INSERT INTO RECEIPTS VALUES(RECEIPTNO_TO_INS,DATE_TO_INS,CUSTID_TO_INS);
END;
/

--PROCEDURE TO FIND CUSTOMER WITH GIVEN NAME AND RETURN CUSTOMER ID
CREATE OR REPLACE PROCEDURE SEARCH_CUSTOMER
(CUST_FNAME IN CUSTOMERS.FNAME%TYPE, CUST_LNAME IN CUSTOMERS.LNAME%TYPE,CUSTID_SAVE OUT CUSTOMERS.CID%TYPE) IS
BEGIN
	BEGIN
		SELECT CID INTO CUSTID_SAVE FROM CUSTOMERS
		WHERE FNAME=CUST_FNAME AND LNAME=CUST_LNAME;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('CUSTOMER ID NOT IN CUSTOMER TABLE');
		CUSTID_SAVE:=0;
	END;
END;
/

DECLARE

	CUSTFNAME CUSTOMERS.FNAME%TYPE;
	CUSTLNAME CUSTOMERS.LNAME%TYPE;
	CUSTID CUSTOMERS.CID%TYPE;
	RECEIPTNO_TO_INS RECEIPTS.RNO%TYPE;
	ORDINAL_TO_INS ITEM_LIST.ORDINAL%TYPE;
	PRODID_TO_INS PRODUCTS.PID%TYPE;
	DATE_TO_INS RECEIPTS.RDATE%TYPE;
	ITEM_ROW ITEM_LIST%ROWTYPE;
	CURSOR ITEMLIST_CURSOR IS SELECT * FROM ITEM_LIST I WHERE I.RNO=RECEIPTNO_TO_INS ORDER BY I.ORDINAL DESC;
	MAXORDI ITEM_LIST.ORDINAL%TYPE;

BEGIN

	RECEIPTNO_TO_INS:='&RECEIPT_NO';
	PRODID_TO_INS:='&PRODUCT_ID';
	OPEN ITEMLIST_CURSOR;
	FETCH ITEMLIST_CURSOR INTO item_row;
	IF ITEMLIST_CURSOR%ROWCOUNT>0 THEN
		BEGIN
		ORDINAL_TO_INS:=item_row.ORDINAL+1;
		INSITEM(RECEIPTNO_TO_INS,ORDINAL_TO_INS,PRODID_TO_INS);
		RETURN;
		END;
	ELSE
		BEGIN
		DBMS_OUTPUT.PUT_LINE('RECEIPT NOT FOUND');
		DBMS_OUTPUT.PUT_LINE('CREATING NEW RECEIPT');
		CUSTFNAME:='&FIRST_NAME';
		CUSTLNAME:='&LAST_NAME';
		DATE_TO_INS:='&DATE';
		SEARCH_CUSTOMER(CUSTFNAME,CUSTLNAME,CUSTID);
		INSERT_INTO_RECEIPT(RECEIPTNO_TO_INS,DATE_TO_INS,CUSTID);
		ORDINAL_TO_INS:=1;
		INSITEM(RECEIPTNO_TO_INS,ORDINAL_TO_INS,PRODID_TO_INS);
		RETURN;
		END;
	END IF;
END;
/
ROLLBACK;

-- 4. Write a stored function to display the customer name who ordered maximum for the
-- given food and flavor.

CREATE OR REPLACE FUNCTION MOST_CUST 
(GIVENFOOD PRODUCTS.FOOD%TYPE, GIVENFLAVOR PRODUCTS.FLAVOR%TYPE) 
RETURN CUSTOMER.CNAME%TYPE
 AS

	CUST_NAME CUSTOMER.CNAME%TYPE;

BEGIN
	SELECT FNAME ||' '|| LNAME 
	INTO CUST_NAME 
	FROM CUSTOMERS
	WHERE CID = (
		SELECT CID FROM (
		 SELECT A.CID, COUNT(*) 
		 FROM CUSTOMERS A, PRODUCTS B, ITEM_LIST C, RECEIPTS D 
		 WHERE A.CID = D.CID AND C.RNO = D.RNO AND C.ITEM = B.PID AND B.FOOD = GIVENFOOD AND FLAVOR = GIVENFLAVOR 
		 GROUP BY A.CID ORDER BY 2 DESC)
		WHERE ROWNUM = 1);
		
RETURN CUST_NAME;
END;
/

---CALLING FUNCTION FROM ANONYMOUS BLOCK

DECLARE

	CUSTNAME VARCHAR(15);
	prodid_to_ins PRODUCTS.PID%TYPE;
	GIVENFOOD PRODUCTS.FOOD%TYPE;
	GIVENFLAVOR PRODUCTS.FLAVOR%TYPE;

BEGIN

	GIVENFOOD:='&FOOD';
	GIVENFLAVOR:='&FLAVOR';
	CUSTNAME:=MOST_CUST(GIVENFOOD,GIVENFLAVOR);
	DBMS_OUTPUT.PUT_LINE('THE CUSTOMER WHO BOUGHT MAXIMUM OF '||GIVENFOOD||' IN '||GIVENFLAVOR||' FLAVOR IS:'||CUSTNAME);
END;
/

rollback;


-- 5. Implement Question (2) using stored function to return the amount to be paid and
-- update the same, for the given receipt number.


