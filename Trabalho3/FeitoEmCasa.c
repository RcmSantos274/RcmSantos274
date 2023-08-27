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

void encontrar_altura(No *raiz, int x, int nivel, int *altura) {
    if (raiz == NULL)
        return;

    if (raiz->valor == x) {
        *altura = nivel;
        return;
    }

    encontrar_altura(raiz->esq, x, nivel + 1, altura);
    encontrar_altura(raiz->dir, x, nivel + 1, altura);
}

// LCA da árvore binária
No *ancestral_comum(No *raiz, int p, int q) {
    if (raiz == NULL || raiz->valor == p || raiz->valor == q)
        return raiz;

    No *esq = ancestral_comum(raiz->esq, p, q);
    No *dir = ancestral_comum(raiz->dir, p, q);

    if (esq == NULL)
        return dir;
    else if (dir == NULL)
        return esq;
    else
        return raiz;
}

int sao_primos(No *raiz, int x, int y) {
    if (raiz == NULL)
        return 0;

    int altura_x, altura_y;
    int altura_ancestral = -1;

    encontrar_altura(raiz, x, 0, &altura_x);
    encontrar_altura(raiz, y, 0, &altura_y);
    encontrar_altura(raiz, ancestral_comum(raiz, x, y)->valor, 0, &altura_ancestral);

    if (altura_x == altura_y && abs(altura_x - altura_ancestral) > 1)
        return 1;
    else
        return 0;
}

int main() {
    No *no = NULL;
    int num, opcao;

    do {
        printf("\n ----- Menu -------\n");
        printf("1 - Insere\n2 - Imprime\n3 - Verifica Primo    4 - Sair\n");
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
            int valor1, valor2;
            printf("Digite os valores dos nos: ");
            scanf("%d %d", &valor1, &valor2);

            if (sao_primos(no, valor1, valor2)) {
                printf("Os nos %d e %d sao primos.\n", valor1, valor2);
            } else {
                printf("Os nos %d e %d nao sao primos.\n", valor1, valor2);
            }
            break;
        }
            case 4: {
                LiberarArvore(no);
                printf("Saindo do programa.\n");
                break;
            }
            default: {
                printf("Comando invalido!\n");
                break;
            }
        }

    } while (opcao != 4);

    return 0;
}
