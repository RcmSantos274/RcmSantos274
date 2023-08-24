Matriz* matrix_create(void) {
    int m, n;

    printf("Digite o número de linhas: ");
    scanf("%d", &m);

    printf("Digite o número de colunas: ");
    scanf("%d", &n);

    Matriz* head = (Matriz*)malloc(sizeof(Matriz));

    // ...

    for (int i = 0; i < m; i++) {
        // ...

        while (1) {
            int j;
            float value;

            printf("Digite a posição (linha coluna) e o valor (-1 -1 para parar): ");
            int status = scanf("%d %d %f", &i, &j, &value);
            if (status == EOF || i == -1 || j == -1) {
                break;
            }

            // ...

            newElem->info = value;
            // ...
        }

        // ...
    }

    // ...
}


int main(void) {
    /* Inicializacao da aplicacao ... */

    // Matriz A
    printf("Matriz A:\n");
    Matriz* A = matrix_create();
    matrix_print(A);

    // Matriz B
    printf("Matriz B:\n");
    Matriz* B = matrix_create();
    matrix_print(B);
