#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *palavra;
    int tamanhop, i;

    printf("Digite a string: \n");
    palavra = (char *)malloc(100 * sizeof(char));
    fgets(palavra, 100, stdin);
    tamanhop = strlen(palavra);

    for (i = 0; i < tamanhop; i++) {
        if (palavra[i] == 'a' || palavra[i] == 'A' || palavra[i] == 'b' || palavra[i] == 'B') {
            printf("%c", palavra[i]);
        }
    }

    free(palavra);
    return 0;
}
