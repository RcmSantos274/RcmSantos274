// Cria uma árvore AVL com número de 1 a 100 aleatórios.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int TipoChave;

typedef struct Registro {
    TipoChave chave;
    /* outros componentes */
} Registro;

typedef struct No {
    Registro Reg;
    struct No *pEsq, *pDir;
} No;

int Altura(No *pRaiz) {
    if (pRaiz == NULL)
        return 0;
    int iEsq = Altura(pRaiz->pEsq);
    int iDir = Altura(pRaiz->pDir);
    return (iEsq > iDir) ? iEsq + 1 : iDir + 1;
}

int FB(No *pRaiz) {
    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

void RSE(No **ppRaiz) {
    No *pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(No **ppRaiz) {
    No *pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsquerda(No **ppRaiz) {
    int fbe = FB((*ppRaiz)->pEsq);
    if (fbe > 0) {
        RSD(ppRaiz);
        return 1;
    } else if (fbe < 0) {
        /* Rotação Dupla Direita */
        RSE(&((*ppRaiz)->pEsq));
        RSD(ppRaiz); /* &(*ppRaiz) */
        return 1;
    }
    return 0;
}

int BalancaDireita(No **ppRaiz) {
    int fbd = FB((*ppRaiz)->pDir);
    if (fbd < 0) {
        RSE(ppRaiz);
        return 1;
    } else if (fbd > 0) {
        /* Rotação Dupla Esquerda */
        RSD(&((*ppRaiz)->pDir));
        RSE(ppRaiz); /* &(*ppRaiz) */
        return 1;
    }
    return 0;
}

int Balanceamento(No **ppRaiz) {
    int fb = FB(*ppRaiz);
    if (fb > 1)
        return BalancaEsquerda(ppRaiz);
    else if (fb < -1)
        return BalancaDireita(ppRaiz);
    else
        return 0;
}

int Insere(No **ppRaiz, Registro *x) {
    if (*ppRaiz == NULL) {
        *ppRaiz = (No *)malloc(sizeof(No));
        (*ppRaiz)->Reg = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    } else if ((*ppRaiz)->Reg.chave > x->chave) {
        if (Insere(&(*ppRaiz)->pEsq, x)) {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    } else if ((*ppRaiz)->Reg.chave < x->chave) {
        if (Insere(&(*ppRaiz)->pDir, x)) {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    } else
        return 0; /* Valor já presente */
    return 0;
}

int EhArvoreArvl(No *pRaiz) {
    if (pRaiz == NULL)
        return 1;

    int fb = FB(pRaiz);
    if (fb > 1 || fb < -1)
        return 0;

    return EhArvoreArvl(pRaiz->pEsq) && EhArvoreArvl(pRaiz->pDir);
}

void ImprimeArvore(No *pRaiz, int nivel) {
    if (pRaiz != NULL) {
        ImprimeArvore(pRaiz->pDir, nivel + 1); // Percorre a subárvore direita

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }

        printf("|-- %d\n", pRaiz->Reg.chave); // Imprime o valor do nó atual com um ramo

        ImprimeArvore(pRaiz->pEsq, nivel + 1); // Percorre a subárvore esquerda
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ... (definições de tipos e estruturas)

int main() {
    No *ppraiz = NULL;
    int n;
    srand(time(0));

    printf("Digite a quantidade de nos: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Registro random;
        random.chave = rand() % 100;
        Insere(&ppraiz, &random);
        Balanceamento(&ppraiz);
    }

    if (EhArvoreArvl(ppraiz)) {
        printf("A arvore esta balanceada.\n");
    } else {
        printf("A arvore nao esta balanceada.\n");
    }

    printf("\nImprimindo arvore:\n");
    ImprimeArvore(ppraiz, 0);

    return 0;
}
