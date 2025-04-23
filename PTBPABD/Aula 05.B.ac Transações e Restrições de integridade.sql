/*Exercicio 1*/
Create Schema avaliacaocontinua;

/*Exercicio 2*/
create table avaliacaocontinua.company(
company_name varchar(50) not null,
city varchar(50),
PRIMARY KEY(company_name)
);
/*eu tentei usar apenas Primary key, mas não estava funcionando*/ 
/*ok, tava fazendo errado e arrumei usando apenas o PK*/
/*o sgbd decidiu dar uma de python e as linhas tinham que estar uma atras da outra sem linha vazia pra funcionar*/

/*Exercicio 3*/
create table avaliacaocontinua.employee(
person_name varchar(100) not null primary key,
street varchar (50),
city varchar(50)
);

/*Exercicio 4*/
create table avaliacaocontinua.manages(
person_name varchar(100) not null primary key,
manager_name varchar(100)
);

/*exercicio 5*/
create table avaliacaocontinua.works (
person_name varchar(100) not null primary key,
company_name varchar(50) not null,
salary numeric(6,2)
);

/*Exercicio 6*/
alter table avaliacaocontinua.works
add constraint FK_Person_Works
foreign key (person_name) references avaliacaocontinua.employee(person_name)
on update cascade
on delete cascade;

/*Exercicio 7*/
alter table avaliacaocontinua.works
add constraint FK_Company_Works
foreign key (company_name) references avaliacaocontinua.company(company_name)
on update cascade
on delete cascade;

/*exercicio 8*/
alter table avaliacaocontinua.manages 
add constraint FK_Person_Manages
foreign key (person_name) references avaliacaocontinua.employee(person_name)
on update cascade
on delete cascade;
