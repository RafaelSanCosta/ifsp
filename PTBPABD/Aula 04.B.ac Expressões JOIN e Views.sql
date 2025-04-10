/*Exercicio 1*/
select i.id, i.name, count(teaches.sec_id) as Number_Of_Sections
from instructor i  
full outer join teaches on i.id = teaches.id
group by i.id, i.name;
/*resolvi usar o alter join e usei um pouco do codigo da atividade anterior*/


/*Exercicio 2*/
select i.id, i.name,(
select count(t.sec_id) from teaches t where t.id = i.id) as Number_Of_Sections
from instructor i;
/*select dentro de select, bem mais simples do que eu imaginava*/

/*Exercicio 3*/
select s.course_id, s.sec_id, s.semester, s.year, i.id, coalesce(i.name, '-') as instructor_name
from section s
left join teaches t on s.course_id = t.course_id 
                   and s.sec_id = t.sec_id 
                   and s.semester = t.semester 
                   and s.year = t.year
left join instructor i on t.id and s.year = 2010;
/*tive que dar uma pesquisada pra como fazia o que o coalesce faz, alem de que a logica pode ser bagunçada, mas foi o jeito q eu consegui fazer funcionar*/

/*Exercicio 4*/
/*não achei uma forma fácil ou que eu entendesse de como usar os points novamente sem usar o case duas vezes*/
select stu.id, stu.name, c.title, stu.dept_name, t.grade, 
case
	when t.grade = 'A+' then 4
	when t.grade = 'A' then 3.7
	when t.grade = 'A-' then 3.4
	when t.grade = 'B+' then 3.1
	when t.grade = 'B' then 2.8
	when t.grade = 'B-' then 2.5
	when t.grade = 'C+' then 2.2
	when t.grade = 'C' then 1.9
	when t.grade = 'C-' then 1.6
	else null
end as points, c.credits, 
case
	when t.grade = 'A+' then 4
	when t.grade = 'A' then 3.7
	when t.grade = 'A-' then 3.4
	when t.grade = 'B+' then 3.1
	when t.grade = 'B' then 2.8
	when t.grade = 'B-' then 2.5
	when t.grade = 'C+' then 2.2
	when t.grade = 'C' then 1.9
	when t.grade = 'C-' then 1.6
	else null
end * c.credits as Pontos_Totais from student as stu
join takes as t on stu.id = t.id
join course as c on t.course_id = c.course_id;

/*Exercicio 5*/
create view Coeficiente_Rendimento as/*criaçao da view sobre o mesmo codigo*/
select stu.id, stu.name, c.title, stu.dept_name, t.grade, 
case
	when t.grade = 'A+' then 4
	when t.grade = 'A' then 3.7
	when t.grade = 'A-' then 3.4
	when t.grade = 'B+' then 3.1
	when t.grade = 'B' then 2.8
	when t.grade = 'B-' then 2.5
	when t.grade = 'C+' then 2.2
	when t.grade = 'C' then 1.9
	when t.grade = 'C-' then 1.6
	else null
end as points, c.credits, 
case
	when t.grade = 'A+' then 4
	when t.grade = 'A' then 3.7
	when t.grade = 'A-' then 3.4
	when t.grade = 'B+' then 3.1
	when t.grade = 'B' then 2.8
	when t.grade = 'B-' then 2.5
	when t.grade = 'C+' then 2.2
	when t.grade = 'C' then 1.9
	when t.grade = 'C-' then 1.6
	else null
end * c.credits as Pontos_Totais from student as stu
join takes as t on stu.id = t.id
join course as c on t.course_id = c.course_id;
