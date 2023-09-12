#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Quicksort(int *V, int left, int right) {
    int mid, tmp, i, j;
    i = left;
    j = right;
    mid = V[(int)floor((right + left) / 2)];

    do {
        while (V[i] < mid)
            i++;
        while (mid < V[j])
            j--;
        if (i <= j) {
            tmp = V[i];
            V[i] = V[j];
            V[j] = tmp;  
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j)
        Quicksort(V, left, j);
    if (i < right)
        Quicksort(V, i, right);
}

int main() {
    int *V, tam;

    printf("Digite a quantidade de elementos: ");
    scanf("%d", &tam);

    V = (int *)malloc(tam * sizeof(int));

    for (int i = 0; i < tam; i++) {
        printf("Digite o valor do elemento[%d]: ", i);
        scanf("%d", &V[i]);
    }

    Quicksort(V, 0, tam - 1);

    printf("\nListando\n");
    for (int j = 0; j < tam; j++) {
        printf("%d ", V[j]);
    }

    free(V);

    return 0;
}
