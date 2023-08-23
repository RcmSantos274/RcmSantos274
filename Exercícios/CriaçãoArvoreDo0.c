#include <stdio.h>
#include <stdlib.h>

struct No{
    struct No *esq;
    struct No *dir;
    int valor;
};
typedef struct No NoArv;

NoArv *Insere1(NoArv *raiz, int num)
{   
    if (raiz == NULL)
    {
        NoArv *aux = (NoArv *)malloc(sizeof(NoArv));
        aux->valor = num;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }

    else if(num == raiz->valor){
        printf("Numero Ja Existente");
        return raiz;
    }
    else 
    {
        if(num < raiz->valor)
        {
            raiz->esq = Insere1(raiz->esq, num);
            return raiz;
        }
        else if(num > raiz->valor)
        {
            raiz->dir = Insere1(raiz->dir, num);
            return raiz;
        }
    }
}

void Imprime(NoArv *raiz)
{
    if (raiz != NULL)
    {
        Imprime(raiz->esq);
        printf("%d ", raiz->valor);
        Imprime(raiz->dir);
    }
}

/*NoArv *Remover(NoArv *raiz, int num)
{
    if(num == raiz->valor)
    {
        raiz->valor = NULL;
    }
    else
    {
        if(num < raiz->valor)
        {
            raiz->esq = Remover(raiz->esq, num);
            return raiz;
        }
        else if(num > raiz->valor)
        {
            raiz->dir = Remover(raiz->dir, num);
            return raiz;
        }
    }
}*/

int main ()
{
    NoArv *raiz = NULL;
    int opcao = 0, num = 0, num2 = 0;

    do
    {
        printf("\n------Menu------\n1 - Insere\n2 - Imprime\n3 - Sair\n- ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                printf("\nDigite o valor: ");
                scanf("%d", &num);
                raiz = Insere1(raiz, num);
                break;
            }
            case 2:
            {
                printf("Ordem da impressao da arvore : Esquerda, Raiz , Direita\n");
                Imprime(raiz);
                break;
            }
            case 3:
            {
                break;
            }
            default: 
            {
                printf("Opcao Invalida");
                break;
            }
        }

    }while(opcao != 3);

}
