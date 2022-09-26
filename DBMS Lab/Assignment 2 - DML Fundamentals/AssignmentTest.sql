
-- nobel (noble_id, name, gender, category, field, year_award, aff_role, dob, country)

-- Write DML queries for the following:

--1.Display the nobel laureate(s) who born after 1-Jul-1960.
SELECT *
FROM NOBEL
WHERE DOB >('1-Jul-1960');

--2. Display the Indian laureate (name, category, field, country, year awarded) who was awarded in the Chemistry category.
SELECT NAME, CATEGORY, FIELD, COUNTRY, YEAR_AWARD
FROM NOBEL
WHERE COUNTRY='India' AND CATEGORY='Che';

-- 3. Display the laureates (name, category,field and year of award) who was awarded between 2000 and 2005 for the Physics or Chemistry category.
SELECT NAME, CATEGORY, FIELD, YEAR_AWARD
FROM NOBEL
WHERE (YEAR_AWARD BETWEEN 2001 AND 2005) AND (CATEGORY='Che' OR CATEGORY='Phy');

-- 4. Display the laureates name with their age at the time of award for the Peace category.
SELECT NAME, YEAR_AWARD-EXTRACT(YEAR FROM DOB) AS AGE, YEAR_AWARD
FROM NOBEL
WHERE CATEGORY='Pea';

-- 5. Display the laureates (name,category,aff_role,country) whose name starts with A or ends with a, but not from Isreal.
SELECT NAME, CATEGORY, AFF_ROLE, COUNTRY
FROM NOBEL
WHERE (NAME LIKE 'A%' OR NAME LIKE '%a') AND COUNTRY <> 'Isreal';

-- 6. Display the name, gender, affiliation, dob and country of laureates who was born in 1950's. Label the dob column as Born 1950.
SELECT NAME, GENDER, AFF_ROLE, DOB AS BORN1950, COUNTRY
FROM NOBEL
WHERE DOB >('1-Jan-1950') AND DOB < ('31-Dec-1959');


-- 7. Display the laureates (name,gender,category,aff_role,country) whose name starts with A, D or H. Remove the laureate if he/she do not have any affiliation. Sort the results in ascending order of name.
SELECT NAME, GENDER, CATEGORY, AFF_ROLE, COUNTRY
FROM NOBEL
WHERE (NAME LIKE 'A%' OR NAME LIKE 'D%' OR NAME LIKE 'H%') AND AFF_ROLE IS NOT NULL
ORDER BY NAME;

-- 8. Display the university name(s) that has to its credit by having at least 2 nobel laureate with them.
SELECT AFF_ROLE
FROM NOBEL
GROUP BY AFF_ROLE
HAVING COUNT(AFF_ROLE) > 1;

-- 9. List the date of birth of youngest and eldest laureates by countrywise. Label the column as Younger, Elder respectively. Include only the country having more than one laureate. Sort the output in alphabetical order of country.
SELECT COUNTRY, MAX(DOB) AS YOUNGEST, MIN(DOB) AS ELDEST
FROM NOBEL
GROUP BY COUNTRY
HAVING (COUNT(COUNTRY) >= 2 )
ORDER BY COUNTRY;


-- 10. Show the details (year award,category,field) where the award is shared among the laureates in the same category and field. Exclude the laureates from USA.
SELECT CATEGORY, FIELD, YEAR_AWARD
FROM NOBEL
WHERE COUNTRY <> 'USA'
GROUP BY FIELD,CATEGORY,YEAR_AWARD
HAVING(COUNT(*) >= 2);


-- Use TCL Statements

-- 11.Mark an intermediate point in the transaction (savepoint)
SAVEPOINT
save;

-- 12.Insert a new tuple into the nobel relation
INSERT INTO NOBEL
VALUES(129, 'Tony Stark', 'm', 'Phy', 'Physics', 2021, '', '17-DEC-1989', 'USA');
-- printing updated table
SELECT *
FROM NOBEL
WHERE NAME='Tony Stark';

-- 13.Update the aff_role of literature laureates as 'Linguists'.

SELECT *
FROM NOBEL
WHERE CATEGORY='Lit';

UPDATE NOBEL SET aff_role='Linguists' WHERE CATEGORY='Lit';

-- printing updated table
SELECT *
FROM NOBEL
WHERE CATEGORY='Lit';
SELECT *
FROM NOBEL;

-- 14.Delete the laureate(s) who was awarded in Enzymes field
SELECT *
FROM NOBEL
WHERE FIELD='Enzymes';

DELETE FROM NOBEL 
WHERE FIELD='Enzymes';

-- printing updated table
SELECT *
FROM NOBEL
WHERE FIELD='Enzymes';

-- 15.Discard the most recent update operations (rollback)

ROLLBACK
TO
save;

-- printing table after rollback
SELECT *
FROM NOBEL
WHERE FIELD='Enzymes';


-- 16.Commit the changes
Commit;