#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

typedef struct no {
    int valor;
    struct no *esq, *dir;
} No;

bool ArvoreValida(No *no, No *noMinimo, No *noMaximo) {
    if (no == NULL) {
        return true;
    }

    if ((noMinimo != NULL && no->valor <= noMinimo->valor) ||
        (noMaximo != NULL && no->valor >= noMaximo->valor)) {
        return false;
    }

    return ArvoreValida(no->esq, noMinimo, no) &&
           ArvoreValida(no->dir, no, noMaximo);
}

bool eArvoreBuscaValida(No *raiz) {
    return ArvoreValida(raiz, NULL, NULL);
}

No *NovoNo(int x) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo != NULL) {
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
    } else {
        printf("Nao foi possivel alocar esse no");
    }
    return novo;
}

int main() {


    No *raiz = NovoNo(5);
    raiz->esq = NovoNo(1);
    raiz->dir = NovoNo(4);
    raiz->dir->esq = NovoNo(3);
    raiz->dir->dir = NovoNo(6);

    /* 
    No *raiz = NovoNo(2);
    raiz->esq = NovoNo(1);
    raiz->dir = NovoNo(3);
    */

    if (eArvoreBuscaValida(raiz)) {
        printf("Verdadeiro\n");
    } else {
        printf("Falso\n");
    }

    if (raiz->esq != NULL)
        free(raiz->esq);
    free(raiz->dir->esq);
    free(raiz->dir->dir);
    free(raiz->dir);
    free(raiz);

    return 0;
}
