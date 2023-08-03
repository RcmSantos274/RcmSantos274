#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){

    char palavra[100], arm[100];
    int tamanho;
    printf("\nDigite a string: ");
    gets(palavra);

    tamanho = strlen(palavra);

    for(int i=0; i<tamanho; i++){
        arm[i] = 0;
        for(int j=0; i<tamanho; i++){
            if (palavra[i] == palavra[j+1]){
                arm[i] = +1;
            }

        }

        
    }
}
