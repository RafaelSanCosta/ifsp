#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){

    double coeficiente[6];
    double polinomio;
    double x=1;

    for(int i = 0; i < 6; i++){
        printf("Digite o coeficiente %d:\n", i);
        scanf("%lg",&coeficiente[i]);
    }

    printf("Digite X: ");
    scanf("%lg", &x);

    while(x!=0){
        polinomio = coeficiente[0] + coeficiente[1] * x + coeficiente [2] * pow(x,2) + coeficiente [3] * pow(x,3) + coeficiente[4] * pow(x,4) + coeficiente[5] * pow (x,5);

        printf("p(%g) = %g\n",x, polinomio);

        printf("Digite X: ");
        scanf("%lg", &x);
    }

    return 0;
}