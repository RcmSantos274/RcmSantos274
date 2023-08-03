#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){

    char palavra[100];
    int tamanho, index = -1, j, count;
    printf("\nDigite a string: ");
    gets(palavra);

    tamanho = strlen(palavra);

    for(int i=0; i<tamanho-1; i++){
        printf("%c = ", palavra[i]);
        count = 0;
        for(j=i+1; j<tamanho; j++){
            printf("%c\n", palavra[j]);
            if (palavra[i] == palavra[j]){
                count++;
                break;
                
            }

        }

        if(count ==0){
            index = i;
            break;
        }
    }
    printf("\no indice e : %d", index);
}
