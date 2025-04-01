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

struct Aluno
{
    char nome[50];
    int matricula;
    char curso[50];

};

int main(){

    struct Aluno aluno[50];

    for(int i = 0; i < 5; i++){

    printf("\nNovo Aluno\n");
    
    printf("Digite seu nome: ");
    sget(aluno[i].nome, sizeof(aluno[i].nome));
    
    printf("Digite seu curso: ");
    sget(aluno[i].curso, sizeof(aluno[i].curso));
    
    printf("Digite sua matricula: ");
    scanf("%d",&aluno[i].matricula);

    getchar(); //pra remover os '\n' q os scanf deixa pra tras
    }

    printf("\nALUNOS MATRICULADOS\n");
    for(int i = 0; i < 5; i++){
        printf("Nome: %s - Curso: %s - Matricula: %d\n",aluno[i].nome, aluno[i].curso, aluno[i].matricula);
    }

    return 0;
}
