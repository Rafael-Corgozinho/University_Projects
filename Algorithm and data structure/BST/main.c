#include <stdlib.h>
#include <stdio.h>

typedef struct Node* Pointer;

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

void initialize(Pointer *n) {
    *n = NULL;
}

Pointer insert(int d, Pointer *n) {
    if (*n == NULL) {
        Pointer temp = (Pointer)malloc(sizeof(Node));
        if (temp == NULL) {
            printf("Error allocating memory.\n");
            return NULL;
        }
        temp->value = d;
        temp->left = NULL;
        temp->right = NULL;
        *n = temp; 
        return temp;
    }
    if (d < (*n)->value) {
        return insert(d, &(*n)->left); 
    } else if (d > (*n)->value) {
        return insert(d, &(*n)->right); 
    }
    return *n; 
}

void printInOrder(Pointer n) {
    if (n != NULL) {
        printInOrder(n->left);
        printf("%d ", n->value);
        printInOrder(n->right);
    }
}

void freeTree(Pointer n) {
    if (n != NULL) {
        freeTree(n->left);
        freeTree(n->right);
        free(n);
    }
}

int main() {
    Pointer root;
    initialize(&root);

    // Example insertions
    insert(10, &root);
    insert(5, &root);
    insert(15, &root);
    insert(3, &root);
    insert(7, &root);
    insert(12, &root);
    insert(18, &root);

    // Print the values in order
    printf("Valores na árvore em ordem: ");
    printInOrder(root);
    printf("\n");

    // Free the allocated memory
    freeTree(root);

    return 0;
}