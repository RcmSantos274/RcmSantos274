#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição da estrutura para representar pares (int, int)
struct Par {
    int primeiro;
    int segundo;
};

// Função de comparação para o heap (min-heap)
int comparar(const void *a, const void *b) {
    return ((struct Par *)a)->primeiro - ((struct Par *)b)->primeiro;
}

// Função para criar um novo par (int, int)
struct Par criarPar(int primeiro, int segundo) {
    struct Par par;
    par.primeiro = primeiro;
    par.segundo = segundo;
    return par;
}

int* Frequentes(int* numeros, int tamanho, int k, int* tamanhoRetornado) {
    // Contagem de frequência dos números usando um dicionário simples (array)
    int maxNum = 10001; // Assumindo que os números estão no intervalo [0, 10000]
    int frequencia[maxNum];
    memset(frequencia, 0, sizeof(frequencia));

    for (int i = 0; i < tamanho; i++) {
        frequencia[numeros[i]]++;
    }

    // Criando um heap (min-heap) para armazenar os K elementos mais frequentes
    struct Par heap[k];
    int tamanhoHeap = 0;

    for (int i = 0; i < maxNum; i++) {
        if (frequencia[i] > 0) {
            if (tamanhoHeap < k) {
                heap[tamanhoHeap++] = criarPar(frequencia[i], i);
                if (tamanhoHeap == k) {
                    // Construir o heap (min-heap) usando qsort
                    qsort(heap, k, sizeof(struct Par), comparar);
                }
            } else if (frequencia[i] > heap[0].primeiro) {
                heap[0] = criarPar(frequencia[i], i);
                // Reordenar o heap (min-heap) após a substituição
                qsort(heap, k, sizeof(struct Par), comparar);
            }
        }
    }

    // Criando o vetor de resposta com os K elementos mais frequentes
    int* resposta = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        resposta[i] = heap[i].segundo;
    }

    *tamanhoRetornado = k;
    return resposta;
}

int main() {
    int numeros[] = {1, 1, 1, 2, 2, 3};
    int k = 2;
    int tamanhoRetornado;
    
    int* resultado = Frequentes(numeros, sizeof(numeros) / sizeof(numeros[0]), k, &tamanhoRetornado);

    printf("Os %d elementos mais frequentes são: ", k);
    for (int i = 0; i < tamanhoRetornado; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");

    free(resultado);

    return 0;
}
