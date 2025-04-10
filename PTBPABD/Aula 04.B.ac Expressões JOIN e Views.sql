/*Exercicio 1*/
select i.id, i.name, count(teaches.sec_id) as Number_Of_Sections
from instructor i  
full outer join teaches on i.id = teaches.id
group by i.id, i.name;


/*Exercicio 2*/
select i.id, i.name,(
select count(t.sec_id) from teaches t where t.id = i.id) as Number_Of_Sections
from instructor i;

/*Exercicio 3*/
select s.course_id, s.sec_id, s.semester, s.year, i.id, coalesce(i.name, '-') AS instructor_name
from section s
left join teaches t on s.course_id = t.course_id 
                   and s.sec_id = t.sec_id 
                   and s.semester = t.semester 
                   and s.year = t.year
left join instructor i on t.id and s.year = 2010;

/*Exercicio 4*/
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
create view Coeficiente_Rendimento as
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
