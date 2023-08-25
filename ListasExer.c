#include <stdio.h>
#include <stdlib.h>

// FB = AlturaEsq - AlturaDir

// Se FB > 1, então realiza rotação pra direita
// Se FB < -1, então realiza rotação pra esquerda

typedef struct no{
    struct no *esq, *dir;
    int valor;
    int altura;
}No;

No *NovoNo(int x)
{
   No *novo = (No *)malloc(sizeof(No));

   if (novo != NULL)
   {
      novo->valor = x;
      novo->esq = NULL;
      novo->dir = NULL;
      novo->altura = 0;
   }
   else
   {
    printf("Nao foi possivel alocar esse no");
   }
   return novo;

}


int Maior (int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Altura (No *no)
{
    if(no == NULL)
    {
        return -1;
    }
    else
    {
        return no->altura;
    }
}

int *FB(No *no)
{
    if(no != NULL)
    {
        return (altura(no->esq) - altura(no->dir));
    }
    else
    {
        return 0;
    }

    }

No *RotaEsq(No *raiz)
{
    No *y, *f;

    y = raiz->dir;
    f = y->esq;

    y->esq = raiz;
    raiz->dir = f;

    raiz = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    y = Maior(Altura(y->esq), Altura(y->dir) +1); 
    
    return y;
}

No *RotaDir(No *raiz)
{
    No *y, *f;

    y = raiz->esq;
    f = y->dir;

    y->dir = raiz;
    raiz->dir = f;

    raiz = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    y = Maior(Altura(y->esq), Altura(y->dir))+1;

    return y;
}

No *RotacaoEsqDir(No *raiz)
{
    raiz->esq = RotEsq(raiz->esq);
    return RotDir(raiz);

}

No *RotacaoDirEsq(No *raiz)
{
    raiz->dir = RotDir(raiz->dir);
    return RotaEsq(raiz);
}

No *Inserir(No *raiz, int x)
{
    if(raiz == NULL)
       return NovoNo(x);
    else
    {
        if(x <raiz->valor)
            raiz->esq = inserir(raiz->esq, x);
        else if(x > raiz->valor)
            raiz->dir = inserir(raiz->dir, x);
        else 
            printf("Insercao nao realizada!");
    }
    
    // recalcula a altura dos nós da arvore e do no inserido
    raiz->altura = Maior(Altura(raiz->esq), Altura(raiz->dir)) +1;

    raiz = Balancear(raiz); // verifica se precisa balancear a arvore

}

No *Balancear(No *raiz)
{
    int fb = FB(raiz);
    //Rotação a esquerda
    if(fb < -1 && FB(raiz->dir) <= 0)
       raiz = RotaEsq(raiz);
    
    //Rotação a direita
    else if ( fb > 1 && FB(raiz->esq) >= 0)
       raiz = RotaDir(raiz);
    
    // Rotação dupla á esquerda
    else if(fb > 1 && FB(raiz->esq) < 0)
       raiz = RotacaoEsqDir(raiz);
    
    //Rotação dupla à direita 

    else if (fb < -1 && FB(raiz->dir) > 0)
       raiz = RotacaoDirEsq(raiz);
    
    return raiz;
}

void Imprimir (No *raiz, int nivel)
{
    int i;
    if(raiz != NULL)
    {
        Imprimir(raiz->dir, nivel + 1);
        printf("/n/n");

        for(i = 0; i< nivel; i++)
           printf("/t");

        printf("%d", raiz->valor);
        Imprimir(raiz->esq, nivel +1);
    }
}
