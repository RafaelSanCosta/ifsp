create trigger dbo.trigger_prevent_assignment_teaches on dbo.teaches
after insert as
begin
	if exists(
		select 1 /*o if verifica se a linha existe*/
		from inserted as i /*verifica na linha inserida*/
		join teaches as t
		on t.id = i.id and t.year = i.year 
		group by t.id, t.year /*filtra por instrutor e ano*/
		having count(*) > 2); /*caso tenha mais q 2 aulas por ano*/
	begin /*cai nesse begin*/
		RAISERROR ('A instructor can not have more than two sections.', 16, 1);/*onde um erro é levantado*/
		rollback transaction;/*a inserção é desfeita*/
		return;
	end
end; /*e fim*/
