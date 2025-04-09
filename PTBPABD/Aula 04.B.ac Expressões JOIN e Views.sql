select i.id, i.name, count(teaches.sec_id) as Number_Of_Sections
from instructor i  
join teaches on i.id = teaches.id
group by i.id, i.name;

select * from instructor;
select * from section where sec_id = 1;
select * from takes;
select * from prereq p ;
select * from classroom c;
SELECT * FROM ADVISOR;
select * from course;
select * from department d ;
select * from teaches;


jdbc:sqlserver://myfreesqldbserver-pt3031934.database.windows.net:1433;database=PTBPABD;user=ptbpabd@myfreesqldbserver-pt3031934;password={your_password_here};encrypt=true;trustServerCertificate=false;hostNameInCertificate=*.database.windows.net;loginTimeout=30;