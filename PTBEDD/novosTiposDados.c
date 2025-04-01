#include <stdio.h>
#include <string.h>

struct Horario
{
    int hora;
    int minutos;
    int segundos;
};

struct Data
{
    int dia;
    int mes;
    int ano;
};

struct Compromisso
{
    struct Data data;
    struct Horario horario;
    char descricao[50];
};

int main(){

    struct Compromisso compromisso;

    //definindo a data do compromisso diretamente na estrutura compromisso
    compromisso.data.dia = 1;
    compromisso.data.mes = 5;
    compromisso.data.ano = 2025;

    /*
    uma variavel
    struct Data data;
    data.dia = 1;
    data.mes = 5;
    data.ano = 2025;

    compromisso.data = data
    acredito que isso funcione
    */

    //definindo o horario
    compromisso.horario.hora = 12;
    compromisso.horario.minutos = 30;
    compromisso.horario.segundos = 00;

    strcpy(compromisso.descricao, "Feriado, logo descanso");

    printf("Compromisso:\n");
    printf("Data: %02d/%02d/%d\n", compromisso.data.dia, compromisso.data.mes, compromisso.data.ano);
    printf("Horario: %02d:%02d:%02d\n", compromisso.horario.hora, compromisso.horario.minutos, compromisso.horario.segundos);
    printf("Descricao: %s\n", compromisso.descricao);

    return 0;
}