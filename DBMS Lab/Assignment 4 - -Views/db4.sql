
-- rem ***1. Create a view named Blue_Flavor, which display the product details (product id, food, price) of Blueberry flavor. ***

-- rem *** creating view ***
create view Blue_flavor as(
select pid,food,price
from products
where flavor='Blueberry');

-- rem ***displaying contents of the view Blue_flavor ***
select * from Blue_flavor;

-- rem *** checking if updatable ***
select column_name, updatable from user_updatable_columns where
table_name='BLUE_FLAVOR';

-- rem *** inserting value into main table to check updation in view ***
insert into products values('14-K29H-2L','Blueberry','Cake',3.21);

-- rem *** displaying contents of the view ***
select * from Blue_flavor;

-- rem *** updating price in the view ***
update Blue_flavor
set price=price+1.5
where food='Cake';

-- rem *** ********************************************* ***

-- rem ***2. Create a view named Cheap_Food, which display the details (product id, flavor, ***
-- rem ***food, price) of products with price lesser than $1. Ensure that, the price of these ***
-- rem ***food(s) should never rise above $1 through view. ***

-- rem *** creating view ***
create view cheap_food as(
select pid,flavor,food,price from products
where price<1)
with check option;

-- rem *** trying to insert a value with price > 1***
insert into cheap_food values('24-L845-P3','Peanut','Bun',1.5);

-- rem ***3. Create a view called Hot_Food that show the product id and its quantity where the ***
-- rem ***same product is ordered more than once in the same receipt. ***

-- rem *** creating view ***
create view hot_food as(
select distinct(item),count(item) as quantity
from item_list
group by(item)
having count(rno)>1);

-- rem *** displaying the products ***
select * from hot_food;

-- rem ***4. Create a view named Pie_Food that will display the details (customer lname, flavor, ***
-- rem ***receipt number and date, ordinal) who had ordered the Pie food with receipt details. ***


-- rem ***5. Create a view Cheap_View from Cheap_Food that shows only the product id, flavor and food. ***

-- rem *** creating view ***
create view cheap_view as(
select pid,flavor,food from cheap_food);

-- rem *** displaying the contents ***
select * from cheap_view;

-- rem ***6. Drop the view Cheap_View ***

drop view cheap_view;