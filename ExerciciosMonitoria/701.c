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


int main() {
    No *no = NULL;
    int num, opcao;
    int *v;
    v = (int*)malloc(5*sizeof(int));
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 7;

    no = InserirLista(no, v, 5);
    
    do {
        printf("\n ----- Menu -------\n");
        printf("1 - Insere\n2 - Imprime\n3 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("\nDigite o valor: ");
                scanf("%d", &num);
                no = Inserir(no, num);
                break;
            }
            case 2: {
                Imprimir(no, 0);
                break;
            }
            case 3: {
                LiberarArvore(no);
                printf("Saindo do programa.\n");
                break;
            }
            default: {
                printf("Comando invalido!\n");
                break;
            }
        }

    } while (opcao != 3);

    return 0;
}
