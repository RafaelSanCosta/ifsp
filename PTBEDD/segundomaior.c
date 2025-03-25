#include <stdio.h>

int segundoMaior(int vetor[], int tamanho){

    int i = 0;
    int maior = -100000;
    int segMaior = -100001;

    //pra achar o maior
    for(i = 0; i<tamanho; i++){
        if(vetor[i] > maior){
            maior = vetor[i];
        }
    }

    for(i = 0; i<tamanho ;i++){
        if(vetor[i] < maior && vetor [i] > segMaior){
            segMaior = vetor[i];
        }
    }

    return segMaior;
}

int main(){

    int vetor[] = {4,2,7,6,5,1,3};

    printf("O Segundo maior alor é : %d",segundoMaior(vetor,7));

    return 0;
}