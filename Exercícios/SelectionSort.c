#include <stdio.h>

void Select(int data[], int n);

void Select(int data[], int n) {
    int tmp, i, j, minid;

    for (i = 0; i < n - 1; i++) {
        minid = i; // 
        for (j = i + 1; j < n; j++) {
            if (data[j] < data[minid]) {
                minid = j;
            }
        }

        tmp = data[i];
        data[i] = data[minid];
        data[minid] = tmp;
    }
}

int main() {
    int n;
    int data[100];

    printf("Digite a quantidade de numeros: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nDigite o valor do elemento[%d]: ", i + 1);
        scanf("%d", &data[i]);
    }

    Select(data, n); 

    printf("\nNumeros em ordem crescente  :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
