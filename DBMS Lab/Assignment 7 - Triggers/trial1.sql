SET SERVEROUTPUT ON;

create or replace trigger before_product_insert
before insert on products for each row

declare
	rowcount int;
    
begin
    select count(*) into rowcount
    from products where food=new.food and flavor=new.flavor;
    
    if rowcount > 0 then
        dbms_output.put_line('product combination already present');
    else
        insert into products(pid, flavor, food, price)
        values(new.pid,new.flavor,new.food,new.price);
    end if; 
end;
