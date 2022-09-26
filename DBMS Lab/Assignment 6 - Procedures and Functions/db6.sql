---DBMS ASSIGNMENT 6---
commit;

---1. For the given receipt number, calculate the Discount as follows:
---For total amount > $10 and total amount < $25: Discount=5%
---For total amount > $25 and total amount < $50: Discount=10%
---For total amount > $50: Discount=20%
---Calculate the amount (after the discount) and update the same in Receipts table

---dropping procedures
drop procedure calcdisc;

---creating procedure
create procedure calcdisc (recno in number) is

total float;
percent int;
disc float;
dop date;
sno int := 0;
cust_fname customers.fname%type;
cust_lname customers.lname%type;
cursor c1 is
select flavor, food, price from products, item_list
where products.pid = item_list.item and item_list.rno = recno;
hold c1%rowtype;

begin
	select sum(price) into total from item_list join products
	on item_list.item = products.pid where item_list.rno = recno;
	if total > 50 then
		percent := 20;
	elsif total > 25 then
		percent := 10;
	elsif total > 10 then
		percent := 5;
	else
		percent := 0;
	end if;
	
	disc := percent * total / 100;

	dbms_output.put_line('**************************************');
	dbms_output.put_line('Receipt Number : ' || recno);
	
	select rdate into dop from receipts
	where rno = recno;

	dbms_output.put_line('Receipt Date : ' || dop);

	select fname, lname into cust_fname, cust_lname from customers, receipts
	where customers.cid = receipts.cid and receipts.rno = recno;

	dbms_output.put_line('Customer Name : ' || cust_fname || ' ' || cust_lname); 
	dbms_output.put_line('**************************************');
	dbms_output.put_line('Sno     Flavor     Food     Price');
	dbms_output.put_line('--------------------------------------');
    open c1;
	loop
		fetch c1 into hold;
		if c1%notfound then
			exit;
		end if;
		sno := sno + 1;
		dbms_output.put_line(sno || '     ' || hold.flavor || '     ' || hold.food || '     ' || hold.price);
	end loop;
    close c1;
	dbms_output.put_line('--------------------------------------');
	dbms_output.put_line('Total Amount : $' || total);
	dbms_output.put_line('Discount(' || percent || '%) : $' || disc);
	dbms_output.put_line('--------------------------------------');

	total := total - disc;
	dbms_output.put_line('Amount to be paid : $' || total);
	dbms_output.put_line('**************************************');
end;
/

exec calcdisc(13355);

rollback;

---2. Ask the user for the budget and his/her preferred food type. You recommend the best 
---item(s) within the planned budget for the given food type. The best item is 
---determined by the maximum ordered product among many customers for the given 
---food type. Print the recommended product that suits your budget

---dropping procedures
drop procedure suggest;


---creating procedure
create procedure suggest(eat in products.food%type,budget in number) is

cursor c1 is select pid,food,flavor,price from products where food=eat and price<budget;
hold c1%rowtype;
cnt number:=0;
flg number:=0;
prodid item_list.item%type;
flav products.flavor%type;
rate products.price%type;
bag number;

begin
    dbms_output.put_line('***************************************************');
    dbms_output.put_line('Budget:'||budget||'           '||'Food:'||eat);
    dbms_output.put_line('***************************************************');
    dbms_output.put_line('Item Id               Food                Flavor              Price');
    open c1;
    loop
        fetch c1 into hold;
        if c1%notfound then
            exit;
        end if;
        select count(*) into flg from item_list where item=hold.pid;
        if flg>cnt then
            cnt:=flg;
            prodid:=hold.pid;

        end if;
        dbms_output.put_line(hold.pid||'          '||hold.food||'           '||hold.flavor||'             '||hold.price);
    end loop;
    close c1;
    select flavor into flav from products where pid=prodid;
    select price into rate from products where pid=prodid;
    dbms_output.put_line('*****************************************************');
    dbms_output.put_line('The item with id '||prodid||' and '||flav||' is the best choice for you');
    bag:=budget/rate;
    dbms_output.put_line('You can buy a maximum of '||bag||' item of this product');
    dbms_output.put_line('*****************************************************');
end;
/

exec suggest('Meringue',10);

rollback;

---3. Take a receipt number and item as arguments, and insert this information into the 
---Item list. However, if there is already a receipt with that receipt number, then keep 
---adding 1 to the maximum ordinal number. Else before inserting into the Item list 
---with ordinal as 1, ask the user to give the customer name who placed the order and 
---insert this information into the Receipts.

---dropping procedures
drop procedure insrec;
drop procedure insitem;
drop procedure findcus;

--procedure to insert into item_list
create or replace procedure insitem
(recno in receipts.rno%type, ord in item_list.ordinal%type, prodid in products.pid%type) is

begin
	insert into item_list values(recno,ord,prodid);
end;
/

--procedure to insert into receipts
create or replace procedure insrec
(recno in receipts.rno%type, r_date in receipts.rdate%type,rcid in receipts.cid%type) is
begin 
	insert into receipts values(recno,r_date,rcid);
end;
/

--procedure to find customer with given name and return customer id
create or replace procedure findcus
(cfn in customers.fname%type, cln in customers.lname%type,cidout out customers.cid%type) is
begin
	begin
		select cid into cidout from customers
		where fname=cfn and lname=cln;
	exception
		when NO_DATA_FOUND then
		dbms_output.put_line('Customer Id unavailable');
		cidout:=0;
	end;
end;
/

declare

	custfname customers.fname%type;
	custlname customers.lname%type;
	custid customers.cid%type;
	recno receipts.rno%type;
	ord item_list.ordinal%type;
	prodid products.pid%type;
	r_date receipts.rdate%type;
	hold item_list%rowtype;
	cursor c1 is
	select * from item_list i where i.rno=recno order by i.ordinal desc;
	maxordi item_list.ordinal%type;

begin

	recno:=&receiptno;
	prodid:='&productid';
	open c1;
	fetch c1 into hold;
	if c1%rowcount>0 then
		begin
		ord:=hold.ordinal+1;
		insitem(recno,ord,prodid);
		return;
		end;
	else
		begin
		dbms_output.put_line('No receipts found');
		dbms_output.put_line('Create receipt');
		custfname:='&first_name';
		custlname:='&last_name';
		r_date:='&date';
		findcus(custfname,custlname,custid);
		insrec(recno,r_date,custid);
		ord:=1;
		insitem(recno,ord,prodid);
		return;
		end;
	end if;
end;
/

rollback;

---4. Write a stored function to display the customer name who ordered maximum for the 
---given food and flavor.

drop function richguy;

---creating function richguy
create function richguy(prodid in products.pid%type) return varchar2 as

custid customers.cid%type;
k int;
custfname customers.fname%type;
custlname customers.lname%type;
custname varchar(15);

begin
	select max(count(*)) into k from receipts r join item_list i on r.rno=i.rno
	where i.item=prodid group by r.cid;
	select r.cid into custid from receipts r join item_list i on r.rno=i.rno
	where i.item=prodid group by r.cid having count(*)=k;
	select fname into custfname from customers where cid=custid;
	select lname into custlname from customers where cid=custid;
	custname:=custlname||' '||custfname;
	return custname;
end richguy;
/

---calling function from anonymous block

declare

	custname varchar(15);
	prodid products.pid%type;
	fo products.food%type;
	fl products.food%type;

begin

	fo:='&Food';
	fl:='&Flavor';
	select pid into prodid from products where food=fo and flavor=fl;
	custname:=richguy(prodid);
	dbms_output.put_line('The customer who bought maximum of '||fo||' in '||fl||' Flavor is:'||custname);
end;
/

rollback;

---5. Implement Question (2) using stored function to return the amount to be paid and 
---update the same, for the given receipt number. 

---creating function discount
create or replace function discount 
(cost in products.price%type,disc out products.price%type,discprice out products.price%type)
return products.price%type is

selling products.price%type;

begin
	---disc:=0;
	---discprice:=0;
	if cost>10 and cost<25 then
		discprice:=0.05*cost;
		disc:=5;
	end if;
	if cost>25 and cost<50 then
		discprice:=0.1*cost;
		disc:=10;
	end if;
	if cost>50 then
		discprice:=.2*cost;
		disc:=20;
	end if;
	selling:=cost-discprice;
	return selling;
end;
/

---anonymmous block to call the function
    
declare
    total float;
    percent int;
    disc float;
    dop date;
    sno int := 0;
    cust_fname customers.fname%type;
    cust_lname customers.lname%type;
    recno receipts.rno%type;
    cursor c1 is
    select flavor, food, price from products, item_list
    where products.pid = item_list.item and item_list.rno = recno;
    hold c1%rowtype;
    selling products.price%type;
    

begin    
    recno:='&receipt_num';
    select sum(price) into total from item_list join products
	on item_list.item = products.pid where item_list.rno = recno;
    dbms_output.put_line('**************************************');
	dbms_output.put_line('Receipt Number : ' || recno);
	
	select rdate into dop from receipts
	where rno = recno;

	dbms_output.put_line('Receipt Date : ' || dop);

	select fname, lname into cust_fname, cust_lname from customers, receipts
	where customers.cid = receipts.cid and receipts.rno = recno;

	dbms_output.put_line('Customer Name : ' || cust_fname || ' ' || cust_lname); 
	dbms_output.put_line('**************************************');
	dbms_output.put_line('Sno     Flavor     Food     Price');
	dbms_output.put_line('--------------------------------------');
    open c1;
	loop
		fetch c1 into hold;
		if c1%notfound then
			exit;
		end if;
		sno := sno + 1;
		dbms_output.put_line(sno || '     ' || hold.flavor || '     ' || hold.food || '     ' || hold.price);
	end loop;
    close c1;

    selling:=discount(total,percent,disc);

    dbms_output.put_line('--------------------------------------');
	dbms_output.put_line('Total Amount : $' || total);
	dbms_output.put_line('Discount(' || percent || '%) : $' || disc);
	dbms_output.put_line('--------------------------------------');

	---total := total - disc;
	dbms_output.put_line('Amount to be paid : $' ||selling );
	dbms_output.put_line('**************************************');
end;
/

rollback;