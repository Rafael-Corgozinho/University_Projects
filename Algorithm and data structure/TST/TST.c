#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct Node* Pointer;

typedef struct Node {
    char value;
    unsigned FlagEnd: 1;
    struct Node *left, *eq, *right;
} Node;

struct Node* newNode(char value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = value;
    temp->FlagEnd = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

void insert(Pointer *root, char* word) {
    if (!(*root))
        *root = newNode(*word);

    if ((*word) < (*root)->value)
        insert(&(*root)->left, word);
    else if ((*word) > (*root)->value)
        insert(&(*root)->right, word);
    else {
        if (*(word + 1))
            insert(&(*root)->eq, word + 1);
        else
            (*root)->FlagEnd = 1;
    }
}

int searchTST(Pointer root, char* word) {
    if (!root)
        return 0;
    if (*word < root->value)
        return searchTST(root->left, word);
    else if (*word > root->value)
        return searchTST(root->right, word);
    else {
        if (*(word + 1) == '\0')
            return root->FlagEnd;
        return searchTST(root->eq, word + 1);
    }
}

int main() {
    int p;
    char name[50];
    Pointer root = NULL;
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        scanf("%s", name);
        insert(&root, name);
    }
    scanf("%d", &p);  
    while (p != 0) {
        scanf("%s", name);  
        if (searchTST(root, name)) {
            printf("Pessoa Encontrada\n");
        } else {
            printf("Pessoa Não Encontrada\n");
        }
        scanf("%d", &p);  
    }
    return 0;
}