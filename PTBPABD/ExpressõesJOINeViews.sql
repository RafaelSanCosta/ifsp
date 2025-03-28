/*Joins*/
--slide 14
select * from student join takes on student.id = takes.id;

--slide 16
SELECT * FROM student LEFT OUTER JOIN takes ON student.ID = takes.ID WHERE takes.course_id IS NULL;

--slide 17
--mesma coisa do de cima, apenas o inverso
SELECT * FROM takes RIGHT OUTER JOIN student ON student.ID = takes.ID WHERE takes.course_id IS NULL;.

--slide 19
SELECT * FROM 
(SELECT * FROM student s WHERE s.dept_name = 'Comp. Sci.') st
FULL OUTER JOIN 
(SELECT * FROM takes t WHERE t.semester = 'Spring' and t.[year] = 2009) ta ON st.ID = ta.ID;

/*Views*/

SELECT ID, name, dept_name FROM instructor;

/* mostra o nome dos instrutores a partir de um departamento */
CREATE VIEW faculty AS SELECT ID, name, dept_name FROM instructor;

SELECT name FROM faculty WHERE dept_name = 'Biology';

/*pega a soma total dos salários por departamento*/
CREATE VIEW departments_total_salary (dept_name, total_salary) as
SELECT dept_name, sum(salary)
FROM instructor
GROUP BY dept_name;

SELECT * from departments_total_salary order by total_salary desc;

/* filtra o curso de geografia de outuno de 2009, selecionando o curso id, o id da sessão, prédio e número da sala */
CREATE VIEW geology_fall_2009 as
SELECT
	course.course_id, sec_id, building, room_number
FROM
	course, section
WHERE
	course.course_id = section.course_id
	and course.dept_name = 'Geology'
	and section.semester = 'Fall'
	and section.year = 2009;

/* essa pega a ultima como atalho, mas apresentando o curso e número de sala de um prédio específico, o whitman*/
CREATE VIEW geology_fall_2009_Whitman as
    SELECT course_id, room_number FROM geology_fall_2009 WHERE building = 'Whitman';

SELECT * FROM geology_fall_2009_Whitman;
