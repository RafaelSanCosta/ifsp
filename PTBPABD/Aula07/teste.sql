/*Exercício 1*/
create procedure dbo.student_grade_points @S_grade varchar(2),
										@S_return varchar(max) out 
as
	begin
		set nocount on;
		set @S_return = (select s.name, s.dept_name, c.title, c.dept_name, t.semester, t.year, t.grade, g.points from
		(((takes t join student s on t.ID = s.ID) join course c on t.course_id = c.course_id)) join grade_points g on t.grade = g.grade);
	end
	
declare @S_grade varchar(2);
declare





select * from takes,student;
select * from student;
select * from takes;
select * from course;

CREATE VIEW grade_points AS (SELECT grade, 
IIF(grade = 'A+', 4.0, 
IIF(grade = 'A ', 3.7, 
IIF(grade = 'A-', 3.3, 
IIF(grade = 'B+', 3.0, 
IIF(grade = 'B ', 2.7, 
IIF(grade = 'B-', 2.3, 
IIF(grade = 'C+', 2.0, 
IIF(grade = 'C ', 1.7, 
IIF(grade = 'C-', 1.3, 0))))))))) as points
FROM takes
group by grade);
