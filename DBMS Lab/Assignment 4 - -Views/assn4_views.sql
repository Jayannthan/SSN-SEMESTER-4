-- Consider the schema used in the Assignment3.

-- Create the following views and perform DML operations on it. Classify whether the view is updatable or not.

-- 1. Create a view named Blue_Flavor, which display the product details (product id,
-- food, price) of Blueberry flavor.

DROP VIEW Blue_Flavor;
-- Creating view
CREATE VIEW Blue_Flavor
AS
    SELECT PID, FOOD, PRICE
    FROM PRODUCTS
    WHERE FLAVOR='Blueberry';

-- DESC Blue_Flavor;

--displaying items in Blue_Flavor
SELECT *
FROM Blue_Flavor;

--viewing the updatable columns in Blue_Flavor
SELECT COLUMN_NAME, UPDATABLE
FROM USER_UPDATABLE_COLUMNS
WHERE
TABLE_NAME='BLUE_FLAVOR';

--  CREATING A SAVEPOINT
SAVEPOINT VIEW1;

--inserting a tuple in products with flavour="Blueberry"
INSERT INTO PRODUCTS
VALUES
    ('20-Ch', 'Blueberry', 'Chocolate', 15);


--displaying items in Blue_Flavor after adding tuple in products
SELECT *
FROM Blue_Flavor;

--updating a tuple in Blue_Flavor
UPDATE Blue_Flavor
SET PRICE=PRICE*1.15
WHERE PID='20-Ch';

--displaying items in Blue_Flavor after updating
SELECT *
FROM Blue_Flavor
WHERE PID ='20-Ch';

--displaying items in base table after updating 
SELECT *
FROM PRODUCTS
WHERE PID ='20-Ch';


--deleting a tuple in Blue_Flavor
DELETE FROM Blue_Flavor WHERE PID='20-Ch';

--displaying items in Blue_Flavor after deleting
SELECT *
FROM Blue_Flavor
WHERE PID ='20-Ch';

--displaying items in base table after deleting
SELECT *
FROM PRODUCTS
WHERE PID ='20-Ch';

--ROLLINGBACK TO SAVEPOINT
ROLLBACK
TO VIEW1;

--SAVING PROGRESS
COMMIT;

-- 2. Create a view named Cheap_Food, which display the details (product id, flavor,
-- food, price) of products with price lesser than $1. Ensure that, the price of these
-- food(s) should never rise above $1 through view.

DROP VIEW Cheap_Food;
-- Creating view
CREATE VIEW Cheap_Food
AS
    SELECT PID, FLAVOR, FOOD, PRICE
    FROM PRODUCTS
    WHERE PRICE < 1 
WITH CHECK OPTION;

-- DESC Cheap_Food;

-- Displaying the contents of the Cheap_Food
SELECT *
FROM Cheap_Food;

--viewing the updatable columns in Cheap_Food
SELECT COLUMN_NAME, UPDATABLE
FROM USER_UPDATABLE_COLUMNS
WHERE
TABLE_NAME='CHEAP_FOOD';

--  CREATING A SAVEPOINT
SAVEPOINT VIEW2;


--inserting a tuple in Cheap_Food

insert INTO Cheap_Food
values
    ('20-Ch1', 'Mango', 'Chocolate', 0.75);


--inserting a tuple in Cheap_Food with price>1

insert INTO Cheap_Food
values
    ('20-Ch2', 'Man', 'Choco', 1.75);


--displaying items in Cheap_Food after insertion
SELECT *
FROM Cheap_Food
WHERE PID='20-Ch1';

--displaying items in base table after insertion
SELECT *
FROM PRODUCTS
WHERE PID='20-Ch1';

--updating a tuple in Cheap_Food
UPDATE Cheap_Food
SET PRICE=PRICE+0.1
WHERE PID='20-Ch1';

--displaying items in Cheap_Food after updating
SELECT *
FROM Cheap_Food
WHERE PID ='20-Ch1';

--displaying items in base table after updating
SELECT *
FROM PRODUCTS
WHERE PID='20-Ch1';


--deleting a tuple in Cheap_Food
DELETE FROM Cheap_Food WHERE PID='20-Ch1';

--displaying items in Cheap_Food after deleting
SELECT *
FROM Cheap_Food
WHERE PID ='20-Ch1';


--displaying items in base table after deleting
SELECT *
FROM PRODUCTS
WHERE PID='20-Ch1';




--ROLLINGBACK TO SAVEPOINT
ROLLBACK
TO VIEW2;

--SAVING PROGRESS
COMMIT;

-- 3. Create a view called Hot_Food that show the product id and its quantity WHERE the
-- same product is ordered more than once in the same receipt.

DROP VIEW Hot_Food;

-- Creating view
CREATE VIEW Hot_Food
(
    pid,
    count
)
AS
    SELECT ITEM, COUNT(ITEM)
    FROM ITEM_LIST
    GROUP BY RNO,ITEM
    HAVING COUNT(*)>1;


-- DESC Hot_Food;

--displaying items in Hot_Food
SELECT *
FROM Hot_Food;

--viewing the updatable columns in Hot_Food
SELECT COLUMN_NAME, UPDATABLE
FROM USER_UPDATABLE_COLUMNS
WHERE
TABLE_NAME='HOT_FOOD';
-- This table isnt updatable because we have used aggregate functions (group by class)


--  CREATING A SAVEPOINT
SAVEPOINT VIEW3;

--inserting a tuple in Cheap_Food
INSERT INTO Hot_Food
VALUES('50-AB', 3);


-- updating item in Hot_Food
UPDATE Hot_Food
SET ITEM='54-SD9-34JS'
WHERE ITEM='46-11';

--updating quantity in Hot_Food
UPDATE Hot_Food
SET QUANTITY=4
WHERE ITEM='46-11';

--deleting a row in Hot_Food
DELETE FROM Hot_Food WHERE ITEM='46-11';


-- making changes in base table to see reflection
INSERT INTO PRODUCTS
VALUES('9-B', 'ORANGE', 'JUICE', 9);
INSERT INTO RECEIPTS
VALUES(12345, '9-JUN-22', 21);
INSERT INTO ITEM_LIST
VALUES(12345, 98, '9-B');
INSERT INTO ITEM_LIST
VALUES(12345, 99, '9-B');

SELECT *
from Hot_food;
-- note the changes in counts
-- making changes in the base table reflects in the view but not vice versa

--ROLLINGBACK TO SAVEPOINT
ROLLBACK
TO VIEW3;

--SAVING PROGRESS
COMMIT;


-- 4. Create a view named Pie_Food that will display the details (customer lname, flavor, 
-- receipt number and date, ordinal) who had ordered the Pie food with receipt details.

DROP VIEW Pie_Food;

-- Creating view
CREATE VIEW Pie_Food
AS
    SELECT LNAME, FLAVOR, R.RNO, RDATE, ORDINAL
    FROM CUSTOMERS C, RECEIPTS R, ITEM_LIST I, PRODUCTS P
    WHERE C.CID=R.CID AND R.RNO=I.RNO AND I.ITEM=P.PID AND FOOD='Pie';

--displaying items in Pie_Food
SELECT *
FROM Pie_Food;

--viewing the updatable columns in Pie_Food
SELECT COLUMN_NAME, UPDATABLE
FROM USER_UPDATABLE_COLUMNS
WHERE
TABLE_NAME='PIE_FOOD';

-- THIS VIEW ISNT UPDATABLE BECAUSE WE HAVE JOINED MULTIPLE TABLE AND THE NOT NULL COLUMNS FROM PRODUCTS , CUSTOMERS (PK) ARENT A PART OF THE VIEW

--  CREATING A SAVEPOINT
SAVEPOINT VIEW4;


--inserting a tuple in Pie_Food
INSERT INTO Pie_Food
VALUES('Tony', 'Blueberry', 51991, '9-Jun-21', 98);


--displaying items in Pie_Food after inserting
SELECT *
FROM Pie_Food
WHERE LNAME='Steve';


--displaying items in base table after inserting
SELECT LNAME, FLAVOR, R.RNO, RDATE, ORDINAL
FROM CUSTOMERS C, RECEIPTS R, ITEM_LIST I, PRODUCTS P
WHERE C.CID=R.CID AND R.RNO=I.RNO AND I.ITEM=P.PID AND FOOD='Pie' AND LNAME='Tony';


--updating a tuple in Pie_Food
UPDATE Pie_Food SET LNAME='Steve' WHERE RNO=51991;

-- updating RNO
UPDATE Pie_Food SET RNO=51991 WHERE LNAME='Steve';

-- updating ORDINAL
UPDATE Pie_Food SET ORDINAL=99 WHERE LNAME='Steve';

-- updating FLAVOUR
UPDATE Pie_Food SET FLAVOR='NEW_FLAVOUR' WHERE LNAME='Steve';


--displaying items in Pie_Food after updating

SELECT *
from Pie_Food
WHERE LNAME='Steve';

--displaying items in base table after updating
SELECT LNAME, FLAVOR, R.RNO, RDATE, ORDINAL
FROM CUSTOMERS C, RECEIPTS R, ITEM_LIST I, PRODUCTS P
WHERE C.CID=R.CID AND R.RNO=I.RNO AND I.ITEM=P.PID AND FOOD='Pie' AND LNAME='Steve';

-- deleting a tuple in view
SELECT *
FROM Pie_Food
WHERE LNAME='Steve';

--displaying items in Pie_Food after deleting

SELECT *
from Pie_Food
WHERE LNAME='Steve';

--displaying items in base table after deleting
SELECT LNAME, FLAVOR, R.RNO, RDATE, ORDINAL
FROM CUSTOMERS C, RECEIPTS R, ITEM_LIST I, PRODUCTS P
WHERE C.CID=R.CID AND R.RNO=I.RNO AND I.ITEM=P.PID AND FOOD='Pie' AND LNAME='Steve';


--ROLLINGBACK TO SAVEPOINT
ROLLBACK
TO VIEW4;

--SAVING PROGRESS
COMMIT;

-- 5. Create a view Cheap_View from Cheap_Food that shows only the product id, flavor
-- and food.

-- Creating view
CREATE VIEW Cheap_View
AS
    SELECT PID, FLAVOR, FOOD
    FROM CHEAP_FOOD;

--displaying items in Cheap_View
SELECT *
FROM Cheap_View;

--viewing the updatable columns in Cheap_View
SELECT COLUMN_NAME, UPDATABLE
FROM USER_UPDATABLE_COLUMNS
WHERE
TABLE_NAME='CHEAP_VIEW';


--  CREATING A SAVEPOINT
SAVEPOINT NEW_VIEW;

--inserting a tuple in Cheap_View
insert INTO Cheap_food
VALUES('20-Ch', 'Mango', 'Chocolate');

--displaying items in Cheap_View after inserting
SELECT *
from Cheap_View
WHERE PID='20-Ch';

--displaying items in Cheap_Food after inserting
SELECT *
from Cheap_Food
WHERE PID='20-Ch';

--updating a tuple in Pie_Food

UPDATE Cheap_View SET PID='20-Ch1' WHERE PID='20-Ch';
UPDATE Cheap_View SET FLAVOR='NEW_FLAVOUR' WHERE PID='20-Ch1';
UPDATE Cheap_View SET FOOD='New_Food' WHERE PID='20-Ch1';

--displaying items in Cheap_View after updating
SELECT *
from Cheap_View
WHERE PID='20-Ch1';

--displaying items in Cheap_Food after updating
SELECT *
from Cheap_Food
WHERE PID='20-Ch1';


DELETE FROM Cheap_View WHERE PID='20-Ch1';
DELETE FROM Cheap_View WHERE FOOD='New_Food';


--displaying items in Cheap_View after deleting
SELECT *
from Cheap_View
WHERE PID='20-Ch1';

--displaying items in Cheap_Food after deleting
SELECT *
from Cheap_Food
WHERE PID='20-Ch1';


--ROLLINGBACK TO SAVEPOINT
ROLLBACK
TO NEW_VIEW;

--SAVING PROGRESS
COMMIT;



-- 6. Drop the view Cheap_View

DROP VIEW Cheap_View;

