#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct{
    int tipo;
}Sanduiche;

typedef struct{
    Sanduiche dados[MAX];
    int topo;
}Pilha;

void insere(Pilha *pilha, Sanduiche sanduiches){
    if(pilha->topo == MAX-1){
        printf("A Pilha de sanduiches esta cheia!\n");
        return;
    }
    pilha->dados[++pilha->topo] = sanduiches;
}

void removetopo(Pilha *pilha){
    if (pilha->topo == -1){
        printf("A pilha esta vazia!\n");
        return;
    }
    pilha->topo--;
}

void imprime(Pilha *pilha){
    printf("Lista de sanduiches\n");
    for(int i = pilha->topo; i>=0; i--){
        printf("%d,", pilha->dados[i].tipo);
    }
    printf("\n");
}

void imprimetopo(Pilha *pilha){
    int i = pilha->topo;
    printf("O Topo e : %d\n", pilha->dados[i].tipo);
}


int main(){
    Pilha pilha;
    pilha.topo = -1;
    Sanduiche sanduiches;
    int alunos[MAX];

    for(int i=0; i<MAX; i++){ 
        printf("\nDigite o tipo do sanduiche[%d]: ", i+1);
        scanf("%d", &sanduiches.tipo);
        insere(&pilha, sanduiches);
    }
}

    



