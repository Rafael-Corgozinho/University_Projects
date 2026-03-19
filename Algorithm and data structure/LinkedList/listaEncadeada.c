#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaEncadeada.h"

void inicializar(ListaP* listap) {
    listap->inicio = NULL;
    listap->fim = NULL;
    listap->tamanho = 0;
}

Apontador* criarApontador(Aluno* a) {
    Apontador* novoApontador = (Apontador*)malloc(sizeof(Apontador));
    if (novoApontador == NULL) {
        printf("Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoApontador->aluno = (Aluno*)malloc(sizeof(Aluno));
    if (novoApontador->aluno == NULL) {
        printf("Erro na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    memcpy(novoApontador->aluno, a, sizeof(Aluno));
    novoApontador->prox = NULL;

    return novoApontador;
}

void inserirAlunoP(ListaP* listap, Aluno* a) {
    Apontador* novoApontador = criarApontador(a);

    if (listap->inicio == NULL) {
        listap->inicio = novoApontador;
    } else {
        listap->fim->prox = novoApontador;
    }
    listap->fim = novoApontador;
    listap->tamanho++;
}

int removerAlunoP(ListaP* listap, int matricula) {
    Apontador *anterior = NULL, *atual = listap->inicio;

    while (atual != NULL && atual->aluno->matricula != matricula) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return 0; 
    }

    if (anterior == NULL) {
        listap->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    if (atual == listap->fim) {
        listap->fim = anterior;
    }

    free(atual->aluno);
    free(atual);
    listap->tamanho--;
    return 1; 
}

void imprimirListaP(ListaP* listap) {
    Apontador *atual = listap->inicio;

    while (atual != NULL) {
        printf("Matricula: %d, Nome: %s, Nota: %.2f\n",
               atual->aluno->matricula,
               atual->aluno->nome,
               atual->aluno->nota);
        atual = atual->prox;
    }
}