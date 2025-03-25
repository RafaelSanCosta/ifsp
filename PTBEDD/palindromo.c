#include <stdio.h>
#include <string.h>

int verificarPalindromo(char palavra[]) {
    int tamanho = strlen(palavra);
    int dif = 0;

    for (int i = 0; i < tamanho / 2; i++) {
        if (palavra[i] != palavra[tamanho - i - 1]) {
            dif++;  
        }
    }
    if(dif > 0){
       return 0; 
    } else {
        return 1;
    }
}

int main() {
    char palavra[30];

    strcpy(palavra, "subi no onibus");
    printf("%d\n", verificarPalindromo(palavra));

    return 0;
}