#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* estudantes;
    int N;
    int quantidadeEstudantes;
} SalaDeProva;

SalaDeProva* criarSalaDeProva(int n) {
    SalaDeProva* sala = (SalaDeProva*)malloc(sizeof(SalaDeProva));
    sala->N = n;
    sala->quantidadeEstudantes = 0;
    sala->estudantes = (int*)malloc(n * sizeof(int));
    return sala;
}

int max(int a, int b) {
    return a > b ? a : b; // se a for maior que b retorna a e se b for maior que a retorna b
}

int sentar(SalaDeProva* sala) {
    if (sala->quantidadeEstudantes == 0) {
        sala->estudantes[0] = 0;
        sala->quantidadeEstudantes++;
        return 0;
    }

    int d = max(sala->estudantes[0], sala->N - 1 - sala->estudantes[sala->quantidadeEstudantes - 1]);
    for (int i = 0; i < sala->quantidadeEstudantes - 1; i++) {
        d = max(d, (sala->estudantes[i + 1] - sala->estudantes[i]) / 2);
    }

    if (sala->estudantes[0] == d) {
        for (int i = sala->quantidadeEstudantes; i > 0; i--) {
            sala->estudantes[i] = sala->estudantes[i - 1];
        }
        sala->estudantes[0] = 0;
        sala->quantidadeEstudantes++;
        return 0;
    }

    for (int i = 0; i < sala->quantidadeEstudantes - 1; i++) {
        if ((sala->estudantes[i + 1] - sala->estudantes[i]) / 2 == d) {
            for (int j = sala->quantidadeEstudantes; j > i + 1; j--) {
                sala->estudantes[j] = sala->estudantes[j - 1];
            }
            sala->estudantes[i + 1] = (sala->estudantes[i + 1] + sala->estudantes[i]) / 2;
            sala->quantidadeEstudantes++;
            return sala->estudantes[i + 1];
        }
    }

    sala->estudantes[sala->quantidadeEstudantes] = sala->N - 1;
    sala->quantidadeEstudantes++;
    return sala->N - 1;
}

void sair(SalaDeProva* sala, int p) {
    for (int i = 0; i < sala->quantidadeEstudantes; i++) {
        if (sala->estudantes[i] == p) {
            for (int j = i; j < sala->quantidadeEstudantes - 1; j++) {
                sala->estudantes[j] = sala->estudantes[j + 1];
            }
            sala->quantidadeEstudantes--;
            return;
        }
    }
}

void destruirSalaDeProva(SalaDeProva* sala) {
    free(sala->estudantes);
    free(sala);
}

int main() {
    SalaDeProva* sala = criarSalaDeProva(10);
    printf("%d\n", sentar(sala));
    printf("%d\n", sentar(sala));
    printf("%d\n", sentar(sala));
    sair(sala, 1);
    printf("%d\n", sentar(sala));
    destruirSalaDeProva(sala);
    return 0;
}
