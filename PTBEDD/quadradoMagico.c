#include <stdio.h>
int TAM = 3;

int verificaQuadradoMagico(int vetor[TAM][TAM]){

    int somaGeral = 0;
    int Linha = 0;
    int Coluna = 0;
    int Diagonal1 = 0;
    int Diagonal2 = 0;

    for (int j = 0; j < TAM; j++) {
        somaGeral += vetor[0][j];
    }

    for (int i = 0; i < TAM; i++) {
        Linha = 0;
        Coluna = 0; 
        for (int j = 0; j < TAM; j++) {
            Linha += vetor[i][j]; 
            Coluna += vetor[j][i]; 
        }
        if (Linha != somaGeral || Coluna != somaGeral) {
            return 0;
        }
    }

    for (int i = 0; i < TAM; i++) {
        Diagonal1 += vetor[i][i]; 
        Diagonal2 += vetor[i][TAM - i - 1]; 
    }

    if (Diagonal1 != somaGeral || Diagonal2 != somaGeral) {
        return 0;
    }

    return 1;
}

int main(){

    
    int vetor[3][3] = {{8, 0, 7}, 
                       {4, 5, 6}, 
                       {3, 10, 8}};

    printf("%d", verificaQuadradoMagico(vetor));

    return 0;
}