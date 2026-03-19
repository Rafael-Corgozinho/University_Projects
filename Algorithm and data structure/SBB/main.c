#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    V,H
}Inclination;

typedef struct Node *Pointer;

typedef struct Node{
    int height;
    char name[50];
    struct Node *right;
    struct Node *left;
    Inclination BitL,BitR;
} Node;

void LL(Pointer *Ap){
    Pointer Ap1;
    Ap1 = (*Ap)->left; 
    (*Ap)->left = Ap1->right;
    Ap1->right = (*Ap);
    Ap1->BitL = V;
    (*Ap)->BitL = V;
    (*Ap) = Ap1;
}

void RR(Pointer *Ap){
    Pointer Ap1;
    Ap1 = (*Ap)->right;
    (*Ap)->right = Ap1->left;
    Ap1->left = (*Ap);
    Ap1->BitR = V;
    (*Ap)->BitR = V;
    (*Ap) = Ap1;
}

void LR(Pointer *Ap){
    Pointer Ap1, Ap2;
    Ap1 = (*Ap)->left;
    Ap2 = Ap1->right;
    Ap1->BitR = V;
    (*Ap)->BitL = V;
    Ap2->BitL = V;
    Ap1->right = Ap2->left;
    Ap2->left = Ap1;
    (*Ap)->left = Ap2->right;
    Ap2->right = (*Ap);
    (*Ap) = Ap2;
}

void RL(Pointer *Ap){
    Pointer Ap1, Ap2;
    Ap1 = (*Ap)->right;
    Ap2 = Ap1->left;
    Ap1->BitL = V;
    (*Ap)->BitR = V;
    Ap2->BitR = V;
    Ap1->left = Ap2->right;
    Ap2->right = Ap1;
    (*Ap)->right = Ap2->left;
    Ap2->left = (*Ap);
    (*Ap) = Ap2;
}

void InOrder(Pointer p, int *first){
    if(p != NULL){
        InOrder(p->left, first);
        if (*first) {
            printf("%s", p->name);
            *first = 0;
        } else {
            printf(" - %s", p->name);
        }
        InOrder(p->right, first);
    }
}

void Insert(int height, char name[], Pointer *Ap){
    if (*Ap == NULL) {
        *Ap = (Pointer)malloc(sizeof(Node));
        (*Ap)->height = height;
        strcpy((*Ap)->name, name);
        (*Ap)->left = NULL;
        (*Ap)->right = NULL;
        (*Ap)->BitL = H;
        (*Ap)->BitR = H;
        return;
    }

    if (height < (*Ap)->height) {
        Insert(height, name, &(*Ap)->left);
        if ((*Ap)->BitL == H) {
            if ((*Ap)->left->BitL == H) {
                LL(Ap);
                (*Ap)->BitR = H;
            } else if ((*Ap)->left->BitR == H) {
                LR(Ap);
                (*Ap)->BitL = H;
                (*Ap)->BitR = H;
            }
        }
    } else if (height > (*Ap)->height) {
        Insert(height, name, &(*Ap)->right);
        if ((*Ap)->BitR == H) {
            if ((*Ap)->right->BitR == H) {
                RR(Ap);
                (*Ap)->BitL = H;
            } else if ((*Ap)->right->BitL == H) {
                RL(Ap);
                (*Ap)->BitL = H;
                (*Ap)->BitR = H;
            }
        }
    }
}

Pointer RemoveAbsent(Pointer root, char absentName[]) {
    if (root == NULL) return NULL;

    root->left = RemoveAbsent(root->left, absentName);
    root->right = RemoveAbsent(root->right, absentName);

    if (strcmp(root->name, absentName) == 0) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            Pointer temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Pointer successor = root->right;
            while (successor->left != NULL) successor = successor->left;
            strcpy(root->name, successor->name);
            root->height = successor->height;
            root->right = RemoveAbsent(root->right, successor->name);
        }
    }
    return root;
}

int main() {
    int N;
    scanf("%d", &N);
    Pointer root = NULL;
    for (int i = 0; i < N; i++) {
        char name[50];
        int height;
        scanf("%s %d", name, &height);
        Insert(height, name, &root);
    }

    int M;
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        char absent[50];
        scanf("%s", absent);
        root = RemoveAbsent(root, absent);
    }

    int first = 1;
    InOrder(root, &first);
    printf("\n"); 
    return 0;
}