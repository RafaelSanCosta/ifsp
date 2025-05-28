create trigger dbo.lost_credits
on dbo.takes
after delete as
if (rowcount_big() = 0)
return;
begin
	update dbo.student
	set tot_cred = tot_cred - (select credits from dbo.course inner join deleted on course.course_id = deleted.course_id)
	where student.id = (select distinct id from deleted);
end

SELECT ID, name, dept_name, tot_cred FROM student WHERE ID = '30299';

SELECT * FROM takes t WHERE t.ID = '30299' ORDER BY t.course_id;

DELETE from takes where id = '30299' and course_id = '105';

select * from takes t where id = '30299' and course_id = '105';