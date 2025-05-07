/*EXERCICIO 1*/
/* seleciona o nome do aluno, o número e o nome do curso*/
select student.name, takes.course_ID, course.title 
from student 
join takes on student.id = takes.id
join course on takes.course_id = course.course_id;

/*EXERCICIO 2*/
/*conta a quantidade de cursos feitos por aluno do departamento de engenharia civil*/
select student.id, student.name, count(takes.course_id) as Quantidade_de_Cursos
from student 
join takes on student.id = takes.id
where student.dept_name = 'Civil Eng.'
group by student.id, student.name
order by Quantidade_de_Cursos DESC;

/*EXERCICIO 3*/
/*view que faz a mesma coisa que o exercicio anterior, mas sem a ordenacao*/
create view civil_eng_students (Id_Estudante, Nome_Estudante, Quantidade_de_Cursos) as
select student.id, student.name, count(takes.course_id) as Quantidade_de_Cursos
from student 
join takes on student.id = takes.id
where student.dept_name = 'Civil Eng.'
group by student.id, student.name;

select * from civil_eng_students;
