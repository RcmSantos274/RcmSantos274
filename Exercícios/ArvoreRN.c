## CÓDIGO EM PROGRESSO ##
## AINDA NÃO TERMINADO ##


#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1


typedef struct{
    int key;
}Registro;

struct node{
    Registro reg;
    int color;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;

void rotate_left(struct node *n) {
    struct node *new_parent = n->right;
    n->right = new_parent->left;

    if (new_parent->left != NULL)
        new_parent->left->parent = n;

    new_parent->parent = n->parent;

    if (n->parent == NULL)
        root = new_parent;
    else if (n == n->parent->left)
        n->parent->left = new_parent;
    else
        n->parent->right = new_parent;

    new_parent->left = n;
    n->parent = new_parent;
}

void rotate_right(struct node *n) {
    struct node *new_parent = n->left;
    n->left = new_parent->right;

    if (new_parent->right != NULL)
        new_parent->right->parent = n;

    new_parent->parent = n->parent;

    if (n->parent == NULL)
        root = new_parent;
    else if (n == n->parent->right)
        n->parent->right = new_parent;
    else
        n->parent->left = new_parent;

    new_parent->right = n;
    n->parent = new_parent;
}
struct node *grandparent(struct node *n)
{
    if ((n!= NULL) && (n->parent !=NULL))
           return n->parent->parent;
    else 
           return NULL;
}

struct node *uncle (struct node *n)
{
    struct node *g = grandparent(n);
    if(g == NULL)
          return NULL;
    if(n->parent == g->left)
          return g->right;
    else  
          return g->left;
}

void insert_case1(struct node *n)
{
    if(n->parent == NULL)
        n->color = BLACK;

    else 
         insert_case2(n);
}

void insert_case2(struct node *n)
{
    if(n->parent->color == BLACK)
        return;
    
    else 
        insert_case3(n);
}

void insert_case3(struct node *n)
{
    struct node *u = uncle(n), *g;

    if((u != NULL) && (u->color == RED)){
        n->parent->color = BLACK;
        u->color = BLACK;
        g = grandparent(n);
        g->color = RED;
        insert_case1(g);
    }else{
        insert_case4(n);
    }
}

void insert_case4(struct node *n)
{
    struct node *g = grandparent(n);

    if ((n == n->parent->right) && (n->parent == g->left)){
        rotate_left(n->parent);
        n = n->left;
    } else if ((n == n->parent->left) && (n->parent == g->right )){
        rotate_right(n->parent);
        n = n->right;
    }
    insert_case5(n);
}

void insert_case5(struct node *n)
{
    struct node *g = grandparent(n);

    if ((n == n->parent->left) && (n->parent == g->left)){
        rotate_right(g);
    }else{
        /*
        Here, (n == ->parent->right) && (n->parent == g->right).
        */
       rotate_left(g);
    }
    n->parent->color = BLACK;
    g->color = RED;
}

void print_tree(struct node *root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("Key: %d, Color: %s\n", root->reg, (root->color == RED) ? "RED" : "BLACK");
    print_tree(root->right);
}


int main() {
    int num;
    Registro no;

    printf("Digite quantos nos quer implementar na arvore: \n");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        printf("Digite o no[%d]: \n", i + 1);
        scanf("%d", &no.key);

        insert(&root, no);
    }

    printf("Árvore:\n");
    print_tree(root);

    // Libere a memória alocada para a árvore (não implementado neste código)

    return 0;
}
