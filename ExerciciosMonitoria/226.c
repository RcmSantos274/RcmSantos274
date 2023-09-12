#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    struct no *esq, *dir;
    int valor;
    int altura;
} No;

No *NovoNo(int x) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo != NULL) {
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    } else {
        printf("Nao foi possivel alocar esse no");
    }
    return novo;
}

int Maior(int a, int b) {
    return (a > b) ? a : b;
}

int Altura(No *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

int FB(No *no) {
    if (no != NULL) {
        return (Altura(no->esq) - Altura(no->dir));
    } else {
        return 0;
    }
}

No *RotaEsq(No *raiz) {
    if (raiz == NULL || raiz->dir == NULL)
        return raiz;

    No *y = raiz->dir;
    No *f = y->esq;

    y->esq = raiz;
    raiz->dir = f;

    raiz->altura = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    y->altura = Maior(Altura(y->esq), Altura(y->dir)) + 1;

    return y;
}

No *RotaDir(No *raiz) {
    if (raiz == NULL || raiz->esq == NULL)
        return raiz;

    No *y = raiz->esq;
    No *f = y->dir;

    y->dir = raiz;
    raiz->esq = f;

    raiz->altura = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    y->altura = Maior(Altura(y->esq), Altura(y->dir)) + 1;

    return y;
}

No *RotacaoEsqDir(No *raiz) {
    if (raiz == NULL)
        return raiz;

    raiz->esq = RotaEsq(raiz->esq);
    return RotaDir(raiz);
}

No *RotacaoDirEsq(No *raiz) {
    if (raiz == NULL)
        return raiz;

    raiz->dir = RotaDir(raiz->dir);
    return RotaEsq(raiz);
}

No *Balancear(No *raiz) {
    if (raiz == NULL)
        return raiz;

    int fb = FB(raiz);

    if (fb < -1 && FB(raiz->dir) <= 0) {
        return RotaEsq(raiz);
    } else if (fb > 1 && FB(raiz->esq) >= 0) {
        return RotaDir(raiz);
    } else if (fb > 1 && FB(raiz->esq) < 0) {
        return RotacaoEsqDir(raiz);
    } else if (fb < -1 && FB(raiz->dir) > 0) {
        return RotacaoDirEsq(raiz);
    }

    return raiz;
}

No *Inserir(No *raiz, int x) {
    if (raiz == NULL)
        return NovoNo(x);
    else {
        if (x < raiz->valor)
            raiz->esq = Inserir(raiz->esq, x);
        else if (x > raiz->valor)
            raiz->dir = Inserir(raiz->dir, x);
        else
            printf("Insercao nao realizada!\n");
    }

    raiz->altura = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;

    raiz = Balancear(raiz);

    return raiz;
}

void LiberarArvore(No *raiz) {
    if (raiz != NULL) {
        LiberarArvore(raiz->esq);
        LiberarArvore(raiz->dir);
        free(raiz);
    }
}

void Imprimir(No *raiz, int nivel) {
    int i;
    if (raiz != NULL) {
        Imprimir(raiz->dir, nivel + 1);
        printf("\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        Imprimir(raiz->esq, nivel + 1);
    }
}



No *InserirLista(No *raiz, int valores[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        raiz = Inserir(raiz, valores[i]);
    }
    return raiz;
}

No *InverterArvore(No *raiz) {
    if (raiz == NULL)
        return NULL;

    No *temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;

    InverterArvore(raiz->esq);
    InverterArvore(raiz->dir);

    return raiz;
}



int main() {
    No *no = NULL;
    int *v;
    v = (int*)malloc(7*sizeof(int));
    v[0] = 4;
    v[1] = 2;
    v[2] = 7;
    v[3] = 1;
    v[4] = 3;
    v[5] = 6;   
    v[6] = 9;
    

    no = InserirLista(no, v, 7);
    
    Imprimir(no, 0);
    InverterArvore(no);
    printf("\n");
    printf("-----------------------");
    printf("\n");
    Imprimir(no, 0);
    return 0;
}
