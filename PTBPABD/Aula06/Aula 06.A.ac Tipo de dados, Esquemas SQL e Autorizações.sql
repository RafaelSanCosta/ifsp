/*Exercício 1*/
create user User_a with password = '156x++1aS';

SELECT name 
FROM sys.database_principals 
WHERE type IN ('S', 'U', 'G', 'R'); -- 'S' = SQL users, 'U' = Windows users, 'G' = groups, 'R' = roles
 /*usei o gpt :), mas isso lista os usuarios*/

drop user user_A;

create user User_A with password = '156x++1aS';
create user User_B with password = '156x++1aS';
create user User_C with password = '156x++1aS';
create user User_D with password = '156x++1aS';
create user User_E with password = '156x++1aS';

/*Exercicio 2*/
grant all privileges on advisor to User_A with grant option;
grant all privileges on company to User_A with grant option;
grant all privileges on course to User_A with grant option;
grant all privileges on department to User_A with grant option;
grant all privileges on endereco to User_A with grant option;
grant all privileges on instructor to User_A with grant option;
grant all privileges on Pessoa to User_A with grant option;
grant all privileges on prereq to User_A with grant option;
grant all privileges on section to User_A with grant option;
grant all privileges on student to User_A with grant option;
grant all privileges on takes to User_A with grant option;
grant all privileges on teaches to User_A with grant option;
grant all privileges on time_slot to User_A with grant option;
/*grant all privileges on classroom to User_A with grant option;*/

/*Exercicio 3*/
select  princ.name
,       princ.type_desc
,       perm.permission_name
,       perm.state_desc
,       perm.class_desc
,       object_name(perm.major_id)
from    sys.database_principals princ
left join
        sys.database_permissions perm
on      perm.grantee_principal_id = princ.principal_id
where princ.name = 'User_A' /*peguei dos exemplos usados na aula e modifiquei essa linha*/
order by princ.name;

