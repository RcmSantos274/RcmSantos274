#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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
                printf("\nDigite a kilometragem da cidade %s para a cidade %s: ", name[i], name[j]);
                scanf("%d", &m[i][j]);
                
                // Considerando 999 como um valor "infinito"
                if (m[i][j] == 0) {
                    m[i][j] = 999;
                }
            }
        }

        int mfinal[v][3];

        // Inicializando a matriz final
        for (int x = 0; x < v; x++) {
            mfinal[x][0] = 0;
            mfinal[x][1] = -1; // Valor inicial para o antecessor
            mfinal[x][2] = INT_MAX;
        }

        // Definindo o vértice de origem (assumindo que seja 0)
        mfinal[0][2] = 0;

        for (int x = 0; x < v; x++) {
            int minIndex = -1;
            int minDist = INT_MAX;

            // Encontrar o vértice não visitado com a menor distância
            for (int w = 0; w < v; w++) {
                if (mfinal[w][0] == 0 && mfinal[w][2] < minDist) {
                    minDist = mfinal[w][2];
                    minIndex = w;
                }
            }

            // Marcar o vértice como visitado
            mfinal[minIndex][0] = 1;

            // Atualizar distâncias para vértices adjacentes
            for (int w = 0; w < v; w++) {
                if (m[minIndex][w] != 999 && mfinal[w][0] == 0 &&
                    mfinal[minIndex][2] + m[minIndex][w] < mfinal[w][2]) {
                    mfinal[w][1] = minIndex;
                    mfinal[w][2] = mfinal[minIndex][2] + m[minIndex][w];
                }
            }
        }

        // Imprimir o resultado
        for (int d = 0; d < v; d++) {
            printf("Matriz final de %s\nFechada: %d\nAntecessor: %s\nPeso: %d\n\n",
                   name[d], mfinal[d][0], name[mfinal[d][1]], mfinal[d][2]);
        }
    } else {
        printf("\nOs vertices devem ser positivos");
    }

    return 0;
}
