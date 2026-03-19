#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 7
#define N 50
#define VAZIO "!!!!!!!!!!"
#define RETIRADO "**********"

typedef char TipoChave[N];
typedef struct TipoItem {
    TipoChave Chave;
} TipoItem;

typedef TipoItem TipoDicionario[M];

void Inicializa(TipoDicionario T) {
    for (int i = 0; i < M; i++) {
        strcpy(T[i].Chave, VAZIO);
    }
}

unsigned int h(TipoChave chave) {
    unsigned int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % M;
}

int Pesquisa(TipoChave chave, TipoDicionario T) {
    unsigned int i = 0, inicial = h(chave);
    while (strcmp(T[(inicial + i) % M].Chave, VAZIO) != 0 &&
           strcmp(T[(inicial + i) % M].Chave, chave) != 0 && i < M) {
        i++;
    }
    if (strcmp(T[(inicial + i) % M].Chave, chave) == 0)
        return (inicial + i) % M;
    else
        return -1;
}

int Insere(TipoChave chave, TipoDicionario T) {
    if (Pesquisa(chave, T) != -1) return 0; 
    unsigned int i = 0, inicial = h(chave);
    while (strcmp(T[(inicial + i) % M].Chave, VAZIO) != 0 &&
           strcmp(T[(inicial + i) % M].Chave, RETIRADO) != 0 && i < M) {
        i++;
    }
    if (i < M) {
        strcpy(T[(inicial + i) % M].Chave, chave);
        return 1;
    }
    return 0; 
}

int main() {
    TipoDicionario tabela;
    char nome[N];
    char carro1[3][N], carro2[3][N];
    int n, i = 0, c1 = 0, c2 = 0;

    Inicializa(tabela);

    scanf("%d\n", &n);
    while (i < n && c1 + c2 < 6) {
        fgets(nome, N, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if (Insere(nome, tabela)) {
            if (c1 < 3) strcpy(carro1[c1++], nome);
            else if (c2 < 3) strcpy(carro2[c2++], nome);
        }
        i++;
    }

    printf("- Primeiro Carro: ");
    for (i = 0; i < c1; i++) printf("%s - ", carro1[i]);
    printf("\n");

    printf("- Segundo Carro: ");
    for (i = 0; i < c2; i++) printf("%s - ", carro2[i]);
    printf("\n");

    while (1) {
        fgets(nome, N, stdin);
        nome[strcspn(nome, "\n")] = '\0';
        if (strcmp(nome, "0") == 0) break;

        if (Pesquisa(nome, tabela) != -1)
            printf("Aluno Confirmado\n");
        else
            printf("Aluno Não Confirmado\n");
    }

    return 0;
}
