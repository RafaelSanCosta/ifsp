#include <stdio.h>
#define TAM 4

int main(void) {
    double numeros[TAM];
    int i = 0;
    double soma = 0;

    while(i != 5){
        printf("Digite o elemento:\n");
        scanf("%lg",&numeros[i]);
        soma += numeros[i];
        i++;
    }

    double media = soma/5;

    for(i = 0; i < 5; i++){
        if(numeros[i] > media){
            printf("%g ",numeros[i]);
        }
    }

    return 0;
}
