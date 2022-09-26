declare
    inrno item_list.rno%type;
    cursor c1 is select * from item_list where rno=inrno;
    hold c1%rowtype;
    record item_list%rowtype;
    
begin
    inrno:='&receipt_no';
    open c1;
    fetch c1 into hold;
    close c1;
    select * into record from item_list where rno=inrno;
    dbms_output.put_line('The given receipt '||inrno||' contains exactly one item');
exception
    when NO_DATA_FOUND then
        dbms_output.put_line('No orders with receipt no:'||inrno);
    when too_many_rows then
        dbms_output.put_line('The given receipt '||inrno||' contains more than one item');
end;
/



create or replace trigger checkdate
before insert on receipts
for each row

declare
    dateexception exception;
    today date;
begin
    select SYSDATE into today from dual;
    if(:NEW.rdate>today) THEN
        raise dateexception; 
    end if;

exception
    when dateexception then
        raise_application_error(-20004,'Receipt date greater than today');
end;
/

insert into receipts values(71253,'22-May-2022',20,21.12);