#include <stdio.h>
#include <locale.h>

int cont(int vetor[], int qntd){
    int contador = 0;
    for(int i = 0; i < qntd; i++){
        if(vetor[i] % 2 == 0){
            contador++;
        }
    }
    return contador;
}

int main(void) {
    int v[] = {1,2,3,4,5,6};
    printf("%d", cont(v,6) );
    
    return 0;
}