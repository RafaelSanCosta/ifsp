create procedure salaryHistogram @numIntervalos int
as
begin
    
	declare @minSalary decimal(10,2), 
            @maxSalary decimal(10,2), 
            @intervalo decimal(10,2),
            @i int,
            @vMin decimal(10,2),
            @vMax decimal(10,2);

    select 
        @minSalary = min(salary), 
        @maxSalary = max(salary)
    from instructor;

    set @intervalo = (@maxSalary - @minSalary) / @numIntervalos;

    create table Histogram (
        valorMinimo decimal(10,2),
        valorMaximo decimal(10,2),
        total int
    ); --cria tabela

    set @i = 0; --cria contador

    --inicio do while
    while @i < @numIntervalos
    begin
	    
        set @vMin = @minSalary + (@i * @intervalo);
        
        set @vMax = 
            case 
                when @i = @numIntervalos - 1 then @maxSalary
                else @minSalary + ((@i + 1) * @intervalo)
            end;

        insert into Histogram(valorMinimo, valorMaximo, total)
        select @vMin, @vMax, count(*)
        from instructor
        where salary >= @vMin and salary < @vMax;
        --insere os dados na tabela

        set @i = @i + 1;
        --incrementa o contador
        
    end
    --fim do while (mt chato n ter chave pra organizar)

    select * from Histogram;

    drop table Histogram;
    --como é criada uma nova table sempre q executada ela tem q ser removida no final da exec sempre
end;
--no meu dbeaver pelo menos, selecione o código da procedure(daqui até o create procedure) e execute

exec salaryHistogram 4;
--e então selecione essa linha e execute
