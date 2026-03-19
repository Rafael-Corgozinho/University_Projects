#include <stdlib.h>
#include <stdio.h>


typedef Struct Node* Pointer;

typedef Struct{
    int value;
    Struct Node* right;
    Struct Node* left;
}Node;

void Initialize(Pointer *p){
    *p = NULL;
}

voind Insert(int v, Pointer *p){
    if(p* == Null){
        Pointer temp = (Pointer)malloc(sizeof(Node));
        temp->value = d;
        temp->left = NULL;
        temp->right = NULL;
        *n = temp;
    }

    if(v < (*n)->value){
        insert(v,&(*n)->left);
    }else if(v > (n*)->value){
        insert(v,&(*n)->right);
    }
}

int main(){
    return 0;
}

