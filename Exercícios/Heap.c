#include <stdlib.h>
#include <stdio.h>

void criaHeap(int *V, int i, int f);

void heapSort(int *V, int n){
    int i, aux;
    for(i=(n-1)/2; i>=0; i--){
        criaHeap(V, i, n-1);
    }
    for( i = n-1; i>=1; i--){
        aux = V[0];
        V[0] = V[i];
        V[i] = aux;
        criaHeap(V, 0, i-1);
    }
}

void criaHeap(int *V, int i, int f){
    int aux = V[i];
    int j = i * 2 + 1;
    while(j <= f){
        if(j < f){
            if(V[j] < V[j+1]){
                j = j + 1;
            }
        }
        if(aux < V[j]){
            V[i] = V[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
    }
    V[i] = aux;
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);

    heapSort(arr, n);

    printf("Impressao em ordem: \n");
    for (int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
