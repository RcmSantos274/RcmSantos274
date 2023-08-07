#include <stdio.h>
#include <stdlib.h>

// Criação da Fila
typedef struct {
    char nome[50];
    int tipo;
} Aluno;

typedef struct {
    Aluno *alunos;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
} FilaAlunos;

void inicializarFila(FilaAlunos *fila, int capacidade) 
{
    fila->alunos = (Aluno *)malloc(capacidade * sizeof(Aluno));
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    fila->capacidade = capacidade;
}

int estaVazia(FilaAlunos *fila) 
{
    return (fila->tamanho == 0);
}

int estaCheia(FilaAlunos *fila) 
{
    return (fila->tamanho == fila->capacidade);
}

void enfileirar(FilaAlunos *fila, Aluno aluno) 
{
    if (!estaCheia(fila)) {
        fila->fim = (fila->fim + 1) % fila->capacidade;
        fila->alunos[fila->fim] = aluno;
        fila->tamanho++;
    } else {
        printf("A fila está cheia. Impossível adicionar o aluno.\n");
    }
}

Aluno desenfileirar(FilaAlunos *fila) 
{
    Aluno alunoRemovido = {"", 0};
    if (!estaVazia(fila)) {
        alunoRemovido = fila->alunos[fila->inicio];
        fila->inicio = (fila->inicio + 1) % fila->capacidade;
        fila->tamanho--;
    } else {
        printf("A fila está vazia. Impossível remover aluno.\n");
    }
    return alunoRemovido;
}

void imprimefila(FilaAlunos *fila) 
{
    if (!estaVazia(fila)) {
        int i = fila->inicio;
        int contador = 0;
        while (contador < fila->tamanho) {
            printf("Aluno %d: Nome: %s, Tipo: %d\n", contador + 1, fila->alunos[i].nome, fila->alunos[i].tipo);
            i = (i + 1) % fila->capacidade;
            contador++;
        }
    } else {
        printf("A fila está vazia.\n");
    }
}

void movefinal(FilaAlunos *fila) 
{
    if (!estaVazia(fila)) {
        Aluno alunoRemovido = desenfileirar(fila);
        enfileirar(fila, alunoRemovido);
    } else {
        printf("A fila está vazia. Não há alunos para mover.\n");
    }
}
// Fim das funções criadas para a fila

// Criação da Pilha
typedef struct {
    int tipo;
}Sanduiche;

typedef struct {
    Sanduiche *dados;
    int topo;
    int capacidade;
}Pilha;

void inicializarPilha(Pilha *pilha, int capacidade) 
{
    pilha->dados = (Sanduiche *)malloc(capacidade * sizeof(Sanduiche));
    pilha->topo = -1;
    pilha->capacidade = capacidade;
}

void InserePilha(Pilha *pilha, Sanduiche sanduiches) 
{
    if (pilha->topo == pilha->capacidade - 1) {
        printf("A Pilha de sanduiches está cheia!\n");
        return;
    }
    pilha->dados[++pilha->topo] = sanduiches;
}

void removeTopoPilha(Pilha *pilha) 
{
    if (pilha->topo == -1) {
        printf("A pilha está vazia!\n");
        return;
    }
    pilha->topo--;
}

void imprimePilha(Pilha *pilha) 
{
    printf("Lista de sanduiches\n");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("%d,", pilha->dados[i].tipo);
    }
    printf("\n");
}

void imprimeTopoPilha(Pilha *pilha) 
{
    int i = pilha->topo;
    printf("O Topo é: %d\n", pilha->dados[i].tipo);
}
//Fim das funções criadas da Pilha

int atendeAlunoComSanduiche(FilaAlunos *fila, Pilha *pilha, int *naoAtendidos) 
{
    int alunnot = 0;
    int encontrouCompativel = 0;

    while (!estaVazia(fila)) {
        Aluno aluno = fila->alunos[fila->inicio]; // Atualiza o aluno que esta no inicio da fila
        Sanduiche sanduiche = pilha->dados[pilha->topo]; // Atualizo sanduiche com o conteudo do topo

        if (aluno.tipo == sanduiche.tipo) 
        {
            desenfileirar(fila);
            removeTopoPilha(pilha);
            printf("O aluno %s foi atendido com o sanduiche do tipo %d e ambos foram removidos.\n", aluno.nome, aluno.tipo);
            encontrouCompativel = 1;
            break;
        } else 
        {
            movefinal(fila);
            printf("O aluno %s teve que ir para o final da fila pois o sanduiche não é do tipo preferido.\n", aluno.nome);
            alunnot++;
        }
    }

    if (!encontrouCompativel) 
    {
        printf("Nenhum aluno foi compatível com o sanduiche do topo da pilha.\n");
        *naoAtendidos = alunnot;
        return alunnot;
    }

    // Aqui eu verifico se há mais alunos compativeis na fila
    while (!estaVazia(fila)) 
    {
        Aluno aluno = fila->alunos[fila->inicio];
        Sanduiche sanduiche = pilha->dados[pilha->topo];

        if (aluno.tipo == sanduiche.tipo) 
        {
            desenfileirar(fila);
            removeTopoPilha(pilha);
            printf("O aluno %s foi atendido com o sanduiche do tipo %d e ambos foram removidos.\n", aluno.nome, aluno.tipo);
            alunosNaoAtendidos--;
        } else 
        {
            movefinal(fila);
            printf("O aluno %s teve que ir para o final da fila pois o sanduiche nao e do tipo preferido.\n", aluno.nome);
        }
    }

    printf("Todos os alunos compatíveis foram atendidos.\n");
    *naoAtendidos = alunosNaoAtendidos;
    return alunosNaoAtendidos;
}

int main() 
{
    int capacidade = 4;
    int naoAtend = 0;
    Pilha pilha;
    inicializarPilha(&pilha, capacidade);
    Sanduiche sanduiches;

    FilaAlunos fila;
    Aluno novoaluno;
    inicializarFila(&fila, capacidade);

    // Código para preencher a pilha de sanduíches
    for (int i = 0; i < capacidade; i++) 
    {
        printf("\nDigite o tipo do sanduiche[%d]: ", i + 1);
        scanf("%d", &sanduiches.tipo);
        InserePilha(&pilha, sanduiches);
    }
    imprimePilha(&pilha);

    // Código para preencher a fila de alunos
    for (int i = 0; i < capacidade; i++) 
    {
        printf("\nDigite o nome do aluno[%d]: ", i + 1);
        scanf("%s", novoaluno.nome);
        printf("\nDigite o tipo preferido[%d]: ", i + 1);
        scanf("%d", &novoaluno.tipo);
        enfileirar(&fila, novoaluno);
    }
    imprimefila(&fila);

    for (int i = 0; i < capacidade; i++) 
    {
        int alunosAntes = naoAtend;
        atendeAlunoComSanduiche(&fila, &pilha, &naoAtend);
        if (alunosAntes == naoAtend) {
            break; // Nenhum aluno novo não conseguiu comer o sanduíche preferido, encerra o loop
        }
    }

    // Imprime o número de alunos não atendidos
    printf("\nQuantidade de alunos que não conseguiram comer o sanduiche preferido: %d\n", naoAtend);

    // Liberando a memória alocada
    free(fila.alunos);
    free(pilha.dados);

    return 0;
}
