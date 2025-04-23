/*Exercicio 1*/
/*criação da tabela*/
create table Pessoa(
ID varchar (10),
nome varchar (20),
sobrenome varchar(30),
idade int,

/*check*/
check (idade > 0)
);

/*Exercicio 2*/
/*adição da constraint unique nas colunas dentro do parenteses*/
alter table Pessoa 
add constraint Uni_Pessoa Unique(ID, nome, sobrenome);

/*Exercicio 3*/
/*isso funciona, apenas adição de not null no final da coluna*/
alter table Pessoa 
alter column idade int not null;

/*Exercicio 4*/

/*Criação da tabela endereço*/
create table Endereco(
ID varchar(10) not null,
rua varchar(100)
);

/*adição da coluna endereço na tabela pessoa, no mesmo tamanho do id*/
alter table Pessoa
add Endereco varchar(10);

/*id virou primary key, porque quando eu fui criar a foreign key dava erro de não achar uma entidade candidata*/
alter table Endereco
add primary key (ID);

/*adição da foreign key referenciando o id da tabela endereço*/
alter table Pessoa 
add constraint FK_Endereco_Pessoa
foreign key (endereco) references Endereco(ID);

