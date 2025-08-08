#include <stdio.h>
#include <string.h>

int sget (char* vetor, int TAM) {
    fflush(stdin);
    if(fgets(vetor, TAM, stdin)){
        int i;
        for(i = 0; vetor[i] != '\n' && vetor[i]; i++)
        ;
        vetor[i] = '\0';
    }

    return 0;
}

struct Alunos
{
    char nome[50];
    int matricula;
    double notaP1;
    double notaP2;
    double notaP3;
    double mediaGeral;
};

int main(){

    struct Alunos alunos[50];
    int maiorNotaP1,maiorMediaGeral,menorMediaGeral;
    double maiorP1 = -5;
    double maiorGeral = -5;
    double menorGeral = 100000;

    for(int i = 0; i < 5; i++){

        printf("\nNovo Aluno\n");
    
        printf("Digite seu nome: ");
        sget(alunos[i].nome, sizeof(alunos[i].nome));
    
        printf("Digite sua matricula: ");
        scanf("%d",&alunos[i].matricula);

        printf("Digite a nota da Primeira Prova: ");
        scanf("%lg",&alunos[i].notaP1);

        printf("Digite a nota da Segunda Prova: ");
        scanf("%lg",&alunos[i].notaP2);

        printf("Digite a nota da Terceira Prova: ");
        scanf("%lg",&alunos[i].notaP3);

        getchar(); //pra remover os '\n' q os scanf deixa pra tras


        if(alunos[i].notaP1 > maiorP1){
            maiorNotaP1 = i; //ele recebe o valor de i pra servir como gps pro indice do aluno no vetor
            maiorP1 = alunos[i].notaP1;
        }

        alunos[i].mediaGeral = (alunos[i].notaP1 + alunos[i].notaP2 + alunos[i].notaP3) / 3;

        if(alunos[i].mediaGeral > maiorGeral){
            maiorMediaGeral = i;
            maiorGeral = alunos[i].mediaGeral;
        }

        if(alunos[i].mediaGeral < menorGeral){
            menorMediaGeral = i;
            menorGeral = alunos[i].mediaGeral;
        }

        if(alunos[i].mediaGeral > 6){
            printf("APROVADO\n");
        } else {
            printf("REPROVADO\n");
        }
    }

    printf("\nAluno com maior nota na primeira prova: \n");
    printf("Nome %s - Nota: %g\n", alunos[maiorNotaP1].nome, alunos[maiorNotaP1].notaP1);

    printf("\nAluno com maior media: \n");
    printf("Nome %s - Nota: %g\n", alunos[maiorMediaGeral].nome, alunos[maiorMediaGeral].mediaGeral);

    printf("\nAluno com menor media: \n");
    printf("Nome %s - Nota: %g\n", alunos[menorMediaGeral].nome, alunos[menorMediaGeral].mediaGeral);

    return 0;
}
