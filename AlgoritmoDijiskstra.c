#include <stdlib.h>
#include <stdio.h>

int main() {
    int v;

    printf("\nDigite a quantidade de vertices: ");
    scanf("%d", &v);

    if (v > 0) {
        int m[v][v];
        char name[v][30];

        for (int f = 0; f < v; f++) {
            printf("\nNome do vertice %d: ", f);
            scanf("%s", name[f]);
        }

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                if (i != j) {
                    printf("\nDigite a kilometragem da cidade %s para a cidade %s: ", name[i], name[j]);
                    scanf("%d", &m[i][j]);
                }
            }
        }

        for (int s = 0; s < v; s++) {
            for (int l = 0; l < v; l++) {
                if (s != l && m[s][l]!= 0) {
                    printf("\nA kilometragem da cidade %s para a cidade %s e: %d", name[s], name[l], m[s][l]);
                }
            }
        }


    } else {
        printf("\nAs vertices tem que ser positivas");
    }

    for (int )

    return 0;
}
