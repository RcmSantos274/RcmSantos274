#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(int *V, int inicio, int meio, int fim);

void merge_sort(int *V, int inicio, int fim){

    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim) /2);
        merge_sort(V, inicio, meio);
        merge_sort(V, meio+1, fim);
        merge(V, inicio, meio , fim);
    }
}

void merge(int *V, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio+1;
    p1 = inicio;
    p2 = meio+1;
    temp = (int *) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(i = 0; i<tamanho; i++){
            if(!fim1 && !fim2){
               if(V[p1] < V[p2])
                  temp[i] = V[p1++];
                else 
                   temp[i] = V[p2++];
                
                if(p1>meio) fim1 = 1;
                if(p2>fim) fim2=1;
            }
            else{
                if(!fim1)
                   temp[i] = V[p1++];
                else 
                   temp[i]=V[p2++];
            }
               
        }
        for(j=0, k=inicio; j<tamanho; j++, k++)
           V[k]=temp[j];
    }
    free(temp);
}

int main(){
    int *V = 0, tam;

    printf("Digite o tamanho do vetor : ");
    scanf("%d", &tam);

    V = (int *)malloc(tam * sizeof(int));

    for (int i = 0; i<tam; i++){
        printf("\nDigite o valor do vetor[%d]: ", i);
        scanf("%d", &V[i]);
    }

    if(V == NULL){
      printf("Nao foi possivel alocar memoria");
      return 1;
    }

    merge_sort(V, 0, tam - 1);
    
    printf("\nImprimindo em ordem\n");
    for (int j = 0; j<tam; j++){
        printf("%d ", V[j]);
    }

    free(V);
}
